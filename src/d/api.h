namespace d {  /* a wrapper for device API */
int ini();
const char *emsg(); /* last error message */

int Malloc(void **p, size_t);
int MemcpyToSymbol(const void *symbol, const void *src, size_t count, size_t offset=0,
                           enum cudaMemcpyKind kind=cudaMemcpyHostToDevice);
int HostAlloc(void **pHost, size_t size, unsigned int flags);
int HostGetDevicePointer(void **pDevice, void *pHost, unsigned int flags);
int Memcpy (void *dst, const void *src, size_t count, enum cudaMemcpyKind kind);
int MemsetAsync (void *devPtr, int value, size_t count, cudaStream_t stream=0);
int Memset (void *devPtr, int value, size_t count);
int MemcpyAsync (void * dst, const void * src, size_t count, enum cudaMemcpyKind
                 kind, cudaStream_t stream = 0);
int Free (void *devPtr);
int DeviceSynchronize (void);
}
