board = [[1,2,3],[4,5,6],[7,8,9]]
a = 0
p = "X"


def test():
    win = True
    for i in range(len(board)):
        ##provjera redaka
        if board[i][0] == board[i][1] and board[i][1] == board[i][2]:
            win = False
        ##provjera stupaca
        if board[0][i] == board[1][i] and board[1][i] == board[2][i]:
            win = False
    
    if board[0][0] == board[1][1] and board[1][1] == board[2][2]:
        win = False
    
    if board[2][0] == board[1][1] and board[1][1] == board[0][2]:
        win = False

    return win

def move(player, place, temp):
    moved = temp
    if place<4:
        moved[0][place-1] = player
    elif place<7:
        moved[1][place-4] = player
    elif place<10:
        moved[2][place-7] = player

    return moved

def free_moves(mm_board):
    moves = []
    for i in range(len(mm_board)):
        for j in range(len(mm_board)):
            if mm_board[i][j] != "X" or mm_board[i][j] != "O":
                moves.append(mm_board[i][j])
    return moves

def minimax(t_board, min, depth):   #false is pc move
    if min:



def pc_turn():
    available = free_moves(board)
    mm_board = board

    for i in range(len(available)):
        mm_board = move("O", available[i], mm_board)
        minimax(mm_board, False, 0)
        






while test():

    for i in board:
        print(i)
    
    while True:
        m = free_moves(board)
        print("Igrac ", p)
        l=input("Pl: ")
        if l.isnumeric():
            l = int(l)
            if l>0 and l<=9 and l in m:
                board = move(p, l, board)
                break
    
    if p == "X":
        p = "O"
    else:
        pc_turn()
        p = "X"
