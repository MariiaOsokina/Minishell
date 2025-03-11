#ifndef LOGIC_TREE_H
# define LOGIC_TREE_H

# include "structs.h"

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

/*Functions from Ltree*/
void		clean_sublist(t_list *new);
t_list		*get_new_token(t_list *tmp);
t_list		*new_sublist(t_list *t_lst);
bool		is_parenthesis(t_list *t_lst);
t_list		*jump_parenthesis(t_list *tmp);
void		*get_or_subnode(t_shell *shell, void *l_node, t_list *t_lst);
void		*get_pipe_subnode(t_shell *shell, void *l_node, t_list *t_lst);
void		*get_andif_subnode(t_shell *shell, void *l_node, t_list *t_lst);
void		*start_parenthesis(t_shell *shell, t_list *t_lst, void *l_node);

/*Ltree utils*/
int			check_token(t_list *node);
void		ltree_free(void *root);
void		*ltree_print(void *root, int space);

#endif
