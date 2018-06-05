/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbleus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 08:19:42 by dbleus            #+#    #+#             */
/*   Updated: 2018/05/23 22:35:06 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int				read_map_2(t_grid *grid, int size)
{
	int			tmp_fd;
	int			count;

	tmp_fd = open("./.map.tmp", O_RDONLY);
	if (tmp_fd < 0)
		return (0);
	grid->begin = malloc(sizeof(char) * (size + 1));
	if (grid->begin == NULL)
		return (0);
	grid->map = grid->begin;
	grid->begin[size] = 0;
	count = 0;
	while (count != size)
		count += read(tmp_fd, &grid->begin[count], size - count);
	close(tmp_fd);
	return (1);
}

int				read_map(t_grid *grid)
{
	char		buffer[BUFF_SIZE + 1];
	int			tmp_fd;
	int			ret;
	int			size;

	tmp_fd = open("./.map.tmp", O_CREAT | O_TRUNC | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (tmp_fd < 0)
		return (0);
	size = 0;
	while ((ret = read(grid->fd, buffer, BUFF_SIZE)) > 0)
	{
		size += ret;
		write(tmp_fd, buffer, ret);
	}
	close(tmp_fd);
	return (read_map_2(grid, size));
}

int				count_column(t_grid *g)
{
	char		*c;

	c = g->map;
	while (*c && *c != '\n')
		++c;
	g->nb_column = c - g->map;
	if (*c == 0 || g->nb_column == 0)
		return (0);
	return (1);
}

int				read_metadata(t_grid *grid)
{
	char		*end_firstline;

	end_firstline = grid->map;
	while (*end_firstline && *end_firstline != '\n')
		++end_firstline;
	if (*end_firstline == 0)
		return (0);
	if (end_firstline - grid->map <= 3)
		return (0);
	grid->empty_cell = *(end_firstline - 3);
	grid->obstacle_cell = *(end_firstline - 2);
	grid->full_cell = *(end_firstline - 1);
	if (NOT_EQUAL(grid->empty_cell, grid->obstacle_cell, grid->full_cell))
		return (0);
	*(end_firstline - 3) = 0;
	grid->nb_line = ft_atoi(grid->map);
	if (grid->nb_line <= 0)
		return (0);
	if (ft_nbrlen(grid->nb_line) != ft_strlen(grid->map))
		return (0);
	grid->begin = grid->map;
	grid->map += ft_nbrlen(grid->nb_line) + 3 + 1;
	if (count_column(grid) == 0 || alloc_compute_map(grid) == 0)
		return (0);
	return (1);
}

int				is_valid_map(t_grid *grid)
{
	int			count;
	int			i;

	i = 0;
	count = 1;
	while (grid->map[i] != '\0')
	{
		if (grid->map[i] == '\n' && (count) % (grid->nb_column + 1) == 0)
			count = 1;
		else if (grid->map[i] == grid->empty_cell)
		{
			grid->map[i] = EMPTY_CELL;
			++count;
		}
		else if (grid->map[i] == grid->obstacle_cell)
		{
			grid->map[i] = OBSTACLE_CELL;
			grid->nb_obstacle++;
			count++;
		}
		else
			return (0);
		++i;
	}
	return (i != (grid->nb_column + 1) * (grid->nb_line) ? 0 : 1);
}
