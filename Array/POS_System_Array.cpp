#include <stdio.h>
#include <string.h>

// Structure to store product details
struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

int main() {
    struct Product products[100]; // Array to store products
    int choice, numProducts = 0, i, id, newId;
    
    do {
        // Display menu
        printf("\n[1] Add Products\n[2] Display Products\n[3] Update Products\n[4] Search Products\n[5] Delete Products\n[6] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Add Products
                printf("Enter Product ID: ");
                scanf("%d", &products[numProducts].id);
                printf("Enter Product Name: ");
                scanf("%s", products[numProducts].name);
                printf("Enter Product Price: ");
                scanf("%f", &products[numProducts].price);
                printf("Enter Product Quantity: ");
                scanf("%d", &products[numProducts].quantity);
                numProducts++;
                break;
            case 2: // Display Products
    			printf("Products in the inventory:\n");
    				for(i = 0; i < numProducts; i++) {
        		printf("| Index: %d |---| ID: %d |---| Name: %s |---| Price: %.2f |---| Quantity: %d |\n", 
               					i, products[i].id, products[i].name, products[i].price, products[i].quantity);
    					}
    			break;

            case 3: // Update Products
                printf("Enter Product ID to update: ");
                scanf("%d", &id);
                for(i = 0; i < numProducts; i++) {
                    if(products[i].id == id) {
                        printf("Enter New Product ID: ");
                        scanf("%d", &newId);
                        printf("Enter New Product Name: ");
                        scanf("%s", products[i].name);
                        printf("Enter New Product Price: ");
                        scanf("%f", &products[i].price);
                        printf("Enter New Product Quantity: ");
                        scanf("%d", &products[i].quantity);
                        products[i].id = newId;
                        printf("Product updated successfully.\n");
                        break;
                    }
                }
                if(i == numProducts) {
                    printf("Product not found.\n");
                }
                break;
            case 4: // Search Products
                printf("Enter Product ID to search: ");
                scanf("%d", &id);
                for(i = 0; i < numProducts; i++) {
                    if(products[i].id == id) {
                        printf("Product found!!!\n| ID: %d |---| Name: %s |---| Price: %.2f |---| Quantity: %d| \n", 
                               products[i].id, products[i].name, products[i].price, products[i].quantity);
                        break;
                    }
                }
                if(i == numProducts) {
                    printf("Product not found.\n");
                }
                break;
            case 5: // Delete Products
                printf("Enter Product ID to delete: ");
                scanf("%d", &id);
                for(i = 0; i < numProducts; i++) {
                    if(products[i].id == id) {
                        // Delete the product by shifting array elements
                        for(int j = i; j < numProducts - 1; j++) {
                            products[j] = products[j + 1];
                        }
                        numProducts--;
                        printf("Product deleted successfully.\n");
                        break;
                    }
                }
                if(i == numProducts) {
                    printf("Product not found.\n");
                }
                break;
            case 6: // Exit
                printf("Exiting the POS system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

