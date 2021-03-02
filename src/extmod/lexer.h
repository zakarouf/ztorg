#ifndef ZAKAROUF_LEXER_PROG_H
#define ZAKAROUF_LEXER_PROG_H


struct _TOKEN_ATTR
{
    char *name;
    char *pattern;
    int colorcode;
};

typedef struct _ZAKAROUF_LEXER_Type
{
    char **tokens;
    int *token_attr;
    
    int tokens_size;

}
zakarouf_lexer_t;


#endif
