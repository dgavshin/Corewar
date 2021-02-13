/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:11:40 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 16:24:10 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			log_cycle(ssize_t cycle)
{
	ft_printf("It is now cycle %zd\n", cycle);
}

void			log_pc_movements(t_corewar *core, t_carriage *carriage,
								int shift)
{
	int	i;

	ft_printf("ADV %d (%0.4p -> %0.4p) ",
			shift,
			carriage->pc,
			carriage->pc + shift);
	i = 0;
	while (i < shift)
	{
		ft_printf("%02x ", core->field[round_address(carriage->pc + i)]);
		i++;
	}
	ft_putstr("\n");
}

void			log_cursor_death(t_corewar *core, t_carriage *carriage)
{
	ft_printf("Process %d hasn't lived for %zu cycles (CTD %zd)\n",
			carriage->id,
			core->cycles - carriage->lastlive,
			core->cycles_to_die);
}

void			log_cycles_to_die(ssize_t cycles_to_die)
{
	ft_printf("Cycle to die is now %zd\n", cycles_to_die);
}
