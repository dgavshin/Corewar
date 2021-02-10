#include "corewar.h"

unsigned char 	get_shift(t_carriage *carriage, int arg_type)
{
	if (arg_type == T_REG)
		return (1);
	if (arg_type == T_IND)
		return (IND_SIZE);
	return (carriage->op->dir_size);
}

unsigned char 	get_shift_to_next_op(t_carriage *carriage)
{
	int shift;

	if (!carriage->op)
		return (1);
	shift = 1 + carriage->op->has_types;
	if (carriage->op->args > 0)
		shift += get_shift(carriage, carriage->types[0]);
	if (carriage->op->args > 1)
		shift += get_shift(carriage, carriage->types[1]);
	if (carriage->op->args > 2)
		shift += get_shift(carriage, carriage->types[2]);
	return (shift);
}

unsigned char 	get_shift_to_arg(t_carriage *carriage, int arg_index)
{
	unsigned char	base_shift;
	int 			ctr;

	ctr = -1;
	base_shift = OP_CODE_SIZE + carriage->op->has_types;
	while (++ctr < arg_index)
		base_shift += get_shift(carriage, carriage->types[ctr]);
	return (base_shift);
}