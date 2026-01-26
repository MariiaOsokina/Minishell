/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:21 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 14:40:30 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libft/libft.h"
#include <limits.h>
#include <stdbool.h>

/*May require a pointer to cwd and old working dir*/
typedef struct s_shell
{
	t_list	*envp;
	char	**envp_arr;
	t_list	*path;
	t_list	*token_lst;
	char	*input;
	char	*trimmed_input;
	void	*root;
	char	*cmd_path;
	char	*cwd;
	int		exit_code;
	t_list	*heredoc_names;
	bool	in_child;
}				t_shell;

typedef struct s_env
{
	char		*value;
	char		*key;
}				t_env;
