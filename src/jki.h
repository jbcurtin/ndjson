#ifndef _jki_h
#define _jki_h

typedef struct {
  unsigned int pos;
  unsigned int toknext;
  int toksuper;
} jki_parser;

typedef enum {
  JKI_INVALID_KEY         = -1,
  JKI_ERROR_NOMEM         = -2,
  JKI_NOT_SUPPORTED       = -3,
  JKI_ERROR_INVALID_KEY   = -4,
  JKI_ERROR_INVALID_CHAR  = -5
} jki_error;

typedef enum {
  JKI_ARRAY_KEY   = 1,
  JKI_OBJECT_KEY  = 2,
  JKI_NOTSURE     = 3,
} jki_key_type;
/**
 * JSON token Key Description
 *  @param type type(object, array) If array, assume unsigned int. If object, assume char[n]
 *  @param start start position of the key in the string
 *  @param end end position of the key in the string
 *  @param size end - start
 */
typedef struct {
  jki_key_type type;
  int start;
  int end;
  int size;
  unsigned int int_counter;
  int tok_super;
} jki_token;

jki_error jki_parse(jki_parser *parser, const char *string,
    size_t len, jki_token *tokens, unsigned int num_tokens);

void jki_init(jki_parser *parser);

#endif

