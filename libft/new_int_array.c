/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_int_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:28:37 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/01 10:28:39 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*new_int_array(int len)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * len);
	i = 0;
	while (i < len)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
