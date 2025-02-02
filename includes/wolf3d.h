/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:38:14 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/13 16:07:57 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define W_WIDTH 1024
# define W_WIDTH4 (W_WIDTH * 4)
# define W_WIDTH2 (W_WIDTH * 0.5)
# define CHAR_SX (W_WIDTH / 2 - 50)
# define CHAR_EX (CHAR_SX + 100)
# define W_HEIGHT 768
# define W_GHEIGHT (W_HEIGHT - 100)
# define W_GHEIGHT2 (W_GHEIGHT * 0.5)
# define IMG_SIZE (4 * W_HEIGHT * W_WIDTH)
# define TEXTURES_N 10
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
	badline,
	noplayer
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

typedef struct		s_minimap
{
	t_bool			display;
	int				time;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}					t_minimap;

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

typedef struct		s_ray_cast
{
	double			raydirx;
	double			raydiry;
	int				line_heigth;
	int				draw_start;
	int				draw_end;
	int				yts;
	int				yte;
	int				xt;
	double			dw;
	double			dp;
	double			cd;
	double			cfx;
	double			cfy;
	double			weight;
	int				ftx;
	int				fty;
	double			fxw;
	double			fyw;
}					t_ray_cast;

typedef struct		s_wolf
{
	t_parser		parser;
	t_canvas		canvas;
	t_cam			player;
	t_ray_cast		ray;
	t_minimap		minimap;
	int				**map;
	int				width;
	int				hei;
	double			t;
	double			ot;
	double			ft;
	double			ms;
	double			rs;
	uint64_t		fps;
	SDL_Surface		*text[TEXTURES_N];
	int				pc;
	int				head;
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
int					leave(t_error ret, t_wolf *w);

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
** Call the ray casting function.
*/
int					draw(t_wolf *w);

/*
** Ray casting function.
*/
int					ray_casting(t_wolf *w);

void				ray_casting2(t_wolf *w, int side, int x, int text);

void				put_line(t_wolf *w, int x, int xd, int text);

/*
** Minimap function.
*/
void				minimap(t_wolf *w);

void				draw_hud(t_wolf *w);

#endif
