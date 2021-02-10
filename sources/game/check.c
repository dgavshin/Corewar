#include "corewar.h"

static void		reset_lives_nums(t_corewar *core)
{
	t_player	*player;

	player = core->players;
	while (player)
	{
		player->previous_lives= player->current_lives;
		player->current_lives = 0;
		player = player->next;
	}
	core->lives_num = 0;
}

static int		is_died(t_corewar *core, t_carriage *carriage)
{
	return (core->cycles_to_die <= 0
			|| core->cycles - carriage->lastlive >= core->cycles_to_die);
}

static void		delete_died_carriages(t_corewar *core)
{
	t_carriage	*previous;
	t_carriage	*current;
	t_carriage	*delete;

	previous = NULL;
	current = core->carriages;
	while (current)
		if (is_died(core, (delete = current)) && core->carriage_num--)
		{
			current = current->next;
			if (core->carriages == delete)
				core->carriages= current;
			if (previous)
				previous->next = current;
//			if (core->log & DEATH_LOG)
//				log_cursor_death(vm, delete);
			ft_memdel((void **)&delete);
		}
		else
		{
			previous = current;
			current = current->next;
		}
}

void			check_cycles_to_die(t_corewar *core)
{
	core->checks_num++;
	delete_died_carriages(core);
	if (core->checks_num == MAX_CHECKS || core->lives_num >= NBR_LIVE)
	{
		core->cycles_to_die -= CYCLE_DELTA;
//		if (vm->log & CYCLE_LOG)
//			log_cycles_to_die(vm->cycles_to_die);
		core->checks_num = 0;
	}
	reset_lives_nums(core);
	core->cycles_after_check = 0;
}