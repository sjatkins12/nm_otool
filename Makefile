# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: satkins <satkins@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 14:05:53 by satkins           #+#    #+#              #
#    Updated: 2018/04/28 15:24:28 by satkins          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm_otool

NM = ft_nm
OTOOL = ft_otool

LIBPATH = libft/
LIBFT = libftprintf.a

CC = gcc

FLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -c

################################################################################
# SOURCE FILES                                                                 #
################################################################################

SRC_NM =  \
		ft_nm \
		symbols
SRC_OTOOL = \
		ft_otool
SRC_UTILS = \
		lex_compare \
		open_file \
		validate_file

################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR_NM = src/nm/
SRCDIR_OTOOL = src/otool/
SRCDIR_UTILS = src/utils/

NMSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_NM), $(SRC_NM)))
NMSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_UTILS), $(SRC_UTILS)))
OTOOLSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_OTOOL), $(SRC_OTOOL)))

################################################################################
# INCLUDE PATHS                                                                #
################################################################################

INCLUDES = \
		-I libft/inc \
		-I inc

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(NMSRC)
	@ echo "$(YELLOW)Compiling programs$(RES)"
	@$(CC) $(FLAGS) -L $(LIBPATH) -lftprintf $(INCLUDES) $(NMSRC) -o $(NM)
	#@$(CC) $(FLAGS) -L $(LIBPATH) -lftprintf $(INCLUDES) $(OTOOLSRC) -o $(OTOOL)
	@echo "$(GREEN)Binaries Compiled$(RES)"


$(LIBFT):
	@make -C $(LIBPATH)

%.o: %.c
	@ echo "$(YELLOW)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: CFLAGS += -g -DDEBUG
debug: clean $(NAME)

clean:
	rm -f $(OBJSRC)
	@make -C $(LIBPATH) clean
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so
	@make -C $(LIBPATH) fclean
	@ echo "$(RED)Removing library file and binary...$(RES)"

re: fclean all
	@ echo "$(GREEN)Binary Remade$(RES)"
