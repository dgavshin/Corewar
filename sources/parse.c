/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:40:25 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:33:43 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"

static t_player		*parse_file(int fd, char *path, t_player *next)
{
	t_header		*header;
	t_player		*player;
	char			buffer[2048];

	header = (t_header *)ft_memalloc(sizeof(t_header));
	player = create_player(header, next);
	if (get_file_size(path) <= 0x88F)
		gexit(g_error_small_file, path, "", "");
	sfread(fd, buffer, COREWAR_MAGIC_LEN, path);
	if (ft_btol(*(unsigned int *)buffer) != COREWAR_BE_INT_MAGIC)
		gexit(g_error_invalid_magic_header, path, COREWAR_ERR_MAGIC, "");
	sfread(fd, header->name, PROG_NAME_LENGTH, path);
	sfread(fd, buffer, 4, path);
	header->size = ft_btol(*(unsigned int *)sfread(fd, buffer, 4, path));
	sfread(fd, header->comment, COMMENT_LENGTH, path);
	sfread(fd, buffer, 4, path);
	if (header->size > CHAMP_MAX_SIZE)
		gexit(g_error_champ_max_size, path, ft_itoa((int)header->size),
			ft_itoa(CHAMP_MAX_SIZE));
	if (read(fd, player->code, (header->size > CHAMP_MAX_SIZE ? CHAMP_MAX_SIZE
	: header->size)) != header->size || read(fd, buffer, 1) != 0)
		gexit(g_error_diff_champ_size, path, "", "");
	close(fd);
	return (player);
}

static int			parse_player(char **argv, int argc, int idx, t_corewar
						*core)
{
	int is_n_flag;
	int id;

	id = 1;
	is_n_flag = ft_strequ(argv[idx], "-n");
	if (is_n_flag && argc < 3)
		usage();
	if (is_n_flag)
	{
		if ((id = ft_atoi(argv[idx + 1])) < 1 || id > MAX_PLAYERS ||
			find_player_by_id(core, id) != NULL)
			usage();
		idx += 2;
	}
	else if (core->players)
		id = core->players->id + 1;
	core->players = parse_file(
			sfopen(argv[idx], O_RDONLY), argv[idx], core->players);
	core->players->id = id;
	core->players_num++;
	return (is_n_flag ? 2 : 0);
}

static void			parse_args(int args, char **argv, t_corewar *core)
{
	int	code;
	int	i;

	i = 1;
	core->flags = init_flags();
	while (args > 0)
	{
		if (argv[i][0] == '-' && !ft_strequ(argv[i], "-n"))
			code = define_flag(argv, i, core->flags);
		else
			code = parse_player(argv, args, i, core);
		i = i + code + 1;
		args = args - code - 1;
	}
}

t_corewar			*parse(int args, char **argv)
{
	t_corewar		*core;

	core = init_corewar();
	parse_args(args, argv, core);
	if (core->players_num > MAX_PLAYERS)
		gexit(g_error_max_players, ft_itoa(MAX_PLAYERS), "", "");
	if (core->players_num == 0)
		usage();
	init_carriages(core);
	core->last_alive = core->players;
	return (core);
}
