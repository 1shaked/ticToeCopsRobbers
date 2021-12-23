/******************************************
* Shaked Chen
* 207253220
* 83-120-01
* Ex 2
******************************************/

#include <stdio.h>
#include <math.h>
// #include <cmath>

#define MAX_SIZE 30
#define MIN_SIZE 5
#define TIC_TAC_TOE_DIMENSIONS 3
#define TIC_TAC_EMPTY_CHAR '-'
#define TIC_TAC_USER_CHAR 'X'
#define TIC_TAC_COMPUTER_CHAR 'O'
void Games(void);
void SetNames(void);
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
void MoveCop(int rowChoise, int colChoise, char action, int rowSize, int colSize,int cops, int copsLocation [5][2]);
float CalcDistance(int x1, int y1, int x2, int y2);
char ClacRobberDireaction(int copRow, int copCol, int robberRow, int robberCol, int maxRow, int maxCol);
void MoveRobber(int robberLocation[2], char action);
int IsThereWinningStrike(char board [3][3], char winType);
int IsInBoardTicTac(int row, int col);
int IsLocationAvailableTicTacToe (char v);
int IsLocationUnAvailableTicTacToe (char v);
void ComputerMoveTicTacToe (int startingLocation[2]);
void PirintTicTacBoard(char board[3][3]);
void OrderCopsArray(int copsLocation [5][2], int maxRow, int maxCol);
int IsBoardFull(char board [3][3]);
char firstName[10];
char lastName[10];
int board [MAX_SIZE][MAX_SIZE];
char *leftAction = "a", *rightAction = "d", *upAction = "w", *downAction = "s", *donotMove = "x";
int main(int argc, const char * argv[]) {
    Games();
    return 0;
}
/*************************************************************************
 Function name: Games
 Input: void
 Output: void
 The function operation: choose the game and play it
 ************************************************************************/
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
/*************************************************************************
 Function name: SetNames
 Input: void
 Output: void
 The function operation: setting the names of the first and last name
 ************************************************************************/
void SetNames(void) {
    printf("Enter first name\n");
    scanf("%s", firstName);
    
    printf("Enter last name\n");
    scanf("%s", lastName);
}
/*************************************************************************
 Function name: CopsAndRobbers
 Input: void
 Output: void
 The function operation: playing the game of cops and robbers and control the operation
 ************************************************************************/
void CopsAndRobbers(void) {
    printf("Let's choose the size:\n");
    int row = SetRows();
    int col = SetColumns(row);
    int maxRowIndex = row  - 1, maxColIndex = col - 1;
    PrintBoard(row, col);
    printf("How many cops would you like (1-5)?\n");
    int cops = 0;
    scanf("%d", &cops);
    // this is the amount of cops we have and will contril all loop over the cops
    const int copsSize = cops;
    int coptsLocations [5][2];
    int rowIndex = 0;
    for (; rowIndex <= row; rowIndex++) {
        int colIndex = 0;
        for (; colIndex <= col; colIndex++) board[rowIndex][colIndex] = 0;
    }
    // set robber location
    board[3][2] = -1;
    int roobberLocation [2] = {3, 2};
    int copIndex = 0;
    while(copIndex < copsSize) {
        // get the user choice and validate it
        printf("Let's choose cells:\n");
        int rowChoise, colChoise;
        scanf("%d %d", &rowChoise, &colChoise);
        int isValid = IsValidLocation(row, col,rowChoise, colChoise);
        if (isValid) {
            board[rowChoise][colChoise] = 1;
            // printf("%d \n", board[rowChoise][colChoise]);
            coptsLocations[copIndex][0] = rowChoise;
            coptsLocations[copIndex][1] = colChoise;
            copIndex++;
        } else printf("Illegal choice!\n");
    }
    // starting the game affter init
    printf("Let's play!\n");
    printf("Initial states:\n");
    PrintBoard(row, col);
    
    
    int isCopTurn = 1;
    int turns = 0;
    
    while (1) {
        if (isCopTurn) {
            turns = turns + 1;
            printf("Cops:\n");
            int copsTurnIndex = 0;
            OrderCopsArray(coptsLocations, row, col);
            for (; copsTurnIndex < copsSize; copsTurnIndex++) {
                int rowLocationCop = coptsLocations[copsTurnIndex][0];
                int colLocationCop = coptsLocations[copsTurnIndex][1];
                printf("Cop [%d, %d] can move: ", rowLocationCop, colLocationCop);
                int up = rowLocationCop > 0  ? board[rowLocationCop - 1][colLocationCop] : board[maxRowIndex][colLocationCop];
                int down = rowLocationCop < maxRowIndex ? board[rowLocationCop + 1][colLocationCop] : board[0][colLocationCop];
                int left = colLocationCop > 0 ? board[rowLocationCop][colLocationCop - 1] : board[rowLocationCop][maxColIndex];
                int right = colLocationCop < maxColIndex ? board[rowLocationCop][colLocationCop + 1] : board[rowLocationCop][0] ;
                
                if (IsLocationAvailable(up, 0)) printf("up(w) ");
                if (IsLocationAvailable(down, 0)) printf("down(s) ");
                if (IsLocationAvailable(left, 0)) printf("left(a) ");
                if (IsLocationAvailable(right, 0)) printf("right(d) ");
                printf("\n");
                
            }
            int rowLocationChoice, colLocationChoice;
            char actionMovement; // a - left w - up r - d down - s
            printf("Select a cop[row,col] and a direction\n");
            scanf("%d %d %c", &rowLocationChoice, &colLocationChoice , &actionMovement);
            int isValidLocation  = IsLocationUnAvailable(board[rowLocationChoice][colLocationChoice], 0) && rowLocationChoice < maxRowIndex + 1 && colLocationChoice < maxColIndex + 1 && rowLocationChoice > -1
            && colLocationChoice > -1;
            int isValidMovement = actionMovement == *leftAction || actionMovement == *rightAction|| actionMovement == *downAction || actionMovement == *upAction;
            // checking if the input is valid
            if (isValidLocation && isValidMovement) {
                // calculate the location need to lend
                MoveCop(rowLocationChoice, colLocationChoice, actionMovement, maxRowIndex, maxColIndex, copsSize, coptsLocations);
                // checking if the location is valid
                
            }
            else printf("you lose this turn\n");
            isCopTurn = 0;
            int robberLocRow = roobberLocation[0], robberLocCol =  roobberLocation[1];
            if (board[robberLocRow][robberLocCol] == 1 ) {
                // finishe the game
                printf("The cops won!");
                // printing what evet
                break;
            }
            if (turns > 30) {
                printf("The robber managed to escape!\n");
                break;
            }
        }
        else {
            printf("Robbers:\n");
            // calc the robber location need to move
            float locationArrayDistances [4][2]; // distance index
            int copsIndexRooberTurn = 0, iterCount = 0;
            for(; copsIndexRooberTurn < copsSize; copsIndexRooberTurn++) {
                int x1 = coptsLocations[copsIndexRooberTurn][0] , y1 = coptsLocations[copsIndexRooberTurn][1];
                float distance = CalcDistance(x1,y1,roobberLocation[0], roobberLocation[1]);
                if (copsIndexRooberTurn) {
                    float currentDistance = locationArrayDistances[0][0];
                    // check is distance is less then
                    if (distance < currentDistance) {
                        iterCount = 1;
                        locationArrayDistances[0][0] = distance;
                        locationArrayDistances[0][1] = copsIndexRooberTurn;
                    } else if (distance == currentDistance) {
                        
                        locationArrayDistances[iterCount][0] = distance;
                        locationArrayDistances[iterCount][1] = copsIndexRooberTurn;
                        iterCount = iterCount + 1;
                    }
                } else {
                    // this is will only fire on the firt iteration
                    locationArrayDistances[0][0] = distance;
                    locationArrayDistances[0][1] = copsIndexRooberTurn;
                    iterCount = iterCount + 1;
                }
            }
            // check the cop to calc the location from
            int closestCopIndex = 0, locationIndex = 1;
            // this loop will help which cop is the closest to us
            for (; locationIndex < iterCount; locationIndex++) {
                int indexToAcceses = locationArrayDistances[closestCopIndex][1];
                int cuurentIndexToAcceses = locationArrayDistances[locationIndex][1];
                int originLocationRow = coptsLocations[indexToAcceses][0], originLocationCol = coptsLocations[indexToAcceses][1];
                int currentLocationRow = coptsLocations[cuurentIndexToAcceses][0], currentLocationCol = coptsLocations[cuurentIndexToAcceses][1];
                if (originLocationRow == currentLocationRow) closestCopIndex = originLocationCol < currentLocationCol ? closestCopIndex : locationIndex;
                else if (originLocationRow > currentLocationRow) closestCopIndex = cuurentIndexToAcceses;
            }
            // need to check which direaction is the closest to.
            int copIndexClose = locationArrayDistances[closestCopIndex][1];
            char action = ClacRobberDireaction(coptsLocations[copIndexClose][0],coptsLocations[copIndexClose][1], roobberLocation[0], roobberLocation[1], maxRowIndex, maxColIndex);
            MoveRobber(roobberLocation, action);
            PrintBoard(row, col);
            isCopTurn = 1;
        }
        
    }
}
/*************************************************************************
 Function name: MoveCop
 Input: rowChoise - your choise,  colChoise - your col chosie, action the action up down, rowSize, the size of the rows ,colSize,amount of cops and there location cops, int copsLocation
 Output: void
 The function operation: move the cop in the game
 ************************************************************************/
void MoveCop(int rowChoise, int colChoise, char action, int rowSize, int colSize,int cops, int copsLocation [5][2]) {
    int rowLocation = rowChoise, colLocation = colChoise;
    if (action == *upAction) {
        rowLocation = rowChoise  == 0 ? rowSize : rowChoise - 1;
    }
    else if (action == *downAction) {
        if (rowChoise == rowSize) rowLocation = 0;
        else rowLocation = rowChoise + 1;
    }
    else if (action == *leftAction) {
        if (colChoise == 0) colLocation = colSize;
        else colLocation = colChoise - 1;
    }
    else if (action == *rightAction) {
        if (colChoise == colSize) colLocation = 0;
        else colLocation = colChoise + 1;
    }
    // when the location is valid
    if (IsLocationAvailable(board[rowLocation][colLocation], 0)) {
        board[rowChoise][colChoise] = 0;
        board[rowLocation][colLocation] = 1;
        PrintBoard(rowSize + 1, colSize + 1);
        int indexCop = 0;
        for (;indexCop < cops; indexCop++) {
            int rowCopLoc = copsLocation[indexCop][0] , colCopLoc = copsLocation[indexCop][1];
            if (rowCopLoc == rowChoise && colChoise == colCopLoc) {
                copsLocation[indexCop][0] = rowLocation;
                copsLocation[indexCop][1] = colLocation;
                break;
            }
        }
    } else printf("you lose this turn\n");
}
/*************************************************************************
 Function name: MoveCop
 Input: void
 Output: void
 The function operation: playing the game of tic tac tow
 ************************************************************************/
void TicTacToe(void) {
    char ticTacToe [3][3] = { };
    int i = 0;
    for (; i < 3; i++) {
        int j = 0;
        for (; j < 3; j++) ticTacToe[i][j] = TIC_TAC_EMPTY_CHAR;
    }
    int computerStartingPoint [2] = {0,0};
    int isComputerTurn = 0;
    PirintTicTacBoard(ticTacToe);
    while (1) {
        
        if (isComputerTurn) {
            // play computer
            printf("Computer's turn\n");
            int rowStart = computerStartingPoint[0], colStart = computerStartingPoint[1];
            int available = 0;
            int locationFind = 0;
            for (; locationFind < 9; locationFind++) {
                if(locationFind) ComputerMoveTicTacToe(computerStartingPoint);
                int value = ticTacToe[computerStartingPoint[0]][computerStartingPoint[1]];
                available = IsLocationAvailableTicTacToe(value);
                if (available) break;
            }
            if (available) {
                ticTacToe[computerStartingPoint[0]][computerStartingPoint[1]] = TIC_TAC_COMPUTER_CHAR;
                computerStartingPoint[0] = rowStart;
                computerStartingPoint[1] = colStart;
                // init the next point
                ComputerMoveTicTacToe(computerStartingPoint);
                ComputerMoveTicTacToe(computerStartingPoint);
            } else {
                // handle what happan when the board is full
                printf("It was a tie!\n");
                break;
            }
            isComputerTurn = 0;
            PirintTicTacBoard(ticTacToe);
            //
        } else {
            // play user
            printf("Select a square [row, col]\n");
            int row, col;
            scanf("%d %d", &row, &col);
            // check if valid location
            if (!IsInBoardTicTac(row, col)) {
                printf("Outside of board\n");
                continue;
            } else if (IsLocationUnAvailableTicTacToe(ticTacToe[row][col])) {
                printf("Invalid square\n");
                continue;
            }
            ticTacToe[row][col] = TIC_TAC_USER_CHAR;
            isComputerTurn = 1;
            PirintTicTacBoard(ticTacToe);
            
        }
        int isUserWinning = IsThereWinningStrike(ticTacToe, TIC_TAC_USER_CHAR);
        if (isUserWinning) {
            printf("%s %s has won\n", firstName, lastName);
            break;
        }
        int isComputerWinning = IsThereWinningStrike(ticTacToe, TIC_TAC_COMPUTER_CHAR);
        if (isComputerWinning) {
            printf("%s %s has lost!\n", firstName, lastName);
            break;
        }
        if (IsBoardFull(ticTacToe)) {
            // handle what happan when the board is full
            printf("It was a tie!\n");
            break;
        }
    }
    
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
        for(; colIndex < col ; colIndex++) PrintLocationForrmated(board[rowIndex][colIndex]);
        printf("\n");
    }
    printf("\n");
}
/*************************************************************************
 Function name: SetRows
 Input: void
 Output: int
 The function operation: get the number of row and return them
 ************************************************************************/
int SetRows(void) {
    int row;
    scanf("%d" , &row);
    if (row > MAX_SIZE) return MAX_SIZE;
    else if (row < MIN_SIZE) return MIN_SIZE;
    return row;
}
/*************************************************************************
 Function name: SetColumns
 Input: int rows
 Output: int
 The function operation: get the number of cols and return them consider the rows
 ************************************************************************/
int SetColumns(int row) {
    int col;
    scanf("%d" , &col);
    if (col == -1) return row;
    else if( col > MAX_SIZE) return MAX_SIZE;
    else if ( col < MIN_SIZE) return MIN_SIZE;
    return col;
}
/*************************************************************************
 Function name: IsValidLocation
 Input: the anount of rows and col , the location chosed by the user
 Output: int
 The function operation: get the number of cols and return them consider the rows
 ************************************************************************/
int IsValidLocation(int row,int col , int userChoiseRow, int userChoiseCol) {
    if (userChoiseRow >= row || userChoiseCol >= col ) return 0;
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
    // return includeRobber ? !(v == 1 || v == -1) : v != 1;
    if (includeRobber) return !(v == 1 || v == -1);
    return v != 1;
}
/*************************************************************************
 Function name: IsLocationUnAvailable
 Input: the value in the boarrd and do you want to include the rubber
 Output: int
 The function operation: chcek if the location in not available
 ************************************************************************/
int IsLocationUnAvailable(int v, int includeRobber) {
    return !IsLocationAvailable(v,includeRobber);
}
/*************************************************************************
 Function name: PrintLocationForrmated
 Input: int v value in point board
 Output: void
 The function operation:print the location the way we want with - R and C
 ************************************************************************/
void PrintLocationForrmated(int v) {
    if (v == 1) printf("C");
    else if (v == -1) printf("R");
    else printf("-");
}
/*************************************************************************
 Function name: CalcDistance
 Input: int x1, int y1, int x2, int y2
 Output: float
 The function operation:return the distance of two points
 ************************************************************************/
float CalcDistance(int x1, int y1, int x2, int y2) {
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}
/*************************************************************************
 Function name: ClacRobberDireaction
 Input:int copRow, int copCol, int robberRow, int robberCol, int maxRow, int maxCol
 Output: char
 The function operation:return the action the roober need to go to
 ************************************************************************/
char ClacRobberDireaction(int copRow, int copCol, int robberRow, int robberCol, int maxRow, int maxCol) {
    int minDistance = -1;
    // check up movement down left and right
    float upDistance = IsLocationAvailable(board[robberRow - 1][robberCol], 0) && robberRow > 0 ? CalcDistance(copRow, copCol, robberRow - 1, robberCol) : minDistance ;
    float downDistance = IsLocationAvailable(board[robberRow + 1][robberCol], 0) && robberRow < maxRow ? CalcDistance(copRow, copCol, robberRow + 1, robberCol) : minDistance;
    float leftDistance = IsLocationAvailable(board[robberRow][robberCol - 1], 0) && robberCol > 0 ? CalcDistance(copRow, copCol, robberRow, robberCol - 1) : minDistance;
    float rightDistance = IsLocationAvailable(board[robberRow][robberCol + 1], 0) && robberCol < maxCol ? CalcDistance(copRow, copCol, robberRow, robberCol + 1) : minDistance;
    float distances [4][2] = { {upDistance, *upAction} , {downDistance, *downAction}, {leftDistance, *leftAction}, {rightDistance, *rightAction}};
    // loop to sort the array and get the max distance
    int i = 1;
    int minIndex = 0;
    for (; i < 4; i++) {
        minIndex = distances[minIndex][0] >= distances[i][0] ? minIndex : i;
    }
    if (distances[minIndex][0] == minDistance) return *donotMove;
    return distances[minIndex][1];
}
/*************************************************************************
 Function name: MoveRobber
 Input: int robberLocation[2], char action
 Output: void
 The function operation: move the robber for each action
 ************************************************************************/
void MoveRobber(int robberLocation[2], char action) {
    int currentRowRobber = robberLocation[0], currentColRobber = robberLocation[1];
    int newLocationRow = currentRowRobber, newLocationCol = currentColRobber;
    if (action == *upAction) newLocationRow = newLocationRow - 1;
    else if (action == *downAction) newLocationRow = newLocationRow + 1;
    else if (action == *leftAction) newLocationCol = newLocationCol - 1;
    else if (action == *rightAction) newLocationCol = newLocationCol + 1;
    board[currentRowRobber][currentColRobber] = 0;
    board[newLocationRow][newLocationCol] = -1;
    robberLocation[0] = newLocationRow;
    robberLocation[1] = newLocationCol;
}
/*************************************************************************
 Function name: IsThereWinningStrike
 Input: char board [3][3], char winType
 Output: int
 The function operation: check in tic tac toe if there is a winning strike
 ************************************************************************/
int IsThereWinningStrike(char board [3][3], char winType) {
    int topLeft = board[0][0], topMiddle = board[0][1], topRight = board[0][2];
    int middleLeft = board[1][0], center = board[1][1], middleRight = board[1][2];
    int bottomLeft = board[2][0], bottomMiddle = board[2][1], bottomRight = board[2][2];
    int horizontal = (topLeft == topMiddle && topRight == topMiddle && topMiddle == winType) ||
    (middleLeft == center && center == middleRight && middleRight == winType) ||
    (bottomLeft == bottomMiddle && bottomMiddle == bottomRight && bottomRight == winType);
    int vertical = (topLeft == middleLeft && middleLeft == bottomLeft && bottomLeft == winType) ||
    (topMiddle == center && center == bottomMiddle && bottomMiddle == winType) ||
    (topRight == middleRight && middleRight == bottomRight && bottomRight == winType);
    int diagonal = (topLeft == center && center == bottomRight && bottomRight == winType) || (topRight == center && center == bottomLeft && bottomLeft  == winType);
    return horizontal || vertical || diagonal;
}
/*************************************************************************
 Function name: IsInBoardTicTac
 Input: int row, int col
 Output: int
 The function operation: check in tic tac toe if the location is valid
 ************************************************************************/
int IsInBoardTicTac(int row, int col) {
    return row < 3 && row > -1 && col < 3 && col > -1;
}
/*************************************************************************
 Function name: IsLocationAvailableTicTacToe
 Input:char v value in point
 Output: int
 The function operation: check is the location aviable tic tac toe game
 ************************************************************************/
int IsLocationAvailableTicTacToe (char v) {
    return v == TIC_TAC_EMPTY_CHAR;
}
/*************************************************************************
 Function name: IsLocationUnAvailableTicTacToe
 Input:char v value in point
 Output: int
 The function operation: check is the location in not aviable tic tac toe game
 ************************************************************************/
int IsLocationUnAvailableTicTacToe (char v) {
    return !IsLocationAvailableTicTacToe(v);
}
/*************************************************************************
 Function name: ComputerMoveTicTacToe
 Input:char v value in point
 Output: void
 The function operation: check is the location in not aviable tic tac toe game
 ************************************************************************/
void ComputerMoveTicTacToe (int startingLocation[2]) {
    int row = startingLocation[0], col = startingLocation[1];
    if (col == row && row == 2) {
        startingLocation[0] = 0;
        startingLocation[1] = 0;
    } else if (col == 2) {
        startingLocation[0] = row + 1;
        startingLocation[1] = 0;
    }
    else startingLocation[1] = col + 1;
    
}
/*************************************************************************
 Function name: PirintTicTacBoard
 Input: char board[3][3]
 Output: int
 The function operation: print the board in tic tac
 ************************************************************************/
void PirintTicTacBoard(char board[3][3]) {
    int i = 0;
    for (; i < 3; i++) {
        int j = 0;
        for (; j < 3; j++) printf("%c", board[i][j]);
        printf("\n");
    }
}
/*************************************************************************
 Function name: OrderCopsArray
 Input: int copsLocation [5][2], int maxRow, int maxCol
 Output: void
 The function operation: Oeder the cops array to print theme
 ************************************************************************/
void OrderCopsArray(int copsLocation [5][2], int maxRow, int maxCol) {
    int row = 0, count = 0;
    for (; row < maxRow; row++) {
        int col = 0;
        for (; col < maxCol; col++) {
            if (board[row][col] == 1) {
                copsLocation[count][0] = row;
                copsLocation[count][1] = col;
                count = count + 1;
            }
        }
    }
}
/*************************************************************************
 Function name: IsBoardFull
 Input: char board [3][3]
 Output: int
 The function operation: check if the board is full tic tac game
 ************************************************************************/
int IsBoardFull(char board [3][3]) {
    int i = 0;
    for (; i< 3; i++) {
        int col = 0;
        for (; col < 3; col++) {
            if (board[i][col] == TIC_TAC_EMPTY_CHAR) return 0;
        }
    }
    return 1;
}

