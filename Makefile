# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dreijans <dreijans@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/24 17:03:57 by dreijans      #+#    #+#                  #
#    Updated: 2023/05/30 17:37:08 by dreijans      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
LIBFT	= ./Libft/libft.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
SRC		= \
		main.c\
		parsing.c\

OBJ	= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

OBJDIR	= obj

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS) $(HEADERS) 

$(LIBFT):
		@git submodule update --init --recursive
		@$(MAKE) -C ./Libft

$(OBJDIR)/%.o: %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)
		
$(OBJDIR)/%.o:
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
		@$(MAKE) clean -C ./Libft
		@rm -rf $(OBJDIR)

fclean: clean
		@$(MAKE) fclean -C ./Libft
		@rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
