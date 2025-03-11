#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* env.c & env_utils.c : Env processes */
char	**env_arr(t_shell *shell);
void	print_env_lst(t_list *lst);
void	free_env_lst(t_list *envp);
void	*env_lst(t_shell *shell, char **envp);
t_list	*path_list(t_shell *shell, char **envp);
char	*get_value(t_shell *shell, char *env, char *savedptr);
char	*get_key(t_shell *shell, char *env, char *savedptr);
char	*sh_get_env(t_list *envp, const char *value);
t_env	*create_env_node(t_shell *shell, char **envp);
int		get_path(t_shell *shell, t_list **path_list, char *path, int i);

#endif
