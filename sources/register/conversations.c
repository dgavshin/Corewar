#include "corewar.h"


t_register	ltor(unsigned long b)
{
	unsigned int	shift;
	int				i;
	t_register		a;

	i = 0;
	shift = 8 * (REG_SIZE - 1);
	ft_bzero(&a, sizeof(t_register));
	while (i < REG_SIZE)
	{
		a.val[i++] = (unsigned char) (b >> shift);
		shift -= 8;
	}
	return (a);
}

unsigned long	rtol(t_register r)
{
	int				i;
	unsigned long	res;

	i = 0;
	res = 0;
	while (i < sizeof(long) && i < REG_SIZE)
	{
		res <<= 8;
		res |= r.val[i++];
	}
	return (res);
}

int int_representable(t_register r)
{
	return (rtol(r) < INT_MAX);
}

