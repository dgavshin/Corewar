/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:06:08 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:06:45 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_register		ltor(long b)
{
	unsigned int	shift;
	int 			sign;
	int				i;
	t_register		a;

	i = 0;
	shift = 8 * (REG_SIZE - 1);
	ft_bzero(&a, sizeof(t_register));
	while (i < REG_SIZE)
	{
		a.val[i++] = (b >> shift);
		shift -= 8;
	}
	return (a);
}

long	rtol(t_register r)
{
	int				i;
	long	res;

	i = 0;
	res = 0;
	while (i < sizeof(long) && i < REG_SIZE)
	{
		res <<= 8;
		res |= r.val[i++];
	}
	return (res);
}

int			register_is_null(t_register reg)
{
	int i;

	i = -1;
	while (++i < REG_SIZE && reg.val[i])
		;
	return (i == REG_SIZE);
}

