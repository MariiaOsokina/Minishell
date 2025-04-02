#include "minishell.h"

char	**collect_args(t_list **curr)
{
	char	**args;
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = *curr;
	while (tmp && ((t_token *)(tmp->content))->type == WORD)
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	for (count = 0; *curr
		&& ((t_token *)(*curr)->content)->type == WORD; count++)
	{
		args[count] = ft_strdup(((t_token *)(*curr)->content)->value);
		next_token(curr);
	}
	args[count] = NULL;
	return (args);
}

t_ast	*create_exec_node(char **args)
{
	t_ast	*node;

	if (!args)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->cmd = args[0];
	node->args = args;
	node->type = N_EXEC;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	print_top_bottom_ast(t_ast *node, int level)
{
	int	spacing;
	int	i;

	// t_node	*node;
	if (!node)
		return ;
	print_top_bottom_ast(node->right, level += 5);
	if (level == 5)
		printf("\n\n\nTREE VIEW:\n\n");
	spacing = 5;
	level += spacing;
	// Print node type
	if (node->type == N_PIPE)
		printf("%*s[|]\n", level, "");
	else if (node->type == N_EXEC)
	{
		printf("%*s[N_EXEC] (%s)\n", level, "", node->cmd ? node->cmd : "NULL");
		i = 0;
		if (node->args)
		{ while (node->args[i])
			printf("%*s (%s)\n", level, "", node->args[i++]);
		}
		// printf("%*s (%s)\n", level, "", node->args[1]);
	}
	else if (node->type == N_ANDIF)
		printf("%*s[&&]\n\n", level, "");
	else if (node->type == N_OR)
		printf("%*s[||]\n\n", level, "");
	else if (node->type == N_HEREDOC)
		printf("%*s[<<]\n", level, "");
	else if (node->type == N_INF)
		printf("[<]\n");
	else if (node->type == N_OUTF)
		printf("[>]\n");
	else if (node->type == N_APPEND)
		printf("%*s[>>]\n", level, "");
	// Print left subtree
	print_top_bottom_ast(node->left, level += 5);
}
