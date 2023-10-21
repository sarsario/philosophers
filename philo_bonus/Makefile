# ================================ VARIABLES ================================= #

# The name of the executable
NAME	= philo_bonus

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3 -fsanitize=thread
endif

# Folder names
SRCDIR	= src/
INCDIR	= includes/
OBJDIR	= obj/
# LIB_DIR	= includes/lib/
# MLX_DIR	= includes/mlx/

# Add include folders
# CFLAGS	+= -I $(INCDIR) -I $(INCDIR)lib -I $(INCDIR)mlx

# Linking stage flags
# LDFLAGS = -framework OpenGL -framework AppKit -L$(INCDIR)lib -lft -L$(INCDIR)mlx -lmlx

# List of source files (add your *.c files here)

SRCS =\
	$(SRCDIR)philo_bonus.c\
	$(SRCDIR)utils.c\
	$(SRCDIR)utils2.c\
	$(SRCDIR)free.c\
	$(SRCDIR)set_data.c\
	$(SRCDIR)set_philo.c\
	$(SRCDIR)routine.c\
	$(SRCDIR)routine2.c\
	$(SRCDIR)thread.c\

HEADERS =\
	$(INCDIR)philo.h

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compiling
$(OBJDIR)%.o : %.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@


# Linking
$(NAME): $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRCS)$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(YE)&&& Linked [$(CC)] &&&\n--- $(NAME)$(RC)\n"

# Cleaning
clean :
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)

fclean : clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# Rule to check norm
norm :
	@norminette $(SRCDIR) $(INCDIR)

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)\n"
	./$(NAME)

# This specifies the rules that does not correspond to any filename
.PHONY: all run clean fclean re