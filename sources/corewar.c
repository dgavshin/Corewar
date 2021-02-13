/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:07:48 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:27:50 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_corewar	*init_corewar(void)
{
	t_corewar	*core;

	core = (t_corewar *)ft_memalloc(sizeof(t_corewar));
	core->cycles_to_die = CYCLE_TO_DIE;
	return (core);
}

void		clean_corewar(t_corewar *corewar)
{
	clean_players(corewar->players);
	clean_carriages(corewar->carriages);
	free(corewar->flags);
	free(corewar);
}
