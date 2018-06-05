/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbleus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 15:38:41 by dbleus            #+#    #+#             */
/*   Updated: 2018/05/23 21:21:20 by dbleus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void		init_struct(t_grid *g)
{
	g->fd = 0;
	g->map = NULL;
	g->begin = NULL;
	g->empty_cell = 0;
	g->full_cell = 0;
	g->obstacle_cell = 0;
	g->nb_column = 0;
	g->nb_line = 0;
	g->nb_obstacle = 0;
	g->pos_max = 0;
	g->value_max = 0;
	g->compute_map = NULL;
}

void		frozen(t_grid *grid)
{
	if (grid->fd > 0)
		close(grid->fd);
	if (grid->map != NULL)
		free(grid->begin);
	return ;
}

int			alloc_compute_map(t_grid *g)
{
	g->compute_map = malloc(sizeof(short) * (g->nb_line * (g->nb_column + 1)));
	if (g->compute_map == NULL)
		return (0);
	return (1);
}

void		*ft_realloc(void *ptr, size_t size)
{
	char	*out;

	if ((out = malloc(size)) == NULL)
		return (NULL);
	ft_bzero(out, size);
	if (ptr != NULL)
	{
		ft_strncpy(out, ptr, ft_strlen(ptr));
		free(ptr);
	}
	return (out);
}

char		*ft_bzero(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = 0;
		++i;
	}
	return (s);
}
