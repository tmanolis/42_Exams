#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct	s_zone
{
	int		width;
	int		height;
	char	bg_char;
}				t_zone;

typedef struct	s_circle
{
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
}				t_circle;

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int print_error(char *str)
{
    if (str)
        write(1, str, ft_strlen(str));
    return (1);
}

int close_and_clear(FILE *file, char *drawing, char *str)
{
    if (file)
        fclose(file);
	if (drawing)
		free(drawing);
	if (str)
		print_error(str);
    return (1);
}

char *get_zone(FILE *file, t_zone *zone)
{
	char *drawing;
	int i;

	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->bg_char) != 3)
		return (NULL);
	if ((zone->width <= 0 || zone->width > 300) || (zone->height <= 0 || zone->height > 300))
		return (NULL);
	drawing = (char *)malloc(sizeof(char) * (zone->width * zone->height));
	if (!drawing)
		return (NULL);
	i = 0;
	while (i < (zone->width * zone->height))
	{
		drawing[i] = zone->bg_char;
		i++;
	}
	return (drawing);
}

int	draw_circles(FILE *file, char *drawing, t_zone *zone)
{
	t_circle	tmp;
	int			ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
	{

	}
	if (ret == -1)
		return (0);
	return (1);
}

void	print_drawing(char *drawing, t_zone *zone)
{
	int i;

	i = 0;
	while (i < zone->height)
	{
		write(1, drawing + (i *zone->width), zone->width);
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv)
{
    FILE    *file;
	t_zone	zone;
    char    *drawing;

	zone.width = 0;
	zone.height = 0;
	zone.bg_char = 0;
	drawing = NULL;
    if (argc != 2)
        return (print_error("Error: argument\n"));
    file = fopen(argv[1], "r");
    if (!file)
        return (print_error("Error: Operation file corrupted\n"));
    if (!(drawing = get_zone(file, &zone)))
		return (close_and_clear(file, drawing, "Error: Operation file corrupted\n"));
	if (!draw_circles(file, drawing, &zone))
		return (close_and_clear(file, drawing, "Error: Operation file corrupted\n"));
	print_drawing(drawing, &zone);
	close_and_clear(file, drawing, NULL);
    return (0);
}