/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:51:04 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 16:24:38 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		st(t_carriage *carriage, t_corewar *core)
{
	int	source;
	int destination;

	source = read_arg_value(core, carriage, 0);
	if (carriage->types[1] == T_REG)
	{
		destination = read_arg_value(core, carriage, 1);
		carriage->regs[destination - 1] = carriage->regs[source - 1];
	}
	else
	{
		destination = read_int(core, carriage->pc + 3, IND_SIZE);
		write_int(core, carriage->regs[source - 1],
			carriage->pc + (destination % IDX_MOD), REG_SIZE);
	}
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | st r%d %d\n", carriage->id, source, destination);
}

static void	log_sti(t_carriage *carriage, int r_id, int src1, int src2)
{
	ft_printf("P %4d | sti r%d %d %d\n", carriage->id, r_id, src1, src2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			src1, src2, src1 + src2, carriage->pc + ((src1 + src2) % IDX_MOD));
}

void		sti(t_carriage *carriage, t_corewar *core)
{
	int	source;
	int	address;
	int	dest1;
	int	dest2;

	source = read_arg_value(core, carriage, 0);
	dest1 = read_arg_value(core, carriage, 1);
	dest2 = read_arg_value(core, carriage, 2);
	if (carriage->types[1] == T_REG)
		dest1 = carriage->regs[dest1 - 1];
	if (carriage->types[2] == T_REG)
		dest2 = carriage->regs[dest2 - 1];
	address = carriage->pc + ((dest1 + dest2) % IDX_MOD);
	write_int(core, carriage->regs[source - 1], address, REG_SIZE);
	if (core->flags->verbosity & V_OPERATIONS)
		log_sti(carriage, source, dest1, dest2);
}
