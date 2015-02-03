/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_getmove_<yourlogin>.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gallard <gallard@student.42.fr             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:13:55 by gallard           #+#    #+#             */
/*   Updated: 2015/02/03 16:42:04 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"
#include <stdio.h>

# define DEPTH 3

int		pr0n_max(t_grid *grid, int depth, int color);
int		pr0n_min(t_grid *grid, int depth, int color);
int		pr0n_eval(t_grid *grid, int color);

/*
** ------------------------------------------------------------------
** p4_getmove_<yourlogin>(t_grid *grid, t_case color, int turn_count)

** t_grid *grid		:		2D array containing ROUGE/JAUNE/VIDE cells
**							it's a copy of the current state of the game
**							(see puiss4.h)
**
** t_case color		:		ROUGE or JAUNE, it's YOUR color
**
** int turn_count	:		number of coins on the grid
**
** return (move)	:		0 <= move < GRID_W
**
** ---------------------
** Available functions :
** ---------------------
** int p4_legal(t_grid *grid, int col)
**		returns 0 if col(umn) is full, 1 if at least one cell is empty
** -
** int p4_won(t_grid *grid, int col);
**		returns 1 if playing in col(umn) will win the game, 0 otherwise
** -
** int p4_play(t_grid *grid, int col, t_case color);
** int p4_unplay(t_grid *grid, int col, t_case color);
**		these 2 functions can help you simulate next moves for both
**		you and your opponent (remember your grid is a copy)
*/

int		pr0n_eval(t_grid *grid, int color)
{
	(void)color;
	(void)grid;
	return(1);
	
}

int		pr0n_max(t_grid *grid, int depth, int color)
{
	int		max;
	int		i;
	int		j;
	int		tmp;

	max = -10000;
	i = 0;
	if (depth == 0 || p4_won(grid, color))
		pr0n_eval(grid, color);
	while (i < GRID_H)
	{
		j = 0;
		while (j < GRID_W)
		{
			if ((*grid)[i][j] == VIDE)
			{
				p4_play(grid, j, color);
				tmp = pr0n_min(grid, depth - 1, color);
				if (tmp > max)
					max = tmp;
				p4_unplay(grid, j, color);
			}
			j++;
		}
		i++;
	}
	return (max);
}

int		pr0n_min(t_grid *grid, int depth, int color)
{
	int		min;
	int		i;
	int		j;
	int		tmp;

	min = -10000;
	i = 0;
	if (depth == 0 || p4_won(grid, color))
		pr0n_eval(grid, color);
	while (i < GRID_H)
	{
		j = 0;
		while (j < GRID_W)
		{
			if ((*grid)[i][j] == VIDE)
			{
				p4_play(grid, j, color);
				tmp = pr0n_max(grid, depth - 1, color);
				if (tmp < min)
					min = tmp;
				p4_unplay(grid, j, color);
			}
			j++;
		}
		i++;
	}
	return (min);
}

int		p4_getmove_vchaillo(t_grid *grid, t_case color, int turn_count)
{
	int		move;
	int		max;
	int		i;
	int		j;
	int		tmp;

	max = -10000;
	i = 0;
	move = 0;
	while (i < GRID_H)
	{
		j = 0;
		while (j < GRID_W)
		{
			if ((*grid)[i][j] == VIDE)
			{
				p4_play(grid, j, color);
				tmp = pr0n_min(grid, DEPTH, color);
//				printf("%d", move);
				if (tmp > max)
				{
					max = tmp;
					move = j;
				}
				p4_unplay(grid, j, color);
			}
			j++;
		}
		i++;
	}
	(void)turn_count;
	return (move);
}
