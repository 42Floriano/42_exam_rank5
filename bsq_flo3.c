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

void process(char *filename){
    t_map *map = parse_map(filename);
    if (!map || !validate(map)){
        if (map) free_map(map);
        fprintf(stderr, "map error\n");
        return ;
    }
    //solve_bsq(map);
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