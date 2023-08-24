/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:50:24 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 11:53:38 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*aux_join(char *s1, char *s2)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	free(s1);
	return (aux);
}
