 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>

typedef struct	s_zone
{
	int 	width;
	int		height;
	char	bg_char;
}				t_zone;

typedef struct	s_rec
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
}				t_rec;


int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	close_and_clear(FILE *file, char *drawing, char *str)
{
	if (file)
		fclose(file);
	if (drawing)
		free(drawing);
	if (str)
		print_error("Error: Operation file corrupted\n");
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

void	print_drawing(char *drawing, t_zone *zone)
{
	int i;

	i = 0;
	while (i < zone->height)
	{
		write(1, drawing + (i * zone->width), zone->width);
		write(1, "\n", 1);
		i++;
	}
}

int	check_rec(float x, float y, t_rec *tmp)
{
	float	check; 
	
	check = 1.00000000;
    if ((x < tmp->x) || (tmp->x + tmp->width < x) || (y < tmp->y) || (tmp->y + tmp->height < y))
		return (0);
    if (((x - tmp->x) < check) || ((tmp->x + tmp->width) - x < check) || ((y - tmp->y) < check) || ((tmp->y + tmp->height) - y < check))
		return (2);
	return (1);
}

void	draw(t_zone *zone, char *drawing, t_rec *tmp)
{
	int x;
	int y;
	int hit;

	y = 0;
	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			hit = check_rec((float)x, (float)y, tmp);
			if ((hit == 2 && tmp->type == 'r') || (hit && tmp->type == 'R'))
				drawing[(y * zone->width) + x] = tmp->color;
			x++;
		}
		y++;
	}
}

int	check_line(t_rec *tmp)
{
	return ((tmp->type == 'r' || tmp->type == 'R') && (tmp->width > 0.00000000 || tmp->height > 0.00000000));
}

int	draw_rec(FILE *file, char *drawing, t_zone *zone)
{
	t_rec	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6)
	{
		if (!check_line(&tmp))
			return (0);
		draw(zone, drawing, &tmp);
	}
	if (ret != -1)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	FILE 	*file;
	t_zone	zone;
	char 	*drawing;

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
		return (close_and_clear(file, NULL, "Error: Operation file corrupted\n"));
	if (!draw_rec(file, drawing, &zone))
		return (close_and_clear(file, NULL, "Error: Operation file corrupted\n"));
	print_drawing(drawing, &zone);
	close_and_clear(file, drawing, NULL);
	return (0);
}