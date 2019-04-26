##
## EPITECH PROJECT, 2017
## 42sh_2017
## File description:
## 42SH
##

SRC_DIR		=	$(realpath src)

SRC_FILES	=	main.c						\
			cut_path.c					\
			display_prompt.c				\
			environement.c					\
			handle_builtin_function.c			\
			mysh.c						\
			run_cmd.c					\
			signal_str.c					\
			run_line.c					\
			parser_set_types.c				\
			parser_set_commands.c				\
			fill_command.c					\
			run_commands.c					\
			destroy_parser.c				\
			redirections.c					\
			my_perror.c					\
			isolate_tokens.c				\
			my_array_index.c				\
			terminal.c					\
			my_strndup.c					\
			alias.c						\
			history.c					\
			globbing.c					\
			reset_parser.c					\
			var_interpreter.c				\
			invalid.c					\
			rc_reader.c					\
			add_elem_to_array.c				\

SRC_DIR_BUILTIN=	$(realpath src/builtin)

SRC_FILES_BUILTIN=	cd_home.c					\
			cd.c						\
			exit.c						\
			set_env.c					\
			alias.c						\
			unset_env.c					\
			echo.c						\
			history.c					\
			builtin.c					\
			set.c						\
			unset.c

SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))		\
			$(addprefix $(SRC_DIR_BUILTIN)/, $(SRC_FILES_BUILTIN))

OBJ		=	$(SRC:%.c=%.o)

NAME		=	42sh

INCLUDE		=	-I include -I lib/my/include

CFLAGS		=	-W -Wall -Wextra -Werror
CFLAGS		+=	$(INCLUDE)

LIB_DIR		=	lib/

LIB_FLAGS	=	-L $(LIB_DIR)my -lmy

LIB		=	$(LIB_DIR)my/libmy.a

CC		=	gcc

all:		$(NAME)

$(NAME):	$(LIB) $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB_FLAGS)

$(LIB):
		$(MAKE) -C $(LIB_DIR)my
		$(MAKE) clean -C $(LIB_DIR)my

clean:
		$(RM) $(OBJ)

gclean:
		$(RM) *.gc*

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

tests_run:
		$(MAKE) -C ./tests
		./tests/test --verbose

debug:		CFLAGS += -g
debug:		re
