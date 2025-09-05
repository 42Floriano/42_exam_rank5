#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_pen {
    int x;
    int y;
    int is_down;
} t_pen;

char **init_map(int width, int height){
    char **map = malloc(sizeof(char*) * height);
        //if null
    for (int y = 0; y < height; y++){
        map[y] = malloc(sizeof(char) * width);
        for(int x = 0; x < width; x++){
            map[y][x] = '.';
        }
    }
    return map;
}

void print_map(char **map, int height, int width){
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

void free_map(char** map, int height){
    for (int i = 0; i < height; i++){
        free(map[i]);
    }
    free(map);
}

int count_nachbar(char **map, int height, int width, int y , int x){
    int count = 0;
    for(int i = -1; i <=1 ; i++){
        for(int j = -1; j <= 1; j++){
            if (i == 0 && j == 0)
                continue ;
            int new_y = y + i;
            int new_x = x + j;
            if (new_x < width && new_x >= 0 && new_y < height && new_y >= 0)
            if(map[new_y][new_x] == '0')
                count++;
        }
        printf("test count: %d \n", count);
    }
    return count;
}

void iter_map(char **map, int height, int width){
    char **new_map = init_map(width, height);
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int count = count_nachbar(map, height, width, y, x);
            if(map[y][x] == '0'){
                if (count == 2 || count == 3)
                    new_map[y][x] = '0';
            } else {
                if (count == 3)
                    new_map[y][x] = '0';
            }
        }
    }
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            map[y][x] = new_map[y][x];
        }
    }
    free(new_map);
}

int main (int ac, char** av){
    if (ac != 4) return 1;
    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iter = atoi(av[3]);
    char command;
    t_pen pen = {0,0,0};

    if (width <= 0 || height <= 0 || iter < 0) return (1);
    char **map = init_map(width, height);
    if (map == NULL) return (1);

    while(read(0, &command, 1) > 0){
        if (pen.is_down)
            map[pen.y][pen.x] = '0';
        switch (command)
        {
        case 'w':
            if(pen.y > 0)
                pen.y--;
            break;
        case 's':
             if(pen.y < height - 1)
                pen.y++;
            break;
        case 'a':
             if(pen.x > 0)
                pen.x--;
            break;
        case 'd':
             if(pen.x < width - 1)
                pen.x++;
            break;
        case 'x':
            pen.is_down = !pen.is_down;
             break;
        }
    }
    print_map(map, height, width);
    for (int i = 0; i < iter; i++)
        iter_map(map, height, width);
    print_map(map, height, width);
    free_map(map, height);
    return (0);
}