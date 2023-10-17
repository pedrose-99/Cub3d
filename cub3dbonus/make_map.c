/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:07:08 by pserrano          #+#    #+#             */
/*   Updated: 2023/10/16 10:40:12 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

char	**new_map(int fd)
{
	t_list	*map_lst;
	char	**map_matrix;
	char	*line;

	line = get_next_line_no_nl(fd);
	while (!*line)
	{
		free(line);
		line = get_next_line_no_nl(fd);
	}
	map_lst = ft_lstnew((void *)line);
	while (line)
	{
		line = get_next_line_no_nl(fd);
		ft_lstadd_back(&map_lst, ft_lstnew((void *)line));
	}
	map_matrix = lst_to_matrix(map_lst);
	free_lst_nodes(map_lst);
	map_lst = NULL;
	return (map_matrix);
}
