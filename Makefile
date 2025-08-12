# HMAP_DYN_ARRAY
# HMAP_LLIMPLEMENTATION
# IMPL=HMAP_LLIMPLEMENTATION
MAIN=./src/main.c
LIBD=./lib
BIN=./bin
LIB=$(LIBD)/libhmap.a
SRCS=./src/djb2_hash.c ./src/hmap.c ./src/stack.c ./src/stack_manipulation.c
OBJS=$(SRCS:%.c=%.o)
NAME=./main
CC=cc
CXX=c++
INCLUDE=-I./include
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) -ggdb $ # -D$(IMPL)
AR=ar rsc
RM=rm -rf

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(LIBD):
	mkdir -p $(LIBD)
$(BIN):
	mkdir -p $(BIN)
$(LIB): $(LIBD) $(OBJS)
	$(AR) $@ $(OBJS)
$(NAME): $(MAIN) $(LIB) $(BIN)
	$(CC) $(CFLAGS) $(INCLUDE) $(MAIN) -L$(LIBD) -lhmap -o $(BIN)/$@
	$(CC) $(CFLAGS) $(INCLUDE) ./tests/word_counter.c -L$(LIBD) -lhmap -o $(BIN)/counter
clean:
	$(RM) $(LIBD)
	$(RM) $(OBJS)
	$(RM) $(BIN)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: re fclean clean bonus
