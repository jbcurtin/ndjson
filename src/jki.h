#ifndef _token_index_h
#define _token_index_h

typedef enum {
  NGX_INVALID_KEY = -1
} json_parse_error;

/**
 * JSON token Key Description
 *  @param type type(object, array) If array, assume unsigned int. If object, assume char[n]
 *  @param start start position of the key in the string
 *  @param end end position of the key in the string
 *  @param size end - start
 */
typedef struct {
  jsmntype_t type;
  int start;
  int ent;
  int size;
} json_key_index;

json_parse_error json_key_parse(json_index_parser *parser, const char *index_string,
    size_t len, json_key_index *indexes, unsigned int num_indexes);

#endif
