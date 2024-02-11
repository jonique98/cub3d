
#ifndef CUB_H
# define CUB_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
// # include <mlx.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1000
#define screenHeight 1000

typedef struct s_key
{
	int	left_rotate;
	int	right_rotate;
	int	left;
	int	right;
	int	forward;
	int	backward;
	int	up;
	int	down;
}t_key;

typedef struct s_data
{
	void	*win_ptr;
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_pos
{
	double	x;
	double	y;
}t_pos;

typedef struct s_dir
{
	double	x;
	double	y;
}t_dir;

typedef struct s_plane
{
	double	x;
	double	y;
}t_plane;

typedef struct s_frame
{
	double	time;
	double	oldTime;
	double	frameTime;
	double	moveSpeed;
	double	rotSpeed;
}t_frame;


typedef struct s_vec
{
	int		up;
	t_pos	pos;
	t_dir	dir;
	t_plane	plane;
}t_vec;

typedef struct s_map
{
	int		**map;
	int		map_flag;
	int		map_start;
	int		map_width;
	int		map_height;
	char 	*no;
	char 	*so;
	char 	*we;
	char 	*ea;
	int		floor;
	int		ceiling;
	int		player_x;
	int		player_y;
	char	player_dir;
}t_map;

typedef struct s_var
{
	t_data	*image;
	t_vec	*vec;
	t_key	*key;
	t_frame	*frame;
	t_map	*map;
} t_var;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	make_new_img(t_data *image);
void	draw_background(t_var *var, int line, t_data *image);
void	draw(t_var *var);
void	init_vec(t_vec *vec);
void	init_key(t_key *key);
void	init_frame(t_frame *frame);
void	move_forward(t_var *var);
void	move_backward(t_var *var);
void	move_left(t_var *var);
void	move_right(t_var *var);
void	rotate_left(t_var *var);
void	rotate_right(t_var *var);
void	draw_map(t_var *var, t_data *image, t_vec *vec);
int		key_press(int key_code, t_var *var);
int		key_lift(int key_code, t_var *var);
int		render(t_var *var);
int		get_time(void);
void	init_mlx(t_data *image);
void 	init_map(int argv, char **argc, t_map *map);
void	*wft_calloc(int count, int size);
int		ft_exit(int ret, char *str);
int		get_next_line(int fd, char **dest);
char	*wft_strdup(const char *src);
char	*wft_substr(char const *s, unsigned int start, size_t len);
int 	ft_strlen_doble(char **str);
int		ft_color(char *str);
char	**wft_split(char const *str, char c);
char	**double_free(int i, char	**be_return);
void	safe_free(void *ptr);
int		ft_max(int a, int b);

# endif