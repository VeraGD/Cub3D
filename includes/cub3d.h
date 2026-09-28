/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:32:58 by narrospi          #+#    #+#             */
/*   Updated: 2025/05/29 14:43:03 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 1500
# define HEIGHT 800
# define PI 3.14159265358979323846
# define WALL_C '1'

typedef struct s_player
{
	double	x;
	double	y;
	double	angle_dir;
	double	x_dir;
	double	y_dir;
	double	turn;
	char	side;
	char	front;
	char	position;
}	t_player;

// MAPA Y COLORES
typedef struct s_map
{
	char		**map;
	uint32_t	f;
	uint32_t	c;
	double		map_width;
	double		map_height;
}	t_map;

typedef struct s_rayc
{
	uint32_t		slice;
	double			shift_factor;
	double			x;
	double			y;
	double			x_delta;
	double			y_delta;
	double			x_dist;
	double			y_dist;
	int				x_hit;
	int				y_hit;
	int				x_dir;
	int				y_dir;
	double			wall_dist[WIDTH];
	double			hit_portion;
	uint32_t		texture_x;
	mlx_texture_t	*hit_text;
	uint32_t		slice_height;
}	t_rayc;

// TEMA VENTANA, IMAGENES Y DEMAS
typedef struct s_data
{
	mlx_t			*mlx;
	t_map			*map;
	double			fov_projection;
	double			shift_distance;
	char			**img_charge;
	mlx_image_t		*image;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	t_player		player;
	t_rayc			rayc;
	int				checker;
}	t_data;

//validation
void			check_parameters(int ac, char **av, t_data *data);

//player
void			find_player(t_data *data, t_map *map);
void			move_player(t_data *data, double next_x, double next_y);

// init
t_map			*ini_map(t_data *data);
void			ini_imgs(t_data *data);

// texture parsing ang general function (gf)
int				search_textures(char *line, t_map *m, t_data *d, int c);
mlx_texture_t	*load_texture(char *f, t_data *d);

// number parsing
int				get_colors(char **split, t_map *m, t_data *d, int i);

// utils parseo
size_t			ft_strlen_double(char **split);
int				ft_strcmp(char *s1, char *s2);
int				skip_spaces(char **split);
int				skip_spaces_simple(char *line);
size_t			max_len_split(char **split);

// split double
char			**ft_split_double(const char *s, char c1, char c2, int i);

// error functions
void			ft_error(char *str, t_data *data);

// free functions
void			free_split(char **split);
void			free_structs(t_map *map, t_data *data);

// error map
void			check_characters(char *map, t_data *data);
char			**fill_spaces(char **split, t_data *data);
void			check_ones(char **s, t_data *data);

//parsing 
void			map_parsing(char *path, t_map *map, t_data *data);

//raycaster
void			raycastum(t_data *data);

//raycaster_utils
void			set_calculation(t_data *d);

//hooks
void			key_hook(mlx_key_data_t keydata, void *param);

//drawing_frame
void			draw_slice(t_data *data);
void			colouring(mlx_image_t *image, uint32_t x, uint32_t y,
					uint32_t colour);

void			close_window(void *param);
void			print_to_check(t_data *data, t_map *map);

#endif
