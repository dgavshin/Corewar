#include "corewar.h"

static void	log_sti(t_carriage *carriage, int r_id, int src1, int src2)
{
	ft_printf("P %4d | sti r%d %d %d\n", carriage->id, r_id, src1, src2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		   src1, src2, src1 + src2, carriage->PC + ((src1 + src2) % IDX_MOD));
}

void	sti(t_carriage *carriage, t_corewar *core)
{
	int	source;
	int address;
	int	dest1;
	int dest2;

	source = read_arg_value(core, carriage, 0);
	dest1 = read_arg_value(core, carriage, 1);
	dest2 = read_arg_value(core, carriage, 2);
	if (carriage->types[1] == T_REG && carriage->types[2] == T_REG)
		address = (int) rtol(regop(carriage->regs[dest1 - 1],
					  carriage->regs[dest2 - 1], &op_add)) % IDX_MOD;
	else
	{
		if (carriage->types[1] == T_REG)
			dest1 = (int) rtol(carriage->regs[dest1 - 1]) % IDX_MOD;
		if (carriage->types[2] == T_REG)
			dest2 = (int) rtol(carriage->regs[dest2 - 1]) % IDX_MOD;
		address = (dest1 + dest2) % IDX_MOD;
	}
	write_register(core, carriage->regs[source - 1], address, REG_SIZE);
	if (core->flags->verbosity & V_OPERATIONS)
		log_sti(carriage, source, dest1, dest2);
}
