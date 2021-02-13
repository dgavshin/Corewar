/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:01:15 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:45:08 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		introduce(t_corewar *core, t_player **arr)
{
	int			i;
	int			printed;
	t_player	*p;

	ft_putendl("Introducing contestants...");
	i = 0;
	printed = 0;
	while (printed < core->players_num && i < MAX_PLAYERS)
	{
		p = arr[i];
		if (p)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					p->id, p->header->size, p->header->name,
					p->header->comment);
			printed++;
		}
		i++;
	}
}

void		init_carriages(t_corewar *core)
{
	int			i;
	int			j;
	t_player	*p;
	t_player	*players_array[MAX_PLAYERS];
	t_carriage	*carriage;

	carriage = NULL;
	fill_players_array(core, players_array);
	i = 0;
	j = 0;
	while (j < core->players_num)
	{
		p = players_array[i];
		if (p)
		{
			carriage = create_carriage(p, carriage);
			core->carriage_num++;
			carriage->pc = (int)(MEM_SIZE / core->players_num) * j++;
			ft_memcpy(core->field + carriage->pc, p->code, p->header->size);
		}
		i++;
	}
	introduce(core, players_array);
	core->carriages = carriage;
}

t_carriage	*create_carriage(t_player *player, t_carriage *next)
{
	static int	carriage_id;
	t_carriage	*carriage;

	if (!carriage_id)
		carriage_id = 1;
	carriage = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	carriage->player = player;
	carriage->id = carriage_id++;
	carriage->regs[0] = -(player->id);
	carriage->lastlive = 0;
	carriage->next = next;
	return (carriage);
}

t_carriage	*duplicate_carriage(t_carriage *carriage, t_carriage *next,
						int address)
{
	int			i;
	t_carriage	*new;

	new = create_carriage(carriage->player, next);
	i = -1;
	while (++i < REG_NUMBER)
		new->regs[i] = carriage->regs[i];
	new->cf = carriage->cf;
	new->pc = round_address(carriage->pc + address);
	new->lastlive = carriage->lastlive;
	new->fine = 0;
	return (new);
}

void		clean_carriages(t_carriage *carriage)
{
	t_carriage	*tmp;

	while (carriage)
	{
		tmp = carriage->next;
		free(carriage);
		carriage = tmp;
	}
}
