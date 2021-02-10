/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:40:25 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:06:00 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"

static t_player	*parse_file(int fd, int id, char *path)
{
	t_header *header;
	t_player *player;
	char buffer[2048];

	header = (t_header *)ft_memalloc(sizeof(t_header));
	player = create_player(id, header);
	sfread(fd, buffer, COREWAR_MAGIC_LEN, path);
	if (ft_btol(*(unsigned int *) buffer) != COREWAR_BE_INT_MAGIC)
		gexit(ERROR_INVALID_MAGIC_HEADER, path, COREWAR_ERR_MAGIC, "");
	sfread(fd, header->name, PROG_NAME_LENGTH, path);
	sfread(fd, buffer, 4, path);
	header->size = ft_btol(*(unsigned int *) sfread(fd, buffer, 4, path));
	sfread(fd, header->comment, COMMENT_LENGTH, path);
	sfread(fd, buffer, 4, path);
	if (read(fd, player->code, (header->size > CHAMP_MAX_SIZE ? CHAMP_MAX_SIZE
	: header->size)) != header->size || read(fd, buffer, 1) != 0)
		gexit(ERROR_DIFF_CHAMP_SIZE, path, "", "");
	if (header->size > CHAMP_MAX_SIZE)
		gexit(ERROR_CHAMP_MAX_SIZE, path, ft_itoa((int) header->size),
			  ft_itoa(CHAMP_MAX_SIZE));
	close(fd);
	return (player);
}


t_player	*parse_files(t_list *files, int nof)
{
	t_list		*saved;
	t_player	*next;
	t_player	*player;

	saved = files;
	next = NULL;
	while (files)
	{
		player = parse_file(sfopen((char *)files->content, O_RDONLY),
					  (int)nof--, files->content);
		player->next = next;
		next = player;
		files = files->next;
	}
	ft_lstdel(&saved, (void (*)(void *, size_t)) free);
	return (player);
}

int			parse_args(int args, char **argv, t_corewar_flags **flags,
					t_list **files)
{
	int 	num_of_files;
	int		i;

	i = 1;
	num_of_files = 0;
	*flags = (t_corewar_flags *)ft_memalloc(sizeof(t_corewar_flags));
	while (i <= args)
	{
		if (argv[i][0] == '-')
			i += define_flag(argv[i][1], argv[i + 1], *flags);
		else
		{
			*files = ft_lstcreate(*files, argv[i], ft_strlen(argv[i]));
			num_of_files++;
		}
		i++;
	}
	return (num_of_files);
}

t_corewar		*parse(int args, char **argv)
{
	t_corewar_flags	*flags;
	t_list			*files;
	int				number_of_files;

	files = NULL;
	number_of_files = parse_args(args, argv, &flags, &files);
	if (number_of_files > MAX_PLAYERS)
		gexit(ERROR_MAX_PLAYERS, ft_itoa(MAX_PLAYERS), "", "");
	return (init_corewar(parse_files(files, number_of_files),
					  number_of_files, flags));
}
