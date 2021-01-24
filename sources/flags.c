#include "corewar.h"

int		define_flag(char f, char *value, t_corewar_flags *flags)
{
	int stf;
	int	int_value;

	int_value = ft_atoi(value);
	if (f == 'n' || f == 'b' || f == 'a')
	{
		stf = ft_strequ(value, "--stealth");
		flags->ncurses = f == 'n' ? 2 | stf : flags->ncurses;
		flags->binary = f == 'b' ? 2 | stf : flags->binary;
		flags->aff = f == 'a';
		return (0);
	}
	else if (f == 'd' && value && int_value >= 0)
		flags->dumps_after = int_value;
	else if (f == 's' && value && int_value > 0)
		flags->runs_dumps = int_value;
	else if (f == 'v' && value && int_value > 0)
		flags->verbosity = int_value;
	else
		usage();
	return (1);
}

int 	is_flag(char *arg)
{
	return (arg && arg[0] == '-' && ft_strchr(ALLOWED_FLAGS, arg[1]));
}