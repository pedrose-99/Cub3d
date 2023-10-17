/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_same_digit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:50:00 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:51:40 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_same_digit(int *arr, int val, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] != val)
			return (0);
		i++;
	}
	return (1);
}
