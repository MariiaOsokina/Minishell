/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:40:25 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/04 15:33:33 by mosokina         ###   ########.fr       */
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

// typedef struct s_shell
// {
// 	t_list *envp;        // Stores environment variables as a linked list.
// 	char **envp_arr;     // Stores environ variables as an array for execve().
// 	t_list *path;        // Stores directories from $PATH in a linked list.
// 	t_list *token_lst;   // Stores parsed command tokens for execution.
// 	char *input;         // Stores the raw command input from the user.
// 	char *trimmed_input; // Stores trimmed input (no leading/trailing spaces).
// 	void *root;          // Root of an AST (Abstract Syntax Tree) for parsing
// 	char *cmd_path;      // Stores the full executable path for a command.
// 	//MO: why we need it?
// 	char *cwd;           // Current working directory
// 	int exit_code;       // Stores the exit code of the last command 
// 	//MO: CHANGE NAME TO EXIT_STATUS?
// 	int fd;              // Stores the file descriptor used for redirections.
// }				t_shell;

// typedef struct s_env
// {
// 	char		*value; //Value
// 	char		*key; //Key
// 	bool		is_export;
// 	bool		is_printed;
// }				t_env;

// /*Types of command nodes*/
// typedef enum e_node_type
// {
// 	N_PIPE,
// 	N_EXEC,
// 	N_ANDIF,
// 	N_OR,
// }				t_node_type;

// typedef struct s_node
// {
// 	t_node_type	type;
// }				t_node;


// /*EXEC*/
// typedef struct s_exec
// {
// 	t_node		type;
// 	char		*command;
// 	char		**av;
// 	t_list		*in_out_list;
// }		t_exec;

// /*PIPES*/
// typedef struct s_pipe
// {
// 	t_node		type;
// 	void		*left;
// 	void		*right;
// 	int			nbr; //just for testing
// }				t_pipe;

// typedef struct s_andif
// {
// 	t_node	type;
// 	void	*left;
// 	void	*right;
// }			t_andif;

// typedef struct s_or
// {
// 	t_node	type;
// 	void	*left;
// 	void	*right;
// }			t_or;

typedef enum e_err_no
{
	ENO_SUCCESS, //0
	ENO_GENERAL, //1
	// ENO_MISUSE_BUILTIN; //2
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND, //127
	ENO_EXEC_255 = 255
}	t_err_no;

/*EXECUTION*/
void	ft_start_execution(t_shell *shell);
int 	ft_exec_node(t_shell *shell, void *node);
int 	ft_exec_andif(t_shell *shell, t_andif *andif_node);
int 	ft_exec_or(t_shell *shell, t_or *or_node);
int 	ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node);
int 	ft_exec_pipe_right(t_shell *shell, t_pipe *pipe_node, int *pipe_fds);
int 	ft_exec_pipe_left(t_shell *shell, t_pipe *pipe_node, int *pipe_fds);
/*execution of simple command*/
int		ft_exec_simple_cmd(t_shell *shell, t_exec *exec_node);
int		ft_exec_external_cmd(t_shell shell, t_exec *exec_node);
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

/*BUILTINS*/
bool 	ft_is_builtin(char *cmd_name);
int		ft_exec_builtin(t_shell *shell, t_exec *exec_node);
// int		ft_strcmp(char *s1, char *s2);

int		ft_builtin_echo(t_shell *shell, t_exec *exec_node);
int		ft_builtin_cd(t_shell *shell, t_exec *exec_node);
int		ft_builtin_export(t_shell *shell, t_exec *exec_node);
int		ft_builtin_unset(t_shell *shell, t_exec *exec_node);
int		ft_builtin_pwd(t_shell *shell, t_exec *exec_node);
int		ft_builtin_env(t_shell *shell, t_exec *exec_node);
int		ft_builtin_exit(t_shell *shell, t_exec *exec_node);

t_env	*ft_get_env(t_shell shell, char *check_key);
void	ft_update_env_value(t_list *envp, char *key, char *new_value);
int 	ft_arr_size(char **arr);

/*envp list utils*/

char	*ft_extract_key(char *str);
char	*ft_extract_value(char *str);
void	*ft_env_lst(t_shell *shell, char **envp);
t_env	*ft_create_env_node(t_shell *shell, char *env);
void	ft_free_env_lst(t_list **envp);
void	ft_print_env_lst(t_list *lst);
void	ft_free_env_node(t_env *envp_node);

/*envp list utils*/
char	*ft_extract_key(char *str);
char	*ft_extract_value(char *str);
void	*ft_env_lst(t_shell *shell, char **envp);
t_env	*ft_create_env_node(t_shell *shell, char *env);
t_env	*ft_dup_env_node(t_shell *shell, char *key, char *value);
void	ft_print_env_lst(t_list *lst); //for testing
void	ft_free_env_node(t_env *envp_node);
void	ft_free_env_lst(t_list **envp);
/*env arr and path list*/
char	**ft_env_arr(t_shell *shell);
void 	ft_free_str_arr(char **arr, int count);
t_list	*ft_path_list(t_shell *shell);
int	ft_get_path(t_shell *shell, t_list **path_list, char *path, int i);



/*HANDLE HEREDOC*/
void 	ft_handle_heredocs(t_shell *shell, void *node);
void		ft_handle_heredocs_pipe(t_shell *shell, t_pipe *pipe);
void		ft_handle_heredocs_andif(t_shell *shell, t_andif *andif);
void		ft_handle_heredocs_or(t_shell *shell, t_or *or);
void		ft_generate_heredocs(t_shell *shell, t_exec *exec_node);
char	*ft_generate_heredoc_name(void);
bool 	ft_is_delimiter_quoted(char *delimiter);
void		ft_fill_heredoc(t_shell *shell, t_in_out *io_here);
char 	*ft_hd_line_expansion(char *hd_line);
void	ft_put_heredoc_line(char *hd_line, int fd_hd, bool quoted);
void	ft_heredoc_expander(char *hd_line, int fd_hd);
bool	ft_is_delimiter(char *delimiter, char *hd_line);
void ft_unlink_heredoc(void *content);


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

int	ft_termios_echoctl(bool echo_ctl_chr);
int	ft_termios_echo(bool echo);



#endif