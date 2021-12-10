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
void PrintBoard(int row, int col);
int SetRows(void);
int SetColumns(int row);
int IsValidLocation(int row,int col , int userChoiseRow, int userChoiseCol);
int IsLocationAvailable(int v, int includeRobber);
int IsLocationUnAvailable(int v, int includeRobber);
void PrintLocationForrmated(int v);
char firstName[10];
char lastName[10];
int board [MAX_SIZE][MAX_SIZE];
int main(int argc, const char * argv[]) {
    Games();
    return 0;
}

void Games(void) {
    
    SetNames();
    printf("Hello %s %s, what would you like to play? (1) Cops and Robbers (2) Tic tac toe (3) Exit\n", firstName, lastName);
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
    int row = SetRows();
    int col = SetColumns(row);
    printf("row = %d col =  %d \n", row, col);
    printf("How many cops would you like (1-5)?\n");
    int cops = 0;
    scanf("%d", &cops);
    const int copsSize = cops; // this is the amount of cops we have and will contril all loop over the cops
    int coptsLocations [5][2];
    //printf("aaaa %d ", coptsLocations[1]);
    
    int roobberLocation [2] = {3, 4};
    printf("roobberLocation = %d \n", roobberLocation[0]);
    // TODO: check if needed
    // init bored
    int rowIndex = 0;
    for (; rowIndex <= row; rowIndex++) {
        int colIndex = 0;
        for (; colIndex <= col; colIndex++) board[rowIndex][colIndex] = 0;
    }
    // set robber location
    board[3][4] = -1;
    int copIndex = 0;
    while(copIndex < copsSize) {
        // get the user choice and validate it
        printf("Let's choose cell:\n");
        int rowChoise, colChoise;
        scanf("%d %d", &rowChoise, &colChoise);
        int isValid = IsValidLocation(row, col,rowChoise, colChoise);
        if (isValid) {
            board[rowChoise][colChoise] = 1;
            printf("%d \n", board[rowChoise][colChoise]);
            coptsLocations[copIndex][0] = rowChoise;
            coptsLocations[copIndex][1] = colChoise;
            copIndex++;
        } else printf("Illegal choice!\n");
    }
    // starting the game affter init
    printf("Let’s play!\n");
    printf("Initial states:\n");
    PrintBoard(row, col);
}
void ComputerMoveTicTacToe(void) {
    
}
void TicTacToe(void) {
    
}
/*************************************************************************
Function name: PrintBoard
Input: int row, int col
Output: int
The function operation: print the bord in the givin input range the range is the bored play range game
************************************************************************/
void PrintBoard (int row, int col) {
    int rowIndex = 0;
    for (; rowIndex < row; rowIndex++) {
        int colIndex = 0;
        for(; colIndex < col; colIndex++) PrintLocationForrmated(board[rowIndex][colIndex]);
        printf("\n");
    }
}
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

int IsValidLocation(int row,int col , int userChoiseRow, int userChoiseCol) {
    if (IsLocationUnAvailable(board[userChoiseRow][userChoiseCol], 1)) return 0;
    // col section
    int startCol = userChoiseCol - 2;
    int previos;
    int next;
    if (startCol >= 0) {
        // we can check next two
        previos = IsLocationUnAvailable(board[userChoiseRow][startCol],0);
        next = IsLocationUnAvailable(board[userChoiseRow][startCol+1],0);
        if (previos && next) return 0;
    }
    startCol = startCol + 1;
    if (startCol >= 0 && startCol + 3 < col ) {
        previos = IsLocationUnAvailable(board[userChoiseRow][startCol],0);
        next = IsLocationUnAvailable(board[userChoiseRow][startCol+2],0);
        if (previos && next) return 0;
    }
    startCol = startCol + 2;
    if (startCol+ 2 < col) {
        previos = IsLocationUnAvailable(board[userChoiseRow][startCol],0);
        next = IsLocationUnAvailable(board[userChoiseRow][startCol+1],0);
        if (previos && next) return 0;
    }
    // checking the rwo if valid
    int startRow = userChoiseRow - 2;
    if (startRow >= 0) {
        previos = IsLocationUnAvailable(board[startRow][userChoiseCol],0);
        next = IsLocationUnAvailable(board[startRow + 1][userChoiseCol],0);
        if (previos && next) return 0;
    }
    startRow  = startRow + 1;
    if (startCol >= 0 && startRow+3 < col) {
        previos = IsLocationUnAvailable(board[userChoiseRow][userChoiseCol],0);
        next = IsLocationUnAvailable(board[startRow + 2][userChoiseCol],0);
        if (previos && next) return 0;
    }
    startRow = startRow + 2;
    if (startCol +2 < col) {
        previos = IsLocationUnAvailable(board[startRow][userChoiseCol],0);
        next = IsLocationUnAvailable(board[startRow+1][userChoiseCol],0);
        if (previos && next) return 0;
    }
    return 1;
}
/*************************************************************************
Function name: IsLocationAvailable
Input: int v, int includeRobber
Output: int
The function operation: check if a cop or a robber is in the location if you give include robber than we will check if a robber is also in the borad location
************************************************************************/
int IsLocationAvailable(int v, int includeRobber) {
    if (includeRobber) return !(v == 1 || v == -1);
    return v != 1;
}
int IsLocationUnAvailable(int v, int includeRobber) {
    return !IsLocationAvailable(v,includeRobber);
}
void PrintLocationForrmated(int v) {
    if (v == 1) printf("C");
    else if (v == -1) printf("R");
    else printf("-");
}
