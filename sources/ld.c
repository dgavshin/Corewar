/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:43:15 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:50:52 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ld(t_carriage *carriage, t_corewar *core)
{
	int r_idx;
	int	value;

	value = read_arg_value(core, carriage, 0);
	r_idx = read_arg_value(core, carriage, 1);
	carriage->regs[r_idx - 1] = value;
	carriage->cf = (value == 0);
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | ld %d r%d\n", carriage->id, value, r_idx);
}

static void	log_ldi(t_carriage *carriage, int src1, int src2, int r_idx)
{
	ft_printf("P %4d | ldi %d %d r%d\n", carriage->id, src1, src2, r_idx);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			src1, src2, src1 + src2, carriage->pc + (src1 + src2) % IDX_MOD);
}

void		ldi(t_carriage *carriage, t_corewar *core)
{
	int		source1;
	int		source2;
	int		address;
	int		destination;

	source1 = read_arg_value(core, carriage, 0);
	source2 = read_arg_value(core, carriage, 1);
	destination = read_arg_value(core, carriage, 2);
	if (carriage->types[0] == T_REG)
		source1 = carriage->regs[source1 - 1];
	if (carriage->types[1] == T_REG)
		source2 = carriage->regs[source2 - 1];
	address = carriage->pc + ((source1 + source2) % IDX_MOD);
	carriage->regs[destination - 1] = read_int(core, address, REG_SIZE);
	if (core->flags->verbosity & V_OPERATIONS)
		log_ldi(carriage, source1, source2, destination);
}
