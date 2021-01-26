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

void	set_code(t_corewar *core)
{
	t_player	*p;
	t_list		*lst;
	int			i;

	i = 0;
	lst = core->players->head;
	while (lst)
	{
		p = from_list(lst);
		p->pos = (MEM_SIZE / core->players_num) * i++;
		ft_memcpy(core->field + p->pos, p->code, p->header->size);
		lst = lst->next;
	}
}

void	init_game(t_corewar *core)
{
	set_code(core);
}

void	do_cycle(t_corewar *core)
{
	/*
	** set_op_code();
	*/
}
