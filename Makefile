MAIN=./src/main.c
LIBD=./lib
LIB=$(LIBD)/libhmap.a
SRCS=./src/djb2_hash.c ./src/hmap.c ./src/stack.c ./src/stack_manipulation.c
OBJS=$(SRCS:%.c=%.o)
NAME=./prog
CC=cc
CXX=c++
INCLUDE=-I./include
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) -ggdb -DHMAP_DYN_ARRAY
AR=ar rsc
RM=rm -rf

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(LIBD):
	mkdir -p $(LIBD)
$(LIB): $(LIBD) $(OBJS)
	$(AR) $@ $(OBJS)
$(NAME): $(MAIN) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDE) $(MAIN) -L$(LIBD) -lhmap -o $@
clean:
	$(RM) $(LIBD)
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: re fclean clean bonus
