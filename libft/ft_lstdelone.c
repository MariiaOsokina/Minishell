/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:17:06 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/16 18:13:34 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	if (lst == NULL || del == NULL)
		return ;
	(del)(lst->content);
	free (lst);
}
