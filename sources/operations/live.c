/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:46:33 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:47:18 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live(t_carriage *carriage, t_corewar *core)
{
	int			player_id;
	t_player	*founded;

	player_id = read_arg_value(core, carriage, 0);
	core->lives_num++;
	carriage->lastlive = core->cycles;
	founded = NULL;
	if (player_id <= -1 && player_id >= -((int)core->players_num))
	{
		founded = find_player_by_id(core, ft_abs(player_id));
		if (!founded)
			ft_putstr("");
		core->last_alive = founded;
	}
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | live %d\n", carriage->id, player_id);
	if (core->flags->verbosity & V_LIVES && founded)
		ft_printf("Player %d (%s) is said to be alive\n", ft_abs(player_id),
				founded->header->name);
}
