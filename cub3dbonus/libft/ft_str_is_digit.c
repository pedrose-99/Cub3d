/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:50:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 10:50:40 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_digit(char *str)
{
	int	cont;

	cont = 0;
	while (str[cont])
	{	
		if (ft_isdigit(str[cont]) == 0)
			return (0);
		cont++;
	}
	return (1);
}
