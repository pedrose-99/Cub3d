/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:50:24 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/20 10:14:45 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoll(const char *str)
{
	unsigned long long int	result;
	int						sign;
	int						c;

	result = 0;
	sign = 1;
	c = 0;
	while (str[c] == 32 || (str[c] > 8 && str[c] < 14))
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			sign = -1;
		c++;
	}
	while (str[c] > 47 && str[c] < 58)
	{
		result = result * 10 + (str[c] - '0');
		c++;
	}
	return (sign * result);
}
