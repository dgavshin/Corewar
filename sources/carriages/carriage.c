#include "corewar.h"

t_carriage	*create_carriage(t_player *player, t_carriage *next)
{
	t_carriage	*carriage;

	carriage = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	carriage->player = player;
	carriage->id = player->id;
	carriage->regs[0] = ltor(-((int)carriage->id));
	carriage->lastlive = 0;
	carriage->next = next;
	return (carriage);
}

t_carriage	*duplicate_carriage(t_carriage *carriage, t_carriage *next)
{
	t_carriage	*new;

	new = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memcpy(carriage, new, sizeof(t_carriage));
	new->fine = 0;
	new->next = next;
	return (new);
}

t_carriage	*find_carriage_by_id(t_corewar *core, int carriage_id)
{
	t_carriage	*carriage;

	carriage = core->carriages;
	while (carriage)
	{
		if (carriage->id == carriage_id)
			return (carriage);
		carriage = carriage->next;
	}
	return (NULL);
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