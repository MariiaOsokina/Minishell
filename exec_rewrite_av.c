/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rewrite_av.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:27:07 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 13:25:19 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	ft_handle_av(t_shell *shell, t_exec *exec_node);

// void ft_rewrite_array(char **array, int size) {
//     for (int i = 0; i < size; ++i) {
//         char *new_str = ft_strdup(array[i]);
//         if (!new_str) {
//             fprintf(stderr, "Memory allocation failed\n");
//             exit(EXIT_FAILURE);
//         }
//         array[i] = new_str;
//     }
// }

// // static void ft_print_str_arr(char **arr)
// // {
// // 	if (!arr)
// // 	{
// // 		printf("(null array)\n");
// // 		return;
// // 	}

// // 	for (int i = 0; arr[i] != NULL; i++)
// // 	{
// // 		printf("[%d] %s\n", i, arr[i]);
// // 	}
// // }

// static void	ft_process_av_pipe(t_shell *shell, t_pipe *pipe)
// {
// 	if (pipe->left)
// 		ft_process_av(shell, pipe->left);
// 	if (pipe->right)
// 		ft_process_av(shell, pipe->right);
// }

// static void	ft_process_av_andif(t_shell *shell, t_andif *andif)
// {
// 	if (andif->left)
// 		ft_process_av(shell, andif->left);
// 	if (andif->right)
// 		ft_process_av(shell, andif->right);
// }

// static void	ft_process_av_or(t_shell *shell, t_or *or)
// {
// 	if (or->left)
// 		ft_process_av(shell, or->left);
// 	if (or->right)
// 		ft_process_av(shell, or->right);
// }

// void	ft_process_av(t_shell *shell, void *node)
// {
// 	t_node	*type_node;

// 	if (!node)
// 		return ;
// 	type_node = (t_node *)node;
// 	if (type_node->type == N_ANDIF)
// 		ft_process_av_andif(shell, (t_andif *)node);
// 	else if (type_node->type == N_OR)
// 		ft_process_av_or(shell, (t_or *)node);
// 	if (type_node->type == N_PIPE)
// 		ft_process_av_pipe(shell, (t_pipe *)node);
// 	else if (type_node->type == N_EXEC)
// 		ft_handle_av(shell, (t_exec *)node);
// 	return ;
// }

// void	ft_handle_av(t_shell *shell, t_exec *exec_node)
// {
// 	int size;

//     (void)shell;
//     size = ft_arr_size(exec_node->av);
//     ft_rewrite_array(exec_node->av, size);
//     // ft_print_str_arr(exec_node->av); //JUST FOR TESTS
// 	return ;
// }
