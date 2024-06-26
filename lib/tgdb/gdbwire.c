/**
 * Copyright (C) 2013 Robert Rossi <bob@brasko.net>
 *
 * This file is an amalgamation of the source files from GDBWIRE.
 *
 * It was created using gdbwire 1.0 and git revision b'6faba36'.
 *
 * GDBWIRE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GDBWIRE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GDBWIRE.  If not, see <http://www.gnu.org/licenses/>.
 */

/***** Begin file gdbwire_sys.c **********************************************/
#include <stdlib.h>
#include <string.h>

/***** Include gdbwire_sys.h in the middle of gdbwire_sys.c ******************/
/***** Begin file gdbwire_sys.h **********************************************/
#ifndef __GDBWIRE_SYS_H__
#define __GDBWIRE_SYS_H__

/**
 * Supporting system functions.
 */

#ifdef __cplusplus 
extern "C" { 
#endif 

/**
 * Duplicate a string.
 *
 * @param str
 * The string to duplicate
 *
 * @return
 * An allocated string that must be freed.
 * Null if out of memory or str is NULL.
 */
char *gdbwire_strdup(const char *str);

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire_sys.h **************************************************/
/***** Continuing where we left off in gdbwire_sys.c *************************/

char *gdbwire_strdup(const char *str)
{
    char *result = NULL;

    if (str) {
        size_t length_to_allocate = strlen(str) + 1;
        result = malloc(length_to_allocate * sizeof(char));
        if (result) {
            strcpy(result, str);
        }
    }

    return result;
}
/***** End of gdbwire_sys.c **************************************************/
/***** Begin file gdbwire_string.c *******************************************/
#include <string.h>
#include <stdlib.h>
/***** Include gdbwire_string.h in the middle of gdbwire_string.c ************/
/***** Begin file gdbwire_string.h *******************************************/
#ifndef __GDBWIRE_STRING_H__
#define __GDBWIRE_STRING_H__

#ifdef __cplusplus 
extern "C" { 
#endif 

#include <stdlib.h>

/**
 * A dynamic string representation.
 *
 * To create and destroy a string use gdbwire_string_create() and
 * gdbwire_string_destroy() respectively.
 *
 * This string is an abstraction of a low level C string. It supports being
 * used as a NULL terminated c string and also as an arbitrary array of
 * bytes. You can append to this string in either of these modes using
 * gdbwire_string_append_cstr() or gdbwire_string_append_data(). This string
 * automatically grows as you append data to it. Please note, the size of
 * the string will not include the NULL terminated character when using
 * the gdbwire_string_append_cstr() function to append data.
 *
 * To get access to the underlying bytes associated with this string
 * call gdbwire_string_data(). It is OK to modify the result as long as
 * you are careful to stay in it's valid bounds.
 *
 * The size (or length) of the string can be accessed through the
 * gdbwire_string_size() function. The character pointer returned from
 * gdbwire_string_data() is valid from the index range of 0 to
 * gdbwire_string_size() - 1.
 */
struct gdbwire_string;

/**
 * Create a string instance.
 *
 * @return
 * A valid string instance or NULL on error.
 */
struct gdbwire_string *gdbwire_string_create(void);

/**
 * Destroy the string instance and it's resources.
 *
 * @param string
 * The string to destroy.
 */
void gdbwire_string_destroy(struct gdbwire_string *string);

/**
 * Clear the contents of a string.
 *
 * Sets the string back to an empty string which also changes it's
 * size back to zero.
 *
 * The capacity remains unchanged.
 *
 * @param string
 * The string to clear
 */
void gdbwire_string_clear(struct gdbwire_string *string);

/**
 * Append a character to the string instance.
 *
 * @param string
 * The string instance to append the character to.
 *
 * @param c
 * The character to append to the string instance.
 *
 * @return
 * 0 on success or -1 on failure.
 */
int gdbwire_string_append_char(struct gdbwire_string *string, char c);

/**
 * Append a c string to the string instance.
 *
 * @param string
 * The string instance to append the c string to.
 *
 * @param cstr
 * The c string to append to the string instance.
 *
 * @return
 * 0 on success or -1 on failure.
 */
int gdbwire_string_append_cstr(struct gdbwire_string *string, const char *cstr);

/**
 * Append a sequence of bytes to the string instance.
 *
 * @param string
 * The string instance to append the sequence of bytes to.
 *
 * @param data
 * The sequence of bytes to append to the string instance. This may
 * contain NUL characters.
 *
 * @param size
 * The number of bytes in data to append to the string instance.
 *
 * @return
 * 0 on success or -1 on failure.
 */
int gdbwire_string_append_data(struct gdbwire_string *string,
        const char *data, size_t size);

/**
 * Get the data associated with this string.
 *
 * The data could be formatted as a NULL terminated C string or
 * as an arbitrary array of bytes. Use gdbwire_string_size() to
 * determine the size (or length) of the result of this function.
 * 
 * Modifying the return value of this function is acceptable as long as you
 * stay in the string's valid bounds.
 *
 * @param string
 * The string index to get the pointer data from.
 *
 * @return
 * The data that has been added to this string instance or "" after
 * creation or clear. The result is gdbwire_string_size() bytes long.
 */
char *gdbwire_string_data(struct gdbwire_string *string);

/**
 * Determine the size (the number of bytes) this string instance represents.
 *
 * Please note, the result of this function will not include the NULL
 * terminated character when using the gdbwire_string_append_cstr() function
 * to append data.
 *
 * @param string
 * The string instance to get the size for.
 *
 * @return
 * The number of bytes contained in this string instance. To access these
 * bytes see gdbwire_string_data(). Will be 0 after creation or clear.
 */
size_t gdbwire_string_size(struct gdbwire_string *string);

/**
 * Determine the maximum capacity (number of bytes) this string may hold.
 *
 * The max capacity of the string is automatically increased when data
 * is appended to this string through the gdbwire_string_append_*()
 * family of functions.
 *
 * @param string
 * The string to determine the capacity of.
 *
 * @return
 * The max number of bytes this string may hold.
 */
size_t gdbwire_string_capacity(struct gdbwire_string *string);

/**
 * Search for the first character in chars occuring in this string.
 *
 * @param string
 * The string to search for the characters in chars in.
 *
 * @param chars
 * A null terminated string of characters. This string is not searched
 * for directly but instead each individually character in the string
 * is searched for.
 *
 * @return
 * The index position of the first matched character in chars.
 * Will return gdbwire_string_size() if not found.
 */
size_t gdbwire_string_find_first_of(struct gdbwire_string *string,
        const char *chars);

/**
 * Erase characters from this string, reducing it's size.
 *
 * @param string
 * The string to erase characters from.
 *
 * @param pos
 * The index position of the first character to be erased.
 *
 * @param count
 * The number of characters to erase starting at position pos.
 * If count goes past the end of the string it is adjusted to erase
 * until the end of the string. This allows the caller to pass in
 * gdbwire_string_size() to erase the end of the string with out
 * doing index arithmetic.
 * 
 * @return
 * On success 0 will be returned otherwise -1. The string will remain
 * unmodified when an error occurs. Success can only occur if the entire
 * requested range can be erased.
 */
int gdbwire_string_erase(struct gdbwire_string *string, size_t pos,
        size_t count);

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire_string.h ***********************************************/
/***** Continuing where we left off in gdbwire_string.c **********************/

struct gdbwire_string {
    /* The bytes that make up the string. May contain NUL characters. */
    char *data;
    /* The number of bytes occuring in data at the moment. */
    size_t size;
    /* The max capacity of the string */
    size_t capacity;
};

struct gdbwire_string *
gdbwire_string_create(void)
{
    struct gdbwire_string *string;

    string = calloc(1, sizeof (struct gdbwire_string));
    if (string) {
        if (gdbwire_string_append_cstr(string, "") == -1) {
            gdbwire_string_destroy(string);
            string = NULL;
        }
    }

    return string;
}

void
gdbwire_string_destroy(struct gdbwire_string *string)
{
    if (string) {
        if (string->data) {
            free(string->data);
            string->data = NULL;
        }
        string->size = 0;
        string->capacity = 0;
        free(string);
    }
}

void
gdbwire_string_clear(struct gdbwire_string *string)
{
    if (string) {
        string->size = 0;
        string->data[0] = '\0';
    }
}

/**
 * Increase the size of the string capacity.
 *
 * @param string
 * The string to increase the capacity.
 *
 * @return
 * 0 on success or -1 on error.
 */
static int
gdbwire_string_increase_capacity(struct gdbwire_string *string)
{
    /**
     * The algorithm chosen to increase the capacity is arbitrary.
     * It starts at 128 bytes. It then doubles it's size in bytes like this,
     *   128, 256, 512, 1024, 2048, 4096
     * After it reaches 4096 it then grows by 4096 bytes at a time.
     */
    if (string->capacity == 0) {
        string->capacity = 128;
    } else if (string->capacity < 4096) {
        string->capacity *= 2;
    } else {
        string->capacity += 4096;
    }

    /* At this point string->capacity is set to the new size, so realloc */
    string->data = (char*)realloc(string->data, string->capacity);

    return (string->data) ? 0 : -1;
}

int
gdbwire_string_append_char(struct gdbwire_string *string, char c)
{
    return gdbwire_string_append_data(string, &c, 1);
}

int
gdbwire_string_append_cstr(struct gdbwire_string *string, const char *cstr)
{
    int result;

    if (string && cstr) {
        size_t length = strlen(cstr) + 1;
        result = gdbwire_string_append_data(string, cstr, length);
        /* Do not include the NUL character in the size for NULL terminated
         * strings. This is documented in the interface. */
        if (result == 0) {
            string->size--;
        }
    } else {
        result = -1;
    }

    return result;
}

int
gdbwire_string_append_data(struct gdbwire_string *string, const char *data,
        size_t size)
{
    int result = (string && data) ? 0 : -1;
    size_t data_index = 0;

    for (; string && data && data_index < size; ++data_index, ++string->size) {
        if (string->size >= string->capacity) {
            result = gdbwire_string_increase_capacity(string);
            if (result == -1) {
                break;
            }
        }

        string->data[string->size] = data[data_index];
    }

    return result;
}

char *
gdbwire_string_data(struct gdbwire_string *string)
{
    char *result = NULL;

    if (string) {
        result = string->data;
    }

    return result;
}

size_t
gdbwire_string_size(struct gdbwire_string *string)
{
    return string->size;
}

size_t
gdbwire_string_capacity(struct gdbwire_string *string)
{
    return string->capacity;
}

size_t
gdbwire_string_find_first_of(struct gdbwire_string *string, const char *chars)
{
    size_t data_pos, data_size = 0;
    char *data_cur;
    const char *chars_cur;

    if (string && chars) {
        data_size = gdbwire_string_size(string);
        data_cur = gdbwire_string_data(string);

        for (data_pos = 0; data_pos < data_size; ++data_pos) {
            char data_c = data_cur[data_pos];
            for (chars_cur = chars; *chars_cur; ++chars_cur) {
                if (data_c == *chars_cur) {
                    return data_pos;
                }
            }
        }
    }

    return data_size;
}

int
gdbwire_string_erase(struct gdbwire_string *string, size_t pos, size_t count)
{
    int result = -1;

    if (string) {
        size_t count_erased = count;
        size_t data_size = gdbwire_string_size(string);
        char *data = gdbwire_string_data(string);

        /* The position index must be smaller than the data size to be valid */
        if (pos < data_size) {
            size_t from_pos = pos + count;

            /**
             * Check to see if anything needs to be copied.
             * If not, just null terminate the position to be erased
             * Null terminating the string ensures the c string and the data
             * string approach are both safe. In the data mode, the nul
             * character is unneeded.
             */
            if (from_pos >= data_size) {
                data[pos] = 0;
                count_erased = data_size - pos;
            /* If so, move characters from the from position
               to the to position */
            } else {
                char *to_cur = &data[pos], *from_cur = &data[from_pos];

                /* shift everything after the erase request to the left */
                for (; from_pos < data_size; ++from_pos, ++to_cur, ++from_cur) {
                    *to_cur = *from_cur;
                }
            }
            string->size -= count_erased;
            result = 0;
        }
    }

    return result;
}
/***** End of gdbwire_string.c ***********************************************/
/***** Begin file gdbwire_logger.c *******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/***** Include gdbwire_logger.h in the middle of gdbwire_logger.c ************/
/***** Begin file gdbwire_logger.h *******************************************/
#ifndef __GDBWIRE_LOGGER_H__
#define __GDBWIRE_LOGGER_H__

/***** Include gdbwire_result.h in the middle of gdbwire_logger.h ************/
/***** Begin file gdbwire_result.h *******************************************/
#ifndef GDBWIRE_RESULT_H
#define GDBWIRE_RESULT_H

enum gdbwire_result {
    /* The result of the operation was successful */
    GDBWIRE_OK,

    /**
     * An assertion failed in the calling code.
     *
     * Functions are encouraged to assert expressions they expect
     * to be true. The macro GDBWIRE_ASSERT and GDBWIRE_ASSERT_ERRNO
     * are useful for asserting expressions, and upon failure, to
     * automatically log the assertion expression and return
     * this result status.
     */
    GDBWIRE_ASSERT,

    /**
     * An internal logic error has occurred.
     *
     * In general, this should be used when a function can no
     * longer carry out it's contract and must abort.
     *
     * This happens, for instance, when a called function returns
     * an error status, or when invalid input was provided, etc.
     */
    GDBWIRE_LOGIC,

    /**
     * The system is out of memory.
     *
     * Will occur when malloc, strdup, calloc, etc fail to allocate memory.
     */
    GDBWIRE_NOMEM
};

#endif /* GDBWIRE_RESULT_H */
/***** End of gdbwire_result.h ***********************************************/
/***** Continuing where we left off in gdbwire_logger.h **********************/

#ifdef __cplusplus 
extern "C" { 
#endif 

enum gdbwire_logger_level {
    GDBWIRE_LOGGER_DEBUG,
    GDBWIRE_LOGGER_INFO,
    GDBWIRE_LOGGER_WARN,
    GDBWIRE_LOGGER_ERROR
};

/**
 * Log a statement to the logger.
 *
 * This is typically not called directly. Use the below macros instead.
 * The macros automatically supply the file, line and level arguments.
 *
 * @param file
 * The filename the logger was invoked from.
 *
 * @param line
 * The line number the logger was invoked from.
 *
 * @param level
 * The level associated with the log message.
 *
 * @param fmt
 * The format string for the message (printf formatting).
 *
 * @param ...
 * Any additional format arguments.
 */
void gdbwire_logger_log(const char *file, int line,
        enum gdbwire_logger_level level, const char *fmt, ...)
#ifdef __GNUC__
        __attribute__((__format__(__printf__, 4, 5)))
#endif
        ;

/* The macros intended to be used for logging */
#define gdbwire_debug(fmt, ...)(gdbwire_logger_log(__FILE__, __LINE__, \
        GDBWIRE_LOGGER_DEBUG, fmt, ##__VA_ARGS__))
#define gdbwire_info(fmt, ...)(gdbwire_logger_log(__FILE__, __LINE__, \
        GDBWIRE_LOGGER_INFO, fmt, ##__VA_ARGS__))
#define gdbwire_warn(fmt, ...)(gdbwire_logger_log(__FILE__, __LINE__, \
        GDBWIRE_LOGGER_WARN, fmt, ##__VA_ARGS__))
#define gdbwire_error(fmt, ...)(gdbwire_logger_log(__FILE__, __LINE__, \
        GDBWIRE_LOGGER_ERROR, fmt, ##__VA_ARGS__))

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire_logger.h ***********************************************/
/***** Continuing where we left off in gdbwire_logger.c **********************/

static const char *gdbwire_logger_level_str[GDBWIRE_LOGGER_ERROR+1] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR"
};

void
gdbwire_logger_log(const char *file, int line, enum gdbwire_logger_level level,
        const char *fmt, ...)
{
    static int checked_env = 0;
    static int gdbwire_debug_to_stderr;
    char *buf;
    int size;

    va_list ap;
    va_start(ap, fmt);

    size = vsnprintf(0, 0, fmt, ap);
    buf = malloc(sizeof(char)*size + 1);

    va_start(ap, fmt);
    size = vsnprintf(buf, size + 1, fmt, ap);
    va_end(ap);

    if (checked_env == 0) {
        checked_env = 1;
        gdbwire_debug_to_stderr = getenv("GDBWIRE_DEBUG_TO_STDERR") != NULL;
    }

    if (gdbwire_debug_to_stderr) {
        fprintf(stderr, "gdbwire_logger_log: [%s] %s:%d %s\n",
            gdbwire_logger_level_str[level], file, line, buf);
    }

    free(buf);
}
/***** End of gdbwire_logger.c ***********************************************/
/***** Begin file gdbwire_mi_parser.c ****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* #include "gdbwire_sys.h" */
/***** Include gdbwire_assert.h in the middle of gdbwire_mi_parser.c *********/
/***** Begin file gdbwire_assert.h *******************************************/
#ifndef GDBWIRE_ERROR_H
#define GDBWIRE_ERROR_H

/* #include "gdbwire_result.h" */
/* #include "gdbwire_logger.h" */

/**
 * Validate that the expression evaluates to true.
 *
 * If the expression does not evaluate to true, log the error and
 * return a GDBWIRE_ASSERT status code.
 *
 * Otherwise, if the expression does evaluate to true, do nothing.
 *
 * @param expr
 * The expression to evaluate.
 */
#define GDBWIRE_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            gdbwire_error("Assertion failure, expr[%s]", #expr); \
            return GDBWIRE_ASSERT; \
        } \
    } while (0)

/**
 * Validate that the expression evaluates to true.
 *
 * If the expression does not evaluate to true, log the error,
 * set the variable provided to GDBWIRE_ASSERT and goto the label
 * provided.
 *
 * Otherwise, if the expression does evaluate to true, do nothing.
 *
 * @param expr
 * The expression to evaluate.
 *
 * @param variable
 * The result variable to assign the value GDBWIRE_ASSERT to.
 *
 * @param label
 * The label to jump to if the expression evaluates to False.
 */
#define GDBWIRE_ASSERT_GOTO(expr, variable, label) \
    do { \
        if (!(expr)) { \
            gdbwire_error("Assertion failure, expr[%s], " \
                "label[%s]", #expr, #label); \
            variable = GDBWIRE_ASSERT; \
            goto label; \
        } \
    } while (0)

/**
 * Validate that the expression evaluates to true.
 *
 * This particular assertion macro is used when a system library
 * call fails and that library call has an associated errno status
 * to describe the failure reason.
 *
 * If the expression does not evaluate to true, log the error,
 * along with the errno value and message and return a GDBWIRE_ASSERT
 * status code.
 *
 * Otherwise, if the expression does evaluate to true, do nothing.
 *
 * @param expr
 * The expression to evaluate.
 */
#define GDBWIRE_ASSERT_ERRNO(expr) \
    do { \
        if (!(expr)) { \
            gdbwire_error("Assertion failure, expr[%s]," \
                "errno[%d], strerror[%s]", \
                #expr, errno, strerror(errno)); \
            return GDBWIRE_ASSERT; \
        } \
    } while (0)

#endif /* GDBWIRE_ERROR_H */
/***** End of gdbwire_assert.h ***********************************************/
/***** Continuing where we left off in gdbwire_mi_parser.c *******************/
/***** Include gdbwire_mi_grammar.h in the middle of gdbwire_mi_parser.c *****/
/***** Begin file gdbwire_mi_grammar.h ***************************************/
/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_GDBWIRE_MI_SRC_GDBWIRE_MI_GRAMMAR_H_INCLUDED
# define YY_GDBWIRE_MI_SRC_GDBWIRE_MI_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int gdbwire_mi_debug;
#endif
/* "%code requires" blocks.  */


/* An opaque pointer. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

    struct gdbwire_mi_output;


/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    OPEN_BRACE = 258,              /* OPEN_BRACE  */
    CLOSED_BRACE = 259,            /* CLOSED_BRACE  */
    OPEN_PAREN = 260,              /* OPEN_PAREN  */
    CLOSED_PAREN = 261,            /* CLOSED_PAREN  */
    ADD_OP = 262,                  /* ADD_OP  */
    MULT_OP = 263,                 /* MULT_OP  */
    EQUAL_SIGN = 264,              /* EQUAL_SIGN  */
    TILDA = 265,                   /* TILDA  */
    AT_SYMBOL = 266,               /* AT_SYMBOL  */
    AMPERSAND = 267,               /* AMPERSAND  */
    OPEN_BRACKET = 268,            /* OPEN_BRACKET  */
    CLOSED_BRACKET = 269,          /* CLOSED_BRACKET  */
    NEWLINE = 270,                 /* NEWLINE  */
    INTEGER_LITERAL = 271,         /* INTEGER_LITERAL  */
    STRING_LITERAL = 272,          /* STRING_LITERAL  */
    CSTRING = 273,                 /* CSTRING  */
    COMMA = 274,                   /* COMMA  */
    CARROT = 275                   /* CARROT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define OPEN_BRACE 258
#define CLOSED_BRACE 259
#define OPEN_PAREN 260
#define CLOSED_PAREN 261
#define ADD_OP 262
#define MULT_OP 263
#define EQUAL_SIGN 264
#define TILDA 265
#define AT_SYMBOL 266
#define AMPERSAND 267
#define OPEN_BRACKET 268
#define CLOSED_BRACKET 269
#define NEWLINE 270
#define INTEGER_LITERAL 271
#define STRING_LITERAL 272
#define CSTRING 273
#define COMMA 274
#define CARROT 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{

  struct gdbwire_mi_output *u_output;
  struct gdbwire_mi_oob_record *u_oob_record;
  struct gdbwire_mi_result_record *u_result_record;
  int u_result_class;
  int u_async_record_kind;
  struct gdbwire_mi_result_list *u_result_list;
  struct gdbwire_mi_result *u_result;
  char *u_token;
  struct gdbwire_mi_async_record *u_async_record;
  struct gdbwire_mi_stream_record *u_stream_record;
  int u_async_class;
  char *u_variable;
  char *u_cstring;
  struct gdbwire_mi_result *u_tuple;
  struct gdbwire_mi_result *u_list;
  int u_stream_record_kind;


};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct gdbwire_mi_pstate gdbwire_mi_pstate;


int gdbwire_mi_push_parse (gdbwire_mi_pstate *ps,
                  int pushed_char, YYSTYPE const *pushed_val, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output);

gdbwire_mi_pstate *gdbwire_mi_pstate_new (void);
void gdbwire_mi_pstate_delete (gdbwire_mi_pstate *ps);


#endif /* !YY_GDBWIRE_MI_SRC_GDBWIRE_MI_GRAMMAR_H_INCLUDED  */
/***** End of gdbwire_mi_grammar.h *******************************************/
/***** Continuing where we left off in gdbwire_mi_parser.c *******************/
/***** Include gdbwire_mi_parser.h in the middle of gdbwire_mi_parser.c ******/
/***** Begin file gdbwire_mi_parser.h ****************************************/
#ifndef GDBWIRE_MI_PARSER_H
#define GDBWIRE_MI_PARSER_H

#ifdef __cplusplus 
extern "C" { 
#endif 

/* #include "gdbwire_result.h" */
/***** Include gdbwire_mi_pt.h in the middle of gdbwire_mi_parser.h **********/
/***** Begin file gdbwire_mi_pt.h ********************************************/
#ifndef GDBWIRE_MI_PT_H
#define GDBWIRE_MI_PT_H

#ifdef __cplusplus 
extern "C" { 
#endif 

/**
 * The position of a token in a GDB/MI line.
 *
 * Note that a string in C is zero based and the token column
 * position is 1 based. For example,
 *   char *str = "hello world";
 * The "hello" token would have a start_column as 1 and an end
 * column as 5.
 *
 * The start_column and end_column will be the same column number for
 * a token of size 1.
 */
struct gdbwire_mi_position {
    /* The starting column position of the token */
    int start_column;
    /* The ending column position of the token */
    int end_column;
};

/** The gdbwire_mi output kinds. */
enum gdbwire_mi_output_kind {
    /**
     * The GDB/MI output contains an out of band record.
     *
     * The out of band record is not necessarily associated with any
     * particular GDB/MI input command.
     */
    GDBWIRE_MI_OUTPUT_OOB,

    /**
     * The GDB/MI output contains a gdbwire_mi result record.
     *
     * This record typically contains the result data from a request
     * made by the client in a previous GDB/MI input command.
     */
    GDBWIRE_MI_OUTPUT_RESULT,

    /**
     * The GDB/MI output represents a prompt. (ie. (gdb) )
     * 
     * TODO: Document when GDB is ready to receive a command. Only if
     * the prompt is received and at *stopped?
     */
    GDBWIRE_MI_OUTPUT_PROMPT,

    /**
     * A parse error occurred.
     */
    GDBWIRE_MI_OUTPUT_PARSE_ERROR
};

/**
 * The GDB/MI output command.
 *
 * A GDB/MI output command is the main mechanism in which GDB
 * corresponds with a front end.
 */
struct gdbwire_mi_output {
    enum gdbwire_mi_output_kind kind;

    union {
        /** When kind == GDBWIRE_MI_OUTPUT_OOB, never NULL. */
        struct gdbwire_mi_oob_record *oob_record;
        /** When kind == GDBWIRE_MI_OUTPUT_RESULT, never NULL. */
        struct gdbwire_mi_result_record *result_record;
        /** When kind == GDBWIRE_MI_OUTPUT_PARSE_ERROR, never NULL. */
        struct {
            /** The token the error occurred on */
            char *token;
            /** The position of the token where the error occurred. */
            struct gdbwire_mi_position pos;
        } error;
    } variant;

    /**
     * The GDB/MI output line that was used to create this output instance.
     *
     * Each gdbwire_mi output structure is created from exactly one line of
     * MI output from GDB. This field represents the line that created 
     * this particular output structure.
     *
     * This field is always available and never NULL, even for a parse error.
     */
    char *line;

    /** The next GDB/MI output command or NULL if none */
    struct gdbwire_mi_output *next;
};

/**
 * A GDB/MI token.
 *
 * A string made up of one or more digits.
 * The regular expression [0-9]+ will match this types contents.
 */
typedef char *gdbwire_mi_token_t;

/**
 * A GDB/MI output command may contain one of the following result indications.
 */
enum gdbwire_mi_result_class {
    /**
     * The synchronous operation was successful (^done).
     */
    GDBWIRE_MI_DONE,

    /**
     * Equivalent to GDBWIRE_MI_DONE (^running).
     *
     * Historically, was output by GDB instead of ^done if the command
     * resumed the target.
     *
     * Do not rely on or use this result class in the front end to determine
     * the state of the target. Use the async *running output record to
     * determine which threads have resumed running.
     *
     * TODO: Ensure that early versions of GDB can depend on the async
     * *running or if front ends DO have to rely on ^running.
     */
    GDBWIRE_MI_RUNNING,

    /**
     * GDB has connected to a remote target (^connected).
     *
     * This is in response to the -target-select command.
     *
     * A comment in the GDB source code says,
     *   There's no particularly good reason why target-connect results
     *   in not ^done.  Should kill ^connected for MI3.
     *
     * With this in mind, it makes sense to assume that GDBWIRE_MI_CONNECTED
     * and GDBWIRE_MI_DONE are equivalent.
     */
    GDBWIRE_MI_CONNECTED,

    /**
     * An error has occurred (^error).
     *
     * This can occur if the user provides an improper command to GDB.
     * In this case, the user will be provided the standard error output but
     * the front end will also be provided this information independently.
     */
    GDBWIRE_MI_ERROR,

    /**
     * GDB has terminated (^exit).
     *
     * When GDB knows it is about to exit, it provides this notification
     * in the GDB/MI output command. However, on all other circumstances,
     * the front end should be prepared to have GDB exit and not provide
     * this information.
     */
    GDBWIRE_MI_EXIT,

    /* An unsupported result class */
    GDBWIRE_MI_UNSUPPORTED
};

/**
 * The GDB/MI result record in an output command.
 *
 * The result record represents the result data in the GDB/MI output
 * command sent by GDB. This typically contains the content the client
 * was requesting when it sent a GDB/MI input command to GDB.
 */
struct gdbwire_mi_result_record {
    /**
     * The token associated with the corresponding GDB/MI input command.
     *
     * The client may provide a unique string of digits at the beginning of a
     * GDB/MI input command. For example,
     *   0000-foo
     * When GDB finally gets around to responding to the GDB/MI input command,
     * it takes the token provided in the input command and puts it into the
     * result record of the corresponding GDB/MI output command. For
     * example, the output commmand associated with the above input command is,
     *   0000^error,msg="Undefined MI command: foo",code="undefined-command"
     * and the result record would have the below token field set to "0000".
     *
     * This is intended to allow the front end to correlate the GDB/MI input
     * command it sent with the GDB/MI output command GDB responded with.
     *
     * This represents the token value the front end provided to the
     * corresponding GDB/MI input command or NULL if no token was provided.
     */
    gdbwire_mi_token_t token;

    /** The result records result class. */
    enum gdbwire_mi_result_class result_class;

    /**
     * An optional list of results for this result record.
     *
     * Will be NULL if there is no results for this result record.
     *
     * This is typically where the result data is that the client
     * is looking for.
     */
    struct gdbwire_mi_result *result;
};

/** The out of band record kinds. */
enum gdbwire_mi_oob_record_kind {
    /**
     * An asyncronous out of band record.
     *
     * An asyncronous record occurs when GDB would like to update the
     * client with information that it has not asked for.
     *
     * For instance, if the inferior has stopped, or a new thread has
     * started.
     */
    GDBWIRE_MI_ASYNC,

    /**
     * A stream out of band record.
     *
     * This is the result of normal output from the console, target or GDB.
     */
    GDBWIRE_MI_STREAM
};

/* This is an out of band record.  */
struct gdbwire_mi_oob_record {
    /** The kind of out of band record. */
    enum gdbwire_mi_oob_record_kind kind;

    union {
        /** When kind == GDBWIRE_MI_ASYNC. */
        struct gdbwire_mi_async_record *async_record;
        /** When kind == GDBWIRE_MI_STREAM. */
        struct gdbwire_mi_stream_record *stream_record;
    } variant;
};

/** The asynchronous out of band record kinds */
enum gdbwire_mi_async_record_kind {
    /**
     * The asynchronous status record kind.
     *
     * Contains on-going status information about the progress of a slow
     * operation. It can be discarded.
     *
     * This output is prepended by the + character.
     */
    GDBWIRE_MI_STATUS,

    /**
     * The asynchronous exec record kind.
     *
     * Contains asynchronous state change regarding the target:
     *  (stopped, started, disappeared).
     *
     * This output is prepended by the * character.
     */
    GDBWIRE_MI_EXEC,

    /**
     * The asyncronous notify record kind.
     *
     * Contains supplementary information that the client should handle 
     * (e.g., a new breakpoint information).
     *
     * This output is prepended by the = character.
     */
    GDBWIRE_MI_NOTIFY
};

/** The stream out of band record kinds */
enum gdbwire_mi_stream_record_kind {
    /**
     * The console output.
     *
     * Output that should be displayed as is in the console.
     * It is the textual response to a CLI command.
     *
     * This output is prepended by the ~ character.
     */
    GDBWIRE_MI_CONSOLE,

    /**
     * The target output.
     *
     * Output produced by the target program.
     *
     * This output is prepended by the @ character.
     */
    GDBWIRE_MI_TARGET,

    /**
     * The GDB log output.
     *
     * Output text coming from GDB's internals. For instance messages 
     * that should be displayed as part of an error log.
     *
     * This output is prepended by the & character.
     */
    GDBWIRE_MI_LOG
};

/**
 * The GDB/MI asyncronous class.
 *
 * 
 */
enum gdbwire_mi_async_class {
    /**
     * Loading the executable onto the remote target.
     *
     * This was undocumented in the GDB manual as far as GDB 7.7.
     *
     * This occurs if the async record is GDBWIRE_MI_STATUS as +download.
     */
    GDBWIRE_MI_ASYNC_DOWNLOAD,

    /**
     * The target has stopped.
     *
     * This occurs if the async record is GDBWIRE_MI_EXEC as *stopped.
     */
    GDBWIRE_MI_ASYNC_STOPPED,

    /**
     * The target is now running.
     *
     * This occurs if the async record is GDBWIRE_MI_EXEC as *running.
     */
    GDBWIRE_MI_ASYNC_RUNNING,

    /**
     * Reports that a thread group was added.
     *
     * When a thread group is added, it generally might not be associated
     * with a running process.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =thread-group-added.
     */
    GDBWIRE_MI_ASYNC_THREAD_GROUP_ADDED,

    /**
     * Reports that a thread group was removed.
     *
     * When a thread group is removed, its id becomes invalid and cannot be
     * used in any way. 
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =thread-group-removed.
     */
    GDBWIRE_MI_ASYNC_THREAD_GROUP_REMOVED,

    /**
     * Reports that a thread group was started.
     *
     * A thread group became associated with a running program.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =thread-group-started.
     */
    GDBWIRE_MI_ASYNC_THREAD_GROUP_STARTED,

    /**
     * Reports that a thread group was exited.
     *
     * A thread group is no longer associated with a running program.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =thread-group-exited.
     */
    GDBWIRE_MI_ASYNC_THREAD_GROUP_EXITED,

    /**
     * Reports that a thread was created.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =thread-created.
     */
    GDBWIRE_MI_ASYNC_THREAD_CREATED,

    /**
     * Reports that a thread was exited.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY as =thread-exited.
     */
    GDBWIRE_MI_ASYNC_THREAD_EXITED,

    /**
     * Reports that a thread was selected.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY as =thread-selected.
     */
    GDBWIRE_MI_ASYNC_THREAD_SELECTED,

    /**
     * Reports that a new library was loaded.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY as =library-loaded.
     */
    GDBWIRE_MI_ASYNC_LIBRARY_LOADED,

    /**
     * Reports that a new library was unloaded.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =library-unloaded.
     */
    GDBWIRE_MI_ASYNC_LIBRARY_UNLOADED,

    /**
     * Reports that a trace frame was changed.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =traceframe-changed.
     */
    GDBWIRE_MI_ASYNC_TRACEFRAME_CHANGED,

    /**
     * Reports that a trace state variable was created.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY as =tsv-created.
     */
    GDBWIRE_MI_ASYNC_TSV_CREATED,

    /**
     * Reports that a trace state variable was modified.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY as =tsv-modified.
     */
    GDBWIRE_MI_ASYNC_TSV_MODIFIED,

    /**
     * Reports that a trace state variable was deleted.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY as =tsv-deleted.
     */
    GDBWIRE_MI_ASYNC_TSV_DELETED,

    /**
     * Reports that a breakpoint was created.
     *
     * Only user-visible breakpoints are reported to the MI user. 
     *
     * If a breakpoint is emitted in the result record of a
     * command, then it will not also be emitted in an async record. 
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =breakpoint-created.
     */
    GDBWIRE_MI_ASYNC_BREAKPOINT_CREATED,

    /**
     * Reports that a breakpoint was modified.
     *
     * Only user-visible breakpoints are reported to the MI user. 
     *
     * If a breakpoint is emitted in the result record of a
     * command, then it will not also be emitted in an async record. 
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =breakpoint-modified.
     */
    GDBWIRE_MI_ASYNC_BREAKPOINT_MODIFIED,

    /**
     * Reports that a breakpoint was deleted.
     *
     * Only user-visible breakpoints are reported to the MI user. 
     *
     * If a breakpoint is emitted in the result record of a
     * command, then it will not also be emitted in an async record. 
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =breakpoint-deleted.
     */
    GDBWIRE_MI_ASYNC_BREAKPOINT_DELETED,

    /**
     * Reports that execution log recording was started on an inferior.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIF
     *  as =record-started.
     */
    GDBWIRE_MI_ASYNC_RECORD_STARTED,

    /**
     * Reports that execution log recording was stopped on an inferior.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =record-stopped.
     */
    GDBWIRE_MI_ASYNC_RECORD_STOPPED,

    /**
     * Reports that a parameter of the command set param is changed to value.
     *
     * For example, when the user runs a command like 'set print pretty on',
     * this async command will be invoked with the parameter reported as
     * 'print pretty' and the value as 'on'.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =cmd-param-changed.
     */
    GDBWIRE_MI_ASYNC_CMD_PARAM_CHANGED,

    /**
     * Reports that bytes from addr to data + len were written in an inferior.
     *
     * This occurs if the async record is GDBWIRE_MI_NOTIFY
     * as =memory-changed.
     */
    GDBWIRE_MI_ASYNC_MEMORY_CHANGED,

    /* An unsupported async class */
    GDBWIRE_MI_ASYNC_UNSUPPORTED
};

/**
 * The GDB/MI asyncronous record in an output command.
 *
 * An asyncronous record occurs when GDB would like to update the
 * client with information that it has not asked for.
 */
struct gdbwire_mi_async_record {
    /**
     * The result record token.
     *
     * Please note that the GDB/MI manual says that asyncronous records
     * do not currently populate this token on output but reserve the right
     * to do so. For that reason, token here should always be NULL.
     *
     * From the GDB documentation:
     *   Note that for all async output, while the token is allowed by the
     *   grammar and may be output by future versions of gdb for select async
     *   output messages, it is generally omitted. Frontends should treat all
     *   async output as reporting general changes in the state of the target
     *   and there should be no need to associate async output to any prior
     *   command. 
     *
     * After further investigation, I determined that newer GDB's will no
     * longer ever output this information. Older GDB's will. The commit
     * that made this change in GDB is 721c02de on April 24th, 2008.
     * The next GDB that was released was on October 6th, 2009, version 7.0.
     *
     * Before the above mentioned commit async *stopped commands would
     * sometimes output the token associated with the last token provided in
     * a GDB/MI input command. After that change, the token is never
     * associated with an async output command, even though the
     * documentation says it might be.
     *
     * Finally, even before that change when the token was output in the
     * async *stopped command, the developers of GDB felt that it was not
     * useful and should be avoided by front ends.
     *
     * With this information, I've determined that front ends should never
     * use this value to determine logic. However, the value is parsed in
     * order to accurately handle and represent the cases where this value
     * occurs.
     *
     * This represents the token value the front end provided to the
     * corresponding GDB/MI input command or NULL if no token was provided.
     */
    gdbwire_mi_token_t token;

    /** The kind of asynchronous record. */
    enum gdbwire_mi_async_record_kind kind;

    /** The asynchronous output class */
    enum gdbwire_mi_async_class async_class;

    /**
     * An optional list of results for this async output.
     *
     * Will be NULL if there is no results.
     */
    struct gdbwire_mi_result *result;
};

/** The GDB/MI result kind */
enum gdbwire_mi_result_kind {
    /** The result is a cstring */
    GDBWIRE_MI_CSTRING,
    /** The result is a tuple */
    GDBWIRE_MI_TUPLE,
    /** The result is a list */
    GDBWIRE_MI_LIST
};

/**
 * A GDB/MI result list.
 *
 * This is one of the important GDB/MI data structures. GDB communicates many
 * of it's values to the front end through this key/value data structure.
 *
 * It is basically a list of key/value pairs, where the key is a
 * variable name and the value expands to a string, a tuple of results or
 * a list of results.
 *
 * This can be thought of as a custom json object.
 */
struct gdbwire_mi_result {
    /** The kind of result this represents. */
    enum gdbwire_mi_result_kind kind;

    /** The key being described by the result. */
    char *variable;

    union {
        /** When kind is GDBWIRE_MI_CSTRING */
        char *cstring;

        /**
         * When kind is GDBWIRE_MI_TUPLE or GDBWIRE_MI_LIST.
         *
         * If kind is GDBWIRE_MI_TUPLE, each result in the tuple should have a
         * valid key according to the GDB/MI specification. That is, for
         * each result, result->variable should not be NULL.
         *   Note: GDBWIRE currently relaxes the above rule. It allows tuple's
         *   with out a key in each member. For instance, {key="value"}
         *   is what the GDB/MI specification advocates for, but some
         *   variations of GDB emit {"value"} and so GDBWIRE allows it.
         *
         * If kind is GDBWIRE_MI_LIST, the GDB/MI specification allows
         * results in this list to not have keys. That is, for each result,
         * result->variable may be NULL.
         *
         * Will be NULL if the tuple or list is empty.
         */
        struct gdbwire_mi_result *result;
    } variant;

    /** The next result or NULL if none */
    struct gdbwire_mi_result *next;
};

/**
 * An out of band GDB/MI stream record.
 *
 * A stream record is intended to provide the front end with information
 * from the console, the target or from GDB itself.
 */
struct gdbwire_mi_stream_record {
    /** The kind of stream record. */
    enum gdbwire_mi_stream_record_kind kind;
    /** The buffer provided in this stream record. */
    char *cstring;
};

void gdbwire_mi_output_free(struct gdbwire_mi_output *param);

struct gdbwire_mi_output *append_gdbwire_mi_output(
        struct gdbwire_mi_output *list, struct gdbwire_mi_output *item);

struct gdbwire_mi_result *append_gdbwire_mi_result(
        struct gdbwire_mi_result *list, struct gdbwire_mi_result *item);

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire_mi_pt.h ************************************************/
/***** Continuing where we left off in gdbwire_mi_parser.h *******************/

/* The opaque GDB/MI parser context */
struct gdbwire_mi_parser;

/**
 * The primary mechanism to alert users of GDB/MI notifications.
 *
 * The flow is like this:
 * - create a parser context (gdbwire_mi_parser_create)
 * - push onto the parser arbitrary amounts of data (gdbwire_mi_parser_push)
 *   - receive callbacks from inside gdbwire_mi_parser_push when
 *     it discovers callbacks the user will find interesting
 * - destroy the parser (gdbwire_mi_parser_destroy)
 */
struct gdbwire_mi_parser_callbacks {
    /**
     * An arbitrary pointer to associate with the callbacks.
     *
     * If the calling api is C++ it is useful to make this an instance
     * of an object you want to bind to the callback functions below.
     */
    void *context;
    
    /**
     * A GDB/MI output command is available.
     *
     * @param context
     * The context pointer above.
     *
     * @param output
     * The gdbwire_mi output command. This output command is now owned by the
     * function being invoked and should be destroyed when necessary.
     */
    void (*gdbwire_mi_output_callback)(void *context,
        struct gdbwire_mi_output *output);
};

/**
 * Create a GDB/MI parser context.
 *
 * @param callbacks
 * The callback functions to invoke upon discovery of parse data.
 *
 * @return
 * A new GDB/MI parser instance or NULL on error.
 */
struct gdbwire_mi_parser *gdbwire_mi_parser_create(
        struct gdbwire_mi_parser_callbacks callbacks);

/**
 * Destroy a gdbwire_mi_parser context.
 *
 * This function will do nothing if parser is NULL.
 *
 * @param parser
 * The instance the parser to destroy
 */
void gdbwire_mi_parser_destroy(struct gdbwire_mi_parser *parser);

/**
 * Push a null terminated string onto the parser.
 *
 * During this function, if a gdbwire_mi output command is discovered by
 * the parser (or any other useful GDB/MI notification), it will invoke
 * the appropriate callbacks assigned during parser creation.
 *
 * @param parser
 * The gdbwire_mi parser context to operate on.
 *
 * @param data
 * The parse data to push onto the parser.
 * 
 * @return
 * GDBWIRE_OK on success or appropriate error result on failure.
 */
enum gdbwire_result gdbwire_mi_parser_push(struct gdbwire_mi_parser *parser,
        const char *data);

/**
 * Push some parse data onto the parser.
 *
 * See gdbwire_mi_parser_push for details on function behavior.
 *
 * @param parser
 * The gdbwire_mi parser context to operate on.
 *
 * @param data
 * The parse data to push onto the parser.
 *
 * @param size
 * The size of the data to push onto the parser.
 *
 * @return
 * GDBWIRE_OK on success or appropriate error result on failure.
 */
enum gdbwire_result gdbwire_mi_parser_push_data(
        struct gdbwire_mi_parser *parser, const char *data, size_t size);

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire_mi_parser.h ********************************************/
/***** Continuing where we left off in gdbwire_mi_parser.c *******************/
/* #include "gdbwire_string.h" */

/* flex prototypes used in this unit */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif

/* Lexer set/destroy buffer to parse */
extern YY_BUFFER_STATE gdbwire_mi__scan_string(
    const char *yy_str, yyscan_t yyscanner);
extern void gdbwire_mi__delete_buffer(YY_BUFFER_STATE state,
    yyscan_t yyscanner);

/* Lexer get token function */
extern int gdbwire_mi_lex(yyscan_t yyscanner);
extern char *gdbwire_mi_get_text(yyscan_t yyscanner);
extern void gdbwire_mi_set_column(int column_no, yyscan_t yyscanner);

/* Lexer state create/destroy functions */
extern int gdbwire_mi_lex_init(yyscan_t *scanner);
extern int gdbwire_mi_lex_destroy(yyscan_t scanner);

struct gdbwire_mi_parser {
    /* The buffer pushed into the parser from the user */
    struct gdbwire_string *buffer;
    /* The GDB/MI lexer state */
    yyscan_t mils;
    /* The GDB/MI push parser state */
    gdbwire_mi_pstate *mipst;
    /* The client parser callbacks */
    struct gdbwire_mi_parser_callbacks callbacks;
};

struct gdbwire_mi_parser *
gdbwire_mi_parser_create(struct gdbwire_mi_parser_callbacks callbacks)
{
    struct gdbwire_mi_parser *parser;

    parser = (struct gdbwire_mi_parser *)calloc(1,
        sizeof(struct gdbwire_mi_parser));
    if (!parser) {
        return NULL;
    }

    /* Create a new buffer for the user to push parse data into */
    parser->buffer = gdbwire_string_create();
    if (!parser->buffer) {
        free(parser);
        return NULL;
    }

    /* Create a new lexer state instance */
    if (gdbwire_mi_lex_init(&parser->mils) != 0) {
        gdbwire_string_destroy(parser->buffer);
        free(parser);
        return NULL;
    }

    /* Create a new push parser state instance */
    parser->mipst = gdbwire_mi_pstate_new();
    if (!parser->mipst) {
        gdbwire_mi_lex_destroy(parser->mils);
        gdbwire_string_destroy(parser->buffer);
        free(parser);
        return NULL;
    }

    /* Ensure that the callbacks are non null */
    if (!callbacks.gdbwire_mi_output_callback) {
        gdbwire_mi_pstate_delete(parser->mipst);
        gdbwire_mi_lex_destroy(parser->mils);
        gdbwire_string_destroy(parser->buffer);
        free(parser);
        return NULL;
    }

    parser->callbacks = callbacks;

    return parser;
}

void gdbwire_mi_parser_destroy(struct gdbwire_mi_parser *parser)
{
    if (parser) {
        /* Free the parse buffer */
        if (parser->buffer) {
            gdbwire_string_destroy(parser->buffer);
            parser->buffer = NULL;
        }

        /* Free the lexer instance */
        if (parser->mils) {
            gdbwire_mi_lex_destroy(parser->mils);
            parser->mils = 0;
        }

        /* Free the push parser instance */
        if (parser->mipst) {
            gdbwire_mi_pstate_delete(parser->mipst);
            parser->mipst = NULL;
        }

        free(parser);
        parser = NULL;
    }
}

static struct gdbwire_mi_parser_callbacks
gdbwire_mi_parser_get_callbacks(struct gdbwire_mi_parser *parser)
{
    return parser->callbacks;
}

/**
 * Parse a single line of output in GDB/MI format.
 *
 * The normal usage of this function is to call it over and over again with
 * more data lines and wait for it to return an mi output command.
 *
 * @param parser
 * The parser context to operate on.
 *
 * @param line
 * A line of output in GDB/MI format to be parsed.
 *
 * \return
 * GDBWIRE_OK on success or appropriate error result on failure.
 */
static enum gdbwire_result
gdbwire_mi_parser_parse_line(struct gdbwire_mi_parser *parser,
    const char *line)
{
    struct gdbwire_mi_parser_callbacks callbacks =
        gdbwire_mi_parser_get_callbacks(parser);
    struct gdbwire_mi_output *output = 0;
    YY_BUFFER_STATE state = 0;
    int pattern, mi_status;

    GDBWIRE_ASSERT(parser && line);

    /* Create a new input buffer for flex. */
    state = gdbwire_mi__scan_string(line, parser->mils);
    GDBWIRE_ASSERT(state);
    gdbwire_mi_set_column(1, parser->mils);

    /* Iterate over all the tokens found in the scanner buffer */
    do {
        pattern = gdbwire_mi_lex(parser->mils);
        if (pattern == 0)
            break;
        mi_status = gdbwire_mi_push_parse(parser->mipst, pattern, NULL,
            parser->mils, &output);
    } while (mi_status == YYPUSH_MORE);

    /* Free the scanners buffer */
    gdbwire_mi__delete_buffer(state, parser->mils);

    /**
     * The push parser will return,
     * - 0 if parsing was successful (return is due to end-of-input).
     * - 1 if parsing failed because of invalid input, i.e., input
     *     that contains a syntax error or that causes YYABORT to be invoked.
     * - 2 if parsing failed due to memory exhaustion. 
     * - YYPUSH_MORE if more input is required to finish parsing the grammar. 
     * Anything besides this would be unexpected.
     *
     * The grammar is designed to accept an infinate list of GDB/MI
     * output commands. For this reason, YYPUSH_MORE is the expected
     * return value of all the calls to gdbwire_mi_push_parse. However,
     * in reality, gdbwire only translates a line at a time from GDB.
     * When the line is finished, gdbwire_mi_lex returns 0, and the parsing
     * is done.
     */

    /* Check mi_status, will be 1 on parse error, and YYPUSH_MORE on success */
    GDBWIRE_ASSERT(mi_status == 1 || mi_status == YYPUSH_MORE);

    /* Each GDB/MI line should produce an output command */
    GDBWIRE_ASSERT(output);
    output->line = gdbwire_strdup(line);

    callbacks.gdbwire_mi_output_callback(callbacks.context, output);

    return GDBWIRE_OK;
}

/**
 * Get the next line available in the buffer.
 *
 * @param buffer
 * The entire buffer the user has pushed onto the gdbwire_mi parser
 * through gdbwire_mi_parser_push. If a line is found, the returned line
 * will be removed from this buffer.
 *
 * @param line
 * Will return as an allocated line if a line is available or NULL
 * otherwise. If this function does not return GDBWIRE_OK then ignore
 * the output of this parameter. It is the callers responsibility to
 * free the memory.
 *
 * @return
 * GDBWIRE_OK on success or appropriate error result on failure.
 */
static enum gdbwire_result
gdbwire_mi_parser_get_next_line(struct gdbwire_string *buffer,
        struct gdbwire_string **line)
{
    enum gdbwire_result result = GDBWIRE_OK;

    GDBWIRE_ASSERT(buffer && line);

    char *data = gdbwire_string_data(buffer);
    size_t size = gdbwire_string_size(buffer);
    size_t pos = gdbwire_string_find_first_of(buffer, "\r\n");

    /**
     * Search to see if a newline has been reached in gdb/mi.
     * If a line of data has been recieved, process it.
     */
    if (pos != size) {
        int status;

        /**
         * We have the position of the newline character from
         * gdbwire_string_find_first_of. However, the length must be
         * calculated to make a copy of the line.
         *
         * This is either pos + 1 (for \r or \n) or pos + 1 + 1 for (\r\n).
         * Check for\r\n for the special case.
         */
        size_t line_length = (data[pos] == '\r' && (pos + 1 < size) &&
                data[pos + 1] == '\n') ? pos + 2 : pos + 1;

        /**
         * - allocate the buffer
         * - append the new line
         * - append a null terminating character
         * - if successful, delete the new line found from buffer
         * - any failures cleanup and return an error
         */
        *line = gdbwire_string_create();
        GDBWIRE_ASSERT(*line);

        status = gdbwire_string_append_data(*line, data, line_length);
        GDBWIRE_ASSERT_GOTO(status == 0, result, cleanup);

        status = gdbwire_string_append_data(*line, "\0", 1);
        GDBWIRE_ASSERT_GOTO(status == 0, result, cleanup);

        status = gdbwire_string_erase(buffer, 0, line_length);
        GDBWIRE_ASSERT_GOTO(status == 0, result, cleanup);
    }

    return result;

cleanup:
    gdbwire_string_destroy(*line);
    *line = 0;
    return result;

}

enum gdbwire_result
gdbwire_mi_parser_push(struct gdbwire_mi_parser *parser, const char *data)
{
    return gdbwire_mi_parser_push_data(parser, data, strlen(data));
}

enum gdbwire_result
gdbwire_mi_parser_push_data(struct gdbwire_mi_parser *parser, const char *data,
    size_t size)
{
    struct gdbwire_string *line = 0;
    enum gdbwire_result result = GDBWIRE_OK;
    int has_newline = 0;
    size_t index;

    GDBWIRE_ASSERT(parser && data);

    /**
     * No need to parse an MI command until a newline occurs.
     *
     * A gdb/mi command may be a very long line. For this reason, it is
     * better to check the data passed into this function once for a newline
     * rather than checking all the data every time this function is called.
     * This optimizes the case where this function is called one character
     * at a time.
     */
    for (index = size; index > 0; --index) {
        if (data[index-1] == '\n' || data[index-1] == '\r') {
            has_newline = 1;
            break;
        }
    }

    GDBWIRE_ASSERT(gdbwire_string_append_data(parser->buffer, data, size) == 0);

    if (has_newline) {
        for (;;) {
            result = gdbwire_mi_parser_get_next_line(parser->buffer, &line);
            GDBWIRE_ASSERT_GOTO(result == GDBWIRE_OK, result, cleanup);

            if (line) {
                result = gdbwire_mi_parser_parse_line(parser,
                    gdbwire_string_data(line));
                gdbwire_string_destroy(line);
                line = 0;
                GDBWIRE_ASSERT_GOTO(result == GDBWIRE_OK, result, cleanup);
            } else {
                break;
            }
        }
    }

cleanup:
    return result;
}
/***** End of gdbwire_mi_parser.c ********************************************/
/***** Begin file gdbwire_mi_pt_alloc.c **************************************/
#include <stdlib.h>

/* #include "gdbwire_mi_pt.h" */
/***** Include gdbwire_mi_pt_alloc.h in the middle of gdbwire_mi_pt_alloc.c **/
/***** Begin file gdbwire_mi_pt_alloc.h **************************************/
#ifndef GDBWIRE_MI_PT_ALLOC_H
#define GDBWIRE_MI_PT_ALLOC_H

#ifdef __cplusplus 
extern "C" { 
#endif 

/**
 * Responsible for allocating and deallocating gdbwire_mi_pt objects.
 */

/* struct gdbwire_mi_output */
struct gdbwire_mi_output *gdbwire_mi_output_alloc(void);
void gdbwire_mi_output_free(struct gdbwire_mi_output *param);

/* struct gdbwire_mi_result_record */
struct gdbwire_mi_result_record *gdbwire_mi_result_record_alloc(void);
void gdbwire_mi_result_record_free(struct gdbwire_mi_result_record *param);

/* struct gdbwire_mi_result */
struct gdbwire_mi_result *gdbwire_mi_result_alloc(void);
void gdbwire_mi_result_free(struct gdbwire_mi_result *param);

/* struct gdbwire_mi_oob_record */
struct gdbwire_mi_oob_record *gdbwire_mi_oob_record_alloc(void);
void gdbwire_mi_oob_record_free(struct gdbwire_mi_oob_record *param);

/* struct gdbwire_mi_async_record */
struct gdbwire_mi_async_record *gdbwire_mi_async_record_alloc(void);
void gdbwire_mi_async_record_free(struct gdbwire_mi_async_record *param);

/* struct gdbwire_mi_stream_record */
struct gdbwire_mi_stream_record *gdbwire_mi_stream_record_alloc(void);
void gdbwire_mi_stream_record_free(struct gdbwire_mi_stream_record *param);

#ifdef __cplusplus 
}
#endif 

#endif /* GDBWIRE_MI_PT_ALLOC_H */
/***** End of gdbwire_mi_pt_alloc.h ******************************************/
/***** Continuing where we left off in gdbwire_mi_pt_alloc.c *****************/

/* struct gdbwire_mi_output */
struct gdbwire_mi_output *
gdbwire_mi_output_alloc(void)
{
    return calloc(1, sizeof (struct gdbwire_mi_output));
}

void
gdbwire_mi_output_free(struct gdbwire_mi_output *param)
{
    if (param) {
        switch (param->kind) {
            case GDBWIRE_MI_OUTPUT_OOB:
                gdbwire_mi_oob_record_free(param->variant.oob_record);
                param->variant.oob_record = NULL;
                break;
            case GDBWIRE_MI_OUTPUT_RESULT:
                gdbwire_mi_result_record_free(param->variant.result_record);
                param->variant.result_record = NULL;
                break;
            case GDBWIRE_MI_OUTPUT_PROMPT:
                break;
            case GDBWIRE_MI_OUTPUT_PARSE_ERROR:
                free(param->variant.error.token);
                param->variant.error.token = NULL;
                break;
        }

        free(param->line);
        param->line = 0;

        gdbwire_mi_output_free(param->next);
        param->next = NULL;

        free(param);
        param = NULL;
    }
}

/* struct gdbwire_mi_result_record */
struct gdbwire_mi_result_record *
gdbwire_mi_result_record_alloc(void)
{
    return calloc(1, sizeof (struct gdbwire_mi_result_record));
}

void
gdbwire_mi_result_record_free(struct gdbwire_mi_result_record *param)
{
    if (param) {
        free(param->token);

        gdbwire_mi_result_free(param->result);
        param->result = NULL;

        free(param);
        param = NULL;
    }
}

/* struct gdbwire_mi_result */
struct gdbwire_mi_result *
gdbwire_mi_result_alloc(void)
{
    return calloc(1, sizeof (struct gdbwire_mi_result));
}

void
gdbwire_mi_result_free(struct gdbwire_mi_result *param)
{
    if (param) {
        if (param->variable) {
            free(param->variable);
            param->variable = NULL;
        }

        switch (param->kind) {
            case GDBWIRE_MI_CSTRING:
                if (param->variant.cstring) {
                    free(param->variant.cstring);
                    param->variant.cstring = NULL;
                }
                break;
            case GDBWIRE_MI_TUPLE:
            case GDBWIRE_MI_LIST:
                gdbwire_mi_result_free(param->variant.result);
                param->variant.result = NULL;
                break;
        }

        gdbwire_mi_result_free(param->next);
        param->next = NULL;

        free(param);
        param = NULL;
    }
}

/* struct gdbwire_mi_oob_record */
struct gdbwire_mi_oob_record *
gdbwire_mi_oob_record_alloc(void)
{
    return calloc(1, sizeof (struct gdbwire_mi_oob_record));
}

void
gdbwire_mi_oob_record_free(struct gdbwire_mi_oob_record *param)
{
    if (param) {
        switch(param->kind) {
            case GDBWIRE_MI_ASYNC:
                gdbwire_mi_async_record_free(param->variant.async_record);
                param->variant.async_record = NULL;
                break;
            case GDBWIRE_MI_STREAM:
                gdbwire_mi_stream_record_free(param->variant.stream_record);
                param->variant.stream_record = NULL;
                break;
        }

        free(param);
        param = NULL;
    }
}

/* struct gdbwire_mi_async_record */
struct gdbwire_mi_async_record *
gdbwire_mi_async_record_alloc(void)
{
    return calloc(1, sizeof (struct gdbwire_mi_async_record));
}

void
gdbwire_mi_async_record_free(struct gdbwire_mi_async_record *param)
{
    if (param) {
        free(param->token);

        gdbwire_mi_result_free(param->result);
        param->result = NULL;

        free(param);
        param = NULL;
    }
}

/* struct gdbwire_mi_stream_record */
struct gdbwire_mi_stream_record *
gdbwire_mi_stream_record_alloc(void)
{
    return calloc(1, sizeof (struct gdbwire_mi_stream_record));
}

void
gdbwire_mi_stream_record_free(struct gdbwire_mi_stream_record *param)
{
    if (param) {
        if (param->cstring) {
            free(param->cstring);
            param->cstring = NULL;
        }

        free(param);
        param = NULL;
    }
}
/***** End of gdbwire_mi_pt_alloc.c ******************************************/
/***** Begin file gdbwire_mi_pt.c ********************************************/
#include <stdio.h>
#include <stdlib.h>

/* #include "gdbwire_mi_pt.h" */

struct gdbwire_mi_output *
append_gdbwire_mi_output(struct gdbwire_mi_output *list,
    struct gdbwire_mi_output *item)
{
    if (!item)
        return NULL;

    if (!list)
        list = item;
    else {
        struct gdbwire_mi_output *cur = list;

        while (cur->next)
            cur = cur->next;

        cur->next = item;
    }

    return list;
}

struct gdbwire_mi_result *
append_gdbwire_mi_result(struct gdbwire_mi_result *list,
    struct gdbwire_mi_result *item)
{
    if (!item)
        return NULL;

    if (!list)
        list = item;
    else {
        struct gdbwire_mi_result *cur = list;

        while (cur->next)
            cur = cur->next;

        cur->next = item;
    }

    return list;
}
/***** End of gdbwire_mi_pt.c ************************************************/
/***** Begin file gdbwire_mi_command.c ***************************************/
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* #include "gdbwire_sys.h" */
/* #include "gdbwire_assert.h" */
/***** Include gdbwire_mi_command.h in the middle of gdbwire_mi_command.c ****/
/***** Begin file gdbwire_mi_command.h ***************************************/
#ifndef GDBWIRE_MI_COMMAND_H
#define GDBWIRE_MI_COMMAND_H

#ifdef __cplusplus 
extern "C" { 
#endif 

/* #include "gdbwire_result.h" */
/* #include "gdbwire_mi_pt.h" */

/**
 * An enumeration representing the supported GDB/MI commands.
 */
enum gdbwire_mi_command_kind {
    /* -break-info */
    GDBWIRE_MI_BREAK_INFO,

    /* -stack-info-frame */
    GDBWIRE_MI_STACK_INFO_FRAME,

    /* -file-list-exec-source-file */
    GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILE,
    /* -file-list-exec-source-files */
    GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILES
};

/**
 * An enumeration representing if debug symbols are fully loaded for a source.
 */
enum gdbwire_mi_debug_fully_read_kind {
    /** It is unknown if the debug symbols are fully loaded */
    GDBWIRE_MI_DEBUG_FULLY_READ_UNKNOWN,
    /** The debug symbols are fully loaded */
    GDBWIRE_MI_DEBUG_FULLY_READ_TRUE,
    /** The debug symbols are not fully loaded */
    GDBWIRE_MI_DEBUG_FULLY_READ_FALSE
};

/** A linked list of source files. */
struct gdbwire_mi_source_file {
    /** A relative path to a file, never NULL */
    char *file;
    /**An absolute path to a file, NULL if unavailable */
    char *fullname;
    /** If the source file has it's debug fully read, or not, or unknown */
    enum gdbwire_mi_debug_fully_read_kind debug_fully_read;
    /** The next file name or NULL if no more. */
    struct gdbwire_mi_source_file *next;
};

/** The disposition of a breakpoint. What to do after hitting it. */
enum gdbwire_mi_breakpoint_disp_kind {
    GDBWIRE_MI_BP_DISP_DELETE,           /** Delete on next hit */
    GDBWIRE_MI_BP_DISP_DELETE_NEXT_STOP, /** Delete on next stop, hit or not */
    GDBWIRE_MI_BP_DISP_DISABLE,          /** Disable on next hit */
    GDBWIRE_MI_BP_DISP_KEEP,             /** Leave the breakpoint in place */
    GDBWIRE_MI_BP_DISP_UNKNOWN           /** When GDB doesn't specify */
};

/**
 * A linked list of breakpoints.
 *
 * A breakpoint is a breakpoint, a tracepoint, a watchpoing or a
 * catchpoint. The GDB breakpoint model is quite sophisticated.
 * This structure can be extended when necessary.
 */
struct gdbwire_mi_breakpoint {
    /**
     * The breakpoint number.
     *
     * An integer, however, for a breakpoint that represents one location of
     * a multiple location breakpoint, this will be a dotted pair, like ‘1.2’. 
     *
     * Never NULL.
     */
    char *number;

    /**
     * Determines if this is a multiple location breakpoint.
     *
     * True for a multi-location breakpoint, false otherwise.
     *
     * It is possible that a breakpoint corresponds to several locations in
     * your program. For example, several functions may have the same name.
     * For the following source code,
     *   int foo(int p) { return p; }
     *   double foo(double p) { return p; }
     *   int main() { int i = 1; double d = 2.3; return foo(i) + foo(d); }
     * If the user sets a breakpoint at foo by typing,
     *   b foo
     * Then gdb will create 3 breakpoints. The multiple location breakpoint,
     * which is the parent of the two breakpoints created for each foo
     * function. Here is the output of gdb from the CLI perspective,
     *   Num     Type           Disp Enb Address            What
     *   1       breakpoint     keep y   <MULTIPLE>         
     *   1.1                         y     0x4004dd in foo(int) at main.cpp:1
     *   1.2                         y     0x4004eb in foo(double) at main.cpp:2
     *
     * However, if the user created a breakpoint for main by typing,
     *   b main
     * Then gdb will only create a single breakpoint which would look like,
     *   1       breakpoint     keep y   0x4004fa in main() at main.cpp:3
     *
     * When this is true, the address field will be "<MULTIPLE>" and
     * the field multi_breakpoints will represent the breakpoints that this
     * multiple location breakpoint has created.
     */
    unsigned char multi:1;
    
    /**
     * True for breakpoints of a multi-location breakpoint, otherwise false.
     *
     * For the example above, 1.1 and 1.2 would have this field set true.
     *
     * When this is true, the field multi_breakpoint will represent
     * the multiple location breakpoint that has created this breakpoint.
     */
    unsigned char from_multi:1;

    /**
     * The breakpoint type.
     *
     * Typically "breakpoint", "watchpoint" or "catchpoint", but can be
     * a variety of different values. In gdb, see breakpoint.c:bptype_string
     * to see all the different possibilities.
     *
     * This will be NULL for breakpoints of a multiple location breakpoint.
     * In this circumstance, check the multi_breakpoint field for the
     * multiple location breakpoint type field.
     */
    char *type;

    /**
     * The type of the catchpoint or NULL if not a catch point.
     *
     * This field is only valid when the breakpoint is a catchpoint.
     * Unfortuntely, gdb says the "type" of the breakpoint in the type field
     * is "breakpoint" not "catchpoint". So if this field is non-NULL, it is
     * safe to assume that this breakpoint represents at catch point.
     */
    char *catch_type;

    /**
     * The breakpoint disposition.
     *
     * For multiple location breakpoints, this will be
     * GDBWIRE_MI_BP_DISP_UNKNOWN. In this circumstance, check the
     * multi_breakpoint field for the multiple location breakpoint
     * disposition field.
     */
    enum gdbwire_mi_breakpoint_disp_kind disposition;

    /** True if enabled or False if disabled. */
    unsigned char enabled:1;

    /**
     * The address of the breakpoint.
     *
     * This may be
     * - a hexidecimal number, representing the address
     * - the string ‘<PENDING>’ for a pending breakpoint
     * - the string ‘<MULTIPLE>’ for a breakpoint with multiple locations
     *
     * This field will be NULL if no address can be determined.
     * For example, a watchpoint does not have an address. 
     */
    char *address;

    /** 
     * The name of the function or NULL if unknown.
     */
    char *func_name;

    /**
     * A relative path to the file the breakpoint is in or NULL if unknown.
     */
    char *file;

    /**
     * An absolute path to the file the breakpoint is in or NULL if unknown.
     */
    char *fullname;

    /**
     * The line number the breakpoint is at or 0 if unkonwn.
     */
    unsigned long line;

    /**
     * The number of times this breakpoint has been hit.
     *
     * For breakpoints of multi-location breakpoints, this will be 0.
     * Look at the multi-location breakpoint field instead.
     */
    unsigned long times;

    /**
     * The location of the breakpoint as originally specified by the user. 
     *
     * This may be NULL for instance, for breakpoints for multi-breakpoints.
     */
    char *original_location;

    /**
     * True for a pending breakpoint, otherwise false.
     *
     * When this is true, the address field will be "<PENDING>".
     */
    unsigned char pending:1;

    /**
     * The breakpoints for a multi-location breakpoint.
     *
     * If multi is true, this will be the breakpoints associated with the
     * multiple location breakpoint. Otherwise will be NULL.
     */
    struct gdbwire_mi_breakpoint *multi_breakpoints;

    /**
     * A pointer to the multi location breakpoint that created this breakpoint.
     *
     * When the field from_multi is true, this will be a pointer to the
     * multi-location breakpoint that created this breakpoint. Otherwise NULL.
     *
     * For the example above in the multi field, breakpoints 1.1 and 1.2
     * would have this field pointing to the breakpoint 1.
     */
    struct gdbwire_mi_breakpoint *multi_breakpoint;


    /** The next breakpoint or NULL if no more. */
    struct gdbwire_mi_breakpoint *next;
};

struct gdbwire_mi_stack_frame {
    /**
     * The frame number.
     *
     * Where 0 is the topmost frame, i.e., the innermost function. 
     *
     * Always present.
     */
    unsigned level;

    /**
     * The address ($pc value) of the frame.
     *
     * May be NULL if GDB can not determine the frame address.
     */
    char *address;

   /**
    * The function name for the frame. May be NULL if unknown.
    */
   char *func;

   /**
    * The file name for the frame. May be NULL if unknown.
    */
   char *file;

   /**
    * The fullname name for the frame. May be NULL if unknown.
    */
   char *fullname;

   /**
    * Line number corresponding to the $pc. Maybe be 0 if unknown.
    */
   int line;

   /**
    * The shared library where this function is defined.
    *
    * This is only given if the frame's function is not known. 
    * May be NULL if unknown.
    */
   char *from;
};

/**
 * Represents a GDB/MI command.
 */
struct gdbwire_mi_command {
    /**
     * The kind of mi command this represents.
     */
    enum gdbwire_mi_command_kind kind;

    union {
        /** When kind == GDBWIRE_MI_BREAK_INFO */
        struct {
            /** The list of breakpoints, NULL if none exist.  */
            struct gdbwire_mi_breakpoint *breakpoints;
        } break_info;

        /** When kind == GDBWIRE_MI_STACK_INFO_FRAME */
        struct {
            struct gdbwire_mi_stack_frame *frame;
        } stack_info_frame;

        /** When kind == GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILE */
        struct {
            /**
             * The line number the inferior is currently executing at.
             */
            int line;

            /**
             * The filename the inferior is currently executing at.
             *
             * This is usually a relative path.
             */
            char *file;

            /**
             * The filename the inferior is currently executing at.
             *
             * This is an absolute path.
             *
             * This command was addd in 2004, however, it was possible
             * at the time that only the "file" field would be put out and
             * the "fullname" field would be omitted. In 2012, in git commit,
             * f35a17b5, gdb was changed to always omit the "fullname" field.
             */
            char *fullname;

            /**
             * Determines if the file includes preprocessor macro information.
             *
             * This command was added in 2004. However, the macro-info
             * field was added to the output in 2008 in git commit 17784837.
             *
             * Only check this field if macro_info_exists is true.
             */
            char macro_info:1;

            /** True if macro-info field was in mi output, otherwise false */
            char macro_info_exists:1;
        } file_list_exec_source_file;

        /** When kind == GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILES */
        struct {
            /**
             * A list of files that make up the inferior.
             *
             * When there are no files (if the gdb does not have an inferior
             * loaded) than files will be NULL.
             *
             * This command was addd in 2004, however, it was possible
             * at the time that only the "file" field would be put out and
             * the "fullname" field would be omitted. In 2012, in git commit,
             * f35a17b5, gdb was changed to always omit the "fullname" field.
             */
            struct gdbwire_mi_source_file *files;
        } file_list_exec_source_files;
        
    } variant;
};

/**
 * Get a gdbwire MI command from the result record.
 *
 * @param kind
 * The kind of command the result record is associated with.
 *
 * @param result_record
 * The result record to turn into a command.
 *
 * @param out_mi_command
 * Will return an allocated gdbwire mi command if GDBWIRE_OK is returned
 * from this function. You should free this memory with
 * gdbwire_mi_command_free when you are done with it.
 *
 * @return
 * The result of this function.
 */
enum gdbwire_result gdbwire_get_mi_command(
        enum gdbwire_mi_command_kind kind,
        struct gdbwire_mi_result_record *result_record,
        struct gdbwire_mi_command **out_mi_command);

/**
 * Free the gdbwire mi command.
 *
 * @param mi_command
 * The mi command to free.
 */
void gdbwire_mi_command_free(struct gdbwire_mi_command *mi_command);

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire_mi_command.h *******************************************/
/***** Continuing where we left off in gdbwire_mi_command.c ******************/

/**
 * Free a source file list.
 *
 * @param files
 * The source file list to free, OK to pass in NULL.
 */
static void
gdbwire_mi_source_files_free(struct gdbwire_mi_source_file *files)
{
    struct gdbwire_mi_source_file *tmp, *cur = files;
    while (cur) {
        free(cur->file);
        free(cur->fullname);
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

/**
 * Free a breakpoint list.
 *
 * @param breakpoints
 * The breakpoint list to free, OK to pass in NULL.
 */
static void
gdbwire_mi_breakpoints_free(struct gdbwire_mi_breakpoint *breakpoints)
{
    struct gdbwire_mi_breakpoint *tmp, *cur = breakpoints;
    while (cur) {
        free(cur->original_location);
        free(cur->fullname);
        free(cur->file);
        free(cur->func_name);
        free(cur->address);
        free(cur->catch_type);
        free(cur->type);
        free(cur->number);

        gdbwire_mi_breakpoints_free(cur->multi_breakpoints);
        cur->multi_breakpoint = 0;

        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

/**
 * Free a stack frame.
 *
 * @param frame
 * The frame to free, OK to pass in NULL.
 */
static void
gdbwire_mi_stack_frame_free(struct gdbwire_mi_stack_frame *frame)
{
    free(frame->address);
    free(frame->func);
    free(frame->file);
    free(frame->fullname);
    free(frame->from);
    free(frame);
}

/**
 * Convert a string to an unsigned long.
 *
 * @param str
 * The string to convert.
 *
 * @param num
 * If GDBWIRE_OK is returned, this will be returned as the number.
 *
 * @return
 * GDBWIRE_OK on success, and num is valid, or GDBWIRE_LOGIC on failure.
 */
static enum gdbwire_result
gdbwire_string_to_ulong(char *str, unsigned long *num)
{
    enum gdbwire_result result = GDBWIRE_LOGIC;
    unsigned long int strtol_result;
    char *end_ptr;

    GDBWIRE_ASSERT(str);
    GDBWIRE_ASSERT(num);

    errno = 0;
    strtol_result = strtoul(str, &end_ptr, 10);
    if (errno == 0 && str != end_ptr && *end_ptr == '\0') {
        *num = strtol_result;
        result = GDBWIRE_OK;
    }

    return result;
}

/**
 * Handle breakpoints from the -break-info command.
 *
 * @param mi_result
 * The mi parse tree starting from bkpt={...}
 *
 * @param bkpt
 * Allocated breakpoint on way out on success. Otherwise NULL on way out.
 *
 * @return
 * GDBWIRE_OK on success and bkpt is an allocated breakpoint. Otherwise
 * the appropriate error code and bkpt will be NULL.
 */
static enum gdbwire_result
break_info_for_breakpoint(struct gdbwire_mi_result *mi_result,
        struct gdbwire_mi_breakpoint **bkpt)
{
    enum gdbwire_result result = GDBWIRE_OK;

    struct gdbwire_mi_breakpoint *breakpoint = 0;

    char *number = 0;
    int multi = 0;
    int from_multi = 0;
    char *catch_type = 0;
    int pending = 0;
    int enabled = 0;
    char *address = 0;
    char *type = 0;
    enum gdbwire_mi_breakpoint_disp_kind disp_kind = GDBWIRE_MI_BP_DISP_UNKNOWN;
    char *func_name = 0;
    char *file = 0;
    char *fullname = 0;
    unsigned long line = 0;
    unsigned long times = 0;
    char *original_location = 0;
    struct gdbwire_mi_breakpoint *multi_breakpoints = 0;

    GDBWIRE_ASSERT(mi_result);
    GDBWIRE_ASSERT(bkpt);

    *bkpt = 0;

    while (mi_result) {
        GDBWIRE_ASSERT(mi_result->variable);
        if (strcmp(mi_result->variable, "number") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            number = mi_result->variant.cstring;

            if (strstr(number, ".") != NULL) {
                from_multi = 1;
            }
        } else if (strcmp(mi_result->variable, "enabled") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            enabled = mi_result->variant.cstring[0] == 'y';
        } else if (strcmp(mi_result->variable, "addr") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            multi = strcmp(mi_result->variant.cstring, "<MULTIPLE>") == 0;
            pending = strcmp(mi_result->variant.cstring, "<PENDING>") == 0;
            address = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "catch-type") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            catch_type = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "type") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            type = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "disp") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            if (strcmp(mi_result->variant.cstring, "del") == 0) {
                disp_kind = GDBWIRE_MI_BP_DISP_DELETE;
            } else if (strcmp(mi_result->variant.cstring, "dstp") == 0) {
                disp_kind = GDBWIRE_MI_BP_DISP_DELETE_NEXT_STOP;
            } else if (strcmp(mi_result->variant.cstring, "dis") == 0) {
                disp_kind = GDBWIRE_MI_BP_DISP_DISABLE;
            } else if (strcmp(mi_result->variant.cstring, "keep") == 0) {
                disp_kind = GDBWIRE_MI_BP_DISP_KEEP;
            } else {
                return GDBWIRE_LOGIC;
            }
        } else if (strcmp(mi_result->variable, "func") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            func_name = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "file") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            file = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "fullname") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            fullname = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "line") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            GDBWIRE_ASSERT(gdbwire_string_to_ulong(
                    mi_result->variant.cstring, &line) == GDBWIRE_OK);
        } else if (strcmp(mi_result->variable, "times") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            GDBWIRE_ASSERT(gdbwire_string_to_ulong(
                    mi_result->variant.cstring, &times) == GDBWIRE_OK);
        } else if (strcmp(mi_result->variable, "original-location") == 0) {
            GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_CSTRING);
            original_location = mi_result->variant.cstring;
        } else if (strcmp(mi_result->variable, "locations") == 0) {
            struct gdbwire_mi_result *loc_result = mi_result;
            GDBWIRE_ASSERT(loc_result->kind == GDBWIRE_MI_LIST);

            loc_result = loc_result->variant.result;
            while (loc_result) {
                GDBWIRE_ASSERT(loc_result->kind == GDBWIRE_MI_TUPLE);
                struct gdbwire_mi_breakpoint *new_bkpt = 0;
                result = break_info_for_breakpoint(
                        loc_result->variant.result, &new_bkpt);

                /* Append breakpoint to the multiple location breakpoints */
                if (multi_breakpoints) {
                    struct gdbwire_mi_breakpoint *cur = multi_breakpoints;
                    while (cur->next) {
                        cur = cur->next;
                    }
                    cur->next = new_bkpt;
                } else {
                    multi_breakpoints = new_bkpt;
                }
                loc_result = loc_result->next;
            }
        }

        mi_result = mi_result->next;
    }

    /* Validate required fields before proceeding. */
    GDBWIRE_ASSERT(number);

    /* At this point, allocate a breakpoint */
    breakpoint = calloc(1, sizeof(struct gdbwire_mi_breakpoint));
    if (!breakpoint) {
        return GDBWIRE_NOMEM;
    }

    breakpoint->multi = multi;
    breakpoint->from_multi = from_multi;
    breakpoint->number = gdbwire_strdup(number);
    breakpoint->type = (type)?gdbwire_strdup(type):0;
    breakpoint->catch_type = (catch_type)?gdbwire_strdup(catch_type):0;
    breakpoint->disposition = disp_kind;
    breakpoint->enabled = enabled;
    breakpoint->address = (address)?gdbwire_strdup(address):0;
    breakpoint->func_name = (func_name)?gdbwire_strdup(func_name):0;
    breakpoint->file = (file)?gdbwire_strdup(file):0;
    breakpoint->fullname = (fullname)?gdbwire_strdup(fullname):0;
    breakpoint->line = line;
    breakpoint->times = times;
    breakpoint->original_location =
        (original_location)?gdbwire_strdup(original_location):0;
    breakpoint->pending = pending;
    breakpoint->multi_breakpoints = multi_breakpoints;

    if (breakpoint->multi_breakpoints) {
        struct gdbwire_mi_breakpoint *cur = breakpoint->multi_breakpoints;
        while (cur) {
            cur->multi_breakpoint = breakpoint;
            cur = cur->next;
        }
    }

    /* Handle the out of memory situation */
    if (!breakpoint->number ||
        (type && !breakpoint->type) ||
        (catch_type && !breakpoint->catch_type) ||
        (address && !breakpoint->address) ||
        (func_name && !breakpoint->func_name) ||
        (file && !breakpoint->file) ||
        (fullname && !breakpoint->fullname) ||
        (original_location && !breakpoint->original_location)) {
        gdbwire_mi_breakpoints_free(breakpoint);
        breakpoint = 0;
        result = GDBWIRE_NOMEM;
    }

    *bkpt = breakpoint;

    return result;
}

/**
 * Handle the -break-info command.
 *
 * @param result_record
 * The mi result record that makes up the command output from gdb.
 *
 * @param out
 * The output command, null on error.
 *
 * @return
 * GDBWIRE_OK on success, otherwise failure and out is NULL.
 */
static enum gdbwire_result
break_info(
    struct gdbwire_mi_result_record *result_record,
    struct gdbwire_mi_command **out)
{
    enum gdbwire_result result = GDBWIRE_OK;
    struct gdbwire_mi_result *mi_result;
    struct gdbwire_mi_command *mi_command = 0;
    struct gdbwire_mi_breakpoint *breakpoints = 0, *cur_bkpt;
    int found_body = 0;

    GDBWIRE_ASSERT(result_record);
    GDBWIRE_ASSERT(out);

    *out = 0;

    GDBWIRE_ASSERT(result_record->result_class == GDBWIRE_MI_DONE);
    GDBWIRE_ASSERT(result_record->result);

    mi_result = result_record->result;

    GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_TUPLE);
    GDBWIRE_ASSERT(strcmp(mi_result->variable, "BreakpointTable") == 0);
    GDBWIRE_ASSERT(mi_result->variant.result);
    GDBWIRE_ASSERT(!mi_result->next);
    mi_result = mi_result->variant.result;

    /* Fast forward to the body */
    while (mi_result) {
        if (mi_result->kind == GDBWIRE_MI_LIST &&
            strcmp(mi_result->variable, "body") == 0) {
            found_body = 1;
            break;
        } else {
            mi_result = mi_result->next;
        }
    }

    GDBWIRE_ASSERT(found_body);
    GDBWIRE_ASSERT(!mi_result->next);
    mi_result = mi_result->variant.result;

    // In GDB version 9, the output of -break-insert changed
    // 
    // Look at commit b4be1b0648608a2578bbed39841c8ee411773edd
    // in GDB for details.
    // 
    // Prior to the change, we have mi2 -break-info output:
    //   ^done,bkpt={...,addr="<MULTIPLE>",...},{number="1.1",...},{number="1.2",...}
    // After the change, we have mi3 -break-info output:
    //   ^done,bkpt={...,addr="<MULTIPLE>",locations=[{number="1.1",...},{number="1.2",...}]}
    // 
    //
    // For both mi2 and mi3, this loop will iterate over all the
    // breakpoints, ie. bkpt={...}
    //
    // In mi2 mode, break_info_for_breakpoint will return a single
    // breakpoint and associated MULTIPLE breakpoints are found by looking
    // at subsequent breakpoints and attaching them in this loop.
    //
    // In mi3 mode, break_info_for_breakpoint will return a single
    // breakpoint with all MULTIPLE breakpoints already attached.
    while (mi_result) {
        struct gdbwire_mi_breakpoint *bkpt;
        GDBWIRE_ASSERT_GOTO(
            mi_result->kind == GDBWIRE_MI_TUPLE, result, cleanup);

        /**
         * GDB emits non-compliant MI when sending breakpoint information.
         *   https://sourceware.org/bugzilla/show_bug.cgi?id=9659
         * In particular, instead of saying
         *   bkpt={...},bkpt={...}
         * it puts out,
         *   bkpt={...},{...}
         * skipping the additional bkpt for subsequent breakpoints. I've seen
         * this output for multiple location breakpoints as the bug points to.
         *
         * For this reason, only check bkpt for the first breakpoint and
         * assume it is true for the remaining.
         */
        if (mi_result->variable) {
            GDBWIRE_ASSERT_GOTO(
                strcmp(mi_result->variable, "bkpt") == 0, result, cleanup);
        }

        result = break_info_for_breakpoint(mi_result->variant.result, &bkpt);
        if (result != GDBWIRE_OK) {
            goto cleanup;
        }

        if (bkpt->from_multi) {

            bkpt->multi_breakpoint = cur_bkpt;

            /* Append breakpoint to the multiple location breakpoints */
            if (cur_bkpt->multi_breakpoints) {
                struct gdbwire_mi_breakpoint *multi =
                    cur_bkpt->multi_breakpoints;
                while (multi->next) {
                    multi = multi->next;
                }
                multi->next = bkpt;
            } else {
                cur_bkpt->multi_breakpoints = bkpt;
            }
        } else {
            /* Append breakpoint to the list of breakpoints */
            if (breakpoints) {
                cur_bkpt->next = bkpt;
                cur_bkpt = cur_bkpt->next;
            } else {
                breakpoints = cur_bkpt = bkpt;
            }
        }

        mi_result = mi_result->next;
    }

    mi_command = calloc(1, sizeof(struct gdbwire_mi_command));
    if (!mi_command) {
        result = GDBWIRE_NOMEM;
        goto cleanup;
    }
    mi_command->variant.break_info.breakpoints = breakpoints;

    *out = mi_command;

    return result;

cleanup:
    gdbwire_mi_breakpoints_free(breakpoints);
    return result;
}

/**
 * Handle the -stack-info-frame command.
 *
 * @param result_record
 * The mi result record that makes up the command output from gdb.
 *
 * @param out
 * The output command, null on error.
 *
 * @return
 * GDBWIRE_OK on success, otherwise failure and out is NULL.
 */
static enum gdbwire_result
stack_info_frame(
    struct gdbwire_mi_result_record *result_record,
    struct gdbwire_mi_command **out)
{
    struct gdbwire_mi_stack_frame *frame;
    struct gdbwire_mi_result *mi_result;
    struct gdbwire_mi_command *mi_command = 0;

    char *level = 0, *address = 0;
    char *func = 0, *file = 0, *fullname = 0, *line = 0, *from = 0;

    *out = 0;

    GDBWIRE_ASSERT(result_record->result_class == GDBWIRE_MI_DONE);
    GDBWIRE_ASSERT(result_record->result);

    mi_result = result_record->result;

    GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_TUPLE);
    GDBWIRE_ASSERT(strcmp(mi_result->variable, "frame") == 0);
    GDBWIRE_ASSERT(mi_result->variant.result);
    GDBWIRE_ASSERT(!mi_result->next);
    mi_result = mi_result->variant.result;

    while (mi_result) {
        if (mi_result->kind == GDBWIRE_MI_CSTRING) {
            if (strcmp(mi_result->variable, "level") == 0) {
                level = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "addr") == 0) {
                address = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "func") == 0) {
                func = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "file") == 0) {
                file = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "fullname") == 0) {
                fullname = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "line") == 0) {
                line = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "from") == 0) {
                from = mi_result->variant.cstring;
            }
        }

        mi_result = mi_result->next;
    }

    GDBWIRE_ASSERT(level && address);

    if (strcmp(address, "<unavailable>") == 0) {
        address = 0;
    }

    frame = calloc(1, sizeof(struct gdbwire_mi_stack_frame));
    if (!frame) {
        return GDBWIRE_NOMEM;
    }

    frame->level = atoi(level);
    frame->address = (address)?gdbwire_strdup(address):0;
    frame->func = (func)?gdbwire_strdup(func):0;
    frame->file = (file)?gdbwire_strdup(file):0;
    frame->fullname = (fullname)?gdbwire_strdup(fullname):0;
    frame->line = (line)?atoi(line):0;
    frame->from = (from)?gdbwire_strdup(from):0;

    /* Handle the out of memory situation */
    if ((address && !frame->address) ||
        (func && !frame->func) ||
        (file && !frame->file) ||
        (fullname && !frame->fullname) ||
        (from && !frame->from)) {
        gdbwire_mi_stack_frame_free(frame);
        return GDBWIRE_NOMEM;
    }

    mi_command = calloc(1, sizeof(struct gdbwire_mi_command));
    if (!mi_command) {
        gdbwire_mi_stack_frame_free(frame);
        return GDBWIRE_NOMEM;
    }
    mi_command->kind = GDBWIRE_MI_STACK_INFO_FRAME;
    mi_command->variant.stack_info_frame.frame = frame;

    *out = mi_command;

    return GDBWIRE_OK;
}

/**
 * Handle the -file-list-exec-source-file command.
 *
 * @param result_record
 * The mi result record that makes up the command output from gdb.
 *
 * @param out
 * The output command, null on error.
 *
 * @return
 * GDBWIRE_OK on success, otherwise failure and out is NULL.
 */
static enum gdbwire_result
file_list_exec_source_file(
    struct gdbwire_mi_result_record *result_record,
    struct gdbwire_mi_command **out)
{
    struct gdbwire_mi_result *mi_result;
    struct gdbwire_mi_command *mi_command = 0;

    char *line = 0, *file = 0, *fullname = 0, *macro_info = 0;

    *out = 0;

    GDBWIRE_ASSERT(result_record->result_class == GDBWIRE_MI_DONE);
    GDBWIRE_ASSERT(result_record->result);

    mi_result = result_record->result;

    while (mi_result) {
        if (mi_result->kind == GDBWIRE_MI_CSTRING) {
            if (strcmp(mi_result->variable, "line") == 0) {
                line = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "file") == 0) {
                file = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "fullname") == 0) {
                fullname = mi_result->variant.cstring;
            } else if (strcmp(mi_result->variable, "macro-info") == 0) {
                macro_info = mi_result->variant.cstring;
                GDBWIRE_ASSERT(strlen(macro_info) == 1);
                GDBWIRE_ASSERT(macro_info[0] == '0' || macro_info[0] == '1');
            }
        }

        mi_result = mi_result->next;
    }

    GDBWIRE_ASSERT(line && file);

    mi_command = calloc(1, sizeof(struct gdbwire_mi_command));
    if (!mi_command) {
        return GDBWIRE_NOMEM;
    }

    mi_command->kind = GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILE;
    mi_command->variant.file_list_exec_source_file.line = atoi(line);
    mi_command->variant.file_list_exec_source_file.file = gdbwire_strdup(file);
    if (!mi_command->variant.file_list_exec_source_file.file) {
        gdbwire_mi_command_free(mi_command);
        return GDBWIRE_NOMEM;
    }
    mi_command->variant.file_list_exec_source_file.fullname =
        (fullname)?gdbwire_strdup(fullname):0;
    if (fullname &&
        !mi_command->variant.file_list_exec_source_file.fullname) {
        gdbwire_mi_command_free(mi_command);
        return GDBWIRE_NOMEM;
    }
    mi_command->variant.file_list_exec_source_file.macro_info_exists =
        macro_info != 0;
    if (macro_info) {
        mi_command->variant.file_list_exec_source_file.macro_info =
            atoi(macro_info);
    }

    *out = mi_command;

    return GDBWIRE_OK;
}

/**
 * Handle the -file-list-exec-source-files command.
 *
 * @param result_record
 * The mi result record that makes up the command output from gdb.
 *
 * @param out
 * The output command, null on error.
 *
 * @return
 * GDBWIRE_OK on success, otherwise failure and out is NULL.
 */
static enum gdbwire_result
file_list_exec_source_files(
    struct gdbwire_mi_result_record *result_record,
    struct gdbwire_mi_command **out)
{
    enum gdbwire_result result = GDBWIRE_OK;
    struct gdbwire_mi_result *mi_result;
    struct gdbwire_mi_source_file *files = 0, *cur_node, *new_node;

    GDBWIRE_ASSERT(result_record->result_class == GDBWIRE_MI_DONE);
    GDBWIRE_ASSERT(result_record->result);

    mi_result = result_record->result;

    GDBWIRE_ASSERT(mi_result->kind == GDBWIRE_MI_LIST);
    GDBWIRE_ASSERT(strcmp(mi_result->variable, "files") == 0);
    GDBWIRE_ASSERT(!mi_result->next);

    mi_result = mi_result->variant.result;

    while (mi_result) {
        struct gdbwire_mi_result *tuple;
        char *file = 0, *fullname = 0;
        enum gdbwire_mi_debug_fully_read_kind debug_fully_read =
            GDBWIRE_MI_DEBUG_FULLY_READ_UNKNOWN;
        GDBWIRE_ASSERT_GOTO(mi_result->kind == GDBWIRE_MI_TUPLE, result, err);
        tuple = mi_result->variant.result;

        while (tuple) {
            /* file field */
            GDBWIRE_ASSERT_GOTO(tuple->kind == GDBWIRE_MI_CSTRING, result, err);

            if (strcmp(tuple->variable, "file") == 0) {
                file = tuple->variant.cstring;
            } else if (strcmp(tuple->variable, "fullname") == 0) {
                fullname = tuple->variant.cstring;
            } else if (strcmp(tuple->variable, "debug-fully-read") == 0) {
                if (strcmp(tuple->variant.cstring, "false") == 0) {
                    debug_fully_read =
                        GDBWIRE_MI_DEBUG_FULLY_READ_FALSE;
                } else if (strcmp(tuple->variant.cstring, "true") == 0) {
                    debug_fully_read =
                        GDBWIRE_MI_DEBUG_FULLY_READ_TRUE;
                }
            }

            tuple = tuple->next;
        }

        // file is required, but fullname and debug_fully_read is not
        GDBWIRE_ASSERT_GOTO(file, result, err);

        /* Create the new */
        new_node = calloc(1, sizeof(struct gdbwire_mi_source_file));
        GDBWIRE_ASSERT_GOTO(new_node, result, err);

        new_node->file = gdbwire_strdup(file);
        new_node->fullname = (fullname)?gdbwire_strdup(fullname):0;
        new_node->debug_fully_read = debug_fully_read;
        new_node->next = 0;

        /* Append the node to the list */
        if (files) {
            cur_node->next = new_node;
            cur_node = cur_node->next;
        } else {
            files = cur_node = new_node;
        }

        GDBWIRE_ASSERT_GOTO(new_node->file && (new_node->fullname || !fullname),
            result, err);

        mi_result = mi_result->next;
    }

    *out = calloc(1, sizeof(struct gdbwire_mi_command));
    GDBWIRE_ASSERT_GOTO(*out, result, err);
    (*out)->kind = GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILES;
    (*out)->variant.file_list_exec_source_files.files = files;

    return result;

err:
    gdbwire_mi_source_files_free(files); 

    return result;
}

enum gdbwire_result
gdbwire_get_mi_command(enum gdbwire_mi_command_kind kind,
        struct gdbwire_mi_result_record *result_record,
        struct gdbwire_mi_command **out)
{
    enum gdbwire_result result = GDBWIRE_OK;

    GDBWIRE_ASSERT(result_record);
    GDBWIRE_ASSERT(out);

    *out = 0;

    switch (kind) {
        case GDBWIRE_MI_BREAK_INFO:
            result = break_info(result_record, out);
            break;
        case GDBWIRE_MI_STACK_INFO_FRAME:
            result = stack_info_frame(result_record, out);
            break;
        case GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILE:
            result = file_list_exec_source_file(result_record, out);
            break;
        case GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILES:
            result = file_list_exec_source_files(result_record, out);
            break;
    }
    
    return result;
}

void gdbwire_mi_command_free(struct gdbwire_mi_command *mi_command)
{
    if (mi_command) {
        switch (mi_command->kind) {
            case GDBWIRE_MI_BREAK_INFO:
                gdbwire_mi_breakpoints_free(
                    mi_command->variant.break_info.breakpoints);
                break;
            case GDBWIRE_MI_STACK_INFO_FRAME:
                gdbwire_mi_stack_frame_free(
                    mi_command->variant.stack_info_frame.frame);
                break;
            case GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILE:
                free(mi_command->variant.file_list_exec_source_file.file);
                free(mi_command->variant.file_list_exec_source_file.fullname);
                break;
            case GDBWIRE_MI_FILE_LIST_EXEC_SOURCE_FILES:
                gdbwire_mi_source_files_free(
                    mi_command->variant.file_list_exec_source_files.files);
                break;
        }

        free(mi_command);
    }
}
/***** End of gdbwire_mi_command.c *******************************************/
/***** Begin file gdbwire_mi_lexer.c *****************************************/


#define  YY_INT_ALIGNED short int

/* A lexical scanner generated by flex */

#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 6
#define YY_FLEX_SUBMINOR_VERSION 4
#if YY_FLEX_SUBMINOR_VERSION > 0
#define FLEX_BETA
#endif

#ifdef yy_create_buffer
#define gdbwire_mi__create_buffer_ALREADY_DEFINED
#else
#define yy_create_buffer gdbwire_mi__create_buffer
#endif

#ifdef yy_delete_buffer
#define gdbwire_mi__delete_buffer_ALREADY_DEFINED
#else
#define yy_delete_buffer gdbwire_mi__delete_buffer
#endif

#ifdef yy_scan_buffer
#define gdbwire_mi__scan_buffer_ALREADY_DEFINED
#else
#define yy_scan_buffer gdbwire_mi__scan_buffer
#endif

#ifdef yy_scan_string
#define gdbwire_mi__scan_string_ALREADY_DEFINED
#else
#define yy_scan_string gdbwire_mi__scan_string
#endif

#ifdef yy_scan_bytes
#define gdbwire_mi__scan_bytes_ALREADY_DEFINED
#else
#define yy_scan_bytes gdbwire_mi__scan_bytes
#endif

#ifdef yy_init_buffer
#define gdbwire_mi__init_buffer_ALREADY_DEFINED
#else
#define yy_init_buffer gdbwire_mi__init_buffer
#endif

#ifdef yy_flush_buffer
#define gdbwire_mi__flush_buffer_ALREADY_DEFINED
#else
#define yy_flush_buffer gdbwire_mi__flush_buffer
#endif

#ifdef yy_load_buffer_state
#define gdbwire_mi__load_buffer_state_ALREADY_DEFINED
#else
#define yy_load_buffer_state gdbwire_mi__load_buffer_state
#endif

#ifdef yy_switch_to_buffer
#define gdbwire_mi__switch_to_buffer_ALREADY_DEFINED
#else
#define yy_switch_to_buffer gdbwire_mi__switch_to_buffer
#endif

#ifdef yypush_buffer_state
#define gdbwire_mi_push_buffer_state_ALREADY_DEFINED
#else
#define yypush_buffer_state gdbwire_mi_push_buffer_state
#endif

#ifdef yypop_buffer_state
#define gdbwire_mi_pop_buffer_state_ALREADY_DEFINED
#else
#define yypop_buffer_state gdbwire_mi_pop_buffer_state
#endif

#ifdef yyensure_buffer_stack
#define gdbwire_mi_ensure_buffer_stack_ALREADY_DEFINED
#else
#define yyensure_buffer_stack gdbwire_mi_ensure_buffer_stack
#endif

#ifdef yylex
#define gdbwire_mi_lex_ALREADY_DEFINED
#else
#define yylex gdbwire_mi_lex
#endif

#ifdef yyrestart
#define gdbwire_mi_restart_ALREADY_DEFINED
#else
#define yyrestart gdbwire_mi_restart
#endif

#ifdef yylex_init
#define gdbwire_mi_lex_init_ALREADY_DEFINED
#else
#define yylex_init gdbwire_mi_lex_init
#endif

#ifdef yylex_init_extra
#define gdbwire_mi_lex_init_extra_ALREADY_DEFINED
#else
#define yylex_init_extra gdbwire_mi_lex_init_extra
#endif

#ifdef yylex_destroy
#define gdbwire_mi_lex_destroy_ALREADY_DEFINED
#else
#define yylex_destroy gdbwire_mi_lex_destroy
#endif

#ifdef yyget_debug
#define gdbwire_mi_get_debug_ALREADY_DEFINED
#else
#define yyget_debug gdbwire_mi_get_debug
#endif

#ifdef yyset_debug
#define gdbwire_mi_set_debug_ALREADY_DEFINED
#else
#define yyset_debug gdbwire_mi_set_debug
#endif

#ifdef yyget_extra
#define gdbwire_mi_get_extra_ALREADY_DEFINED
#else
#define yyget_extra gdbwire_mi_get_extra
#endif

#ifdef yyset_extra
#define gdbwire_mi_set_extra_ALREADY_DEFINED
#else
#define yyset_extra gdbwire_mi_set_extra
#endif

#ifdef yyget_in
#define gdbwire_mi_get_in_ALREADY_DEFINED
#else
#define yyget_in gdbwire_mi_get_in
#endif

#ifdef yyset_in
#define gdbwire_mi_set_in_ALREADY_DEFINED
#else
#define yyset_in gdbwire_mi_set_in
#endif

#ifdef yyget_out
#define gdbwire_mi_get_out_ALREADY_DEFINED
#else
#define yyget_out gdbwire_mi_get_out
#endif

#ifdef yyset_out
#define gdbwire_mi_set_out_ALREADY_DEFINED
#else
#define yyset_out gdbwire_mi_set_out
#endif

#ifdef yyget_leng
#define gdbwire_mi_get_leng_ALREADY_DEFINED
#else
#define yyget_leng gdbwire_mi_get_leng
#endif

#ifdef yyget_text
#define gdbwire_mi_get_text_ALREADY_DEFINED
#else
#define yyget_text gdbwire_mi_get_text
#endif

#ifdef yyget_lineno
#define gdbwire_mi_get_lineno_ALREADY_DEFINED
#else
#define yyget_lineno gdbwire_mi_get_lineno
#endif

#ifdef yyset_lineno
#define gdbwire_mi_set_lineno_ALREADY_DEFINED
#else
#define yyset_lineno gdbwire_mi_set_lineno
#endif

#ifdef yyget_column
#define gdbwire_mi_get_column_ALREADY_DEFINED
#else
#define yyget_column gdbwire_mi_get_column
#endif

#ifdef yyset_column
#define gdbwire_mi_set_column_ALREADY_DEFINED
#else
#define yyset_column gdbwire_mi_set_column
#endif

#ifdef yywrap
#define gdbwire_mi_wrap_ALREADY_DEFINED
#else
#define yywrap gdbwire_mi_wrap
#endif

#ifdef yyalloc
#define gdbwire_mi_alloc_ALREADY_DEFINED
#else
#define yyalloc gdbwire_mi_alloc
#endif

#ifdef yyrealloc
#define gdbwire_mi_realloc_ALREADY_DEFINED
#else
#define yyrealloc gdbwire_mi_realloc
#endif

#ifdef yyfree
#define gdbwire_mi_free_ALREADY_DEFINED
#else
#define yyfree gdbwire_mi_free
#endif

/* First, we deal with  platform-specific or compiler-specific issues. */

/* begin standard C headers. */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* end standard C headers. */

/* flex integer type definitions */

#ifndef FLEXINT_H
#define FLEXINT_H

/* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */

#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
 * if you want the limit (max/min) macros for int types. 
 */
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS 1
#endif

#include <inttypes.h>
typedef int8_t flex_int8_t;
typedef uint8_t flex_uint8_t;
typedef int16_t flex_int16_t;
typedef uint16_t flex_uint16_t;
typedef int32_t flex_int32_t;
typedef uint32_t flex_uint32_t;
#else
typedef signed char flex_int8_t;
typedef short int flex_int16_t;
typedef int flex_int32_t;
typedef unsigned char flex_uint8_t; 
typedef unsigned short int flex_uint16_t;
typedef unsigned int flex_uint32_t;

/* Limits of integral types. */
#ifndef INT8_MIN
#define INT8_MIN               (-128)
#endif
#ifndef INT16_MIN
#define INT16_MIN              (-32767-1)
#endif
#ifndef INT32_MIN
#define INT32_MIN              (-2147483647-1)
#endif
#ifndef INT8_MAX
#define INT8_MAX               (127)
#endif
#ifndef INT16_MAX
#define INT16_MAX              (32767)
#endif
#ifndef INT32_MAX
#define INT32_MAX              (2147483647)
#endif
#ifndef UINT8_MAX
#define UINT8_MAX              (255U)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX             (65535U)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX             (4294967295U)
#endif

#ifndef SIZE_MAX
#define SIZE_MAX               (~(size_t)0)
#endif

#endif /* ! C99 */

#endif /* ! FLEXINT_H */

/* begin standard C++ headers. */

/* TODO: this is always defined, so inline it */
#define yyconst const

#if defined(__GNUC__) && __GNUC__ >= 3
#define yynoreturn __attribute__((__noreturn__))
#else
#define yynoreturn
#endif

/* Returned upon end-of-file. */
#define YY_NULL 0

/* Promotes a possibly negative, possibly signed char to an
 *   integer in range [0..255] for use as an array index.
 */
#define YY_SC_TO_UI(c) ((YY_CHAR) (c))

/* An opaque pointer. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

/* For convenience, these vars (plus the bison vars far below)
   are macros in the reentrant scanner. */
#define yyin yyg->yyin_r
#define yyout yyg->yyout_r
#define yyextra yyg->yyextra_r
#define yyleng yyg->yyleng_r
#define yytext yyg->yytext_r
#define yylineno (YY_CURRENT_BUFFER_LVALUE->yy_bs_lineno)
#define yycolumn (YY_CURRENT_BUFFER_LVALUE->yy_bs_column)
#define yy_flex_debug yyg->yy_flex_debug_r

/* Enter a start condition.  This macro really ought to take a parameter,
 * but we do it the disgusting crufty way forced on us by the ()-less
 * definition of BEGIN.
 */
#define BEGIN yyg->yy_start = 1 + 2 *
/* Translate the current start state into a value that can be later handed
 * to BEGIN to return to the state.  The YYSTATE alias is for lex
 * compatibility.
 */
#define YY_START ((yyg->yy_start - 1) / 2)
#define YYSTATE YY_START
/* Action number for EOF rule of a given start state. */
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)
/* Special action meaning "start processing a new file". */
#define YY_NEW_FILE yyrestart( yyin , yyscanner )
#define YY_END_OF_BUFFER_CHAR 0

/* Size of default input buffer. */
#ifndef YY_BUF_SIZE
#ifdef __ia64__
/* On IA-64, the buffer size is 16k, not 8k.
 * Moreover, YY_BUF_SIZE is 2*YY_READ_BUF_SIZE in the general case.
 * Ditto for the __ia64__ case accordingly.
 */
#define YY_BUF_SIZE 32768
#else
#define YY_BUF_SIZE 16384
#endif /* __ia64__ */
#endif

/* The state buf must be large enough to hold one state per character in the main buffer.
 */
#define YY_STATE_BUF_SIZE   ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif

#ifndef YY_TYPEDEF_YY_SIZE_T
#define YY_TYPEDEF_YY_SIZE_T
typedef size_t yy_size_t;
#endif

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2
    
    #define YY_LESS_LINENO(n)
    #define YY_LINENO_REWIND_TO(ptr)
    
/* Return all but the first "n" matched characters back to the input stream. */
#define yyless(n) \
	do \
		{ \
		/* Undo effects of setting up yytext. */ \
        int yyless_macro_arg = (n); \
        YY_LESS_LINENO(yyless_macro_arg);\
		*yy_cp = yyg->yy_hold_char; \
		YY_RESTORE_YY_MORE_OFFSET \
		yyg->yy_c_buf_p = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
		} \
	while ( 0 )
#define unput(c) yyunput( c, yyg->yytext_ptr , yyscanner )

#ifndef YY_STRUCT_YY_BUFFER_STATE
#define YY_STRUCT_YY_BUFFER_STATE
struct yy_buffer_state
	{
	FILE *yy_input_file;

	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	 * characters.
	 */
	int yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	 * characters.
	 */
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	 * and can realloc() it to grow it, and should free() it to
	 * delete it.
	 */
	int yy_is_our_buffer;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	 * If so, '^' rules will be active on the next match, otherwise
	 * not.
	 */
	int yy_at_bol;

    int yy_bs_lineno; /**< The line count. */
    int yy_bs_column; /**< The column count. */

	/* Whether to try to fill the input buffer when we reach the
	 * end of it.
	 */
	int yy_fill_buffer;

	int yy_buffer_status;

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
	/* When an EOF's been seen but there's still some text to process
	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
	 * shouldn't try reading from the input source any more.  We might
	 * still have a bunch of tokens to match, though, because of
	 * possible backing-up.
	 *
	 * When we actually see the EOF, we change the status to "new"
	 * (via yyrestart()), so that the user can continue scanning by
	 * just pointing yyin at a new input file.
	 */
#define YY_BUFFER_EOF_PENDING 2

	};
#endif /* !YY_STRUCT_YY_BUFFER_STATE */

/* We provide macros for accessing buffer states in case in the
 * future we want to put the buffer states in a more general
 * "scanner state".
 *
 * Returns the top of the stack, or NULL.
 */
#define YY_CURRENT_BUFFER ( yyg->yy_buffer_stack \
                          ? yyg->yy_buffer_stack[yyg->yy_buffer_stack_top] \
                          : NULL)
/* Same as previous macro, but useful when we know that the buffer stack is not
 * NULL or when we need an lvalue. For internal use only.
 */
#define YY_CURRENT_BUFFER_LVALUE yyg->yy_buffer_stack[yyg->yy_buffer_stack_top]

void yyrestart ( FILE *input_file , yyscan_t yyscanner );
void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer , yyscan_t yyscanner );
YY_BUFFER_STATE yy_create_buffer ( FILE *file, int size , yyscan_t yyscanner );
void yy_delete_buffer ( YY_BUFFER_STATE b , yyscan_t yyscanner );
void yy_flush_buffer ( YY_BUFFER_STATE b , yyscan_t yyscanner );
void yypush_buffer_state ( YY_BUFFER_STATE new_buffer , yyscan_t yyscanner );
void yypop_buffer_state ( yyscan_t yyscanner );

static void yyensure_buffer_stack ( yyscan_t yyscanner );
static void yy_load_buffer_state ( yyscan_t yyscanner );
static void yy_init_buffer ( YY_BUFFER_STATE b, FILE *file , yyscan_t yyscanner );
#define YY_FLUSH_BUFFER yy_flush_buffer( YY_CURRENT_BUFFER , yyscanner)

YY_BUFFER_STATE yy_scan_buffer ( char *base, yy_size_t size , yyscan_t yyscanner );
YY_BUFFER_STATE yy_scan_string ( const char *yy_str , yyscan_t yyscanner );
YY_BUFFER_STATE yy_scan_bytes ( const char *bytes, int len , yyscan_t yyscanner );

void *yyalloc ( yy_size_t , yyscan_t yyscanner );
void *yyrealloc ( void *, yy_size_t , yyscan_t yyscanner );
void yyfree ( void * , yyscan_t yyscanner );

#define yy_new_buffer yy_create_buffer
#define yy_set_interactive(is_interactive) \
	{ \
	if ( ! YY_CURRENT_BUFFER ){ \
        yyensure_buffer_stack (yyscanner); \
		YY_CURRENT_BUFFER_LVALUE =    \
            yy_create_buffer( yyin, YY_BUF_SIZE , yyscanner); \
	} \
	YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive; \
	}
#define yy_set_bol(at_bol) \
	{ \
	if ( ! YY_CURRENT_BUFFER ){\
        yyensure_buffer_stack (yyscanner); \
		YY_CURRENT_BUFFER_LVALUE =    \
            yy_create_buffer( yyin, YY_BUF_SIZE , yyscanner); \
	} \
	YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
	}
#define YY_AT_BOL() (YY_CURRENT_BUFFER_LVALUE->yy_at_bol)

/* Begin user sect3 */

#define gdbwire_mi_wrap(yyscanner) (/*CONSTCOND*/1)
#define YY_SKIP_YYWRAP
typedef flex_uint8_t YY_CHAR;

typedef int yy_state_type;

#define yytext_ptr yytext_r

static yy_state_type yy_get_previous_state ( yyscan_t yyscanner );
static yy_state_type yy_try_NUL_trans ( yy_state_type current_state  , yyscan_t yyscanner);
static int yy_get_next_buffer ( yyscan_t yyscanner );
static void yynoreturn yy_fatal_error ( const char* msg , yyscan_t yyscanner );

/* Done after the current pattern has been matched and before the
 * corresponding action - sets up yytext.
 */
#define YY_DO_BEFORE_ACTION \
	yyg->yytext_ptr = yy_bp; \
	yyleng = (int) (yy_cp - yy_bp); \
	yyg->yy_hold_char = *yy_cp; \
	*yy_cp = '\0'; \
	yyg->yy_c_buf_p = yy_cp;
#define YY_NUM_RULES 23
#define YY_END_OF_BUFFER 24
/* This struct is not used in this scanner,
   but its presence is necessary. */
struct yy_trans_info
	{
	flex_int32_t yy_verify;
	flex_int32_t yy_nxt;
	};
static const flex_int16_t yy_accept[33] =
    {   0,
        0,    0,   24,   21,   19,   15,   17,   21,    8,   13,
       14,    4,    3,    2,   18,    5,    7,   20,    9,   10,
        1,   11,   12,    6,   16,    0,   22,    0,   18,   20,
       20,    0
    } ;

static const YY_CHAR yy_ec[256] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
        2,    2,    4,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    2,    1,    5,    1,    1,    1,    6,    1,    7,
        8,    9,   10,   11,   12,    1,    1,   13,   13,   13,
       13,   13,   13,   13,   13,   13,   13,    1,    1,    1,
       14,    1,    1,   15,   16,   16,   16,   16,   16,   16,
       16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
       16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
       17,   18,   19,   20,   16,    1,   16,   16,   16,   16,

       16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
       16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
       16,   16,   21,    1,   22,   23,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,

        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1
    } ;

static const YY_CHAR yy_meta[24] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1
    } ;

static const flex_int16_t yy_base[34] =
    {   0,
        0,    0,   42,   43,   43,   43,   38,   19,   43,   43,
       43,   43,   43,   43,   26,   43,   43,   13,   43,   43,
       43,   43,   43,   43,   43,   22,   43,   35,   22,   18,
       20,   43,   27
    } ;

static const flex_int16_t yy_def[34] =
    {   0,
       32,    1,   32,   32,   32,   32,   32,   33,   32,   32,
       32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
       32,   32,   32,   32,   32,   33,   32,   33,   32,   32,
       32,    0,   32
    } ;

static const flex_int16_t yy_nxt[67] =
    {   0,
        4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
       14,    4,   15,   16,   17,   18,   19,    4,   20,   21,
       22,   23,   24,   27,   30,   30,   27,   26,   31,   30,
       30,   30,   30,   30,   29,   31,   28,   32,   29,   28,
       25,   32,    3,   32,   32,   32,   32,   32,   32,   32,
       32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
       32,   32,   32,   32,   32,   32
    } ;

static const flex_int16_t yy_chk[67] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    8,   18,   18,   26,   33,   18,   30,
       30,   31,   31,   30,   29,   31,    8,   28,   15,   26,
        7,    3,   32,   32,   32,   32,   32,   32,   32,   32,
       32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
       32,   32,   32,   32,   32,   32
    } ;

/* The intent behind this definition is that it'll catch
 * any uses of REJECT which flex missed.
 */
#define REJECT reject_used_but_not_detected
#define yymore() yymore_used_but_not_detected
#define YY_MORE_ADJ 0
#define YY_RESTORE_YY_MORE_OFFSET
#define YY_NO_INPUT 1
/* Avoids the use of fileno, which is POSIX and not compatible with c11 */

/* flex 2.6.0 produces a sign-compare warning */
#pragma GCC diagnostic ignored "-Wsign-compare"

#include <stdio.h>
/* #include "gdbwire_mi_grammar.h" */
/* #include "gdbwire_mi_pt.h" */

/**
 * This macro sets the beginning and ending column position of each
 * token in the pure lexer. No global state is used.
 *
 * The parser can then use this position to determine the location
 * of any token it desires.
 *
 * Currently only the column is stored as the parser only uses
 * the lexer on a line at a time. Currently, the caller of the
 * lexer sets the column position back to 1 each time a new
 * line is set to be parsed in the lexer.
 */
#define YY_USER_ACTION \
    { \
    struct gdbwire_mi_position pos = { yycolumn, yycolumn+yyleng-1 }; \
    yyextra = pos; \
    yycolumn += yyleng; \
    }

#define INITIAL 0

#ifndef YY_NO_UNISTD_H
/* Special case for "unistd.h", since it is non-ANSI. We include it way
 * down here because we want the user's section 1 to have been scanned first.
 * The user has a chance to override it with an option.
 */
#include <unistd.h>
#endif

#define YY_EXTRA_TYPE struct gdbwire_mi_position

/* Holds the entire state of the reentrant scanner. */
struct yyguts_t
    {

    /* User-defined. Not touched by flex. */
    YY_EXTRA_TYPE yyextra_r;

    /* The rest are the same as the globals declared in the non-reentrant scanner. */
    FILE *yyin_r, *yyout_r;
    size_t yy_buffer_stack_top; /**< index of top of stack. */
    size_t yy_buffer_stack_max; /**< capacity of stack. */
    YY_BUFFER_STATE * yy_buffer_stack; /**< Stack as an array. */
    char yy_hold_char;
    int yy_n_chars;
    int yyleng_r;
    char *yy_c_buf_p;
    int yy_init;
    int yy_start;
    int yy_did_buffer_switch_on_eof;
    int yy_start_stack_ptr;
    int yy_start_stack_depth;
    int *yy_start_stack;
    yy_state_type yy_last_accepting_state;
    char* yy_last_accepting_cpos;

    int yylineno_r;
    int yy_flex_debug_r;

    char *yytext_r;
    int yy_more_flag;
    int yy_more_len;

    }; /* end struct yyguts_t */

static int yy_init_globals ( yyscan_t yyscanner );

int yylex_init (yyscan_t* scanner);

int yylex_init_extra ( YY_EXTRA_TYPE user_defined, yyscan_t* scanner);

/* Accessor methods to globals.
   These are made visible to non-reentrant scanners for convenience. */

int yylex_destroy ( yyscan_t yyscanner );

int yyget_debug ( yyscan_t yyscanner );

void yyset_debug ( int debug_flag , yyscan_t yyscanner );

YY_EXTRA_TYPE yyget_extra ( yyscan_t yyscanner );

void yyset_extra ( YY_EXTRA_TYPE user_defined , yyscan_t yyscanner );

FILE *yyget_in ( yyscan_t yyscanner );

void yyset_in  ( FILE * _in_str , yyscan_t yyscanner );

FILE *yyget_out ( yyscan_t yyscanner );

void yyset_out  ( FILE * _out_str , yyscan_t yyscanner );

			int yyget_leng ( yyscan_t yyscanner );

char *yyget_text ( yyscan_t yyscanner );

int yyget_lineno ( yyscan_t yyscanner );

void yyset_lineno ( int _line_number , yyscan_t yyscanner );

int yyget_column  ( yyscan_t yyscanner );

void yyset_column ( int _column_no , yyscan_t yyscanner );

/* Macros after this point can all be overridden by user definitions in
 * section 1.
 */

#ifndef YY_SKIP_YYWRAP
#ifdef __cplusplus
extern "C" int yywrap ( yyscan_t yyscanner );
#else
extern int yywrap ( yyscan_t yyscanner );
#endif
#endif

#ifndef YY_NO_UNPUT
    
#endif

#ifndef yytext_ptr
static void yy_flex_strncpy ( char *, const char *, int , yyscan_t yyscanner);
#endif

#ifdef YY_NEED_STRLEN
static int yy_flex_strlen ( const char * , yyscan_t yyscanner);
#endif

#ifndef YY_NO_INPUT
#ifdef __cplusplus
static int yyinput ( yyscan_t yyscanner );
#else
static int input ( yyscan_t yyscanner );
#endif

#endif

/* Amount of stuff to slurp up with each read. */
#ifndef YY_READ_BUF_SIZE
#ifdef __ia64__
/* On IA-64, the buffer size is 16k, not 8k */
#define YY_READ_BUF_SIZE 16384
#else
#define YY_READ_BUF_SIZE 8192
#endif /* __ia64__ */
#endif

/* Copy whatever the last rule matched to the standard output. */
#ifndef ECHO
/* This used to be an fputs(), but since the string might contain NUL's,
 * we now use fwrite().
 */
#define ECHO do { if (fwrite( yytext, (size_t) yyleng, 1, yyout )) {} } while (0)
#endif

/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
 * is returned in "result".
 */
#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \
		{ \
		int c = '*'; \
		int n; \
		for ( n = 0; n < max_size && \
			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
			buf[n] = (char) c; \
		if ( c == '\n' ) \
			buf[n++] = (char) c; \
		if ( c == EOF && ferror( yyin ) ) \
			YY_FATAL_ERROR( "input in flex scanner failed" ); \
		result = n; \
		} \
	else \
		{ \
		errno=0; \
		while ( (result = (int) fread(buf, 1, (yy_size_t) max_size, yyin)) == 0 && ferror(yyin)) \
			{ \
			if( errno != EINTR) \
				{ \
				YY_FATAL_ERROR( "input in flex scanner failed" ); \
				break; \
				} \
			errno=0; \
			clearerr(yyin); \
			} \
		}\
\

#endif

/* No semi-colon after return; correct usage is to write "yyterminate();" -
 * we don't want an extra ';' after the "return" because that will cause
 * some compilers to complain about unreachable statements.
 */
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif

/* Number of entries by which start-condition stack grows. */
#ifndef YY_START_STACK_INCR
#define YY_START_STACK_INCR 25
#endif

/* Report a fatal error. */
#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) yy_fatal_error( msg , yyscanner)
#endif

/* end tables serialization structures and prototypes */

/* Default declaration of generated scanner - a define so the user can
 * easily add parameters.
 */
#ifndef YY_DECL
#define YY_DECL_IS_OURS 1

extern int yylex (yyscan_t yyscanner);

#define YY_DECL int yylex (yyscan_t yyscanner)
#endif /* !YY_DECL */

/* Code executed at the beginning of each rule, after yytext and yyleng
 * have been set up.
 */
#ifndef YY_USER_ACTION
#define YY_USER_ACTION
#endif

/* Code executed at the end of each rule. */
#ifndef YY_BREAK
#define YY_BREAK /*LINTED*/break;
#endif

#define YY_RULE_SETUP \
	YY_USER_ACTION

/** The main scanner function which does all the work.
 */
YY_DECL
{
	yy_state_type yy_current_state;
	char *yy_cp, *yy_bp;
	int yy_act;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	if ( !yyg->yy_init )
		{
		yyg->yy_init = 1;

#ifdef YY_USER_INIT
		YY_USER_INIT;
#endif

		if ( ! yyg->yy_start )
			yyg->yy_start = 1;	/* first start state */

		if ( ! yyin )
			yyin = stdin;

		if ( ! yyout )
			yyout = stdout;

		if ( ! YY_CURRENT_BUFFER ) {
			yyensure_buffer_stack (yyscanner);
			YY_CURRENT_BUFFER_LVALUE =
				yy_create_buffer( yyin, YY_BUF_SIZE , yyscanner);
		}

		yy_load_buffer_state( yyscanner );
		}

	{



	while ( /*CONSTCOND*/1 )		/* loops until end-of-file is reached */
		{
		yy_cp = yyg->yy_c_buf_p;

		/* Support of yytext. */
		*yy_cp = yyg->yy_hold_char;

		/* yy_bp points to the position in yy_ch_buf of the start of
		 * the current run.
		 */
		yy_bp = yy_cp;

		yy_current_state = yyg->yy_start;
yy_match:
		do
			{
			YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
			if ( yy_accept[yy_current_state] )
				{
				yyg->yy_last_accepting_state = yy_current_state;
				yyg->yy_last_accepting_cpos = yy_cp;
				}
			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
				{
				yy_current_state = (int) yy_def[yy_current_state];
				if ( yy_current_state >= 33 )
					yy_c = yy_meta[yy_c];
				}
			yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
			++yy_cp;
			}
		while ( yy_current_state != 32 );
		yy_cp = yyg->yy_last_accepting_cpos;
		yy_current_state = yyg->yy_last_accepting_state;

yy_find_action:
		yy_act = yy_accept[yy_current_state];

		YY_DO_BEFORE_ACTION;

do_action:	/* This label is used only to access EOF actions. */

		switch ( yy_act )
	{ /* beginning of action switch */
			case 0: /* must back up */
			/* undo the effects of YY_DO_BEFORE_ACTION */
			*yy_cp = yyg->yy_hold_char;
			yy_cp = yyg->yy_last_accepting_cpos;
			yy_current_state = yyg->yy_last_accepting_state;
			goto yy_find_action;

case 1:
YY_RULE_SETUP
{ return CARROT; }
	YY_BREAK
case 2:
YY_RULE_SETUP
{ return COMMA; }
	YY_BREAK
case 3:
YY_RULE_SETUP
{ return ADD_OP; }
	YY_BREAK
case 4:
YY_RULE_SETUP
{ return MULT_OP; }
	YY_BREAK
case 5:
YY_RULE_SETUP
{ return EQUAL_SIGN; }
	YY_BREAK
case 6:
YY_RULE_SETUP
{ return TILDA; }
	YY_BREAK
case 7:
YY_RULE_SETUP
{ return AT_SYMBOL; }
	YY_BREAK
case 8:
YY_RULE_SETUP
{ return AMPERSAND; }
	YY_BREAK
case 9:
YY_RULE_SETUP
{ return OPEN_BRACKET; }
	YY_BREAK
case 10:
YY_RULE_SETUP
{ return CLOSED_BRACKET; }
	YY_BREAK
case 11:
YY_RULE_SETUP
{ return OPEN_BRACE; }
	YY_BREAK
case 12:
YY_RULE_SETUP
{ return CLOSED_BRACE; }
	YY_BREAK
case 13:
YY_RULE_SETUP
{ return OPEN_PAREN; }
	YY_BREAK
case 14:
YY_RULE_SETUP
{ return CLOSED_PAREN; }
	YY_BREAK
case 15:
/* rule 15 can match eol */
YY_RULE_SETUP
{ return NEWLINE; }
	YY_BREAK
case 16:
/* rule 16 can match eol */
YY_RULE_SETUP
{ return NEWLINE; }
	YY_BREAK
case 17:
YY_RULE_SETUP
{ return NEWLINE; }
	YY_BREAK
case 18:
YY_RULE_SETUP
{ return INTEGER_LITERAL; }
	YY_BREAK
case 19:
YY_RULE_SETUP
{}
	YY_BREAK
case 20:
YY_RULE_SETUP
{ return STRING_LITERAL;    }
	YY_BREAK
case 21:
YY_RULE_SETUP
{ return STRING_LITERAL;    }
	YY_BREAK
case 22:
/* rule 22 can match eol */
YY_RULE_SETUP
{ return CSTRING; }
	YY_BREAK
case 23:
YY_RULE_SETUP
ECHO;
	YY_BREAK
case YY_STATE_EOF(INITIAL):
	yyterminate();

	case YY_END_OF_BUFFER:
		{
		/* Amount of text matched not including the EOB char. */
		int yy_amount_of_matched_text = (int) (yy_cp - yyg->yytext_ptr) - 1;

		/* Undo the effects of YY_DO_BEFORE_ACTION. */
		*yy_cp = yyg->yy_hold_char;
		YY_RESTORE_YY_MORE_OFFSET

		if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW )
			{
			/* We're scanning a new file or input source.  It's
			 * possible that this happened because the user
			 * just pointed yyin at a new source and called
			 * yylex().  If so, then we have to assure
			 * consistency between YY_CURRENT_BUFFER and our
			 * globals.  Here is the right place to do so, because
			 * this is the first action (other than possibly a
			 * back-up) that will match for the new input source.
			 */
			yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
			YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
			}

		/* Note that here we test for yy_c_buf_p "<=" to the position
		 * of the first EOB in the buffer, since yy_c_buf_p will
		 * already have been incremented past the NUL character
		 * (since all states make transitions on EOB to the
		 * end-of-buffer state).  Contrast this with the test
		 * in input().
		 */
		if ( yyg->yy_c_buf_p <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
			{ /* This was really a NUL. */
			yy_state_type yy_next_state;

			yyg->yy_c_buf_p = yyg->yytext_ptr + yy_amount_of_matched_text;

			yy_current_state = yy_get_previous_state( yyscanner );

			/* Okay, we're now positioned to make the NUL
			 * transition.  We couldn't have
			 * yy_get_previous_state() go ahead and do it
			 * for us because it doesn't know how to deal
			 * with the possibility of jamming (and we don't
			 * want to build jamming into it because then it
			 * will run more slowly).
			 */

			yy_next_state = yy_try_NUL_trans( yy_current_state , yyscanner);

			yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;

			if ( yy_next_state )
				{
				/* Consume the NUL. */
				yy_cp = ++yyg->yy_c_buf_p;
				yy_current_state = yy_next_state;
				goto yy_match;
				}

			else
				{
				yy_cp = yyg->yy_last_accepting_cpos;
				yy_current_state = yyg->yy_last_accepting_state;
				goto yy_find_action;
				}
			}

		else switch ( yy_get_next_buffer( yyscanner ) )
			{
			case EOB_ACT_END_OF_FILE:
				{
				yyg->yy_did_buffer_switch_on_eof = 0;

				if ( yywrap( yyscanner ) )
					{
					/* Note: because we've taken care in
					 * yy_get_next_buffer() to have set up
					 * yytext, we can now set up
					 * yy_c_buf_p so that if some total
					 * hoser (like flex itself) wants to
					 * call the scanner after we return the
					 * YY_NULL, it'll still work - another
					 * YY_NULL will get returned.
					 */
					yyg->yy_c_buf_p = yyg->yytext_ptr + YY_MORE_ADJ;

					yy_act = YY_STATE_EOF(YY_START);
					goto do_action;
					}

				else
					{
					if ( ! yyg->yy_did_buffer_switch_on_eof )
						YY_NEW_FILE;
					}
				break;
				}

			case EOB_ACT_CONTINUE_SCAN:
				yyg->yy_c_buf_p =
					yyg->yytext_ptr + yy_amount_of_matched_text;

				yy_current_state = yy_get_previous_state( yyscanner );

				yy_cp = yyg->yy_c_buf_p;
				yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
				goto yy_match;

			case EOB_ACT_LAST_MATCH:
				yyg->yy_c_buf_p =
				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars];

				yy_current_state = yy_get_previous_state( yyscanner );

				yy_cp = yyg->yy_c_buf_p;
				yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
				goto yy_find_action;
			}
		break;
		}

	default:
		YY_FATAL_ERROR(
			"fatal flex scanner internal error--no action found" );
	} /* end of action switch */
		} /* end of scanning one token */
	} /* end of user's declarations */
} /* end of yylex */

/* yy_get_next_buffer - try to read in a new buffer
 *
 * Returns a code representing an action:
 *	EOB_ACT_LAST_MATCH -
 *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
 *	EOB_ACT_END_OF_FILE - end of file
 */
static int yy_get_next_buffer (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
	char *source = yyg->yytext_ptr;
	int number_to_move, i;
	int ret_val;

	if ( yyg->yy_c_buf_p > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] )
		YY_FATAL_ERROR(
		"fatal flex scanner internal error--end of buffer missed" );

	if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )
		{ /* Don't try to fill the buffer, so this is an EOF. */
		if ( yyg->yy_c_buf_p - yyg->yytext_ptr - YY_MORE_ADJ == 1 )
			{
			/* We matched a single character, the EOB, so
			 * treat this as a final EOF.
			 */
			return EOB_ACT_END_OF_FILE;
			}

		else
			{
			/* We matched some text prior to the EOB, first
			 * process it.
			 */
			return EOB_ACT_LAST_MATCH;
			}
		}

	/* Try to read more data. */

	/* First move last chars to start of buffer. */
	number_to_move = (int) (yyg->yy_c_buf_p - yyg->yytext_ptr - 1);

	for ( i = 0; i < number_to_move; ++i )
		*(dest++) = *(source++);

	if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
		/* don't do the read, it's not guaranteed to return an EOF,
		 * just force an EOF
		 */
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars = 0;

	else
		{
			int num_to_read =
			YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;

		while ( num_to_read <= 0 )
			{ /* Not enough room in the buffer - grow it. */

			/* just a shorter name for the current buffer */
			YY_BUFFER_STATE b = YY_CURRENT_BUFFER_LVALUE;

			int yy_c_buf_p_offset =
				(int) (yyg->yy_c_buf_p - b->yy_ch_buf);

			if ( b->yy_is_our_buffer )
				{
				int new_size = b->yy_buf_size * 2;

				if ( new_size <= 0 )
					b->yy_buf_size += b->yy_buf_size / 8;
				else
					b->yy_buf_size *= 2;

				b->yy_ch_buf = (char *)
					/* Include room in for 2 EOB chars. */
					yyrealloc( (void *) b->yy_ch_buf,
							 (yy_size_t) (b->yy_buf_size + 2) , yyscanner );
				}
			else
				/* Can't grow it, we don't own it. */
				b->yy_ch_buf = NULL;

			if ( ! b->yy_ch_buf )
				YY_FATAL_ERROR(
				"fatal error - scanner input buffer overflow" );

			yyg->yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];

			num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
						number_to_move - 1;

			}

		if ( num_to_read > YY_READ_BUF_SIZE )
			num_to_read = YY_READ_BUF_SIZE;

		/* Read in more data. */
		YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
			yyg->yy_n_chars, num_to_read );

		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
		}

	if ( yyg->yy_n_chars == 0 )
		{
		if ( number_to_move == YY_MORE_ADJ )
			{
			ret_val = EOB_ACT_END_OF_FILE;
			yyrestart( yyin  , yyscanner);
			}

		else
			{
			ret_val = EOB_ACT_LAST_MATCH;
			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =
				YY_BUFFER_EOF_PENDING;
			}
		}

	else
		ret_val = EOB_ACT_CONTINUE_SCAN;

	if ((yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
		/* Extend the array by 50%, plus the number we really need. */
		int new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);
		YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) yyrealloc(
			(void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf, (yy_size_t) new_size , yyscanner );
		if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
			YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
		/* "- 2" to take care of EOB's */
		YY_CURRENT_BUFFER_LVALUE->yy_buf_size = (int) (new_size - 2);
	}

	yyg->yy_n_chars += number_to_move;
	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;

	yyg->yytext_ptr = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];

	return ret_val;
}

/* yy_get_previous_state - get the state just before the EOB char was reached */

    static yy_state_type yy_get_previous_state (yyscan_t yyscanner)
{
	yy_state_type yy_current_state;
	char *yy_cp;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	yy_current_state = yyg->yy_start;

	for ( yy_cp = yyg->yytext_ptr + YY_MORE_ADJ; yy_cp < yyg->yy_c_buf_p; ++yy_cp )
		{
		YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
		if ( yy_accept[yy_current_state] )
			{
			yyg->yy_last_accepting_state = yy_current_state;
			yyg->yy_last_accepting_cpos = yy_cp;
			}
		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
			{
			yy_current_state = (int) yy_def[yy_current_state];
			if ( yy_current_state >= 33 )
				yy_c = yy_meta[yy_c];
			}
		yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
		}

	return yy_current_state;
}

/* yy_try_NUL_trans - try to make a transition on the NUL character
 *
 * synopsis
 *	next_state = yy_try_NUL_trans( current_state );
 */
    static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state , yyscan_t yyscanner)
{
	int yy_is_jam;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner; /* This var may be unused depending upon options. */
	char *yy_cp = yyg->yy_c_buf_p;

	YY_CHAR yy_c = 1;
	if ( yy_accept[yy_current_state] )
		{
		yyg->yy_last_accepting_state = yy_current_state;
		yyg->yy_last_accepting_cpos = yy_cp;
		}
	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
		{
		yy_current_state = (int) yy_def[yy_current_state];
		if ( yy_current_state >= 33 )
			yy_c = yy_meta[yy_c];
		}
	yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
	yy_is_jam = (yy_current_state == 32);

	(void)yyg;
	return yy_is_jam ? 0 : yy_current_state;
}

#ifndef YY_NO_UNPUT

#endif

#ifndef YY_NO_INPUT
#ifdef __cplusplus
    static int yyinput (yyscan_t yyscanner)
#else
    static int input  (yyscan_t yyscanner)
#endif

{
	int c;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	*yyg->yy_c_buf_p = yyg->yy_hold_char;

	if ( *yyg->yy_c_buf_p == YY_END_OF_BUFFER_CHAR )
		{
		/* yy_c_buf_p now points to the character we want to return.
		 * If this occurs *before* the EOB characters, then it's a
		 * valid NUL; if not, then we've hit the end of the buffer.
		 */
		if ( yyg->yy_c_buf_p < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
			/* This was really a NUL. */
			*yyg->yy_c_buf_p = '\0';

		else
			{ /* need more input */
			int offset = (int) (yyg->yy_c_buf_p - yyg->yytext_ptr);
			++yyg->yy_c_buf_p;

			switch ( yy_get_next_buffer( yyscanner ) )
				{
				case EOB_ACT_LAST_MATCH:
					/* This happens because yy_g_n_b()
					 * sees that we've accumulated a
					 * token and flags that we need to
					 * try matching the token before
					 * proceeding.  But for input(),
					 * there's no matching to consider.
					 * So convert the EOB_ACT_LAST_MATCH
					 * to EOB_ACT_END_OF_FILE.
					 */

					/* Reset buffer status. */
					yyrestart( yyin , yyscanner);

					/*FALLTHROUGH*/

				case EOB_ACT_END_OF_FILE:
					{
					if ( yywrap( yyscanner ) )
						return 0;

					if ( ! yyg->yy_did_buffer_switch_on_eof )
						YY_NEW_FILE;
#ifdef __cplusplus
					return yyinput(yyscanner);
#else
					return input(yyscanner);
#endif
					}

				case EOB_ACT_CONTINUE_SCAN:
					yyg->yy_c_buf_p = yyg->yytext_ptr + offset;
					break;
				}
			}
		}

	c = *(unsigned char *) yyg->yy_c_buf_p;	/* cast for 8-bit char's */
	*yyg->yy_c_buf_p = '\0';	/* preserve yytext */
	yyg->yy_hold_char = *++yyg->yy_c_buf_p;

	return c;
}
#endif	/* ifndef YY_NO_INPUT */

/** Immediately switch to a different input stream.
 * @param input_file A readable stream.
 * @param yyscanner The scanner object.
 * @note This function does not reset the start condition to @c INITIAL .
 */
    void yyrestart  (FILE * input_file , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	if ( ! YY_CURRENT_BUFFER ){
        yyensure_buffer_stack (yyscanner);
		YY_CURRENT_BUFFER_LVALUE =
            yy_create_buffer( yyin, YY_BUF_SIZE , yyscanner);
	}

	yy_init_buffer( YY_CURRENT_BUFFER, input_file , yyscanner);
	yy_load_buffer_state( yyscanner );
}

/** Switch to a different input buffer.
 * @param new_buffer The new input buffer.
 * @param yyscanner The scanner object.
 */
    void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	/* TODO. We should be able to replace this entire function body
	 * with
	 *		yypop_buffer_state();
	 *		yypush_buffer_state(new_buffer);
     */
	yyensure_buffer_stack (yyscanner);
	if ( YY_CURRENT_BUFFER == new_buffer )
		return;

	if ( YY_CURRENT_BUFFER )
		{
		/* Flush out information for old buffer. */
		*yyg->yy_c_buf_p = yyg->yy_hold_char;
		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
		}

	YY_CURRENT_BUFFER_LVALUE = new_buffer;
	yy_load_buffer_state( yyscanner );

	/* We don't actually know whether we did this switch during
	 * EOF (yywrap()) processing, but the only time this flag
	 * is looked at is after yywrap() is called, so it's safe
	 * to go ahead and always set it.
	 */
	yyg->yy_did_buffer_switch_on_eof = 1;
}

static void yy_load_buffer_state  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
	yyg->yytext_ptr = yyg->yy_c_buf_p = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
	yyg->yy_hold_char = *yyg->yy_c_buf_p;
}

/** Allocate and initialize an input buffer state.
 * @param file A readable stream.
 * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.
 * @param yyscanner The scanner object.
 * @return the allocated buffer state.
 */
    YY_BUFFER_STATE yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
{
	YY_BUFFER_STATE b;
    
	b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state ) , yyscanner );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_buf_size = size;

	/* yy_ch_buf has to be 2 characters longer than the size given because
	 * we need to put in 2 end-of-buffer characters.
	 */
	b->yy_ch_buf = (char *) yyalloc( (yy_size_t) (b->yy_buf_size + 2) , yyscanner );
	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_is_our_buffer = 1;

	yy_init_buffer( b, file , yyscanner);

	return b;
}

/** Destroy the buffer.
 * @param b a buffer created with yy_create_buffer()
 * @param yyscanner The scanner object.
 */
    void yy_delete_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	if ( ! b )
		return;

	if ( b == YY_CURRENT_BUFFER ) /* Not sure if we should pop here. */
		YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;

	if ( b->yy_is_our_buffer )
		yyfree( (void *) b->yy_ch_buf , yyscanner );

	yyfree( (void *) b , yyscanner );
}

/* Initializes or reinitializes a buffer.
 * This function is sometimes called more than once on the same buffer,
 * such as during a yyrestart() or at EOF.
 */
    static void yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file , yyscan_t yyscanner)

{
	int oerrno = errno;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	yy_flush_buffer( b , yyscanner);

	b->yy_input_file = file;
	b->yy_fill_buffer = 1;

    /* If b is the current buffer, then yy_init_buffer was _probably_
     * called from yyrestart() or through yy_get_next_buffer.
     * In that case, we don't want to reset the lineno or column.
     */
    if (b != YY_CURRENT_BUFFER){
        b->yy_bs_lineno = 1;
        b->yy_bs_column = 0;
    }

        b->yy_is_interactive = 0;
    
	errno = oerrno;
}

/** Discard all buffered characters. On the next scan, YY_INPUT will be called.
 * @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
 * @param yyscanner The scanner object.
 */
    void yy_flush_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	if ( ! b )
		return;

	b->yy_n_chars = 0;

	/* We always need two end-of-buffer characters.  The first causes
	 * a transition to the end-of-buffer state.  The second causes
	 * a jam in that state.
	 */
	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

	b->yy_buf_pos = &b->yy_ch_buf[0];

	b->yy_at_bol = 1;
	b->yy_buffer_status = YY_BUFFER_NEW;

	if ( b == YY_CURRENT_BUFFER )
		yy_load_buffer_state( yyscanner );
}

/** Pushes the new state onto the stack. The new state becomes
 *  the current state. This function will allocate the stack
 *  if necessary.
 *  @param new_buffer The new state.
 *  @param yyscanner The scanner object.
 */
void yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	if (new_buffer == NULL)
		return;

	yyensure_buffer_stack(yyscanner);

	/* This block is copied from yy_switch_to_buffer. */
	if ( YY_CURRENT_BUFFER )
		{
		/* Flush out information for old buffer. */
		*yyg->yy_c_buf_p = yyg->yy_hold_char;
		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
		}

	/* Only push if top exists. Otherwise, replace top. */
	if (YY_CURRENT_BUFFER)
		yyg->yy_buffer_stack_top++;
	YY_CURRENT_BUFFER_LVALUE = new_buffer;

	/* copied from yy_switch_to_buffer. */
	yy_load_buffer_state( yyscanner );
	yyg->yy_did_buffer_switch_on_eof = 1;
}

/** Removes and deletes the top of the stack, if present.
 *  The next element becomes the new top.
 *  @param yyscanner The scanner object.
 */
void yypop_buffer_state (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	if (!YY_CURRENT_BUFFER)
		return;

	yy_delete_buffer(YY_CURRENT_BUFFER , yyscanner);
	YY_CURRENT_BUFFER_LVALUE = NULL;
	if (yyg->yy_buffer_stack_top > 0)
		--yyg->yy_buffer_stack_top;

	if (YY_CURRENT_BUFFER) {
		yy_load_buffer_state( yyscanner );
		yyg->yy_did_buffer_switch_on_eof = 1;
	}
}

/* Allocates the stack if it does not exist.
 *  Guarantees space for at least one push.
 */
static void yyensure_buffer_stack (yyscan_t yyscanner)
{
	yy_size_t num_to_alloc;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	if (!yyg->yy_buffer_stack) {

		/* First allocation is just for 2 elements, since we don't know if this
		 * scanner will even need a stack. We use 2 instead of 1 to avoid an
		 * immediate realloc on the next call.
         */
      num_to_alloc = 1; /* After all that talk, this was set to 1 anyways... */
		yyg->yy_buffer_stack = (struct yy_buffer_state**)yyalloc
								(num_to_alloc * sizeof(struct yy_buffer_state*)
								, yyscanner);
		if ( ! yyg->yy_buffer_stack )
			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );

		memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));

		yyg->yy_buffer_stack_max = num_to_alloc;
		yyg->yy_buffer_stack_top = 0;
		return;
	}

	if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){

		/* Increase the buffer to prepare for a possible push. */
		yy_size_t grow_size = 8 /* arbitrary grow size */;

		num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
		yyg->yy_buffer_stack = (struct yy_buffer_state**)yyrealloc
								(yyg->yy_buffer_stack,
								num_to_alloc * sizeof(struct yy_buffer_state*)
								, yyscanner);
		if ( ! yyg->yy_buffer_stack )
			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );

		/* zero only the new slots.*/
		memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
		yyg->yy_buffer_stack_max = num_to_alloc;
	}
}

/** Setup the input buffer state to scan directly from a user-specified character buffer.
 * @param base the character buffer
 * @param size the size in bytes of the character buffer
 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
{
	YY_BUFFER_STATE b;
    
	if ( size < 2 ||
	     base[size-2] != YY_END_OF_BUFFER_CHAR ||
	     base[size-1] != YY_END_OF_BUFFER_CHAR )
		/* They forgot to leave room for the EOB's. */
		return NULL;

	b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state ) , yyscanner );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_buffer()" );

	b->yy_buf_size = (int) (size - 2);	/* "- 2" to take care of EOB's */
	b->yy_buf_pos = b->yy_ch_buf = base;
	b->yy_is_our_buffer = 0;
	b->yy_input_file = NULL;
	b->yy_n_chars = b->yy_buf_size;
	b->yy_is_interactive = 0;
	b->yy_at_bol = 1;
	b->yy_fill_buffer = 0;
	b->yy_buffer_status = YY_BUFFER_NEW;

	yy_switch_to_buffer( b , yyscanner );

	return b;
}

/** Setup the input buffer state to scan a string. The next call to yylex() will
 * scan from a @e copy of @a str.
 * @param yystr a NUL-terminated string to scan
 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 * @note If you want to scan bytes that may contain NUL values, then use
 *       yy_scan_bytes() instead.
 */
YY_BUFFER_STATE yy_scan_string (const char * yystr , yyscan_t yyscanner)
{
    
	return yy_scan_bytes( yystr, (int) strlen(yystr) , yyscanner);
}

/** Setup the input buffer state to scan the given bytes. The next call to yylex() will
 * scan from a @e copy of @a bytes.
 * @param yybytes the byte buffer to scan
 * @param _yybytes_len the number of bytes in the buffer pointed to by @a bytes.
 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE yy_scan_bytes  (const char * yybytes, int  _yybytes_len , yyscan_t yyscanner)
{
	YY_BUFFER_STATE b;
	char *buf;
	yy_size_t n;
	int i;
    
	/* Get memory for full buffer, including space for trailing EOB's. */
	n = (yy_size_t) (_yybytes_len + 2);
	buf = (char *) yyalloc( n , yyscanner );
	if ( ! buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_bytes()" );

	for ( i = 0; i < _yybytes_len; ++i )
		buf[i] = yybytes[i];

	buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;

	b = yy_scan_buffer( buf, n , yyscanner);
	if ( ! b )
		YY_FATAL_ERROR( "bad buffer in yy_scan_bytes()" );

	/* It's okay to grow etc. this buffer, and we should throw it
	 * away when we're done.
	 */
	b->yy_is_our_buffer = 1;

	return b;
}

#ifndef YY_EXIT_FAILURE
#define YY_EXIT_FAILURE 2
#endif

static void yynoreturn yy_fatal_error (const char* msg , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;
	fprintf( stderr, "%s\n", msg );
	exit( YY_EXIT_FAILURE );
}

/* Redefine yyless() so it works in section 3 code. */

#undef yyless
#define yyless(n) \
	do \
		{ \
		/* Undo effects of setting up yytext. */ \
        int yyless_macro_arg = (n); \
        YY_LESS_LINENO(yyless_macro_arg);\
		yytext[yyleng] = yyg->yy_hold_char; \
		yyg->yy_c_buf_p = yytext + yyless_macro_arg; \
		yyg->yy_hold_char = *yyg->yy_c_buf_p; \
		*yyg->yy_c_buf_p = '\0'; \
		yyleng = yyless_macro_arg; \
		} \
	while ( 0 )

/* Accessor  methods (get/set functions) to struct members. */

/** Get the user-defined data for this scanner.
 * @param yyscanner The scanner object.
 */
YY_EXTRA_TYPE yyget_extra  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yyextra;
}

/** Get the current line number.
 * @param yyscanner The scanner object.
 */
int yyget_lineno  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        if (! YY_CURRENT_BUFFER)
            return 0;
    
    return yylineno;
}

/** Get the current column number.
 * @param yyscanner The scanner object.
 */
int yyget_column  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        if (! YY_CURRENT_BUFFER)
            return 0;
    
    return yycolumn;
}

/** Get the input stream.
 * @param yyscanner The scanner object.
 */
FILE *yyget_in  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yyin;
}

/** Get the output stream.
 * @param yyscanner The scanner object.
 */
FILE *yyget_out  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yyout;
}

/** Get the length of the current token.
 * @param yyscanner The scanner object.
 */
int yyget_leng  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yyleng;
}

/** Get the current token.
 * @param yyscanner The scanner object.
 */

char *yyget_text  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yytext;
}

/** Set the user-defined data. This data is never touched by the scanner.
 * @param user_defined The data to be associated with this scanner.
 * @param yyscanner The scanner object.
 */
void yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yyextra = user_defined ;
}

/** Set the current line number.
 * @param _line_number line number
 * @param yyscanner The scanner object.
 */
void yyset_lineno (int  _line_number , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        /* lineno is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           YY_FATAL_ERROR( "yyset_lineno called with no buffer" );
    
    yylineno = _line_number;
}

/** Set the current column.
 * @param _column_no column number
 * @param yyscanner The scanner object.
 */
void yyset_column (int  _column_no , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        /* column is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           YY_FATAL_ERROR( "yyset_column called with no buffer" );
    
    yycolumn = _column_no;
}

/** Set the input stream. This does not discard the current
 * input buffer.
 * @param _in_str A readable stream.
 * @param yyscanner The scanner object.
 * @see yy_switch_to_buffer
 */
void yyset_in (FILE *  _in_str , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yyin = _in_str ;
}

void yyset_out (FILE *  _out_str , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yyout = _out_str ;
}

int yyget_debug  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yy_flex_debug;
}

void yyset_debug (int  _bdebug , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yy_flex_debug = _bdebug ;
}

/* Accessor methods for yylval and yylloc */

/* User-visible API */

/* yylex_init is special because it creates the scanner itself, so it is
 * the ONLY reentrant function that doesn't take the scanner as the last argument.
 * That's why we explicitly handle the declaration, instead of using our macros.
 */
int yylex_init(yyscan_t* ptr_yy_globals)
{
    if (ptr_yy_globals == NULL){
        errno = EINVAL;
        return 1;
    }

    *ptr_yy_globals = (yyscan_t) yyalloc ( sizeof( struct yyguts_t ), NULL );

    if (*ptr_yy_globals == NULL){
        errno = ENOMEM;
        return 1;
    }

    /* By setting to 0xAA, we expose bugs in yy_init_globals. Leave at 0x00 for releases. */
    memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));

    return yy_init_globals ( *ptr_yy_globals );
}

/* yylex_init_extra has the same functionality as yylex_init, but follows the
 * convention of taking the scanner as the last argument. Note however, that
 * this is a *pointer* to a scanner, as it will be allocated by this call (and
 * is the reason, too, why this function also must handle its own declaration).
 * The user defined value in the first argument will be available to yyalloc in
 * the yyextra field.
 */
int yylex_init_extra( YY_EXTRA_TYPE yy_user_defined, yyscan_t* ptr_yy_globals )
{
    struct yyguts_t dummy_yyguts;

    yyset_extra (yy_user_defined, &dummy_yyguts);

    if (ptr_yy_globals == NULL){
        errno = EINVAL;
        return 1;
    }

    *ptr_yy_globals = (yyscan_t) yyalloc ( sizeof( struct yyguts_t ), &dummy_yyguts );

    if (*ptr_yy_globals == NULL){
        errno = ENOMEM;
        return 1;
    }

    /* By setting to 0xAA, we expose bugs in
    yy_init_globals. Leave at 0x00 for releases. */
    memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));

    yyset_extra (yy_user_defined, *ptr_yy_globals);

    return yy_init_globals ( *ptr_yy_globals );
}

static int yy_init_globals (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    /* Initialization is the same as for the non-reentrant scanner.
     * This function is called from yylex_destroy(), so don't allocate here.
     */

    yyg->yy_buffer_stack = NULL;
    yyg->yy_buffer_stack_top = 0;
    yyg->yy_buffer_stack_max = 0;
    yyg->yy_c_buf_p = NULL;
    yyg->yy_init = 0;
    yyg->yy_start = 0;

    yyg->yy_start_stack_ptr = 0;
    yyg->yy_start_stack_depth = 0;
    yyg->yy_start_stack =  NULL;

/* Defined in main.c */
#ifdef YY_STDINIT
    yyin = stdin;
    yyout = stdout;
#else
    yyin = NULL;
    yyout = NULL;
#endif

    /* For future reference: Set errno on error, since we are called by
     * yylex_init()
     */
    return 0;
}

/* yylex_destroy is for both reentrant and non-reentrant scanners. */
int yylex_destroy  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

    /* Pop the buffer stack, destroying each element. */
	while(YY_CURRENT_BUFFER){
		yy_delete_buffer( YY_CURRENT_BUFFER , yyscanner );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		yypop_buffer_state(yyscanner);
	}

	/* Destroy the stack itself. */
	yyfree(yyg->yy_buffer_stack , yyscanner);
	yyg->yy_buffer_stack = NULL;

    /* Destroy the start condition stack. */
        yyfree( yyg->yy_start_stack , yyscanner );
        yyg->yy_start_stack = NULL;

    /* Reset the globals. This is important in a non-reentrant scanner so the next time
     * yylex() is called, initialization will occur. */
    yy_init_globals( yyscanner);

    /* Destroy the main struct (reentrant only). */
    yyfree ( yyscanner , yyscanner );
    yyscanner = NULL;
    return 0;
}

/*
 * Internal utility routines.
 */

#ifndef yytext_ptr
static void yy_flex_strncpy (char* s1, const char * s2, int n , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;

	int i;
	for ( i = 0; i < n; ++i )
		s1[i] = s2[i];
}
#endif

#ifdef YY_NEED_STRLEN
static int yy_flex_strlen (const char * s , yyscan_t yyscanner)
{
	int n;
	for ( n = 0; s[n]; ++n )
		;

	return n;
}
#endif

void *yyalloc (yy_size_t  size , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;
	return malloc(size);
}

void *yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;

	/* The cast to (char *) in the following accommodates both
	 * implementations that use char* generic pointers, and those
	 * that use void* generic pointers.  It works with the latter
	 * because both ANSI C and C++ allow castless assignment from
	 * any pointer type to void*, and deal with argument conversions
	 * as though doing an assignment.
	 */
	return realloc(ptr, size);
}

void yyfree (void * ptr , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;
	free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
}

#define YYTABLES_NAME "yytables"



/***** End of gdbwire_mi_lexer.c *********************************************/
/***** Begin file gdbwire_mi_grammar.c ***************************************/
/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 0


/* Substitute the variable and function names.  */
#define yypush_parse    gdbwire_mi_push_parse
#define yypstate_new    gdbwire_mi_pstate_new
#define yypstate_clear  gdbwire_mi_pstate_clear
#define yypstate_delete gdbwire_mi_pstate_delete
#define yypstate        gdbwire_mi_pstate
#define yylex           gdbwire_mi_lex
#define yyerror         gdbwire_mi_error
#define yydebug         gdbwire_mi_debug
#define yynerrs         gdbwire_mi_nerrs

/* First part of user prologue.  */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* #include "gdbwire_sys.h" */
/* #include "gdbwire_mi_grammar.h" */
/* #include "gdbwire_mi_pt.h" */
/* #include "gdbwire_mi_pt_alloc.h" */

char *gdbwire_mi_get_text(yyscan_t yyscanner);
struct gdbwire_mi_position gdbwire_mi_get_extra(yyscan_t yyscanner);

/**
 * Used only in the parser to build a gdbwire_mi_result list.
 *
 * The grammar wants to build a list of gdbwire_mi_result pointers.
 * However, the gdbwire_mi_result is a traditional linked list and
 * standard append functionality (using next to get to end of list) is slow.
 *
 * This structure allows us to keep around the last result in the list
 * for fast insertion.
 */
struct gdbwire_mi_result_list {
    /** The gdbwire_mi_result list that is being built */
    struct gdbwire_mi_result *head;
    /** The pointer to the last result in the list for fast insertion. */
    struct gdbwire_mi_result **tail;
};

/** 
 * Allocate a gdbwire_mi_result_list data structure.
 *
 * @return
 * The gdbwire_mi_result_list. Use free() to release the memory.
 */
struct gdbwire_mi_result_list *gdbwire_mi_result_list_alloc(void)
{
    struct gdbwire_mi_result_list *result;
    result = calloc(1, sizeof(struct gdbwire_mi_result_list));
    result->tail = &result->head;
    return result;
}

/**
 * Append an item to this list.
 *
 * @param list
 * The list to append to.
 *
 * @param result
 * The result to append to the end of the list.
 */
void gdbwire_mi_result_list_push_back(struct gdbwire_mi_result_list *list,
        struct gdbwire_mi_result *result)
{
    *list->tail = result;
    list->tail = &result->next;
}

void gdbwire_mi_error(yyscan_t yyscanner,
    struct gdbwire_mi_output **gdbwire_mi_output, const char *s)
{ 
    char *text = gdbwire_mi_get_text(yyscanner);
    struct gdbwire_mi_position pos = gdbwire_mi_get_extra(yyscanner);

    *gdbwire_mi_output = gdbwire_mi_output_alloc();
    (*gdbwire_mi_output)->kind = GDBWIRE_MI_OUTPUT_PARSE_ERROR;
    (*gdbwire_mi_output)->variant.error.token = gdbwire_strdup(text);
    (*gdbwire_mi_output)->variant.error.pos = pos;
}

/**
 * GDB/MI escapes characters in the c-string rule.
 *
 * The c-string starts and ends with a ".
 * Each " in the c-string is escaped with a \. So GDB turns " into \".
 * Each \ in the string is then escaped with a \. So GDB turns \ into \\.
 *
 * Remove the GDB/MI escape characters to provide back to the user the
 * original characters that GDB was intending to transmit. So
 *   \" -> "
 *   \\ -> \
 *   \n -> new line
 *   \r -> carriage return
 *   \t -> tab
 *
 * See gdbwire_mi_grammar.txt (GDB/MI Clarifications) for more information.
 *
 * @param str
 * The escaped GDB/MI c-string data.
 *
 * @return
 * An allocated strng representing str with the escaping undone.
 */
static char *gdbwire_mi_unescape_cstring(char *str)
{
    char *result;
    size_t r, s, length;

    /*assert(str);*/

    result = gdbwire_strdup(str);
    length = strlen(str);

    /* a CSTRING should start and end with a quote */
    /*assert(result);*/
    /*assert(length >= 2);*/

    for (r = 0, s = 1; s < length - 1; ++s) {
        if (str[s] == '\\') {
            switch (str[s+1]) {
                case 'n':
                    result[r++] = '\n';
                    ++s;
                    break;
                case 'b':
                    result[r++] = '\b';
                    ++s;
                    break;
                case 't':
                    result[r++] = '\t';
                    ++s;
                    break;
                case 'f':
                    result[r++] = '\f';
                    ++s;
                    break;
                case 'r':
                    result[r++] = '\r';
                    ++s;
                    break;
                case 'e':
                    result[r++] = '\033';
                    ++s;
                    break;
                case 'a':
                    result[r++] = '\007';
                    ++s;
                    break;
                case '"':
                    result[r++] = '\"';
                    ++s;
                    break;
                case '\\':
                    result[r++] = '\\';
                    ++s;
                    break;
                default:
                    result[r++] = str[s];
                    break;
            }
        } else {
            result[r++] = str[s];
        }
    }

    result[r] = 0;

    return result;
}



# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_GDBWIRE_MI_SRC_GDBWIRE_MI_GRAMMAR_H_INCLUDED
# define YY_GDBWIRE_MI_SRC_GDBWIRE_MI_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int gdbwire_mi_debug;
#endif
/* "%code requires" blocks.  */


/* An opaque pointer. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

    struct gdbwire_mi_output;


/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    OPEN_BRACE = 258,              /* OPEN_BRACE  */
    CLOSED_BRACE = 259,            /* CLOSED_BRACE  */
    OPEN_PAREN = 260,              /* OPEN_PAREN  */
    CLOSED_PAREN = 261,            /* CLOSED_PAREN  */
    ADD_OP = 262,                  /* ADD_OP  */
    MULT_OP = 263,                 /* MULT_OP  */
    EQUAL_SIGN = 264,              /* EQUAL_SIGN  */
    TILDA = 265,                   /* TILDA  */
    AT_SYMBOL = 266,               /* AT_SYMBOL  */
    AMPERSAND = 267,               /* AMPERSAND  */
    OPEN_BRACKET = 268,            /* OPEN_BRACKET  */
    CLOSED_BRACKET = 269,          /* CLOSED_BRACKET  */
    NEWLINE = 270,                 /* NEWLINE  */
    INTEGER_LITERAL = 271,         /* INTEGER_LITERAL  */
    STRING_LITERAL = 272,          /* STRING_LITERAL  */
    CSTRING = 273,                 /* CSTRING  */
    COMMA = 274,                   /* COMMA  */
    CARROT = 275                   /* CARROT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define OPEN_BRACE 258
#define CLOSED_BRACE 259
#define OPEN_PAREN 260
#define CLOSED_PAREN 261
#define ADD_OP 262
#define MULT_OP 263
#define EQUAL_SIGN 264
#define TILDA 265
#define AT_SYMBOL 266
#define AMPERSAND 267
#define OPEN_BRACKET 268
#define CLOSED_BRACKET 269
#define NEWLINE 270
#define INTEGER_LITERAL 271
#define STRING_LITERAL 272
#define CSTRING 273
#define COMMA 274
#define CARROT 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{

  struct gdbwire_mi_output *u_output;
  struct gdbwire_mi_oob_record *u_oob_record;
  struct gdbwire_mi_result_record *u_result_record;
  int u_result_class;
  int u_async_record_kind;
  struct gdbwire_mi_result_list *u_result_list;
  struct gdbwire_mi_result *u_result;
  char *u_token;
  struct gdbwire_mi_async_record *u_async_record;
  struct gdbwire_mi_stream_record *u_stream_record;
  int u_async_class;
  char *u_variable;
  char *u_cstring;
  struct gdbwire_mi_result *u_tuple;
  struct gdbwire_mi_result *u_list;
  int u_stream_record_kind;


};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct gdbwire_mi_pstate gdbwire_mi_pstate;


int gdbwire_mi_push_parse (gdbwire_mi_pstate *ps,
                  int pushed_char, YYSTYPE const *pushed_val, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output);

gdbwire_mi_pstate *gdbwire_mi_pstate_new (void);
void gdbwire_mi_pstate_delete (gdbwire_mi_pstate *ps);


#endif /* !YY_GDBWIRE_MI_SRC_GDBWIRE_MI_GRAMMAR_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_OPEN_BRACE = 3,                 /* OPEN_BRACE  */
  YYSYMBOL_CLOSED_BRACE = 4,               /* CLOSED_BRACE  */
  YYSYMBOL_OPEN_PAREN = 5,                 /* OPEN_PAREN  */
  YYSYMBOL_CLOSED_PAREN = 6,               /* CLOSED_PAREN  */
  YYSYMBOL_ADD_OP = 7,                     /* ADD_OP  */
  YYSYMBOL_MULT_OP = 8,                    /* MULT_OP  */
  YYSYMBOL_EQUAL_SIGN = 9,                 /* EQUAL_SIGN  */
  YYSYMBOL_TILDA = 10,                     /* TILDA  */
  YYSYMBOL_AT_SYMBOL = 11,                 /* AT_SYMBOL  */
  YYSYMBOL_AMPERSAND = 12,                 /* AMPERSAND  */
  YYSYMBOL_OPEN_BRACKET = 13,              /* OPEN_BRACKET  */
  YYSYMBOL_CLOSED_BRACKET = 14,            /* CLOSED_BRACKET  */
  YYSYMBOL_NEWLINE = 15,                   /* NEWLINE  */
  YYSYMBOL_INTEGER_LITERAL = 16,           /* INTEGER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 17,            /* STRING_LITERAL  */
  YYSYMBOL_CSTRING = 18,                   /* CSTRING  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_CARROT = 20,                    /* CARROT  */
  YYSYMBOL_YYACCEPT = 21,                  /* $accept  */
  YYSYMBOL_output_list = 22,               /* output_list  */
  YYSYMBOL_output = 23,                    /* output  */
  YYSYMBOL_output_variant = 24,            /* output_variant  */
  YYSYMBOL_25_1 = 25,                      /* $@1  */
  YYSYMBOL_result_record = 26,             /* result_record  */
  YYSYMBOL_oob_record = 27,                /* oob_record  */
  YYSYMBOL_async_record = 28,              /* async_record  */
  YYSYMBOL_async_record_class = 29,        /* async_record_class  */
  YYSYMBOL_result_class = 30,              /* result_class  */
  YYSYMBOL_async_class = 31,               /* async_class  */
  YYSYMBOL_opt_variable = 32,              /* opt_variable  */
  YYSYMBOL_result_list = 33,               /* result_list  */
  YYSYMBOL_result = 34,                    /* result  */
  YYSYMBOL_variable = 35,                  /* variable  */
  YYSYMBOL_cstring = 36,                   /* cstring  */
  YYSYMBOL_tuple = 37,                     /* tuple  */
  YYSYMBOL_list = 38,                      /* list  */
  YYSYMBOL_stream_record = 39,             /* stream_record  */
  YYSYMBOL_stream_record_class = 40,       /* stream_record_class  */
  YYSYMBOL_opt_token = 41,                 /* opt_token  */
  YYSYMBOL_token = 42                      /* token  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   42

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  21
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  40
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  56

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   275


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   264,   264,   267,   270,   274,   278,   284,   290,   290,
     302,   309,   317,   323,   329,   337,   346,   350,   354,   358,
     375,   428,   432,   436,   441,   446,   453,   460,   467,   472,
     477,   481,   486,   490,   495,   501,   505,   509,   513,   517,
     521
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "OPEN_BRACE",
  "CLOSED_BRACE", "OPEN_PAREN", "CLOSED_PAREN", "ADD_OP", "MULT_OP",
  "EQUAL_SIGN", "TILDA", "AT_SYMBOL", "AMPERSAND", "OPEN_BRACKET",
  "CLOSED_BRACKET", "NEWLINE", "INTEGER_LITERAL", "STRING_LITERAL",
  "CSTRING", "COMMA", "CARROT", "$accept", "output_list", "output",
  "output_variant", "$@1", "result_record", "oob_record", "async_record",
  "async_record_class", "result_class", "async_class", "opt_variable",
  "result_list", "result", "variable", "cstring", "tuple", "list",
  "stream_record", "stream_record_class", "opt_token", "token", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-19)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-39)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -19,     0,   -19,    15,    11,   -19,   -19,   -19,   -19,   -19,
      16,   -19,   -19,   -19,   -19,    -3,    14,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,    12,    18,    27,
     -19,    17,   -19,    19,   -19,    11,    11,     1,    20,   -19,
      28,    20,     9,   -11,   -19,   -19,   -19,    11,   -19,   -19,
      -2,   -19,    13,   -19,   -19,   -19
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,    35,    36,    37,    40,     3,
       0,     7,     6,    12,    13,     0,     0,    39,     5,    28,
       8,     4,    29,    34,    17,    16,    18,     0,     0,     0,
      19,    10,    20,    14,     9,    21,    21,     0,    11,    23,
       0,    15,    21,    21,    25,    26,    27,    21,    22,    30,
       0,    32,     0,    24,    31,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -18,    -7,    37,     5,   -19,   -19,   -19,   -19,
     -19,   -19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     9,    10,    29,    11,    12,    13,    28,    31,
      33,    37,    38,    39,    40,    23,    45,    46,    14,    15,
      16,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       2,     3,    54,    51,    42,     4,    19,   -38,   -38,   -38,
       5,     6,     7,    49,    43,    22,     8,    47,    41,    22,
     -38,    24,    25,    26,    50,    52,    19,    55,    19,    30,
      18,    21,    47,    34,    27,    32,    35,    48,    36,    47,
      53,    20,    44
};

static const yytype_int8 yycheck[] =
{
       0,     1,     4,    14,     3,     5,    17,     7,     8,     9,
      10,    11,    12,     4,    13,    18,    16,    19,    36,    18,
      20,     7,     8,     9,    42,    43,    17,    14,    17,    17,
      15,    15,    19,     6,    20,    17,    19,     9,    19,    19,
      47,     4,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,     0,     1,     5,    10,    11,    12,    16,    23,
      24,    26,    27,    28,    39,    40,    41,    42,    15,    17,
      35,    15,    18,    36,     7,     8,     9,    20,    29,    25,
      17,    30,    17,    31,     6,    19,    19,    32,    33,    34,
      35,    33,     3,    13,    36,    37,    38,    19,     9,     4,
      33,    14,    33,    34,     4,    14
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    21,    22,    22,    23,    23,    24,    24,    25,    24,
      26,    26,    27,    27,    28,    28,    29,    29,    29,    30,
      31,    32,    32,    33,    33,    34,    34,    34,    35,    36,
      37,    37,    38,    38,    39,    40,    40,    40,    41,    41,
      42
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     1,     1,     0,     4,
       3,     5,     1,     1,     3,     5,     1,     1,     1,     1,
       1,     0,     2,     1,     3,     2,     2,     2,     1,     1,
       2,     3,     2,     3,     2,     1,     1,     1,     0,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (yyscanner, gdbwire_mi_output, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, yyscanner, gdbwire_mi_output); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yyscanner);
  YY_USE (gdbwire_mi_output);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, yyscanner, gdbwire_mi_output);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], yyscanner, gdbwire_mi_output);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, yyscanner, gdbwire_mi_output); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif
/* Parser data structure.  */
struct yypstate
  {
    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;
    /* Whether this instance has not started parsing yet.
     * If 2, it corresponds to a finished parsing.  */
    int yynew;
  };






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output)
{
  YY_USE (yyvaluep);
  YY_USE (yyscanner);
  YY_USE (gdbwire_mi_output);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_output_variant: /* output_variant  */
            { gdbwire_mi_output_free(((*yyvaluep).u_output)); }
        break;

    case YYSYMBOL_opt_variable: /* opt_variable  */
            { free(((*yyvaluep).u_variable)); }
        break;

    case YYSYMBOL_result_list: /* result_list  */
            { gdbwire_mi_result_free(((*yyvaluep).u_result_list)->head); free(((*yyvaluep).u_result_list)); }
        break;

    case YYSYMBOL_result: /* result  */
            { gdbwire_mi_result_free(((*yyvaluep).u_result)); }
        break;

    case YYSYMBOL_variable: /* variable  */
            { free(((*yyvaluep).u_variable)); }
        break;

    case YYSYMBOL_opt_token: /* opt_token  */
            { free(((*yyvaluep).u_token)); }
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}





#define gdbwire_mi_nerrs yyps->gdbwire_mi_nerrs
#define yystate yyps->yystate
#define yyerrstatus yyps->yyerrstatus
#define yyssa yyps->yyssa
#define yyss yyps->yyss
#define yyssp yyps->yyssp
#define yyvsa yyps->yyvsa
#define yyvs yyps->yyvs
#define yyvsp yyps->yyvsp
#define yystacksize yyps->yystacksize

/* Initialize the parser data structure.  */
static void
yypstate_clear (yypstate *yyps)
{
  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yyssp = yyss;
  yyvsp = yyvs;

  /* Initialize the state stack, in case yypcontext_expected_tokens is
     called before the first call to yyparse. */
  *yyssp = 0;
  yyps->yynew = 1;
}

/* Initialize the parser data structure.  */
yypstate *
yypstate_new (void)
{
  yypstate *yyps;
  yyps = YY_CAST (yypstate *, YYMALLOC (sizeof *yyps));
  if (!yyps)
    return YY_NULLPTR;
  yystacksize = YYINITDEPTH;
  yyss = yyssa;
  yyvs = yyvsa;
  yypstate_clear (yyps);
  return yyps;
}

void
yypstate_delete (yypstate *yyps)
{
  if (yyps)
    {
#ifndef yyoverflow
      /* If the stack was reallocated but the parse did not complete, then the
         stack still needs to be freed.  */
      if (yyss != yyssa)
        YYSTACK_FREE (yyss);
#endif
      YYFREE (yyps);
    }
}



/*---------------.
| yypush_parse.  |
`---------------*/

int
yypush_parse (yypstate *yyps,
              int yypushed_char, YYSTYPE const *yypushed_val, yyscan_t yyscanner, struct gdbwire_mi_output **gdbwire_mi_output)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  switch (yyps->yynew)
    {
    case 0:
      yyn = yypact[yystate];
      goto yyread_pushed_token;

    case 2:
      yypstate_clear (yyps);
      break;

    default:
      break;
    }

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      if (!yyps->yynew)
        {
          YYDPRINTF ((stderr, "Return for a new token:\n"));
          yyresult = YYPUSH_MORE;
          goto yypushreturn;
        }
      yyps->yynew = 0;
yyread_pushed_token:
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yypushed_char;
      if (yypushed_val)
        yylval = *yypushed_val;
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* output_list: %empty  */
             {
}
    break;

  case 3: /* output_list: output_list output  */
                                {
}
    break;

  case 4: /* output: output_variant NEWLINE  */
                               {
  *gdbwire_mi_output = (yyvsp[-1].u_output);
}
    break;

  case 5: /* output: error NEWLINE  */
                      {
  yyerrok;
}
    break;

  case 6: /* output_variant: oob_record  */
                           {
  (yyval.u_output) = gdbwire_mi_output_alloc();
  (yyval.u_output)->kind = GDBWIRE_MI_OUTPUT_OOB;
  (yyval.u_output)->variant.oob_record = (yyvsp[0].u_oob_record);
}
    break;

  case 7: /* output_variant: result_record  */
                              {
  (yyval.u_output) = gdbwire_mi_output_alloc();
  (yyval.u_output)->kind = GDBWIRE_MI_OUTPUT_RESULT;
  (yyval.u_output)->variant.result_record = (yyvsp[0].u_result_record);
}
    break;

  case 8: /* $@1: %empty  */
                                    {
      if (strcmp("gdb", (yyvsp[0].u_variable)) != 0) {
          /* Destructor will be called to free $2 on error */
          yyerror(yyscanner, gdbwire_mi_output, "");
          YYERROR;
      }
    }
    break;

  case 9: /* output_variant: OPEN_PAREN variable $@1 CLOSED_PAREN  */
                   {
      (yyval.u_output) = gdbwire_mi_output_alloc();
      (yyval.u_output)->kind = GDBWIRE_MI_OUTPUT_PROMPT;
      free((yyvsp[-2].u_variable));
    }
    break;

  case 10: /* result_record: opt_token CARROT result_class  */
                                             {
  (yyval.u_result_record) = gdbwire_mi_result_record_alloc();
  (yyval.u_result_record)->token = (yyvsp[-2].u_token);
  (yyval.u_result_record)->result_class = (yyvsp[0].u_result_class);
  (yyval.u_result_record)->result = NULL;
}
    break;

  case 11: /* result_record: opt_token CARROT result_class COMMA result_list  */
                                                               {
  (yyval.u_result_record) = gdbwire_mi_result_record_alloc();
  (yyval.u_result_record)->token = (yyvsp[-4].u_token);
  (yyval.u_result_record)->result_class = (yyvsp[-2].u_result_class);
  (yyval.u_result_record)->result = (yyvsp[0].u_result_list)->head;
  free((yyvsp[0].u_result_list));
}
    break;

  case 12: /* oob_record: async_record  */
                         {
  (yyval.u_oob_record) = gdbwire_mi_oob_record_alloc();
  (yyval.u_oob_record)->kind = GDBWIRE_MI_ASYNC;
  (yyval.u_oob_record)->variant.async_record = (yyvsp[0].u_async_record);
}
    break;

  case 13: /* oob_record: stream_record  */
                          {
  (yyval.u_oob_record) = gdbwire_mi_oob_record_alloc();
  (yyval.u_oob_record)->kind = GDBWIRE_MI_STREAM;
  (yyval.u_oob_record)->variant.stream_record = (yyvsp[0].u_stream_record);
}
    break;

  case 14: /* async_record: opt_token async_record_class async_class  */
                                                       {
  (yyval.u_async_record) = gdbwire_mi_async_record_alloc();
  (yyval.u_async_record)->token = (yyvsp[-2].u_token);
  (yyval.u_async_record)->kind = (yyvsp[-1].u_async_record_kind);
  (yyval.u_async_record)->async_class = (yyvsp[0].u_async_class);
  (yyval.u_async_record)->result = NULL;
}
    break;

  case 15: /* async_record: opt_token async_record_class async_class COMMA result_list  */
                                                                         {
  (yyval.u_async_record) = gdbwire_mi_async_record_alloc();
  (yyval.u_async_record)->token = (yyvsp[-4].u_token);
  (yyval.u_async_record)->kind = (yyvsp[-3].u_async_record_kind);
  (yyval.u_async_record)->async_class = (yyvsp[-2].u_async_class);
  (yyval.u_async_record)->result = (yyvsp[0].u_result_list)->head;
  free((yyvsp[0].u_result_list));
}
    break;

  case 16: /* async_record_class: MULT_OP  */
                            {
  (yyval.u_async_record_kind) = GDBWIRE_MI_EXEC;
}
    break;

  case 17: /* async_record_class: ADD_OP  */
                           {
  (yyval.u_async_record_kind) = GDBWIRE_MI_STATUS;
}
    break;

  case 18: /* async_record_class: EQUAL_SIGN  */
                               {
  (yyval.u_async_record_kind) = GDBWIRE_MI_NOTIFY;	
}
    break;

  case 19: /* result_class: STRING_LITERAL  */
                             {
  char *text = gdbwire_mi_get_text(yyscanner);
  if (strcmp("done", text) == 0) {
    (yyval.u_result_class) = GDBWIRE_MI_DONE;
  } else if (strcmp("running", text) == 0) {
    (yyval.u_result_class) = GDBWIRE_MI_RUNNING;
  } else if (strcmp("connected", text) == 0) {
    (yyval.u_result_class) = GDBWIRE_MI_CONNECTED;
  } else if (strcmp("error", text) == 0) {
    (yyval.u_result_class) = GDBWIRE_MI_ERROR;
  } else if (strcmp("exit", text) == 0) {
    (yyval.u_result_class) = GDBWIRE_MI_EXIT;
  } else {
    (yyval.u_result_class) = GDBWIRE_MI_UNSUPPORTED;
  }
}
    break;

  case 20: /* async_class: STRING_LITERAL  */
                            {
  char *text = gdbwire_mi_get_text(yyscanner);
  if (strcmp("download", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_DOWNLOAD;
  } else if (strcmp("stopped", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_STOPPED;
  } else if (strcmp("running", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_RUNNING;
  } else if (strcmp("thread-group-added", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_GROUP_ADDED;
  } else if (strcmp("thread-group-removed", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_GROUP_REMOVED;
  } else if (strcmp("thread-group-started", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_GROUP_STARTED;
  } else if (strcmp("thread-group-exited", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_GROUP_EXITED;
  } else if (strcmp("thread-created", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_CREATED;
  } else if (strcmp("thread-exited", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_EXITED;
  } else if (strcmp("thread-selected", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_THREAD_SELECTED;
  } else if (strcmp("library-loaded", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_LIBRARY_LOADED;
  } else if (strcmp("library-unloaded", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_LIBRARY_UNLOADED;
  } else if (strcmp("traceframe-changed", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_TRACEFRAME_CHANGED;
  } else if (strcmp("tsv-created", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_TSV_CREATED;
  } else if (strcmp("tsv-modified", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_TSV_MODIFIED;
  } else if (strcmp("tsv-deleted", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_TSV_DELETED;
  } else if (strcmp("breakpoint-created", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_BREAKPOINT_CREATED;
  } else if (strcmp("breakpoint-modified", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_BREAKPOINT_MODIFIED;
  } else if (strcmp("breakpoint-deleted", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_BREAKPOINT_DELETED;
  } else if (strcmp("record-started", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_RECORD_STARTED;
  } else if (strcmp("record-stopped", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_RECORD_STOPPED;
  } else if (strcmp("cmd-param-changed", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_CMD_PARAM_CHANGED;
  } else if (strcmp("memory-changed", text) == 0) {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_MEMORY_CHANGED;
  } else {
      (yyval.u_async_class) = GDBWIRE_MI_ASYNC_UNSUPPORTED;
  }
}
    break;

  case 21: /* opt_variable: %empty  */
              {
    (yyval.u_variable) = 0;
}
    break;

  case 22: /* opt_variable: variable EQUAL_SIGN  */
                                  {
    (yyval.u_variable) = (yyvsp[-1].u_variable);
}
    break;

  case 23: /* result_list: result  */
                    {
  (yyval.u_result_list) = gdbwire_mi_result_list_alloc();
  gdbwire_mi_result_list_push_back((yyval.u_result_list), (yyvsp[0].u_result));
}
    break;

  case 24: /* result_list: result_list COMMA result  */
                                      {
  gdbwire_mi_result_list_push_back((yyvsp[-2].u_result_list), (yyvsp[0].u_result));
  (yyval.u_result_list) = (yyvsp[-2].u_result_list);
}
    break;

  case 25: /* result: opt_variable cstring  */
                             {
  (yyval.u_result) = gdbwire_mi_result_alloc();
  (yyval.u_result)->variable = (yyvsp[-1].u_variable);
  (yyval.u_result)->kind = GDBWIRE_MI_CSTRING;
  (yyval.u_result)->variant.cstring = (yyvsp[0].u_cstring);
}
    break;

  case 26: /* result: opt_variable tuple  */
                           {
  (yyval.u_result) = gdbwire_mi_result_alloc();
  (yyval.u_result)->variable = (yyvsp[-1].u_variable);
  (yyval.u_result)->kind = GDBWIRE_MI_TUPLE;
  (yyval.u_result)->variant.result = (yyvsp[0].u_tuple);
}
    break;

  case 27: /* result: opt_variable list  */
                          {
  (yyval.u_result) = gdbwire_mi_result_alloc();
  (yyval.u_result)->variable = (yyvsp[-1].u_variable);
  (yyval.u_result)->kind = GDBWIRE_MI_LIST;
  (yyval.u_result)->variant.result = (yyvsp[0].u_list);
}
    break;

  case 28: /* variable: STRING_LITERAL  */
                         {
  char *text = gdbwire_mi_get_text(yyscanner);
  (yyval.u_variable) = gdbwire_strdup(text);
}
    break;

  case 29: /* cstring: CSTRING  */
                 {
  char *text = gdbwire_mi_get_text(yyscanner);
  (yyval.u_cstring) = gdbwire_mi_unescape_cstring(text);
}
    break;

  case 30: /* tuple: OPEN_BRACE CLOSED_BRACE  */
                               {
  (yyval.u_tuple) = NULL;
}
    break;

  case 31: /* tuple: OPEN_BRACE result_list CLOSED_BRACE  */
                                           {
  (yyval.u_tuple) = (yyvsp[-1].u_result_list)->head;
  free((yyvsp[-1].u_result_list));
}
    break;

  case 32: /* list: OPEN_BRACKET CLOSED_BRACKET  */
                                  {
  (yyval.u_list) = NULL;
}
    break;

  case 33: /* list: OPEN_BRACKET result_list CLOSED_BRACKET  */
                                              {
  (yyval.u_list) = (yyvsp[-1].u_result_list)->head;
  free((yyvsp[-1].u_result_list));
}
    break;

  case 34: /* stream_record: stream_record_class cstring  */
                                           {
  (yyval.u_stream_record) = gdbwire_mi_stream_record_alloc();
  (yyval.u_stream_record)->kind = (yyvsp[-1].u_stream_record_kind);
  (yyval.u_stream_record)->cstring = (yyvsp[0].u_cstring);
}
    break;

  case 35: /* stream_record_class: TILDA  */
                           {
  (yyval.u_stream_record_kind) = GDBWIRE_MI_CONSOLE;
}
    break;

  case 36: /* stream_record_class: AT_SYMBOL  */
                               {
  (yyval.u_stream_record_kind) = GDBWIRE_MI_TARGET;
}
    break;

  case 37: /* stream_record_class: AMPERSAND  */
                               {
  (yyval.u_stream_record_kind) = GDBWIRE_MI_LOG;
}
    break;

  case 38: /* opt_token: %empty  */
           {
  (yyval.u_token) = NULL;	
}
    break;

  case 39: /* opt_token: token  */
                 {
  (yyval.u_token) = (yyvsp[0].u_token);
}
    break;

  case 40: /* token: INTEGER_LITERAL  */
                       {
  char *text = gdbwire_mi_get_text(yyscanner);
  (yyval.u_token) = gdbwire_strdup(text);
}
    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (yyscanner, gdbwire_mi_output, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, yyscanner, gdbwire_mi_output);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yyscanner, gdbwire_mi_output);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (yyscanner, gdbwire_mi_output, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, yyscanner, gdbwire_mi_output);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yyscanner, gdbwire_mi_output);
      YYPOPSTACK (1);
    }
  yyps->yynew = 2;
  goto yypushreturn;


/*-------------------------.
| yypushreturn -- return.  |
`-------------------------*/
yypushreturn:

  return yyresult;
}
#undef gdbwire_mi_nerrs
#undef yystate
#undef yyerrstatus
#undef yyssa
#undef yyss
#undef yyssp
#undef yyvsa
#undef yyvs
#undef yyvsp
#undef yystacksize
/***** End of gdbwire_mi_grammar.c *******************************************/
/***** Begin file gdbwire.c **************************************************/
/**
 * Copyright (C) 2013 Robert Rossi <bob@brasko.net>
 *
 * This file is part of GDBWIRE.
 *
 * GDBWIRE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GDBWIRE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GDBWIRE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

/* #include "gdbwire_assert.h" */
/***** Include gdbwire.h in the middle of gdbwire.c **************************/
/***** Begin file gdbwire.h **************************************************/
/**
 * Copyright (C) 2013 Robert Rossi <bob@brasko.net>
 *
 * This file is part of GDBWIRE.
 *
 * GDBWIRE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GDBWIRE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GDBWIRE.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GDBWIRE_H
#define GDBWIRE_H

#ifdef __cplusplus 
extern "C" { 
#endif 

#include <stdlib.h>
/* #include "gdbwire_result.h" */
/* #include "gdbwire_mi_pt.h" */
/* #include "gdbwire_mi_command.h" */

/* The opaque gdbwire context */
struct gdbwire;

/**
 * The primary mechanism for gdbwire to send events to the caller.
 *
 * The flow is like this:
 * - create a gdbwire instance
 * - loop:
 *   - call gdbwire functions to send commands to gdb
 *   - receive callback events with results when they become available
 * - destroy the instance
 */
struct gdbwire_callbacks {
    /**
     * An arbitrary pointer to associate with the events.
     *
     * This pointer will be passed back to the caller in each event.
     */
    void *context;
    
    /**
     * A console, target or log output event has occured.
     *
     * @param context
     * The context pointer above.
     *
     * @param stream_record
     * The stream record to display to the user.
     */
    void (*gdbwire_stream_record_fn)(void *context,
            struct gdbwire_mi_stream_record *stream_record);

    /**
     * An asynchronous output event.
     *
     * @param context
     * The context pointer above.
     *
     * @param async_record
     * The asychronous record output by GDB.
     */
    void (*gdbwire_async_record_fn)(void *context,
            struct gdbwire_mi_async_record *async_record);

    /**
     * A result output event.
     *
     * @param context
     * The context pointer above.
     *
     * @param result_record
     * The result record output by GDB.
     */
    void (*gdbwire_result_record_fn)(void *context,
            struct gdbwire_mi_result_record *result_record);

    /**
     * A prompt output event.
     *
     * @param context
     * The context pointer above.
     *
     * @param prompt
     * The prompt output to display to the user.
     */
    void (*gdbwire_prompt_fn)(void *context, const char *prompt);

    /**
     * A gdbwire parse error occurred.
     *
     * If you receive this callback, that means the gdbwire parser
     * failed to parse some gdb/mi coming out of gdb.
     * Please send the parameters received in this callback to the
     * gdbwire develpment team.
     *
     * @param context
     * The context pointer above.
     *
     * @param mi
     * The mi string that gdbwire could not parse.
     *
     * @param token
     * The token the error occurred on.
     *
     * @param position
     * The position of the token the error occurred on.
     */
    void (*gdbwire_parse_error_fn)(void *context, const char *mi,
            const char *token, struct gdbwire_mi_position position);
};

/**
 * Create a gdbwire context.
 *
 * Each gdbwire structure is capable of talking to a single gdb instance.
 *
 * @param callbacks
 * The callback functions for when events should be sent. Be sure to
 * initialize all of the callback functions. If a callback event is
 * initialized to NULL, it will not be called.
 *
 * @return
 * A new gdbwire instance or NULL on error.
 */
struct gdbwire *gdbwire_create(struct gdbwire_callbacks callbacks);

/**
 * Destroy a gdbwire context.
 *
 * This function will do nothing if the instance is NULL.
 *
 * @param gdbwire
 * The instance of gdbwire to destroy
 */
void gdbwire_destroy(struct gdbwire *wire);

/**
 * Push some GDB output characters to gdbwire for processing.
 *
 * Currently, the calling application is responsible for reading the
 * output of GDB and sending it to gdbwire. This may change in the future.
 * Call this function with output from GDB when it is available.
 *
 * During this function, callback events may be invoked to alert the
 * caller of useful gdbwire_mi events.
 *
 * @param wire
 * The gdbwire context to operate on.
 *
 * @param data
 * The data to push to gdbwire for interpretation.
 *
 * @param size
 * The size of the data to push to gdbwire.
 *
 * @return
 * GDBWIRE_OK on success or appropriate error result on failure.
 */
enum gdbwire_result gdbwire_push_data(struct gdbwire *wire, const char *data,
        size_t size);

/**
 * Handle an interpreter-exec command.
 *
 * Typically, a front end would start gdb with the MI interface and create
 * a corresponding gdbwire instance. The front end would feed the gdbwire
 * instance all of the MI output. In this scenario, gdbwire triggers
 * callbacks when interesting events occur.
 *
 * Some GDB front ends use the annotate interface with gdb, and will
 * transition to using MI through the use of the interpreter-exec command.
 * In this scenario, the front end will send GDB a single interpreter-exec
 * command and will want to interpret the output of only that command.
 * For this use case, a gdbwire instance is not necessary for the front end,
 * nor any of the callbacks associated with that instance.
 *
 * This function provides a way for a front end to interpret the output
 * of a single interpreter-exec command with out the need for creating
 * a gdbwire instance or any gdbwire callbacks.
 *
 * @param interpreter_exec_output
 * The MI output from GDB for the interpreter exec command.
 *
 * @param kind
 * The interpreter-exec command kind.
 *
 * @param out_mi_command
 * Will return an allocated gdbwire mi command if GDBWIRE_OK is returned
 * from this function. You should free this memory with
 * gdbwire_mi_command_free when you are done with it.
 *
 * @return
 * The result of this function.
 */
enum gdbwire_result gdbwire_interpreter_exec(
        const char *interpreter_exec_output,
        enum gdbwire_mi_command_kind kind,
        struct gdbwire_mi_command **out_mi_command);

#ifdef __cplusplus 
}
#endif 

#endif
/***** End of gdbwire.h ******************************************************/
/***** Continuing where we left off in gdbwire.c *****************************/
/* #include "gdbwire_mi_parser.h" */

struct gdbwire
{
    /* The gdbwire_mi parser. */
    struct gdbwire_mi_parser *parser;

    /* The client callback functions */
    struct gdbwire_callbacks callbacks;
};

static void
gdbwire_mi_output_callback(void *context, struct gdbwire_mi_output *output) {
    struct gdbwire *wire = (struct gdbwire *)context;

    struct gdbwire_mi_output *cur = output;

    while (cur) {
        switch (cur->kind) {
            case GDBWIRE_MI_OUTPUT_OOB: {
                struct gdbwire_mi_oob_record *oob_record =
                    cur->variant.oob_record;
                switch (oob_record->kind) {
                    case GDBWIRE_MI_ASYNC:
                        if (wire->callbacks.gdbwire_async_record_fn) {
                            wire->callbacks.gdbwire_async_record_fn(
                                wire->callbacks.context,
                                    oob_record->variant.async_record);
                        }
                        break;
                    case GDBWIRE_MI_STREAM:
                        if (wire->callbacks.gdbwire_stream_record_fn) {
                            wire->callbacks.gdbwire_stream_record_fn(
                                wire->callbacks.context,
                                    oob_record->variant.stream_record);
                        }
                        break;
                }
                break;
            }
            case GDBWIRE_MI_OUTPUT_RESULT:
                if (wire->callbacks.gdbwire_result_record_fn) {
                    wire->callbacks.gdbwire_result_record_fn(
                        wire->callbacks.context, cur->variant.result_record);
                }
                break;
            case GDBWIRE_MI_OUTPUT_PROMPT:
                if (wire->callbacks.gdbwire_prompt_fn) {
                    wire->callbacks.gdbwire_prompt_fn(
                        wire->callbacks.context, cur->line);
                }
                break;
            case GDBWIRE_MI_OUTPUT_PARSE_ERROR:
                if (wire->callbacks.gdbwire_parse_error_fn) {
                    wire->callbacks.gdbwire_parse_error_fn(
                        wire->callbacks.context, cur->line,
                            cur->variant.error.token,
                                cur->variant.error.pos);
                }
                break;
        }

        cur = cur->next;
    }

    gdbwire_mi_output_free(output);
}

struct gdbwire *
gdbwire_create(struct gdbwire_callbacks callbacks)
{
    struct gdbwire *result = 0;
    
    result = malloc(sizeof(struct gdbwire));
    if (result) {
        struct gdbwire_mi_parser_callbacks parser_callbacks =
            { result,gdbwire_mi_output_callback };
        result->callbacks = callbacks;
        result->parser = gdbwire_mi_parser_create(parser_callbacks);
        if (!result->parser) {
            free(result);
            result = 0;
        }
    }

    return result;
}

void
gdbwire_destroy(struct gdbwire *gdbwire)
{
    if (gdbwire) {
        gdbwire_mi_parser_destroy(gdbwire->parser);
        free(gdbwire);
    }
}

enum gdbwire_result
gdbwire_push_data(struct gdbwire *wire, const char *data, size_t size)
{
    enum gdbwire_result result;
    GDBWIRE_ASSERT(wire);
    result = gdbwire_mi_parser_push_data(wire->parser, data, size);
    return result;
}

struct gdbwire_interpreter_exec_context {
    enum gdbwire_result result;
    enum gdbwire_mi_command_kind kind;
    struct gdbwire_mi_command *mi_command;
};

static void gdbwire_interpreter_exec_stream_record(void *context,
    struct gdbwire_mi_stream_record *stream_record)
{
    struct gdbwire_interpreter_exec_context *ctx =
        (struct gdbwire_interpreter_exec_context*)context;
    ctx->result = GDBWIRE_LOGIC;
}

static void gdbwire_interpreter_exec_async_record(void *context,
    struct gdbwire_mi_async_record *async_record)
{
    struct gdbwire_interpreter_exec_context *ctx =
        (struct gdbwire_interpreter_exec_context*)context;
    ctx->result = GDBWIRE_LOGIC;
}

static void gdbwire_interpreter_exec_result_record(void *context,
    struct gdbwire_mi_result_record *result_record)
{
    struct gdbwire_interpreter_exec_context *ctx =
        (struct gdbwire_interpreter_exec_context*)context;

    if (ctx->result == GDBWIRE_OK) {
        ctx->result = gdbwire_get_mi_command(
            ctx->kind, result_record, &ctx->mi_command);
    }
}

static void gdbwire_interpreter_exec_prompt(void *context, const char *prompt)
{
    struct gdbwire_interpreter_exec_context *ctx =
        (struct gdbwire_interpreter_exec_context*)context;
    ctx->result = GDBWIRE_LOGIC;
}

static void gdbwire_interpreter_exec_parse_error(void *context,
        const char *mi, const char *token, struct gdbwire_mi_position
        position)
{
    struct gdbwire_interpreter_exec_context *ctx =
        (struct gdbwire_interpreter_exec_context*)context;
    ctx->result = GDBWIRE_LOGIC;
}


enum gdbwire_result
gdbwire_interpreter_exec(
        const char *interpreter_exec_output,
        enum gdbwire_mi_command_kind kind,
        struct gdbwire_mi_command **out_mi_command)
{
    struct gdbwire_interpreter_exec_context context = {
            GDBWIRE_OK, kind, 0 };
    size_t len;
    enum gdbwire_result result = GDBWIRE_OK;
    struct gdbwire_callbacks callbacks = {
        &context,
        gdbwire_interpreter_exec_stream_record,
        gdbwire_interpreter_exec_async_record,
        gdbwire_interpreter_exec_result_record,
        gdbwire_interpreter_exec_prompt,
        gdbwire_interpreter_exec_parse_error
    };
    struct gdbwire *wire;

    GDBWIRE_ASSERT(interpreter_exec_output);
    GDBWIRE_ASSERT(out_mi_command);

    len = strlen(interpreter_exec_output);

    wire = gdbwire_create(callbacks);
    GDBWIRE_ASSERT(wire);

    result = gdbwire_push_data(wire, interpreter_exec_output, len);
    if (result == GDBWIRE_OK) {
        /* Honor function documentation,
         * When it returns GDBWIRE_OK - the command will exist.
         * Otherwise it will not. */
        if (context.result == GDBWIRE_OK && !context.mi_command) {
            result = GDBWIRE_LOGIC;
        } else if (context.result != GDBWIRE_OK && context.mi_command) {
            result = context.result;
            gdbwire_mi_command_free(context.mi_command);
        } else {
            result = context.result;
            *out_mi_command = context.mi_command;
        }
    }

    gdbwire_destroy(wire);
    return result;
}
/***** End of gdbwire.c ******************************************************/
