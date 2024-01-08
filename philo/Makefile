NAME	=	philo
HEADER	=	inc/philo.h
SRC		=	src
OBJ		=	obj
SRCS	=	$(wildcard $(SRC)/*.c)
OBJS	=	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
DEPS	=	$(addsuffix .d, $(basename $(SRCS)))
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -MMD -pthread
RM		=	rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ):
	mkdir $@

clean:
	$(RM) $(OBJ) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : clean fclean re all
