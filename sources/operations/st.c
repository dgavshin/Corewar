#include "corewar.h"

void	st(t_carriage *carriage, t_corewar *core)
{
	int	source;
	int destination;

	source = read_arg_value(core, carriage, 0);
	if (carriage->types[1] == T_REG)
	{
		destination = read_arg_value(core, carriage, 1);
		carriage->regs[destination - 1] = carriage->regs[source - 1];
	}
	else
	{
		destination = read_int(core, carriage->PC + 3, IND_SIZE);
		write_register(core, carriage->regs[source - 1],
					   carriage->PC + (destination % IDX_MOD), REG_SIZE);
	}
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | st r%d %d\n", carriage->id, source, destination);
}
