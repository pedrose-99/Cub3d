/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:23:36 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/01 10:24:35 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_char_num(char *str, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			num++;
		i++;
	}
	return (num);
}
