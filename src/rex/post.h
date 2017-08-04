namespace rex {
bool post_check() {
    bool packingfailed;
    int i;
    packingfailed = false;
    for (i = 0; i < 26; ++i) packingfailed |= send_counts[i] > local[i]->size();
    return packingfailed;
}

void post_resize() {
    int sizes[26];
    int *indexes[26];
    int i;
    for (i = 0; i < 26; ++i) sizes[i] = local[i]->size();
    CC(cudaMemcpyToSymbolAsync(k_rex::g::sizes, sizes, sizeof(sizes), 0, H2D));
    for (i = 0; i < 26; ++i) indexes[i] = local[i]->indexes->D;
    CC(cudaMemcpyToSymbolAsync(k_rex::g::indexes, indexes, sizeof(indexes), 0, H2D));
}

void local_resize() {
    int i;
    for (i = 0; i < 26; ++i) local[i]->resize(send_counts[i]);
}

}
