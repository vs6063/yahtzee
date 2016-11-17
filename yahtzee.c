// This program is designed to implement a simple scoring system for Yahtzee.
// Name: Victor Shen   
// zID:  z5117298

#include<stdio.h>
#include<stdlib.h>

#define NUM_OF_DICE 5
#define NUM_OF_INPUTS 800

#define TRUE 1
#define FALSE -1
#define NONE 0

void diceInput(char dummyDice[]);
int diceCheck(char dummyDice[]);
int checkFormat(char dummyDice[]);
int checkRange(char dummyDice[]);
int checkNumOfValues(char dummyDice[]);
void diceTransfer(char dummyDice[], int dice[]);
void dicePrint(int dice[]);
int diceSet(char dummyDice[], int dice[]);
int diceOptions(char dummyDice[], int dice[]);
int rerollSome(char dummyDice[],int dice[]);

int scoreOptions(int dice[], int score);
int threeOfAKind(int dice[]);
int fourOfAKind(int dice[]);
int fullHouse(int dice[]);
int smallStraight(int dice[]);
int straight(int dice[]);
int yahtzee(int dice[]);

int main(int argc, char *argv[]){
    
    int error = FALSE;
    printf("\n");
    char dummyDice[NUM_OF_INPUTS] = {0};
    int dice[NUM_OF_DICE] = {0};
    int score = 0;
    error = diceSet(dummyDice, dice);
    if(error == FALSE && score != FALSE){
        error = diceOptions(dummyDice, dice);
    }
    if(error == FALSE && score != FALSE){
        score = scoreOptions(dice, score);
    }
    if(error == FALSE && score != FALSE){
        printf("\nYour score is: %d points\n\n", score);
    }

    return EXIT_SUCCESS;
}

//Sets dice input; Combines all relevant functions into one. 
int diceSet(char dummyDice[], int dice[]){

    int error = FALSE;
    printf("Please enter dice values:\n> ");
    diceInput(dummyDice);
    error = diceCheck(dummyDice);
    if(error == FALSE){
        diceTransfer(dummyDice, dice);
        dicePrint(dice);
    }

    return error;
} 

//Inputs dice
void diceInput(char dummyDice[]){
    
    int i = 0;
    char x = 0;
    while(x != '\n' && i < NUM_OF_INPUTS){
        x = getchar();
        dummyDice[i] = x;
        i++;
    }
    dummyDice[i-1] = 0;
}

//Combines all the dice checking cases into one function.
int diceCheck(char dummyDice[]){
    
    int error = FALSE;
    error = checkFormat(dummyDice);
    if(error == FALSE){
        error = checkRange(dummyDice);
    }
    if(error == FALSE){
        error = checkNumOfValues(dummyDice);
    }

    return error;
}

//Check input format.
int checkFormat(char dummyDice[]){
    
    int error = FALSE;
    int i = 0;
    //Checks for non-integers and non-white spaces
    while(dummyDice[i] != 0 && error == FALSE){
        if((dummyDice[i] > '9' || dummyDice[i] < '0') && dummyDice[i] != ' '){
            printf("\nIncorrect Input Format.\n");
            error = TRUE;
        }
        i ++;
    }
    i = 0;
    //Checks for consecutive integers without white spaces inbetween
    while(dummyDice[i] != 0 && error == FALSE){
        if(dummyDice[i] <= '9' && dummyDice[i] >= '0' && dummyDice[i] != ' ' && dummyDice[i+1] <= '9' && dummyDice[i+1] >= '0' && dummyDice[i+1] != ' ' && dummyDice[i+1] != 0){
            printf("\nIncorrect Input Format.\n");
            error = TRUE;
        }
        i ++;
    }

    return error;
}

//Check input range. 
int checkRange(char dummyDice[]){
    
    int error = FALSE;
    int i = 0;
    //Checks for values that are not between 1 and 6
    while(dummyDice[i] != 0 && error == FALSE){
        if((dummyDice[i] < '1' || dummyDice[i] > '6') && dummyDice[i] != ' '){
            printf("\nValue Out of Range.\n");
            error = TRUE;
        }
        i ++;
    }

    return error;
}

//Check number of values of input. 
int checkNumOfValues(char dummyDice[]){
    
    int error = FALSE;
    int i = 0;
    int numOfDigits = 0;
    //Checks for if number of inputs not equal to 5
    while(dummyDice[i] != 0){
        if(dummyDice[i] >= '1' && dummyDice[i] <= '9'){
            numOfDigits ++;
        }
        i ++;
    }
    if(numOfDigits != NUM_OF_DICE){
        printf("\nIncorrect Number of Values.\n");
        error = TRUE;
    }

    return error;
}

//Transfers initial string input of dice into an integer array. 
void diceTransfer(char dummyDice[], int dice[]){
    
    int i = 0;
    int a = 0;
    while(dummyDice[i] != 0){
        if(dummyDice[i] <= '6' && dummyDice[i] >= '1'){
            dice[a] = dummyDice[i] - '0';
            a ++;
        }
        i ++;
    }
}

//Prints dice. 
void dicePrint(int dice[]){
    
    int i = 0;
    printf("\nYour dice values are:");
    while(i < NUM_OF_DICE){
        printf(" %d", dice[i]);
        i ++;
    }
    printf("\n\n");
}

//Reroll options for the dice. 
int diceOptions(char dummyDice[], int dice[]){
    
    int error = FALSE;
    int a[NUM_OF_INPUTS] = {0};
    int firstInteger = 0;
    int rerollTurn = 0;
    //Collecting input into a string
    while(a[firstInteger] != '3' && error == FALSE && rerollTurn < 2){
        printf("Please choose:\n");
        printf(" 1 -> Reroll some dice\n 2 -> Reroll all dice\n 3 -> Keep dice\n> ");
        int i = 0;
        char newLineCounter = 0;
        while(newLineCounter != '\n' && i < NUM_OF_INPUTS){
            newLineCounter = getchar();
            a[i] = newLineCounter;
            i++;
        }
        while(a[firstInteger] == ' '){
            firstInteger ++;
        }
        //Selects choice according to input
        if(a[firstInteger] == '1'){
            error = rerollSome(dummyDice, dice);
            rerollTurn ++;
        } else if(a[firstInteger] == '2'){
            printf("\n");
            error = diceSet(dummyDice, dice);
            rerollTurn ++;
        } else if(a[firstInteger] == '3'){
            printf("\n");
        } else if(a[firstInteger] != '3'){
            printf("\nInvalid Choice.\n");
            error = TRUE;
        }
    }

    return error;
}

//Allows player to reroll specific dice values
int rerollSome(char dummyDice[],int dice[]){
    
    //Prompts user to enter which dice to reroll, and stores in a string
    int error = FALSE;
    int i = 0;
    int h = 0;
    int newLineCounter = 0;
    char rerollInput[NUM_OF_INPUTS] = {0};
    printf("\nPlease enter dice to reroll (1 - 5):\n> ");
    while(newLineCounter != '\n' && i < NUM_OF_INPUTS){
        rerollInput[i] = getchar();
        h = 0;
        while(h < i){
            if(rerollInput[h] == rerollInput[i] && rerollInput[i] != ' '){
                rerollInput[i] = 0;
                h = i;
                i --;
            }
            h ++;
        }
        newLineCounter = rerollInput[i];
        i ++;
    }
    rerollInput[i-1] = 0;
    //Checks for errors when entering which dice to reroll
    int a = 0;
    error = checkFormat(rerollInput);
    if(error == FALSE){
        //Checks for values that are not between 1 and 5
        while(rerollInput[a] != 0 && error == FALSE){
            if((rerollInput[a] < '1' || rerollInput[a] > '5') && rerollInput[a] != ' '){
                printf("\nDice Number Out of Range.\n");
                error = TRUE;
            }
            a ++;
        }
    }
    //Transfers the string values into an integer array
    if(error == FALSE){
        int rerollInput2[NUM_OF_INPUTS] = {0};
        int b = 0;
        int inputNum = 0;
        while(rerollInput[b] != 0){
            if(rerollInput[b] != ' '){
                rerollInput2[inputNum] = rerollInput[b] - '0';
                inputNum ++;
            }
            b ++;
        }
        if(inputNum == 1){
            printf("\nPlease enter %d value:\n> ", inputNum);
        } else{
            printf("\nPlease enter %d values:\n> ", inputNum);
        }

        //Prompts user to enter the dice values for reroll some, stored in a string
        int c = 0;
        char diceInput[NUM_OF_INPUTS] = {0};
        newLineCounter = 0;
        while(newLineCounter != '\n'){
            diceInput[c] = getchar();
            newLineCounter = diceInput[c];
            c ++;
        }
        diceInput[c-1] = 0;
        //Checks the dice values for errors
        error = checkFormat(diceInput);
        if(error == FALSE){
            error = checkRange(diceInput);
        }
        if(error == FALSE){
            int d = 0;
            int numOfDigits = 0;
            //Checks for if num of inputs are not equal to num of dice chosen for reroll
            while(diceInput[d] != 0){
                if(diceInput[d] >= '1' && diceInput[d] <= '9'){
                    numOfDigits ++;
                 }
            d ++;
            }  
            if(numOfDigits != inputNum){
                printf("\nIncorrect Number of Values.\n");
                error = TRUE;
            }
        }
        if(error == FALSE){
            //Stores the string of dice input values into an integer array
            int e = 0;
            int f = 0;
            int diceInput2[NUM_OF_INPUTS] = {0};
            while(diceInput[e] != 0){
                if(diceInput[e] != ' '){
                    diceInput2[f] = diceInput[e] - '0';
                    f ++;
                }
                e ++;
            }
            //Transfers the dice input into the original dice array
            int g = 0;
            while(rerollInput2[g] != 0){
                dice[rerollInput2[g]-1] = diceInput2[g];
                g ++;
            }
            dicePrint(dice);
        }
    }

    return error;
}

//Valuation of score options for dice. 
int scoreOptions(int dice[], int score){    
    
    int threeOfAKindState = threeOfAKind(dice);
    int fourOfAKindState = fourOfAKind(dice);
    int fullHouseState = fullHouse(dice);
    int smallStraightState = smallStraight(dice);
    int straightState = straight(dice);
    int yahtzeeState = yahtzee(dice);
    
    int threeOfAKindWorth = (dice[0] + dice[1] + dice[2] + dice[3] + dice[4]);
    int fourOfAKindWorth = (dice[0] + dice[1] + dice[2] + dice[3] + dice[4]);
    int fullHouseWorth = 25;
    int smallStraightWorth = 30;
    int straightWorth = 40;
    int yahtzeeWorth = 50;
    int chanceWorth = (dice[0] + dice[1] + dice[2] + dice[3] + dice[4]);
    
    int choice1 = NONE;
    int choice2 = NONE;
    int choice3 = NONE;
    int choice4 = NONE;

    printf("Your score options are:\n");
    //Goes through all the dice combination cases and sets choices accordingly
    if(yahtzeeState == TRUE){
        printf(" 1 -> Three of a Kind (%d points)\n", threeOfAKindWorth);
        printf(" 2 -> Four of a Kind (%d points)\n", fourOfAKindWorth);
        printf(" 3 -> Yahtzee (%d points)\n", yahtzeeWorth);
        printf(" 4 -> Chance (%d points)\n> ", chanceWorth);
        choice1 = threeOfAKindWorth;
        choice2 = fourOfAKindWorth;
        choice3 = yahtzeeWorth;
        choice4 = chanceWorth;
    } else if(fourOfAKindState == TRUE){
        printf(" 1 -> Three of a Kind (%d points)\n", threeOfAKindWorth);
        printf(" 2 -> Four of a Kind (%d points)\n", fourOfAKindWorth);
        printf(" 3 -> Chance (%d points)\n> ", chanceWorth);
        choice1 = threeOfAKindWorth;
        choice2 = fourOfAKindWorth;
        choice3 = chanceWorth;    
    } else if(fullHouseState == TRUE){
        printf(" 1 -> Three of a Kind (%d points)\n", threeOfAKindWorth);
        printf(" 2 -> Full House (%d points)\n", fullHouseWorth);
        printf(" 3 -> Chance (%d points)\n> ", chanceWorth);
        choice1 = threeOfAKindWorth;
        choice2 = fullHouseWorth;
        choice3 = chanceWorth;
    } else if(threeOfAKindState == TRUE){ 
        printf(" 1 -> Three of a Kind (%d points)\n", threeOfAKindWorth);
        printf(" 2 -> Chance (%d points)\n> ", chanceWorth);
        choice1 = threeOfAKindWorth;
        choice2 = chanceWorth;
    } else if(straightState == TRUE){
        printf(" 1 -> Small Straight (%d points)\n", smallStraightWorth);
        printf(" 2 -> Straight (%d points)\n", straightWorth);
        printf(" 3 -> Chance (%d points)\n> ", chanceWorth); 
        choice1 = smallStraightWorth;
        choice2 = straightWorth;
        choice3 = chanceWorth;
    } else if(smallStraightState == TRUE){
        printf(" 1 -> Small Straight (%d points)\n", smallStraightWorth);
        printf(" 2 -> Chance (%d points)\n> ", chanceWorth); 
        choice1 = smallStraightWorth;
        choice2 = chanceWorth;
    } else{
        printf(" 1 -> Chance (%d points)\n> ", chanceWorth); 
        choice1 = chanceWorth;
    }

    //Receives input for choices into a string
    char input[NUM_OF_INPUTS] = {0};
    int i = 0;
    char newLineCounter = 0;
    while(newLineCounter != '\n' && i < NUM_OF_INPUTS){
        input[i] = getchar();
        newLineCounter = input[i];
        i ++;
    }
    int firstInteger = 0;
    while(input[firstInteger] == ' '){
        firstInteger ++;
    }

    //adds score according to the relevant case
    if(input[firstInteger] == '1'){
        if(choice1 == NONE){
            printf("\nInvalid Choice\n");
            score = FALSE;
        }
        if(score != FALSE){
            score = score + choice1;
        }
    } else if(input[firstInteger] == '2'){
        if(choice2 == NONE){
            printf("\nInvalid Choice\n");
            score = FALSE;
        }
        if(score != FALSE){
            score = score + choice2;
        }
    } else if(input[firstInteger] == '3'){
        if(choice3 == NONE){
            printf("\nInvalid Choice\n");
            score = FALSE;
        }
        if(score != FALSE){
            score = score + choice3;
        }
    } else if(input[firstInteger] == '4'){
        if(choice4 == NONE){
            printf("\nInvalid Choice\n");
            score = FALSE;
        }
        if(score != FALSE){
            score = score + choice4;
        }
    } else{
        printf("\nInvalid Choice\n");
        score = FALSE;
    }
    
    return score;
}

//Check for three of a kind combination
int threeOfAKind(int dice[]){
    
    int num = 1;
    int i = 0;
    int result = FALSE;
    int occurrence = 0;
    while(num <= 6){
        i = 0;
        occurrence = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == num){
                occurrence ++;
            }
            if(occurrence == 3){
                result = TRUE;
            }
            i ++;
        }
        num ++;
    }

    return result;
}

//Check for four of a kind combination
int fourOfAKind(int dice[]){
    
    int num = 1;
    int i = 0;
    int result = FALSE;
    int occurrence = 0;
    while(num <= 6){
        i = 0;
        occurrence = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == num){
                occurrence ++;
            }
            if(occurrence == 4){
               result = TRUE;
            }
            i ++;
        }
        num ++;
    }
    
    return result;
}

//Check for full house combination
int fullHouse(int dice[]){
    
    int num = 1;
    int i = 0;
    int result = FALSE;
    int tripleNum = FALSE;
    int doubleNum = FALSE;
    int occurrence = 0;
    //Check for triple
    while(num <= 6){
        i = 0;
        occurrence = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == num){
                occurrence ++;
            }
            i ++;
        }
        if(occurrence == 3){
            tripleNum = TRUE;
        }
        num ++;
    }
    //Check for double
    num = 1;
    i = 0;
    occurrence = 0;
    while(num <= 6){
        i = 0;
        occurrence = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == num){
                occurrence ++;
            }
            i ++;
        }
        if(occurrence == 2){
            doubleNum = TRUE;
        }
        num ++;
    }
    //Check for both triple and double
    if(tripleNum == TRUE && doubleNum == TRUE){
        result = TRUE;
    }

    return result;
}

//Check for small straight combination
int smallStraight(int dice[]){
    
    int result = FALSE;
    int min = 1;
    int a = 1;
    int i = 0;
    //Check for lowest number with consecutive numbers after it
    while(a < 6){
        i = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == min){
                int b = 0;
                while(b < NUM_OF_DICE){
                    if(dice[b] == (min + 1)){
                        i = NUM_OF_DICE;
                        a = 6;
                        min --;
                        b = NUM_OF_DICE;
                    }
                    b ++;
                }
            }
            i ++;
        }
        a ++;
        min ++;
    }
    //Checks for amount of consecutive numbers after lowest number
    i = 0;
    int occurrence = 1;
    while(i < NUM_OF_DICE){
        if(dice[i] == min + 1){
            min = dice[i];
            occurrence ++;
            i = -1;
        }
        i ++;
    }
    if(occurrence >= (NUM_OF_DICE - 1)){
        result = TRUE;
    }

    return result;
}

//Check for straight combination
int straight(int dice[]){
    
    int result = FALSE;
    int min = 1;
    int a = 1;
    int i = 0;
    //Finds the lowest number
    while(a < 6){
        i = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == min){
                i = NUM_OF_DICE;
                a = 6;
                min --;
            }
            i ++;
        }
        a ++;
        min ++;
    }
    //Finds the amount of consecutive numbers after the 'lowest number'
    i = 0;
    int occurrence = 1;
    while(i < NUM_OF_DICE){
        if(dice[i] == min + 1){
            min = dice[i];
            occurrence ++;
            i = -1;
        }
        i ++;
    }
    if(occurrence == NUM_OF_DICE){
        result = TRUE;
    }

    return result;
}

//Check for Yahtzee combination, i.e. five of the same number
int yahtzee(int dice[]){
    
    int num = 1;
    int i = 0;
    int result = FALSE;
    int occurrence = 0;
    while(num <= 6){
        i = 0;
        occurrence = 0;
        while(i < NUM_OF_DICE){
            if(dice[i] == num){
                occurrence ++;
            }
            if(occurrence == 5){
               result = TRUE;
            }
            i ++;
        }
        num ++;
    }

    return result;
}
