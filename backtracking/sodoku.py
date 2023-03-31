class Sudoku:
    def __init__(self, board=None):
        self.board = board or [['.' for i in range(9)] for j in range(9)]
        # BUG: any board passed in that's bigger or smaller than 9x9 leads to UB

    def __str__(self): 
        s = ''
        for i,r in enumerate(self.board):
            if (i%3 == 0): s += '+---+---+---+\n'
            for j,c in enumerate(r):
                if (j%3 == 0): s+='|'
                s += str(c) 
            s += '|\n'
        s += '+---+---+---+\n'
        return s 

    def check(self, row, col, val):
        if val in self.board[row]: return False #row
        for r in range(9):
            if self.board[r][col] == val: return False #col
        r,c = row//3*3, col//3*3
        for i in range(r, r+3):
            for j in range(c, c+3):
                if self.board[i][j] == val: return False
        return True
    
    def next_cell(self):
        for i in range(9):
            for j in range(9):
                if (self.board[i][j] == '.'):
                    return (i,j)
        raise Exception

    def solve(self):
        try: r, c = self.next_cell()
        except: return true
        for i in range(1, 10):
            if (self.check(r, c, i)):
                self.board[r][c] = i
                if (self.solve()): return True
                self.board[r][c] = '.'
        return False

    @classmethod
    def from_string(cls, s):
        board = []
        for line in s.split():
            board.append(list(int(c) if c != '.' else '.' for c in line.strip()))
        return cls(board)


class Ninja:
    def __init__(self, tl, tr, m, bl, br):
        pass

if 0:
    s = Sudoku.from_string("""
    .8752396.
    .9.....8.
    ....8....
    ..32.48..
    .749.163.
    ..98.74..
    ....1....
    .4.....5.
    .2869534.
    """)
    s.solve()
    print(s)

    s = Sudoku.from_string("""
    8...647..
    .5.91....
    .16......
    9....3.57
    6........
    ....9.63.
    ..4.7.2.8
    .........
    58..291..
    """)
    s.solve()
    print(s)
