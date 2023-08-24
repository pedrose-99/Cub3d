/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:07:08 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/24 11:00:12 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**realloc_matrix(char **matrix, int len)
{
	char	**new_matrix;
	int		i;
	int		prev_len;

	new_matrix = init_matrix(len);
	i = 0;
	prev_len = matrix_len(matrix);
	while (i < prev_len)
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	free(matrix);
	return (new_matrix);
}

char	**init_matrix(int len)
{
	char	**matrix;
	int		i;

	matrix = (char **)malloc(sizeof(char *) * len);
	i = 0;
	while (i < len)
	{
		matrix[i] = NULL;
		i++;
	}
	return (matrix);
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

char	**matrix_cast_charptr(void **matrix)
{
	int		i;
	char	**charptr_matrix;

	i = 0;
	charptr_matrix = (char **)matrix;
	while (charptr_matrix[i])
	{
		charptr_matrix[i] = (char *)matrix;
		i++;
	}
	return (charptr_matrix);
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

char	**new_map(int fd)
{
	t_list	*map_lst;
	char	**map_matrix;
	char	*line;

	line = get_next_line_no_nl(fd);
	map_lst = ft_lstnew((void *)line);
	while (line)
	{
		line = get_next_line_no_nl(fd);
		ft_lstadd_back(&map_lst, ft_lstnew((void *)line));
	}
	printf("Hizo lista\n");
	map_matrix = lst_to_matrix(map_lst);
	free_lst_nodes(map_lst);
	printf("%p\n", &map_lst);
	map_lst = NULL;
	print_matrix(map_matrix);
	printf("Hizo mapa matriz\n");
	return (map_matrix);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s$\n", matrix[i]);
		i++;
	}
}
