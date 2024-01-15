NAME			:=	philo

MANDATORY_DIR	:=	philo/

FLAGS			=	-Werror -Wextra -Wall

CC				=	gcc

all:
			@$(MAKE) -C $(MANDATORY_DIR)

$(NAME):
			@$(MAKE) -C $(MANDATORY_DIR)

clean:
			@make clean -sC $(MANDATORY_DIR)

fclean:
			@make fclean -sC $(MANDATORY_DIR)

re:			fclean
			@$(MAKE)

.PHONY:		all clean fclean re norm