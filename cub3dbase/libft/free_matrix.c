/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:50:24 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/02 09:54:12 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_matrix(void **matrix)
{
	int	cont;

	cont = 0;
	if (matrix)
	{
		while (matrix[cont])
		{
			free(matrix[cont]);
			cont++;
		}
		free(matrix);
	}
	matrix = NULL;
}
