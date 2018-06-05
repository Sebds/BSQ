/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbleus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:15:24 by dbleus            #+#    #+#             */
/*   Updated: 2018/05/23 22:40:56 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

void		show_result(t_grid *grid)
{
	int		i;

	i = 0;
	while (i < ((grid->nb_column + 1) * grid->nb_line))
	{
		if (grid->compute_map[i] == -1)
			grid->map[i] = '\n';
		else if (grid->compute_map[i] == 0)
			grid->map[i] = grid->obstacle_cell;
		else if (is_zone(i, grid))
			grid->map[i] = grid->full_cell;
		else
			grid->map[i] = grid->empty_cell;
		++i;
	}
	ft_putstr(grid->map);
}

void		ft_putstr_file(char *str, int fd)
{
	char	*end;

	end = str;
	while (*end)
		++end;
	write(fd, str, end - str);
	return ;
}

void		ft_putstr(char *str)
{
	ft_putstr_file(str, STDOUT_FILENO);
	return ;
}

void		error(char *error)
{
	ft_putstr_file(error, STDERR_FILENO);
	return ;
}

void		fatal_error(t_grid *grid, char *str_error)
{
	frozen(grid);
	error(str_error);
	exit(EXIT_FAILURE);
	return ;
}
