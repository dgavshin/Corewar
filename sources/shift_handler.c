/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:15:41 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:40:10 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	get_shift(t_carriage *carriage, int arg_type)
{
	if (arg_type == T_REG)
		return (1);
	else if (arg_type == T_IND)
		return (IND_SIZE);
	else if (arg_type == T_DIR)
		return (carriage->op->dir_size);
	return (0);
}

unsigned char	get_shift_to_next_op(t_carriage *carriage)
{
	int		shift;

	if (!carriage->op)
		return (1);
	if (carriage->op->id == 0x09 && carriage->cf)
		return (0);
	shift = 1 + carriage->op->has_types;
	if (carriage->op->args > 0)
		shift += get_shift(carriage, carriage->types[0]);
	if (carriage->op->args > 1)
		shift += get_shift(carriage, carriage->types[1]);
	if (carriage->op->args > 2)
		shift += get_shift(carriage, carriage->types[2]);
	return (shift);
}

unsigned char	get_shift_to_arg(t_carriage *carriage, int arg_index)
{
	unsigned char	base_shift;
	int				ctr;

	ctr = -1;
	base_shift = OP_CODE_SIZE + carriage->op->has_types;
	while (++ctr < arg_index)
		base_shift += get_shift(carriage, carriage->types[ctr]);
	return (base_shift);
}
