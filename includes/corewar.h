#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

#include "stdio.h"
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

# define MAX_ARGS	10

typedef struct				s_register
{
    unsigned char			val[REG_SIZE];
}							t_register;

typedef struct 				s_player
{
	unsigned char 			code[CHAMP_MAX_SIZE + 1];
	struct s_header			*header;
	char					id;
	struct s_player			*next;
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


typedef struct 				s_carriage
{
	struct s_carriage		*next;
	struct s_register		regs[REG_NUMBER];
	struct s_player			*player;
	unsigned char 			lastlive;
	unsigned char			cur_op;
	unsigned char			fine;
	unsigned char			CF;
	unsigned int 			PC;
	char					id;
}							t_carriage;

typedef struct				s_corewar
{
	struct s_player			*players;
	struct s_carriage		*carriages;
	struct s_corewar_flags	*flags;
	int 					players_num;
	int 					last_alive;
	int 					cycles_to_die;
	int 					cycles;
	int 					live_count;
	unsigned char			field[MEM_SIZE];
}							t_corewar;

t_corewar		*parse(int args, char **argv);
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
void			clean_players(t_player *player);
t_player		*get_player(t_corewar *core, int id);
t_list			*to_list(t_player *player);
t_player		*from_list(t_list *lst);

/*
** corewar.c
*/
t_corewar		*init_corewar(t_player *players, int n, t_corewar_flags *f);
void 			clean_corewar(t_corewar *corewar);

/*
** flags.c
*/
int				define_flag(char flag, char *value, t_corewar_flags *flags);
int		 		is_flag(char *arg);

/*
** registers
*/
unsigned long	rtol(t_register r);
t_register		ltor(unsigned long b);
int 			int_representable(t_register r);

t_register		regadd(t_register a, t_register b);
t_register		regsub(t_register a, t_register b);
t_register		regmul(t_register a, long b);
t_register		reglongmul(t_register a, t_register b);


/*
** debug
*/

void			print_field(t_corewar *core);
void			init_game(t_corewar *core);

/*
** game.c
*/
void 			set_op_code(t_corewar *core, t_carriage *carriage);

/*
** carriage.c
*/
t_carriage		*new_carriage(t_player *player, t_carriage *next);
void	 		clean_carriages(t_carriage *carriage);
#endif