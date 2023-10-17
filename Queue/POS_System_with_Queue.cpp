#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[100];
    float price;
    int quantity;
};

struct Queue {
    struct Product *products;
    int front;
    int rear;
    int count;
    int size;
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int searchProduct(struct Product products[], int count, int id, struct Product *foundProduct);
void deleteProduct(struct Product products[], int *count, int id);
void updateProduct(struct Product products[], int count, int id, char newName[], float newPrice, int *newQuantity);

void enqueue(struct Queue *queue, int id, char name[], float price, int quantity) {
    if (queue->count < queue->size) {
        // Queue is not full, simply add the new item
        queue->products[queue->rear].id = id;
        strcpy(queue->products[queue->rear].name, name);
        queue->products[queue->rear].price = price;
        queue->products[queue->rear].quantity = quantity;
        queue->rear = (queue->rear + 1) % queue->size;
        queue->count++;
        printf("Product added successfully.\n");
    } else {
        // Queue is full, ask user if they want to remove the first item
        char choice;
        printf("Queue is full. Do you want to remove the first item? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            // Remove the oldest item and add the new one
            printf("Removing the oldest product: %s\n", queue->products[queue->front].name);
            queue->front = (queue->front + 1) % queue->size;
        } else {
            // Do not add the new item
            printf("New product was not added.\n");
            return;
        }

        // Add the new item
        queue->products[queue->rear].id = id;
        strcpy(queue->products[queue->rear].name, name);
        queue->products[queue->rear].price = price;
        queue->products[queue->rear].quantity = quantity;
        queue->rear = (queue->rear + 1) % queue->size;
        printf("New product added successfully.\n");
    }
}


void displayQueue(struct Queue *queue) {
    printf("Queue Contents (Front to Rear):\n");
    printf("%-5s%-20s%-10s%-10s\n", "ID", "Name", "Price", "Quantity");
    int i;
    for (i = queue->front; i < queue->front + queue->count; i++) {
        int index = i % queue->size;
        printf("%-5d%-20s%-10.2f%-10d\n", queue->products[index].id, queue->products[index].name,
               queue->products[index].price, queue->products[index].quantity);
    }
}

void initQueue(struct Queue *queue, int size){
    queue->products = (struct Product *)malloc(size * sizeof(struct Product));
    if(queue->products == NULL){
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    queue->size = size;
}

void destroyQueue(struct Queue *queue){
	free(queue->products);
}

int main() {
    struct Queue queue;
    int maxSize;
    queue.front = 0;
    queue.rear = 0;
    queue.count = 0;

    int choice, id, quantity;
    char name[100];
    float price;
    
    printf("Enter the maximum size of the queue: ");
    scanf("%d", &maxSize);
    initQueue(&queue, maxSize);

    do {
        printf("\n==== Point of Sale System ====\n");
        printf("[1.] Add Product\n");
        printf("[2.] Display Product\n");
        printf("[3.] Update Product\n");
        printf("[4.] Search Product\n");
        printf("[5.] Delete Product\n");
        printf("[6.] Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

		// Clear the input buffer
        clearInputBuffer();
		
        switch (choice) {
            case 1:
                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter Product Name: ");
                scanf("%s", name);
                printf("Enter Product Price: ");
                scanf("%f", &price);
                printf("Enter Product Quantity: ");
                scanf("%d", &quantity);
                enqueue(&queue, id, name, price, quantity);
                break;
            case 2:
                displayQueue(&queue);
                break;
            case 3:
    			printf("Enter Product ID to update: ");
    			scanf("%d", &id);
    			printf("Enter new Product Name: ");
    			scanf("%s", name);
    			printf("Enter new Product Price: ");
    			scanf("%f", &price);
    			printf("Enter new Product Quantity: ");
    			scanf("%d", &quantity);  // Corrected line: &quantity instead of quantity
    			updateProduct(queue.products, queue.count, id, name, price, &quantity); // Pass quantity as a pointer
    			break;
            case 4:
                printf("Enter Product ID to search: ");
    			scanf("%d", &id);
    			struct Product foundProduct;
    			int index = searchProduct(queue.products, queue.count, id, &foundProduct);
    			if (index != -1) {
        		printf("Product found at index %d:\n", index);
        		printf("ID: %d\n", foundProduct.id);
        		printf("Name: %s\n", foundProduct.name);
        		printf("Price: %.2f\n", foundProduct.price);
        		printf("Quantity: %d\n", foundProduct.quantity);
    			} else {
        		printf("Product not found.\n");
    			}
    			break;
            case 5:
                printf("Enter Product ID to delete: ");
                scanf("%d", &id);
                deleteProduct(queue.products, &queue.count, id);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
	
	destroyQueue(&queue);
	
    return 0;
}

int searchProduct(struct Product products[], int count, int id, struct Product *foundProduct) {
    int i;
    for (i = 0; i < count; i++) {
        if (products[i].id == id) {
            if (foundProduct != NULL) {
                *foundProduct = products[i]; // Copy the found product details
            }
            return i;
        }
    }
    return -1;
}

void deleteProduct(struct Product products[], int *count, int id){
	int index = searchProduct(products, *count, id, NULL);
	if (index != -1){
		int i;
		for (i = index; i < *count - 1; i++){
			products[i] = products[i+1];
		}
		(*count)--;
		printf("Product delete successfully.\n");
	} else{
		printf("Product not found.\n");
	}
}

void updateProduct(struct Product products[], int count, int id, char newName[], 
                   float newPrice, int *newQuantity) {
    int index = searchProduct(products, count, id, NULL);
    if (index != -1) {
        // Update individual fields of the product at the found index
        strcpy(products[index].name, newName);
        products[index].price = newPrice;
        products[index].quantity = *newQuantity; // Update quantity using pointer
        printf("Product updated successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}



