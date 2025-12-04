# Overview of the Program

This program is a **console-based banking management system written in C for windows**.

All account data is saved locally inside a folder called **Database**, and each account has its own file.

The program uses **Index.txt** to store a list of existing account numbers and **Transaction.log** to track actions performed.



When the program starts, it automatically:

* Creates a Database folder (if not already present)
* Creates **Index.txt** and **Transaction.log** (if not already present)
* Displays **Session Information** (date, time, number of accounts)



### How to Navigate the Program

* The user only needs to type simple commands in **lowercase**(1–6 or names like “deposit”, “create”).
* Incorrect inputs are handled with warnings.
* After each operation, the program automatically returns to the main menu.

The session information (date, time, number of accounts) appears before each menu.



### How the Interface Works

Every time the main menu appears, the user sees:

Please Choose An Option (1–6)

1\. Create New Bank Account

2\. Delete Bank Account

3\. Deposit

4\. Withdrawal

5\. Remittance

6\. Quit



The user can type either the **number** or the **name** of the option in all **lowercase** (e.g., “1” or “create”).



### Explanation of Each Menu Option

##### 1\. Create New Bank Account

Allows the user to register a **new account**.



Steps:

* Enter name (can be name with spaces) 
* Enter ID (Must be greater than 1000)
* Choose account type (1 = Savings, 2 = Current)
* Set 4-digit PIN (Must be greater than 1000 and Less than 9999)
* System generates a unique account number
* Account is stored in /Database/<acc\_no>.txt
* Account number is added to Index.txt



##### 2\. Delete Bank Account

**Deletes** an **existing** account after verifying credentials.



Steps:

* Program displays all account numbers
* User selects which account to delete
* User enters last 4 digits of ID for security
* User enters 4-digit PIN for confirmation
* Account file is removed
* Index.txt is updated to remove the account number



##### 3\. Deposit

Adds **money** to an **existing account.**



Steps:

* Program lists accounts
* User selects the target account
* User enters the correct PIN
* Enter deposit amount (must be **0–50,000**)
* New balance is updated and stored





##### 4\. Withdrawal

Removes **money** from an **existing account**.



Steps:

* User selects an account from the displayed list
* Enter PIN to verify identity
* System shows the current balance
* User enters withdrawal amount (must be **less than or equal** to **current balance**)
* Program subtracts the amount and updates the file





##### 5\. Remittance

Transfers **money** from one **account to another**.



Steps:

* Select sender account
* Enter sender PIN
* Enter transfer amount
* Select receiver account (cannot be the same as sender)
* System applies transfer **charges** depending on **account types** (Saving → Current and Current → Saving)
* Deducts from sender and adds to receiver
* Updates both account files





##### 6\. Quit

Closes the program.

The program also writes **"Quit"** to **Transaction.log** before exiting.


