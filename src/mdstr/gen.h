namespace mdstr {
namespace gen {

template <typename T>
struct pbuf { /* pack buffer */
    T *dd[27];
};

enum DataLoc {Host, Device};

template <typename T, DataLoc> void cpy_pck (T *dst, const T *src, int n);
template <typename T, DataLoc> void cpy_upck(T *dst, const T *src, int n);
template <typename T> MPI_Datatype MType();

template <typename T, DataLoc LOC>
void pack(int *reord[27], const int counts[27],  const T *dd, int npd, /**/ pbuf<T> *b) {
    int fid, count, j, src;
    for (fid = 0; fid < 27; ++fid) {
        count = counts[fid];
        for (j = 0; j < count; ++j) {
            src = reord[fid][j];
            cpy_pck <LOC> (b->dd[fid] + j * npd, dd + src * npd, npd);
        }
    }
}

template <typename T>
void post_send(int npd, const int counts[27], const pbuf<T> *b, MPI_Comm cart, int bt, int rnk_ne[27],
               /**/ MPI_Request sreq[26]) {
    for (int i = 1; i < 27; ++i)
        MC(l::m::Isend(b->dd[i], npd * counts[i], MType<T>(), rnk_ne[i], bt + i, cart, sreq + i - 1));
}

template <typename T>
void post_recv(MPI_Comm cart, int nmax, int bt, int ank_ne[27], /**/ pbuf<T> *b, MPI_Request rreq[26]) {
    for (int i = 1; i < 27; ++i)
        MC(l::m::Irecv(b->dd[i], nmax, MType<T>, ank_ne[i], bt + i, cart, rreq + i - 1));
}

// TODO make it generic
int unpack(int nv, Particle *const ppr[27], const int counts[27], /**/ Particle *pp) {
    int nm = 0;
    for (int i = 0; i < 27; ++i) {
        int c = counts[i];
        int n = c * nv;
        if (n) {
            CC(cudaMemcpyAsync(pp + nm * nv, ppr[i], n * sizeof(Particle), H2D));
            if (i) dev::shift <<<k_cnf(n)>>> (n, i, /**/ pp + nm * nv);
        } 
        nm += c;
    }
    return nm;
}

void shift();

/* template specializations */

template <typename T, Host>
void cpy_pck(T *dst, const T *src, int n) { memcpy(dst, src, n*sizeof(T)); }

template <typename T, Device>
void cpy_pck(T *dst, const T *src, int n) { CC(cudaMemcpy(dst, src, n*sizeof(T), D2H)); }

template <typename T, Host>
void cpy_upck(T *dst, const T *src, int n) { memcpy(dst, src, n*sizeof(T)); }

template <typename T, Device>
void cpy_upck(T *dst, const T *src, int n) { CC(cudaMemcpy(dst, src, n*sizeof(T), H2D)); }

MPI_Datatype MType<int>()      {return MPI_INT;}
MPI_Datatype MType<Particle>() {return datatype::particle;}
MPI_Datatype MType<Solid>()    {return datatype::solid;}

} // gen
} // mdstr
