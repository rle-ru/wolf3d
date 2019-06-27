# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 14:17:52 by rle-ru            #+#    #+#              #
#    Updated: 2019/06/27 01:25:39 by rle-ru           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	wolf3d

# Raw Sources

SRCS_RAW			:=	\
						main.c							\
						open_file.c						\
						parse_file.c					\
						create_map.c					\
						free_lines.c					\
						leave.c							\
						init_sdl.c						\
						hook.c							\
						draw.c							\
						bresenham.c						\
						\

# Directories

SRCSDIR   			=	src

OBJSDIR   			=	obj

LIBSPATH			=	.

LIBS				:=	$(LIBSPATH)/libft					\


INCDIR				:=	$(LIBS:%=%/includes) 				\
						/usr/local/include					\
						includes							\
						/usr/local/include/SDL2

# Files

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES		:=	$(OBJS:%.o=%.d)

LIBFILES			:=	$(foreach LIB, $(LIBS), $(LIB)/$(notdir $(LIB)).a)

# Compiler Config

CC					=	clang

CFLAGS				+=	-Wall -Werror -Wextra -flto -Ofast

INCLUDES			:=	$(addprefix -I ,$(INCDIR)) 

INCLIBS				:=	$(foreach LIB,$(LIBS),-L $(LIB) $(subst lib,-l,$(notdir $(LIB))))

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						$(CC) $(CFLAGS) -o $@ $(INCLIBS) -lSDL2 $(OBJS)

# Make Libs

.PHONY				:	libs
libs				:
						@$(foreach LIB, $(LIBS), make -j4 -C $(LIB);)

# Objs Target

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p $(OBJSDIR)
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) -MMD -c $<

# Cleanup

.PHONY				:	clean
clean				:
						@$(foreach LIB, $(LIBS), $(MAKE) clean -C $(LIB);)
						rm -rf $(OBJSDIR)

.PHONY				:	fclean
fclean				:	clean
						@$(foreach LIB, $(LIBS), $(MAKE) fclean -C $(LIB);)
						rm -f $(NAME)

.PHONY				:	re
re					:	fclean all
