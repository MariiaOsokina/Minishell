/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:40:25 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/23 11:42:13 by mosokina         ###   ########.fr       */
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
#include <dirent.h>  // opendir, readdir, closedir

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
int		ft_exec_node(t_shell *shell, void *node);
int		ft_exec_andif(t_shell *shell, t_andif *andif_node);
int		ft_exec_or(t_shell *shell, t_or *or_node);
int		ft_exec_subshell(t_shell *shell, t_op *subshell_node);
int		ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node);
void	ft_exec_pipe_right(t_shell *shell, t_pipe *pipe_node, int *pipe_fds);
void	ft_exec_pipe_left(t_shell *shell, t_pipe *pipe_node, int *pipe_fds);

/*execution of simple command*/
int		ft_exec_simple_cmd(t_shell *shell, t_exec *exec_node);
int		ft_exec_external_cmd(t_shell *shell, t_exec *exec_node);
int		ft_check_access(char *cmd_path); // check the permission to the file, print the error msg and return the error number
bool	ft_cmd_is_dir(char *cmd_path);
char	*ft_get_env_path(t_shell shell, char *cmd_name, t_err_no *err_no);
char	*ft_find_cmd_path(char *cmd_name, t_list *path_list);
int		ft_exec_no_cmd(t_shell *shell, t_exec *exec_node);
int		ft_exec_builtins_start(t_shell *shell, t_exec *exec_node);

/*redirections*/
int		ft_redirections(t_shell *shell, t_exec *exec_node);
int		ft_redir_inf(t_shell *shell, t_in_out	*in_out_node);
int		ft_redir_outf(t_shell *shell, t_in_out	*in_out_node);

/*exec utils*/
int		ft_get_exit_status(int status);
void	ft_err_msg(char *s1, char *s2, char *s3);
void	ft_free_full_shell(t_shell *shell);
void	ft_exit_with_full_cleanup(t_shell *shell, int status);


/*BUILTINS*/
bool	ft_is_builtin(char *cmd_name);
int		ft_exec_builtin(t_shell *shell, t_exec *exec_node);

int		ft_builtin_echo(t_shell *shell, t_exec *exec_node);
int		ft_builtin_cd(t_shell *shell, t_exec *exec_node);
int		ft_builtin_export(t_shell *shell, t_exec *exec_node);
int		ft_builtin_unset(t_shell *shell, t_exec *exec_node);
int		ft_builtin_pwd(t_shell *shell, t_exec *exec_node);
int		ft_builtin_env(t_shell *shell, t_exec *exec_node);
int		ft_builtin_exit(t_shell *shell, t_exec *exec_node);
int		ft_exit_child(t_shell *shell, t_exec *exec_node);
int		ft_exit_parent(t_shell *sh, t_exec *exec_node, int in, int out);
int		ft_get_exit_code(char *exit_arg);

/*SHELL ATTRIBUTES*/
/*envp list utils*/

void	*ft_env_lst(t_shell *shell, char **envp);
t_env	*ft_create_env_node(t_shell *shell, char *env);
void	ft_free_env_node(void *envp);
t_env	*ft_dup_env_node(t_shell *shell, char *key, char *value);
t_env	*ft_get_env_node(t_shell shell, char *target_key);
void	ft_update_env_value(t_list *envp, char *key, char *new_value);

void	ft_print_env_lst(t_list *lst); //for testing

/*env arr and path list*/

char	**ft_env_arr(t_shell *shell, t_list *envp_list);
void	ft_free_str_arr(char **arr, int count);
int		ft_arr_size(char **arr);
int		ft_count_str_arr(char **arr);


t_list	*ft_path_list(t_shell *shell);
int		ft_get_path(t_shell *shell, t_list **path_list, char *path, int i);

/*HEREDOC*/
void	ft_process_heredocs(t_shell *shell, void *node);
void	ft_handle_heredocs(t_shell *shell, t_exec *exec_node);
void	ft_fill_heredoc(t_shell *shell, t_in_out *io_here);
char	*ft_generate_heredoc_name(void);
bool	ft_is_delimiter_quoted(char *delimiter);
bool	ft_is_delimiter(char *delimiter, char *hd_line);
void	ft_unlink_heredocs(t_list *heredoc_names);
void	ft_heredoc_unquoted(t_shell *shell, char *hd_line, int hd_fd);

/*EXPANSION*/

void	ft_expand_args(t_shell *shell, t_exec *exec_node);
int		ft_expand_redir_name(t_shell *shell, t_in_out *io_node);
char	*ft_var_expansion(t_shell *shell, char *word);
char	**ft_expand_word_split(char const *word);
size_t 	ft_count_words(const char *word);
// void	ft_delete_empty_arg(t_exec *exec_node);
// void	ft_clean_empty_strs(t_exec *exec_node);

char	*ft_quote_removal(const char *word);
/*wildcards*/
char 	**ft_replace_args(char **old_args, char **new_items, int index);
char 	**ft_get_filenames_arr(const char *pattern, int match_count);
bool	ft_scan_for_asterisk(const char *word);
int		ft_match_count(const char *pattern);


/*move to utils.h*/

/*SIGNALS*/
void	ft_signals_interactive(void);
void	ft_signals_heredoc(void);
void	ft_signals_noninteractive(void);

int		ft_termios_echoctl(bool echo_ctl_chr);
int		ft_termios_echo(bool echo);

/*move to binary_tree.h*/
t_list	*get_in_out_files(t_shell *shell, t_list *tkn_lst, t_list **i_ofiles);
void	print_int_out_files(t_list *i_ofiles, int space);
void	free_int_out_list(void *content);


void	ft_process_av(t_shell *shell, void *node);


#endif