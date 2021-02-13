/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:05:50 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:53:44 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		map_to_type(int bytes)
{
	if (bytes == REG_CODE)
		return (T_REG);
	else if (bytes == DIR_CODE)
		return (T_DIR);
	else if (bytes == IND_CODE)
		return (T_IND);
	return (0);
}

void	set_arg_types_manual(t_carriage *carriage)
{
	int i;

	i = -1;
	while (++i < carriage->op->args)
		carriage->types[i] = carriage->op->mod[i];
}

int		set_and_validate_arg_types(t_carriage *carriage, t_corewar *core)
{
	int		i;
	int		types;

	if (!carriage->op->has_types)
	{
		set_arg_types_manual(carriage);
		return (1);
	}
	types = core->field[round_address(carriage->pc + 1)];
	carriage->types[0] = map_to_type(types >> 6 & 0x3);
	carriage->types[1] = map_to_type(types >> 4 & 0x3);
	carriage->types[2] = map_to_type(types >> 2 & 0x3);
	i = -1;
	while (++i < carriage->op->args)
		if (!(carriage->op->mod[i] & carriage->types[i]))
			return (0);
	return (1);
}

int		validate_args(t_carriage *carriage, t_corewar *core)
{
	long	value;
	int		shift;
	int		i;

	shift = 2;
	if (!(set_and_validate_arg_types(carriage, core)))
		return (0);
	i = -1;
	while (++i < carriage->op->args)
	{
		if (carriage->types[i] == T_REG)
		{
			value = read_byte(core, carriage, shift);
			if (value <= 0 || value > REG_NUMBER)
				return (0);
		}
		shift += get_shift(carriage, carriage->types[i]);
	}
	return (1);
}
