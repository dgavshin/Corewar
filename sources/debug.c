/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:04:10 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:28:10 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char *g_error_max_players = "The maximum allowed player limit has been "\
"exceeded. Max value: %s";
char *g_error_invalid_file = "Can't open file \"%s\"";
char *g_error_invalid_file_read = "Can't read from file \"%s\". Expected "\
"number of bytes read: %s";
char *g_error_invalid_magic_header = "File \"%s\" has invalid magic header. "\
"Expected: %s";
char *g_error_champ_max_size = "File %s has too large a code (%s bytes > "\
"%s bytes)";
char *g_error_diff_champ_size = "File %s has a code size that differ "\
"from what its header says";
char *g_error_small_file = "File %s is too small to be a champion";

void		print_last_alive(t_corewar *core)
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
