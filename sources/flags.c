/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:04:21 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:29:40 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				define_flag(char **argv, int index, t_corewar_flags *flags)
{
	char	flag;
	int		int_value;

	flag = *(argv[index] + 1);
	int_value = ft_atoi(argv[index + 1]);
	if (ft_strequ(argv[index], "-dump"))
		flags->dumps = int_value;
	else if (flag == 'a')
	{
		flags->aff = flag == 'a';
		return (0);
	}
	else if (flag == 'v' && int_value > 0)
		flags->verbosity = int_value;
	else
		usage();
	return (1);
}

t_corewar_flags	*init_flags(void)
{
	t_corewar_flags	*flags;

	flags = (t_corewar_flags *)ft_memalloc(sizeof(t_corewar_flags));
	flags->dumps = -1;
	return (flags);
}
