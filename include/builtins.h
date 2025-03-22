#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*size_utils.c*/
int		key_size(char *env);
int		value_size(char *env);

/* env.c*/
char	**env_arr(t_shell *shell);
void	print_env_lst(t_list *lst);
void	free_env_lst(t_list *envp);
t_list	*path_list(t_shell *shell, char **envp);
int		get_path(t_shell *shell, t_list **path_list, char *path, int i);

/*env_utils.c*/
char	*get_key(t_shell *shell, char *env);
char	*get_value(t_shell *shell, char *env);
void	*env_lst(t_shell *shell, char **envp);
char	*sh_get_env(t_list *envp, const char *value);
t_env	*create_env_node(t_shell *shell, char **envp);
#endif
