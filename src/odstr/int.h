struct TicketD { /* distribution */
    MPI_Comm cart;
    int rank[27];
    MPI_Request send_size_req[27], recv_size_req[27];
    MPI_Request send_mesg_req[27], recv_mesg_req[27];
    MPI_Request send_ii_req[27], recv_ii_req[27];
    bool first = true;
    sub::Distr distr; /* was odstr; */
};

struct Work {
    uchar4 *subi_lo, *subi_re; /* local remote subindices */
    uint   *iidx;              /* scatter indices         */
    Particle *pp_re;           /* remote particles        */
    int *ii_re;                /* remote ids              */
    unsigned char *count_zip;
};

void alloc_ticketD(TicketD *t) {
    l::m::Comm_dup(m::cart, &t->cart);
    t->distr.ini(t->cart, t->rank);
    t->first = true;
}

void free_ticketD(/**/ TicketD *t) {
    t->distr.fin();
}

void alloc_work(Work *w) {
    mpDeviceMalloc(&w->subi_lo);
    mpDeviceMalloc(&w->subi_re);
    mpDeviceMalloc(&w->iidx);
    mpDeviceMalloc(&w->pp_re);
    if (global_ids) mpDeviceMalloc(&w->ii_re);
    CC(cudaMalloc(&w->count_zip, sizeof(w->count_zip[0])*XS*YS*ZS));
}

void free_work(Work *w) {
    CC(cudaFree(w->subi_lo));
    CC(cudaFree(w->subi_re));
    CC(cudaFree(w->iidx));
    CC(cudaFree(w->pp_re));
    if (global_ids) CC(cudaFree(w->ii_re));
    CC(cudaFree(w->count_zip));
}

void distr(flu::Quants *q, TicketD *td, flu::TicketZ *tz, Work *w) {
    MPI_Comm cart = td->cart; /* can be a copy */
    int *rank = td->rank; /* arrays */
    MPI_Request *send_size_req = td->send_size_req;
    MPI_Request *recv_size_req = td->recv_size_req;
    MPI_Request *send_mesg_req = td->send_mesg_req;
    MPI_Request *recv_mesg_req = td->recv_mesg_req;
    MPI_Request *send_ii_req = td->send_ii_req;
    MPI_Request *recv_ii_req = td->recv_ii_req;
    bool *qfirst = &td->first; /* shoud be updated */

    float4  *zip0 = tz->zip0;
    ushort4 *zip1 = tz->zip1;

    uchar4 *subi_lo = w->subi_lo; /* arrays */
    uchar4 *subi_re = w->subi_re;
    uint   *iidx = w->iidx;
    unsigned char *count_zip = w->count_zip;
    Particle *pp_re = w->pp_re;
    int *ii_re = w->ii_re;

    int n = q->n;
    bool first = *qfirst;
    Particle *pp  = q->pp;
    Particle *pp0 = q->pp0;
    int *ii  = q->ii;
    int *ii0 = q->ii0;
    sub::Distr *D = &td->distr;
  
    int nbulk, nhalo;
    D->post_recv(cart, rank, /**/ recv_size_req, recv_mesg_req);
    if (global_ids) D->post_recv_ii(cart, rank, /**/ recv_ii_req);
    
    if (n) {
        D->halo(pp, n);
        D->scan(n);
        D->pack_pp(pp, n);
        if (global_ids) D->pack_ii(ii, n);
        dSync();
    }
    if (!first) {
        D->waitall(send_size_req);
        D->waitall(send_mesg_req);
        if (global_ids) D->waitall(send_ii_req);
    }
    first = false;
    nbulk = D->send_sz(cart, rank, send_size_req);
    D->send_pp(cart, rank, send_mesg_req);
    if (global_ids) D->send_ii(cart, rank, send_ii_req);

    CC(cudaMemsetAsync(q->cells->count, 0, sizeof(int)*XS*YS*ZS));
    if (n)
    k_common::subindex_local<false><<<k_cnf(n)>>>
        (n, (float2*)pp, /*io*/ q->cells->count, /*o*/ subi_lo);

    D->waitall(recv_size_req);
    D->recv_count(&nhalo);
    D->waitall(recv_mesg_req);
    if (global_ids) D->waitall(recv_ii_req);
    
    if (nhalo) {
        D->unpack_pp(nhalo, /*o*/ pp_re);
        if (global_ids) D->unpack_ii(nhalo, ii_re);
        D->subindex_remote(nhalo, /*io*/ pp_re, q->cells->count, /**/ subi_re);
    }
    
    k_common::compress_counts<<<k_cnf(XS*YS*ZS)>>>
        (XS*YS*ZS, (int4*)q->cells->count, /**/ (uchar4*)count_zip);
    l::scan::d::scan(count_zip, XS*YS*ZS, /**/ (uint*)q->cells->start);

    if (n)
    sub::dev::scatter<<<k_cnf(n)>>>
        (false, subi_lo,  n, q->cells->start, /**/ iidx);

    if (nhalo)
    sub::dev::scatter<<<k_cnf(nhalo)>>>
        (true, subi_re, nhalo, q->cells->start, /**/ iidx);

    n = nbulk + nhalo;
    if (n) {
        sub::dev::gather_pp<<<k_cnf(n)>>>((float2*)pp, (float2*)pp_re, n, iidx,
                                          /**/ (float2*)pp0, zip0, zip1);

        if (global_ids)
        sub::dev::gather_id<<<k_cnf(n)>>>(ii, ii_re, n, iidx, /**/ ii0);
        
    }

    q->n = n;
    *qfirst = first;

    /* swap */
    q->pp = pp0; q->pp0 = pp; 
    if (global_ids) {
        q->ii = ii0; q->ii0 = ii;
    }
}
