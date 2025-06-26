#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

void openlog(const char *ident, int option, int typ) {
    // STUB
}

void closelog(void) {
    // STUB
}

void
syslog(int _p, const char * str, ...) {
    va_list ap;
    va_start(ap, str);
    vsyslog(_p, str, ap);
    va_end(ap);
}

void
vsyslog(int _p, const char * str, __va_list lst) {
    vprintf(str, lst);
}