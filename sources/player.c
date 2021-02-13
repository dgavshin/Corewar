/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:07:17 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:29:13 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	*create_player(t_header *header, t_player *next)
{
	t_player *player;

	player = (t_player *)ft_memalloc(sizeof(t_player));
	player->header = header;
	player->next = next;
	return (player);
}

void		clean_players(t_player *player)
{
	t_player	*tmp;

	while (player)
	{
		tmp = player->next;
		ft_memdel((void **)&(player->header));
		ft_memdel((void **)&player);
		player = tmp;
	}
}

void		fill_players_array(t_corewar *core, t_player **players_array)
{
	t_player	*player;
	int			i;

	i = 0;
	player = core->players;
	ft_bzero(players_array, sizeof(t_player *) * MAX_PLAYERS);
	while (i < core->players_num && player)
	{
		players_array[player->id - 1] = player;
		player = player->next;
		i++;
	}
}

t_player	*find_player_by_id(t_corewar *core, int player_id)
{
	t_player	*player;

	player = core->players;
	while (player)
	{
		if (player->id == player_id)
			return (player);
		player = player->next;
	}
	return (NULL);
}
