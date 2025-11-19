#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// Account structure
typedef struct acc_details
{
    char name[50];
    int ID;
    int acc_number;
    int type;           // 1 for saving, 2 for current
    int PIN;
    float balance;
} details;

// Function to set up the database folder and files
void setup_database_folder()
{
    mkdir("database", 0755);

    char indexPath[] = "database/index.txt";
    char transactionPath[] = "database/Transaction.log";

    // Check if index file exists, create if not
    FILE *indexFile = fopen(indexPath, "r");
    if (indexFile == NULL) 
    {
        indexFile = fopen(indexPath, "w");
    }
    if (indexFile != NULL) 
    {
        fclose(indexFile);
    }

    // Same for transaction log
    FILE *transactionFile = fopen(transactionPath, "r");
    if (transactionFile == NULL) 
    {
        transactionFile = fopen(transactionPath, "w");
        if (transactionFile == NULL) {
            printf("Error creating %s\n", transactionPath);
            exit(0);
        }
    }
    if (transactionFile != NULL) 
    {
        fclose(transactionFile);
    }
}

void show_session_info()
{
    printf("        Session Information        \n");
    printf("-----------------------------------\n");

    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char date_str[20], time_str[20];

    strftime(date_str, sizeof(date_str), "%d-%m-%Y", time_info);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);

    // Count existing account files
    int account_count = 0;
    DIR *db_directory = opendir("database");
    
    if (db_directory != NULL) {
        struct dirent *entry;
        while ((entry = readdir(db_directory)) != NULL) 
        {
            // Look for .txt files but skip index.txt
            if (strstr(entry->d_name, ".txt") && strcmp(entry->d_name, "index.txt") != 0)
            {
                account_count++;
            }
        }
        closedir(db_directory);
    }

    printf("Date: %s\n", date_str);
    printf("Time: %s\n", time_str);
    printf("Loaded Accounts: %d\n", account_count);
    printf("-----------------------------------\n");
}

void create_new_account()
{
    details new_account;
    
    printf("\n");
    printf("        Creating New Account        \n");
    printf("-----------------------------------\n");
    printf("Enter Name: ");
    while (getchar() != '\n');  // Clear any leftover input
    fgets(new_account.name, sizeof(new_account.name), stdin);
    new_account.name[strcspn(new_account.name, "\n")] = '\0';  // Remove newline

    // ID validation - needs to be at least 4 digits
    int id_is_valid = 0;
    while (!id_is_valid)
    {
        printf("Enter ID (minimum 4 digits): ");
        if (scanf("%d", &new_account.ID) != 1)
        {
            printf("Invalid input. Please enter numbers only.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (new_account.ID >= 1000)
        {
            id_is_valid = 1;
        }
        else
        {
            printf("ID must be at least 4 digits long.\n");
        }
        while (getchar() != '\n'); 
    }

    // Account type validation
    int type_is_valid = 0;
    while (!type_is_valid)
    {
        printf("Account Type (1 = Savings, 2 = Current): ");
        if (scanf("%d", &new_account.type) != 1)
        {
            printf("Invalid input. Please enter numbers only.\n");
            while (getchar() != '\n');
            continue;
        }

        if (new_account.type == 1 || new_account.type == 2)
        {
            type_is_valid = 1;
        }
        else
        {
            printf("Account Type must be either 1 or 2.\n");
        }
    }

    // PIN validation - exactly 4 digits
    int pin_is_valid = 0;
    while (!pin_is_valid)
    {
        printf("Enter PIN (exactly 4 digits): ");
        if (scanf("%d", &new_account.PIN) != 1)
        {
            printf("Invalid input. Please enter numbers only.\n");
            while (getchar() != '\n');
            continue;
        }

        if (new_account.PIN >= 1000 && new_account.PIN <= 9999)
            pin_is_valid = 1;
        else
            printf("PIN must be exactly 4 digits\n");
    }

    // Start with zero balance
    new_account.balance = 0.0;

    // Generate unique account number - 7 digits
    srand(time(NULL));
    int account_num_unique = 0;
    FILE *indexFile;
    
    while (!account_num_unique)
    {
        new_account.acc_number = 1000000 + rand() % 9000000; 

        // Check if this number already exists
        indexFile = fopen("database/index.txt", "r");
        if (indexFile != NULL)
        {
            account_num_unique = 1; 
            int existing_acc_num;
            while (fscanf(indexFile, "%d", &existing_acc_num) == 1)
            {
                if (existing_acc_num == new_account.acc_number)
                {
                    account_num_unique = 0; // Duplicate found, try again
                    break;
                }
            }
            fclose(indexFile);
        }
        else
        {
            account_num_unique = 1; // File doesn't exist, so number is unique
        }
    }

    // Add account number to index
    indexFile = fopen("database/index.txt", "a");
    fprintf(indexFile, "%d\n", new_account.acc_number);
    fclose(indexFile);

    // Create individual account file
    char account_filename[100];
    sprintf(account_filename, "database/%d.txt", new_account.acc_number);

    FILE *account_file = fopen(account_filename, "w");
    if (account_file != NULL)
    {
        fprintf(account_file, "%s\n", new_account.name);
        fprintf(account_file, "%d\n", new_account.ID);
        fprintf(account_file, "%d\n", new_account.type);
        fprintf(account_file, "%d\n", new_account.PIN);
        fprintf(account_file, "%d\n", new_account.acc_number);
        fprintf(account_file, "%.2f\n", new_account.balance);
        fclose(account_file);
    }
    else
    {
        printf("Error: Could not create account file!\n");
        return;  // Exit function on error
    }

    // Display account info
    printf("\n");
    printf("-----------------------------------\n");
    printf("       Account Created Successfully       \n");
    printf("-----------------------------------\n");
    printf("Name: %s\n", new_account.name);
    printf("ID: %d\n", new_account.ID);
    printf("Account Type: %s\n", (new_account.type == 1) ? "Savings" : "Current");
    printf("Account Number: %d\n", new_account.acc_number);
    printf("Initial Balance: RM%.2f\n", new_account.balance);
    printf("-----------------------------------\n");
}

void delete_account()
{
    int existing_accounts[100];  // Array to store account numbers
    int total_accounts = 0;

    // Read all existing account numbers
    FILE *indexFile = fopen("database/index.txt", "r");
    if (indexFile == NULL) {
        printf("No accounts found.\n");
        return;
    }

    while (fscanf(indexFile, "%d", &existing_accounts[total_accounts]) == 1) {
        total_accounts++;
    }
    fclose(indexFile);

    if (total_accounts == 0) {
        printf("No accounts available to delete.\n");
        return;
    }

    // Show existing account numbers
    printf("\n      Existing Account Numbers       \n");
    printf("-----------------------------------------\n");
    int i;
    for (i = 0; i < total_accounts; i++) {
        printf("%d\n", existing_accounts[i]);
    }

    int account_to_remove;
    printf("Enter account number to delete: ");
    scanf("%d", &account_to_remove);

    // Check if account file exists
    char account_filename[100];
    sprintf(account_filename, "database/%d.txt", account_to_remove);

    FILE *account_file = fopen(account_filename, "r");
    if (!account_file) {
        printf("Error: Account number %d not found.\n", account_to_remove);
        return;
    }

    // Read account details for verification
    details account_info;
    fgets(account_info.name, sizeof(account_info.name), account_file);
    account_info.name[strcspn(account_info.name, "\n")] = '\0'; 

    fscanf(account_file, "%d", &account_info.ID);
    fscanf(account_file, "%d", &account_info.type);
    fscanf(account_file, "%d", &account_info.PIN);
    fscanf(account_file, "%d", &account_info.acc_number);
    fscanf(account_file, "%f", &account_info.balance);
    fclose(account_file);

    // Verify identity before deletion
    int entered_id;
    int entered_pin;
    printf("For security, enter last 4 digits of ID: ");
    scanf("%d", &entered_id);
    printf("Enter 4-digit PIN: ");
    scanf("%d", &entered_pin);

    // Check credentials
    if ((account_info.ID % 10000 != entered_id) || (account_info.PIN != entered_pin)) {
        printf("Incorrect ID or PIN. Account deletion cancelled.\n");
        return;
    }

    // Delete the account file
    if (remove(account_filename) == 0) 
    {
        printf("Account %d deleted successfully.\n", account_to_remove);
    } 
    else 
    {
        printf("Error: Could not delete account file.\n");
        return;
    }

    // Update index file (remove deleted account number)
    indexFile = fopen("database/index.txt", "w");
    for (i = 0; i < total_accounts; i++) {
        if (existing_accounts[i] != account_to_remove) {
            fprintf(indexFile, "%d\n", existing_accounts[i]);
        }
    }
    fclose(indexFile);

    printf("Account successfully removed from system.\n");
}

void make_deposit()
{
    details account_data;
    int user_pin;
    float deposit_amount;
    char account_filename[100];

    printf("\n        Money Deposit      \n");
    printf("-----------------------------\n");

    printf("Enter Account Number: ");
    scanf("%d", &account_data.acc_number);

    sprintf(account_filename, "database/%d.txt", account_data.acc_number);

    // Open and read account file
    FILE *file_ptr = fopen(account_filename, "r");
    if (!file_ptr)
    {
        printf("Account not found! Please check account number.\n");
        return;
    }

    // Read account details
    fscanf(file_ptr, "%[^\n]\n", account_data.name);      
    fscanf(file_ptr, "%d\n", &account_data.ID);          
    fscanf(file_ptr, "%d\n", &account_data.type);        
    fscanf(file_ptr, "%d\n", &account_data.PIN);         
    fscanf(file_ptr, "%d\n", &account_data.acc_number);  
    fscanf(file_ptr, "%f\n", &account_data.balance);     
    fclose(file_ptr);

    // Verify PIN
    printf("Enter your 4-digit PIN: ");
    scanf("%d", &user_pin);

    if (user_pin != account_data.PIN)
    {
        printf("Incorrect PIN! Access denied.\n");
        return;
    }

    // Get deposit amount
    printf("Enter deposit amount (RM): ");
    scanf("%f", &deposit_amount);

    // Validate deposit amount
    if (deposit_amount <= 0 || deposit_amount > 50000)
    {
        printf("Invalid amount. Must be greater than 0 and not exceed RM50,000.\n");
        return;
    }

    // Update balance
    account_data.balance += deposit_amount;

    // Write updated data back to file
    file_ptr = fopen(account_filename, "w");
    fprintf(file_ptr, "%s\n", account_data.name);
    fprintf(file_ptr, "%d\n", account_data.ID);
    fprintf(file_ptr, "%d\n", account_data.type);
    fprintf(file_ptr, "%d\n", account_data.PIN);
    fprintf(file_ptr, "%d\n", account_data.acc_number);
    fprintf(file_ptr, "%.2f\n", account_data.balance);
    fclose(file_ptr);

    printf("\nDeposit completed successfully!\n");
    printf("New Balance: RM%.2f\n", account_data.balance);
}

void make_withdrawal()
{
    // TODO: Implement withdrawal functionality
    printf("Withdrawal feature coming soon!\n");
}

void remittance()
{
    // TODO: Implement remittance functionality
    printf("Money transfer feature under development!\n");
}

void transactionlog (char *array)
{
    FILE *transaction_log = fopen("database/Transaction.log", "a");
    fprintf(transaction_log, "%s\n", array); // add newline
    fclose(transaction_log);
}

void display_main_menu()
{
    char user_input[10];
    
    while(1)  // Main program loop
    {
        printf("\n");
        printf("        Welcome To Our Bank     \n");
        printf("-----------------------------------\n");
        printf("Please Choose An Option:\n");
        printf("1. Create New Bank Account\n");
        printf("2. Delete Existing Account\n");
        printf("3. Make Deposit\n");
        printf("4. Make Withdrawal\n");
        printf("5. Remittance Abroad\n");
        printf("6. Exit System\n");
        printf("-----------------------------------\n");
        printf("\n");
        
        printf("Select Option: ");
        scanf("%s", user_input);

        // Handle user menu selection
        if( strcmp(user_input, "1") == 0 || strcmp(user_input, "create") == 0 )
        {
            // Log transaction
            transactionlog("Create");
            create_new_account();
        }
        else if ( strcmp(user_input, "2") == 0 || strcmp(user_input, "delete") == 0 )
        {
            transactionlog("Delete");
            delete_account();
        }
        else if ( strcmp(user_input, "3") == 0 || strcmp(user_input, "deposit") == 0 )
        {
            transactionlog("Deposit");
            make_deposit();
        } 
        else if ( strcmp(user_input, "4") == 0 || strcmp(user_input, "withdraw") == 0 )
        {
            transactionlog("Withdraw");
            make_withdrawal();
        } 
        else if ( strcmp(user_input, "5") == 0 || strcmp(user_input, "remittance") == 0 || strcmp(user_input, "transfer") == 0 )
        {
            transactionlog("Remittance");
            Remittance();
        }
        else if ( strcmp(user_input, "6") == 0 || strcmp(user_input, "quit") == 0 || strcmp(user_input, "exit") == 0 )
        {
            transactionlog("Quit");
            exit(0);
        }
        else 
        {
            printf("Invalid selection. Please try again.\n");
        }
    }
}

int main()
{
    // Initialize database and show session info
    setup_database_folder();
    show_session_info();
    
    // Start main menu
    display_main_menu();
    
    return 0;
}
