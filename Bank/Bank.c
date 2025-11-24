#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

typedef struct account_details
{
    char name[1024];
    int ID;
    int acc_type;
    int PIN;
    float Balance;
    int acc_no;
}acc_details;

void make_database()
{
    // Creates the files in Current working Directory
    char current_directory[1024];
    getcwd(current_directory, 1024); // Gets the current directory and stores the location in current_directory

    // Makes Database Directory in current directory
    char database_path[1024];
    strcpy(database_path, current_directory); // Copies the current directory location
    strcat(database_path, "/Database"); // Appends /Database to the end
    mkdir(database_path);  // Create database folder


    // Makes index.txt file - Same principles as database folder
    char Indexfile_path[1024];
    strcpy(Indexfile_path, database_path);
    strcat(Indexfile_path, "/Index.txt");

    FILE *indexptr;
    indexptr = fopen(Indexfile_path, "a");
    fclose(indexptr);

    // Makes transaction.log file
    char Transactionfile_path[1024];
    strcpy(Transactionfile_path, database_path);
    strcat(Transactionfile_path, "/Transaction.log");

    FILE *Transactionptr;
    Transactionptr = fopen(Transactionfile_path, "a");
    fclose(Transactionptr);
}



// Shows Session Info
void show_session_info()
{
    printf("\n\n          Session Info            \n");
    printf("------------------------------------\n");
    time_t timing = time(NULL);
    struct tm date = *localtime(&timing);

    // Count number of account by counting the number of lines in index.txt
    FILE *Indexptr = fopen("Database/Index.txt", "r");
    int acc_count = 0;

    if (Indexptr == NULL)
    {
        // File doesn't exist yet → no accounts
        acc_count = 0;
    }
    else
    {
        int newline;
        while ((newline = fgetc(Indexptr)) != EOF)
        {
            if (newline == '\n')
            acc_count++;
        }
        fclose(Indexptr);
    }

    printf("Date: %02d/%02d/%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900); // Prints the Current Date
    printf("Time: %02d:%02d:%02d\n", date.tm_hour, date.tm_min, date.tm_sec); // Prints the Current Time 
    printf("Loaded Account: %d\n", acc_count);

    printf("------------------------------------\n");
}


void Create()
{
    acc_details account;
    printf("\n      Creating New Bank Account       \n");
    printf("------------------------------------\n");
    // Name
    printf("Enter Name: ");
    while(getchar() != '\n');
    fgets(account.name, sizeof(account.name), stdin); // Takes Multi-line input from User
    account.name[strcspn(account.name, "\n")] = '\0'; //  Removes the newline character

    // ID
    while(1) // Infinite Loop that runs until the the ID is 4 digits numbers
    {
        printf("ID (4 digits Minimum): ");
        if(scanf("%d", &account.ID) == 1) // Checks if Input is Number 
        {
            if (account.ID > 1000) // Verifies the ID is atleast 4 digits and breaks the loop
            {
                break;
            }
            else // Otherwise prints to enter 4 digits and loop runs again
            {
                printf("Must be Atleast 4 digits\n");
            }
        } 
        else // Prints When input is not a number
        {
            printf("Invalid input. ID must be a number.\n");
        }
        while(getchar() != '\n');
    }

    // Account Type - Same logic as ID
     while(1) // Infinite Loop that runs until input is 1 or 2
    {
        printf("Account Type (1 - Saving, 2 - Current): ");
        if(scanf("%d", &account.acc_type) == 1) // Checks if Type is Number 
        {
            if (account.acc_type == 1 || account.acc_type == 2) // Verifies the Type is either 1 or 2 and breaks the loop
            {
                break;
            }
            else // Otherwise prints to enter 1 or 2 loop runs again
            {
                printf("Must be Only 1 or 2\n");
            }
        } 
        else // Prints When input is not a number
        {
            printf("Invalid input. Account Type must be a number.\n");
        }
        while(getchar() != '\n');
    }

    // Account PIN 
     while(1) // Infinite Loop that runs until PIN is exactly 4 digits
    {
        printf("PIN: ");
        if(scanf("%d", &account.PIN) == 1) // Checks if Type is Number 
        {
            if (account.PIN >= 1000 && account.PIN <= 9999 ) // Verifies the Pin is 4 digits;
            {
                break;
            }
            else // Otherwise prints to enter 1 or 2 loop runs again
            {
                printf("Must be Exactly 4 Digits\n");
            }
        } 
        else // Prints When PIN is not a number
        {
            printf("Invalid input. Account Type must be a number.\n");
        }
        while(getchar() != '\n');
    }

    account.Balance = 0.00; // Initial Account balance is always zero

    // Account Number Generator - HARDEST THING
    srand(time(NULL));

    // Opens Index File for
    char current_directory[1024];
    getcwd(current_directory, 1024);
    
    char Indexfile_path[1024];
    strcpy(Indexfile_path, current_directory);
    strcat(Indexfile_path, "/Database/Index.txt");

    int unique_acc = 0;

    FILE *Indexptr;
    while(!unique_acc)
    {
        account.acc_no = 1000000 + rand() % 9000000; // generate random number from 1000000 to 8999999 
        int existing_acc_no; // Varaible to store the account number in Index.txt
        unique_acc = 1;
        Indexptr = fopen(Indexfile_path, "r");

        while(fscanf(Indexptr, "%d", &existing_acc_no) == 1)
        {
            if (account.acc_no == existing_acc_no) // Checks if the generated account number is eqaul to the account numbers already in Index.txt
            {
                unique_acc = 0;
                break; // Breaks and generates a new number
            }
        }
        fclose(Indexptr);
    }

    // Append the Account Number to Index.txt
    char current_directory_append[1024];
    getcwd(current_directory_append, 1024);
    char Indexfile_append_path[1024];
    strcpy(Indexfile_append_path, current_directory_append);
    strcat(Indexfile_append_path, "/Database/Index.txt");

    FILE *Index_append_ptr;
    Index_append_ptr = fopen(Indexfile_path, "a");
    fprintf(Index_append_ptr, "%d\n", account.acc_no); // Writes the Number to the file
    fclose(Index_append_ptr);

    // Creates The Account.txtt file
    char current_directory_create[1024];
    getcwd(current_directory_create, 1024);
    char account_path[1024];
    strcpy(account_path, current_directory);
    sprintf(account_path, "Database/%d.txt", account.acc_no);
    FILE *account_file;
    account_file = fopen(account_path, "w");
    // Writes the account file
    fprintf(account_file, "%s\n", account.name);
    fprintf(account_file, "%d\n", account.ID);
    fprintf(account_file, "%d\n", account.PIN);
    fprintf(account_file, "%.3f\n", account.Balance);
    fprintf(account_file, "%d\n", account.acc_no);
    fclose(account_file);

    printf("------------------------------------\n");


    // Prints Account Details
    printf("\n          Account Created         \n");
    printf("------------------------------------\n");
    printf("Name: %s\n", account.name);
    printf("ID: %d\n", account.ID);
    printf("Account Type: %d\n", account.acc_type);
    printf("PIN: %d\n", account.PIN);
    printf("Balance: %.3f\n", account.Balance);
    printf("Account Number: %d\n", account.acc_no);
    printf("------------------------------------\n");
}

void Delete()
{
    printf("Deleting Bank Account\n");
}

void Deposit()
{
    printf("Depositing Money\n");
}

void Withdrawal()
{
    printf("Withdrawing Money\n");
}

void Remittance()
{
    printf("Remittance money\n");
}

// Records Transactions in transaction.log
void Transactionlog_update(const char *action)
{
    // Gets the current directory and stores the location in current_location
    char current_directory[1024];
    getcwd(current_directory, 1024);
    
    char Transactionfile_path[1024];
    strcpy(Transactionfile_path, current_directory);
    strcat(Transactionfile_path, "/Database/Transaction.log");

    FILE *Transactionptr;
    Transactionptr = fopen(Transactionfile_path, "a");
    fprintf(Transactionptr, "%s\n", action);
    fclose(Transactionptr);
}


// Acts as the main menu to take the the user input
void main_menu()
{
    char user_input[50]; // Array to store user input
    while(1) // Continously prompts user to take input until 'quit' or 6
    {
        show_session_info(); // Calls session_info Function here rather than main to show info everytime at the start

        printf("\n            Welcome To Bank         \n");
        printf("------------------------------------\n");

        // Prints all the options
        printf("Please Choose An Option (1-6) \n");
        printf("1. Create New Bank Account\n");
        printf("2. Delete Bank Account\n");
        printf("3. Deposit\n");
        printf("4. Withdrawal\n");
        printf("5. Remittance\n");
        printf("6. Quit\n");

        printf("------------------------------------\n");

        printf("Select Option: ");
        scanf("%s", user_input);

        
        // Bunch of conditional statement to check for user input
        if (strcmp(user_input, "create") == 0 || strcmp(user_input, "1") == 0) // checks for create
        {
            Transactionlog_update("Create");
            Create();
        }

        else if (strcmp(user_input, "delete") == 0 || strcmp(user_input, "2") == 0 ) // checks for delete
        {
            Transactionlog_update("Delete");
            Delete();
        }

        else if (strcmp(user_input, "deposit") == 0 || strcmp(user_input, "3") == 0 ) // checks for deposit
        {
            Transactionlog_update("Deposit");
            Deposit();
        }

        else if (strcmp(user_input, "withdrawal") == 0 || strcmp(user_input, "4") == 0 ) // checks for withdrawal
        {
            Transactionlog_update("Withdrawal");
            Withdrawal();
        }

         else if (strcmp(user_input, "remittance") == 0 || strcmp(user_input, "5") == 0 ) // checks for remittance
        {
            Transactionlog_update("Remittance");
            Remittance();
        }

        else if (strcmp(user_input, "quit")  == 0 || strcmp(user_input, "6")  == 0 ) // Checks for quit
        {
            Transactionlog_update("Quit");
            printf("Quitted Sucessfully\n"); // Closes so fast that lines never seems to be printed :(
            exit(0); // Exit the Program
        }

        else // If none of the cases matches
        {
            printf("Invalid Input. Please Try Again\n");
        }
    }
}


int main()
{
    // Call database Function
    make_database();

    // Call main_menu function
    main_menu();

    return 0;
}
