#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct account_details {
    int acc_number;
    char name[50];
    int acc_type;  
    float balance;
} details;

void Create() 
{
    printf("Creating a new account\n");
}

void Delete() 
{
    printf("Deleting account\n");
}

void Deposit() 
{
    printf("Processing deposit\n");
}

void Withdrawal() 
{
    printf("withdrawal\n");
}

void Remittance() 
{
    printf(" remittance\n");
}


void menu() 
{
    char choice[10];
    details my_account; 
    details *acc_ptr = &my_account;

    do {
        printf("\n          Welcome to Bank            \n");
        printf("----------------------------------------------\n");
        printf("1. Create New Bank Account\n");
        printf("2. Delete Bank Account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Remittance\n");
        printf("6. Quit\n");
        printf("----------------------------------------------\n");

        printf("Select Option: ");
        scanf("%s", choice);  

        

        if (strcmp(choice, "1") == 0 || strcasecmp(choice, "create") == 0) 
        {
            Create();
        }
        else if (strcmp(choice, "2") == 0 || strcasecmp(choice, "delete") == 0) {
            Delete();
        }
        else if (strcmp(choice, "3") == 0 || strcasecmp(choice, "deposit") == 0) {
            Deposit();
        }
        else if (strcmp(choice, "4") == 0 || strcasecmp(choice, "withdraw") == 0) {
            Withdrawal();
        }
        else if (strcmp(choice, "5") == 0 || strcasecmp(choice, "remittance") == 0) {
            Remittance();
        }
        else if (strcmp(choice, "6") == 0 || strcasecmp(choice, "quit") == 0) {
            printf("Quitted Successfully!\n");
            break;
        }
        else {
            printf("Invalid Option\n");
        }


    } while (strcmp(choice, "6") != 0 && strcasecmp(choice, "quit") != 0);
}

int main() {
    menu();
    return 0;
}
