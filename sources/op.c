/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:55:53 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/26 21:05:44 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

t_op	g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, &live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4, &ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 0, 1, 4, &st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 4, &add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "subtraction", 1, 1, 4, &sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"and r1, r2, r3   r1&r2 -> r3", 1, 1, 4, &and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"or r1, r2, r3   r1 | r2 -> r3", 1, 1, 4, &or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4, &xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2, &zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 0, 1, 2, &ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 0, 1, 2, sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2, &sfork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4, lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2, lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2, &lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 0, 1, 4, &aff}
};
