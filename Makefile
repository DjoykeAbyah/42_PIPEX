# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dreijans <dreijans@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/24 17:03:57 by dreijans      #+#    #+#                  #
#    Updated: 2023/06/15 17:47:05 by dreijans      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
LIBFT	= ./LIBFT/libft.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
SRC		= \
		main.c\
		parse.c\
		pipex.c\
		utils.c\

OBJ	= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

OBJDIR	= obj

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS) $(HEADERS) 

$(LIBFT):
		@git submodule update --init --recursive
		@$(MAKE) -C ./LIBFT

$(OBJDIR)/%.o: %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)
		
$(OBJDIR)/%.o:
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
		@$(MAKE) clean -C ./LIBFT
		@rm -rf $(OBJDIR)

fclean: clean
		@$(MAKE) fclean -C ./LIBFT
		@rm -f $(NAME)
		@rm -f $(LIBFT)
		@rm -f file2

re:		fclean all

.PHONY: all clean fclean re
