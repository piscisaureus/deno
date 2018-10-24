#define __FBSDID(x)
#define __BEGIN_DECLS
#define __END_DECLS

#include <stdarg.h>
#include <stdio.h>

static void
warnx(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

static const char* _getprogname(void) { return "wrk"; }