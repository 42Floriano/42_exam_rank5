#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
    FILE *file = filename ? fopen(filename, "r") : stdin;
    if (!file) return NULL;

    t_map *map = malloc(sizeof(t_map));
    if (fscanf(file, "%d %c %c %c", &map->height, &map->empty, &map->obst, &map->full) != 4){
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

        int line_len = strlen(line);

        if(line[line_len - 1] == '\n') line[line_len - 1] == '\0';

        if (i == 0)
            map->width = line_len;
        else if((int)strlen(line) != map->width){
            free(map);
            if(filename) fclose(file);
            return NULL;
        }
    }

    if (filename) fclose(file);
    return map;
}

void solve_bsq(t_map *map){
    

}

void print_map(t_map *map){
    for (int i = 0; i < map->height; i++)
        fprint(stdout, map->map[i]);
}

void free_map(t_map *map){
    if (!map) return ;
    for (int i = 0; i < map->height; i++){
        free(map->map[i]);
    }
    free(map->map);
    free(map);
}

void process(char **filename){
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


int main(int ac, char *av){
    if (ac == 1)
        process(NULL);
    else {
        for (int i = 1; i < ac; i++)
            process(av[i]);
    }
    return 1;
}