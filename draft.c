#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

struct item
{
    int cost, quantity;
    char name[50];
};

// ALl functions:
void showbill(struct item items[], int counter);
void inventory();
int addItem(FILE *fp);
void strlower(char c[]);
int search(char name[]);
void store();
void list();
void pmode(char name[]);

int main()
{
    printf("********************************************\n************* BILLING SYSTEM ***************\n********************************************\n\n");
    int mode;
step1:
    pmode("Dashboard");
    printf("\n0 -> EXIT\n1 -> INVENTORY MODE\n2 -> BILLING MODE\n\nEnter Mode:");
    scanf("%d", &mode);
    system("clear");
    switch (mode)
    {
    case 1:
        inventory();
        break;
    case 2:
        store();
        return 0;
        break;
    case 0:
        return 1;
        break;
    default:
        break;
    }
    goto step1;
    return 0;
}

// INVENTORY MODE
void inventory()
{
    FILE *fp = fopen("shop.csv", "a");
    if (fp == NULL)
        printf("Could not open file");
    else
    {
    here:
        pmode("Inventory Mode");
        printf("0-> Exit\n1-> List Items\n2-> Add Items");
        printf("\n:");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            list();
            goto here;
        }
        else if (choice == 2)
        {
            /* code */

            int run = 0;
            while (run == 0)
            {
                fseek(fp, 0, SEEK_END);
                int size = ftell(fp);
                if (size == 0)
                {
                    printf("File is empty!!");
                   //file setup 
                    char setup[50] = "Product, Price/unit";
                    fputs(setup, fp);
                    fputs("\n", fp);
                }
                run = addItem(fp);
            }
            goto here;
        }
        else if (choice == 0)
        {
            goto there;
        }

        else
        {
            goto here;
        }
    there:
        system("clear");
        fclose(fp);
    }
}

// Add items to csv
int addItem(FILE *fp)
{
    char name[50];
    char price[50];
    printf("\nProduct name (Without space):");
    scanf("%s", name);
    if (strcmp(name, "0") == 0)
    {
        system("clear");
        return 1;
    }
    printf("Cost per unit (Rs):");
    scanf("%s", price);
    strcat(name, ",");
    strcat(name, price);
    strlower(name);
    fputs(name, fp);
    fputs("\n", fp);
    return 0;
}

// Lowercase a string
void strlower(char a[])
{
    int i;
    for (i = 0; i < 50; i++)
    {
        a[i] = tolower(a[i]);
    }
}

//Store or billing mode
void store()
{
    pmode("Billing Mode");
    FILE *fp = fopen("shop.csv", "a");
    printf("Enter 0 in product name when done\n");
    int counter = 0;
    struct item items[20];
    while (true)
    {
        printf("\n%d)Product Name: ", counter + 1);
        scanf("%s", &items[counter].name);
        if (strcmp(items[counter].name, "0") == 0)
        {
            break;
        }
        printf("Quantity: ");
        scanf("%d", &items[counter].quantity);
        strlower(items[counter].name);
        items[counter].cost = search(items[counter].name);
        if (items[counter].cost == 0)
        {
            printf("\nProduct not in inventory\nPlease add\n");
            addItem(fp);
            printf("\nPlease re-enter the product price:");
            scanf("%d", &items[counter].cost);
        }
        counter++;
    }
    showbill(items, counter);
}

// search in file and return
int search(char name[])
{
    int rate = 0;
    FILE *fp = fopen("shop.csv", "r");
    if (fp == NULL)
    {
        printf("Could not open file");
        return rate;
    }
    else
    {
        char buffer[200];
        while (feof(fp) != true)
        {
            fgets(buffer, 200, fp);
            // printf("Row: %s", buffer);
            char *token;
            token = strtok(buffer, ",");
            int col = 0;
            char product[50];
            char price[20];
            while (token != NULL)
            {
                col++;
                // printf("%s ", token);
                switch (col)
                {
                case 1:
                    strcpy(product, token);
                    break;
                case 2:
                    strcpy(price, token);
                    break;
                default:
                    continue;
                }
                if (strcmp(name, product) == 0)
                {
                    // printf("Found");
                    rate = atoi(price);
                }
                token = strtok(NULL, ",");
            }
        }
        return rate;
    }
}

//Print the bill
void showbill(struct item product[], int counter)
{
    system("clear");
    int total;
    printf("DBRAIT GENERAL STORE\n\tBILL");
    printf("\n________________________________");
    printf("\nItem\tRate\tQuantity  Price\n");
    printf("________________________________\n");
    for (int i = 0; i < counter; i++)
    {
        printf("%s \t %d \t %d \t %d\n", product[i].name, product[i].cost, product[i].quantity, product[i].cost * product[i].quantity);
        total += product[i].cost * product[i].quantity;
    }
    printf("________________________________");
    printf("\nTotal: %d Rs\n\n", total);
    printf("________________________________\n");
}

//list the content of csv
void list()
{
    FILE *fp = fopen("shop.csv", "r");
    if (fp == NULL)
    {
        printf("Could not open file");
    }
    else
    {
        char buffer[200];
        printf("\n");
        while (feof(fp) != true)
        {
            fgets(buffer, 200, fp);
            printf("%s", buffer);
        }
        printf("\n");
    }
}

//print mode name
void pmode(char name[])
{
    printf("**************************\n");
    printf("\t%s\n", name);
    printf("**************************\n");
}