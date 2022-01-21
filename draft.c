#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// ALl functions:
void showbill(int a[], char **products, int counter);
void inventory();
void fileSetup(FILE *fp);
int addItem(FILE *fp);
void strlower(char c[]);
int search(char name[]);
void store();
//void makezero();

void main()
{
    printf("*******************************************\n************* BILLING SYSTEM *************\n********************************************\n");
    int mode;
step1:
    printf("\n0 -> EXIT\n1 -> INVENTORY MODE\n2 -> BILLING MODE\n\nEnter Mode:");
    scanf("%d", &mode);
    system("clear");
    if(mode == 1)
    {
        inventory();
    }
    else if (mode == 2)
    {
        store();
    }
   goto step1; 
}

// INVENTORY MODE

void inventory()
{
    FILE *fp = fopen("shop.csv", "a");
    if (fp == NULL)
        printf("Could not open file");
    else
    {
        int run = 0;
        while (run == 0)
        {
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);
            if (size == 0)
            {
                printf("File is empty!!");
                fileSetup(fp);
            }
            run = addItem(fp);
        }
        fclose(fp);
    }
}

// Initial CSV setup
void fileSetup(FILE *fp)
{
    char setup[50] = "Product, Price/unit";
    fputs(setup, fp);
    fputs("\n", fp);
}

// Add items to csv
int addItem(FILE *fp)
{
    char name[50];
    char price[50];
    printf("Product name (Without space):");
    scanf("%s", name);
    if (strcmp(name, "1") == 0)
    {
        return 1;
    }
    printf("\nCost per unit (Rs):");
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

void store()
{
    FILE *fp = fopen("shop.csv", "a");
    char productName[50];
    int quantity;
    int rate;
    int prices[10];
    char *products[50];
    int counter = 0;
    while (true)
    {
        printf("Product Name: ");
        scanf("%s", productName);
        if (strcmp(productName, "1") == 0)
        {
            break;
        }
        printf("Quantity: ");
        scanf("%d", &quantity);
        strlower(productName);
        rate = search(productName);
        if (rate == 0)
        {
            printf("Product not in inventory\nPlease add this in inventory");
            addItem(fp);
            rate = search(productName);
        }
        prices[counter] = rate;
        // strcpy(products[counter],productName);
        counter++;
        // printf("\nrate: %d Rs\nCost: %d Rs\n\n", rate, rate * quantity);
    }
    for (int i = 0; i < counter; i++)
    {
        printf("%s\t%d", products[i], prices[i]);
    }

    // showbill(prices, products, counter);
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
                    printf("Found");
                    rate = atoi(price);
                }
                token = strtok(NULL, ",");
            }
        }
        return rate;
    }
}

void showbill(int a[], char **products, int counter)
{
    int total;
    printf("________________________________");
    printf("Item\tPrice");
    for (int i = 0; i < counter; i++)
    {
        printf("%s  %d", products[i], a[i]);
        total += a[i];
    }
    printf("\nTotal: %d", total);
    printf("________________________________");
}

void makezero(int a[])
{
}
