#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

typedef struct s_map{
    int height, width;
    char empty, obst, full;
    char **map;
} t_map;

int ft_strlen(char *str){
    int count = 0;
    while(str && str[count])
        count++;
    return count;
}

void print_map(t_map *map){
    for (int y = 0; y < map->height; y++){
        fprintf(stdout, "%s\n", map->map[y]);
    }
}

void free_map(t_map *map){
    if(!map) return ;
    if(map->map){
        for(int y = 0; y < map->height; y++){
            free(map->map[y]);
        }
        free(map->map);
    }
    free(map);
}

int min3(int a, int b, int c){
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

int validate_map(t_map *map) {
    if (!map || map->height <= 0 || map->width <= 0) return 0;
    if (map->empty == map->obst || map->empty == map->full || map->obst == map->full) return 0;
    
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            char c = map->map[i][j];
            if (c != map->empty && c != map->obst) return 0;
        }
    }
    return 1;
}

void solve_bsq(t_map *map){
    int **bq = malloc(sizeof(int*) * map->height);
    if (bq == NULL) return ;
    for (int y = 0; y < map->height; y++){
        bq[y] = malloc(sizeof(int) * map->width);
    }

    int max_size = 0, best_y = 0, best_x = 0;

    for (int y = 0; y < map->height; y++){
        for(int x = 0; x < map->width; x++){
            if(map->map[y][x] == map->obst){
                bq[y][x] = 0;
            } else if (y == 0 || x == 0){
                bq[y][x] = 1;
            } else {
                bq[y][x] = min3(bq[y -1][x], bq[y][x -1], bq[y -1][x-1]) +1;
            }

            if(bq[y][x] > max_size){
                max_size = bq[y][x];
                best_y = y;
                best_x = x;
            }
        }
    }

    int start_y = best_y - max_size +1;
    int start_x = best_x - max_size +1;

    for (int y = start_y; y < start_y + max_size; y++){
        for(int x = start_x; x < start_x + max_size; x++){
            map->map[y][x] = map->full;
        }
    }

    for (int y = 0; y < map->height; y++){
        free(bq[y]);
    } 
    free(bq);
}

t_map *init_map(char *filename){
    t_map *map = malloc(sizeof(t_map));
    if (!map) return NULL;
    FILE *file = (filename) ? fopen(filename, "r") : stdin;
    if (!file){ free(map); return NULL; }
    if(fscanf(file, "%d %c %c %c\n", &map->height, &map->empty, &map->obst, &map->full) != 4){
        free(map);
        if(filename) fclose(file);
        return NULL;
    }

    map->map = malloc(sizeof(char*) * map->height);
    if (!map->map){ free(map); if(filename) fclose(file); return NULL;}
    
    map->width = 0;

    for(int y = 0; y < map->height; y++){
        char* line = NULL;
        size_t len = 0;
        if (getline(&line, &len, file) < 0){
            free_map(map);
            free(line);
            if(filename) fclose(file);
            return NULL;
        }

        int str_len = ft_strlen(line);
        if (str_len > 0 && line[str_len - 1] == '\n') line[str_len -1] = '\0';
        if(y == 0) map->width = ft_strlen(line);
        else {
            if(ft_strlen(line) != map->width){
                free(line);
                free_map(map);
                if(filename) fclose(file);
                return NULL;
            }
        }
        map->map[y] = line;
    }

    if(filename) fclose(file);
    return map;
}

void process(char *filename){
    t_map *map = init_map(filename);
    if(!map || !validate_map(map)){
        if (map) free_map(map);
        fprintf(stderr, "map error\n");
        return ;
    }
    print_map(map);
    solve_bsq(map);
    print_map(map);
    free_map(map);
}


int main(int ac, char **av){
    if(ac == 1)
        process(NULL);
    else {
        for (int i = 1; i < ac; i++){
            process(av[i]);
        }
    }
    return 0;
}