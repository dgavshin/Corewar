/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:09:52 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/14 00:30:24 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sfork(t_carriage *carriage, t_corewar *core)
{
	int	address;

	address = read_arg_value(core, carriage, 0);
	core->carriages = duplicate_carriage(carriage, core->carriages,
									address % IDX_MOD);
	core->carriage_num++;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | fork %d (%d)\n",
				carriage->id, address, carriage->pc + (address % IDX_MOD));
}

void	lfork(t_carriage *carriage, t_corewar *core)
{
	int	address;

	address = read_arg_value(core, carriage, 0);
	core->carriages = duplicate_carriage(carriage, core->carriages, address);
	core->carriage_num++;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | lfork %d (%d)\n",
				carriage->id, address, carriage->pc + address);
}
