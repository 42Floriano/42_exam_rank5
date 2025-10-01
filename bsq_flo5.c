#include <unistd.h>
#include <errno.h>
#include <stdio.h>
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
    while(*str == ' ') str++;

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
        if(map->map[y] != NULL)
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

void solve_bsq(t_map *map){
    int **dp = malloc(sizeof(int*) * map->height);
    if(dp == NULL) return;
    for (int y = 0; y < map->height; y++){
        dp[y] = malloc(sizeof(int) * map->width);
        if(dp[y] == NULL) return ;
    }

    int max_size = 0, best_y = 0, best_x = 0;


    for (int y = 0; y < map->height; y++){
        for(int x = 0; x  < map->width; x++){
            if (map->map[y][x] == map->obst){\
                dp[y][x] = 0;
            } else if (y == 0 || x == 0){
                dp[y][x] = 1;
            } else {
                dp[y][x] = min3(dp[y -1][x], dp[y][x-1], dp[y-1][x-1]) + 1;
            }


            if(max_size < dp[y][x]){
                max_size = dp[y][x];
                best_x = x;
                best_y = y;
            }
        }
    }

    int start_y =  best_y - max_size + 1;
    int star_x = best_x - max_size + 1;

    for(int y = start_y; y < start_y + max_size; y++){
        for(int x = star_x; x < star_x + max_size; x++){
            map->map[y][x] = map->full;
        }
    }


    for(int y = 0; y < map->height; y++){
        free(dp[y]);
    }
    free(dp);
    return ;
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

t_map *init_map(char *filename){
    t_map *map = malloc(sizeof(t_map));
    if (!map) return NULL;

    FILE  *file = (filename) ? fopen(filename, "r") : stdin;
    if(!file){free(map); return NULL;}

    char *line = NULL;
    size_t len_l = 0;

    if(getline(&line, &len_l, file) < 0){
        free(map);
        if(filename) fclose(file);
        return NULL;
    }

    int str_len = ft_strlen(line);
    if(str_len > 0 && line[str_len - 1] == '\n') line[--str_len] = '\0';
    
    // char empty, obst, full;
    // int height;
    // int nscan = fscanf(file, "%d %c %c %c", &height, &empty, &obst, &full);

    // if(nscan == 4){
    //     map->height = height;
    //     map->empty = empty;
    //     map->obst = obst;
    //     map->full = full;

    //     printf("Test2: %d %c %c %c\n", map->height, map->empty, map->obst, map->full);
    // } else { 
        int len = ft_strlen(line);
        if(len < 4){
            free(line);
            free(map);
            if(filename) fclose(file);
            return NULL;
        }

        map->empty = line[len -3];
        map->obst = line[len -2];
        map->full = line[len -1];

        line[len -3] = '\0';

        char *p = line;

        for(int i; p[i]; i++){
            if(p[i] < '0' || p[i] > '9'){
                free(line);
                free(map);
                if(filename) fclose(file);
                return NULL;
            }
        }

        map->height = atoi(p);
    free(line);

    map->width = 0;
    map->map = malloc(sizeof(char*) * map->height);
    if(map->map == NULL){
        free(map);
        if(filename) fclose(file);
        return NULL;
    }
    for (int i = 0; i < map->height; i++) map->map[i] = NULL;

    for (int y = 0; y < map->height; y++){
        char *row = NULL;
        size_t len_r = 0;
        if(getline(&row, &len_r, file) < 0){
            free(row);
            free_map(map);
            if(filename) fclose(file);
            return NULL;
        }

        int sl = ft_strlen(row);
        if (sl > 0 && row[sl -1] == '\n') row[sl - 1] = '\0';

        if(y == 0) map->width = ft_strlen(row);
        else {
            if(map->width != ft_strlen(row)){
                free(row);
                free_map(map);
                if(filename) fclose(file);
                return NULL;
            }
        }
        map->map[y] = row;
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
        for(int i = 1; i < ac; i++)
            process(av[i]);
    }
    return 0;
}