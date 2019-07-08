/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:02:05 by rle-ru            #+#    #+#             */
/*   Updated: 2019/07/08 14:39:04 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>
#include "keys.h"
#include <SDL.h>

int			chose(int tile)
{
	if (tile == 1)
		return (0xFFF0);
	else if (tile == 2)
		return (0xFFF);
	else if (tile == 3)
		return (0xFF);
	else
		return (0xFFFFFF);
}

int			ray_casting(t_wolf *w)
{
	int		x;
	double	camx;
	double	raydirx;
	double	raydiry;
	int		hit;
	int		side;

	x = 0;
	while (x < W_WIDTH)
	{
		camx = 2 * x / (double)W_WIDTH - 1;
		raydirx = w->player.dir.x + w->player.plane.x * camx;
		raydiry = w->player.dir.y + w->player.plane.y * camx;
		w->player.map.x = (int)w->player.pos.x;
		w->player.map.y = (int)w->player.pos.y;
		w->player.deltadist.x = sqrt(1 + (raydiry * raydiry) / (raydirx * raydirx));
		w->player.deltadist.y = sqrt(1 + (raydirx * raydirx) / (raydiry * raydiry));
		hit = 0;
		if (raydirx < 0)
		{
			w->player.step.x = -1;
			w->player.sidedist.x = (w->player.pos.x - w->player.map.x) * w->player.deltadist.x;
		}
		else
		{
			w->player.step.x = 1;
			w->player.sidedist.x = (w->player.map.x + 1.0 - w->player.pos.x) * w->player.deltadist.x;
		}
		if (raydiry < 0)
		{
			w->player.step.y = -1;
			w->player.sidedist.y = (w->player.pos.y - w->player.map.y) * w->player.deltadist.y;
		}
		else
		{
			w->player.step.y = 1;
			w->player.sidedist.y = (w->player.map.y + 1.0 - w->player.pos.y) * w->player.deltadist.y;
		}
		while (!hit)
		{
			if (w->player.sidedist.x < w->player.sidedist.y)
			{
				w->player.sidedist.x += w->player.deltadist.x;
				w->player.map.x += w->player.step.x;
				side = 0;
			}
			else
			{
				w->player.sidedist.y += w->player.deltadist.y;
				w->player.map.y += w->player.step.y;
				side = 1;
			}
			if (w->map[w->player.map.x][w->player.map.y] > 0)
				hit = 1;
		}
		if (!side)
			w->player.pwdist = (w->player.map.x - w->player.pos.x + (1 - w->player.step.x) * 0.5) / raydirx;
		else
			w->player.pwdist = (w->player.map.y - w->player.pos.y + (1 - w->player.step.y) * 0.5) / raydiry;
		int lineh = (int)(W_GHEIGHT / w->player.pwdist);
		int draws = -lineh * 0.5 + W_GHEIGHT2;
		if (draws < 0)
			draws = 0;
		int drawe = lineh * 0.5 + W_GHEIGHT2;
		if (drawe >= W_GHEIGHT)
			drawe = W_GHEIGHT - 1;
		int	color = chose(w->map[w->player.map.x][w->player.map.y]);
		bresenham(w, (t_point){x, draws}, (t_point){x, drawe}, side == 1 ? color : (color >> 1));
		//remplacer bresenham par une fonction qui dessine en vertical, sans multiplication
		++x;
	}
	return (0);
}


#include <stdio.h>
static void	update_hooks(t_wolf *w)
{
	const uint8_t	*s = SDL_GetKeyboardState(NULL);
	
	if(s[SDL_SCANCODE_ESCAPE])
		exit(0);//
	if (s[SDL_SCANCODE_LEFT])
	{
		double odx = w->player.dir.x;
		w->player.dir.x = odx * cos(w->rs) - w->player.dir.y * sin(w->rs);
		w->player.dir.y = odx * sin(w->rs) + w->player.dir.y * cos(w->rs);
		double	opx = w->player.plane.x;
		w->player.plane.x = opx * cos(w->rs) - w->player.plane.y * sin(w->rs);
		w->player.plane.y = opx * sin(w->rs) + w->player.plane.y * cos(w->rs);
	}
	if (s[SDL_SCANCODE_RIGHT])
	{
		double odx = w->player.dir.x;
		w->player.dir.x = odx * cos(-w->rs) - w->player.dir.y * sin(-w->rs);
		w->player.dir.y = odx * sin(-w->rs) + w->player.dir.y * cos(-w->rs);
		double	opx = w->player.plane.x;
		w->player.plane.x = opx * cos(-w->rs) - w->player.plane.y * sin(-w->rs);
		w->player.plane.y = opx * sin(-w->rs) + w->player.plane.y * cos(-w->rs);
	}
	if (s[SDL_SCANCODE_UP])
	{
		if (!w->map[(int)(w->player.pos.x + w->player.dir.x * w->ms)][(int)w->player.pos.y])
			w->player.pos.x += w->player.dir.x * w->ms;
		if (!w->map[(int)w->player.pos.x][(int)(w->player.pos.y + w->player.dir.y * w->ms)])
			w->player.pos.y += w->player.dir.y * w->ms;
	}
	if (s[SDL_SCANCODE_DOWN])
	{
		if (!w->map[(int)(w->player.pos.x - w->player.dir.x * w->ms)][(int)w->player.pos.y])
			w->player.pos.x -= w->player.dir.x * w->ms;
		if (!w->map[(int)w->player.pos.x][(int)(w->player.pos.y - w->player.dir.y * w->ms)])
			w->player.pos.y -= w->player.dir.y * w->ms;
	}
}

static void	update_fps(t_wolf *w)
{
	w->ot = w->t;
	w->t = SDL_GetTicks();
	w->ft = (w->t - w->ot) / 1000.0;
	w->fps = (1 / w->ft);
	w->ms = w->ft * 5.0;
	w->rs = w->ft * 3.0;
	// printf("FPS :%llu\n", w->fps);
}

// void		put_img(t_wolf *w)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < w->text->h)
// 	{
// 		x = 0;
// 		while (x < w->text->w)
// 		{
// 			w->canvas.img[y * w->text->w + x] = (int*)(w->text->pixels)[y * w->text->w + x];
// 			++x;
// 		}
// 		++y;
// 	}
// }

int			draw(t_wolf *w)
{
	SDL_Event	event;
	while (1)
	{
		update_fps(w);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break;
		ft_bzero(w->canvas.img, IMG_SIZE);
		update_hooks(w);
		ray_casting(w);
		// put_img(w);
		SDL_UpdateTexture(w->canvas.texture, NULL, w->canvas.img,
				W_WIDTH * 4);
		SDL_RenderCopy(w->canvas.renderer, w->canvas.texture, NULL, NULL);
		SDL_RenderPresent(w->canvas.renderer);
	}
	free(w->canvas.img);
	SDL_DestroyRenderer(w->canvas.renderer);
    SDL_Quit();
	return (0);
}
