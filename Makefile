# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/16 00:33:00 by acyrenna          #+#    #+#              #
#    Updated: 2021/02/14 00:25:30 by acyrenna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				corewar
OBJS_DIR =			.objects
CC =				cc
CFLAGS =			-g -O3 -Wall -Wextra -Werror

ECHO =				echo
RM =				/bin/rm -rf
NORM =				/usr/bin/fnorm

LIBFT_PATH =		./libft
LIBFT_SRCS =		$(LIBFT_PATH)/sources
LIBFT_LIB =			$(LIBFT_PATH)/libft.a
LIBFT_INCS_DIR =	$(LIBFT_PATH)/includes
LIBFT_HEADERS =		$(LIBFT_INCS_DIR)/ft_printf.h $(LIBFT_INCS_DIR)/libft.h

PROJECT_PATH =		sources/
PROJECT_SRCS =		aff.c carriage.c check.c corewar.c debug.c field.c flags.c \
					fork.c game.c ioutils.c ld.c live.c lld.c logging.c main.c op.c \
					op_handler.c parse.c player.c shift_handler.c st.c ternar.c validate.c zjmp.c

PROJECT_INCS_DIR =	./includes
PROJECT_OBJS =		$(PROJECT_SRCS:%.c=$(PROJECT_OBJS_DIR)/%.o)
PROJECT_OBJS_DIR =	$(OBJS_DIR)
PROJECT_HEADERS =	$(PROJECT_INCS_DIR)/corewar.h $(PROJECT_INCS_DIR)/op.h

PROJECT_HEADERS +=	$(LIBFT_HEADERS)

GREEN_COLOR =		"\033[0;32m"
DEFAULT_COLOR =		"\033[0m"

.PHONY: all clean fclean re norm test

all: check_lib $(NAME)

$(NAME): $(OBJS_DIR) $(LIBFT_LIB) $(PROJECT_OBJS)
	@$(ECHO) "Corewar: " $(GREEN_COLOR) $(NAME) $(DEFAULT_COLOR) "\r"
	@$(CC) $(CFLAGS) $(PROJECT_OBJS) $(LIBFT_LIB) -I$(LIBFT_INCS_DIR) -o $(word 1, $(NAME))

$(OBJS_DIR):
	@mkdir .objects

$(OBJS_DIR)/%.o: $(PROJECT_PATH)%.c $(PROJECT_HEADERS)
	@$(ECHO) "Corewar: " $(GREEN_COLOR) $< $(DEFAULT_COLOR) "\r"
	@$(CC) $(CFLAGS) -c $< -I$(PROJECT_INCS_DIR) -I$(LIBFT_INCS_DIR) -o $@

check_lib:
	@make -sC $(LIBFT_PATH)

clean:
	@make clean -sC $(LIBFT_PATH)
	@$(RM) $(OBJS_DIR)
	@$(RM) peda*

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@$(RM) $(NAME)

re: fclean all

norm:
	@$(NORM) $(addprefix $(PROJECT_PATH),$(PROJECT_SRCS)) \
			 $(PROJECT_HEADERS) $(LIBFT_SRCS)/*
