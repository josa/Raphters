/*
    Copyright (C) 2011 Raphters authors,
    
    This file is part of Raphters.
    
    Raphters is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Raphters is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "regex.h"
#include "stdlib.h"
#include "stdbool.h"

#define GET 1
#define POST 2
#define PUT 3
#define HEAD 4
#define DELETE 5

extern void (*error_handler)(const char *);

struct handler {
    void (*func)(regmatch_t[]);
    int method;
    const char *regex_str;
    regex_t regex;
    size_t nmatch;
    struct handler *next;
    bool regex_set;
};
typedef struct handler handler;

#define START_HANDLER(NAME, METHOD, REGEX, RES, NUM, MATCHES) \
void NAME##_func(); \
 handler NAME##_data = {NAME##_func, METHOD, REGEX, {0}, NUM, NULL, false}; \
handler *NAME = &NAME##_data; \
void NAME##_func(regmatch_t MATCHES[]) { \
    response *int_response = response_empty(); \
    response *RES = int_response;

#define END_HANDLER \
    response_send(int_response); \
}

void dispatch();
void add_handler(handler *);
void cleanup_handlers();

#endif
