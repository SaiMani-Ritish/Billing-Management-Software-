#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENU_ITEMS 100
#define MAX_TABLES 50
#define MAX_ORDERS_PER_TABLE 20
#define MAX_NAME_LENGTH 100

// Structure for menu item
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
} MenuItem;

// Structure for order item
typedef struct {
    int menu_id;
    int quantity;
} OrderItem;

// Structure for table
typedef struct {
    int table_number;
    OrderItem orders[MAX_ORDERS_PER_TABLE];
    int order_count;
    int is_occupied;
} Table;

// Global variables
MenuItem menu[MAX_MENU_ITEMS];
Table tables[MAX_TABLES];
int menu_count = 0;
int table_count = 0;

// Function prototypes
void display_menu();
void add_menu_item();
void add_order();
void display_table_bill();
void display_all_tables();
void initialize_system();
int find_table(int table_number);
int find_menu_item(int menu_id);
void clear_input_buffer();

int main() {
    int choice;
    
    initialize_system();
    
    printf("=== RESTAURANT BILLING MANAGEMENT SYSTEM ===\n\n");
    
    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add Menu Item\n");
        printf("2. Display Menu\n");
        printf("3. Add Order to Table\n");
        printf("4. Display Table Bill\n");
        printf("5. Display All Tables Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                add_menu_item();
                break;
            case 2:
                display_menu();
                break;
            case 3:
                add_order();
                break;
            case 4:
                display_table_bill();
                break;
            case 5:
                display_all_tables();
                break;
            case 6:
                printf("Thank you for using Restaurant Billing System!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

void initialize_system() {
    // Initialize all tables
    for (int i = 0; i < MAX_TABLES; i++) {
        tables[i].table_number = 0;
        tables[i].order_count = 0;
        tables[i].is_occupied = 0;
    }
    
    // Add some sample menu items
    strcpy(menu[0].name, "Chicken Curry");
    menu[0].id = 1;
    menu[0].price = 250.0;
    
    strcpy(menu[1].name, "Vegetable Biryani");
    menu[1].id = 2;
    menu[1].price = 180.0;
    
    strcpy(menu[2].name, "Dal Tadka");
    menu[2].id = 3;
    menu[2].price = 120.0;
    
    strcpy(menu[3].name, "Naan");
    menu[3].id = 4;
    menu[3].price = 40.0;
    
    strcpy(menu[4].name, "Cold Drink");
    menu[4].id = 5;
    menu[4].price = 30.0;
    
    menu_count = 5;
    
    printf("System initialized with sample menu items.\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_menu_item() {
    if (menu_count >= MAX_MENU_ITEMS) {
        printf("Menu is full! Cannot add more items.\n");
        return;
    }
    
    printf("\n--- ADD MENU ITEM ---\n");
    
    menu[menu_count].id = menu_count + 1;
    
    printf("Enter item name: ");
    fgets(menu[menu_count].name, MAX_NAME_LENGTH, stdin);
    menu[menu_count].name[strcspn(menu[menu_count].name, "\n")] = 0; // Remove newline
    
    printf("Enter item price: ");
    scanf("%f", &menu[menu_count].price);
    clear_input_buffer();
    
    menu_count++;
    printf("Menu item added successfully!\n");
}

void display_menu() {
    if (menu_count == 0) {
        printf("No menu items available.\n");
        return;
    }
    
    printf("\n--- RESTAURANT MENU ---\n");
    printf("%-5s %-30s %-10s\n", "ID", "Item Name", "Price");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < menu_count; i++) {
        printf("%-5d %-30s ₹%-10.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

void add_order() {
    int table_number, menu_id, quantity;
    int table_index;
    
    printf("\n--- ADD ORDER ---\n");
    
    // Display menu first
    display_menu();
    
    printf("\nEnter table number (1-50): ");
    scanf("%d", &table_number);
    
    if (table_number < 1 || table_number > 50) {
        printf("Invalid table number!\n");
        return;
    }
    
    printf("Enter menu item ID: ");
    scanf("%d", &menu_id);
    
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    // Validate menu item
    if (find_menu_item(menu_id) == -1) {
        printf("Invalid menu item ID!\n");
        return;
    }
    
    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }
    
    // Find or create table
    table_index = find_table(table_number);
    if (table_index == -1) {
        // Create new table
        if (table_count >= MAX_TABLES) {
            printf("Maximum tables limit reached!\n");
            return;
        }
        table_index = table_count;
        tables[table_index].table_number = table_number;
        tables[table_index].is_occupied = 1;
        tables[table_index].order_count = 0;
        table_count++;
    }
    
    // Check if table has space for more orders
    if (tables[table_index].order_count >= MAX_ORDERS_PER_TABLE) {
        printf("Table order limit reached!\n");
        return;
    }
    
    // Add order to table
    tables[table_index].orders[tables[table_index].order_count].menu_id = menu_id;
    tables[table_index].orders[tables[table_index].order_count].quantity = quantity;
    tables[table_index].order_count++;
    
    printf("Order added successfully to Table %d!\n", table_number);
}

void display_table_bill() {
    int table_number;
    int table_index;
    float total = 0.0;
    
    printf("\n--- TABLE BILL ---\n");
    printf("Enter table number: ");
    scanf("%d", &table_number);
    
    table_index = find_table(table_number);
    if (table_index == -1) {
        printf("Table %d not found or has no orders!\n", table_number);
        return;
    }
    
    printf("\n=== BILL FOR TABLE %d ===\n", table_number);
    printf("%-30s %-8s %-10s %-12s\n", "Item Name", "Quantity", "Price", "Amount");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < tables[table_index].order_count; i++) {
        int menu_id = tables[table_index].orders[i].menu_id;
        int quantity = tables[table_index].orders[i].quantity;
        int menu_index = find_menu_item(menu_id);
        
        if (menu_index != -1) {
            float amount = menu[menu_index].price * quantity;
            printf("%-30s %-8d ₹%-10.2f ₹%-12.2f\n", 
                   menu[menu_index].name, quantity, menu[menu_index].price, amount);
            total += amount;
        }
    }
    
    printf("----------------------------------------------------------------\n");
    printf("%-50s ₹%-12.2f\n", "TOTAL AMOUNT:", total);
    printf("================================================================\n");
}

void display_all_tables() {
    printf("\n--- ALL TABLES STATUS ---\n");
    
    if (table_count == 0) {
        printf("No tables have orders yet.\n");
        return;
    }
    
    printf("%-10s %-12s %-15s\n", "Table No.", "Orders", "Status");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < table_count; i++) {
        printf("%-10d %-12d %-15s\n", 
               tables[i].table_number, 
               tables[i].order_count,
               tables[i].is_occupied ? "Occupied" : "Free");
    }
}

int find_table(int table_number) {
    for (int i = 0; i < table_count; i++) {
        if (tables[i].table_number == table_number) {
            return i;
        }
    }
    return -1; // Table not found
}

int find_menu_item(int menu_id) {
    for (int i = 0; i < menu_count; i++) {
        if (menu[i].id == menu_id) {
            return i;
        }
    }
    return -1; // Menu item not found
}