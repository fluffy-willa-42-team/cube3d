
#include "cube3d.h"

void draw_line(double x1, double y1, double x2, double y2, int32_t color)
{
	float step;
	float dx = (x2 - x1);
	float dy = (y2 - y1);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	float x = x1;
	float y = y1;
	int i = 1;
	while (i <= step) {
		if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
			mlx_put_pixel(g_img, x, y, color);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

void draw_line_coord(double x1, double y1, double x2, double y2, int32_t color)
{
	draw_line(x1 * MINIMAP_SIZE, y1 * MINIMAP_SIZE, x2 * MINIMAP_SIZE, y2 * MINIMAP_SIZE, color);
}

void draw_square(float x, float y, int size, int32_t color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (0 <= x && x + i < WIDTH && 0 <= y && y + j < HEIGHT)
				mlx_put_pixel(g_img, x + i, y + j, color);
		}
	}
}

void draw_minimap(void)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			draw_square(x * MINIMAP_SIZE, y * MINIMAP_SIZE, MINIMAP_SIZE, 0x111111ff);
			if (map[y][x] == 1)
				draw_square(x * MINIMAP_SIZE + 2, y * MINIMAP_SIZE + 2, MINIMAP_SIZE - 4, 0xffff22ff);
			else
				draw_square(x * MINIMAP_SIZE + 2, y * MINIMAP_SIZE + 2, MINIMAP_SIZE - 4, 0x333333ff);
		}
	}
}

