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

void print(t_map *map){
    for (int y = 0; y < map->height; y++){
        fprintf(stdout, "%s\n", map[y]);
    }
}

void free_map(t_map *map){
    if(!map) return ;
    if(map->map){
        for(int y = 0; y < map->height; y++){
            
        }
    }
}

int min3(int a, int b, int c){
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

void process(char *filename){
    t_map *map = init_map(filename);
    if(!map || !validate(map)){
        if (map) free_map(map);
        fprintf(stderr, "map error\n");
        return ;
    }
    // print_map(map);
    // solve_bsq(map);
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