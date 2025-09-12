#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_map {
    int width, height;
    char empty, obstacle, full;
    char **map;
} t_map;

int min3(int a, int b, int c){
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

t_map *read_map(char *filename){
    FILE *file;
    if(!filename){
        size_t cap;
        ssize_t r = getline(&filename, &cap, stdin);
        if (r <= 0) { free(filename); return NULL; }
        if (r > 0 && filename[r-1] == '\n') filename[r-1] = '\0';
    }
    if (!filename) return NULL;
    file = fopen(filename, "r");
    if(!file) return NULL;

    t_map *map = malloc(sizeof(t_map));
    if(fscanf(file, "%d %c %c %c\n", &map->height, &map->empty, &map->obstacle, &map->full) != 4){
        free(map);
        if(filename) fclose(file);
        return NULL;
    }

    map->map = malloc(sizeof(char*) * map->height);
    map->width = 0;
    
    for (int i = 0; i < map->height; i++){
        char *line = NULL;
        size_t len = 0;
        if(getline(&line, &len, file) == -1){
            if(filename) fclose(file);
            free(map->map);
            free(map);
            return NULL;
        }

        int len_line = strlen(line);

        if(line[len_line - 1] == '\n') line[len_line - 1] = '\0';

        if(i == 0) map->width = strlen(line);
        else{
            if ((int)strlen(line) !=  map->width){
                if(filename) fclose(file);
                free(map->map);
                free(map);
                return NULL;
            }
        }
        map->map[i] = line;
    }
    if(filename) fclose(file);
    return map;
}

void solve_bsq(t_map *map){
    int **dp = malloc(map->height * sizeof(int*));
    for (int i = 0; i < map->height; i++){
        dp[i] = malloc(sizeof(int) * map->width);
    }

    int max_size = 0, best_i = 0, best_y = 0;

    for (int i = 0; i < map->height; i++){
        for (int y = 0; y < map->width; y++){
            if(map->map[i][y] == map->obstacle){
                dp[i][y] = 0;
            } else if (i == 0 || y == 0){
                dp[i][y] = 1;
            } else {
                dp[i][y] = min3(dp[i - 1][y], dp[i][y - 1], dp[i -1][y -1]) + 1;
            }

            if (dp[i][y] > max_size){
                max_size = dp[i][y];
                best_i = i;
                best_y = y; 
            }
        }
    }

    int start_i = best_i - max_size + 1;
    int start_y = best_y - max_size + 1;
    for (int i = start_i; i < start_i + max_size; i++){
        for (int y = start_y; y < start_y + max_size; y++){
            map->map[i][y] = map->full;
        }
    }

    for (int i = 0; i < map->height; i++){
        free(dp[i]);
    }
    free(dp);

}

int is_valid(t_map *map){
    if(map->height <= 0 || map->width <= 0) return 0;
    if (map->empty == map->obstacle || map->empty == map->full || map->full == map->obstacle) return 0;
    for (int i = 0; i < map->height; i++){
        for (int y = 0; y < map->width; y++){
            if (map->map[i][y] != map->obstacle && map->map[i][y] != map->empty && map->map[i][y] != map->full) return 0;
        }
    }
    return 1;
}

void free_map(t_map *map){
    if (!map) return;
    for (int i = 0; i < map->height; i++)
        free(map->map[i]);
    free(map->map);
    free(map);
}

void print_map(t_map *map){
    for (int i = 0; i < map->height; i++)
        fprintf(stdout, "%s\n", map->map[i]);
}

void process_file(char *filename){
    t_map *map = read_map(filename);
    if(!map || !is_valid(map)){
        fprintf(stderr, "map_error\n");
        if (map) free_map(map);
        return ;
    }
    print_map(map);
    fprintf(stdout, "\n");
    solve_bsq(map);
    print_map(map);
    fprintf(stdout, "\n");
    free_map(map);
    
}

int main(int ac,  char **av){
    if (ac == 1){
        process_file(NULL);
    } else if (ac > 1){
        for(int i = 1; i < ac; i++)
            process_file(av[i]);
    }
    return 0;
}

int min3(int a, int b, int c){
    return (a < c) ? ((a < b) ? a )
}

typedef struct s_map{
    int empty, obst, full;
    int height, widht;
    char **map;
} t_map;

void process_file(char **av){
    t_map *map = read_map(av);
    if (!map || validate(map)){
        fprintf(stderr,"map error\n");
        if (map) free(map);
        return ;
    }
    solve_bsq(map);
    print_map(map);
    free_map(map);
    return ;
}

int main(int ac, char**av{
    if (ac == 1)
        process_file(NULL);
    else{
        for(int i = 1; i < ac; i++)
            process_file(av[i]);
    }
    return (0);
}