/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:05:21 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:37:18 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_winner(t_corewar *core)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
			ft_abs((int)core->last_alive->id),
			core->last_alive->header->name);
}

void	do_cycle(t_corewar *core)
{
	int			shift;
	t_carriage	*carriage;

	carriage = core->carriages;
	core->cycles++;
	core->cycles_after_check++;
	if (core->flags->verbosity & V_CYCLES)
		log_cycle(core->cycles);
	while (carriage)
	{
		set_op_if_need(carriage, core);
		carriage->fine -= carriage->fine ? 1 : 0;
		if (carriage->fine == 0)
		{
			if (carriage->op && validate_args(carriage, core))
				carriage->op->invoke(carriage, core);
			shift = get_shift_to_next_op(carriage);
			if (core->flags->verbosity & V_MOVEMENTS && shift > 1)
				log_pc_movements(core, carriage, shift);
			carriage->pc = round_address(carriage->pc + shift);
		}
		carriage = carriage->next;
	}
}

void	start_game(t_corewar *core)
{
	while (core->carriage_num)
	{
		if (core->flags->dumps == core->cycles)
		{
			print_field(core);
			exit(0);
		}
		do_cycle(core);
		if (core->cycles_to_die == core->cycles_after_check
			|| core->cycles_to_die <= 0)
			check_cycles_to_die(core);
	}
}
