#include "corewar.h"

void 	set_op_code(t_corewar *core, t_carriage *carriage)
{
	carriage->cur_op = core->field[carriage->PC];
	if (carriage->cur_op <= 16)
		g_op_tab[carriage->cur_op];
}