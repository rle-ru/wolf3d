/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:38:14 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/08 13:26:45 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define W_WIDTH 640
# define W_WIDTH2 W_WIDTH * 0.5
# define W_HEIGHT 480
# define W_GHEIGHT 380 // reserve 100px for hud
# define W_GHEIGHT2 W_GHEIGHT * 0.5
# define IMG_SIZE 4 * W_HEIGHT * W_WIDTH
# include <stdint.h>
# include <SDL.h>
# include <SDL_image.h>

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef enum		e_error
{
	ok,
	falloc,
	usage,
	filepath,
	badline
}					t_error;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img;
	int				bpp;
	int				stride;
	int				endian;
}					t_img;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_line
{
	char			*line;
	int				nbx;
	struct s_line	*next;
}					t_line;

typedef struct		s_matrix
{
	double			m[4][4];
}					t_matrix;

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vector3;

typedef struct		s_canvas
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				*img;
}					t_canvas;

typedef struct		s_crea
{
	t_bool			mode;
	t_point			current;
}					t_crea;

typedef struct		s_func
{
	void			(*f)();
}					t_func;

typedef struct		s_vertex2
{
	double			x;
	double			y;
}					t_vertex2;

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct		s_cam
{
	t_point			map;
	t_point			step;
	t_vertex2		plane;
	t_vertex2		pos;
	t_vertex2		sidedist;
	t_vertex2		deltadist;
	t_vector2		dir;
	double			pwdist;
}					t_cam;

typedef struct		s_parser
{
	char			*fname;
	int				fd;
	t_bool			player;
	t_line			*lines;
	t_line			*last_line;
}					t_parser;

typedef struct		s_wolf
{
	t_parser		parser;
	t_canvas		canvas;
	t_cam			player;
	int				**map;
	int				width;
	int				height;
	t_bool			keys[300];
	double			t;
	double			ot;
	double			ft;
	double			ms;
	double			rs;
	uint64_t		fps;
	SDL_Surface		*text;
}					t_wolf;

/*
** Open the map file.
*/
t_error				ft_open_file(int ac, char **av, t_parser *parser);

/*
** Parse the map and checks its format.
*/
t_error				ft_parse_file(t_wolf *w);

/*
** Put the map's data into an array, and checks it's validity.
*/
t_error				ft_create_map(t_wolf *w);

/*
** Free the file's lines
*/
void				free_lines(t_wolf *w);

/*
** Leave programs, frees memory.
*/
int					ft_leave(t_error ret, t_wolf *w);

/*
** Call ft_leave if a leave call is sent.
*/
int					hook_leave(t_wolf *w);

/*
** Init SDL loops.
*/
t_error				init_sdl(t_wolf *w);

/*
** Manages keys input.
*/
int					key_hook(int key, t_wolf *w);

/*
** Manages key releases.
*/
int					key_unhook(int key, t_wolf *w);

/*
** Ray casting function.
*/
int					draw(t_wolf *w);

/*
** Put pixels between two points
*/
void				bresenham(t_wolf *w, t_point o, t_point t, int color);

#endif
