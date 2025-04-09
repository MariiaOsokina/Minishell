/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:40:25 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/09 12:24:21 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../libft/libft.h"
#include <limits.h>
#include <stdbool.h> //for type bool;

#include <stdio.h>  // for readline()
#include <readline/readline.h> // for readline()
#include <readline/history.h> // for readline()
#include <unistd.h> //functions access(), pipe(), fork(), getpcwd(). chdir()
#include <stdlib.h> // exit ()
#include <wait.h> // for MACROS WIFSIGNALED, WTERMSIG, and WEXITSTATUS 
#include <string.h> // for strerror()
#include <sys/stat.h> // for stat() and stat structure
#include <sys/types.h> // for MACRO S_ISDIR for t_pid
#include <fcntl.h> // for open()
#include <signal.h> //for signal()
#include <sys/ioctl.h> //for iostl function
/*May require a pointer to cwd and old working dir*/
#include <termios.h>

# define HEREDOC_NAME "/tmp/.minishell_heredoc_"
# define MAX_SIZE_HEREDOC 1024

typedef enum e_err_no
{
	ENO_SUCCESS, //0
	ENO_GENERAL, //1
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND, //127
	ENO_EXEC_255 = 255
}	t_err_no;

/*EXECUTION*/
void	ft_start_execution(t_shell *shell);
int 	ft_exec_node(t_shell *shell, void *node);
int 	ft_exec_andif(t_shell *shell, t_andif *andif_node);
int 	ft_exec_or(t_shell *shell, t_or *or_node);
int 	ft_exec_subshell(t_shell *shell, t_op *subshell_node);
int 	ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node);
int 	ft_exec_pipe_right(t_shell *shell, t_pipe *pipe_node, int *pipe_fds);
int 	ft_exec_pipe_left(t_shell *shell, t_pipe *pipe_node, int *pipe_fds);

/*execution of simple command*/
int		ft_exec_simple_cmd(t_shell *shell, t_exec *exec_node);
int		ft_exec_external_cmd(t_shell *shell, t_exec *exec_node);
int		ft_check_access(char *cmd_path); // check the permission to the file, print the error msg and return the error number
bool	ft_cmd_is_dir(char *cmd_path);
char	*ft_get_env_path(t_shell shell, char *cmd_name, t_err_no *err_no);
char	*ft_find_cmd_path(char *cmd_name, t_list *path_list);

/*redirections*/
int		ft_redirections(t_exec *exec_node);
int		ft_redir_inf(t_in_out	*in_out_node);
int		ft_redir_outf(t_in_out	*in_out_node);

/*exec utils*/
int		ft_get_exit_status(int status);
void	ft_err_msg(char *s1, char *s2, char *s3);
void	ft_free_full_shell(t_shell *shell);

/*BUILTINS*/
bool 	ft_is_builtin(char *cmd_name);
int		ft_exec_builtin(t_shell *shell, t_exec *exec_node);

int		ft_builtin_echo(t_shell *shell, t_exec *exec_node);
int		ft_builtin_cd(t_shell *shell, t_exec *exec_node);
int		ft_builtin_export(t_shell *shell, t_exec *exec_node);
int		ft_builtin_unset(t_shell *shell, t_exec *exec_node);
int		ft_builtin_pwd(t_shell *shell, t_exec *exec_node);
int		ft_builtin_env(t_shell *shell, t_exec *exec_node);
int		ft_builtin_exit(t_shell *shell, t_exec *exec_node);
int		ft_builtin_exit_parent(t_shell *shell, t_exec *exec_node, int in, int out);
int		ft_builtin_exit_child(t_shell *shell, t_exec *exec_node);
int		ft_get_exit_code(char *exit_arg);

/*envp list utils*/

void	*ft_env_lst(t_shell *shell, char **envp);
t_env	*ft_create_env_node(t_shell *shell, char *env);
void	ft_free_env_lst(t_list **envp);
void	ft_free_env_node(void *envp);
t_env	*ft_dup_env_node(t_shell *shell, char *key, char *value);
t_env	*ft_get_env_node(t_shell shell, char *target_key);
void	ft_update_env_value(t_list *envp, char *key, char *new_value);

void	ft_print_env_lst(t_list *lst); //for testing

/*env arr and path list*/

char	**ft_env_arr(t_shell *shell, t_list *envp_list);
void 	ft_free_str_arr(char **arr, int count);
int 	ft_arr_size(char **arr);

t_list	*ft_path_list(t_shell *shell);
int		ft_get_path(t_shell *shell, t_list **path_list, char *path, int i);


/*HANDLE HEREDOC*/
void 	ft_process_heredocs(t_shell *shell, void *node);
void	ft_handle_heredocs(t_shell *shell, t_exec *exec_node);
char	*ft_generate_heredoc_name(void);
void	ft_fill_heredoc(t_in_out *io_here);
char 	*ft_hd_line_expansion(char *hd_line);
void	ft_put_heredoc_line(char *hd_line, int fd_hd, bool quoted);
void	ft_heredoc_expander(char *hd_line, int fd_hd);
void	ft_unlink_heredocs(t_list *heredoc_names);

/*move to binary_tree.h*/
t_list	*get_in_out_files(t_shell *shell, t_list *tkn_lst, t_list **in_out_list);
void	print_int_out_files(t_list *in_out_list, int space);
void	free_int_out_list(void *content);
/*move to utils.h*/

void	ft_signals_interactive(void);
void	ft_sigint_interact_handler(int signo);
void	ft_signals_heredoc(void);
void	ft_sigint_heredoc_handler(int signo);
void	ft_signals_noninteractive(void);
void	ft_sigint_siquit_noninteract_handler(int signo);

int		ft_termios_echoctl(bool echo_ctl_chr);
int		ft_termios_echo(bool echo);



#endif