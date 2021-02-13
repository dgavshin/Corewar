/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:06:25 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:10:23 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zjmp(t_carriage *carriage, t_corewar *core)
{
	int address;

	address = read_arg_value(core, carriage, 0);
	if (carriage->cf)
		carriage->pc = round_address(carriage->pc + (address % IDX_MOD));
	carriage->pc = round_address(carriage->pc);
	if (core->flags->verbosity & V_OPERATIONS)
	{
		ft_printf("P %4d | zjmp %d ", carriage->id, address);
		(carriage->cf) ? write(1, "OK\n", 3) : write(1, "FAILED\n", 7);
	}
}
