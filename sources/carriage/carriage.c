#include "corewar.h"

t_carriage	*new_carriage(t_player *player, t_carriage *next)
{
	t_carriage	*carriage;

	carriage = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	carriage->player = player;
	carriage->id = player->id;
	carriage->regs[0].val[3] = carriage->id;
	carriage->lastlive = 0;
	carriage->next = next;
	return (carriage);
}

void 		clean_carriages(t_carriage *carriage)
{
	t_carriage	*tmp;

	while (carriage)
	{
		tmp = carriage->next;
		free(carriage);
		carriage = tmp;
	}
}