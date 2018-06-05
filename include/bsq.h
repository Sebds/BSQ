/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbleus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 08:42:19 by dbleus            #+#    #+#             */
/*   Updated: 2018/05/23 22:39:45 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define ERROR_BAD_ARGUMENT	"map error\n"
# define ERROR_READING_MAP	"map error\n"
# define ERROR_BAD_MAP		"map error\n"
# define ERROR_BAD_METADATA	"map error\n"
# define FATAL_BSQ			"map error\n"
# define BUFF_SIZE			8192
# define EMPTY_CELL			'.'
# define OBSTACLE_CELL		'o'
# define FULL_CELL          'x'

# define MINIMUM2(a, b) (a < b ? a : b)
# define MN(a, b, c) MINIMUM2(a, MINIMUM2(b, c))
# define NOT_EQUAL(a, b, c) (a == b) || (a == c) || (b == c)

typedef struct	s_grid
{
	int			fd;
	char		*map;
	char		*begin;
	short		*compute_map;
	char		empty_cell;
	char		full_cell;
	char		obstacle_cell;
	int			nb_column;
	int			nb_line;
	int			nb_obstacle;
	int			pos_max;
	int			value_max;
}				t_grid;

void			process(t_grid *grid);
int				bsq(t_grid *grid);
int				solver(t_grid *g);
int				is_zone(int i, t_grid *grid);
void			ft_set_sum(t_grid *grid, int i, int j);

void			show_result(t_grid *grid);
void			ft_putstr(char *str);
void			ft_putstr_file(char *str, int fd);
void			fatal_error(t_grid *grid, char *error);
void			error(char *error);

char			*ft_strcpy(char *dest, char *str);
char			*ft_strncpy(char *dest, char *src, int n);
int				ft_strlen(char *s);
int				ft_nbrlen(int nbr);
int				ft_atoi(char *str);

void			*ft_realloc(void *ptr, size_t size);
void			init_struct(t_grid *grid);
char			*ft_bzero(char *s, size_t n);
void			frozen(t_grid *grid);

int				alloc_compute_map(t_grid *grid);
int				read_metadata(t_grid *grid);
int				read_map(t_grid *grid);
int				is_valid_map(t_grid *grid);

#endif
