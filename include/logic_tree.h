#ifndef LOGIC_TREE_H
# define LOGIC_TREE_H

# include "binary_tree.h"

typedef struct s_andif
{
	t_node	type;
	void	*left;
	void	*right;
}			t_andif;

typedef struct s_or
{
	t_node	type;
	void	*left;
	void	*right;
}			t_or;

/*ltree_utils.c*/
int			check_token(t_list *node);
void		ltree_free(void *root);
void		*ltree_print(void *root, int space);

/*build_ltree.c*/
void		*build_ltree(t_shell *shell, t_list *token_list);
void		*create_subtree(t_shell *shell, t_list *token_lst);
void		*create_or(t_shell *shell, void *left, void *right);
void		*create_and(t_shell *shell, void *left, void *right);
void		*insert_lnode(t_shell *shell, void *l_node, t_list *t_lst);

/*ltree_parens_utils.c*/
t_list		*get_new_token(t_list *tmp);
t_list		*jump_parenthesis(t_list *tmp);
void		*get_pipe_subnode(t_shell *shell, void *l_node, t_list *t_lst);
void		*start_parenthesis(t_shell *shell, t_list *t_lst, void *l_node);

/*ltree_parenthesis.c*/
void		clean_sublist(t_list *new);
t_list		*new_sublist(t_list *t_lst);
bool		is_parenthesis(t_list *t_lst);
void		*get_or_subnode(t_shell *shell, void *l_node, t_list *t_lst);
void		*get_andif_subnode(t_shell *shell, void *l_node, t_list *t_lst);

#endif
