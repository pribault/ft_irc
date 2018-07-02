/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_del_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:33:15 by pribault          #+#    #+#             */
/*   Updated: 2018/07/02 20:55:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_del_one(t_vector *vector, size_t i)
{
	if (!vector)
		return ;
	if (i + 1 == vector->n)
		ft_vector_resize(vector, i);
	else if (i < vector->n)
	{
		ft_memcpy(vector->ptr + vector->type * i,
		vector->ptr + vector->type * (i + 1),
		vector->type * (vector->n - i - 1));
		vector->n--;
	}
}
