#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pen{
    int y;
    int x;
    int is_down;
} t_pen;

char **init_map(int height, int width){
    char **map = malloc(sizeof(char*) * height);
    if (map == NULL) return NULL;
     for (int i = 0; i < height; i++){
        map[i] = malloc(sizeof(char) * width);
        if (map[i] == NULL) return NULL;
      for (int j = 0; j < width; j++){
        map[i][j] = '.';
      }
    }
    return map;
}

void draw_map(char **map, int height, int width){
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        printf("%c", map[i][j]);
      }
      printf("\n");
    }
}

void free_map(char **map, int height){
    for (int i = 0; i < height; i++)
        free(map[i]);
    free(map);
}

int count_nachbar(char**map, int height, int widht, int y, int x){
    int count = 0;
    for(int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (j == 0 && i == 0)
                continue ;
            int new_y = y + i;
            int new_x = x + j;
            if (new_x < widht && new_x >= 0 && new_y < height && new_y >= 0)
                if (map[new_y][new_x] == '0')
                    count++;
        }
    }
    return count;
}

void iter_map(char **map, int height, int width){
    char **n_map = init_map(height, width);
    if (n_map == NULL) return ;

    for (int y = 0; y < height; y++){
      for (int x = 0; x < width; x++){
        int count = count_nachbar(map, height, width, y, x);
        if (map[y][x] == '0'){
            if (count == 2 || count == 3)
                n_map[y][x] = '0';
        } else {
            if (count == 3)
                n_map[y][x] = '0';
        }
      }
    }

     for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        map[i][j] = n_map[i][j];
      }
    }
      free_map(n_map, height);
} 


int main(int ac, char **av){
    if(ac != 4) return 1;
    int height = atoi(av[1]);
    int width = atoi(av[2]);
    int iter = atoi(av[3]);
    char command;
    t_pen pen = {0,0,0};

    if (height <= 0 || width <= 0 || iter < 0) return 1;
    char **map = init_map(height, width);
    if (map == NULL) return 1;

    while(read(0, &command, 1) > 0){
        if(pen.is_down)
            map[pen.y][pen.x] = '0';
        switch(command){
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
                if(pen.x < width)
                    pen.x++;
                break;
            case 'x':
                pen.is_down = !pen.is_down;
                break;
        }
    }
    draw_map(map, height, width);
    for (int i = 0; i < iter; i++)
        iter_map(map, height, width);
    draw_map(map, height, width);
    free_map(map, height);
    return (0);
}