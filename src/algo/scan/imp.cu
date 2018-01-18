#include <stdio.h>
#include <conf.h>
#include "inc/conf.h"

#include "inc/def.h"
#include "inc/dev.h"
#include "utils/imp.h"
#include "utils/error.h"
#include "utils/cc.h"
#include "utils/kl.h"
#include "d/api.h"
#include "d/q.h"
#include "d/ker.h"

#include "algo/scan/imp.h"
#include "algo/scan/dev.h"

#if   defined(DEV_CUDA)
  #include "algo/scan/cuda/type.h"
  #include "algo/scan/cuda/imp.h"
#elif defined(DEV_CPU)
  #include "algo/scan/cpu/type.h"
  #include "algo/scan/cpu/imp.h"
#else
  #error DEV_* is undefined
#endif
