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
    printf("\n      Deleting Bank Account       \n");
    printf("------------------------------------\n");

    printf("        Existing Account:\n");

    // Gets Current Directory address to access Index.txt
    char current_directory_read[1024];
    getcwd(current_directory_read, 1024);

    // Open Index.txt
    char Indexfile_read_path[1024];
    strcpy(Indexfile_read_path, current_directory_read);
    strcat(Indexfile_read_path, "/Database/Index.txt");
    
    char file_end[1024]; // Reads the File for end
    char existing_account[1024][8]; // 2D array to store 1024 Accounts of 7 Characters + Null terminator
    int account_count = 0; // Numberes the Accounts (1. XXXXXXX)

    FILE *index_read_ptr;
    index_read_ptr = fopen(Indexfile_read_path, "r");

    // Loop to Read and Display all the current Acccount
    while (fgets(file_end, 1024, index_read_ptr) != NULL) // Runs until the Files is empty
    {
        file_end[strcspn(file_end, "\n")] = 0; // Removes the newline Character
        strcpy(existing_account[account_count], file_end);
        printf("%d. %s\n", account_count + 1, existing_account[account_count]);
        account_count++;
    }
    fclose(index_read_ptr);
    printf("------------------------------------\n");
    
    int account_found = 0;
    char account_delete[10];
    while (!account_found)
    {
        printf("Please Select Account to delete: ");
        scanf("%s", account_delete);

        for (int i = 0; i < account_count; i++) // Compares all the exisiting_account array
        {
            if (strcmp(account_delete, existing_account[i]) == 0) // If the account matches; breaks
            {
                account_found = 1;
            }
        }
        if (!account_found) // If didnt find account in existing_account array
        {
            printf("Account Not Found\n");
        }
    }

    // Gets Current Directory address to access account.txt
    char current_directory_delete[1024];
    getcwd(current_directory_delete, 1024);

    // Open the Account file for Verifications- ID & PIN
    char Accountfile_path[1024];
    strcpy(Accountfile_path, current_directory_read);
    sprintf(Accountfile_path, "%s/Database/%s.txt", current_directory_delete, account_delete);
    
    FILE *accountfile;
    accountfile = fopen(Accountfile_path, "r");

    acc_details account_info;
    fgets(account_info.name, 1024, accountfile); // reads the names of the account name
    account_info.name[strcspn(account_info.name, "\n")] = '\0'; // Removes the newline character

    // Reads information the Account Files and Stores in struct
    fscanf(accountfile, "%d", &account_info.ID);
    fscanf(accountfile, "%d", &account_info.acc_type);
    fscanf(accountfile, "%d", &account_info.PIN);
    fscanf(accountfile, "%f", &account_info.Balance);
    fscanf(accountfile, "%d", &account_info.acc_no);
    fclose(accountfile);

    account_info.ID = account_info.ID % 10000; // Extracts the last 4 digits. 1234567 % 10000 ----> 4567
    // Checks the Last 4 digits of the ID
    int user_ID;
    while(1)
    {
        printf("ID (Last 4 Digits): ");
        
        if (scanf("%d", &user_ID) == 1) // Checks the ID is Integer
        {
            if (user_ID >= 1000 && user_ID <= 9999) // Ensures the input is 4 digits
            {
                if (user_ID == account_info.ID) // If the 4 digits of input and account ID matches, breaks the inifinte loop
                {
                    break;
                }
                else
                {
                    printf("Invalid ID\n");
                }
            }
            else
            {
                int clear;
                while ((clear = getchar()) != '\n' && clear != EOF); //Remove Characters 
                printf("Must 4 digits\n");
            }
        }
        else
        {
            int clear;
            while ((clear = getchar()) != '\n' && clear != EOF); //Remove Characters 
            printf("Must Numbers\n");
        }
    }

    // Checks the PIN - Same as ID but just changed the name and less hassle
    int user_PIN;
    while(1)
    {
        printf("PIN: ");
        
        if (scanf("%d", &user_PIN) == 1) // Checks the PIN is Integer
        {
            if (user_PIN >= 1000 && user_PIN <= 9999) // Ensures the input is 4 digits
            {
                if (user_PIN == account_info.PIN) // If the 4 digits of input and account ID matches, breaks the inifinte loop
                {
                    break;
                }
                else
                {
                    printf("Invalid PIN\n");
                }
            }
            else
            {
                int clear;
                while ((clear = getchar()) != '\n' && clear != EOF); //Remove Characters 
                printf("Must 4 digits\n");
            }
        }
        else
        {
            int clear;
            while ((clear = getchar()) != '\n' && clear != EOF); //Remove Characters 
            printf("Must Numbers\n");
        }
    }

    // Delete the Account File
    if (remove(Accountfile_path) == 0) 
    {
        printf("Account %s deleted\n", account_delete);
    } 
    else 
    {
        printf("Error: Could not delete account file.\n");
        return;
    }

    // Remove from Index.txt
    char Indexfile_delete_path[1024];
    strcpy(Indexfile_delete_path, current_directory_read);
    strcat(Indexfile_delete_path, "/Database/Index.txt");
    FILE *index_delete;
    index_delete = fopen("database/index.txt", "w"); // Oveerwrites all the existing account

    // For loop checks to write all accounts except the account deleted
    for (int i = 0; i < account_count; i++) 
    {
        if (strcmp(existing_account[i], account_delete) != 0) // if the account to to be deleted and existing account acounts are different, writes back to index
        {
            fprintf(index_delete, "%s\n", existing_account[i]);
        }
    }

    fclose(index_delete);
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

    // Creates the file location for transaction.log
    char Transactionfile_path[1024];
    strcpy(Transactionfile_path, current_directory);
    strcat(Transactionfile_path, "/Database/Transaction.log");

    // Open Transraction.log and updates it
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
