ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
TEST_EXEC = test
LIB_NAME = lft_malloc_$(HOSTTYPE)
INCLUDE = -Iinclude
HEADER = include/peer_stdlib.h

SRC_DIR = srcs
BUILD_DIR = obj
SRC_EXT = c
OBJ_EXT = o

SOURCES     := $(shell find $(SRC_DIR) -type f -name "*.$(SRC_EXT)")
OBJECTS     := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.$(OBJ_EXT)))


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

all: directories $(NAME)

directories:
	@mkdir -p $(BUILD_DIR)

$(NAME): $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJECTS) -shared -o $(NAME)
	@printf "$(PINK)Done building malloc $(RESET)\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -fPIC $(INCLUDE) $^ -o $@

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME) $(TEST_EXEC)

re: fclean all

test: re
	$(CC) $(CFLAGS) main.c -L. -Iinclude -$(LIB_NAME) -o $(TEST_EXEC)
	./$(TEST_EXEC)

dirs:
	@mkdir $(patsubst %, $(PATH_OBJ)/%, $(DIRS)) $(patsubst %, bin/%, $(DIRS))
