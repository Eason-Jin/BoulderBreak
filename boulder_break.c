#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAVE_SIZE 10

/*  Edge # = 1
    Path   = 0
    Exit E = -1
    Player X = 2
    Hole * = -2
    Treasure + = 3
    Boulder o = -3
*/

// InitialiseStory
// Write a story and copy it to the string where the stpry pointer is pointed at.
// Input: NONE
// Output: NONE
void InitialiseStory(char* paragraph)
{
	char temp[2000] = "The sun is shining, the birds are singing, and Peter\nhappily juggles machete while riding his 6-foot tall,\nchrome-plated, neon-glowing unicycle. As he turns\naround a corner, a wild\n\n<The C Programming Language (by Brian K. & Dennis R.)>\n\nappeared and starts attacking him with errors and warnings!\nPeter quickly pulled out his Arch Linux (while juggling)\nand quickly typed:\n\n#define _CRT_SECURE_NO_WARNINGS\n\nBut it is not very effective, as <The C Programming\nLanguage> removed the base condition for a recursive\nfunction, Peter's memory overflowed, fell off his\nunicycle and into a 6-foot cave. Without his unicycle,\nhe is now trapped! After being passed out for 2^8 seconds,\nPeter stood up and started exploring the cave. The cave is\ndark, Peter looked at his Linux and decided to activate the\nemergency protocol. He booted it up, opened VS Code and\nclicked on Settings\\Themes. His hand shaking, but he still\npressed the button. \"Github Light Default\". Suddenly, the\ncave is filled with blindingly bright light. So bright that\nit is burning Peter's eye. He knew he must get out of this\ncave ASAP......\0";
    strcpy(paragraph,temp);
}

// PrintCave
// Print out a cave using symbols.
// Input: Cave matrix of integers
// Output: The corresponding symbol for each value
void PrintCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int i,j;

	for (i=0;i<CAVE_SIZE;i++) {
		for (j=0;j<CAVE_SIZE;j++) {
			switch(cave[i][j])
            {
                case 1:
                    printf("#");
                    break;
                case -1:
                    printf(" ");
                    break;
                case 0:
                    printf(" ");
                    break;
                case 2:
                    printf("X");
                    break;
                case -2:
                    printf("*");
                    break;
                case 3:
                    printf("+");
                    break;
                case -3:
                    printf("O");
                    break;
            }
		}
		printf("\n");
	}
}


// InitialiseCave
// Define the boundary, moving space and exit of the cave.
// Input: Cave matrix of integers
// Output: NONE, modify the cave matrix using pointers
void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char *layout)
{
	int i,j;
    char current;

    for (i=0;i<CAVE_SIZE;i++) {
        for (j=0;j<CAVE_SIZE;j++){
            current = layout[i*CAVE_SIZE+j];
            switch(current)
            {
                case '1':
                    cave[i][j] = 1;
                    break;
                case 'E':
                    cave[i][j] = -1;
                    break;
                default:
                    cave[i][j] = 0;
            }
        }
    }
}

// IsBorderComplete
// Check for the completeness of the boundary. There can be no gaps or ‘empty space’ in the outside border of the cave. The exit position must be on the border of the cave.
// Input: Cave matrix of integers
// Output: Boolean(integer) of whether the boundary is complete
int IsBorderComplete(int cave[CAVE_SIZE][CAVE_SIZE])
{
    int i,j;

    //First line
    for (j=0;j<CAVE_SIZE;j++) {
        if (cave[0][j]==0) {
            return 0;
        }
    }
    //Last line
    for (j=0;j<CAVE_SIZE;j++) {
        if (cave[CAVE_SIZE-1][j]==0) {
            return 0;
        }
    }
    //Body
    for (i=1;i<CAVE_SIZE-1;i++) {
        //First column
        if (cave[i][0]==0) {
            return 0;
        }
        //Last column
        if (cave[i][CAVE_SIZE-1]==0) {
            return 0;
        }
    }

    return 1;   
}

// IsExitUnique
// Check for the number is exits in the cave. There can only be one exit.
// Input: Cave matrix of integers
// Output: Boolean(integer) of whether there is only one integer
int IsExitUnique(int cave[CAVE_SIZE][CAVE_SIZE])
{
    int i,j;
    int counter = 0;

    // Check exit number
    for (i=0;i<CAVE_SIZE;i++) {
        for (j=0;j<CAVE_SIZE;j++){
            if (cave[i][j] == -1) {
                counter++;
            }
        }
    }
    if (counter==1) {
        return 1;
    } else {
        return 0;
    }
}

// IsExitAccessible
// Check whether the exit can be reached by the player. The exit cannot be at the corners or inside of the cave.
// Input: Cave matrix of integers
// Output: Boolean(integer) of whether the player can reach the exit
int IsExitAccessible(int cave[CAVE_SIZE][CAVE_SIZE])
{
    int i,j;
    for (i=0;i<CAVE_SIZE;i++) {
        if ((i==0)||(i==CAVE_SIZE-1)) {
            for (j=1;j<CAVE_SIZE-1;j++) {
                if (cave[i][j]==-1) {
                    return 1;
                }
            }
        } else {
            for (j=0;j<CAVE_SIZE;j+=CAVE_SIZE-1) {
                if (cave[i][j]==-1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// AddItem
// Add other game elements like the boulder, the hole and treasure.
// Input: Cave matrix of integers, coordinates(row,col), element
// Output: NONE. Modified cave with the elements added using pointers
void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char *element)
{
    int i,j;
    int plr = 0;

    if ((row<CAVE_SIZE) && (row>0) && (col<CAVE_SIZE) && (col>0)) {
        
        if (cave[row][col]!=0) {
            return;
        }
        
        if (strcmp(element,"player")==0) {
            
            for (i=0;i<CAVE_SIZE;i++) {
                for (j=0;j<CAVE_SIZE;j++){
                    if (cave[i][j]==2) {
                        plr = 1;
                        break;
                    }
                }
            }
            if (plr == 0) {
                cave[row][col] = 2;
            }

        } else if (strcmp(element,"boulder")==0) {
            cave[row][col] = -3;
        } else if (strcmp(element,"hole")==0) {
            cave[row][col] = -2;
        } else if (strcmp(element,"treasure")==0) {
            cave[row][col] = 3;
        }
    }
}

// RotateCave
// Rotate the cave 90 degrees clockwise everytime this function is called
// Input: Cave matrix of integers
// Output: NONE. Modify the cave using pointers
void RotateCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
    int temp[CAVE_SIZE][CAVE_SIZE];
    int i,j;

    for (i=0;i<CAVE_SIZE;i++) {
        for (j=0;j<CAVE_SIZE;j++) {
            temp[j][CAVE_SIZE-1-i] = cave[i][j];
        }
    }
    for (i=0;i<CAVE_SIZE;i++) {
        for (j=0;j<CAVE_SIZE;j++) {
            cave[i][j] = temp[i][j];
        }
    }
}

// MakeMove
// Make the player move accordingly to the user input and game elements
// Input: Cave matrix of integers, move
// Output: Modify the cave using pointers and return an integer indicating the status of the player
int MakeMove(int cave[CAVE_SIZE][CAVE_SIZE], char move)
{
    int i,j,plrRow,plrCol;
    int bouRow,bouCol;

    //Get player position
    for (i=1;i<CAVE_SIZE-1;i++) {
        for (j=1;j<CAVE_SIZE-1;j++) {
            if (cave[i][j]==2) {
                plrRow = i;
                plrCol = j;
            }
        }
    }

    switch(move)
    {
        //Move UP
        case 'w':
            switch(cave[plrRow-1][plrCol])
            {
                //When player is against a wall
                case 1:
                    break;
                //When player is free to move
                case 0:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow-1][plrCol] = 2;
                    break;
                //When player exits
                case -1:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow-1][plrCol] = 2;
                    return 2;
                //When player falls into a hole
                case -2:
                    cave[plrRow][plrCol] = 0;
                    return 1;
                //When player gets a treasure
                case 3:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow-1][plrCol] = 2;
                    break;
                //When player pushes a boulder
                case -3:
                    bouRow = plrRow-1;
                    bouCol = plrCol;
                    
                    while ((cave[bouRow-1][bouCol]==0)||(cave[bouRow-1][bouCol]==-2)) {
                        cave[bouRow][bouCol] = 0;
                        bouRow--;
                        if (cave[bouRow][bouCol]==-2) {
                            cave[bouRow][bouCol]=0;
                            break;
                        } else {
                            cave[bouRow][bouCol] = -3;
                        }
                    }
                    
                    break;
            }
            break;

        //Move LEFT
        case 'a':
            switch(cave[plrRow][plrCol-1])
            {
                //When player is against a wall
                case 1:
                    break;
                //When player is free to move
                case 0:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow][plrCol-1] = 2;
                    break;
                //When player exits
                case -1:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow][plrCol-1] = 2;
                    return 2;
                //When player falls into a hole
                case -2:
                    cave[plrRow][plrCol] = 0;
                    return 1;
                //When player gets a treasure
                case 3:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow][plrCol-1] = 2;
                    break;
                //When player pushes a boulder
                case -3:
                    bouRow = plrRow;
                    bouCol = plrCol-1;
                    
                    while ((cave[bouRow][bouCol-1]==0)||(cave[bouRow][bouCol-1]==-2)) {
                        cave[bouRow][bouCol] = 0;
                        bouCol--;
                        if (cave[bouRow][bouCol]==-2) {
                            cave[bouRow][bouCol]=0;
                            break;
                        } else {
                            cave[bouRow][bouCol] = -3;
                        }
                    }
                    
                    break;
            }
            break;

        //Move DOWN
        case 's':
            switch(cave[plrRow+1][plrCol])
            {
                //When player is against a wall
                case 1:
                    break;
                //When player is free to move
                case 0:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow+1][plrCol] = 2;
                    break;
                //When player exits
                case -1:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow+1][plrCol] = 2;
                    return 2;
                //When player falls into a hole
                case -2:
                    cave[plrRow][plrCol] = 0;
                    return 1;
                //When player gets a treasure
                case 3:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow+1][plrCol] = 2;
                    break;
                //When player pushes a boulder
                case -3:
                    bouRow = plrRow+1;
                    bouCol = plrCol;
                    
                    while ((cave[bouRow+1][bouCol]==0)||(cave[bouRow+1][bouCol]==-2)) {
                        cave[bouRow][bouCol] = 0;
                        bouRow++;
                        if (cave[bouRow][bouCol]==-2) {
                            cave[bouRow][bouCol]=0;
                            break;
                        } else {
                            cave[bouRow][bouCol] = -3;
                        }
                    }
                    
                    break;
            }
            break;

        //Move RIGHT
        case 'd':
            switch(cave[plrRow][plrCol+1])
            {
                //When player is against a wall
                case 1:
                    break;
                //When player is free to move
                case 0:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow][plrCol+1] = 2;
                    break;
                //When player exits
                case -1:
                    cave[plrRow][plrCol] = 0;
                    cave[plrRow][plrCol+1] = 2;
                    return 2;
                //When player falls into a hole
                case -2:
                    cave[plrRow][plrCol] = 0;
                    return 1;
                //When player gets a treasure
                case 3:
                    cave[plrRow][plrCol+1] = 2;
                    cave[plrRow][plrCol] = 0;
                    break;
                //When player pushes a boulder
                case -3:
                    bouRow = plrRow;
                    bouCol = plrCol+1;
                    
                    while ((cave[bouRow][bouCol+1]==0)||(cave[bouRow][bouCol+1]==-2)) {
                        cave[bouRow][bouCol] = 0;
                        bouCol++;
                        if (cave[bouRow][bouCol]==-2) {
                            cave[bouRow][bouCol]=0;
                            break;
                        } else {
                            cave[bouRow][bouCol] = -3;
                        }
                    }
                    
                    break;
            }
            break;
    }
    return 0;
}


/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
		scanf("%c", &move);
	}
	return move;
}

/* The Boulder Break simulation */
int main(void)
{
	char story[2000];
	char layout[200] = "1111111E11111000000110000000011000011111100000111110000001111000000001111000000110000000011111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = {0};
	int gameOver = 0;

	InitialiseStory(story);
	InitialiseCave(cave, layout);
    AddItem(cave, 7, 8, "player");
    AddItem(cave, 3, 1, "hole");
    AddItem(cave, 3, 2, "hole");
    AddItem(cave, 3, 3, "hole");
    AddItem(cave, 3, 4, "hole");
    AddItem(cave, 7, 7, "boulder");
    AddItem(cave, 7, 5, "boulder");
    AddItem(cave, 5, 5, "boulder");
    AddItem(cave, 2, 2, "treasure");
    AddItem(cave, 1, 6, "treasure");

	printf("ENGGEN131 - C Project 2022\n");
	printf("                          ... presents ...\n");
	printf("______   _____  _     _        ______  _______  ______\n");
	printf("|_____] |     | |     | |      |     \\ |______ |_____/\n");
	printf("|_____] |_____| |_____| |_____ |_____/ |______ |    \\_\n");
	printf("______   ______ _______ _______ _     _\n");
	printf("|_____] |_____/ |______ |_____| |____/ \n");
	printf("|_____] |    \\_ |______ |     | |    \\_\n");
	printf("\n");
	printf("%s\n", story);
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	PrintCave(cave);
	while (!gameOver) {
		gameOver = MakeMove(cave, GetMove());
		PrintCave(cave);
		if (gameOver == 1) {
			printf("\n\nGAME OVER!! \nYou died!\n\n");
		} else if (gameOver == 2) {
			printf("\n\nCONGRATULATIONS!! \nYou escaped!\n\n");
		}
	}

	return 0;
}