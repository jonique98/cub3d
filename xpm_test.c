#include "./man_src/cub.h"
int	main(void)
{
	t_data img;

	img.mlx = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx, 1000, 1000, "putImage");
	img.img = mlx_xpm_file_to_image(img.mlx, "./reload_20.xpm", &img.width, &img.height);
	mlx_put_image_to_window(img.mlx, img.win_ptr, img.img, 250, 250);

	printf("width: %d, height: %d\n", img.width, img.height);
	mlx_loop(img.mlx);
	return (0);
}