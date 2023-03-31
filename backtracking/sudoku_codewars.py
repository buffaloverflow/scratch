def check(board, row, col, val):
    if val in board[row]: return False #row
    for r in range(9):
        if board[r][col] == val: return False #col
    r,c = row//3*3, col//3*3
    for i in range(r, r+3):
        for j in range(c, c+3):
            if board[i][j] == val: return False
    return True
    
def next_cell(board):
    for i in range(9):
        for j in range(9):
            if (board[i][j] == 0):
                return (i,j)
    raise Exception

def sudoku(board):
    try: r, c = next_cell(board)
    except: return board
    for i in range(1, 10):
        if (check(board, r, c, i)):
            board[r][c] = i
            if (sudoku(board)): return board
            board[r][c] = 0
    return False
