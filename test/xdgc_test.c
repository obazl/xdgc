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

int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
        case 'h':
            log_info("Help: ");
            exit(EXIT_SUCCESS);
        default:
            log_error("Usage: %s [-f] [findlibfile]", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    char *wd = getenv("BUILD_WORKING_DIRECTORY");
    if (wd) {
        /* we launched from bazel workspace, cd to launch dir */
        chdir(wd);
    }

    char *s = xdg_data_home();
    log_info("xdg data home: %s", s);
    free(s);

    s = xdg_config_home();
    log_info("xdg config home: %s", s);
    free(s);

    log_info("exiting");
}
