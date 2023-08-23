/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:07:36 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/22 15:07:14 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**new_data_dict(void)
{
	char	**dict;

	dict = (char **)malloc(sizeof(char *) * 7);
	dict[0] = "NO";
	dict[1] = "SO";
	dict[2] = "WE";
	dict[3] = "EA";
	dict[4] = "F";
	dict[5] = "C";
	dict[6] = NULL;
	return (dict);
}

static int	set_data(t_cub3d *cub3d, char *data, char **dict)
{
	int	check;
	int	i;

	check = -1;
	i = 0;
	if (!*data)
		return (0);
	while (dict[i])
	{
		if (!ft_strncmp(data, dict[i], ft_strlen(dict[i])))
		{
			if (i < 4)
				cub3d->textures[i] = set_texture(cub3d, data);
			else
			{
				cub3d->colors[i - 4] = set_color(data);
				if (cub3d->colors[i - 4] < 0)
					return (-1);
			}
			check = i;
			break ;
		}
		i++;
	}
	return (check);
}

int	set_visual_data(t_cub3d *cub3d, int fd)
{
	char	*line;
	char	**dict;
	int		check;
	int		result;

	dict = new_data_dict();
	result = 0;
	line = get_next_line_no_nl(fd);
	while (line && result != 15)
	{
		check = set_data(cub3d, line, dict);
		free(line);
		if (check == -1)
			return (0);
		result += check;
		line = get_next_line_no_nl(fd);
	}
	if (result != 15)
		return (0);
	return (1);
}
