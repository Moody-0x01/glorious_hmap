MAIN=./src/main.c
SRCS=./src/djb2_hash.c ./src/hmap.c
OBJS=$(SRCS:%.c=%.o)
NAME=./prog
CC=cc
INCLUDE=-I./include
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) -ggdb
AR=ar rsc
RM=rm -f

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(NAME): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: re fclean clean bonus
