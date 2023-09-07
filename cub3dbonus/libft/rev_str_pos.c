/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_str_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:40:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 09:40:27 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	rev_str_pos(char *str, char c)
{
	int	pos;

	pos = ft_strlen(str);
	while (pos > 0)
	{
		if (str[pos] == c)
			return (pos);
		pos--;
	}
	return (0);
}
