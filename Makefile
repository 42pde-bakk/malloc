ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
TEST_EXEC = a.out
LIB_NAME = lft_malloc_$(HOSTTYPE)
INCLUDE = -Iinclude
HEADER = include/peer_stdlib.h

SRC_DIR = ./srcs
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m

CFLAGS = -Wall -Werror -Wextra
ifdef DEBUG
 CFLAGS += -g3 -fsanitize=address
endif
SHELL := /bin/bash
export SHELL
export DEBUG

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -shared -o $(NAME)
	@printf "$(PINK)Done building malloc $(RESET)\n"

%.o: %.c
	$(CC) $(CFLAGS) -c -fPIC $(INCLUDE) $^ -o $@

clean:
	/bin/rm -f $(OBJS)
	@/bin/rm -f *.o *~ *.gch *.so

fclean: clean
	/bin/rm -f $(NAME) $(TEST_EXEC)

re: fclean all

test: re
	$(CC) $(CFLAGS) main.c -L. -Iinclude -$(LIB_NAME)
	./$(TEST_EXEC)
