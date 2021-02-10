#include "corewar.h"

void	sfork(t_carriage *carriage, t_corewar *core)
{
	int address;

	address = read_arg_value(core, carriage, 0);
	core->carriages = create_carriage(carriage->player, core->carriages);
	core->carriages->PC = carriage->PC + (address % IDX_MOD);
	core->carriage_num++;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | fork %d (%d)\n",
				  carriage->id, address, carriage->PC + (address % IDX_MOD));
}
