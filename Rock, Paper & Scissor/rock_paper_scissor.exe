#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    char player[50];
    int computer;
    int win = 0, lost = 0, draw = 0;
    int total_games = 0;

    srand(time(0)); // seed random number generator

    while (1)
    {
        printf("\nEnter rock, paper, scissor, stats, or stop: ");
        scanf("%s", player);

        // Stop game
        if (strcmp(player, "stop") == 0)
        {
            printf("Game stopped.\n");
            break;
        }

        // Show stats
        if (strcmp(player, "stats") == 0)
        {
            total_games = win + lost + draw;
            float win_percentage = (total_games > 0) ? ((float)win / total_games) * 100 : 0;
            printf("\n----- GAME STATS -----\n");
            printf("Wins: %d\n", win);
            printf("Losses: %d\n", lost);
            printf("Draws: %d\n", draw);
            printf("Total games: %d\n", total_games);
            printf("Win rate: %.2f%%\n", win_percentage);
            printf("----------------------\n");
            continue;
        }

        // Generate computer choice
        computer = rand() % 3;

        // Show computer's move
        if (computer == 0) printf("Computer chose: rock\n");
        else if (computer == 1) printf("Computer chose: paper\n");
        else printf("Computer chose: scissor\n");

        // Compare outcomes
        if (strcmp(player, "rock") == 0)
        {
            if (computer == 0) 
            {
                printf("Draw!\n"); 
                draw++; 
            }
            else if (computer == 1) 
            { 
                printf("You lost :(\n"); 
                lost++; 
            }
            else 
            { 
                printf("You win!\n"); 
                win++; 
            }
        }
        else if (strcmp(player, "paper") == 0)
        {
            if (computer == 1) 
            { printf("Draw!\n"); draw++; }
            else if (computer == 2) 
            { 
                printf("You lost :(\n"); 
                lost++; 
            }
            else 
            { 
                printf("You win!\n"); 
                win++; 
            }
        }
        else if (strcmp(player, "scissor") == 0)
        {
            if (computer == 2) 
            { 
                printf("Draw!\n"); 
                draw++; 
            }
            else if (computer == 0) 
            { 
                printf("You lost :(\n"); 
                lost++; 
            }
            else 
            { 
                printf("You win!\n"); 
                win++; 
            }
        }
        else
        {
            printf("Invalid input! Try again.\n");
        }
    }

    return 0;
}
