#include "corewar.h"

void	zjmp(t_carriage *carriage, t_corewar *core)
{
	int address;

	if (!carriage->CF)
	{
		address = read_arg_value(core, carriage, 0);
		carriage->PC = carriage->PC + (address % IDX_MOD);
	}
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | zjmp %d %s\n", carriage->id, address,
			(carriage->CF) ? "OK" : "FAILED");
}
