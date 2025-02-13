##
## EPITECH PROJECT, 2024
## ftp
## File description:
## Makefile
##

SRC	=	./main.c \
\
		./src/init.c \
		./src/server_loop.c \
		./src/client_management.c \
		./src/command_handling.c \
		./src/do_command.c \
\
		./src/commands/commands_utils.c \
		./src/commands/user.c \
		./src/commands/pass.c \
		./src/commands/noop.c \
		./src/commands/help.c \
		./src/commands/quit.c \
		./src/commands/pwd.c \
		./src/commands/cwd.c \
		./src/commands/cdup.c \
		./src/commands/pasv.c \
		./src/commands/port.c \
		./src/commands/list.c \
		./src/commands/retr.c \
		./src/commands/dele.c \
		./src/commands/stor.c \

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS 	=	-Wall -Wextra

CPPFLAGS	=	-iquote ./include

NAME	=	myftp

all:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)


fclean: clean
		$(RM) $(NAME)

debug:	CFLAGS += -g3
debug:	clean all

re:	fclean all

.PHONY:	all clean fclean re
