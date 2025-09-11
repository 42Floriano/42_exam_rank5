#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_pen{
    int y;
    int x;
    int is_down;
} t_pen;

char **init_map(int height, int width){
    char **map;
    map = malloc(sizeof(char*) * height);
    for(int y = 0; y < height; y++){
        map[y] = malloc(sizeof(char) * width);
        for (int x = 0; x < width; x++){
            map[y][x] = '.';
        } 
    }
    return map;
}

void print_map(char **map, int height, int width){
    for(int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

void free_map(char **map, int height){
    for (int y = 0; y < height; y++){
        free(map[y]);
    }
    free(map);
}

int count_nachbar(char **map, int height, int width){

}

void iter_map(char **map, int height, int width){
    char **new_map = init_map(height, width);
    if (new_map == NULL) return ;
    for(int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if
        }
        printf("\n");
    }
    free(new_map);
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
    if (map == NULL) return 1;

    while(read(0, &command, 1) > 0){
        if (pen.is_down)
            map[pen.x][pen.y] = '0';
        switch (command){
            case 'w':
                if (pen.x > 0)
                    pen.x--;
                break ;
            case 's':
                if (pen.x < height -1)
                    pen.x++;
                break ;
            case 'a':
                if (pen.y > 0)
                    pen.y--;
                break ;
            case 'd':
                if (pen.y < width -1)
                    pen.y++;
                break ;
            case 'x':
                pen.is_down = !pen.is_down;
                break ;   
        }
    }
    print_map(map, height, width);
    for (int i = 0; i < iter; i++)
        iter_map(map, height, width);
    print_map(map, height, width);
    free_map(map, height);
    return 0;
}