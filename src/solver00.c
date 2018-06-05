/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbleus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 08:19:42 by dbleus            #+#    #+#             */
/*   Updated: 2018/05/23 20:30:32 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int			is_zone(int i, t_grid *grid)
{
	int		x;
	int		y;
	int		x2;
	int		y2;
	int		val;

	val = grid->value_max;
	y = grid->pos_max / (grid->nb_column + 1);
	x = grid->pos_max % (grid->nb_column + 1);
	x2 = i % (grid->nb_column + 1);
	y2 = i / (grid->nb_column + 1);
	if (x2 >= x && x2 < x + val && y2 >= y && y2 < y + val)
		return (1);
	return (0);
}

void		ft_set_num(t_grid *g, int i, int j)
{
	g->compute_map[i] = MN(g->compute_map[i + 1],
			g->compute_map[i + j],
			g->compute_map[i + j + 1]) + 1;
}

int			solver(t_grid *g)
{
	int		i;
	int		j;

	j = 1 + g->nb_column;
	i = (g->nb_column + 1) * g->nb_line - 1;
	while (i >= 0)
	{
		if (g->map[i] == '\n')
			g->compute_map[i] = -1;
		else if (g->map[i] == g->obstacle_cell)
			g->compute_map[i] = 0;
		else if (i >= ((g->nb_line - 1) * (g->nb_column + 1)))
			g->compute_map[i] = 1;
		else if ((i + 1) % (g->nb_column + 1) == g->nb_column)
			g->compute_map[i] = 1;
		else
			ft_set_num(g, i, j);
		if (g->value_max <= g->compute_map[i])
		{
			g->value_max = g->compute_map[i];
			g->pos_max = i;
		}
		--i;
	}
	return (1);
}
