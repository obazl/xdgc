#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>

#if INTERFACE
#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif
#endif

#include <unistd.h>

#include "liblogc.h"
#include "utarray.h"
#include "utstring.h"
#include "utstring.h"
#include "xdgc_test.h"

#if defined(PROFILE_fastbuild)
#define TRACE_FLAG xdgc_trace
bool TRACE_FLAG;
#define DEBUG_LEVEL xdgc_debug
int  DEBUG_LEVEL;
#endif

void usage(char *arg)
{
    log_info("Usage: %s [-f] [findlibfile]", arg);
}

int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "hdtv")) != -1) {
        switch (opt) {
        case 'h':
            usage(argv[0]);
            exit(EXIT_SUCCESS);
#if defined(PROFILE_fastbuild)
        case 'd':
            xdgc_debug++;
            break;
        case 't':
            xdgc_trace = true;
            break;
#endif
        default:
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    char *wd = getenv("BUILD_WORKING_DIRECTORY");
    if (wd) {
        /* we launched from bazel workspace, cd to launch dir */
        int rc = chdir(wd);
        (void)rc;
    }

    char *s = xdg_bin_home();
    log_info("xdg bin home: %s", s);
    free(s);

    s = xdg_cache_home();
    log_info("xdg cache home: %s", s);
    free(s);

    s = xdg_config_home();
    log_info("xdg config home: %s", s);
    free(s);

    s = xdg_data_home();
    log_info("xdg data home: %s", s);
    free(s);

    s = xdg_state_home();
    log_info("xdg state home: %s", s);
    free(s);

    log_info("exiting");
}
