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

# define OP_CODE_SIZE 1
# define ARG_TYPES_SIZE 1

typedef struct				s_register
{
    unsigned char			val[REG_SIZE];
}							t_register;

typedef struct 				s_player
{
	unsigned char 			code[CHAMP_MAX_SIZE + 1];
	struct s_header			*header;
	struct s_player			*next;
	unsigned int			id;
	unsigned int			current_lives;
	unsigned int			previous_lives;
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
	struct s_op				*op;
	unsigned char 			lastlive;
	unsigned char 			types[3];
	unsigned char			fine;
	unsigned char			CF;
	unsigned int 			PC;
	unsigned int			id;
}							t_carriage;

typedef struct				s_corewar
{
	struct s_player			*players;
	struct s_player			*last_alive;
	struct s_carriage		*carriages;
	struct s_corewar_flags	*flags;
	unsigned int			players_num;
	unsigned int			carriage_num;
	unsigned int			cycles_to_die;
	unsigned int			cycles;
	unsigned int			live_count;
	unsigned char			field[MEM_SIZE];
	unsigned int			lives_num;
	unsigned int			checks_num;
	unsigned int			cycles_after_check;
	unsigned int			dump_cycle;
}							t_corewar;

typedef struct				s_op
{
	char					name[6];
	char					args;
	char					mod[3];
	char					id;
	short					cost;
	char					description[32];
	char					modifies_carry;
	char 					has_types;
	char					dir_size;
	void 					(*invoke)(t_carriage*, t_corewar*);
}							t_op;

extern						t_op g_op_tab[16];

void				add(t_carriage *carriage, t_corewar *core);
void				aff(t_carriage *carriage, t_corewar *core);
void				and(t_carriage *carriage, t_corewar *core);
void				sfork(t_carriage *carriage, t_corewar *core);
void				ld(t_carriage *carriage, t_corewar *core);
void				ldi(t_carriage *carriage, t_corewar *core);
void				lfork(t_carriage *carriage, t_corewar *core);
void				live(t_carriage *carriage, t_corewar *core);
void				lld(t_carriage *carriage, t_corewar *core);
void				lldi(t_carriage *carriage, t_corewar *core);
void				or(t_carriage *carriage, t_corewar *core);
void				sti(t_carriage *carriage, t_corewar *core);
void				sub(t_carriage *carriage, t_corewar *core);
void				xor(t_carriage *carriage, t_corewar *core);
void				zjmp(t_carriage *carriage, t_corewar *core);
void				st(t_carriage *carriage, t_corewar *core);

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
long			rtol(t_register r);
t_register		ltor(long b);
int 			int_representable(t_register r);
t_register		regop(t_register a, t_register b, int (*op)(int, int));
t_register		regmul(t_register a, long b);
t_register		reglongmul(t_register a, t_register b);
t_register		regdiv(t_register a, long b);
int				register_is_null(t_register reg);
/*
** debug
*/
void			print_field(t_corewar *core);
void			start_game(t_corewar *core);
/*
** game.c
*/

/*
** carriages.c
*/
t_carriage		*create_carriage(t_player *player, t_carriage *next);
void	 		clean_carriages(t_carriage *carriage);
/*
** operations
*/
void 			set_op_if_need(t_carriage *carriage, t_corewar *core);

/*
** field.c
*/
unsigned char 	read_byte(t_corewar *core, t_carriage *carriage, int shift);
int				read_int(t_corewar *core, unsigned int address, int size);
int 			validate_args(t_carriage *carriage, t_corewar *core);
void			write_int(t_corewar *core, int value, int s, int addr);
void 			write_register(t_corewar *core, t_register reg,
					   unsigned int addr, int size);
void			write_to_register(t_corewar *core, t_register *reg, int size,
							  int addr);
/*
** shift handler
*/
unsigned char 	get_shift(t_carriage *carriage, int arg_type);
unsigned char 	get_shift_to_next_op(t_carriage *carriage);
unsigned char 	get_shift_to_arg(t_carriage *carriage, int arg_index);

/*
** Primitives
*/
int				op_add(int a, int b);
int				op_xor(int a, int b);
int				op_and(int a, int b);
int				op_or(int a, int b);
int				op_sub(int a, int b);

/*
** ./game/op_handler.c
*/
int				read_direct(t_corewar *core, t_carriage *carriage, int shift);
int 			read_indirect(t_corewar *core, t_carriage *carriage, int shift,
							int manual_address);
int 			read_arg_value(t_corewar *core, t_carriage *carriage,
							int arg_index);

/*
** game/check.c
*/
void			check_cycles_to_die(t_corewar *core);

t_carriage		*find_carriage_by_id(t_corewar *core, int carriage_id);
/*
** carriages/carriage.c
*/
t_carriage		*duplicate_carriage(t_carriage *carriage, t_carriage *next);

#endif