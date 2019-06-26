/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:38:14 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/26 17:02:51 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define MAX_PROJ 2
# define MAX_DRAW 2
# define FOV 110.0 * M_PI / 180.0
# define FAR 10.0
# define NEAR 0.1
# define W_LEFT -500.0
# define W_RIGHT 500.0
# define W_BOTTOM 500.0
# define W_TOP -500.0
# define W_WIDTH 640
# define W_HEIGHT 480
# include <stdint.h>

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

// typedef struct		s_vector2
// {
// 	double			x;
// 	double			y;
// }					t_vector2;

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vector3;

// typedef struct		s_cam
// {
// 	t_vector3		pos;
// 	t_matrix		projection[2];
// 	t_matrix		rotation;
// 	t_vector3		rot_angles;
// 	t_vector3		pre_rot_angles;
// }					t_cam;

// typedef struct		s_parser
// {
// 	char			*fname;
// 	int				fd;
// 	t_line			*lines;
// 	t_line			*last_line;
// 	int				maxz;
// 	int				minz;
// }					t_parser;

typedef struct		s_canvas
{
	void			*mlx_ptr;
	void			*window;
	t_img			img;
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
	int				*map;
	int				width;
	int				height;
	t_bool			keys[300];
	uint64_t		t;
	uint64_t		ot;
	uint64_t		ft;
	double			ms;
	double			rs;
	uint64_t		fps;
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
** Creates a MLX image and starts the MLX loops.
*/
t_error				init_mlx(t_wolf *w);

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
void				bresenham(t_wolf *w, t_point o, t_point t);




// /*
// ** Initialize fdf struct
// */
// void				ft_init_fdf(t_fdf *fdf);






// /*
// ** Initialize three different matrixes
// */
// void				init_matrixes(t_fdf *fdf);



// /*
// ** Display the map on the mlx screen
// */
// int					draw_map(t_fdf *fdf);

// /*
// ** Multiply matrixes
// */
// t_matrix			mat_4_mul(int nb, ...);

// /*
// ** Put lines on screen
// */
// void				put_line(t_fdf *fdf, int ox, int oy);

// /*
// ** Multiply a matrix with a vector
// */
// t_vector3			mat_4_mul_v(t_matrix m, t_vector3 v);

// /*
// ** Get pixel color
// */
// int					get_color(int from, int to, double a);

// /*
// ** Add two vectors
// */
// t_vector3			vec_3_add(t_vector3 a, t_vector3 b);

// /*
// ** Sub two vectors
// */
// t_vector3			vec_3_sub(t_vector3 a, t_vector3 b);

// /*
// ** Manage the rotation matrixes
// */
// void				rotator(t_fdf *fdf, t_vector3 a);



// /*
// ** Return a color gradient
// */
// double				get_gradient(double val, double first, double second);

// /*
// ** Put a pixel on the window
// */
// void				put_pixel(t_fdf *fdf, int x, int y, int color);

// /*
// ** Select a color for a point, depending on its altitude
// */
// void				select_color(t_fdf *fdf, int i);

// /*
// ** Reset the cam position
// */
// void				reset_cam(t_fdf *fdf);

// /*
// **	Calls line drawers
// */
// int					put_pixels(t_fdf *fdf);

// /*
// ** Put a circle around a point in creative mode
// */
// void				put_circle(t_fdf *fdf);

// /*
// **	Project a 3D point in 2D
// */
// t_vector2			project_point(t_fdf *fdf, int x, int y);

// /*
// **	Swap two integer pointers
// */
// void				swap(int *a, int *b);

#endif
