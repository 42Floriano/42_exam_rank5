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

int min3(int a, int b, int c){
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

void print_map(t_map *map){
    for(int i = 0; i < map->height; i++){
        fprintf(stdout, "%s\n", map->map[i]);
    }
}

void free_map(t_map *map){
    if (!map) return;
    if (map->map){
        for (int y = 0; y < map->height; y++){
            free(map->map[y]); /* free(NULL) is safe */
        }
        free(map->map);
    }
    free(map);
}


int validate(t_map *map){
    if(!map) return 0;
    if(map->height <= 0 || map->width <= 0) return 0;
    if(map->empty == map->full || map->empty == map->obst || map->obst == map->full) return 0;

    for(int y = 0; y < map->height; y++){
        for(int x = 0; x < map->width; x++){
            char c = map->map[y][x];
            if (c != map->empty && c != map->obst)
                return 0;
        }
    }
    return 1;
}

t_map *parse_map(char *filename){
    FILE *file = (filename) ? fopen(filename, "r") : stdin;
    if (!file)  return NULL;
    t_map *map = malloc(sizeof(t_map));
    if(map == NULL) return NULL; 
    if (fscanf(file, "%d %c %c %c\n", &map->height, &map->empty, &map->obst, &map->full) != 4){
        if (filename) fclose(file);
        free(map);
        return NULL;
    }

    map->map = malloc(sizeof(char*) * map->height);
    if (map->map == NULL){ if(filename) fclose(file); free(map); return NULL;}
    //for (int i = 0; i < map->height; i++) map->map[i] = NULL;
    map->width = 0;

    for(int y = 0; y < map->height; y++){
        char *line = NULL;
        size_t len = 0;
        if(getline(&line, &len, file) == -1){
            free(line);
            if(filename) fclose(file);
            free_map(map);
            return NULL;
        }

        int str_len = ft_strlen(line);
        if(line && str_len > 0 && line[str_len - 1] == '\n') line[str_len -1] = '\0';
        if(y == 0) map->width = ft_strlen(line);
        else {
            if(ft_strlen(line) != map->width){
                free(line);
                if (filename) fclose(file);
                free_map(map);
                return NULL;
            }
        }
        //map->map[y] = malloc(sizeof(char) * map->width);
        map->map[y] = line;
    }
    if (filename) fclose(file);
    return map;
}

void solve_bsq(t_map *map){
    //alloce mem
    int **dp = malloc(sizeof(int*) * map->height);
    if (dp == NULL) return ;
    for (int y = 0; y < map->height; y++){
        dp[y] = malloc(sizeof(int) * map->width);
        if (dp[y] == NULL) return ;
    }

    int max_size = 0, best_y = 0, best_x = 0;

    for (int y = 0; y < map->height; y++){
        for (int x = 0; x < map->width; x++){
            if(map->map[y][x] == map->obst){
                dp[y][x] = 0;
            } else if (y == 0 || x == 0){
                dp[y][x] = 1;
            } else {
                dp[y][x] = min3(dp[y -1][x], dp[y][x -1], dp[y -1][x -1]) + 1;
            }

            if(dp[y][x] > max_size){
                max_size = dp[y][x];
                best_y = y;
                best_x = x;
            }
        }
    }

    int start_y = best_y - max_size + 1;
    int start_x = best_x - max_size + 1;

    for (int y = start_y; y < start_y + max_size; y++){
        for(int x = start_x; x < start_x + max_size; x++){
            map->map[y][x] = map->full; 
        }
    }

    //free meme
    for (int y = 0; y < map->height; y++){
        free(dp[y]);
    }
    free(dp);
}

void process(char *filename){
    t_map *map = parse_map(filename);
    if (!map || !validate(map)){
        if (map) free_map(map);
        fprintf(stderr, "map error\n");
        return ;
    }
    solve_bsq(map);
    print_map(map);
    free_map(map);
}

int main (int ac, char **av){
    if(ac == 1)
        process(NULL);
    else{
        for (int i = 1; i < ac; i++){
            process(av[i]);
        }
    }
    return 0;
}