#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "bop_common.h"
#include "bop_serial.h"

#include "macros.h"
#include "pp_id.h"

enum {X, Y, Z, D};
enum {EMPTY=0, OCCUPIED=1};

struct Args {
    int L[D];
    char **pp;
    char **ii;
    int n;
};

static void usg() {
    fprintf(stderr, "Usage: po.disp <Lx> <Ly> <Lz> <rr-*.bop> -- <ii-*.bop>\n");
    exit(1);
}

static int shift_args(int *c, char ***v) {
    (*c)--;
    (*v)++;
    return (*c) > 0;
}

static void parse(int argc, char **argv, Args *a) {
    int n, found_separator;    

    // skip executable
    if (!shift_args(&argc, &argv)) usg();
    a->L[X] = atoi(*argv);

    if (!shift_args(&argc, &argv)) usg();
    a->L[Y] = atoi(*argv);

    if (!shift_args(&argc, &argv)) usg();
    a->L[Z] = atoi(*argv);

    if (!shift_args(&argc, &argv)) usg();
    a->pp = argv;

    found_separator = 0;
    n = 0;    
    do {
        if (0 == strcmp(*argv, "--")) {
            found_separator = 1;
            break;
        }
        ++n;
    } while (shift_args(&argc, &argv));

    if (n <= 1) ERR("Need more than one file\n");
    if (!found_separator) usg();

    if (!shift_args(&argc, &argv)) usg();

    a->n = n;
    a->ii = argv;

    if (argc != n) usg();
}

void empty_tags(const int bufsize, int *tags) {
    for (int i = 0; i < bufsize; ++i) tags[i] = EMPTY;
}

void compute_tags(const int *ii, const int n, int *tags) {
    int j, i;
    for (j = 0; j < n; ++j) {
        i = ii[j];
        tags[i] = OCCUPIED;
    }
}

void disp_1p(const int L[3], const float *rp, const float *rc, float *dr) {
    int c, sign;
    for (c = 0; c < 3; ++c) {
        dr[c] = rc[c] - rp[c];
        sign = dr[c] > 0 ? 1 : -1;
        dr[c] -= fabs(dr[c]) > L[c]/2 ? sign * L[c] : 0.f;        
    }
}

void disp(const int L[3], const float *rrp, const float *rrc, const int buffsize, /**/ float *ddr) {
    int i;
    const float *rp, *rc;
    float *dr;
    for (i = 0; i < buffsize; ++i) {
        rp = rrp + 3*i;
        rc = rrc + 3*i;
        dr = ddr + 3*i;
        disp_1p(L, rp, rc, /**/ dr);
    }
}

void outname(const char *inrr, char *out) {
    const int l = strlen(inrr);
    memcpy(out, inrr, l * sizeof(char));
    const int strt = l - 4;
    const char newext[] = ".disp";
    memcpy(out + strt, newext, sizeof(newext));
}

static int collect(const float *rr, const float *ddr, int nmax, const int *tags, const int *ii, /**/ float *pp) {
    int i, c, j = 0, id;
    const float *r, *dr;
    float *p;

    for (i = 0; i < nmax; ++i)
    if (tags[i] == OCCUPIED) {
        id = ii[j];
        r  = rr  + 3 * id;
        dr = ddr + 3 * id;
        p = pp + 6 * j;
        for (c = 0; c < 3; ++c) {
            p[c + 0] = r[c];
            p[c + 3] = dr[c];
        }
        ++j;
    }
    return j;
}


void dump(const BopType type, const char *fout, const float *rr, const float *ddr, const int *tags, const int *ii, const int buffsize, /*w*/ float *work) {
    BopData *d;
    int n = collect(rr, ddr, buffsize, tags, ii, /**/ work);
    
    /* dump */
    
    BPC( bop_ini(&d) );
    BPC( bop_set_n(n, d) );
    BPC( bop_set_vars(6, "x y z dx dy dz", d) );
    BPC( bop_set_type(type, d) );    

    BPC( bop_alloc(d) );
    
    memcpy(bop_get_data(d), work, n * 6 * sizeof(float));

    BPC( bop_write_header(fout, d) );
    BPC( bop_write_values(fout, d) );

    BPC( bop_fin(d) );
}

int main(int argc, char **argv) {
    Args a;
    long np, buffsize;
    int nvars, i;
    BopType type;
    BopData *dpp, *dii;
    const int *ii;
    int *iip;
    const float *pp;
    float *rrc, *rrp, *ddr, *rrw;
    int *tags;
    
    parse(argc, argv, &a);

    BPC( bop_ini(&dpp) );
    BPC( bop_ini(&dii) );
    
    read_data(a.pp[0], dpp, a.ii[0], dii);

    pp = (const float *) bop_get_data(dpp);
    ii = (const   int *) bop_get_data(dii);

    BPC( bop_get_n(dii, &np) );
    BPC( bop_get_nvars(dpp, &nvars) );
    buffsize = max_index(ii, np) + 1;

    iip  = new int  [buffsize];   /* global ids of previous */
    rrc  = new float[D*buffsize]; /* current  positions     */
    rrp  = new float[D*buffsize]; /* previous positions     */
    ddr  = new float[D*buffsize]; /* displacements          */
    rrw  = new float[6*buffsize]; /* work                   */
    tags = new int[buffsize];     /* tags: particle with this id or not? */

    memset(rrp, 0, 3*buffsize*sizeof(float));
    pp2rr_sorted(ii, pp, np, nvars, /**/ rrp);

    empty_tags(buffsize, /**/ tags);
    compute_tags(ii, np, /**/ tags);
    memcpy(iip, ii, buffsize*sizeof(int));

    BPC( bop_fin(dpp) );
    BPC( bop_fin(dii) ); 
    
    for (i = 0; i < a.n-1; ++i) {
        char fout[1024] = {0};
        BPC( bop_ini(&dpp) );
        BPC( bop_ini(&dii) );

        outname(a.pp[i], /**/ fout);
        printf("%s -- %s -> %s\n", a.pp[i], a.ii[i], fout);

        read_data(a.pp[i+1], dpp, a.ii[i+1], dii);
        pp = (const float *) bop_get_data(dpp);
        ii = (const   int *) bop_get_data(dii);

        BPC( bop_get_n(dii, &np) );
        BPC( bop_get_type(dpp, &type) );
        
        pp2rr_sorted(ii, pp, np, nvars, /**/ rrc);

        disp(a.L, rrp, rrc, buffsize, /**/ ddr);

        dump(type, fout, rrp, ddr, tags, iip, buffsize, /*w*/ rrw);
        compute_tags(ii, np, /**/ tags);
        memcpy(iip, ii, buffsize*sizeof(int));
        
        BPC( bop_fin(dpp) );
        BPC( bop_fin(dii) ); 

        {   /* swap */
            float *const tmp = rrp;
            rrp = rrc; rrc = tmp;
        }
    }

    delete[] rrp; delete[] rrc;
    delete[] ddr; delete[] rrw;
    delete[] tags; delete[] iip;
    
    return 0;
}

/*
  
  # nTEST: small.t0
  # make install -j
  # po.disp 4 4 4 data/s-??.bop -- data/id-??.bop
  # cp data/s-00.disp.values disp.out.txt

 */
