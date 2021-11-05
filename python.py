board = [[1,2,3],[4,5,6],[7,8,9]]
a = 0
p = "X"


def test(t_board):
    win = True
    for i in range(len(t_board)):
        ##provjera redaka
        if t_board[i][0] == t_board[i][1] and t_board[i][1] == t_board[i][2]:
            win = t_board[i][0]
        ##provjera stupaca
        if t_board[0][i] == t_board[1][i] and t_board[1][i] == t_board[2][i]:
            win = t_board[0][i]
    
    if t_board[0][0] == t_board[1][1] and t_board[1][1] == t_board[2][2]:
        win = t_board[0][0]
    
    if t_board[2][0] == t_board[1][1] and t_board[1][1] == t_board[0][2]:
        win = t_board[2][0]

    return win

def move(player, place, moved):
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
            if mm_board[i][j] != "X" and mm_board[i][j] != "O":
                moves.append(int(mm_board[i][j]))
    return moves

def minimax(t_board, min, depth):   #false is pc move
    moves = free_moves(t_board)
    if test(t_board)!=True:
        if test(t_board) == "X":
            return 10 
        elif test(t_board) == "O":
            return -10  
    best_score = 0
    

    if min:
        best_score = -11
        for i in range(len(moves)):
            temp = move("X", moves[i], t_board)
            d = depth+1
            s = minimax(temp, False, d)
            if s > best_score:
                best_score = s
        return best_score

    else:
        best_score = 11
        for i in range(len(moves)):
            temp = move("O", moves[i], t_board)
            d = depth+1
            s = minimax(temp, True, d)
            if s < best_score:
                best_score = s
        return best_score 


def pc_turn():
    available = free_moves(board)
    mm_board = board
    best = -11
    b_move = 0

    for i in range(len(available)):
        mm_board = move("O", available[i], mm_board)
        score = minimax(mm_board, False, 0)

        if score > best:
            print(score)
            best = score
            b_move = int(available[i])
    
    return b_move




while True:
    if test(board)!=True:
        print(board)
        print("POBJEDIO JE: ", test(board))
        break

    for i in board:
        print(i)
    
    while True:
        m = free_moves(board)
        print("Igrac ", p)
        
        if p == "X":
            l=int(input("Pl: "))
        else:
            l= int(pc_turn())
            print(l)

        if l>0 and l<=9 and l in m:
            print(p, "move")
            board = move(p, l, board)
            break
    
    if p == "X":
        p = "O"
    else:
        p = "X"
