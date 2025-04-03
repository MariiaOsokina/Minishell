#include "minishell.h"

void	handle_pid1(t_shell *shell, int fd[], t_pipe *pipe_node)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_tree(shell, pipe_node->left);
	exit(0);
}

void	handle_pid2(t_shell *shell, int fd[], t_pipe *pipe_node)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_tree(shell, pipe_node->right);
	exit(0);
}

char	*find_cmd_path(t_shell *shell, t_list *path_list, char cmd)
{
	char	*path;
	char	*only_path;
	t_list	*current;
	char	*path_dir;

	current = path_list;
	if (ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
		return (ft_strdup(cmd));
	if (!cmd || ft_srlen(cmd) == 0 || !ft_strcmp(cmd, ""))
		return (ft_strdup(""));
	while (current != NULL)
	{
		path_dir = (char *)current->content;
		only_path = ft_strjoin(path_dir, "/");
		path = ft_strjoin(only_path, cmd);
		free(only_path);
		if (!path)
			exit_failure(shell, "find_cmd_path");
		if (access(path, F_OK) == 0)
			return (path);
		current = current->next;
	}
	return (ft_strdup(cmd));
}
