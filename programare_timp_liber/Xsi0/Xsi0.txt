#include <stdio.h>
#include <stdlib.h>

void game_board(char board[3][3])
{
    printf("-------------\n");
    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        printf("-------------\n");
    }
}

void winner(char board[3][3], int player){
    //horizontal
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            printf("Player %d WON the GAME!!!\n", player);
            game_board(board);
            exit(0);
        }
    }

    //vertical
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != '-' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            printf("Player %d WON the GAME!!!\n", player);
            game_board(board);
            exit(0);
        }
    }

    //diagonale
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        printf("Player %d WON the GAME!!!\n", player);
        game_board(board);
            exit(0);
    }
    if (board[2][0] != '-' && board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
        printf("Player %d WON the GAME!!!\n", player);
        game_board(board);
        exit(0);
    }
}
int main()
{
    int sw = 0, player, game_over = 0, pick;
    char symbol;
    char board[3][3] =
    {
        {'-','-','-'},
        {'-','-','-'},
        {'-','-','-'}
    };

    printf("Welcome to X and 0! \n\n");

    while(game_over < 9)
    {
        game_over += 1;
        game_board(board);
        printf("blabla");
        if(sw == 0)
        {
            player = 1;
            symbol = 'X';
            sw = 1;
        }
        else if (sw == 1)
        {
            player = 2;
            symbol = 'O';
            sw = 0;
        }
        printf("Player %d: choose your move! ", player);
        scanf("%d", &pick);

        /// choose the moves for players
        while( (pick<1 || pick>9) || (board[(pick-1)/3][(pick-1)%3] != '-'))
        {
            printf("Invalid move! Please choose a valid move: ");
            scanf("%d", &pick);
        }
        if(pick == 1)
            board[0][0] = symbol;
        else if(pick == 2)
            board[0][1] = symbol;
        else if(pick == 3)
            board[0][2] = symbol;
        else if(pick == 4)
            board[1][0] = symbol;
        else if(pick == 5)
            board[1][1] = symbol;
        else if(pick == 6)
            board[1][2] = symbol;
        else if(pick == 7)
            board[2][0] = symbol;
        else if(pick == 8)
            board[2][1] = symbol;
        else if(pick == 9)
            board[2][2] = symbol;
        winner(board, player);
    }
    game_board(board);
    return 0;
}
