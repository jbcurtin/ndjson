#include <stdio.h>
#include "jki.h"

static jki_token *jki_allocate_token(jki_parser *parser,
    jki_token *tokens, size_t num_tokens)
{
  jki_token *token;
  if(parser->toknext >= num_tokens)
  {
    return NULL;
  }
  token                         = &tokens[parser->toknext++];
  token->start                  = -1;
  token->end                    = -1;
  token->size                   = 0;
  token->int_counter            = 0;
  token->type                   = JKI_NOTSURE;
  return token;
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

jki_error jki_parse(jki_parser *parser, const char *js,
    size_t len, jki_token *tokens, unsigned int num_tokens)
{
  jki_error jki_error;
  jki_token *token;
  jki_key_type jki_type;
  int count = 0;
  int start = 0;

  for(;parser->pos < len && js[parser->pos] != '\0';)
  {
    if (tokens == NULL)
    {
      return count;
    }
    token     = jki_allocate_token(parser, tokens, num_tokens);
    if (token == NULL){
      return JKI_ERROR_NOMEM;
    }
    jki_type  = JKI_ARRAY_KEY;
    for(; parser->pos < len && js[parser->pos] != '\0';)
    {
      char c;
      c = js[parser->pos];
      if(c == ',')
      {
        if(parser->pos == 0){
          return JKI_INVALID_KEY;
        }
        jki_fill_token(token, jki_type, start, parser->pos - 1);
        start             = ++parser->pos;
        count++;
        break;
      } else if (c >= 48 && c <=57)
      {
        // 0-9
        parser->pos++;
        continue;
      } else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
      {
        // a-z && A-Z respectivly
        parser->pos++;
        jki_type          = JKI_OBJECT_KEY;
        continue;
      } else if (c == '\\')
      {
        int i;
        parser->pos++;
        jki_type          = JKI_OBJECT_KEY;
        switch (c)
        {
          case 'u':
            parser->pos++;
            for(i=0; i < 4 && parser->pos < len && js[parser->pos] != '\0'; i++)
            {
              // if none hex
              if(! ((js[parser->pos] >= 48 && js[parser->pos] <= 57) || // 0-9
                    (js[parser->pos] >= 65 && js[parser->pos] <= 70) || // A-F
                    (js[parser->pos] >= 97 && js[parser->pos] <= 102)   // a-f
                   ))
              {
                parser->pos           = start;
                return JKI_ERROR_INVALID_CHAR;
              }
              parser->pos++;
            }
            parser->pos--;
        }
      } else
      {
        return JKI_INVALID_KEY;
      }
    }
  }
  jki_fill_token(token, jki_type, start, parser->pos - 1);
  count++;
  return count;
}

void jki_init(jki_parser *parser)
{
  parser->pos       = 0;
  parser->toknext   = 0;
  parser->toksuper  = -1;
}

