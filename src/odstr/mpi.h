namespace odstr {
namespace sub {

void waitall(MPI_Request *reqs) {
    MPI_Status statuses[123];
    l::m::Waitall(26, reqs, statuses) ;
}

void post_recv(const MPI_Comm cart, const int rank[], const int btc, const int btp,
               MPI_Request *size_req, MPI_Request *mesg_req, Recv *r) {
    for(int i = 1, c = 0; i < 27; ++i)
    l::m::Irecv(r->size + i, 1, MPI_INTEGER, rank[i],
                btc + r->tags[i], cart, size_req + c++);

    for(int i = 1, c = 0; i < 27; ++i)
    l::m::Irecv(r->pp.hst[i], MAX_PART_NUM, MPI_FLOAT, rank[i],
                btp + r->tags[i], cart, mesg_req + c++);
}

void post_recv_ii(const MPI_Comm cart, const int rank[], const int tags[], const int bt, /**/ MPI_Request *ii_req, Pbufs<int> *rii) {
    for(int i = 1, c = 0; i < 27; ++i)
    l::m::Irecv(rii->hst[i], MAX_PART_NUM, MPI_INT, rank[i],
                bt + tags[i], cart, ii_req + c++);
}

int send_sz(MPI_Comm cart, const int rank[], const int btc, /**/ Send *s, MPI_Request *req) {
    for(int i = 0; i < 27; ++i) s->size[i] = s->size_pin.D[i];
    for(int i = 1, cnt = 0; i < 27; ++i)
    l::m::Isend(s->size + i, 1, MPI_INTEGER, rank[i],
                btc + i, cart, &req[cnt++]);
    return s->size[0]; /* `n' bulk */
}

void send_pp(MPI_Comm cart, const int rank[], const int btp, /**/ Send *s, MPI_Request *req) {
    for(int i = 1, cnt = 0; i < 27; ++i)
    l::m::Isend(s->pp.hst[i], s->size[i] * 6, MPI_FLOAT, rank[i],
                btp + i, cart, &req[cnt++]);
}

void send_ii(MPI_Comm cart, const int rank[], const int size[], const int bt, /**/ Pbufs<int> *sii, MPI_Request *req) {
    for(int i = 1, cnt = 0; i < 27; ++i)
    l::m::Isend(sii->hst[i], size[i], MPI_INT, rank[i],
                bt + i, cart, &req[cnt++]);
}

/* TODO: this is not used, why? */
void cancel_recv(/**/ MPI_Request *size_req, MPI_Request *mesg_req) {
    for(int i = 0; i < 26; ++i) l::m::Cancel(size_req + i) ;
    for(int i = 0; i < 26; ++i) l::m::Cancel(mesg_req + i) ;
}
}
