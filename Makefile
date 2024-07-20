NAME=minishell

MY_SOURCES= src/prompt/minishell.c				\
			utils/utils.c 						\
			utils/print.c 						\
			utils/lst_new.c						\
			utils/lst_size.c 					\
			utils/utils_two.c 					\
			utils/lstnew_env.c 					\
			src/signal/signal.c					\
			utils/free_struct.c 				\
			src/init/init_env.c					\
			utils/lst_add_back.c 				\
			utils/lstclear_env.c  				\
			src/init/update_shlvl.c				\
			utils/ft_strjoin_utils.c 			\
			src/parsing/parsing_utils.c			\
			src/parsing/expand_arguments.c		\
			src/parsing/parse_redirection.c		\
			src/parsing/parse_command_line.c	\


MY_SOURCES+= utils/test_utils.c  

MY_OBJECTS=$(MY_SOURCES:.c=.o)

white='\033[1;37m'
dark_green='\033[0;32m'

RM=rm -f
CC=cc
FLAGS=-Wall -Werror -Wextra -g

MAKEFLAGS += --no-print-directory

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(MY_OBJECTS)
	@clear
	@$(CC) $(FLAGS) $(MY_OBJECTS) -o $(NAME) -lreadline
	@echo $(dark_green)"\tExecutable is ready\n"


clean: 
	@echo $(light_green)"\t  »»-————　Clean　————-««\n"
	@$(RM) $(MY_OBJECTS) $(MY_TESTER)

fclean: clean
	@$(RM) $(NAME)
	@echo $(white)"\t»»-————　Full clean　————-««\n"

re: fclean all
	@echo $(green_c)"\t   »»-————　Done　————-««"

.PHONY: all clean fclean header re
