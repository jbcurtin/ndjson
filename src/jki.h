#ifndef _jki_h
#define _jki_h

typedef struct {
  unsigned int pos;
  unsigned int toknext;
  int toksuper;
} jki_parser;

typedef enum {
  JKI_INVALID_KEY = -1,
  JKI_NOMEM
} jki_error;

typedef enum {
  JKI_ARRAY_KEY,
  JKI_OBJECT_KEY,
  JKI_NOTSURE
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
  int tok_super;
} jki_token;

jki_error json_key_parse(jki_parser *parser, const char *string,
    size_t len, jki_token *tokens, unsigned int num_tokens);

void jki_init(jki_parser *parser);

#endif

