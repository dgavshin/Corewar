#include "corewar.h"

void	aff(t_carriage *carriage, t_corewar *core)
{
	unsigned char	byte;
	int				shift;

	shift = ARG_TYPES_SIZE + OP_CODE_SIZE;
	byte = carriage->regs[read_byte(core, carriage, shift)].val[REG_SIZE - 1];
	write(1, &byte, 1);
}
