/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:00:35 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/10 19:00:45 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_corewar	*init_corewar(t_player *players, int n_of_players,
						t_corewar_flags *flags)
{
	t_carriage	*carriage;
	t_player	*p;
	t_corewar	*core;
	int			i;

	core = (t_corewar *)ft_memalloc(sizeof(t_corewar));
	core->players = players;
	core->players_num = n_of_players;
	core->flags = flags;
	core->cycles_to_die = CYCLE_TO_DIE;
	core->dump_cycle = -1;
	carriage = NULL;
	i = 0;
	p = core->players;
	while (p)
	{
		carriage = create_carriage(p, carriage);
		carriage->PC = (MEM_SIZE / core->players_num) * i++;
		ft_memcpy(core->field + carriage->PC, p->code, p->header->size);
		p = p->next;
	}
	core->carriages = carriage;
	core->carriage_num = i;
	return (core);
}

void		clean_corewar(t_corewar *corewar)
{
	clean_players(corewar->players);
	clean_carriages(corewar->carriages);
	free(corewar->flags);
	free(corewar);
}
