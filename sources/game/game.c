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

int		has_alive_carriage(t_corewar *core)
{
	t_carriage	*l;

	l = core->carriages;
	while (l)
	{
		/*
		** TODO: Добавить правильное условие
		*/
		if (l->lastlive)
			return (1);
		l = l->next;
	}
	return (0);
}

void	do_cycle(t_corewar *core)
{
	t_carriage 	*carriage;

	carriage = core->carriages;
	while (carriage)
	{
		if (carriage->fine == 0)
			set_op_code(core, carriage);
		if (carriage->fine == 0)
		carriage = carriage->next;
	}
}

void	init_game(t_corewar *core)
{
	introduce(core);
	while (has_alive_carriage(core))
	{
		do_cycle(core);
	}
}

