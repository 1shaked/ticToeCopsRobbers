//
//  main.c
//  ticTacToe
//
//  Created by shaked chen on 05/12/2021.
//

#include <stdio.h>
#define MAX_SIZE 30
#define MIN_SIZE 5

void Games(void);
void SetNames(void);
void ComputerMoveTicTacToe(void);
void TicTacToe(void);
void CopsAndRobbers(void);
void RobberMove(void);
void PrintBoard(void);
int SetRows(void);
int SetColumns(int row);
char firstName[10];
char lastName[10];
// TODO: chake if change change the board dynamicly and pass it
int board [MAX_SIZE][MIN_SIZE];
int row;
int col;
int main(int argc, const char * argv[]) {
    Games();
    return 0;
}

void Games(void) {
    
    SetNames();
    printf("Hello %s %s, what would you like to play? (1) Cops and Robbers (2) Tic tac toe (3) Exit", firstName, lastName);
    int userInput = -1;
    while(!(userInput > 0 && userInput < 4)) {
        scanf("%d", &userInput);
    }
    if (userInput == 3) printf("Bye, %s %s", firstName, lastName);
    else if (userInput == 1) CopsAndRobbers();
    else if (userInput == 2) TicTacToe();
}
void SetNames(void) {
    printf("Enter first name\n");
    scanf("%s", firstName);
    
    printf("Enter last name\n");
    scanf("%s", lastName);
}
void CopsAndRobbers(void) {
    /*
        cops: [[x1, y1], [x2, y2], [x3, y3]]
        robber: [x, y]
     [----------------c------]
     [------c----------------]
     [----------c------------]
     [---------------r-------]
     [------------c----------]
     [-------------c---------]
        
     */
    printf("Let's choose the size:\n");
    row = SetRows();
    col = SetColumns(row);
    printf("row = %d col =  %d \n", row, col);
    printf("How many cops would you like (1-5)?\n");
    int cops = 0;
    scanf("%d", &cops);
    
    //int coptsLocations [cops][2];
    //int roobberLocation [2] = {3, 4};
    int board [row][col];
    // init bored
    int rowIndex = 0;
    for (; rowIndex <= row; rowIndex++) {
        int colIndex = 0;
        for (; colIndex <= col; colIndex++) board[rowIndex][colIndex] = 0;
    }
    // set robber location
    board[3][4] = -1;
    int copIndex = 0;
    for (; copIndex <= cops; copIndex++) {
        // get the user choice and validate it
        printf("Let's choose cell:\n");
        int rowChoise, colChoise;
        scanf("%d %d", &rowChoise, &colChoise);
    }
}
void ComputerMoveTicTacToe(void) {
    
}
void TicTacToe(void) {
    
}
void PrintBoard (void) {}
int SetRows(void) {
    int row;
    scanf("%d" , &row);
    if (row > MAX_SIZE) return MAX_SIZE;
    else if (row < MIN_SIZE) return MIN_SIZE;
    return row;
}
int SetColumns(int row) {
    int col;
    scanf("%d" , &col);
    if (col == -1) return row;
    else if( col > MAX_SIZE) return MAX_SIZE;
    else if ( col < MIN_SIZE) return MIN_SIZE;
    return col;
}

