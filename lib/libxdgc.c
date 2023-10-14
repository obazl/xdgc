#include <stdbool.h>

#include "log.h"
#include "utstring.h"
#include "libxdgc.h"

bool verbose;

/* XDG
   https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
   Base dirs:
       XDG_DATA_HOME      $HOME/.local/share
       XDG_CONFIG_HOME    $HOME/.config
       XDG_STATE_HOME     $HOME/.local/state
       XDG_CACHE_HOME     $HOME/.cache
       XDG_BIN_HOME       $HOME/.local/bin (NB: env var not specified)
       XDG_RUNTIME_DIR (NB:not _HOME; no default location)
 */
#define XDG_DATA_HOME 0
#define XDG_DATA_HOME_SFX ".local/share"
/* UT_string *ut_xdg_data_home; */

#define XDG_CONFIG_HOME 1
#define XDG_CONFIG_HOME_SFX ".config"
/* UT_string *ut_xdg_config_home; */

/* state home for history files, current state to be reused on restart */
#define XDG_STATE_HOME 2
#define XDG_STATE_HOME_SFX ".local/state"
/* UT_string *ut_xdg_state_home; */

#define XDG_CACHE_HOME 3
#define XDG_CACHE_HOME_SFX ".cache"
/* UT_string *ut_xdg_cache_home; */

#define XDG_BIN_HOME 4
#define XDG_BIN_HOME_SFX   ".local/bin"
/* UT_string *ut_xdg_bin_home; */

/* sockets, named pipes, etc. */
/* #define XDG_RUNTIME_DIR */

/* preference-ordered base directories in addition to XDG_DATA_HOME */
#define XDG_DATA_DIRS   "/usr/local/share:/usr/share"
#define XDG_CONFIG_DIRS "/etc/xdg"

/* client is responsible for checking existence */
char *_xdg_home_dir(int which)
{
    UT_string *ut_xdg_home_dir;
    char *_xdg_home_env;
    char *sfx;
    switch(which) {
    case XDG_DATA_HOME:
        _xdg_home_env = getenv("XDG_DATA_HOME");
        sfx = XDG_DATA_HOME_SFX;
        break;
    case XDG_CONFIG_HOME:
        _xdg_home_env = getenv("XDG_CONFIG_HOME");
        sfx = XDG_CONFIG_HOME_SFX;
        break;
    case XDG_STATE_HOME:
        _xdg_home_env = getenv("XDG_STATE_HOME");
        sfx = XDG_STATE_HOME_SFX;
        break;
    case XDG_CACHE_HOME:
        _xdg_home_env = getenv("XDG_CACHE_HOME");
        sfx = XDG_CACHE_HOME_SFX;
        break;
    case XDG_BIN_HOME:
        _xdg_home_env = getenv("XDG_BIN_HOME");
        sfx = XDG_BIN_HOME_SFX;
        break;
    }

    utstring_new(ut_xdg_home_dir);

    if (_xdg_home_env == NULL) {
        _xdg_home_env = getenv("HOME");
        utstring_printf(ut_xdg_home_dir,
                        "%s/%s", _xdg_home_env, sfx);
    } else {
        utstring_printf(ut_xdg_home_dir, "%s", _xdg_home_env);
    }
    char *s = strdup(utstring_body(ut_xdg_home_dir));
    utstring_free(ut_xdg_home_dir);
    return s;
}

EXPORT char *xdg_data_home(void)
{
    return _xdg_home_dir(XDG_DATA_HOME);
}

EXPORT char *xdg_config_home(void)
{
    return _xdg_home_dir(XDG_CONFIG_HOME);
}

EXPORT char *xdg_state_home(void)
{
    return _xdg_home_dir(XDG_STATE_HOME);
}

EXPORT char *xdg_cache_home(void)
{
    return _xdg_home_dir(XDG_CACHE_HOME);
}

EXPORT char *xdg_bin_home(void)
{
    return _xdg_home_dir(XDG_BIN_HOME);
}
