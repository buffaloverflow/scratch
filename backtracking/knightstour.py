"""
Knights tour using backtracking
"""

def printBoard(board):
    for i in board:
        for j in i:
            print(j, end=' ')
        print("")

class Tour():
    __moves = (
        (1, -2),
        (1, 2),
        (-1, -2),
        (-1, 2),
        (2, -1),
        (2, 1),
        (-2, -1),
        (-2, 1),
    )

    def __init__(self, n):
        self._n = n
        self.board = [['__' for i in range(n)] for j in range(n)]

    def validMove(self, x, y):
        return (0 <= x < self._n) and \
               (0 <= y < self._n) and \
               self.board[x][y] == '__'

    def __repr__(self):
        s = ""
        for i in self.board:
            for j in i:
                s += ("%02d " % j) if not isinstance(j, type("")) else (j+" ")
            s += "\n\n"
        return s

    def __str__(self):
        return repr(self)

    def __solve(self, pos, x_, y_):
        if pos == self._n**2:
            return True
    
        for (i, j) in Tour.__moves:
            x = x_+i
            y = y_+j

            if self.validMove(x, y):
                self.board[x][y] = pos
                //print(self)
                if (self.__solve(pos+1, x, y)):
                    return True
                self.board[x][y] = "" 
        return False

    def solve(self, x, y):
        self.board[x][y] = 0
        return self.__solve(1, x, y)

t = Tour(8)
print(t.solve(0,0))
print(t)
