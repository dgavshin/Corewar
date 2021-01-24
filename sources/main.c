/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:41:02 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/10 19:03:36 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

void	usage(void)
{
	ft_putendl(
	"Usage: /corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."
 	" -dump nbr_cycles\n"
  		"\tat the end of nbr_cycles of executions, dump the memory\n"
  		"\ton the standard output and quit the game. The memory will\n"
   		"\tbe dumped in the hexadecimal format with32 octets per line\n"
	"-n number\n"
 	"\tsets the number of the next player. If non-existent, the player\n"
   	"\twill have the next available number in the order of the parameters.\n"
	"\tThe last player will have the first process in the order\n"
  	"of execution.");
	exit(1);
}

void	gexit(char *format, char *f1, char *f2, char *f3)
{
	ft_putstr_fd("\033[1;3;31m", 2);
	ft_putstr_fd("Error: ", 2);
	ft_dprintf(2, format, f1, f2, f3);
	ft_putendl_fd("\033[0m", 2);
	exit(0);
}

int		main(int args, char **argv)
{
	t_corewar	*corewar;

	if (args < 2)
		usage();
	corewar = parse(args - 1, argv);

	ft_printf("flags:\n");
	ft_printf("\t-a: %d\n", corewar->flags->aff);
	ft_printf("\t-s: %d\n", corewar->flags->runs_dumps);
	ft_printf("\t-d: %d\n", corewar->flags->dumps_after);
	ft_printf("\t-b: %d\n", corewar->flags->binary);
	ft_printf("\t-n: %d\n", corewar->flags->ncurses);
	ft_printf("\t-v: %d\n", corewar->flags->verbosity);

	for (int i = 0; i < corewar->players_num; i++)
	{
		ft_printf("%s: %d\n", corewar->players[i]->header->name,
			corewar->players[i]->id);
	}

	clean_corewar(corewar);
	return (0);
}
