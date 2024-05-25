#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Item {
    char code[10];
    char name[50];
    float quantity;  // Updated to float for KG
    float seller_price;
    float wholesale_price;
    float retail_price;
};

// Function Declarations
void addInformation(struct Item inventory[], int *count);
void deleteInformation(struct Item inventory[], int *count, char itemCode[]);
void viewInformation(struct Item inventory[], int count);
void searchInformation(struct Item inventory[], int count, char itemCode[]);
void editInformation(struct Item inventory[], int count, char itemCode[]);
float calculateTotalPrice(struct Item inventory[], int count, char itemName[], float quantity);

void saveToFile(struct Item inventory[], int count, const char* filename);
void loadFromFile(struct Item inventory[], int *count, const char* filename);

int main()
    {
    struct Item inventory[100]; // Assuming a maximum of 100 items
    int itemCount = 0;
    int choice;

    // Load data from a file (if available)
    loadFromFile(inventory, &itemCount, "inventory_data.txt");

           printf("\t\t\t\t ------------------------------------------------\n");
           printf("\t\t\t\t |\tSTREMLINED FOOD MANAGEMENT SYSTEM\t|\n\t*****************************************************************************************************\n");

    do {
        printf("\n\n1. View Information\n");
        printf("2. Add Information\n");
        printf("3. Delete Information\n");
        printf("4. Search Information\n");
        printf("5. Edit Information\n");
        printf("6. Order Processing\n");
        printf("7. Save to File\n");
        //printf("8. Load from File\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                viewInformation(inventory, itemCount);
                break;

            case 2:
                addInformation(inventory, &itemCount);
                break;

            case 3:
                 {
                char itemCode[10];
                printf("-Enter Item Code to delete: ");
                scanf("%s", itemCode);
                deleteInformation(inventory, &itemCount, itemCode);
                break;
                }
            case 4:
                 {
                char itemCode[10];
                printf("-Enter Item Code to search:");
                scanf("%s", itemCode);
                searchInformation(inventory, itemCount, itemCode);
                break;
                }
            case 5: {
                char itemCode[10];
                printf("-Enter Item Code to edit: ");
                scanf("%s", itemCode);
                editInformation(inventory, itemCount, itemCode);
                break;
                    }
            case 6: {
                char itemName[50];
                float quantity;
                printf("-Enter Item Name for order processing: ");
                scanf("%s", itemName);
                printf("-Enter Quantity (KG): ");
                scanf("%f", &quantity);
                float totalPrice = calculateTotalPrice(inventory, itemCount, itemName, quantity);
                if (totalPrice > 0) {
                    printf("Total Price: %.2f\n", totalPrice);
                } else {
                    printf("Item not found.\n");
                }
                break;
            }
            case 7:
                saveToFile(inventory, itemCount, "inventory_data.txt");
                printf("Data saved to file.\n");
                break;
            case 8:
                loadFromFile(inventory, &itemCount, "inventory_data.txt");
                printf("Data loaded from file.\n");
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void viewInformation(struct Item inventory[], int count) {
    printf("\n=========================================================================================================\n");
    printf("| %-10s | %-20s | %-15s | %-13s | %-16s | %-13s |\n", "Item Code", "Item Name", "Quantity (KG)", "Seller Price", "Wholesale Price", "Retail Price");
    printf("=========================================================================================================\n");

    for (int i = 0; i < count; i++) {
        printf("| %-10s | %-20s | %-15.2f | %-13.2f | %-16.2f | %-13.2f |\n", inventory[i].code, inventory[i].name,
               inventory[i].quantity, inventory[i].seller_price, inventory[i].wholesale_price, inventory[i].retail_price);
    }

    printf("=========================================================================================================\n");
}

void addInformation(struct Item inventory[], int *count) {
    // Input item details
    printf("--Enter Item Code: ");
    scanf("%s", inventory[*count].code);

    printf("--Enter Item Name: ");
    scanf("%s", inventory[*count].name);

    printf("--Enter Item Quantity (KG): ");
    scanf("%f", &inventory[*count].quantity);

    printf("--Enter Seller Price: ");
    scanf("%f", &inventory[*count].seller_price);

    printf("--Enter Wholesale Price: ");
    scanf("%f", &inventory[*count].wholesale_price);

    printf("--Enter Retail Price: ");
    scanf("%f", &inventory[*count].retail_price);

    // Increment count
    (*count)++;

    printf("\nItem added successfully.\n___________________________________");
}

void deleteInformation(struct Item inventory[], int *count, char itemCode[]) {
    // Iterate through inventory to find item with given code
    int i;
    for (i = 0; i < *count; i++) {
        if (strcmp(inventory[i].code, itemCode) == 0) {
            // Delete item
            for (int j = i; j < *count - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*count)--;
            printf("\nItem deleted successfully.\n___________________________________________");
            return;
        }
    }
    printf("Item not found.\n");
}



void searchInformation(struct Item inventory[], int count, char itemCode[]) {
    printf("\n========================================================================================================\n");
    printf("| %-10s | %-20s | %-15s | %-13s | %-16s | %-13s |\n", "Item Code", "Item Name", "Quantity (KG)", "Seller Price", "Wholesale Price", "Retail Price");
    printf("========================================================================================================\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].code, itemCode) == 0) {
            printf("| %-10s | %-20s | %-15.2f | %-13.2f | %-16.2f | %-13.2f |\n", inventory[i].code, inventory[i].name,
                   inventory[i].quantity, inventory[i].seller_price, inventory[i].wholesale_price, inventory[i].retail_price);
            printf("========================================================================================================\n");
            return;
        }
    }

    printf("Item with code %s not found.\n", itemCode);
}


void editInformation(struct Item inventory[], int count, char itemCode[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].code, itemCode) == 0) {
            // Edit item details
            printf("---Enter New Item Name: ");
            scanf("%s", inventory[i].name);

            printf("---Enter New Item Quantity (KG): ");
            scanf("%f", &inventory[i].quantity);

            printf("---Enter New Seller Price: ");
            scanf("%f", &inventory[i].seller_price);

            printf("---Enter New Wholesale Price: ");
            scanf("%f", &inventory[i].wholesale_price);

            printf("---Enter New Retail Price: ");
            scanf("%f", &inventory[i].retail_price);

            printf("Item edited successfully.\n_____________________________________________");
            return;
        }
    }
    printf("Item not found.\n");
}

float calculateTotalPrice(struct Item inventory[], int count, char itemName[], float quantity) {
    printf("\n===============================================================================================================\n");
    printf("| %-20s | %-15s | %-13s | %-16s | %-13s | %-15s |\n", "Item Name", "Quantity (KG)", "Seller Price", "Wholesale Price", "Retail Price", "Total Price");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, itemName) == 0) {
            float totalPrice = quantity * inventory[i].retail_price;
            printf("| %-20s | %-15.2f | %-13.2f | %-16.2f | %-13.2f | %-15.2f |\n", inventory[i].name, quantity,
                   inventory[i].seller_price, inventory[i].wholesale_price, inventory[i].retail_price, totalPrice);
            printf("===============================================================================================================\n");

            return totalPrice;
        }
    }

    printf("Item with name %s not found.\n", itemName);
    return 0; // Item not found
}



void saveToFile(struct Item inventory[], int count, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.2f %.2f %.2f %.2f\n", inventory[i].code, inventory[i].name,
                inventory[i].quantity, inventory[i].seller_price, inventory[i].wholesale_price, inventory[i].retail_price);
    }

    fclose(file);
}

void loadFromFile(struct Item inventory[], int *count, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    *count = 0;
    while (fscanf(file, "%s %s %f %f %f %f", inventory[*count].code, inventory[*count].name,
                  &inventory[*count].quantity, &inventory[*count].seller_price, &inventory[*count].wholesale_price, &inventory[*count].retail_price) == 6) {
        (*count)++;
    }

    fclose(file);
}
