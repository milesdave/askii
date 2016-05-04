#include <stdlib.h>
#include <sys/time.h>
#include "util.h"

long get_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (long)(t.tv_sec * 1000 + t.tv_sec / 1000);
}
