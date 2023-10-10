/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:46 by pserrano          #+#    #+#             */
/*   Updated: 2023/10/04 13:43:32 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

double	degree_to_radians(double degree)
{
	return (degree * (M_PI / 180.0));
}

char	**lst_to_matrix(t_list *lst)
{
	int		i;
	char	**matrix;

	matrix = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		matrix[i] = (char *)lst->content;
		i++;
		lst = lst->next;
	}
	matrix[i] = NULL;
	return (matrix);
}

void	free_lst_nodes(t_list *lst)
{
	t_list	*aux;

	while (lst)
	{
		aux = lst;
		lst = lst->next;
		free(aux);
	}
	lst = NULL;
}
