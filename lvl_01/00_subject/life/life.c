#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

typedef struct {
	int x;
	int y;
	int is_draw;
}   Pen;

char **create_board(int width, int height){
	char **board = malloc(sizeof(char *) * height);
	for (int i = 0; i < height; i++){
		board[i] = calloc(sizeof(char), width);
		for (int j = 0; j < width; j++){
			board[i][j] = ' ';
		}
	}
	return (board);
}

int	count_neighboors(char **board, int y, int x, int width, int height){
	int count = 0;
	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			if (j == 0 && i == 0)
				continue ;
			int new_x = x + i;
			int new_y = y + j;
			if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height){
				if (board[new_y][new_x] == 'O')
					count++;
			}
		}
	}
	return (count);
}

void	free_board(char **board, int height){
	for (int i = 0; i < height; i++){
		free (board[i]);
	}
	free (board);
}

void    iter_game(char **board, int width, int height){
	char **new_board = create_board(width, height);
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			int count = count_neighboors(board, y, x, width, height);
			//printf("COUNT = %i\n", count);
			if (board[y][x] == 'O'){
				if (count == 2 || count == 3)
					new_board[y][x] = 'O';
			}
			else{
				if (count == 3)
					new_board[y][x] = 'O';
			}
		}
	}
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			board[i][j] = new_board[i][j];
		}
	}
	free_board(new_board, height);
}

void	print_board(char **board, int width, int height){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			putchar(board[i][j]);
		}
		putchar('\n');
	}
	return ;
}



int main(int ac, char **av){
	if (ac != 4)
		return (1);

	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iter = atoi(av[3]);
	char **board = create_board(width, height);
	Pen pen = {0, 0, 0};
	char command;

	while (read(0, &command, 1) > 0){
		switch (command){
			case 'w':
				if (pen.y > 0)
					pen.y--;
				if (pen.is_draw){
					board[pen.y][pen.x] = 'O';
				}
				break;
			case 's':
				if (pen.y < height -1)
					pen.y++;
				if (pen.is_draw){
					board[pen.y][pen.x] = 'O';
				}
				break;
			case 'a':
				if (pen.x > 0)
					pen.x--;
				if (pen.is_draw){
					board[pen.y][pen.x] = 'O';
				}
				break;
			case 'd':
				if (pen.x < width - 1)
					pen.x++;
				if (pen.is_draw){
					board[pen.y][pen.x] = 'O';
				}
				break;
			case 'x':
				pen.is_draw = !pen.is_draw;
				if (pen.is_draw){
					board[pen.y][pen.x] = 'O';
				}
				break;
		}
	}
	print_board(board, width, height);
	for (int i = 0; i < iter; i++)
		iter_game(board, width, height);
	print_board(board, width, height);
	free_board(board, height);

	return (0);	
}