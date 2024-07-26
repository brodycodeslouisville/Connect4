#include <stdio.h>
#include <stdlib.h> /* included for rand() function FROM geeksforgeeks.org (https://www.geeksforgeeks.org/c-rand-function/) */

char boardTemp[6][7]; /* Create array for game board */
int i, j, result, x, y, xCons, yCons, x1, yC, compChoice, compX, moves; /* various integers for tracking */
char user, winner; /* keeps track of user and winner, indicated by 'X' or 'O' */

int printBoard(char boardTemp[6][7]) { /* Function to print graphic for new board */

    printf("\n6\t");
    for (i = 0; i < 6; i++) { /* loops through entire array printing current values in boardTemp */
        for (j = 0; j < 7; j++) {
            printf("| %c ", boardTemp[i][j]);
        }
        if (i == 5){
            printf("|\n");
        }
        else {
            printf("|\n%d\t", 5-i);
        }
    }
    printf("Y/X\t  1   2   3   4   5   6   7\n\n"); /* print column labels at bottom of game board*/
}

int checkWin(char boardTemp[6][7], char user) { /* Function to check if winner */
    
            xCons = 0; /* counter for consecutive values on board in X axis */
            yCons = 0; /* counter for consecutive values on board in Y axis */
            
            for (x = 0; x < 7; x++) { /* Check Y for win */
                for (y = 0; y < 6; y++){
                       if (boardTemp[y][x] == user) {
                           yCons++; /* add to counter if values in a row are same */
                       }
                       else{
                           yCons = 0; /* reset counter when consecutive values are broken */
                       }
                       if (yCons >= 4) { /* once four in a row, current user wins */
                           result = 1;
						   winner = user;
                       }
                }
                yCons = 0; /* reset when moving to new column */
            }
            for (y = 0; y < 6; y++){ /* Check X for Win */
                for (x = 0; x < 7; x++) {
                       if (boardTemp[y][x] == user) {
                           xCons++; /* add to counter if values in a row are same */
                       }
                       else{
                           xCons = 0; /* reset counter when consecutive values are broken */
                       }
                       if (xCons >= 4) { /* once four in a row, current user wins */
                           result = 1;
						   winner = user;
                       }
                }
                xCons = 0; /* reset when moving to new row */
            }
        	for (yC = 0; yC < 3; yC++) {
	            for (x1 = 0; x1 < 7; x1++) { /* Diagonal Down & Right Direction Check for win*/
	            	for (x = x1, y = yC; (x < 7 && y < 6); x++, y++) {
	                       if (boardTemp[y][x] == user) {
	                           xCons++;
	                       }
	                       else{
	                           xCons = 0;
	                       }
	                       if (xCons >= 4) {
	                           result = 1;
	                           winner = user;
	                       }
	            	}
	        	}
        	}
        	for (yC = 0; yC < 3; yC++) {
	            for (x1 = 7; x1 > 0; x1--) { /* Diagonal Down & Left Direction Check for win */
	            	for (x = x1, y = yC; (x < 7 && y < 6); x--, y++) {
	                       if (boardTemp[y][x] == user) {
	                           xCons++;
	                       }
	                       else{
	                           xCons = 0;
	                       }
	                       if (xCons >= 4) {
	                           result = 1;
	                           winner = user;
	                       }
	            	}
	        	}
        	}
    return result;
}

int compDec(char boardTemp[6][7], int heights[8]) { /* function for computer player decision on placement of marker */
	
	compChoice = (rand() % (7-1+1)) + 1; /* generate random integer between 1 and 7 that is representative of the column */
	
while ((heights[compChoice] == 6)){ /* loop through until computer selects column with empty space */	
	compChoice = rand() % (7-1+1);
}
	return compChoice;
}

int main() { /* main function to run connect 4 game */

int menuChoice, rowH[7];

while (menuChoice != 2){
    
int heights[8] = {0, 0, 0, 0, 0, 0, 0, 0}; /* keeps track of marker height in each column to subsequently stack markers */
    
    for (i = 0; i < 6; i++) { /* clear board by making all values in array blank */
        for (j = 0; j < 7; j++) {
            boardTemp[i][j] = ' ';
        }
    }

    printf("Welcome to Connect Four!\n\n");
	printf("Game Objective: create four adjacent markings");
	printf("\neither horizontally, vertically, or diagonally.\n");
	printf("\n\t1) Start Game\n\t2) Exit\n"); /* intro to main function */
    scanf("%d", &menuChoice); /* user selection to start game/exit */

    if (menuChoice == 1) { /* user decides to start game */
    	
    	moves = 0; /* reset total game moves to zero */
    	
        while (result == 0){ /* loop through code while no one has connected 4 (no winner) */
               
            printBoard(boardTemp); /* print board so user can see options */
            printf("Please Choose a Column to Place Marker in:\n\tX: "); /* user entry for column to drop marker in*/
            scanf("%d", &j);
                while (j > 7 || j < 1 || heights[j] == 6) { /* check that column value is valid, and not yet full of markers */
                    printf("Invalid Entry\n\n"); /* inform user if invalid */
                    printf("Please Choose a Coordinate to Mark:\n\tX: ");
                    scanf("%d", &j);
                }

            user = 'X'; /* user indicated by 'X' markers on board */
            
            boardTemp[5-heights[j]][j-1] = user; /* register valid mark for user */
            heights[j] = heights[j] + 1; /* track column height on board */
            
            moves++; /* add game move */
            
            checkWin(boardTemp, user); /* checkWin function to determine if user has won or not */
            
            if (result == 0){ /* if user hasn't won yet, proceed */
            
            user = 'O'; /* computer player markers notated with 'O' marker on board */
            
            j = compDec(boardTemp, heights); /* user computer decision function to determine where the computer player will mark */
            boardTemp[5-heights[j]][j-1] = user; /* make computer marking */
            heights[j] = heights[j] + 1;
            printf("\nComputer Move:\n\tX: %d\n", j); /* inform user of computer move */
            
            moves++; /* add to total moves */
            
            checkWin(boardTemp, user); /* check to see if computer player won */
            
if ((moves == 42) && (result != 1)) { /* check if board is full and no winner, in which case game ends in draw (tie) */
	result = 2;
}
            
        	}
            
        }
    }

if (menuChoice != 2) {

printBoard(boardTemp);

if ((moves == 42) && (result != 1)) {
	winner = 'D';
}

//printf("\n\nWinner: %c\n\n", winner);

if (winner == 'X') { /* if statements to inform user of outcome of game */
	printf("User Wins!!!\n\n");
}
else if (winner == 'O') {
	printf("Computer Wins :(\n\n");
}
else{
	printf("Draw, play again!\n\n");
}

result = 0; /* restart menu sequence in case user wants to play again */

}
}

    return 0;
}