#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pen {
    int y, x;
    int is_down;
} t_pen;

char **init_map(int height, int width){
    char **map = malloc(sizeof(char*) * height);
    for (int y = 0; y < height; y++){
        map[y] = malloc(sizeof(char) * width);
        for (int x = 0; x < width; x++)
            map[y][x] = ' ';
    }
    return map;
}

void free_map(char **map, int height){
    for (int y = 0; y < height; y++){
        free(map[y]);
    }
    free(map);
}

void print_map(char **map, int height, int width){
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++)
            putchar(map[y][x]);
        putchar('\n');
    }
}

int count_nbh(char **map, int height, int width, int y, int x){
    int count = 0;
    for (int yi = -1; yi <= 1; yi++){
        for (int xi = -1; xi <= 1; xi++){
            if(yi == 0 && xi == 0)
                continue;
            int new_y = y + yi;
            int new_x = x + xi;

            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height){
                if(map[new_y][new_x] == 'O')
                    count++;
            }
        }
    }
    return count;
}

void iter_map(char **map, int height, int width){
    char **new_map = init_map(height, width);

     for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
         int count = count_nbh(map, height, width, y, x);
         printf("Test at pos y:%d, x%d, count:%d \n", y, x, count);
         if (map[y][x] == 'O'){
            if (count == 2 || count == 3)
                new_map[y][x] = 'O';
         } else {
            if (count == 3)
                 new_map[y][x] = 'O';
         }
        }
    }

     for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++)
            map[y][x] = new_map[y][x];
    }
    free_map(new_map, height);
}

int main(int ac, char **av){
    if (ac != 4) return 1;
    int height = atoi(av[2]);
    int width = atoi(av[1]);
    int iter = atoi(av[3]);
    char command;
    if (height <= 0 || width <= 0 || iter < 0) return 1;

    t_pen pen = {0,0,0};
    char **map = init_map(height, width);
    while(read(0, &command, 1) > 0){
        if (pen.is_down)
            map[pen.y][pen.x] = 'O';
        switch(command){
            case 'w':
                if(pen.y > 0) 
                    pen.y--;
                break ;
            case 's':
                if(pen.y < height -1) 
                    pen.y++;
                break ;
            case 'a':
                if(pen.x > 0) 
                    pen.x--;
                break ;
            case 'd':
                if(pen.x < width -1) 
                    pen.x++;
                break ;
            case 'x':
                pen.is_down = !pen.is_down;
                break ;
        }
        if (command == '\n') break;
    }
    for (int i = 0; i < iter; i++)
        iter_map(map, height, width);
    print_map(map, height, width);
    free_map(map, height);
    return 0;
}