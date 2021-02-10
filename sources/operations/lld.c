#include "corewar.h"

void	lld(t_carriage *carriage, t_corewar *core)
{
	int r_idx;
	int	value;

	value = read_arg_value(core, carriage, 0);
	r_idx = read_arg_value(core, carriage, 1);
	carriage->regs[r_idx - 1] = ltor(value);
	carriage->CF = (value == 0);
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | lld %d r%d\n", carriage->id, value, r_idx);
}
