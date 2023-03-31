"""
 n-Queens Problem
 
 Put n-queens on an nxn board without them
 attacking each other.
"""
import random


class Queens:
    def __init__(self, n):
        self.n = n
        self.board = [['.' for i in range(n)] for i in range(n)]
        self.queens = set()

    def check(self, r, c):
        for col in range(self.n):
            if self.board[r][col] == 'Q':
                return False
        for i, j in zip(range(r, -1, -1), range(c, -1, -1)):
            if self.board[i][j] == 'Q':
                return False
        for i, j in zip(range(r, self.n, 1), range(c, -1, -1)):
            if self.board[i][j] == 'Q':
                return False
        return True 
            
    def __repr__(self):
        s = ''
        for r in self.board:
            for c in r:
                s += c
            s += '\n'
        return s 

    def __str__(self):
        return repr(self)

    def solve(self, col=0):
        if col >= self.n:
            return True

        for row in range(self.n):
            if (self.check(row, col)):
                self.board[row][col] = 'Q'
                if (self.solve(col+1)):
                    return True
                self.board[row][col] = '.'
        return False

q = Queens(18)
q.solve()
print(q)
