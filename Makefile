NAME		=	philo
HEADER		=	inc/philo.h
SRC			=	src/
OBJ			=	obj/
SRC_FILES	=	main.c \
				init.c \
				input.c \
				monitor.c \
				routine.c \
				safe_func.c \
				time.c \
				utils.c \
				write.c \

#SRCS		=	$(addprefix $(SRC), $(addsuffix, .c, $(SRC_FILES)))
#OBJS		=	$(addprefix $(OBJ), $(addsuffix, .o, $(SRC_FILES)))
#DEPS		=	$(addprefix $(OBJ), $(addsuffix, .d, $(SRC_FILES)))

#SRCS	=	$(wildcard $(SRC)/*.c
#OBJS	=	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
#DEPS	=	$(addsuffix .d, $(basename $(SRCS)))
SRCS		= $(addprefix $(SRC), $(SRC_FILES))
OBJS		= $(addprefix $(OBJ), $(SRC_FILES:.c=.o))
DEPS		= $(addprefix $(OBJ), $(SRC_FILES:.c=.d))
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -MMD #-fsanitize=thread
RM			=	rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ):
	mkdir $@

-include $(DEPS)

clean:
	$(RM) $(OBJ) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : clean fclean re all
