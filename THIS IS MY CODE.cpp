#include <iostream>
#include <list>
#include <string>

// Function to display the menu
void displayMenu() {
    std::cout << "KULA KWANZA MENU\n";
    std::cout << "1. Burger - sh.120\n";
    std::cout << "2. Fries - sh.150\n";
    std::cout << "3. Coke - sh.60\n";
}

// Structure to store employee details
struct Employee {
    std::string name;
    std::string id;
    std::string email;
};

// Structure to store food item details
struct FoodItem {
    std::string name;
    double price;
    int quantity;
};

// Function to update stock and show quantity remaining
void updateStock(std::list<FoodItem>& stock, int index, int quantityOrdered) {
    std::list<FoodItem>::iterator it = stock.begin();
    std::advance(it, index);
    it->quantity -= quantityOrdered;
    std::cout << "Remaining quantity of " << it->name << " is: " << it->quantity << std::endl;
}

// Function to find employee with the given ID
std::list<Employee>::iterator findEmployee(std::list<Employee>& employees, const std::string& enteredID) {
    for (std::list<Employee>::iterator it = employees.begin(); it != employees.end(); ++it) {
        if (it->id == enteredID) {
            return it;
        }
    }
    return employees.end();
}

int main() {
    std::list<FoodItem> stock;
    stock.push_back({"Burger", 120.0, 30});
    stock.push_back({"Fries", 150.0, 50});
    stock.push_back({"Coke", 60.0, 50});

    std::list<Employee> employees;
    employees.push_back({"Harufu James", "EM001", "harufujames@gmail.com"});
    employees.push_back({"Fufuka Jeru", "EM002", "fufukajeru@gmail.com"});

    std::string customerName, customerAddress, paymentMethod;
    int choice, quantityOrdered;
    double totalAmount = 0.0;

    // Display the menu
    displayMenu();

    // Prompt user for name and ID/Password
    std::string enteredID;
    std::cout << "\nEnter your name: ";
    std::cin >> customerName;
    std::cout << "Enter your ID/Password: ";
    std::cin >> enteredID;

    // Find the employee with the entered ID/Password
    bool foundEmployee = false;
    std::list<Employee>::iterator servingEmployee = findEmployee(employees, enteredID);
    if (servingEmployee != employees.end()) {
        foundEmployee = true;
    }

    if (foundEmployee) {
        std::cout << "\nEnter your address: ";
        std::cin.ignore();
        std::getline(std::cin, customerAddress);
        std::cout << "Select the food item (1, 2, or 3): ";
        std::cin >> choice;
        std::cout << "Enter the quantity: ";
        std::cin >> quantityOrdered;

        // Validate choice and quantity
        if (choice >= 1 && choice <= 3 && quantityOrdered > 0) {
            std::list<FoodItem>::iterator it = stock.begin();
            std::advance(it, choice - 1);
            if (it->quantity >= quantityOrdered) {
                totalAmount = it->price * quantityOrdered;
                updateStock(stock, choice - 1, quantityOrdered);

                // Payment method (assuming valid input for simplicity)
                std::cout << "Enter payment method (Cash or Mpesa): ";
                std::cin >> paymentMethod;

                std::cout << "\n------------------- RECEIPT -------------------\n";
                std::cout << "Restaurant Name: KULA KWANZA\n";
                std::cout << "Customer Details: " << customerName << ", " << customerAddress << std::endl;
                std::cout << "Served by: " << servingEmployee->name << std::endl;
                std::cout << "Food Ordered: " << it->name << " x" << quantityOrdered << std::endl;
                std::cout << "Total Amount: sh." << totalAmount << std::endl;
                std::cout << "RUDI TENA\n";
                std::cout << "----------------------------------------------\n";
            } else {
                std::cout << "Insufficient quantity in stock for the selected food item.\n";
            }
        } else {
            std::cout << "Invalid choice or quantity.\n";
        }
    } else {
        std::cout << "Employee not found with the entered ID/Password.\n";
    }

    // Prompt whether to see the daily sales
    char viewSales;
    std::cout << "Do you want to see the daily sales? (Y/N): ";
    std::cin >> viewSales;

    if (viewSales == 'Y' || viewSales == 'y') {
        double totalRevenue = 0.0;
        std::cout << "\n----------------- DAILY SALES -----------------\n";
        for (std::list<FoodItem>::iterator it = stock.begin(); it != stock.end(); ++it) {
            double revenue = it->price * it->quantity;
            totalRevenue += revenue;
            std::cout << "Food: " << it->name << " - Quantity Remaining: " << it->quantity
                      << " - Revenue: sh." << revenue << std::endl;
        }
        std::cout << "Total Revenue Generated: sh." << totalRevenue << std::endl;
        std::cout << "----------------------------------------------\n";
    }

    return 0;
}
