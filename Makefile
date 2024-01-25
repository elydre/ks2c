.PHONY: clean re

SRCS	=	o_src/main.c \
			o_src/fcm.c \
			o_src/tools.c \

OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

NAME	= prog.out

COL_CC	= \033[0;30m
COL_RE	= \033[0m

$(NAME): $(OBJS)
	@echo "$(COL_CC)Linking:	$(NAME)$(COL_RE)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	@echo "$(COL_CC)Compiling:	$<$(COL_RE)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(COL_CC)Cleaning objects...$(COL_RE)"
	@$(RM) o_src/*.o $(NAME)

re:	clean $(NAME)
