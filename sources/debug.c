#include "corewar.h"

char colors[8][9] = {"\033[0m", "\033[1;37m", "\033[1;34m", "\033[1;35m",
					 "\033[1;36m", "\033[1;33m", "\033[1;32m", "\033[1;31m"};

void	print_field(t_corewar *core)
{
	int 	i;
	int 	j;

	i = 0;
	while (i < core->players_num)
	{
		j = MEM_SIZE / core->players_num * i;
		while (j < MEM_SIZE / core->players_num * (i + 1))
		{
			if (j % 64 == 0)
				ft_putchar('\n');
			ft_putstr(core->field[j] ? colors[i + 2 % 8] : colors[1]);
			ft_printf("%02x ", core->field[j]);
			j++;
		}
		ft_putstr(colors[0]);
		i++;
	}
	ft_putstr("\n");
}