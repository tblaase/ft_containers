#binaries
NAME		=	ft_containers
STD_NAME	=	std_containers

#compiler
CXX			=	c++

#standard flags
CXXFLAGS	=	-std=c++98  -Wall -Wextra -Werror

#additional flags
# CXXFLAGS	+=	-g # add this to get debug information
# CXXFLAGS	+=	-fsanitize=address # check for invalid addresses, disable for checking with valgrind
# CXXFLAGS	+=	-D LEAK # enable to check for leaks with leaks command for each container

#directories
PWD			=	$(shell pwd)
SRC_DIR		=	src/
OBJ_DIR		=	obj/
STD_OBJ_DIR	=	std_obj/
INC_DIR		=	include/

#controll codes
RESET		=	\033[0m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
UP			=	\033[A
CUT			=	\033[K

#source files
SRC_FILES	=	main.cpp

OBJ_FILES	=	$(SRC_FILES:.cpp=.o)

STD_OBJ_FILES=	$(SRC_FILES:.cpp=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
STD_OBJ		=	$(addprefix $(STD_OBJ_DIR), $(STD_OBJ_FILES))

#all rule
all: $(NAME) $(STD_NAME)
#ascii art can be found at: https://patorjk.com/software/taag/#p=display&f=Calvin%20S&t=ft%20containers
	@printf "\n"
	@printf "$(GREEN)┌─┐┌┬┐  ┌─┐┌─┐┌┐┌┌┬┐┌─┐┬┌┐┌┌─┐┬─┐┌─┐ \n$(RESET)"
	@printf "$(GREEN)├┤  │   │  │ ││││ │ ├─┤││││├┤ ├┬┘└─┐ \n$(RESET)"
	@printf "$(GREEN)└   ┴   └─┘└─┘┘└┘ ┴ ┴ ┴┴┘└┘└─┘┴└─└─┘ \n$(RESET)"
	@printf "\n"

#compile the executable
$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

$(STD_NAME): $(STD_OBJ)
	@echo "$(YELLOW)Compiling [$(STD_NAME)]...$(RESET)"
	@$(CXX) $(CXXFLAGS) -D STD $(STD_OBJ) -o $(STD_NAME)
	@echo "$(GREEN)Finished [$(STD_NAME)]$(RESET)"

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

$(STD_OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(STD_OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CXX) $(CXXFLAGS) -D STD -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects from $(PWD)...$(RESET)"; else \
	echo "No objects to remove from $(PWD)."; \
	fi;
	@if [ -d "$(STD_OBJ_DIR)" ]; then \
	rm -rf $(STD_OBJ_DIR); \
	echo "$(BLUE)Deleting all std_objects from $(PWD)...$(RESET)"; else \
	echo "No std_objects to remove from $(PWD)."; \
	fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	echo "$(BLUE)Deleting $(NAME) from $(PWD)...$(RESET)"; else \
	echo "No Executable to remove from $(PWD)."; \
	fi;
	@if [ -f "$(STD_NAME)" ]; then \
	rm -f $(STD_NAME); \
	echo "$(BLUE)Deleting $(STD_NAME) from $(PWD)...$(RESET)"; else \
	echo "No Executable to remove from $(PWD)."; \
	fi;
	@if [ -f "ft_out.log" ]; then \
	rm -f ft_out.log; \
	echo "$(BLUE)Deleting ft_out.log from $(PWD)...$(RESET)"; else \
	echo "No ft_out.log to remove from $(PWD)."; \
	fi;
	@if [ -f "std_out.log" ]; then \
	rm -f std_out.log; \
	echo "$(BLUE)Deleting std_out.log from $(PWD)...$(RESET)"; else \
	echo "No ft_out.log to remove from $(PWD)."; \
	fi;

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re
