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
	player->regs[0].val[3] = id;
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

t_player	*get_player(t_corewar *core, int id)
{
	t_player	*player;
	t_list		*lst;

	lst = core->players->head;
	while (lst)
	{
		player = from_list(lst);
		if (player && player->id == id)
			return (player);
		lst = lst->next;
	}
	return (NULL);
}

t_list	*to_list(t_player *player)
{
	return (ft_lstnew(player, sizeof(t_player)));
}

t_player *from_list(t_list *lst)
{
	if (lst->content_size == sizeof(t_player))
		return ((t_player *)lst);
	return (NULL);
}
