/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:07:17 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:06:04 by acyrenna         ###   ########.fr       */
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

void		clean_player(void *content)
{
	t_player	*player;

	player = (t_player *)content;
	ft_memdel((void **) &(player->header));
	ft_memdel((void **) &player);
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
	t_list	*lst;

	lst = ft_memalloc(sizeof(t_list));
	lst->content = player;
	lst->content_size = sizeof(t_player);
	return (lst);
}

t_player *from_list(t_list *lst)
{
	if (lst->content_size == sizeof(t_player))
		return ((t_player *)lst->content);
	return (NULL);
}
