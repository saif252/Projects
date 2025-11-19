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

    char *moves[3] = {"rock", "paper", "scissors"};

    srand(time(0)); // seed random generator

    while (1)
    {
        printf("\nEnter rock, paper, scissors, stats, or stop: ");
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
        printf("Computer chose: %s\n", moves[computer]);

        // Determine outcome
        if (strcmp(player, moves[computer]) == 0 ||
            (strcmp(player, "scissor") == 0 && computer == 2)) {
            printf("Draw!\n");
            draw++;
        } else if ((strcmp(player, "rock") == 0 && computer == 2) ||
                   (strcmp(player, "paper") == 0 && computer == 0) ||
                   (strcmp(player, "scissors") == 0 && computer == 1) ||
                   (strcmp(player, "scissor") == 0 && computer == 1)) {
            printf("You win!\n");
            win++;
        } else if (strcmp(player, "rock") == 0 || strcmp(player, "paper") == 0 || 
                   strcmp(player, "scissors") == 0 || strcmp(player, "scissor") == 0) {
            printf("You lost :(\n");
            lost++;
        } else {
            printf("Invalid input! Try again.\n");
        }
    }

    return 0;
}
