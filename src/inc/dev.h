/* ceiling `m' to `n' (returns the smallest `A' such n*A is not less than `m') */
#define ceiln(m, n) (   ((m) + (n) - 1)/(n)   )

/* a common kernel execution configuration */
#define k_cnf(n) ceiln((n), 128), 128

#define dSync() CC(d::DeviceSynchronize())

/* test if inside device function                                 */
/* useful for small differences in __device__ __host__ functions */
#define DEVICE_FUNC (defined (__CUDA_ARCH__) && (__CUDA_ARCH__ > 0))

#define D2D cudaMemcpyDeviceToDevice
#define D2H cudaMemcpyDeviceToHost
#define H2D cudaMemcpyHostToDevice
#define H2H cudaMemcpyHostToHost
#define A2A cudaMemcpyDefault /* "[a]ll to [a]ll" */

#define cD2D(t, f, n) CC(cudaMemcpy((t), (f), (n) * sizeof((f)[0]), D2D))
#define cH2H(t, f, n) CC(cudaMemcpy((t), (f), (n) * sizeof((f)[0]), H2H))  /* [t]to, [f]rom */
#define cA2A(t, f, n) CC(cudaMemcpy((t), (f), (n) * sizeof((f)[0]), A2A))

#define cD2H(h, d, n) CC(cudaMemcpy((h), (d), (n) * sizeof((h)[0]), D2H))
#define cD2H0(H, D, n) CC(d::Memcpy((H), (D), (n) * sizeof((H)[0]), D2H))

#define cH2D(d, h, n) CC(cudaMemcpy((d), (h), (n) * sizeof((h)[0]), H2D))
#define cH2D0(D, H, n) CC(d::Memcpy((D), (H), (n) * sizeof((H)[0]), H2D))

#define aD2D(t, f, n) CC(d::MemcpyAsync((t), (f), (n) * sizeof((f)[0]), D2D))
#define aH2H(t, f, n) CC(cudaMemcpyAsync((t), (f), (n) * sizeof((f)[0]), H2H))  /* [t]to, [f]rom */
#define aA2A(t, f, n) CC(cudaMemcpyAsync((t), (f), (n) * sizeof((f)[0]), A2A))
#define aD2H(h, d, n) CC(cudaMemcpyAsync((h), (d), (n) * sizeof((h)[0]), D2H))
#define aH2D(d, h, n) CC(cudaMemcpyAsync((d), (h), (n) * sizeof((h)[0]), H2D))
#define aH2D0(D, H, n) CC(d::MemcpyAsync((D), (H), (n) * sizeof((H)[0]), H2D))

/* device allocation */
#define Dalloc(d, n) CC(cudaMalloc((d), (n) * sizeof((**(d)))))
#define Dfree(d)     CC(cudaFree(d))
#define Dfree0(D)    CC(d::Free(D))

/* generic device allocation: TODO: */
#define Dalloc000000(D, sz) d::Malloc((void**)(void*)(D), (sz))
#define Dalloc000(D, sz)    CC(Dalloc000000(D, sz))
#define Dalloc0(D, n)       CC(Dalloc000000(D, (n) * sizeof(**(D))))

/* pinned memory allocation */
#define Palloc(d, n) CC(cudaHostAlloc((d), (n) * sizeof((**(d))), cudaHostAllocMapped))
#define Pfree(d)     CC(cudaFreeHost(d))

/* generic pinned memory allocation */
#define Palloc0(D, n) CC(d::HostAlloc((void**)(void*)(D), (n) * sizeof(**(D)), cudaHostAllocMapped))

#define Link(D, H) CC(d::HostGetDevicePointer((void**)(void*)(D), H,   0))

/* [d]evice set */
#define Dset(P, v, n) CC(cudaMemset(P, v, (n)*sizeof(*(P))))
#define Dzero(P, n)   Dset(P, 0, n)

/* [d]evice [a]synchronous set */
#define DsetA(P, v, n) CC(d::MemsetAsync(P, v, (n)*sizeof(*(P))))
#define DzeroA(P, n)   DsetA(P, 0, n)

template <typename T> struct DeviceBuffer {
    /* `C': capacity; `S': size; `D' : data*/
    int C, S; T *D;
    explicit DeviceBuffer(int n = 0) : C(0), S(0), D(NULL) { resize(n); }
    ~DeviceBuffer() {
        if (D != NULL) CC(cudaFree(D));
        D = NULL;
    }

    void resize(int n) {
        S = n;
        if (C >= n) return;
        if (D != NULL) CC(cudaFree(D));
        int conservative_estimate = (int)ceil(1.1 * n);
        C = 128 * ((conservative_estimate + 129) / 128);
        CC(cudaMalloc(&D, sizeof(T) * C));
    }
};

template <typename T> struct PinnedHostBuffer {
private:
    int capacity;
public:
    /* `S': size; `D' is for data; `DP' device pointer */
    int S;  T *D, *DP;
    explicit PinnedHostBuffer(int n = 0)
        : capacity(0), S(0), D(NULL), DP(NULL) {
        resize(n);
    }

    ~PinnedHostBuffer() {
        if (D != NULL) CC(cudaFreeHost(D));
        D = NULL;
    }

    void resize(const int n) {
        S = n;
        if (capacity >= n) return;
        if (D != NULL) CC(cudaFreeHost(D));
        const int conservative_estimate = (int)ceil(1.1 * n);
        capacity = 128 * ((conservative_estimate + 129) / 128);

        CC(cudaHostAlloc(&D, sizeof(T) * capacity, cudaHostAllocMapped));

        CC(cudaHostGetDevicePointer(&DP, D, 0));
    }

    void preserve_resize(const int n) {
        T *old = D;
        const int oldS = S;
        S = n;
        if (capacity >= n) return;
        const int conservative_estimate = (int)ceil(1.1 * n);
        capacity = 128 * ((conservative_estimate + 129) / 128);
        D = NULL;
        CC(cudaHostAlloc(&D, sizeof(T) * capacity, cudaHostAllocMapped));
        if (old != NULL) {
            CC(cudaMemcpy(D, old, sizeof(T) * oldS, H2H));
            CC(cudaFreeHost(old));
        }
        CC(cudaHostGetDevicePointer(&DP, D, 0));
    }
};
