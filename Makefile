CC = c++
CPPFLAGS = -Wall -Wextra -Werror -Wshadow -Wno-shadow -MMD -std=c++98

OS_NAME	= $(shell uname -s | tr A-Z a-z)
ifeq	($(OS_NAME), linux)
	CPPFLAGS += -Wno-unused
endif

NAME =	a.out

SRCS = main.cpp parser.cpp node.cpp cutils.cpp SyntaxException.cpp validator.cpp config.cpp utils.cpp

OBJ_DIR = ./objs/
WORK_DIRS = config exceptions utils

vpath %.cpp ./srcs/ $(addprefix ./srcs/, $(WORK_DIRS))
INC = -I./includes/ $(addprefix -I./includes/, $(WORK_DIRS))

OBJS = $(SRCS:%.cpp=$(OBJ_DIR)%.o)
DEPS = $(patsubst %.o,%.d,$(OBJS))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@ $(INC)
	@printf "\033[0;34mObject %-40.100s [\033[0;32m✔\033[0;34m]\r" $@

$(NAME): $(OBJ_DIR) $(OBJS) $(SRCS)
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@printf '\033[1;32m%-100.100s\n\033[0m' '${NAME} compile success!'

clean:
	@$(RM) $(OBJS) $(DEPS)
	@rm -rf $(OBJ_DIR)
	@printf '\033[1;35mDelete objects success!\n\033[0m'

fclean: clean
	@$(RM) $(NAME)
	@printf '\033[1;35mDelete ${NAME} success!\n\033[0m'

-include $(DEPS)

re: fclean all

.PHONY: all re clean fclean