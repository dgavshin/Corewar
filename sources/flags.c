/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:04:21 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:05:29 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		define_flag(char f, char *value, t_corewar_flags *flags)
{
	int	stf;
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


