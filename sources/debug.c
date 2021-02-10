/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:04:10 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:07:12 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char g_colors[8][9] = {"\033[0m", "\033[1;37m", "\033[1;34m", "\033[1;35m",
					 "\033[1;36m", "\033[1;33m", "\033[1;32m", "\033[1;31m"};

//void	print_field(t_corewar *core)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	while (i < core->players_num)
//	{
//		j = MEM_SIZE / core->players_num * i;
//		while (j < MEM_SIZE / core->players_num * (i + 1))
//		{
//			if (j % 64 == 0)
//				ft_putchar('\n');
//			ft_putstr(core->field[j] ? g_colors[i + 2 % 8] : g_colors[1]);
//			ft_printf("%02x ", core->field[j]);
//			j++;
//		}
//		ft_putstr(g_colors[0]);
//		i++;
//	}
//	ft_putstr("\n");
//}

inline void	print_last_alive(t_corewar *core)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
			  core->last_alive->id,
			  core->last_alive->header->name);
}

void		print_field(t_corewar *core)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = 0;
		while (j < 32)
		{
			ft_printf("%.2x ", core->field[i + j]);
			j++;
		}
		ft_printf("\n");
		i += 32;
	}
}
