/* interface.h:
 * ------------
 * 
 * Provides the routines for displaying the interface, and interacting with
 * the user via keystrokes.
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/* Local Includes */
#include "sources.h"

// window split type enumeration
typedef enum { WIN_SPLIT_FREE        = -3,   // split point not on quarter mark

               WIN_SPLIT_BOTTOM_FULL = -2,   // src window is 0%   of screen
               WIN_SPLIT_BOTTOM_BIG  = -1,   // src window is 25%  of screen
               WIN_SPLIT_EVEN        =  0,   // src window is 50%  of screen
               WIN_SPLIT_TOP_BIG     =  1,   // src window is 75%  of screen
               WIN_SPLIT_TOP_FULL    =  2    // src window is 100% of screen

             } WIN_SPLIT_TYPE;

/* --------- */
/* Functions */
/* --------- */

/* if_init: Initializes the interface.
 * --------
 *
 * Return Value: Zero on success, or...
 *               1: Initializing curses failed
 *               2: Signal handler install failed
 *               3: Terminal too small
 *               4: Can't create new GDB scroller
 *               5: Can not init the file dialog
 */
int if_init(void);

/* if_input: Handles special input keys from user.
 * ---------
 *
 *   key:  Key code that was received.
 *
 * Return Value:  0 if internal key was used, 
 *                1 if input to gdb,
 *                2 if input to tty or ...
 *                -1        : Quit cgdb
 */

/* if_resize_term: Resizes the application to the current term size.
 * --------------
 *
 * Return Value: -1 on error, 0 on success
 */
int if_resize_term(void);

int if_input(int key);

/* if_print: Prints data to the GDB input/output window.
 * ---------
 *
 *   buf:  NULL-terminated buffer to display.
 */
void if_print(const char *buf);

/* if_print_message: Prints data to the GDB input/output window.
 * -----------------
 *
 * fmt:     The message to display
 */
void if_print_message(const char *fmt, ...);

/* if_tty_print: Prints data to the tty input/output window.
 * -------------
 *
 *   buf:  NULL-terminated buffer to display.
 */
void if_tty_print(const char *buf);

/* if_show_file: Displays the requested file in the source display window.
 * -------------
 *
 *   path:  Full path to the file to display
 *   line:  Current line of the file being executed
 */
void if_show_file(char *path, int line);

/* if_get_sview: Return a pointer to the source viewer object.
 * -------------
 */
struct sviewer *if_get_sview();

/* if_display_message: Displays a message on the source window status bar.
 * -------------------
 *
 * msg:     A message to the user. This will not be truncated unless the width
 *          of the terminal is smaller than this message. 
 *          msg should never be NULL. use "" instead.
 *          
 * width:   The width of the status bar to use up before truncating. 
 *          If width is 0 then if_display_message will assume the whole width
 *          of the terminal.
 *
 * fmt:     The message to display
 */
void if_display_message(const char *msg, int width, const char *fmt, ...);


/* if_clear_filedlg: Clears all the files the file dialog has to show the user.
 * -----------------
 */
void if_clear_filedlg(void);

/* if_add_fildlg_choice: adds the file filename to the choices the user gets.
 * ---------------------
 *
 *  filename: a file the user can choose to open.
 */
void if_add_filedlg_choice(const char *filename);

/* if_filedlg_display_message: Displays a message on the filedlg window status bar.
 * ---------------------------
 *
 * message: The message to display
 */
void if_filedlg_display_message(char *message);

/* if_shutdown: Cleans up, and restores the terminal (shuts off curses).
 * ------------
 */
void if_shutdown(void);

/* enum Focus: An enumeration representing a focus state. 
 * ------------
 *  GDB: focus on the gdb i/o window
 *  TTY: focus on the debugged program i/o window
 *  CGDB: focus on source window, accepts command input.
 *  FILE_DLG: focus on file dialog window
 */
typedef enum Focus { GDB, TTY, CGDB, FILE_DLG } Focus;

/* if_set_focus: Sets the current input focus to a different window 
 * ------------
 *  f: The region to focus
 */
void if_set_focus( Focus f );

/* if_get_focus: Sets the current input focus to a different window 
 * ------------
 *  Return: The region thats focused
 */
Focus if_get_focus( void );

/* if_display_help: Displays the help on the screen.
 * ------------
 */
void if_display_help(void);

/* if_search_next: finds the next match in a given direction.
 * ------------
 */
void if_search_next( void );

/* if_tty_toggle: 
 * ------------
 */
void if_tty_toggle( void );

/* if_draw:
 * -----------
 */
 void if_draw( void );

 /* if_set_winsplit:
  * ________________
  */
void if_set_winsplit( WIN_SPLIT_TYPE newSplit );

/* if_highlight_sviewer:
 * ---------------------
 *
 *  Highlights the current node of the source viewer to be the
 *  new language type.
 *
 *  l 	The new langugage type to highlight.
 */
void if_highlight_sviewer ( enum tokenizer_language_support l );

#endif
