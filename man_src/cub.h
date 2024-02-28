/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:57:32 by jiko              #+#    #+#             */
/*   Updated: 2024/02/28 20:24:56 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080
# define TEXTWIDTH 128
# define TEXTHEIGHT 128

typedef struct s_key
{
	int	left_rotate;
	int	right_rotate;
	int	left;
	int	right;
	int	forward;
	int	backward;
	int	down;
	int	mouse_x;
	int	mouse_y;
	int	mouse_press;
}	t_key;

typedef struct s_data
{
	void	*win_ptr;
	void	*mlx;
	void	*img;
	char	*addr;
	int		*addr_tex;
	int		bits_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_cor
{
	int	x;
	int	y;
}	t_cor;

typedef struct s_frame
{
	double	time;
	double	frame_time;
	double	move_speed;
	double	rot_speed;
}	t_frame;

typedef struct s_vectorset
{
	int		up;
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_vec_set;

typedef struct s_map
{
	int		**map;
	int		map_flag;
	int		map_start;
	int		map_width;
	int		map_height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_ray
{
	double	camera_x;
	t_vec	ray_dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	double	perpwall_dist;
	t_cor	step;
	t_cor	map;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		hit;
}	t_ray;

typedef struct s_texture
{
	char	*tex_path;
	int		*texture;
	int		width;
	int		height;
}	t_texture;

typedef struct s_texture_var
{
	double	wallx;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		direction;
}	t_texture_var;

typedef struct s_var
{
	t_data			*image;
	t_vec_set		*vec;
	t_key			*key;
	t_frame			*frame;
	t_map			*map;
	t_ray			*ray;
	t_texture		tex[4];
	t_texture_var	tex_var;
}	t_var;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	make_new_img(t_data *image);
void	draw_background(int line, t_data *image);
void	draw(t_var *var);
void	init_vec_set(t_vec_set *vec, t_map *map);
void	init_key(t_key *key);
void	init_frame(t_frame *frame);
void	move_forward(t_var *var);
void	move_backward(t_var *var);
void	move_left(t_var *var);
void	move_right(t_var *var);
void	rotate_left(t_var *var);
void	rotate_right(t_var *var);
void	draw_map(t_var *var);
int		key_press(int key_code, t_var *var);
int		key_lift(int key_code, t_var *var);
int		render(t_var *var);
void	init_mlx(t_data *image);
void	init_map(int argv, char **argc, t_map *map);
void	*wft_calloc(int count, int size);
int		ft_exit(int ret, char *str);
int		get_next_line(int fd, char **dest);
char	*wft_strdup(const char *src);
char	*wft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen_doble(char **str);
int		ft_color(char *str);
char	**wft_split(char const *str, char c);
char	**double_free(int i, char	**be_return);
int		double_free_int(int i, int **be_return);
void	safe_free(void *ptr);
int		ft_max(int a, int b);
int		rgb_translate(int color);
void	init_ray(t_ray *ray);
void	calculate_ray_values(t_var *var, int x);
void	calculate_side_dist(t_var *var);
void	calculate_wall_hit_dda(t_var *var);
void	calculate_distance_between_wall(t_var *var);
void	calculate_draw_start_end(t_var *var);
void	draw_sq(t_data *img, int x, int y, int color);
void	copy_texture(t_data *img, t_var *var, int idx);
void	init_texture_direction(char *path, t_data *img, t_var *var, int idx);
void	init_texture(t_data *img, t_var *var);
void	texture_mapping(t_var *var);
int		open_cube(int argc, char **argv, t_map *map);
void	dfs(t_map *map, int **visited, int x, int y);
void	dfs_valid_map(t_map *map);
int		is_param_full(t_map *map);
int		ft_color_atoi(char *str);
int		ft_color(char *str);
int		is_map(char *line);
void	remove_space_side(char **line, t_map *map);
void	set_param_if_char(t_map *map, char **s);
void	set_param_elif_char(t_map *map, char *line);
void	set_param_if_null(char *line, t_map *map);
int		check_valid_string(char **s);
void	if_check_vaild_string(char **s, t_map *map, char *line);
void	init1(t_var *var);
void	init2(t_var *var);
int		mouse_event_draw(int x, int y, t_var *var);
int		mouse_press(int button, int x, int y, t_var *var);
int		is_inside_map(int x, int y, t_map *map);

#endif