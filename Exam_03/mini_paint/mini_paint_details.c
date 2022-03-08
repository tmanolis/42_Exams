#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
** This struct is the struct that countaint all the infos needed for the drawing zone
*/

typedef struct	s_zone
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

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/** 
* @brief Print the string send in params and return 1.
*
* @param str: Error message you want to print on the STDOUT 
*/

int	print_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

/** 
* @brief This function is called when a error occured or before closing the program. 
	It does 3 actions before closing :
	- close the file opened.
	- free the drawing allocated.
	- print if necessary and error message.
*
* @param file: the Operations file we opened and we want to close
* @param drawing: the str that stocks all characters that represent our drawing 
* @param str: Error message you want to print on the STDOUT 
*/

int	close_and_clear(FILE *file, char *drawing, char *str)
{
	if (file)
		fclose(file);
	if (drawing)
		free(drawing);
	if (str)
		print_error(str);
	return (1);
}

/** 
* @brief Read the first line of the Operations File. 
*	This line countains the params we need to define the drawing zone.
*	Scanf reads and fills the variables in the t_zone structure.
*	Then this function checks if the params we got are corrects.
*	This function returns 0 if an error occured.
*
* @param file: the file we want to read from (the Operations File)
* @param zone: the structure that will stock all the infos to define the drawing zone
*/

int	get_zone(FILE *file, t_zone *zone)
{
	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->bg_char) != 3)
		return (0);
	if ((zone->width <= 0 || zone->width > 300) || (zone->height <= 0 || zone->height > 300))
		return (0);
}

/** 
* @brief Malloc a str (char *) that represents the drawing zone.
	We fill it with the background character.
	Then we return the pointer to the drawing allocated.
	/!\ For more explainations :
	As we malloc a char* and not a char**, 
	the total size of the str we want to allocate we will be the multication of
	the width and the height.
*	
* @param zone: the structure stocks all the infos that define the drawing zone
*/

char	*fill_drawing_zone(t_zone *zone)
{
	int i;
	char *drawing;

	drawing = (char *)malloc(sizeof(char) * (zone->width * zone->height));
	if (!drawing)
		return (NULL);
	i = 0;
	while (i < zone->width * zone->height)
	{
		drawing[i] = zone->bg_char;
		i++;
	}
	return (drawing);
}

int	check(float x, float y, t_circle *tmp)
{
	float dist;

	dist = sqrtf(((x - tmp->x) * (x - tmp->x)) + ((y - tmp->y) * (y - tmp->y)));
	if (dist <= tmp->radius)
	{
		if ((tmp->radius - dist) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void	draw(t_circle *tmp, char *drawing, t_zone *zone)
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
			hit = check((float)x, (float)y, tmp);
			if ((hit == 2 && tmp->type == 'c') || (hit && tmp->type == 'C'))
				drawing[(y * zone->width) + x] = tmp->color;
			x++;
		}
		y++;
	}
}

int	draw_circles(FILE *file, char *drawing, t_zone *zone)
{
	t_circle	tmp;
	int			ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
	{
		if (tmp.radius <= 0.00000000 && (tmp.type != 'c' || tmp.type != 'C'))
		{
			
			return (0);
		}
			
		draw(&tmp, drawing, zone);	
	}
	if (ret != -1)
		return (0);
	return (1);
}

/** 
* @brief Print the final drawing
*	
* @param zone: the structure stocks all the infos from the drawing zone
* @param drawing: the drawing we want to print
*/

void	print_drawing(t_zone *zone, char *drawing)
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

int	main(int argc, char **argv)
{
	t_zone	zone;
	FILE	*file;
	char	*drawing;

	// Init variables
	zone.width = 0;
	zone.height = 0;
	zone.bg_char = 0;
	drawing = NULL;
	
	// Check if exec is launched with only one argument (it should be what is called 'The Operations File')
	if (argc != 2)
		return (print_error("Error: argument\n"));
	
	// Check if is it possible to read from the Operations file
	file = fopen(argv[1], "r");
	if (!file)
		return (print_error("Error: Operation file corrupted\n"));
	
	// Get params for the drawing zone and check if params are valids
	if (!get_zone(file, &zone))
		return (close_and_clear(file, drawing, "Error: Operation file corrupted\n"));
	
	// Fill the drawing zone with the background character (zone.bg_char) 
	drawing = fill_drawing_zone(&zone);
	if (!drawing)
		return (close_and_clear(file, drawing, NULL));
	
	// Draw the circles into the drawing
	if (!draw_circles(file, drawing, &zone))
		return (close_and_clear(file, drawing, "Error: Operation file corrupted\n"));
	
	// Print the drawing to the terminal
	print_drawing(&zone, drawing);

	// close and clear before leaving the program
	close_and_clear(file, drawing, NULL);
	return (0);
}
