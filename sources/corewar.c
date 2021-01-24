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

t_corewar	*init_corewar(t_player **players, int n_of_players,
						t_corewar_flags *flags)
{
	t_corewar	*corewar;

	corewar = (t_corewar *)ft_memalloc(sizeof(t_corewar));
	corewar->players = players;
	corewar->players_num = n_of_players;
	corewar->flags = flags;
	return (corewar);
}

void		clean_corewar(t_corewar *corewar)
{
	clean_players(corewar->players, corewar->players_num);
	free(corewar->flags);
	free(corewar);
}
