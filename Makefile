# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 23:53:07 by acyrenna          #+#    #+#              #
#    Updated: 2021/01/07 23:53:25 by acyrenna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CMAKEDIR = ./tmp/
LIBDIR = ./libft/

all: $(NAME)

$(NAME): callcmake

callcmake: $(CMAKEDIR) $(CMAKEDIR)Makefile
	$(MAKE) -C $(CMAKEDIR) $(MAKECMDGOALS)

$(CMAKEDIR):
	mkdir -p $(CMAKEDIR)

cmake: $(CMAKEDIR)
	cd $(CMAKEDIR); cmake ../

$(CMAKEDIR)Makefile:
	cd $(CMAKEDIR); cmake ../

clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -r -f $(CMAKEDIR)
	rm -r -f *.dSYM
	rm -r -f $(NAME).debug

fclean:
	$(MAKE) -C $(LIBDIR) fclean
	rm -r -f $(CMAKEDIR)
	rm -r -f $(NAME)
	rm -r -f $(NAME).debug
	rm -r -f *.dSYM

re: fclean
	$(MAKE) all

debug: all

