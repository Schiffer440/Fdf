/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:31:31 by adugain           #+#    #+#             */
/*   Updated: 2023/05/24 12:04:06 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#define MLX_ERROR 1
#define RED_PIX 0xff0000
#define GREEN_PIX 0x00ff00
#define BLUE_PIX 0x0000ff
#define WHITE_PIX 0xffffff
#define DARK_PIX 0x000000

typedef struct s_img
{
        void    *mlx_img;
        char    *addr;
        int     bpp;
        int     line_len;
        int     endian;
}       t_img;

 typedef struct s_fdf
{
        void    *mlx;
        void    *win;
	t_img   img;
	int     win_x;
	int     win_y;
}	t_fdf;
        
typedef struct s_rect
{
        int     x;
        int     y;
        int     h;
        int     l;
        int     color;
}       t_rect;




int     key_hook(int key, t_fdf *fdf)
{
        if (key == XK_Escape)
        {
               mlx_destroy_window(fdf->mlx, fdf->win);
               fdf->win = NULL;
        }
        return (0);
}
/*index formula --> index = line_len * y + x * (bpp / 8) */

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int	i;
	
	i = img->bpp - 8;
	pixel = img->addr + (img->line_len * y + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int     render_dot(t_fdf *fdf)
{
        if (fdf->win != NULL)
                img_pix_put(&fdf->img, fdf->win_x / 2, fdf->win_y / 2, RED_PIX);
        return (0);
}

int     render_rect(t_img *img, t_rect rect)
{
        int     i;
        int     j;

	i = rect.y;
        while (i < rect.y + rect.h)
        {
                j = rect.x;
                while (j < rect.x + rect.l)
                        img_pix_put(img, j++, i, rect.color);
                ++i;
        }
        return (0);
}

void    render_bg(t_fdf *fdf, int color)
{
        int     i;
        int     j;
        
	i = 0;
        while (i < fdf->win_y)
        {
                j = 0;
                while (j < fdf->win_x)
                        img_pix_put(&fdf->img, j++, i, color);
                ++i;
        }
}

int     render(t_fdf *fdf)
{
        render_bg(fdf, DARK_PIX);
        render_dot(fdf);
        render_rect(&fdf->img, (t_rect){fdf->win_x - 100, fdf->win_y -100,
                100, 100, GREEN_PIX});
        render_rect(&fdf->img, (t_rect){0, 0, 100, 100, RED_PIX});
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.mlx_img, 0, 0);
        return (0);
}

int     main()
{
        
        t_fdf   fdf;

        fdf.win_x = 600;
        fdf.win_y = 300;
        fdf.mlx = mlx_init();
        if (fdf.mlx == NULL)
                return (MLX_ERROR);
        fdf.win = mlx_new_window(fdf.mlx, fdf.win_x, fdf.win_y, "Fdf");
        if (fdf.win == NULL)
        {
                free(fdf.win);
                return (MLX_ERROR);
        }
	fdf.img.mlx_img = mlx_new_image(fdf.mlx, fdf.win_x, fdf.win_y);
	fdf.img.addr = mlx_get_data_addr(fdf.img.mlx_img, &fdf.img.bpp, &fdf.img.line_len, &fdf.img.endian);
        mlx_loop_hook(fdf.mlx, &render, &fdf);
        mlx_hook(fdf.win, KeyPress, KeyPressMask, &key_hook ,&fdf);
        mlx_loop(fdf.mlx);
	mlx_destroy_image(fdf.mlx, fdf.img.mlx_img);
        mlx_destroy_display(fdf.mlx);
        free(fdf.mlx); 
        return (0);
}