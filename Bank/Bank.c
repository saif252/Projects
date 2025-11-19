#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

typedef struct acc_details
{
    char name[50];
    int ID;
    int acc_number;
    int type;
    int PIN;
    float balance;
} details;



void folder()
{
    mkdir("database", 0755);

    char indexPath[] = "database/index.txt";
    char transactionPath[] = "database/Transaction.log";

    FILE *indexFile = fopen(indexPath, "r");
    if (indexFile == NULL) 
    {
        indexFile = fopen(indexPath, "w");
        if (indexFile == NULL) {
            printf("Error creating %s\n", indexPath);
        }
    }
    if (indexFile != NULL) fclose(indexFile);

    FILE *transactionFile = fopen(transactionPath, "r");
    if (transactionFile == NULL) 
    {
        transactionFile = fopen(transactionPath, "w");
        if (transactionFile == NULL) {
            printf("Error creating %s\n", transactionPath);
        }
    }
    if (transactionFile != NULL) fclose(transactionFile);
}


void session_info()
{
    printf("        Session Info        \n");
    printf("-----------------------------------\n");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[20], time_str[20];

    strftime(date, sizeof(date), "%d-%m-%Y", t);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", t);

    int acc_count = 0;
    DIR *dir = opendir("database");
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {
        if (strstr(entry->d_name, ".txt") && strcmp(entry->d_name, "index.txt") != 0)
        {
            acc_count++;
        }
    }
    closedir(dir);

    printf("Date: %s\n", date);
    printf("Time: %s\n", time_str);
    printf("Loaded Account: %d\n", acc_count);

    printf("-----------------------------------\n");
}

void create()
{
    details account;

    printf("\n");
    printf("        Creating Account        \n");
    printf("-----------------------------------\n");
    printf("Name: ");
    while (getchar() != '\n');
    fgets(account.name, sizeof(account.name), stdin);
    account.name[strcspn(account.name, "\n")] = '\0';

    int valid_ID = 0;
    while (valid_ID != 1)
    {
        printf("ID (Digits): ");
        if (scanf("%d", &account.ID) != 1)
        {
            printf("Invalid input. Numbers only.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        valid_ID = 1;
    }

    
    int valid_Type = 0;
    while (!valid_Type)
    {
        printf("Account Type (1 = Saving, 2 = Current): ");
        if (scanf("%d", &account.type) != 1)
        {
            printf("Invalid input. Numbers only.\n");
            while (getchar() != '\n');
            continue;
        }

    if (account.type == 1 || account.type == 2)
    {
        valid_Type = 1;
    }
    else
    {
        printf("Account Type must be 1 or 2.\n");
    }
    }

    int valid_PIN = 0;
    while (!valid_PIN)
    {
        printf("PIN (4 digits): ");
        if (scanf("%d", &account.PIN) != 1)
        {
            printf("Invalid input. Numbers only.\n");
            while (getchar() != '\n');
            continue;
        }

        if (account.PIN >= 1000 && account.PIN <= 9999)
        valid_PIN = 1;
        else
        printf("PIN must be exactly 4 digits.\n");
    }

    account.balance = 0.0;

    srand(time(NULL));
    account.acc_number = 1000000 + rand() % 9000000;

    printf("\n");
    printf("-----------------------------------\n");
    printf("       Account Information        \n");
    printf("-----------------------------------\n");
    printf("Name: %s\n", account.name);
    printf("ID: %d\n", account.ID);
    printf("Account Type: %d\n", account.type);
    printf("Account Number: %d\n", account.acc_number);
    printf("Balance: %.2f\n", account.balance);
    printf("-----------------------------------\n");

}

void delete()
{

}

void deposit()
{

}

void withdraw()
{

}

void remittance()
{
    
}

void menu()
{
    char input[10];
    
    while(1)
    {
        printf("\n");
        printf("        Welcome To Bank     \n");
        printf("-----------------------------------\n");
        printf("Please Choose An Option\n");
        printf("1. Create New Bank Account\n");
        printf("2. Delete Bank Account \n");
        printf("3. Deposit\n");
        printf("4. Withdrawal\n");
        printf("5. Remittance\n");
        printf("6. Quit\n");
        printf("-----------------------------------\n");
        printf("\n");
        
        printf("Select Option: ");
        scanf("%s", input);

        if( strcmp(input, "1") == 0 || strcmp(input, "create") == 0 )
        {
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Create\n");
            fclose(transaction);
            create();
        }
        else if ( strcmp(input, "2") == 0 || strcmp(input, "delete") == 0 )
        {
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Delete\n");
            fclose(transaction);
            delete();
        }
        else if ( strcmp(input, "3") == 0 || strcmp(input, "deposit") == 0 )
        {
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Deposit\n");
            fclose(transaction);
            deposit();
        } 
        else if ( strcmp(input, "4") == 0 || strcmp(input, "withdraw") == 0 )
        {
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Withdraw\n");
            fclose(transaction);
            withdraw();
        } 
        else if ( strcmp(input, "5") == 0 || strcmp(input, "remittance") == 0 )
        {
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Remittance\n");
            fclose(transaction);
            remittance();
        }
        else if ( strcmp(input, "6") == 0 || strcmp(input, "quit") == 0 )
        {
            printf("Qitted Successfully\n");
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Quit\n");
            fclose(transaction);
            exit(0);
        }
        else 
        {
            printf("Invalid Input\n");
        }
    }
}

int main()
{
    folder();
    session_info();
    menu();
    return 0;
}
