#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

#include "libft.h"
#include "op.h"

# define ERROR_MAX_PLAYERS 	"The maximum allowed player limit has been "\
							"exceeded. Max value: %s"
# define ERROR_INVALID_FILE "Can't open file \"%s\""
# define ERROR_INVALID_FILE_READ "Can't read from file \"%s\". Expected "\
"number of bytes read: %s"
# define ERROR_INVALID_MAGIC_HEADER	"File \"%s\" has invalid magic header. "\
									"Expected: %s"
# define ERROR_CHAMP_MAX_SIZE 	"File \"%s\" has too large a code (%s bytes > "\
								"%s bytes)"
# define ERROR_DIFF_CHAMP_SIZE "File %s has a code size that differ "\
									"from what its header says"

# define ERROR_MAX_ARGUMENTS "The maximum number of arguments has been reached"
# define ALLOWED_FLAGS "dsvbna"

/*
** Show only essentials
*/
# define V_ESSENTIALS

/*
** Show lives
*/
# define V_LIVES 1

/*
** Show cycles
*/
# define V_CYCLES 2

/*
** Show operations (Params are NOT litteral ...)
*/
# define V_OPERATIONS 4

/*
** Show deaths
*/
# define V_DEATHS 8

/*
** Show PC movements (Except for jumps)
*/
# define V_MOVEMENTS 16

# define MAX_ARGS	11

typedef union				s_register
{

}							t_register;

typedef struct 				s_player
{
	char 					code[CHAMP_MAX_SIZE + 1];
	char 					registers[REG_NUMBER][REG_SIZE * 8];
	struct s_header			*header;
	int 					pos;
	int 					cf;
	int 					id;
}							t_player;

typedef struct 				s_corewar_flags
{
	int 					size;
	int 					dumps_after;
	int 					runs_dumps;
	int 					verbosity;
	int 					aff;
	int 					binary;
	int 					ncurses;
}							t_corewar_flags;

typedef struct				s_corewar
{
	struct s_player			**players;
	struct s_corewar_flags	*flags;
	int 					players_num;
	char 					field[MEM_SIZE];
}							t_corewar;

t_corewar		*parse(int args, char **argv);
void			gexit(char *format, char *f1, char *f2, char *f3);
int 			sfopen(char *path, int flags);
void 			*sfread(int fd, void *buf, size_t nbytes, char *path);

int 			parse_args(int as, char **av, t_corewar_flags **fg,
					 t_list **fl);
/*
** main.c
*/
void			usage(void);

/*
** player.c
*/
t_player		*create_player(int id, t_header *header);
void 			clean_players(t_player **players, int s);

/*
** corewar.c
*/
t_corewar		*init_corewar(t_player **players, int n, t_corewar_flags *f);
void 			clean_corewar(t_corewar *corewar);

/*
** flags.c
*/
int				define_flag(char flag, char *value, t_corewar_flags *flags);
int		 		is_flag(char *arg);
#endif