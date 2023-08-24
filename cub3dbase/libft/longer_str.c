/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longer_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:53:54 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 11:54:01 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	longer_str(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 > len_s2)
		return (len_s1);
	return (len_s2);
}
