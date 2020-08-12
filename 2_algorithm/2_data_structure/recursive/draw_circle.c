#include <stdio.h>
#include <mlx.h>
#include <math.h>

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



void	draw_cirlce(t_mlx *mlx, int x, int y, int r, int color)
{
	int i;

	i = 0;
	while (i <= M_PI * 2)
	{
		mlx->i_dat[y * IMAG_H + x] = color;
		i += 0.01;
	}
}

int		main(void)
{
	t_mlx	mlx;
	
	mlx.mlx = mlx_init();
	mlx.wind = mlx_new_window(mlx.mlx, WIND_W, WIND_H, "jinbkim");
	mlx.imag = mlx_new_image(mlx.mlx, IMAG_W, IMAG_H);
	mlx.i_dat = (int *)mlx_get_data_addr(mlx.imag, &mlx.bpp, &mlx.size_l, &mlx.endi);

	draw_circle(&mlx, 500, 500, 100, 0xff0000);

	mlx_put_image_to_window(mlx.mlx, mlx.wind, mlx.imag, 0 , 0);
	mlx_loop(mlx.mlx);
}