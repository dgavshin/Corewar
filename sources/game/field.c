/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:11:21 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:41:38 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			write_int(t_corewar *core, int value, int addr, int size)
{
	int	i;

	i = 0;
	while (size)
	{
		core->field[round_address(addr + size - 1)] = ((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int				read_int(t_corewar *core, int address, int size)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = (core->field[round_address(address)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((core->field[round_address(address + size - 1)] ^ 0xFF)
					<< (i++ * 8));
		else
			result += core->field[round_address(address + size - 1)]
					<< (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

unsigned char	read_byte(t_corewar *core, t_carriage *carriage, int shift)
{
	return (core->field[round_address(carriage->pc + shift)]);
}

void			set_op_if_need(t_carriage *carriage, t_corewar *core)
{
	if (carriage->fine != 0)
		return ;
	carriage->cur_opcode = core->field[round_address(carriage->pc)];
	if (carriage->cur_opcode >= 1 && carriage->cur_opcode <= 16)
	{
		carriage->op = &g_op_tab[carriage->cur_opcode - 1];
		carriage->fine = carriage->op->cost;
	}
	else
		carriage->op = NULL;
}
