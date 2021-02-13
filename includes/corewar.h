/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:16:34 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 16:21:24 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# include "stdio.h"
# include "libft.h"
# include "op.h"
# include <stdarg.h>

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

# define MAX_ARGS 10

# define OP_CODE_SIZE 1
# define ARG_TYPES_SIZE 1

typedef struct				s_player
{
	unsigned char			code[CHAMP_MAX_SIZE + 1];
	struct s_header			*header;
	struct s_player			*next;
	int						id;
}							t_player;

typedef struct				s_corewar_flags
{
	int						size;
	int						dumps;
	int						verbosity;
	int						aff;
}							t_corewar_flags;

typedef struct				s_carriage
{
	int						cur_opcode;
	int						regs[REG_NUMBER];
	struct s_carriage		*next;
	struct s_player			*player;
	struct s_op				*op;
	int						pc;
	int						id;
	int						fine;
	int						lastlive;
	int						types[3];
	int						cf;
}							t_carriage;

typedef struct				s_corewar
{
	struct s_player			*players;
	struct s_player			*last_alive;
	struct s_carriage		*carriages;
	struct s_corewar_flags	*flags;
	int						players_num;
	int						carriage_num;
	int						cycles_to_die;
	int						cycles;
	unsigned char			field[MEM_SIZE];
	int						lives_num;
	int						checks_num;
	int						cycles_after_check;
}							t_corewar;

typedef struct				s_op
{
	char					name[6];
	char					args;
	char					mod[3];
	char					id;
	int						cost;
	char					description[32];
	char					modifies_carry;
	char					has_types;
	char					dir_size;
	void					(*invoke)(t_carriage*, t_corewar*);
}							t_op;

extern						t_op g_op_tab[16];
extern char					*g_error_max_players;
extern char					*g_error_invalid_file;
extern char					*g_error_invalid_file_read;
extern char					*g_error_invalid_magic_header;
extern char					*g_error_champ_max_size;
extern char					*g_error_diff_champ_size;
extern char					*g_error_small_file;

void						add(t_carriage *carriage, t_corewar *core);
void						aff(t_carriage *carriage, t_corewar *core);
void						and(t_carriage *carriage, t_corewar *core);
void						sfork(t_carriage *carriage, t_corewar *core);
void						ld(t_carriage *carriage, t_corewar *core);
void						ldi(t_carriage *carriage, t_corewar *core);
void						lfork(t_carriage *carriage, t_corewar *core);
void						live(t_carriage *carriage, t_corewar *core);
void						lld(t_carriage *carriage, t_corewar *core);
void						lldi(t_carriage *carriage, t_corewar *core);
void						or(t_carriage *carriage, t_corewar *core);
void						sti(t_carriage *carriage, t_corewar *core);
void						sub(t_carriage *carriage, t_corewar *core);
void						xor(t_carriage *carriage, t_corewar *core);
void						zjmp(t_carriage *carriage, t_corewar *core);
void						st(t_carriage *carriage, t_corewar *core);

t_corewar					*parse(int args, char **argv);
int							sfopen(char *path, int flags);
void						*sfread(int fd, void *buf, size_t nbytes, char *p);
off_t						get_file_size(const char *filename);

/*
** main.c
*/
void						usage(void);

/*
** player.c
*/
t_player					*create_player(t_header *header, t_player *next);
void						clean_players(t_player *player);
void						fill_players_array(t_corewar *core, t_player **p);
t_player					*find_player_by_id(t_corewar *core, int player_id);

/*
** corewar.c
*/
t_corewar					*init_corewar();
void						clean_corewar(t_corewar *corewar);

/*
** flags.c
*/
int							define_flag(char **argv, int idx,
											t_corewar_flags *flags);
t_corewar_flags				*init_flags();
/*
** debug
*/
void						print_field(t_corewar *core);
void						start_game(t_corewar *core);
/*
** game.c
*/

void						print_winner(t_corewar *core);

/*
** carriages.c
*/
t_carriage					*create_carriage(t_player *player, t_carriage *c);
void						clean_carriages(t_carriage *carriage);
void						init_carriages(t_corewar *core);
/*
** operations
*/
void						set_op_if_need(t_carriage *carriage, t_corewar *c);

/*
** field.c
*/
unsigned char				read_byte(t_corewar *core, t_carriage *c, int s);
int							read_int(t_corewar *core, int address, int size);
int							validate_args(t_carriage *carriage, t_corewar *c);
void						write_int(t_corewar *core, int val, int s, int a);

/*
** shift handler
*/
unsigned char				get_shift(t_carriage *carriage, int arg_type);
unsigned char				get_shift_to_next_op(t_carriage *carriage);
unsigned char				get_shift_to_arg(t_carriage *carriage, int idx);

/*
** ./game/op_handler.c
*/
int							read_direct(t_corewar *core, t_carriage *c, int s);
int							read_indirect(t_corewar *core, t_carriage *c, int s,
										int manual_address);
int							read_arg_value(t_corewar *core,
									t_carriage *carriage, int arg_index);
int							round_address(int address);

/*
** game/check.c
*/
void						check_cycles_to_die(t_corewar *core);

/*
** carriages/carriage.c
*/
t_carriage					*duplicate_carriage(t_carriage *carriage,
								t_carriage *next, int address);

void						light_printf(char *format, ...);

/*
** logging.c
*/
void						log_cycle(ssize_t cycle);
void						log_pc_movements(t_corewar *core,
								t_carriage *carriage, int shift);
void						log_cursor_death(t_corewar *core,
								t_carriage *carriage);
void						log_cycles_to_die(ssize_t cycles_to_die);

#endif
