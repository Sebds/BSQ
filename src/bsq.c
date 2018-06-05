/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbleus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 08:19:42 by dbleus            #+#    #+#             */
/*   Updated: 2018/05/23 20:43:43 by dbleus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void		process(t_grid *grid)
{
	if (grid->fd < 0)
		error(ERROR_BAD_ARGUMENT);
	else if (!read_map(grid))
		error(ERROR_READING_MAP);
	else if (!read_metadata(grid))
		error(ERROR_BAD_METADATA);
	else if (!is_valid_map(grid))
		error(ERROR_BAD_MAP);
	else if (!solver(grid))
		fatal_error(grid, FATAL_BSQ);
	else
		show_result(grid);
	return ;
}

int			main(int argc, char **argv)
{
	t_grid	grid;
	int		count;

	init_struct(&grid);
	if (argc == 1)
	{
		grid.fd = 0;
		process(&grid);
		frozen(&grid);
		return (EXIT_SUCCESS);
	}
	count = 1;
	while (count < argc)
	{
		init_struct(&grid);
		grid.fd = open(argv[count], O_RDONLY);
		process(&grid);
		if (count != argc - 1)
			ft_putstr("\n");
		++count;
		frozen(&grid);
	}
	return (EXIT_SUCCESS);
}
