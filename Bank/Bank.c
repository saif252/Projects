#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
//#include <direct.h>


void database()
{
    char exe_path[1024];
    get_executable_directory(NULL, exe_path, 1024);

    // Makes Database Directory
    char database_path[1024];
    strcpy(database_path, exe_path);
    strcat(database_path, "/Database");
    mkdir(database_path, 0755);


    // Makes index.txt file
    char indexfile_path[1024];
    strcpy(indexfile_path, database_path);
    strcat(indexfile_path, "/index.txt");

    FILE *indexptr;
    indexptr = fopen(indexfile_path, "a");
    fclose(indexptr);

    // Makes transaction.log file
    char transactionfile_path[1024];
    strcpy(transactionfile_path, database_path);
    strcat(transactionfile_path, "/Transactranstion.log");

    FILE *transactionptr;
    transactionptr = fopen(transactionfile_path, "a");
    fclose(transactionptr);
}



// Shows Session Info
void show_session_info()
{
    printf("        Session Info        \n");
    printf("-------------------------------\n");
    time_t timing = time(NULL);
    struct tm date = *localtime(&timing);

    // Count number of account by counting the number of lines in index.txt
    FILE *indexptr;
    indexptr = fopen("Database/Index.txt", "r");
    int acc_count = 0;  // ------------------------- FIX THIS ISSUE------------------------------------
    int end = fgetc(indexptr); // Reads the line
    
    while (end != EOF) // Loops through the files until End of the file
    {
        if (end == '\n') // If Newline is found, then increment by 1
        {
            acc_count++;
        }
        end = fgetc(indexptr);
    }

    fclose(indexptr);

    printf("Date: %02d/%02d/%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900); // Prints the Current Date
    printf("Time: %02d:%02d:%02d\n", date.tm_hour, date.tm_min, date.tm_sec); // Prints the Current Time 
    printf("Loaded Account: %d\n", acc_count);

    printf("-------------------------------\n");
}

// Acts as the main menu to take the the user input
void main_menu()
{
    // Calls session_info Function here rather than main to show info everytime at the start
    show_session_info();

    printf("            Welcome To Bank         \n");
    printf("------------------------------------\n");





    printf("------------------------------------\n");
}

int main()
{
    // Call database Function
    database();

    // Call main_menu function
    main_menu();

    return 0;
}
