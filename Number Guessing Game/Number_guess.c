#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() 
{
    srand(time(0));
    int randomNumber = (rand() % 100) + 1;
    printf("Random number between 1 and 100: %d\n", randomNumber);

    int guess;
    int no_guess = 0;


    while(1)
    {
        printf("Enter the number: ");
        scanf("%d", &guess);
        if (guess <1 || guess > 100)
        {
            printf("Invalid Input. Input Number between 1 - 100\n");
            continue;
        }

        no_guess += 1;
        printf("This was %d guess\n", no_guess);

        if (guess == randomNumber)
        {
            printf("Congrats!! Guess correct in %d%s tries\n", no_guess, no_guess == 1 ? "st": no_guess == 2 ? "nd": no_guess == 3 ? "rd": "th" );
            break;
        }
        else if (guess > randomNumber)
        {
            printf("Number is lower\n");
        }
        else 
        {
            printf("Number is higher\n");
        }
    }
    
    
    return 0;
}
