#include "cub3d.h"

int	color_int(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}
