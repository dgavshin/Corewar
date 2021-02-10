#include "corewar.h"

void	and(t_carriage *carriage, t_corewar *core)
{
	int 		r1_idx;
	int 		r2_idx;
	int 		r3_idx;
	t_register	r1;
	t_register	r2;

	r1_idx = read_arg_value(core, carriage, 0) - 1;
	r2_idx = read_arg_value(core, carriage, 1) - 1;
	r3_idx = read_arg_value(core, carriage, 2) - 1;
	r1 = carriage->regs[r1_idx];
	r2 = carriage->regs[r2_idx];
	carriage->regs[r3_idx] = regop(r1, r2, &op_and);
	carriage->CF = register_is_null(carriage->regs[r3_idx]);
	if (core->flags->verbosity & V_OPERATIONS)
		ft_printf("P %4d | and r%d r%d r%d\n", carriage->id, r1_idx + 1,
				  r2_idx + 1, r3_idx + 1);
}