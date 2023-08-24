/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_strncmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:07:44 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/23 10:26:14 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rev_strncmp(char *s1, char *s2, int n)
{
	int	cont_s1;

	cont_s1 = (int)ft_strlen(s1) - 1;
	while (n >= 0 && (s1[cont_s1] != '\0' || s2[n] != '\0'))
	{
		if (s1[cont_s1] != s2[n])
			return ((unsigned char)s1[cont_s1] - (unsigned char)s2[n]);
		cont_s1--;
		n--;
	}
	return (0);
}
