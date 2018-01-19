#include <stdio.h>

#include "utils/error.h"
#include "parser/imp.h"

#include "imp.h"

static void set(const Config *cfg, const char *desc, int kind, Dbg *dbg) {
    int enabled = 0;
    UC(conf_lookup_bool(cfg, desc, &enabled));
    if (enabled) dbg_enable (kind, dbg);
    else         dbg_disable(kind, dbg);
}

void dbg_set_conf(const Config *cfg, Dbg *dbg) {
    set(cfg, "dbg.pos",      DBG_POS,      dbg);
    set(cfg, "dbg.pos_soft", DBG_POS_SOFT, dbg);
    set(cfg, "dbg.vel",      DBG_VEL,      dbg);
    set(cfg, "dbg.forces",   DBG_FORCES,   dbg);
    set(cfg, "dbg.colors",   DBG_COLORS,   dbg);
    set(cfg, "dbg.clist",    DBG_CLIST,    dbg);
}
