
#include "miniRT.h"

int	exit_game(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(0);
}
typedef struct  s_img
{
    void    *img_ptr;
    char    *data;
    int     size_l;
    int     bpp;
    int     endian;
}   t_img;

void	my_mlx_pixel_put(t_img *img, int x, int y)
{
    int     r;
    int     g;
    int     b;
    int     rgb_color;
    char	*dst;

    r = (int)(255.999 * ((double)x / 255));
    g = (int)(255.999 * ((double)y / 255));
    b = (int)(255.999 * 0.25);
    rgb_color = (r << 16) | (g << 8) | b;
    dst = img->data + (x * (img->bpp / 8)) + ((255 - y) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int main()
{
	//t_elements	elements;
	t_set 		set;
	t_img 		img;

	set.mlx = mlx_init();
	set.win = mlx_new_window(set.mlx, 1920, 1080, "miniRT");
	// mlx_hook(set.win, X_EVENT_KEYPRESS, 0, &exit_game, &set);
	img.img_ptr = mlx_new_image(set.mlx, 1920, 1080);
    img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
    int count_h = 256;
	int count_w;
    while (--count_h >= 0)
    {
        count_w = -1;
        while (++count_w < 256)
            my_mlx_pixel_put(&img, count_w, count_h);
    }
    mlx_put_image_to_window(set.mlx, set.win, img.img_ptr, 0, 0);
	mlx_hook(set.win, X_EVENT_DESTROYNOTIFY, 0, &exit_game, &set);
	mlx_loop(set.mlx);
	free(set.mlx);
	return (0);
}