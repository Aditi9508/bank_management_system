#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store account details
struct Account {
    int acc_no;
    char name[100];
    float balance;
};

// Function prototypes
void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void display_all();

int main() {
    int choice;
    
    while(1) {
        printf("\n====================================");
        printf("\n    Central Union BANK");
        printf("\n====================================");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Display All Accounts");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: create_account(); break;
            case 2: deposit_money(); break;
            case 3: withdraw_money(); break;
            case 4: check_balance(); break;
            case 5: display_all(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice! Try again.");
        }
    }
    return 0;
}

void create_account() {
    FILE *fp = fopen("accounts.dat", "ab");
    struct Account acc;
    
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Name: ");
    getchar(); // to clear buffer
    gets(acc.name);
    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);
    
    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("\nAccount Created Successfully!");
}

void deposit_money() {
    int acc_no, found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb+");
    
    if (fp == NULL) {
        printf("\nFile Error!");
        return;
    }
    
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    
    while(fread(&acc, sizeof(struct Account), 1, fp)) {
        if(acc.acc_no == acc_no) {
            printf("\nCurrent Balance: %.2f", acc.balance);
            printf("\nEnter Amount to Deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            
            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            printf("\nDeposit Successful!");
            found = 1;
            break;
        }
    }
    
    if(!found) printf("\nAccount Not Found!");
    fclose(fp);
}

void withdraw_money() {
    int acc_no, found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb+");
    
    if (fp == NULL) return;
    
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    
    while(fread(&acc, sizeof(struct Account), 1, fp)) {
        if(acc.acc_no == acc_no) {
            printf("\nCurrent Balance: %.2f", acc.balance);
            printf("\nEnter Amount to Withdraw: ");
            scanf("%f", &amount);
            
            if(amount > acc.balance) {
                printf("\nInsufficient Funds!");
            } else {
                acc.balance -= amount;
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("\nWithdrawal Successful!");
            }
            found = 1;
            break;
        }
    }
    
    if(!found) printf("\nAccount Not Found!");
    fclose(fp);
}

void check_balance() {
    int acc_no, found = 0;
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");
    
    if (fp == NULL) return;
    
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    
    while(fread(&acc, sizeof(struct Account), 1, fp)) {
        if(acc.acc_no == acc_no) {
            printf("\nAccount Holder: %s", acc.name);
            printf("\nCurrent Balance: %.2f", acc.balance);
            found = 1;
            break;
        }
    }
    
    if(!found) printf("\nAccount Not Found!");
    fclose(fp);
}

void display_all() {
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");
    
    if (fp == NULL) return;
    
    printf("\n--- ALL ACCOUNTS ---");
    printf("\nACC NO | NAME             | BALANCE");
    printf("\n----------------------------------");
    
    while(fread(&acc, sizeof(struct Account), 1, fp)) {
        printf("\n%-6d | %-16s | %.2f", acc.acc_no, acc.name, acc.balance);
    }
    
    fclose(fp);
}

