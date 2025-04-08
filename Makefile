NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRCDIR	= .
OBJDIR	= objs

SRC		= $(wildcard $(SRCDIR)/*.c)
OBJ		= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM		= rm -f
MKDIR	= mkdir -p

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32m"
	@echo "       ▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀​▀▀▀▀▀▀▌ "
	@echo "    ▄▄██▌█ beep beep MAFARTO-        ▌ "
	@echo " ▄▄▄▌Ç██▌█ Entrega del Philo         ▌ "
	@echo " ███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄​▄▄▄▄▄▄▌ "
	@echo " ▀(@)▀▀▀▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀▀▀​▀▀▀▀(@) "
	@echo ""
	@echo "  ✅ Compilation finished successfully!🚛"
	@echo "\033[0m"

clean:
	@$(RM) $(OBJS)
	@echo "\033[1;32m"
	@echo " ▌▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌▐▄       "
	@echo " ▌     -OTRAFAM beep beep █▌██▄▄     "
	@echo " ▌     olihP led agaertnE █▌██Ç ▌▄▄  "
	@echo " ▌▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▌███████  "
	@echo " (@)▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀(@)(@)▀▀▀   "
	@echo ""
	@echo "\033[0;33mCleanup done.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(OBJDIR)
	@echo "\033[0;31mBinary removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re