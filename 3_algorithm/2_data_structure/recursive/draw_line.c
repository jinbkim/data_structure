#include <stdio.h>
#include <mlx.h>

# define WIND_W 1000
# define WIND_H	1000
# define IMAG_W	900
# define IMAG_H	900

typedef	struct	s_mlx
{
	void		*mlx;
	void		*wind;
	void		*imag;
	
	int			*i_dat;
	int			bpp;
	int			size_l;
	int			endi;
}				t_mlx;



void	draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, int color)
{
	if (-1 <= x1 - x2 && x1 - x2 <= 1 && -1 <= y1 - y2 && y1 - y2 <= 1)
		return ;
	else
	{
		// mlx_pixel_put(mlx->mlx, mlx->wind, (x1 + x2) / 2, (y1 + y2) / 2, color);
		mlx->i_dat[(y1 + y2) / 2 * IMAG_H + (x1 + x2) / 2] = color;
		draw_line(mlx, x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, color);
		draw_line(mlx, x2, y2, (x1 + x2) / 2, (y1 + y2) / 2, color);
	}
}



int		main(void)
{
	t_mlx	mlx;
	
	mlx.mlx = mlx_init();
	mlx.wind = mlx_new_window(mlx.mlx, WIND_W, WIND_H, "jinbkim");
	mlx.imag = mlx_new_image(mlx.mlx, IMAG_W, IMAG_H);
	mlx.i_dat = (int *)mlx_get_data_addr(mlx.imag, &mlx.bpp, &mlx.size_l, &mlx.endi);

	draw_line(&mlx, 100, 100, 300, 600, 0xff0000);

	mlx_put_image_to_window(mlx.mlx, mlx.wind, mlx.imag, 0 , 0);
	mlx_loop(mlx.mlx);
}