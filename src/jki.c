#include <stdio.h>
#include "jki.h"

#define DELIMITER ,

jki_error json_key_parse(jki_parser *parser, const char *string,
    size_t len, jki_token *tokens, unsigned int num_tokens)
{
  return JKI_INVALID_KEY;
}
void jki_init(jki_parser *parser)
{
  parser->pos = 0;
  parser->toknext = 0;
  parser->toksuper = -1;
}

static jki_token jki_allocate_token(jki_parser *parser,
    jki_token *tokens, size_t num_tokens)
{
  jki_token *token;
  if(parser->toknext >= num_tokens)
  {
    return NULL;
  }
  tok = &tokens[parser->toknext++];
  tok->start = tok->end = -1;
  tok->size = 0;
  tok->type = JKI_NOTSURE;
}

static void jki_fill_token(jki_token *token, jki_key_type type,
    unsigned int start, unsigned int end)
{
  token->type       = type;
  token->start      = start;
  token->end        = end;
  token->size       = 0;
  token->tok_super  = -1;
}

static bool is_integer(const char c)
{
  return false;
}
static bool is_ascii(const char c)
{
  return false;
}
static jki_error parse_hex(const char c)
{

}
jki_error jki_parse(jki_parser *parser, const char *js, size_t len,
    jki_token *tokens, unsigned int num_tokens)
{
  jki_error r;
  int i;
  jki_token *token;
  int count = 0;

  for(; parser->pos < len && js[parser->pos] != '\0'; parser->pos++)
  {
    char c = js[parser->pos];

    if(c == '\"')
    {
      if (tokens == NULL)
      {return 0;}
    }
    token = jki_allocate_token(parser, tokens, num_tokens);
    if (token == NULL)
    {
      parser->pos = start;
      return JKI_NOMEM;
    }
    char c;
    jki_token_type type;

    c = js[parser->pos];

    if (js[parser->pos] >= 48 && js[parser->pos] <=57) /* 0-9*/
    {
    }
    if ( is_integer(c)
    switch (c)
    {
      case is_integer(c):
        break;
      case is_ascii(c):
        break
      case '\\':
        parse_hex
      cast 
      case DELIMITER:
        break
    }
  }
}
