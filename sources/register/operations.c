#include "corewar.h"

t_register	regadd(t_register a, t_register b)
{
	t_register	c;
	int			carry;
	int 		res;
	int			i;

	i = REG_SIZE - 1;
	ft_bzero(&c, sizeof(t_register));
	carry = 0;
	while (i >= 0)
	{
		res = carry + a.val[i] + b.val[i];
		carry = res >= 0xff;
		c.val[i] = res;
		i--;
	}
	return (c);
}

t_register	regsub(t_register a, t_register b)
{
	t_register	c;
	int			carry;
	int 		res;
	int			i;

	i = REG_SIZE - 1;
	ft_bzero(&c, sizeof(t_register));
	carry = 0;
	while (i >= 0)
	{
		res = carry - b.val[i] + a.val[i];
		carry = res < 0;
		c.val[i] = res;
		i--;
	}
	return (c);
}

t_register	regmul(t_register a, long b)
{
	t_register	c;
	long long	carry;
	long long 	res;
	int			i;

	i = REG_SIZE - 1;
	ft_bzero(&c, sizeof(t_register));
	carry = 0;
	while (i >= 0)
	{
		res = carry + a.val[i] * b;
		c.val[i] = (int) res % 0x100;
		carry = res / 0x100;
		i--;
	}
	return (c);
}

t_register	regdiv(t_register a, long b)
{
	t_register	c;
	long long	carry;
	long long 	res;
	int			i;

	i = REG_SIZE - 1;
	ft_bzero(&c, sizeof(t_register));
	carry = 0;
	while (i >= 0)
	{
		res = carry + a.val[i] * 0x100;
		c.val[i] = (int) res / b;
		carry = res % b;
		i--;
	}
	return (c);
}
