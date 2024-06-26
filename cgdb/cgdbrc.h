#ifndef __CGDBRC_H__
#define __CGDBRC_H__

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#if HAVE_STDIO_H
#include <stdio.h>
#endif /* HAVE_STDIO_H */

/* TODO: Remove this include. It is simply used to get 
 * enum tokenizer_language_support.
 */
#include "tokenizer.h"

/**
 * \file
 * cgdbrc.h
 *
 * \brief
 * An interface for dealing with config parameters. A client can determine
 * the value of a configuration option by calling cgdbrc_get. A client can
 * also ask to be notified when a particular option is changed. This gives
 * them two benefits. They can determine if the new value the user is trying
 * to set the option to is valid, and they can be kept up to date when
 * the option is changed.
 *
 * This package is currently not context driven. That is because at this
 * point there is only need for one cgdbrc package. Feel free to make
 * a 'struct cgdbrc' if it's needed in the future.
 *
 * Also, the highlight_group package is really part of the configuration too.
 * Feel free to integrate the two files somehow.
 */

/* Initialization {{{ */

/** 
 * Initialize the cgdbrc interface. 
 *
 * TODO: This interface should become instance driven instead of having
 * a global context.
 *
 * \return
 * 0 on success, otherwise error.
 */
void cgdbrc_init(void);

/* }}} */

/* Parse options {{{ */

/** 
 * Parse a string of command data and execute the commands that it represents.
 *
 * \param buffer
 * A line of command data to parse (representing a single command).
 *
 * \return
 * 0 on success, otherwise error.
 */
int command_parse_string(const char *buffer);

/**
 * Parse a configuration file, and execute the commands that it contains.
 * The commands will be executed in order.
 *
 * \param fp
 * The file to parse.
 *
 * \return
 * Currently only returns 0.
 */
int command_parse_file(const char *config_file);

/* }}} */

/* Options types {{{ */

/** 
 * The different ways to display a line in the CGDB window.
 */
enum LineDisplayStyle {
    LINE_DISPLAY_SHORT_ARROW,
    LINE_DISPLAY_LONG_ARROW,
    LINE_DISPLAY_HIGHLIGHT,
    LINE_DISPLAY_BLOCK
};

/** window split type enumeration*/
typedef enum { WIN_SPLIT_FREE = -3, /* split point not on quarter mark */

    WIN_SPLIT_GDB_FULL = -2,    /* src window is 0%   of screen */
    WIN_SPLIT_GDB_BIG = -1,     /* src window is 25%  of screen */
    WIN_SPLIT_EVEN = 0,         /* src window is 50%  of screen */
    WIN_SPLIT_SRC_BIG = 1,      /* src window is 75%  of screen */
    WIN_SPLIT_SRC_FULL = 2      /* src window is 100% of screen */
} WIN_SPLIT_TYPE;

/** window split orientation type enumeration
 *  
 *  SPLIT_VERTICAL and SPLIT_HORIZONTAL refer to the orientation
 *  of the split between the source and GDB windows.
 */
typedef enum {
    WSO_HORIZONTAL, /* source above and GDB below (default) */
    WSO_VERTICAL    /* source left and GDB right            */
} WIN_SPLIT_ORIENTATION_TYPE;

/** All of the different configuration options */
enum cgdbrc_option_kind {
    /* Arrow style is deprecated, use CGDBRC_EXECUTING_LINE_DISPLAY instead */
    CGDBRC_ARROWSTYLE,
    CGDBRC_AUTOSOURCERELOAD,
    CGDBRC_CGDB_MODE_KEY,
    CGDBRC_COLOR,
    CGDBRC_DEBUGWINCOLOR,
    CGDBRC_DISASM,
    CGDBRC_EXECUTING_LINE_DISPLAY,
    CGDBRC_HLSEARCH,
    CGDBRC_IGNORECASE,
    CGDBRC_SCROLLBACK_BUFFER_SIZE,
    CGDBRC_SELECTED_LINE_DISPLAY,
    CGDBRC_SHOWMARKS,
    CGDBRC_SYNTAX,
    CGDBRC_TABSTOP,
    CGDBRC_TIMEOUT,
    CGDBRC_TIMEOUT_LEN,
    CGDBRC_TTIMEOUT,
    CGDBRC_TTIMEOUT_LEN,
    CGDBRC_WINMINHEIGHT,
    CGDBRC_WINMINWIDTH,
    CGDBRC_WINSPLIT,
    CGDBRC_WINSPLITORIENTATION,
    CGDBRC_WRAPSCAN
};

/** This represents a single configuration option. */
struct cgdbrc_config_option {
    enum cgdbrc_option_kind option_kind;
    union {
        /* option_kind == CGDBRC_ARROWSTYLE */
        /* option_kind == CGDBRC_EXECUTING_LINE_DISPLAY */
        /* option_kind == CGDBRC_SELECTED_LINE_DISPLAY */
        enum LineDisplayStyle line_display_style;
        /* option_kind == CGDBRC_AUTOSOURCERELOAD */
        /* option_kind == CGDBRC_CGDB_MODE_KEY */
        /* option_kind == CGDBRC_COLOR */
        /* option_kind == CGDBRC_DEBUGWINCOLOR */
        /* option_kind == CGDBRC_DISASM */
        /* option_kind == CGDBRC_HLSEARCH */
        /* option_kind == CGDBRC_IGNORECASE */
        /* option_kind == CGDBRC_SCROLLBACK_BUFFER_SIZE */
        /* option_kind == CGDBRC_SHOWMARKS */
        /* option_kind == CGDBRC_TABSTOP */
        /* option_kind == CGDBRC_TIMEOUT */
        /* option_kind == CGDBRC_TIMEOUTLEN */
        /* option_kind == CGDBRC_TTIMEOUT */
        /* option_kind == CGDBRC_TTIMEOUTLEN */
        /* option_kind == CGDBRC_WINMINHEIGHT */
        /* option_kind == CGDBRC_WINMINWIDTH */
        /* option_kind == CGDBRC_WRAPSCAN */
        int int_val;
        /* option_kind == CGDBRC_SYNTAX */
        enum tokenizer_language_support language_support_val;
        /* option_kind == CGDBRC_WINSPLIT */
        WIN_SPLIT_TYPE win_split_val;
        /* option_kind == CGDBRC_WINSPLITORIENTATION */
        WIN_SPLIT_ORIENTATION_TYPE win_split_orientation_val;
    } variant;
};

/* }}} */

/* Attach/Detach options {{{ */

typedef struct cgdbrc_config_option *cgdbrc_config_option_ptr;

/**
 * If the notify function fails, this tells the configuration package
 * that the option was not acceptable. The option will not be kept.
 * This allows a mechanism for the configuration package to allow other
 * packages to validate if a particular config option value is OK. So,
 * a client might use this even if they are not interested in getting the
 * new values, but want to validate the values, in order to not tightly
 * couple the config reader with the other parts of CGDB.
 */
typedef int (*cgdbrc_notify) (cgdbrc_config_option_ptr option);

/**
 * This will attach a new callback function for a particular option.
 * The client will be notified when the value is changed.
 *
 * \param option
 * The new option to attach a callback to.
 *
 * \param notify
 * The callback function to call when the state of the data changes.
 * 
 * \return
 * 0 on success or -1 on error
 */
int cgdbrc_attach(enum cgdbrc_option_kind option, cgdbrc_notify notify);

/* }}} */

/* Get options {{{ */

/**
 * Get a configuration option.
 *
 * \param option
 * The option to get
 *
 * \return
 * This will never return NULL. It is returned as a pointer simply to not
 * pass the entire structure back. The configuration option corresponding
 * to the option asked for is returned.
 */
cgdbrc_config_option_ptr cgdbrc_get(enum cgdbrc_option_kind option);
int cgdbrc_get_int(enum cgdbrc_option_kind option);
enum LineDisplayStyle cgdbrc_get_displaystyle(enum cgdbrc_option_kind option);

/**
 * A convenience function for determining the timeout that should be used to
 * allow a key code sequence to complete. This function can not fail.
 *
 * \return
 * The number of milliseconds to delay before timing out. If 0, then do not 
 * timeout.
 */
int cgdbrc_get_key_code_timeoutlen(void);

/**
 * A convenience function for determining the timeout that should be used to
 * allow a mapped key sequence to complete. This function can not fail.
 *
 * \return
 * The number of milliseconds to delay before timing out. If 0, then do not 
 * timeout.
 */
int cgdbrc_get_mapped_key_timeoutlen(void);

/* }}} */

#endif /* __CGDBRC_H__ */
