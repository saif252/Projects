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
    scanf("%s", account.name);

    while (getchar() != '\n');
    printf("ID: ");
    scanf("%d", &account.ID);

    printf("Account Type: ");
    scanf("%d", &account.type);

    account.balance = 0.0;

    srand(time(NULL));
    account.acc_number = 1000000 + rand() % 9000000;


    printf("-----------------------------------\n");

    printf("            Account Information        \n");
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
            create();
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Create");
            fclose(transaction);
        }
        else if ( strcmp(input, "2") == 0 || strcmp(input, "delete") == 0 )
        {
            delete();
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Delete");
            fclose(transaction);
        }
        else if ( strcmp(input, "3") == 0 || strcmp(input, "deposit") == 0 )
        {
            deposit();
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Deposit");
            fclose(transaction);
        } 
        else if ( strcmp(input, "4") == 0 || strcmp(input, "withdraw") == 0 )
        {
            withdraw();
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Withdraw");
            fclose(transaction);
        } 
        else if ( strcmp(input, "5") == 0 || strcmp(input, "remittance") == 0 )
        {
            remittance();
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Remittance");
            fclose(transaction);
        }
        else if ( strcmp(input, "6") == 0 || strcmp(input, "quit") == 0 )
        {
            printf("Qitted Successfully\n");
            FILE *transaction = fopen("database/Transaction.log", "a");
            fprintf(transaction, "Quit");
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
