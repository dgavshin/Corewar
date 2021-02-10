#include "corewar.h"

void		write_to_register(t_corewar *core, t_register *reg, int size,
						int addr)
{
	unsigned char i;

	i = 0;
	while (size)
	{
		reg->val[size - 1] = core->field[addr + size - 1 % MEM_SIZE] & 0xFF;
		i += 8;
		size--;
	}
}

void 		write_register(t_corewar *core, t_register reg,
					  unsigned int addr, int size)
{
	int	i;

	i = 0;
	while (size)
	{
		core->field[addr + size - 1 % MEM_SIZE] = reg.val[size - 1] & 0xFF;
		i += 8;
		size--;
	}
}

int			read_int(t_corewar *core, unsigned int address, int size)
{
	int 	sign;
	int		res;

	address %= MEM_SIZE;
	sign = (core->field[address] & 0x80) > 0;
	size = (size - 1) * 8;
	res = 0;
	while (size >= 0)
	{
		if (sign)
			res += (0xff - core->field[address++ % MEM_SIZE]) << size;
		else
			res += core->field[address++ % MEM_SIZE] << size;
		size -= 8;
	}
	if (sign)
		res = ~res;
	return (res);
}

unsigned char 	read_byte(t_corewar *core, t_carriage *carriage, int shift)
{
	return (core->field[carriage->PC + shift]);
}

void	set_op_if_need(t_carriage *carriage, t_corewar *core)
{
	unsigned char opcode;

	if (carriage->fine != 0)
		return ;
	opcode = core->field[carriage->PC % MEM_SIZE];
	if (opcode >= 1 && opcode <= 16)
	{
		carriage->op = &g_op_tab[opcode - 1];
		carriage->fine = carriage->op->cost;
	}
	else
		carriage->op = NULL;
}




