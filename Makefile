# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 00:50:07 by jonchoi           #+#    #+#              #
#    Updated: 2022/09/30 02:08:14 by jonchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror


SRC			=	ft_printf			\
				ft_parsing			\
				ft_boxing			\
				ft_print_box		\
				boxing_utils		\
				utils				\
			
SRC_BONUS	=	ft_printf_bonus		\
				ft_parsing_bonus	\
				ft_boxing_bonus		\
				ft_print_box_bonus	\
				boxing_utils_bonus	\
				utils_bonus			\

MAND_DIR	=	./mandatory/
BONUS_DIR	=	./bonus/

SRCS = $(addprefix $(MAND_DIR), $(addsuffix .c, $(SRC)))
SRCS_BONUS = $(addprefix $(BONUS_DIR), $(addsuffix .c, $(SRC_BONUS)))

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all

$(NAME) : $(OBJECTS)
	ar -cr $@ $^

bonus :
	make WITH_BONUS=1 all

.PHONY : all clean fclean re bonus
