# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 14:17:52 by rle-ru            #+#    #+#              #
#    Updated: 2019/06/22 15:29:17 by rle-ru           ###   ########.fr        #
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
						init_mlx.c						\
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
						minilibx

# Files

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES		:=	$(OBJS:%.o=%.d)

LIBFILES			:=	$(foreach LIB, $(LIBS), $(LIB)/$(notdir $(LIB)).a)

# Compiler Config

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra -fsanitize="address" -g

INCLUDES			:=	$(addprefix -I ,$(INCDIR))	

INCLIBS				:=	$(foreach LIB,$(LIBS),-L $(LIB) $(subst lib,-l,$(notdir $(LIB))))

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						$(CC) -o $@ $(CFLAGS) $(INCLIBS) $(OBJS) -framework OpenGL -framework AppKit -L /usr/local/lib -lmlx

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

mlx					:	$(OBJS) libs
						make -C minilibx
						$(CC) -o $(NAME) $(CFLAGS) $(INCLIBS) -I minilibx/ $(OBJS) minilibx/libmlx.a -framework OpenGL -framework Appkit -L ./minilibx
						
