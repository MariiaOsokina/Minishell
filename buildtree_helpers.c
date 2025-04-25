#include "minishell.h"

t_list	*check_w_args(t_list *tkn_lst, int *args)
{
	if (tkn_lst && ((t_token *)tkn_lst->content)->type == WORD)
	{
		if ((((t_token *)tkn_lst->content)->state == EXPAND)
			&& ft_strlen(((t_token *)tkn_lst->content)->value) == 0)
			return (tkn_lst->next);
		(*args)++;
	}
	return (tkn_lst->next);
}

t_list	*skip_if(t_list *tmp)
{
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tmp = tmp->next;
		if (!check_token(tmp))
			break ;
	}
	return (tmp);
}

t_list	*skip_else(t_list *tmp)
{
	tmp = tmp->next;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tmp = tmp->next;
		if (!check_token(tmp))
			break ;
	}
	return (tmp);
}

t_list	*check_word(t_list **cur, char **av, int *i)
{
	if (*cur && ((t_token *)(*cur)->content)->state == EXPAND
		&& ft_strlen(((t_token *)(*cur)->content)->value) == 0)
	{
		*cur = (*cur)->next;
		return (*cur);
	}
	av[*i] = ((t_token *)(*cur)->content)->value;
	*cur = (*cur)->next;
	(*i)++;
	return (*cur);
}
