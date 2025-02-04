# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstegema <mstegema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/01/03 13:55:56 by mstegema      #+#    #+#                  #
#    Updated: 2024/02/02 18:06:22 by mstegema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo

# compilation
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
HEADER	= -I $(INCDIR)

ifdef DEBUG
CFLAGS	+= -g -fsanitize=thread #-fsanitize=address
endif

# directories
SRCDIR	= src
INCDIR	= inc
OBJDIR	= obj
BINDIR	= bin

# sources
SRCS	= $(SRCDIR)/main.c \
		$(SRCDIR)/parsing.c \
		$(SRCDIR)/init.c \
		$(SRCDIR)/routine.c \
		$(SRCDIR)/free.c \
		$(SRCDIR)/utils.c

# objects
OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# colours
PURPLE	= \033[0;35m
NC		= \033[0m

# rules
all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJS) $(CFLAGS) -o $(BINDIR)/$(NAME)
	@echo "$(PURPLE)$(NAME)$(NC) has been created"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $(HEADER) -o $@ $^
	@echo "Compiling: $(PURPLE)$<$(NC)"

debug: fclean
	$(MAKE) DEBUG=1

clean:
	@rm -rf $(OBJDIR)
	@echo "$(PURPLE)object files$(NC) have been removed"

fclean: clean
	@rm -rf $(BINDIR)
	@echo "$(PURPLE)$(NAME) & directories$(NC) have been removed"

re: fclean all

.PHONY: all debug clean fclean re
