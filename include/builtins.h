#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* Builtins.h: Env processes */
void	*env_lst(t_shell *shell, char **envp);
char	*get_value(t_shell *shell, char *env);
char	*get_content(t_shell *shell, char *env);
char	*sh_get_env(t_list *envp, const char *value);
t_env	*create_env_node(t_shell *shell, char **envp);
t_env	*create_env_node(t_shell *shell, char **envp);

#endif
