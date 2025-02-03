/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:43:15 by mosokina          #+#    #+#             */
/*   Updated: 2024/09/13 11:04:59 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	polish_list(t_lst_g	**ptr_list)
{
	t_lst_g	*saved_node;
	t_lst_g	*last_node;
	int		i;
	int		k;
	char	*saved_str;

	saved_str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!saved_str)
		return ;
	saved_node = malloc(sizeof(t_lst_g));
	if (!saved_node)
		return ;
	last_node = find_last_node(*ptr_list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
		saved_str[k++] = last_node->content[i];
	saved_str[k] = '\0';
	saved_node->content = saved_str;
	saved_node->next = NULL;
	dealloc(saved_node, ptr_list, saved_str);
}

void	add_to_list(t_lst_g **ptr_list, char *buf, int fd)
{
	t_lst_g	*new_node;
	t_lst_g	*last_node;

	last_node = find_last_node(ptr_list[fd]);
	new_node = malloc(sizeof(t_lst_g));
	if (!new_node)
		return ;
	if (!last_node)
		ptr_list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

int	create_list(t_lst_g	**ptr_list, int fd)
{
	int		chars_read;
	char	*buf;

	while (!found_newline(ptr_list[fd]))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (0);
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(buf);
			return (-1);
		}
		if (chars_read == 0)
		{
			free(buf);
			return (0);
		}
		buf[chars_read] = '\0';
		add_to_list(ptr_list, buf, fd);
	}
	return (0);
}

char	*get_line(t_lst_g *list)
{
	char	*line_str;
	int		str_len;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	line_str = malloc((sizeof(char) * (str_len +1)));
	if (!line_str)
		return (NULL);
	cpystr_upto_newline(list, line_str);
	return (line_str);
}

char	*get_next_line(int fd)
{
	char				*line_str;
	static t_lst_g		*list_arr[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (create_list(list_arr, fd) < 0)
		return (NULL);
	if (!list_arr[fd])
		return (NULL);
	line_str = get_line(list_arr[fd]);
	polish_list(&list_arr[fd]);
	return (line_str);
}
