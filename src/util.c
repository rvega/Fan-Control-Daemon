#include <stdarg.h>
#include <stdio.h>
#define __USE_MISC
#include <syslog.h>

#include "global.h"

void mbp_log(int level, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    if (daemonize) {
        vsyslog(level, fmt, args);
    }
    vprintf(fmt, args);
    puts("");  // trailing newline
    va_end(args);
}
