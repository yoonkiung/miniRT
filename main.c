
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

void	my_mlx_pixel_put(t_img *img, int x, int y, t_sphere sp)
{
    int     rgb_color;
    char	*dst;

    rgb_color = (sp.red << 16) | (sp.green << 8) | sp.blue;
    dst = img->data + (x * (img->bpp / 8)) + ((255 - y) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int hit_sphere(t_sphere sp, t_ray ray)
{
	t_vec3   oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;

    oc = vec3_sub(ray.pos, sp.pos);
    a = vec3_dot(ray.dir, ray.dir);
    b = vec3_dot(oc, ray.dir);
    c = vec3_dot(oc, oc) - ((sp.dia / 2) * (sp.dia / 2));
    discriminant = b * b - a * c; // 점화식
    if (discriminant >= 0)
        return (1);
    return (0);
}

int main()
{
	//t_elements	elements;
	t_set 		set;
	t_img 		img;
	t_sphere	sph;
	t_ray		ray;
	t_camera 	cam;

	set.mlx = mlx_init();
	set.win = mlx_new_window(set.mlx, 1920, 1080, "miniRT");
	// mlx_hook(set.win, X_EVENT_KEYPRESS, 0, &exit_game, &set);
	img.img_ptr = mlx_new_image(set.mlx, 1920, 1080);
    img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    int count_h = sph.pos.y;
	int count_w;
	sph.pos = vec3_set(100, 0, 0);
	sph.dia = 3.0;
	sph.red = 255;
	sph.green = 100;
	sph.blue = 255;
	cam.pos = vec3_set(0, 0, 0);
	cam.norm = vec3_set(1, 0, 0);
	cam.fov = 90;
    while (--count_h >= 0)
    {
        count_w = -1;
        while (++count_w < sph.pos.x)
		{
			if (hit_sphere(sph, ray))
				my_mlx_pixel_put(&img, count_w, count_h, sph);
		}
    }
    mlx_put_image_to_window(set.mlx, set.win, img.img_ptr, 0, 0);

	mlx_hook(set.win, X_EVENT_DESTROYNOTIFY, 0, &exit_game, &set);
	mlx_loop(set.mlx);
	free(set.mlx);
	return (0);
}