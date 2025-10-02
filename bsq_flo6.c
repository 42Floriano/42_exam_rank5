#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

typedef struct s_map{
    int height, width;
    char empty, obst, full;
    char **map;
} t_map;

int min3(int a, int b, int c){
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c); 
}

int ft_strlen(char *str){
    int count = 0;
    while(str && str[count]){
        count++;
    }
    return count;
}

int ft_atoi(char *str){
    int res = 0;

    while(*str == ' ')
        str++;
    while(*str >= '0' && *str <= '9'){
        res = res * 10 + (*str - '0');
        str++; 
    }
    return res;
}

void free_map(t_map *map){
    if(map == NULL) return;
    if(map->map == NULL) return;
    for(int y = 0; y < map->height; y++){
        //if(map->map[y] != NULL)
        free(map->map[y]);
    }
    free(map->map);
    free(map);
}

void print_map(t_map *map){
    for(int y = 0; y < map->height; y++){
        fprintf(stdout, "%s\n", map->map[y]);
    }
}

int validate_map(t_map *map){
    if (!map) return 1;
    if (map->height <= 0 || map->width <= 0) return 1;
    if (map->empty == map->full || map->empty == map->obst || map->obst == map->full) return 1;

    printf("Test: %d %c %c %c\n", map->height, map->empty, map->obst, map->full);

    for(int y = 0; y < map->height; y++){
        for(int x = 0; x < map->width; x++){
            char c = map->map[y][x];
            if (c != map->empty && c != map->obst)
                return 1;
        }
    }
    //printf("Passing here\n");
    return 0;
}

void solve_bsq(t_map *map){
    int **qb = malloc(sizeof(int*) * map->height);
    if(qb == NULL) return ;
    for (int y = 0; y < map->height; y++){
        qb[y] = malloc(sizeof(int) * map->width);
        if(qb[y] == NULL) return ;
    }

    int max_size = 0, best_y = 0, best_x = 0;
     for (int y = 0; y < map->height; y++){
         for (int x = 0; x < map->width; x++){
            if(map->map[y][x] == map->obst){
                qb[y][x] = 0;
            } else if (y == 0 || x == 0){
                qb[y][x] = 1;
            } else {
                qb[y][x] = min3(qb[y -1][x], qb[y][x -1], qb[y-1][x-1]) + 1;
            }

            if(qb[y][x] > max_size){
                max_size = qb[y][x];
                best_x = x;
                best_y = y;
            }
         }
     }

    int start_y = best_y - max_size +1;
    int start_x = best_x - max_size +1;

    for (int y = start_y; y < start_y + max_size; y++){
         for (int x = start_x; x < start_x + max_size; x++){
            map->map[y][x] = map->full;
         }
    }
    for (int y = 0; y < map->height; y++){
        free(qb[y]);
    }
    free(qb);
}

t_map *init_map(char *filename){
    t_map *map = malloc(sizeof(t_map));
    if(!map) return NULL;

    FILE *file = (filename) ? fopen(filename, "r") : stdin;
    if(!file) {free(map); return NULL;}

    char *fline = NULL;
    size_t flen = 0;
    if(getline(&fline, &flen, file) < 0){
        free(fline);
        free(map);
        if(filename) fclose(file);
    }

    int fstrlen = ft_strlen(fline);
    if(fstrlen < 4){
        free(fline);
        free(map);
        if(filename) fclose(file);
        return NULL;
    }

    if (fstrlen > 0 && fline[fstrlen - 1] == '\n') fline[--fstrlen] = '\0';

    map->full = fline[fstrlen - 1];
    map->obst = fline[fstrlen - 2];
    map->empty = fline[fstrlen - 3];

    fline[fstrlen - 3] = '\0';

    char *p = fline;
    while(*p == ' ') p++;
    for(int i = 0; p[i]; i++){
        if(p[i] < '0' || p[i] > '9'){
            free(fline);
            free(map);
            if(filename) fclose(file);
            return NULL;
        }
    }
    map->height = ft_atoi(fline);
    free(fline);

    map->width = 0;
    map->map = malloc(sizeof(char*) * map->height);
    if(!map->map){
        free(map);
        if(filename) fclose(file);
        return NULL;
    }
    for(int y = 0; y < map->height; y++) map->map[y] = NULL;

    for(int y = 0; y < map->height; y++){
        char *line = NULL;
        size_t len = 0;
        if(getline(&line, &len, file) < 0){
            free(line);
            free_map(map);
            if(filename) fclose(file);
            return NULL;
        }

        int str_len = ft_strlen(line);
        if(str_len > 0 && line[str_len -1] == '\n') line[str_len -1] = '\0';

        if(y == 0) map->width = ft_strlen(line);
        else{
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
    if(!map || validate_map(map)){
        if (map) free_map(map);
        fprintf(stderr, "map error\n");
        return ;
    }
    solve_bsq(map);
    print_map(map);
    free_map(map);
}

int main(int ac, char **av){
    if(ac == 1)
        process(NULL);
    else{
        for (int i = 1; i < ac; i++)
            process(av[i]);
    }
    return 1;
}