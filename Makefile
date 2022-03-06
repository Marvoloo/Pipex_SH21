NAME = pipex

BNAME = pipex_bonus

HEADERS = pipex.h get_next_line.h

SRCS = split.c lib_utils.c pipex.c utils.c findqoutes.c joinarg.c remqoutes.c getpath.c error.c

BSRCS = split.c lib_utils.c lib_utils_bonus.c pipex_bonus.c utils.c utils_bonus.c get_next_line.c findqoutes.c joinarg.c remqoutes.c getpath.c error.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSRCS:%.c=%.o)

all: $(NAME)

bonus: $(BNAME)

$(NAME): $(OBJS)
	cc -Wall -Wextra -Werror $(OBJS) -o $(NAME)

$(BNAME): $(BOBJS)
	cc -Wall -Wextra -Werror $(BOBJS) -o $(BNAME)

%.o: %.c $(HEADERS)
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(BOBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)
	
re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus