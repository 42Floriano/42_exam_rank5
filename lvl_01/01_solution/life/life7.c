#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pen
{
    int y, x, is_down;
} t_pen;

char **init_map(int height, int width){
    char **map = malloc(sizeof(char*) * height);
    if(map == NULL) return NULL;
    for (int y = 0; y < height; y++){
        map[y] = malloc(sizeof(char) * width);
        if (map[y] == NULL) return NULL;
        for (int x = 0; x < width; x++){
            map[y][x] = ' ';
        }
    }
    return map;
}

void print_map(char **map, int height, int width){
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            putchar(map[y][x]);
        }
        putchar('\n');
    }
}

void free_map(char **map, int height){
    for (int y = 0; y < height; y++){
        free(map[y]);
    }
    free(map);
}

int count_nbh(char **map, int height, int width, int y, int x){
    int count = 0;
    for(int yi = -1; yi <= 1; yi++){
        for(int xi = -1; xi <= 1; xi++){
            if(xi == 0 && yi == 0)
                continue ;
            
            int new_y = y + yi;
            int new_x = x + xi;

            if(new_y >= 0 && new_y < height && new_x >= 0 && new_x < width)
                if(map[new_y][new_x] == 'O')
                    count++;
        }
    }
    return count;
}

void iter_map(char **map, int height, int width){
    char **new_map = init_map(height, width);
    if(new_map == NULL) return ;

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int count = count_nbh(map, height, width, y, x);
            if(map[y][x] == 'O'){
                if (count == 2 || count == 3)
                    new_map[y][x] = 'O';
            } else {
                if(count == 3)
                    new_map[y][x] = 'O';
            }
        }
    }

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            map[y][x] = new_map[y][x];
        }
    }
    free_map(new_map, height);
}

int main(int ac, char**av){
    if (ac != 4) return 1;
    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iter = atoi(av[3]);
    char command;
    if(width <= 0 || height <= 0 || iter < 0) return 1;
    t_pen pen = {0,0,0};
    char **map = init_map(height, width);
    if (map == NULL) return 1;

    while(read(0, &command, 1) > 0){
        if(pen.is_down)
            map[pen.y][pen.x] = 'O';
        switch(command)
        {
        case 'w':
            if(pen.y > 0)
                pen.y--;
            break;
        case 's':
            if(pen.y < height -1)
                pen.y++;
            break;
        case 'a':
            if(pen.x > 0)
                pen.x--;
            break;
        case 'd':
            if(pen.x < width -1)
                pen.x++;
            break;
        case 'x':
            pen.is_down = !pen.is_down;
            break;
        }
        if(command == '\n')
            break ;
    }

    //print_map(map, height, width);
    for(int i = 0; i < iter; i++)
        iter_map(map, height, width);
    print_map(map, height, width);
    free_map(map, height);
    return 0;
}
