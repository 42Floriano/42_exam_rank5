#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pen{
    int x;
    int y;
    int is_down;
} t_pen;

char **new_map(int width, int height){
    char **nmap = malloc(sizeof(char*) * (height));
    if (nmap == NULL) return nmap;
    for (int i = 0; i < height; i++){
        nmap[i] = malloc(sizeof(char) * width);
        if (nmap[i] == NULL) return NULL;
        for(int j = 0; j < width; j++)
            nmap[i][j] = '.';
    }
    return nmap;
}

void draw_map(char **map, int width, int height){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            putchar(map[i][j]);
        }
        putchar('\n');
    }
}

void free_map(char** map, int height){
    int i = 0;
    while(map && i < height){
        free(map[i]);
        i++;
    }
    free(map);
}

int count_nachbar(char **map, int x, int y, int width, int height){
    int count = 0;
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0)
                continue ;
            int new_y = y + i;
            int new_x = x + j;
            if(new_y >= 0 && new_y < height && new_x >= 0 && new_x < width)
                if (map[new_x][new_y] == '0')
                    count++;
        }
        printf("test count: %d \n", count);
    }
    return count;
}

int iter_map(char **map, int width, int height){
    char **n_map = new_map(width, height);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int count = count_nachbar(map, x, y,  width, height);
            if (map[x][y] == '0'){
                if(count == 2 || count == 3)
                    n_map[x][y] = '0';
            } else {
                if(count == 3)
                    n_map[x][y] = '0';
            }
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            map[i][j] = n_map[i][j];
        }
    }
    free_map(n_map, height);
    return (0);
}


int main(int ac, char** av){
    if (ac != 4) return 1;

    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iter = atoi(av[3]);
    char command;
    t_pen pen = {0, 0, 0};

    if (height <= 0 || width <= 0 || iter < 0) return 1;
    char **map = new_map(width, height);
        if (map == NULL) return 1;
    
    while (read(0, &command, 1) > 0){
        if(pen.is_down)
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
    draw_map(map, width, height);
    printf("\n");
    for(int x = 0; x < iter; x++)
        iter_map(map, width, height);
    draw_map(map, width, height);
    free_map(map, height);
    return (1);
}