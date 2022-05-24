#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
char	**tokenize(char *str);
t_token_list *make_token_list(char **tokens);

enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT
};

typedef struct s_token
{
	char				*str;
	enum e_token_type 	type;
}	t_token;

typedef struct s_token_list
{
	t_token *next;
	t_token token;
}	t_token_list;

typedef struct s_ast_tree_node
{
	t_ast_tree_node*	left;
	t_ast_tree_node*	right;
	t_token				token;
}	t_ast_tree_node;

#endif
