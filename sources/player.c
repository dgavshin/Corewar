/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:07:17 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/10 19:08:00 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	*create_player(int id, t_header *header)
{
	t_player *player;

	player = (t_player *)ft_memalloc(sizeof(t_player));
	player->id = id;
	player->header = header;
	return (player);
}

void		clean_players(t_player **players, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(players[i]->header);
		free(players[i++]);
	}
	free(players);
}
