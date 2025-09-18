#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int ft_strlen(char *str){
    int count = 0;
        while(str[count])
            count++;
    return count;
}

typedef struct s_map{
    int height, width;
    char empty, obst, full;
    char **map;
} t_map;

int min3(int a, int b, int c){
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c); 
}

int validate_map(t_map *map){
    if (!map || map->height <=0 || map->width <= 0) return 0;
    if (map->empty == map->full || map->empty == map->obst || map->obst == map->full) return 0;

    for (int y = 0; y < map->height; y++){
        for (int x = 0; x < map->width; x++){
            char c = map->map[y][x];
            if (c != map->empty && c != map->obst) return 0;
        }
    }
    return 1;
}

t_map *read_map(char *filename){
    char *line = NULL;

    if(!filename){
        size_t len = 0;
        getline(&line, &len, stdin);
        int line_len = ft_strlen(line);
        if(line[line_len - 1] == '\n') line[line_len - 1] = '\0';
    }

    //printf("test: %s\n", line);
    FILE *file = filename ? fopen(filename, "r") : fopen(line, "r");
    if (!file) return NULL;
    free(line);

    t_map *map = malloc(sizeof(t_map));
    if (fscanf(file, "%d %c %c %c\n", &map->height, &map->empty, &map->obst, &map->full) != 4){
        free(map);
        if (filename) fclose(file);
        return NULL;
    }

    map->map = malloc(sizeof(char*) * map->height);
    map->width = 0;

    for (int i = 0; i < map->height; i++){
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, file) == -1){
            free(map);
            if(filename) fclose(file);
            return NULL;
        }

        int line_len = ft_strlen(line);

        if(line[line_len - 1] == '\n') line[line_len - 1] = '\0';

        if (i == 0)
            map->width = ft_strlen(line);
        else if(ft_strlen(line) != map->width){
            free(map);
            if(filename) fclose(file);
            return NULL;
        }

        map->map[i] = line;
    }

    if (filename) fclose(file);
    return map;
}

void solve_bsq(t_map *map){
    int **dp = malloc(sizeof(int*) * map->height);
    for (int i = 0; i < map->height; i++){
        dp[i] = malloc(sizeof(int) * map->width);
    }

    int max_size = 0, best_y = 0, best_x = 0;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if(map->map[y][x] == map->obst){
                dp[y][x] = 0;
            } else if(y == 0 || x == 0){
                dp[y][x] = 1;
            } else {
                dp[y][x] = min3(dp[y-1][x], dp[y][x-1], dp[y-1][x-1]) + 1;
            }

            if(dp[y][x] > max_size){
                max_size = dp[y][x];
                best_y = y;
                best_x = x;
            }
        }
    }

    //file the square
    int start_x = best_x - max_size + 1;
    int start_y = best_y - max_size + 1;

    for (int i = start_y; i< start_y + max_size; i++){
        for (int y = start_x; y < start_x + max_size; y++){
            map->map[i][y] = map->full;
        }
    }

    for(int i = 0; i < map->height; i++){
        free(dp[i]);
    }
    free(dp);
}

void print_map(t_map *map){
    for (int i = 0; i < map->height; i++)
        fprintf(stdout, "%s\n", map->map[i]);
}

void free_map(t_map *map){
    if (!map) return ;
    for (int i = 0; i < map->height; i++){
        free(map->map[i]);
    }
    free(map->map);
    free(map);
}

void process(char *filename){
    t_map *map = read_map(filename);
    if(!map || !validate_map(map)){
        fprintf(stderr, "map error\n");
        if(map) free(map);
        return ;
    }
    solve_bsq(map);
    print_map(map);
    free_map(map);
}


int main(int ac, char **av){
    if (ac == 1)
        process(NULL);
    else {
        for (int i = 1; i < ac; i++)
            process(av[i]);
    }
    return 1;
}