#include "bsq.h"

int main(int ac, char **av){
    if (ac == 1){
        if(!check_map(av[1]) || !resolve(av[1]))
            return (1);
    }
    if (ac == 0){
        
    }
    int i = 1;
    if (ac > i){
        while(i <= ac){
            if(!check_map(av[i]) || !resolve(av[i]))
            return (1);
            i++;
        }
    }
    return (0);
}