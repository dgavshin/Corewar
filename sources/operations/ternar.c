/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:06:17 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:52:27 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_carriage *carriage, t_corewar *core)
{
	int		r1_idx;
	int		r2_idx;
	int		r3_idx;
	int		r1;
	int		r2;

	r1_idx = read_arg_value(core, carriage, 0) - 1;
	r2_idx = read_arg_value(core, carriage, 1) - 1;
	r3_idx = read_arg_value(core, carriage, 2) - 1;
	r1 = carriage->regs[r1_idx];
	r2 = carriage->regs[r2_idx];
	carriage->regs[r3_idx] = r1 + r2;
	carriage->cf = carriage->regs[r3_idx] == 0;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | add r%d r%d r%d\n", carriage->id, r1_idx + 1,
				r2_idx + 1, r3_idx + 1);
}

void	or(t_carriage *carriage, t_corewar *core)
{
	int		v1;
	int		v2;
	int		r3_idx;

	v1 = read_arg_value(core, carriage, 0);
	v2 = read_arg_value(core, carriage, 1);
	r3_idx = read_arg_value(core, carriage, 2) - 1;
	if (carriage->types[0] == T_REG)
		v1 = carriage->regs[v1 - 1];
	if (carriage->types[1] == T_REG)
		v2 = carriage->regs[v2 - 1];
	carriage->regs[r3_idx] = v1 | v2;
	carriage->cf = carriage->regs[r3_idx] == 0;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | or %d %d r%d\n", carriage->id, v1, v2, r3_idx + 1);
}

void	sub(t_carriage *carriage, t_corewar *core)
{
	int		r1_idx;
	int		r2_idx;
	int		r3_idx;
	int		r1;
	int		r2;

	r1_idx = read_arg_value(core, carriage, 0) - 1;
	r2_idx = read_arg_value(core, carriage, 1) - 1;
	r3_idx = read_arg_value(core, carriage, 2) - 1;
	r1 = carriage->regs[r1_idx];
	r2 = carriage->regs[r2_idx];
	carriage->regs[r3_idx] = r1 - r2;
	carriage->cf = carriage->regs[r3_idx] == 0;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | sub r%d r%d r%d\n", carriage->id, r1_idx + 1,
				r2_idx + 1, r3_idx + 1);
}

void	and(t_carriage *carriage, t_corewar *core)
{
	int		v1;
	int		v2;
	int		r3_idx;

	v1 = read_arg_value(core, carriage, 0);
	v2 = read_arg_value(core, carriage, 1);
	r3_idx = read_arg_value(core, carriage, 2) - 1;
	if (carriage->types[0] == T_REG)
		v1 = carriage->regs[v1 - 1];
	if (carriage->types[1] == T_REG)
		v2 = carriage->regs[v2 - 1];
	carriage->regs[r3_idx] = v1 & v2;
	carriage->cf = carriage->regs[r3_idx] == 0;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | and %d %d r%d\n", carriage->id, v1, v2,
				r3_idx + 1);
}

void	xor(t_carriage *carriage, t_corewar *core)
{
	int		v1;
	int		v2;
	int		r3_idx;

	v1 = read_arg_value(core, carriage, 0);
	v2 = read_arg_value(core, carriage, 1);
	r3_idx = read_arg_value(core, carriage, 2) - 1;
	if (carriage->types[0] == T_REG)
		v1 = carriage->regs[v1 - 1];
	if (carriage->types[1] == T_REG)
		v2 = carriage->regs[v2 - 1];
	carriage->regs[r3_idx] = v1 ^ v2;
	carriage->cf = carriage->regs[r3_idx] == 0;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | xor %d %d r%d\n", carriage->id, v1, v2,
				r3_idx + 1);
}
