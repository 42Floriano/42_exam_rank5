#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pen {
	int height;
	int width;
	char empty;
	char full;
	char obst;
	char **grid;
} t_map;

int init_map(t_map *map, FILE *file)
{
	if (!file || !map)
		return 0;
	size_t len = 0;
	ssize_t read = 0;
	char *line = NULL;

	read = getline(&line, &len, file);

	if (read == -1)
	{
		free(line);
		return 0;
	}
	int  i = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->height = map->height * 10 + (line[i] - '0');
		i++;
	}
	if (i == 0 || map->height <= 0)
	{
		free(line);
		return 0;
	}
	if (read < i + 3)
	{
		free(line);
		return 0;
	}
	map->empty = line[i++];
	map->obst = line[i++];
}

int main(int ac, char **av)
{
	if (ac == 1)
	{
		t_map map = {0};
		if (!init_map(&map, stdin) || !read_grid(&map, stdin))
		{
		}
	}
}