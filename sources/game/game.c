/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:05:21 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:05:30 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	introduce(t_corewar *core)
{
	t_player	*p;

	ft_putendl("Introducing contestants...");
	p = core->players;
	while (p)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
			p->id, p->header->size, p->header->name, p->header->comment);
		p = p->next;
	}
}

void	do_cycle(t_corewar *core)
{
	t_carriage 	*carriage;

	carriage = core->carriages;
	core->cycles++;
	core->cycles_after_check++;
	while (carriage)
	{
		set_op_if_need(carriage, core);
		carriage->fine -= carriage->fine ? 1 : 0;
		if (carriage->fine == 0)
		{
			if (carriage->op && validate_args(carriage, core))
				carriage->op->invoke(carriage, core);
			carriage->PC += get_shift_to_next_op(carriage);
		}
		carriage = carriage->next;
	}
}

void	start_game(t_corewar *core)
{
	introduce(core);
	while (core->carriage_num)
	{
		if (core->dump_cycle == core->cycles)
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
