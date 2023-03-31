#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef unsigned char cell;

typedef struct game_t {
    size_t n;
    cell** board;
} game;

const char moves[9][2] = {
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},
    {2, 1},
    {2, -1},
    {-2, 1},
    {-2, -1},
    {0, 0}
};

void print(game *g, size_t pos) {
    for (int i=0; i<g->n; i++) {
        for (size_t z=0; z<pos; z++) printf("  ");
        for (int j=0; j<g->n; j++) {
            if (g->board[i][j] != 0xff)
                printf("%02d ", g->board[i][j]);
            else
                printf("__ ");
        }
        printf("\n");
    }
    printf("\n");
}

bool _solve(game *g, size_t pos, size_t x_, size_t y_) {
    if (pos == (g->n) * (g->n)) return true;

    print(g, pos);
    
    for (size_t i=0; i<8; i++) {
        size_t x = x_ + moves[i][0]; 
        size_t y = y_ + moves[i][1]; 
        if ((x>=0) && (x<g->n) && (y>=0) && (y<g->n) && g->board[x][y] == 0xff) {
            g->board[x][y] = pos;
            if (_solve(g, pos+1, x, y))
                return true;
            g->board[x][y] = -1;
        }
    } 

    return false;
}

bool solve(game *g, size_t i, size_t j) {
    g->board[i][j] = 0;
    return _solve(g, 1, i, j);
}

int main(int argc, char **argv) {
    size_t _n = 5;
    cell **board = (cell **) malloc(sizeof(cell *) * _n);
    for (int i=0; i<_n; i++) {
        board[i] = (cell *) malloc(sizeof(cell) * _n);
        memset(board[i], 0xff, sizeof(cell) * _n);
    }

    game g = {0};
    g.n = _n;
    g.board = board;


    bool res = solve(&g, 0, 0);
    if (res)
        print(&g, 0);

    free(board);
}
