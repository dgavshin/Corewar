#include "corewar.h"

static void	log_lldi(t_carriage *carriage,
						int32_t src1,
						int32_t src2,
						int32_t r_idx)
{
	ft_printf("P %4d | lldi %d %d r%d\n", carriage->id, src1, src2, r_idx);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			  src1, src2, src1 + src2, carriage->PC + (src1 + src2));
}


void	lldi(t_carriage *carriage, t_corewar *core)
{
	int source1;
	int source2;
	int address;
	int destination;

	source1 = read_arg_value(core, carriage, 0);
	source2 = read_arg_value(core, carriage, 1);
	destination = read_arg_value(core, carriage, 2);
	if (carriage->types[0] == T_REG && carriage->types[1] == T_REG)
		address = (int) rtol(regop(carriage->regs[source1 - 1],
								   carriage->regs[source2 - 1], &op_add));
	else
	{
		if (carriage->types[0] == T_REG)
			source1 = (int) rtol(carriage->regs[source1 - 1]);
		if (carriage->types[1] == T_REG)
			source2 = (int) rtol(carriage->regs[source2 - 1]);
		address = (source1 + source2);
	}
	write_to_register(core, &carriage->regs[destination - 1], REG_SIZE,
					  address);
	carriage->CF = register_is_null(carriage->regs[destination - 1]);
	if (core->flags->verbosity & V_OPERATIONS)
		log_lldi(carriage, source1, source2, destination);
}
