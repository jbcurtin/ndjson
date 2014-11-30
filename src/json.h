#ifndef _json_h
#define _json_h

#include <stddef.h>
#include <stdbool.h>
#include <jsmn.h>

char * json_fetch(char *url);
jsmntok_t * json_tokenise(char *js);
bool json_token_streq(char *js, jsmntok_t *t, char *s);
char * json_token_tostr(char *js, jsmntok_t *t);

#endif
