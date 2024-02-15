#include "./man_src/cub.h"

#define screenW 640
#define screenH 480

void init_width_height(t_data *img)
{
	t_data img2;
	img2.img = mlx_xpm_file_to_image(img->mlx, "./teapot.xpm", &img2.width, &img2.height);
	img->width = img2.width;
	img->height = img2.height;
}

int	main(void)
{
	t_data img;
	int *result;

	img.mlx = mlx_init();
	init_width_height(&img);
	img.win_ptr = mlx_new_window(img.mlx, screenW, screenH, "Hello World!");
	img.img = mlx_new_image(img.mlx, screenW, screenH);
	img.addr_tex = (int *)mlx_get_data_addr(img.img, &img.bits_pixel, &img.line_length, &img.endian);

	result = texture_copy(&img);

	int col = 0;
	int row = 0;
	int color;

	mlx_put_image_to_window(img.mlx, img.win_ptr, img.img, 0, 0);

	mlx_loop(img.mlx);
	return (0);
}
