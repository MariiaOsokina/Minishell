#pragma once

/*exec_tree.c*/
void	exec_tree(t_shell *shell, void *root);
void	lexec_tree(t_shell *shell, void *root);
void	exec_pipe(t_shell *shell, t_pipe *pipe_node);
void	*exec_node(t_shell *shell, t_exec *exec_node);

/*For later*/
find_cmd_path(t_shell *shell, t_list *path, char *node);
