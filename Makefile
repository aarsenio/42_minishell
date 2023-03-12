CC			= 	cc
CFLAGS		= 	-Wall -Wextra -Werror -g -fsanitize=thread #-fsanitize=address
RM			= 	/bin/rm -f
NAME		= 	minishell
INCLUDES	= 	./headers

SRCS		= 	main.c $(shell find src/ -name '*.c')
OBJS		= 	$(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0;32mOBJECT FILES COMPILED\033[0m"
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJS) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -o $(NAME)
	@echo "\033[0;32mMINISHELL IS READY TO USE\033[0m"

clean:
	@$(RM) $(OBJS)
	@echo "\033[0;31mREMOVED OBJECT FILES\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[0;31mREMOVED MINISHELL EXECUTABLE\033[0m"

re: fclean all

norm :
	@norminette -R CheckForbiddenSourceHeader $(SRCS)

m: fclean

e:
	@make re && make clean && clear && valgrind --leak-check=full --track-origins=yes ./minishell
r:
	@make re && make clean && clear && ./minishell

.PHONY: all re clean fclean m
