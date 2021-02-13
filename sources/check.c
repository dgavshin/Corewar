/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:11:26 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:34:13 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		is_died(t_corewar *core, t_carriage *carriage)
{
	return (core->cycles_to_die <= 0
			|| core->cycles - carriage->lastlive >= core->cycles_to_die);
}

static void		delete_died_carriages(t_corewar *core)
{
	t_carriage	*previous;
	t_carriage	*current;
	t_carriage	*delete;

	previous = NULL;
	current = core->carriages;
	while (current)
		if (is_died(core, (delete = current)) && core->carriage_num--)
		{
			current = current->next;
			if (core->carriages == delete)
				core->carriages = current;
			if (previous)
				previous->next = current;
			if (core->flags->verbosity & V_DEATHS)
				log_cursor_death(core, delete);
			ft_memdel((void **)&delete);
		}
		else
		{
			previous = current;
			current = current->next;
		}
}

void			check_cycles_to_die(t_corewar *core)
{
	core->checks_num++;
	delete_died_carriages(core);
	if (core->checks_num == MAX_CHECKS || core->lives_num >= NBR_LIVE)
	{
		core->cycles_to_die -= CYCLE_DELTA;
		core->checks_num = 0;
		if (core->flags->verbosity & V_CYCLES)
			log_cycles_to_die(core->cycles_to_die);
	}
	core->lives_num = 0;
	core->cycles_after_check = 0;
}
