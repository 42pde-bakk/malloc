ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
LIBNAME := libft_malloc.so
INCLUDE = -Iinclude
HEADER = include/malloc.h include/malloc_internal.h

SRC_DIR = srcs
BUILD_DIR = obj
SRC_EXT = c
OBJ_EXT = o

SOURCES := $(shell find $(SRC_DIR) -type f -name "*.$(SRC_EXT)")
OBJS    := $(SOURCES:.$(SRC_EXT)=.$(OBJ_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(OBJS))


# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m

CFLAGS = -Wall -Werror -Wextra -pthread
ifdef DEBUG
 CFLAGS += -g3
endif
ifdef LEAKS
 CFLAGS += -g3 -fsanitize=address
endif
ifdef DEFRAGMENT
 CFLAGS += -D DEFRAGMENT=1
endif
ifdef DEBUG_FAULTY_POINTERS
 CFLAGS += -D DEBUG_FAULTY_POINTERS=1
endif

SHELL := /bin/bash
export SHELL
export DEBUG

all: directories $(NAME)

directories:
	@mkdir -p $(BUILD_DIR)

$(NAME): $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJECTS) -shared -o $(NAME)
	ln -sf $(NAME) $(LIBNAME)
	@printf "$(PINK)Done building malloc $(RESET)\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -fPIC $(INCLUDE) $^ -o $@

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME) $(LIBNAME)
	/bin/rm -f libft_malloc_*.so
	/bin/rm -rf *.dSYM

bonus: BONUS=1
bonus: re

re: fclean all

test: re
	./test.sh $(NAME)

dirs:
	@mkdir $(patsubst %, $(PATH_OBJ)/%, $(DIRS)) $(patsubst %, bin/%, $(DIRS))
