/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:42:30 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:43:00 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	aff(t_carriage *carriage, t_corewar *core)
{
	int			reg_id;

	reg_id = read_arg_value(core, carriage, 0);
	if (core->flags->aff)
		ft_printf("Aff: %c\n",
			(unsigned char)carriage->regs[reg_id - 1]);
}
