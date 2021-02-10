#include "corewar.h"

void	lfork(t_carriage *carriage, t_corewar *core)
{
	int address;

	address = read_arg_value(core, carriage, 0);
	core->carriages = duplicate_carriage(carriage, core->carriages);
	core->carriages->PC = carriage->PC + address;
	core->carriage_num++;
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | lfork %d (%d)\n", carriage->id, address,
			carriage->PC + address);
}
