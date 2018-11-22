#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define DEBUG 0

struct item
{
    char UPC[14]; // UPC stands for Universal Product Code
    char name[31];
    int quantity;
    float price;
    char company[21];
    int capacities;
};

struct available
{
    int valid;
    char foundUPC[14];
    int quantity;
};

void welcome();
int userAuthen();
void add();
void manage();
void view();
void display(struct item[], int);
void removeItem(struct item[], int);
void distribute(struct item[], int);
void addquantity(struct item[], int);
int isValidInt(char []);
int isValidName(char []);
int isValidFloat(char []);
int check_capacity();
struct available getAvailable(struct item[],char [], int);
void putInStorage(struct item[], char [], char [], int, int, int);
int MAXCAPACITIES = 5000;


int main()
{
    welcome();
    userAuthen();
    getchar();
    do
    {
        system("cls");
        char menu[10];
        char choice;
        printf("\n==============================================================");
        printf("\nMAIN MENU: Add, Manage, View, Setting, Exit [A/M/V/S/Q]: ");
        gets(menu);
        if (strlen(menu) == 1)
        {
            choice = menu[0];
            switch (toupper(choice))
            {
                case 'A':
                    add();
                    break;
                case 'M' :
                    manage();
                    break;
                case 'V' :
                    view();
                    break;
                case 'S' :
                    printf("Welcome to Setting function\nComing Soon!\n\npress any key to continue.\n");
                    getchar();
                    fflush(stdin);
                    break;
                case 'Q' :
                    exit(1);
                default:
                {
                    fflush(stdin);
                    printf("Error : Menu is wrong\n");
                }
            }
        }
        else
            printf("Invalid!\n");

    }while (1);
}

void welcome() {
    int i;
    printf("|||||||||||||||||||||||||||||||||||||||||||||\n");
    for (i = 0; i < 2; i++) printf("||                                         ||\n");
    printf("||              Welcome to                 ||\n");
    printf("||    Warehouse Management System V1.0     ||\n");
    for (i = 0; i < 2; i++) printf("||                                         ||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||\n");
}

int userAuthen()
{
    int count = 3;
    char inPassword[6];
    char password[6] = "12345"; //set password here
    do
    {
        printf("\t%d attempt(s) left.\n", count);
        printf("\tEnter Password:");

        scanf("%6s", &inPassword[0]);
        int lenInPass = strlen(inPassword);
//        printf("%d\n", lenInPass);
        int lenPass = strlen(password);

        if (strlen(inPassword) <= 5)
        {
            for (int i = 0; i < strlen(inPassword); ++i)
            {
                if(inPassword[i] != password[i])
                {
                    lenInPass--;
                }
            }
        }
        if (lenInPass == lenPass)
        {
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>> ACCESS GRANTED <<<<<<<<<<<<<<<<<<<<<<<<\n");
            return 1;
        }
        count--;
        fflush(stdin); //clear input buffer
        printf("Error! : Password incorrect.\n");
        printf("----------------------------\n");
    } while (count > 0);
    exit(1);
}
int check_capacity()
{
    FILE *cap;
    int now_capacity;
    cap = fopen("stock.txt", "r");
    fscanf(cap, "%d", &now_capacity);
    fclose(cap);
    return now_capacity;
}
void add()
{
    // data loading
    FILE *database;
    struct item newProduct;
    struct item productList[20001];
    database = fopen("main_warehouse.csv", "r");

    int i = 0;
    int totalProductList;
    char buffer[100];
    fscanf(database,"%s\n",buffer);
    while(fscanf(database,"%[^,],%[^,],%d,%f,%[^,],%d\n",newProduct.UPC,newProduct.name,&newProduct.quantity,
                 &newProduct.price,newProduct.company, &newProduct.capacities) == 6)
    {
        productList[i++] = newProduct;
    }
    totalProductList = i;
    fclose(database);
    // end of the data loading section and start the main program

    printf(">> ADD PRODUCT FUNCTION\n");
    FILE *inFile;
    inFile = fopen("main_warehouse.csv", "a");

//    if (inFile != NULL)
//        printf("File open successfully.\n");
    struct item newItem;
    while (1)
    {
        char tempUPC[14];
        printf("Universal Product Code: ");
        gets(tempUPC);
        if (strlen(tempUPC) == 13 && isValidInt(tempUPC))
        {
            int count;
//            printf("pass\n");
            for (count = 0 ; count < totalProductList; count++)
            {
                if (strcmp(productList[count].UPC, tempUPC) != 0)
                {
                    strcpy(newItem.UPC, tempUPC);
//                    printf("pass");
//                    printf("temp UPC = %s\n", tempUPC);
//                    printf("item UPC = %s\n", newItem.UPC);
                }
                else
                {
                    printf("Error! : Product duplication detected.\n");
                    return;
                }
            }
            break;
        }
        else printf("Error! : Invalid data.\nUniversal Product code contains only 13-digit numbers.\n\n");
    }
    while (1)
    {
        char tempName[31];
        printf("Product Name: ");
        gets(tempName);
        if (strlen(tempName) <= 30 && isValidName(tempName))
        {
            strcpy(newItem.name, tempName);
            break;
        }
        else printf("Error! : Invalid name.\nProduct's name contains only 30 characters and not allow to use ',' and '\"'\n\n");
    }
    while (1)
    {
        char tempquantity[20];
        printf("Quantity: ");
        gets(tempquantity);
        if (isValidInt(tempquantity) == 1)
        {
            newItem.quantity = atoi(tempquantity);
            break;
        }
        else printf("Error! : Invalid Data.\nQuantity must be positive integer.\n\n");
    }
    while (1)
    {
        char tempPrice[10];
        printf("Selling price: ");
        gets(tempPrice);
        if (isValidFloat(tempPrice) == 1)
        {
            newItem.price = atof(tempPrice);
            break;
        }
        else printf("Error! : Invalid Data.\nPrice must be positive single-precision number.\n\n");
    }

    while (1)
    {
        char tempcompany[21];
        printf("Name of manufacturing company:");
        gets(tempcompany);
        if (strlen(tempcompany) <= 20 && isValidName(tempcompany))
        {
            strcpy(newItem.company, tempcompany);
            break;
        }
        else printf("Error! : Invalid name.\nProduct's name contains only 30 characters and not allow to use ',' and '\"'\n\n");
    }

    while (1)
    {
        char tempcap[5];
        char choice, choice1;
        int currentCap;
        printf("capacities per unit: ");
        gets(tempcap);
        if (isValidInt(tempcap) == 1)
        {
            newItem.capacities = atoi(tempcap);
            if (((newItem.capacities * newItem.quantity)+check_capacity()) <= MAXCAPACITIES)
            {
//                printf("cap using = %d previous cap = %d\n", newItem.capacities*newItem.quantity,check_capacity());
                system("cls");
                printf("\nProduct Summary\n=============\n");
                printf("UPC : %s\n", newItem.UPC);
                printf("Product name :  %s\n", newItem.name);
                printf("Quantity : %d\n", newItem.quantity);
                printf("Selling Price : %.2f\n", newItem.price);
                printf("Manufacturer : %s\n", newItem.company);
                printf("=============\nDo you want to save? [Y/N] : ");
                choice1 = getchar();
                getchar();
                choice1 = toupper(choice1);
                if (choice1 == 'Y')
                {
                    fprintf(inFile, "%s,%s,%d,%.3f,%s,%d\n", newItem.UPC, newItem.name, newItem.quantity,
                            newItem.price, newItem.company, newItem.capacities);
                    currentCap = (newItem.capacities * newItem.quantity)+check_capacity();
                    FILE *capfile;
                    capfile = fopen("stock.txt", "w");
                    fprintf(capfile, "%d",currentCap);
                    fclose(capfile);
                    break;
                }
                else if (choice1 == 'N') break;
                else printf("unknown");
            }

            else
            {
                printf("Error! : Capacity is full.\n");
                printf("Do you want to edit?\nAnswer : Yes, No [Y/N]:");
                choice = getchar();
                getchar();
                switch (toupper(choice))
                {
                    case 'Y' :
                    {
                        continue;
                    }
                    case 'N' :
                    {
                        printf("Navigate you to main menu.\n");
                        break;
                    }
                }
                break;
            }
        }
    }
    fclose(inFile);
}

int isValidInt(char inp[])
{
    int i, valid = TRUE;

    if (inp[0] == '\0')
        valid = FALSE;

    if(valid == TRUE)
        for (i = 0; i < strlen(inp); i++)
            if (inp[i] < '0' || inp[i] > '9')
                valid = FALSE;
    return valid;
}

int isValidName(char inp[])
{
    int i, valid = TRUE;

    if (inp[0] == '\0')
        valid = FALSE;

    for (i = 0; i < strlen(inp); i++)
        if (inp[i] == ',' || inp[i] == '"') valid = FALSE;
    return valid;
}

int isValidFloat(char inp[])
{
    int i, valid = TRUE;

    if (inp[0] == '\0' || inp[0] == '0')
        valid = FALSE;

    for (i = 0; i < strlen(inp); i++)
    {
        if (inp[i] < '0' || inp[i] > '9')
        {
            if (inp[i] != '.') valid = FALSE;
        }
    }
    return valid;
}
void manage()
{
    // data loading
    FILE *database;
    struct item newProduct;
    struct item productList[10001];
    database = fopen("main_warehouse.csv", "r");

    int i = 0;
    int totalProductList;
    char buffer[100];
    fscanf(database,"%s\n",buffer);
    while(fscanf(database,"%[^,],%[^,],%d,%f,%[^,],%d\n",newProduct.UPC,newProduct.name,&newProduct.quantity,
                 &newProduct.price,newProduct.company, &newProduct.capacities) == 6)
    {
        productList[i++] = newProduct;
    }
    totalProductList = i;
    fclose(database);
    // end of the data loading section and start the main program

//    for (int z = 0; z < totalProductList; ++z) {
//        printf("%s\n", productList[z].UPC);
//    }

    char optMenu[10], choice;
    printf(">> MANAGEMENT OPTION: Remove Item(R), Distribute Item(D), Add Quantity(A): ");
    gets(optMenu);
    printf("\n");
    if (strlen(optMenu) == 1)
    {
        choice = optMenu[0];
        switch (toupper(choice))
        {
            case 'R' :
            {
                removeItem(productList, totalProductList);
                break;
            }
            case 'D' :
            {
                distribute(productList, totalProductList);
                printf("Distribute");
                break;
            }
            case 'A' :
            {
                addquantity(productList, totalProductList);
                break;
            }
            default:{
                printf("unknown");
                break;
            }
        }
    }
    else
        printf("Error! : Invalid Data\n");


}

void removeItem(struct item list[], int total)
{
    printf(">> REMOVE FUNCTION\n");
    char nameInp[31];
    int i,j,k;
    printf("Enter Product's UPC :");
    gets(nameInp);
    if (isValidName(nameInp) == 1)
    {
        for (i = 0; i < total; i++)
        {
            if (strcmp(list[i].UPC, nameInp) == 0)
            {
//                printf("item match\n");
                for (j = i; j < total; j++)
                {
                    list[j] = list[j+1];
//                    printf("now %d = %s\n", j,list[j].UPC);
                }
                int x;
                FILE *database;
                char header[] = "UPC,name,quantity,price,company,capacities\n";
                database = fopen("main_warehouse.csv", "w");
                fputs(header, database);
                for (x = 0; x < total-1; x++)
                    fprintf(database, "%s,%s,%d,%.3f,%s,%d\n", list[x].UPC, list[x].name, list[x].quantity,
                            list[x].price, list[x].company, list[x].capacities);
                fclose(database);

            }


        }
        printf("Message : Delete Success\n");
    }
    printf("Error! : Invalid Input.\n\n\nPress any key to continue...\n\n");
//    for (k = 0; k < total; k++)
//    {
//        printf("%s\n", list[k].UPC);
//    }
}

struct available getAvailable(struct item list[], char input[], int total)
{
    int j, valid = FALSE, quantity;
    char found[14];
    for (j = 0; j < total; j++)
    {
//        printf("%s\n",list[j].UPC);
        if (strcmp(list[j].UPC,input) == 0)
        {
            valid = TRUE;
            strcpy(found, list[j].UPC);
            quantity = list[j].quantity;
        }
    }

    struct available result;
    result.valid = valid;
    strcpy(result.foundUPC, found);
    result.quantity = quantity;
    return (result);
};

void distribute(struct item list[], int total)
{
    char inp[14], quantity[7];
    int q;
    printf(">> DISTRIBUTE FUNCTION\n");
    printf("Enter Product's UPC :");
    gets(inp);
    struct available result;
    result = getAvailable(list,inp,total);
    if (result.valid == 0)
    {
        printf("Error! : Item not found\n");
        return;
    }
    printf("Quantity in stock : %d\n", result.quantity);
    printf("Distribute quantity :");
    gets(quantity);
    if(isValidInt(inp) == 1 & isValidInt(quantity) == 1)
    {
        q = atoi(quantity);
        if ((result.quantity - q) < 0)
        {
            printf("Error! : You only have %d unit(s).", result.quantity);
            return;
        }
        printf("Select target warehouse:\n");
        printf("\t1. Chiang Mai\t\tWarehouse.\n\t2. Nakorn Ratchasrima\tWarehouse.\n\t"
                       "3. Ubon Ratchathani\tWarehouse.\n\t4. Rayong\t\tWarehouse.\n\t5. Songkhla\t\tWarehouse.\n");
        char choice[20], menu;
        gets(choice);
        if (strlen(choice) == 1)
        {
            menu = choice[0];
            switch (menu)
            {
                case '1' :
                {
                    printf("Distribute to ... Chiang Mai.\n");
                    char fileName[] = "chiangmai_warehouse.csv";
                    putInStorage(list, result.foundUPC, fileName, result.quantity, q,  total);
                    break;
                }
                case '2':
                {
                    printf("Distribute to ... Nakorn Ratchasrima.\n");
                    char fileName[] = "korat_warehouse.csv";
                    putInStorage(list, result.foundUPC, fileName, result.quantity, q,  total);
                    break;
                }
                case '3' :
                {
                    printf("Distribute to ... Ubon Ratchathani.\n");
                    char fileName[] = "ubon_warehouse.csv";
                    putInStorage(list, result.foundUPC, fileName, result.quantity, q,  total);
                    break;
                }
                case '4' :
                {
                    printf("Distribute to ... Rayong.\n");
                    char fileName[] = "rayong_warehouse.csv";
                    putInStorage(list, result.foundUPC, fileName, result.quantity, q,  total);
                    break;
                }
                case '5':
                {
                    printf("Distribute to ... Songkhla.\n");
                    char fileName[] = "songkla_warehouse.csv";
                    putInStorage(list, result.foundUPC, fileName, result.quantity, q,  total);
                    break;
                }
                default:
                    break;
            }
        }

        else
        {
            printf("Error! :Invalid Input.");
        }

    }
}
void putInStorage(struct item unused[], char UPC[], char filename[], int prev_q, int dist_q, int total)
{
    // data loading
    FILE *data;
    struct item itemMain;
    struct item mainList[10001];
    data = fopen("main_warehouse.csv", "r");

    int v = 0;
    int totalProductList;
    char buffer[100];
    fscanf(data,"%s\n",buffer);
    while(fscanf(data,"%[^,],%[^,],%d,%f,%[^,],%d\n",itemMain.UPC,itemMain.name,&itemMain.quantity,
                 &itemMain.price,itemMain.company, &itemMain.capacities) == 6)
    {
        mainList[v++] = itemMain;
    }

    totalProductList = v;
    fclose(data);
    // end of the data loading section and start the main program

//    printf("\ndata in main\n");
//    for (int z = 0; z < totalProductList; ++z) {
//        printf("%s\n", mainList[z].UPC);
//    }

    // data loading from branch-warehouse file
    FILE *branchFile;
    struct item newProduct;
    struct item branchProductList[2001];
    branchFile = fopen(filename, "r");

    int i = 0;
    int branch_totalProductList;
    char buffer1[100];
    fscanf(branchFile,"%s\n",buffer1);
    while(fscanf(branchFile,"%[^,],%[^,],%d,%f,%[^,],%d\n",newProduct.UPC,newProduct.name,&newProduct.quantity,
                 &newProduct.price,newProduct.company, &newProduct.capacities) == 6)
    {
        branchProductList[i++] = newProduct;
    }
    branch_totalProductList = i;
    fclose(branchFile);
    // end of the data loading section and start the main program
//    printf("data in branch\n");
//    for (int m = 0; m < branch_totalProductList; ++m) {
//        printf("%s\n", branchProductList[m].UPC);
//
//    }

//    printf("branch total list = %d\n", branch_totalProductList);
    //loop for check branch product list if it exist or not and collect the index of the exist item in mainlist
    int  HAVE = 0, index = 0, index_branch =0;
    for (int k = 0; k < branch_totalProductList; ++k) {
        if (strcmp(UPC, branchProductList[k].UPC) == 0)
        {
            HAVE = 1;
            for (int j = 0; j < total; ++j) {
                if (strcmp(mainList[j].UPC, branchProductList[k].UPC) == 0)
                {
//                    printf("item match\n");
                    index = j;
                    index_branch = k;
                    break;
                }
            }
        }
    }
    if (HAVE == 1)
    {
//        printf("\nindex in mainList = %d\n", index);
//        printf("\nindex in branchList = %d\n", index_branch);
//        printf("%s :: %s\n",mainList[index].UPC,branchProductList[index_branch].UPC);
    }

    if (HAVE == 0)
    {
        for (int f = 0; f < total; ++f) {
            if (strcmp(UPC, mainList[f].UPC) == 0)
            {
                index = f;
            }
        }
    }


    switch (HAVE)
    {
        case 0 : //case not have
        {
            printf("Product doesn't detected.\nCreating new product\n"); //create new structure in branch warehouse
            struct item newItem;
//            printf("\nindex in mainList = %d,%s\n", index,mainList[index].UPC);
            strcpy(newItem.UPC,mainList[index].UPC);
            strcpy(newItem.name,mainList[index].name);
            newItem.quantity = dist_q;
            newItem.price = mainList[index].price;
            strcpy(newItem.company, mainList[index].company);
            newItem.capacities = mainList[index].capacities;
            mainList[index].quantity -= dist_q;
            branchProductList[branch_totalProductList] = newItem;
//            printf("%13s  %-30s %9d %10.3f   %-15s %6d\n", newItem.UPC, newItem.name,
//                   newItem.quantity, newItem.price, newItem.company, newItem.capacities);

            printf("\nProduct Summary\n=============\n");
            printf("UPC : %s\n", newItem.UPC);
            printf("Product name :  %s\n", newItem.name);
            printf("Quantity : %d\n", newItem.quantity);
            printf("Selling Price : %.2f\n", newItem.price);
            printf("Manufacturer : %s\n", newItem.company);
            printf("=============\n");

            //append to file
            FILE *branch_database;
            branch_database = fopen(filename, "a");
            fprintf(branch_database, "%s,%s,%d,%.3f,%s,%d\n", newItem.UPC, newItem.name, newItem.quantity,
                    newItem.price, newItem.company, newItem.capacities);
            fclose(branch_database);
            break;
        }
        case 1: // case have
        {
            printf("already have\n");
            printf("Before in branch : %d\n",branchProductList[index_branch].quantity);
            branchProductList[index_branch].quantity += dist_q; //update quantity in branch array
            mainList[index].quantity -= dist_q; //update quantity in main array
            printf("After in branch : %d\n",branchProductList[index_branch].quantity);


            //update branch file
            int x;
            FILE *database;
            char header[] = "UPC,name,quantity,price,company,capacities\n";
            database = fopen(filename, "w");
            fputs(header, database);
            for (x = 0; x < branch_totalProductList; x++)
                fprintf(database, "%s,%s,%d,%.3f,%s,%d\n", branchProductList[x].UPC, branchProductList[x].name, branchProductList[x].quantity,
                        branchProductList[x].price, branchProductList[x].company, branchProductList[x].capacities);
            fclose(database);

            break;
        }
        default:break;
    }

    //update main file
//    printf("Updating main file\n");
    int x;
    FILE *database;
    char header[] = "UPC,name,quantity,price,company,capacities\n";
    database = fopen("main_warehouse.csv", "w");
    fputs(header, database);
    for (x = 0; x < total; x++)
        fprintf(database, "%s,%s,%d,%.3f,%s,%d\n", mainList[x].UPC, mainList[x].name, mainList[x].quantity,
                mainList[x].price,mainList[x].company, mainList[x].capacities);
    fclose(database);

    //update stock file
//    printf("Updating stock file\n");
    int prev_cap = check_capacity();
    FILE *capfile;
    capfile = fopen("stock.txt", "w");
    fprintf(capfile, "%d",prev_cap - dist_q);
    fclose(capfile);
    return;
}
void addquantity(struct item list[], int total)
{
    char inp[14],quantity[7];
    int i,j,new_quantity;
    printf(">>> ADD QUANTITY FUNCTION\n");
    printf("Enter Product's UPC : ");
    gets(inp);

    struct available result;
    result = getAvailable(list,inp,total);
    if (result.valid == 0)
    {
        printf("Error! : Item not found\n");
        return;
    }

    printf("Add Quantity :");
    gets(quantity);

    if (isValidInt(inp) == 1 && strlen(inp) == 13 && isValidInt(quantity) == 1 && strlen(quantity) <= 7)
    {
        for (i=0; i < total; i++)
        {
            if(strcmp(list[i].UPC, inp) == 0)
            {
                int temp;
                new_quantity = atoi(quantity);
                temp = new_quantity * list[i].capacities;
                if (check_capacity() + temp < MAXCAPACITIES)
                {
//                    printf("before : %d\n", list[i].quantity);
                    list[i].quantity += new_quantity;
//                    printf("after : %d\n", list[i].quantity);

                    int x;
                    FILE *database;
                    char header[] = "UPC,name,quantity,price,company,capacities\n";
                    database = fopen("main_warehouse.csv", "w");
                    fputs(header, database);
                    for (x = 0; x < total-1; x++)
                        fprintf(database, "%s,%s,%d,%.3f,%s,%d\n", list[x].UPC, list[x].name, list[x].quantity,
                                list[x].price, list[x].company, list[x].capacities);
                    fclose(database);
                    int prev_cap = check_capacity();
                    FILE *capfile;
                    capfile = fopen("stock.txt", "w");
                    fprintf(capfile, "%d",prev_cap + temp);
                    fclose(capfile);
                    return;
                }
            }
        }
    }
}

void view()
{
    // data loading
    FILE *database;
    struct item newProduct;
    struct item productList[20001];
    database = fopen("main_warehouse.csv", "r");

    int i = 0;
    int totalProductList;
    char buffer[100];
    fscanf(database,"%s\n",buffer);
    while(fscanf(database,"%[^,],%[^,],%d,%f,%[^,],%d\n",newProduct.UPC,newProduct.name,&newProduct.quantity,
                 &newProduct.price,newProduct.company, &newProduct.capacities) == 6)
    {
        productList[i++] = newProduct;
    }
    totalProductList = i;

    char optmenu[10], menu;
    fclose(database);
    // end of the data loading section and start the main program
    printf("VIEW MENU : View All Stock (A)");
    gets(optmenu);
    if (strlen(optmenu) == 1)
    {
        menu = optmenu[0];
        switch (toupper(menu))
        {
            case 'A' :
            {
                display(productList, totalProductList);
                break;
            }
            default:{
                printf("unknown");
                break;
            }
        }
    }
    else printf("Error! : invalid Data\n");
}

void display(struct item list[], int total)
{
    system("cls");
    int i;
    printf("============== ============================== ========= ===========\n");
    printf("UPC            Name                            Quantity  Cap. used\n");
    printf("============== ============================== ========= ===========\n");

    for (i = 0; i < total; i++)
    {
        printf("%13s  %-30s %9d  %6d\n", list[i].UPC, list[i].name, list[i].quantity,
        list[i].capacities);
    }
    if (total == 0)
    {
        printf("              (empty)               \n\n");
    }
    else printf("\n\n");
    printf("============== ============================== ========= ===========\n");
    printf("press any key to continue\n\n");
    getchar();
}

