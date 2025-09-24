#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

void process(char *filename){
    t_map *map = parse_map(filename);
    if (!map || !validate(map)){
        free_map(map);
        fprintf(2, "map error\n", 0)
    }
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