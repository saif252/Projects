#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

// Stores the imp information about the Account 
typedef struct account_details
{
    char name[1024];
    int ID;
    int acc_type; // 1 - Saving, 2 - Current // Should have used enum but really used to enums for now,
    int PIN;
    float Balance;
    int acc_no;
}acc_details;

// Utility Function to get location of current Directory 
char *current_working_directory()
{
    static char current_directory[1024]; // To store the current directory location
    getcwd(current_directory, 1024); // Gets the current directory and stores the location in current_directory
    return current_directory;
}

// Utility Function to build path easily
void path_builder(char *Store, const char *file_open)
{
    snprintf(Store, 1024, "%s/Database/%s", current_working_directory(), file_open);
}

void clear_input() {
    int clear;
    while ((clear = getchar()) != '\n' && clear != EOF);
}

// Makes Database Folder, Index.txt and Transaction.log
void make_database()
{
    char current_directory[1024];
     strcpy(current_directory, current_working_directory()); // Location of current Directory

    // Makes Database Directory in current directory
    char database_path[1024];
    snprintf(database_path, sizeof(database_path), "%s/Database", current_working_directory()); // current_working_directory/Database ----> database_path
    mkdir(database_path);  // Create database folder


    // Makes index.txt file - Same thing as database folder
    char Indexfile_path[1024];
    path_builder(Indexfile_path, "Index.txt");

    FILE *indexptr;
    indexptr = fopen(Indexfile_path, "a");
    fclose(indexptr);

    // Makes transaction.log file
    char Transactionfile_path[1024];
    path_builder(Transactionfile_path, "Transaction.log");

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
    char index_path[1024];
    path_builder(index_path, "Index.txt");

    // Open Index.txt and counts
    FILE *Indexptr = fopen(index_path, "r");
    int acc_count = 0;
    if (Indexptr == NULL)
    {
        // File doesn't exist yet, then no accounts
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
    }
    fclose(Indexptr);

    // Prints the Session Information
    printf("Date: %02d/%02d/%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900); // Prints the Current Date
    printf("Time: %02d:%02d:%02d\n", date.tm_hour, date.tm_min, date.tm_sec); // Prints the Current Time 
    printf("Loaded Account: %d\n", acc_count);

    printf("------------------------------------\n");
}

// Records Transactions in transaction.log
void Transactionlog_update(const char *action)
{
    // Gets the current directory and stores the location in current_location
    char current_directory[1024];
    strcpy(current_directory, current_working_directory());
    
    char Transactionfile_path[1024];
    path_builder(Transactionfile_path, "Transaction.log");

    FILE *Transactionptr;
    Transactionptr = fopen(Transactionfile_path, "a");
    fprintf(Transactionptr, "%s\n", action);
    fclose(Transactionptr);
}

// Creates New bank Account
void Create()
{
    acc_details account;
    printf("\n      Creating New Bank Account       \n");
    printf("------------------------------------\n");

    // Name
    int name_valid = 0;
    while(!name_valid)
    {
        printf("Enter Name: ");
        fgets(account.name, sizeof(account.name), stdin); // Takes input from User even spaces
        account.name[strcspn(account.name, "\n")] = '\0'; //  Removes the newline character
        if (strlen(account.name) > 0 && strspn(account.name, " ") != strlen(account.name)) // checks the length of name to ensure it has atleast one character and not white spaces
        {
            name_valid = 1;
        }
        else
        {
            printf("Cant be NULL Character\n");
        }
    } 
    

    // ID
    int user_ID[50];
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
                printf("Must > 1000\n");
            }
        } 
        else // Prints When input is not a number
        {
            printf("Invalid input. ID must be a number.\n");
        }
        clear_input();
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
        clear_input();
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
                printf("Must > 1000 and < 9999\n");
            }
        } 
        else // Prints When PIN is not a number
        {
            printf("Invalid input. PIN must be a number.\n");
        }
        clear_input();
    }

    account.Balance = 0.00; // Initial Account balance is always zero

    // Account Number Generator - HARDEST THING
    // Opens Index File for
    char Indexfile_path[1024];
    path_builder(Indexfile_path, "Index.txt");

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
    char current_directory[1024]; 
    strcpy(current_directory, current_working_directory());

    FILE *Index_append_ptr;
    Index_append_ptr = fopen(Indexfile_path, "a");
    fprintf(Index_append_ptr, "%d\n", account.acc_no); // Writes the Number to the file
    fclose(Index_append_ptr);


    char account_path[1024];
    sprintf(account_path, "%s/Database/%d.txt", current_directory, account.acc_no);

    FILE *account_file;
    account_file = fopen(account_path, "w");
    // Writes the account file
    fprintf(account_file, "%s\n", account.name);
    fprintf(account_file, "%d\n", account.ID);
    fprintf(account_file, "%d\n", account.acc_type);
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

int valid_PIN(const char *account_no)
{
    acc_details account;
    char Account_path[1024];
    snprintf(Account_path, 1024, "%s/Database/%s.txt", current_working_directory() ,account_no);

    FILE *accountfile;
    accountfile = fopen(Account_path, "r");
    

    fgets(account.name, sizeof(account.name), accountfile);  // read full name line
    fscanf(accountfile, "%d", &account.ID);
    fscanf(accountfile, "%d", &account.acc_type);
    fscanf(accountfile, "%d", &account.PIN);
    fscanf(accountfile, "%f", &account.Balance);
    fscanf(accountfile, "%d", &account.acc_no);

    fclose(accountfile);

    int user_PIN;
    while(1)
    {
        printf("PIN: ");
        
        if (scanf("%d", &user_PIN) == 1) // Checks the PIN is Integer
        {
            if (user_PIN >= 1000 && user_PIN <= 9999) // Ensures the input is 4 digits
            {
                if (user_PIN == account.PIN) // If the 4 digits of input and account ID matches, breaks the inifinte loop
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
                printf("Must 4 digits\n");
            }
        }
        else
        {
            printf("Must Numbers\n");
        }
        clear_input();
    }
    return user_PIN;
}

// Delete Existing Bank Account
void Delete()
{
    printf("\n      Deleting Bank Account       \n");
    printf("------------------------------------\n");

    printf("        Existing Account:\n");

    // Gets Current Directory address to access Index.txt
    char current_directory[1024];
    strcpy(current_directory, current_working_directory());

    // Open Index.txt
    char Indexfile_read_path[1024];
    path_builder(Indexfile_read_path, "Index.txt");
    
    char file_end[16]; // Reads the File for end
    char existing_account[1024][16]; // 2D array to store 1024 Accounts of 7 Characters + Null terminator
    int account_count = 0; 

    FILE *index_read_ptr;
    index_read_ptr = fopen(Indexfile_read_path, "r");

    // Loop to Read and Display all the current Acccount
    while (fgets(file_end, sizeof(file_end), index_read_ptr) != NULL) // Runs until the Files is empty
    {
        file_end[strcspn(file_end, "\n")] = 0; // Removes the newline Character
        strcpy(existing_account[account_count], file_end);
        printf("%d. %s\n", account_count + 1, existing_account[account_count]);
        account_count++;
    }
    fclose(index_read_ptr);
    printf("------------------------------------\n");
    
    int account_found = 0;
    char account_delete[16];
    while (!account_found)
    {
        printf("Please Select Account to delete: ");
        scanf("%15s", account_delete);

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
        clear_input();
    }


    // Open the Account file for Verifications- ID & PIN
    char Accountfile_path[1024];
    sprintf(Accountfile_path, "%s/Database/%s.txt", current_directory, account_delete);
    
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

    // Checks the Last 4 digits of the ID
    int user_ID;
    int last4_ID = account_info.ID % 10000; // Temporary Hold and Extracts the last 4 digits. 1234567 % 10000 ----> 4567

    while(1)
    {
        printf("ID (Last 4 Digits): ");
        
        if (scanf("%d", &user_ID) == 1) // Checks the ID is Integer
        {
            if (user_ID >= 1000 && user_ID <= 9999) // Ensures the input is 4 digits
            {
                if (user_ID == last4_ID) // If the 4 digits of input and account ID matches, breaks the inifinte loop
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
                printf("Must last 4 digits\n");
            }
        }
        else
        {
            printf("Must Numbers\n");
        }
        clear_input();
    }

    // Checks the PIN - Same as ID but just changed the name and less hassle
    int user_PIN = valid_PIN(account_delete);

    // Delete the Account File
    if (remove(Accountfile_path) == 0) 
    {
        printf("------Account %s deleted--------\n", account_delete);
    } 
    else 
    {
        printf("----------Could not delete account file.--------\n");
        return;
    }

    // Remove from Index.txt
    char Indexfile_delete_path[1024];
    path_builder(Indexfile_delete_path, "Index.txt");

    FILE *index_delete;
    index_delete = fopen(Indexfile_delete_path, "w"); // Oveerwrites all the existing account

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

// Depositing Money. Quite Similar to Delete function (Copied and Pasted, just better variable name)
void Deposit()
{
    acc_details account_info;

    // Copied from Delete Function to Display the Existing Accounts
    printf("\n              Deposit             \n");
    printf("------------------------------------\n");

    printf("        Existing Account:           \n");

    // Gets Current Directory address to access Index.txt
    char current_directory[1024];
    strcpy(current_directory, current_working_directory());

    // Open Index.txt
    char Indexfile_read_path[1024];
    path_builder(Indexfile_read_path, "Index.txt");
    
    char file_end[16]; // Reads the File for end
    char existing_account[1024][16]; // 2D array to store 1024 Accounts of 7 Characters + Null terminator
    int account_count = 0;

    FILE *index_read_ptr;
    index_read_ptr = fopen(Indexfile_read_path, "r");

    // Loop to Read and Display all the current Acccount
    while (fgets(file_end, sizeof(file_end), index_read_ptr) != NULL) // Runs until the Files is empty
    {
        file_end[strcspn(file_end, "\n")] = 0; // Removes the newline Character
        strcpy(existing_account[account_count], file_end);
        printf("%d. %s\n", account_count + 1, existing_account[account_count]);
        account_count++;
    }
    fclose(index_read_ptr);
    printf("------------------------------------\n");

    int account_found = 0;
    char account_deposit[16];
    while (!account_found)
    {
        printf("Please Select Account to Deposit: ");
        scanf("%15s", account_deposit);

        for (int i = 0; i < account_count; i++) // Compares all the exisiting_account array
        {
            if (strcmp(account_deposit, existing_account[i]) == 0) // If the account matches; breaks
            {
                account_found = 1;
            }
        }
        if (!account_found) // If didnt find account in existing_account array
        {
            printf("Account Not Found\n");
        }
        clear_input();
    }

    // Read the Account File
    char accountpath[1024];
    snprintf(accountpath, 1024, "%s/Database/%s.txt", current_directory, account_deposit);

    FILE *account;
    account = fopen(accountpath, "r");
    fgets(account_info.name, sizeof(account_info.name), account);
account_info.name[strcspn(account_info.name, "\n")] = '\0';
    fscanf(account, "%d", &account_info.ID);
    fscanf(account, "%d", &account_info.acc_type);
    fscanf(account, "%d", &account_info.PIN);
    fscanf(account, "%f", &account_info.Balance);
    fscanf(account, "%d", &account_info.acc_no);
    fclose(account);

    // Open the Account file for Verifications- PIN
    int user_PIN = valid_PIN(account_deposit);

    //Takes the input for Balance
    int amount_valid = 0;
    float amount_deposit;
    while (!amount_valid)
    {
        printf("Enter Amount to Deposit: ");
        if (scanf("%f", &amount_deposit) == 1) // Checks if the input is numberes or character
        {   
            if (amount_deposit > 0) // Ensures the number is positve
            {
                if (amount_deposit > 0 && amount_deposit <= 50000) // Verifies the amount is between 0-50000
                {
                    amount_valid = 1;
                }
                else
                {
                    printf("Amount Must be > 0 and <= 50000\n");
                }
            }
            else
            {
                printf("Amount Can't be Negative\n");
            }
        }
        else
        {
            printf("Amount Must be Numbers\n");
        }
        clear_input();
    }
    
    account_info.Balance += amount_deposit; // Adds the current balance and amount entered by user 

    // Open the Account File
    char account_path[1024];
    snprintf(account_path, sizeof(account_path),"%s/Database/%s.txt", current_directory, account_deposit);  // account_deposit contains the account number string

    FILE *account_file;
    account_file = fopen(account_path, "w"); // Overwrites all the data

    fprintf(account_file, "%s\n", account_info.name);
    fprintf(account_file, "%d\n", account_info.ID);
    fprintf(account_file, "%d\n", account_info.acc_type);
    fprintf(account_file, "%d\n", account_info.PIN);
    fprintf(account_file, "%.3f\n", account_info.Balance);
    fprintf(account_file, "%d\n", account_info.acc_no);

    fclose(account_file);
    printf("\n--------Deposited Money-----------\n");
    printf("New Balance: %.3f", account_info.Balance);
}

// Withdraw Money
void Withdrawal()
{
    acc_details account_info;

    printf("\n      Withdrawing Money       \n");
    printf("--------------------------------\n");
    // Show Existing Account
    printf("        Existing Account:       \n");
    // Gets Current Directory address to access Index.txt
    char current_directory[1024];
    strcpy(current_directory, current_working_directory());

    // Open Index.txt
    char Indexfile_read_path[1024];
    path_builder(Indexfile_read_path, "Index.txt");
    
    char file_end[16]; // Reads the File for end
    char existing_account[1024][16]; // 2D array to store 1024 Accounts of 7 Characters + Null terminator
    int account_count = 0;

    FILE *index_ptr;
    index_ptr = fopen(Indexfile_read_path, "r");

    // Loop to Read and Display all the current Acccount
    while (fgets(file_end, sizeof(file_end), index_ptr) != NULL) // Runs until the Files is empty
    {
        file_end[strcspn(file_end, "\n")] = 0; // Removes the newline Character
        strcpy(existing_account[account_count], file_end);
        printf("%d. %s\n", account_count + 1, existing_account[account_count]);
        account_count++;
    }
    fclose(index_ptr);
    printf("--------------------------------\n");

    // Continue Prompt to Enter Correct Account
    int account_found = 0;
    char account_withdraw[16];
    while (!account_found)
    {
        printf("Please Select Account to Withdraw: ");
        scanf("%15s", account_withdraw);

        for (int i = 0; i < account_count; i++) // Compares all the exisiting_account array
        {
            if (strcmp(account_withdraw, existing_account[i]) == 0) // If the account matches; breaks
            {
                account_found = 1;
            }
        }
        if (!account_found) // If didnt find account in existing_account array
        {
            printf("Account Not Found\n");
        }
        clear_input();
    }
    char accountpath[1024];
    snprintf(accountpath, 1024, "%s/Database/%s.txt", current_directory, account_withdraw);

    FILE *account;
    account = fopen(accountpath, "r");
    fgets(account_info.name, sizeof(account_info.name), account);
account_info.name[strcspn(account_info.name, "\n")] = '\0';
    fscanf(account, "%d", &account_info.ID);
    fscanf(account, "%d", &account_info.acc_type);
    fscanf(account, "%d", &account_info.PIN);
    fscanf(account, "%f", &account_info.Balance);
    fscanf(account, "%d", &account_info.acc_no);
    fclose(account);

    // Validate PIN
    int user_PIN = valid_PIN(account_withdraw);
    printf("--------------------------------\n");
    printf("Available Balance: %.3f\n", account_info.Balance);// Show Balance
    printf("--------------------------------\n");

    // Loop to Ensure the amount is valid and has enough money to withdraw
    int amount_valid = 0;
    float amount_withdraw;
    while(!amount_valid)
    {
        printf("Enter Amount to Withdraw: ");
        if (scanf("%f", &amount_withdraw) == 1)
        {
            if (amount_withdraw > 0) // Valid the amount cant be negative
            {
                if (amount_withdraw <= account_info.Balance) // Ensures the amount to withdraw is than the account balance
                {
                    amount_valid = 1;
                }
                else
                {
                    printf("Not Enough Balance\n");
                }
            }
            else
            {
                printf("Amount Can't be Negative\n");
            }
            
        }
        else
        {
            printf("Enter Numbers\n");
        }
        clear_input();
    }
    account_info.Balance -= amount_withdraw;

    // Write Back to the Account File
    // Open the Account File
    char account_path[1024];
    snprintf(account_path, sizeof(account_path),"%s/Database/%s.txt", current_directory, account_withdraw);  // account_deposit contains the account number string

    FILE *account_file;
    account_file = fopen(account_path, "w"); // Overwrites all the data

    fprintf(account_file, "%s\n", account_info.name);
    fprintf(account_file, "%d\n", account_info.ID);
    fprintf(account_file, "%d\n", account_info.acc_type);
    fprintf(account_file, "%d\n", account_info.PIN);
    fprintf(account_file, "%.3f\n", account_info.Balance);
    fprintf(account_file, "%d\n", account_info.acc_no);

    fclose(account_file);
    printf("\n--------Withdrawed Money-----------\n");
    printf("New Balance: %.3f", account_info.Balance);
}

void Remittance()
{
    acc_details sender_info;
    acc_details reciever_info;

    printf("\n            Remittance        \n");
    printf("--------------------------------\n");
    printf("Select Sender Account: \n");

    char current_directory[1024];
    strcpy(current_directory, current_working_directory());

    /* Read all accounts from Index.txt */
    char Indexfile_read_path[1024];
    path_builder(Indexfile_read_path, "Index.txt");

    char line[32];
    char existing_account[1024][16];
    int account_count = 0;

    FILE *index_ptr = fopen(Indexfile_read_path, "r");
    if (!index_ptr)
    {
        printf("ERROR: Cannot open Index.txt\n");
        return;
    }

    while (fgets(line, sizeof(line), index_ptr) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        strcpy(existing_account[account_count], line);
        printf("%d. %s\n", account_count + 1, existing_account[account_count]);
        account_count++;
    }
    fclose(index_ptr);

    printf("--------------------------------\n");

    /// CHoose sender acc
    char sender_account[16];
    int account_found = 0;

    while (!account_found)
    {
        printf("Please Select Sender Account: ");
        scanf("%15s", sender_account);

        for (int i = 0; i < account_count; i++)
        {
            if (strcmp(sender_account, existing_account[i]) == 0)
            {
                account_found = 1;
                break;
            }
        }
        if (!account_found)
            printf("Account Not Found\n");

        clear_input();
    }

    // Read sender acc
    char sender_path[1024];
    snprintf(sender_path, 1024, "%s/Database/%s.txt", current_directory, sender_account);

    FILE *fp_sender = fopen(sender_path, "r");
    if (!fp_sender)
    {
        printf("ERROR: Cannot open sender account file!\n");
        return;
    }

    fgets(sender_info.name, sizeof(sender_info.name), fp_sender);
    sender_info.name[strcspn(sender_info.name, "\n")] = 0;

    fscanf(fp_sender, "%d", &sender_info.ID);
    fscanf(fp_sender, "%d", &sender_info.acc_type);
    fscanf(fp_sender, "%d", &sender_info.PIN);
    fscanf(fp_sender, "%f", &sender_info.Balance);
    fscanf(fp_sender, "%d", &sender_info.acc_no);

    fclose(fp_sender);

    // Validate PIN 
    valid_PIN(sender_account);

    printf("--------------------------------\n");
    printf("Available Balance: %.3f\n", sender_info.Balance);
    printf("--------------------------------\n");

    // Choose reciever account
    char reciever_account[16];
    account_found = 0;

    while (!account_found)
    {
        printf("Please Select Receiver Account: ");
        scanf("%15s", reciever_account);

        if (strcmp(sender_account, reciever_account) == 0)
        {
            printf("ERROR: Sender and Receiver cannot be the same.\n");
            clear_input();
            continue;
        }

        for (int i = 0; i < account_count; i++)
        {
            if (strcmp(reciever_account, existing_account[i]) == 0)
            {
                account_found = 1;
                break;
            }
        }

        if (!account_found)
            printf("Account Not Found\n");

        clear_input();
    }

    // Read receiver account data 
    char receiver_path[1024];
    snprintf(receiver_path, 1024, "%s/Database/%s.txt", current_directory, reciever_account);

    FILE *fp_receiver = fopen(receiver_path, "r");
    if (!fp_receiver)
    {
        printf("ERROR: Cannot open receiver account file!\n");
        return;
    }

    fgets(reciever_info.name, sizeof(reciever_info.name), fp_receiver);
    reciever_info.name[strcspn(reciever_info.name, "\n")] = 0;

    fscanf(fp_receiver, "%d", &reciever_info.ID);
    fscanf(fp_receiver, "%d", &reciever_info.acc_type);
    fscanf(fp_receiver, "%d", &reciever_info.PIN);
    fscanf(fp_receiver, "%f", &reciever_info.Balance);
    fscanf(fp_receiver, "%d", &reciever_info.acc_no);

    fclose(fp_receiver);

   
    // AMOUNT VALIDATION
    float amount, total_deduction;

    while (1)
    {
        printf("Enter Amount to Send: ");
        if (scanf("%f", &amount) != 1)
        {
            printf("Enter Numbers Only.\n");
            clear_input();
            continue;
        }

        if (amount <= 0)
        {
            printf("Amount must be positive.\n");
            continue;
        }

        // Fee calc
        if (sender_info.acc_type == 1 && reciever_info.acc_type == 2)
            total_deduction = amount * 1.02; // Saving → Current = 2%
        else if (sender_info.acc_type == 2 && reciever_info.acc_type == 1)
            total_deduction = amount * 1.03; // Current → Saving = 3%
        else
            total_deduction = amount;        // Same type = no fee

        if (total_deduction > sender_info.Balance)
        {
            printf("Not Enough Balance. Required: %.3f, Available: %.3f\n",
                   total_deduction, sender_info.Balance);
        }
        else
        {
            break; // Valid
        }

        clear_input();
    }

    // Fee deduct
    sender_info.Balance -= total_deduction;
    reciever_info.Balance += amount;

    // Write sender acc
    fp_sender = fopen(sender_path, "w");
    fprintf(fp_sender, "%s\n", sender_info.name);
    fprintf(fp_sender, "%d\n", sender_info.ID);
    fprintf(fp_sender, "%d\n", sender_info.acc_type);
    fprintf(fp_sender, "%d\n", sender_info.PIN);
    fprintf(fp_sender, "%.3f\n", sender_info.Balance);
    fprintf(fp_sender, "%d\n", sender_info.acc_no);
    fclose(fp_sender);

    // Write reciever acc
    fp_receiver = fopen(receiver_path, "w");
    fprintf(fp_receiver, "%s\n", reciever_info.name);
    fprintf(fp_receiver, "%d\n", reciever_info.ID);
    fprintf(fp_receiver, "%d\n", reciever_info.acc_type);
    fprintf(fp_receiver, "%d\n", reciever_info.PIN);
    fprintf(fp_receiver, "%.3f\n", reciever_info.Balance);
    fprintf(fp_receiver, "%d\n", reciever_info.acc_no);
    fclose(fp_receiver);

    // Print information
    printf("--------------------------------\n");
    printf("       Transfer Successful\n");
    printf("--------------------------------\n");
    printf("Sender: %s (Acc: %d)\nBalance: %.3f\n",
           sender_info.name, sender_info.acc_no, sender_info.Balance);

    printf("Receiver: %s (Acc: %d)\nBalance: %.3f\n",
           reciever_info.name, reciever_info.acc_no, reciever_info.Balance);
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
        scanf("%49s", user_input);
        clear_input();

        
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
            printf("Quitted Sucessfully\n"); 
            fflush(stdout);
            exit(0); // Exit the Program
        }

        else // If none of the cases matches
        {
            printf("Invalid Input. Please Try Again\n");
        }
    }
    clear_input();
}


int main()
{
    srand(time(NULL));

    // Call database Function
    make_database();

    // Call main_menu function
    main_menu();

    return 0;
}
