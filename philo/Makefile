NAME		= philo
SRCS		= init.c input.c main.c monitor.c routine.c safe_func.c time.c utils.c write.c
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra -MMD -g #-fsanitize=address -pthread
INCLUDES	= inc/philo.h

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS		= $(SRCS:.c=.d)

vpath %.c src

$(OBJ_DIR)/%.o: %.c $(INCLUDES) Makefile
					$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

# rules for cleaning (a phony rule) doesnt have depencies (all: if i dont tell 'make' anything, it will execute the specified rules)
all: make_dir $(NAME)

make_dir:
					@mkdir -p $(OBJ_DIR)

# rule for creating main program
$(NAME): $(OBJS) $(INCLUDES)
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJ_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re make_dir
