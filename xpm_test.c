#include "./man_src/cub.h"

#define wid 1000
#define hei 1000

void init_width_height(t_data *img)
{
	t_data img2;
	img2.img = mlx_xpm_file_to_image(img->mlx, "/Users/josumin/Desktop/cub/teapot.xpm", &img2.width, &img2.height);
	img->width = img2.width;
	img->height = img2.height;
}

int	main(void)
{
	t_data img;
	int *result;

	img.mlx = mlx_init();
	init_width_height(&img);
	img.win_ptr = mlx_new_window(img.mlx, wid, hei, "Hello World!");
	img.img = mlx_xpm_file_to_image(img.mlx, "/Users/josumin/Desktop/cub/teapot.xpm", &img.width, &img.height);
	img.addr_tex = (int *)mlx_get_data_addr(img.img, &img.bits_pixel, &img.line_length, &img.endian);

for(int i = 0; i < hei; i++){
	for(int j = 0; j < wid; j++){
		int color;
	int height = img.height;
	int width = img.width;
	int result_row = (height * j) / hei;
	int result_col = (width * i) / wid;

	if (result_row < 0)
		result_row = 0;
	if (result_col < 0)
		result_col = 0;
	color = img.addr_tex[img.width * result_row + result_col];
		mlx_pixel_put(img.mlx, img.win_ptr, i, j, color);
	}
}

	mlx_put_image_to_window(img.mlx, img.win_ptr, img.img, 0, 0);

	mlx_loop(img.mlx);
	return (0);
}
