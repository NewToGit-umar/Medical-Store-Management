#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

const int MAX_Medicines = 1000;

struct Medicine 
{
    int id = 0;
    string name;
    int quantity = 0;
    float price = 0;
    string location;
};

Medicine inventory[MAX_Medicines];
int medicineCount = 0; 
float totalSales = 0.0;
// Function to set text color
void SetColor(int color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void addMedicine() 
{
    if (medicineCount < MAX_Medicines) 
	{
        int id, quantity;
        float price;
        string name, location;

        cout << "Enter ID(e.g 01,02 etc): ";
        cin >> id;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter location(e.g 12 '1' for 'row','2' for 'column'): ";
        cin.ignore();
        getline(cin, location);
        
        inventory[medicineCount] = { id, name, quantity, price, location };
        medicineCount++;

        cout << "Please Wait..." << endl;
        Sleep(1000); 
        cout << endl;
        cout << "Medicine Added Successfully...." << endl << endl;
    }
	 else 
	{
        cout << "Inventory is full. Cannot add more medicines." << endl;
    }
}

void displayAll() 
{
    cout << "Reading inventory from file..." << endl;
    fstream inFile;
    inFile.open("inventory.txt", ios::in);
    if (!inFile)
	 {
        cout << "No existing inventory file found." << endl;
        return;
    }

    inFile >> medicineCount;
    inFile.ignore(); 
    for (int i = 0; i < medicineCount; i++) 
	{
        inFile >> inventory[i].id;
        inFile.ignore(); 
        getline(inFile, inventory[i].name);
        inFile >> inventory[i].quantity >> inventory[i].price;
        inFile.ignore(); 
        getline(inFile, inventory[i].location);
    }
    inFile.close();

    cout << "ID\tName\t\tQuantity\tPrice\t\tLocation\n";
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < medicineCount; i++)
	 {
        cout << inventory[i].id << "\t" 
             << inventory[i].name << "\t\t" 
             << inventory[i].quantity << "\t\t" 
             << inventory[i].price << "\t\t" 
             << inventory[i].location << endl;
    }
}

void checkLocation(int id) 
{
    for (int i = 0; i < medicineCount; i++)
	 {
        if (inventory[i].id == id)
		 {
            cout << "Location of " << inventory[i].name << " is: " << inventory[i].location << endl;
            return;
        }
    }
    cout << "Medicine not found." << endl;
}

void manageSales(int id, int quantity)
 {
    for (int i = 0; i < medicineCount; i++) 
	{
        if (inventory[i].id == id) 
		{
            if (inventory[i].quantity >= quantity) 
			{
                inventory[i].quantity -= quantity;
                float saleAmount = quantity * inventory[i].price;
                totalSales += saleAmount;
                cout << "Sold " << quantity << " units of " << inventory[i].name << " for " << saleAmount << endl;
                cout << "Total Sales: " << totalSales << endl;
            } 
			else
			 {
                cout << "Not enough stock available." << endl;
            }
            return;
        }
    }
    cout << "Medicine not found." << endl;
}

void saveToFile() 
{
    cout << "Saving inventory to file..." << endl;
    fstream outFile;
    outFile.open("inventory.txt", ios::out);
    outFile << medicineCount << endl;
    for (int i = 0; i < medicineCount; i++)
	 {
        outFile << inventory[i].id << endl
                << inventory[i].name << endl
                << inventory[i].quantity << endl
                << inventory[i].price << endl
                << inventory[i].location << endl;
    }
    outFile.close();
    cout << "Inventory saved to file." << endl;
}

void Header()
 {
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "****************************************************" << endl;
    cout << "*                                                  *" << endl;
    cout << "*            PHARMACY MANAGEMENT SYSTEM            *" << endl;
    cout << "*                                                  *" << endl;
    cout << "****************************************************" << endl;
    cout << endl;
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void MainMenu() 
{
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Main Menu>" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. Check Location" << endl;
    cout << "2. Check Sales" << endl;
    cout << "3. Add New Product" << endl;
    cout << "4. Check All Medicines" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() 
{
    int choice, id, quantity;

    while (true) 
	{
        Header();
        MainMenu();
        cin >> choice;
        cout << endl;

        if (choice == 1) 
		{
            system("cls");
            Header();
            cout << "Main Menu> Check location" << endl;
            cout << "----------------------------------------------------" << endl;
            cout << "Enter ID: ";
            cin >> id;
            checkLocation(id);
        } 
		else if (choice == 2) 
		{
            system("cls");
            Header();
            fstream inFile;
            cout << "Main Menu> Check Sales" << endl;
            cout << "----------------------------------------------------" << endl;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter quantity to sell: ";
            cin >> quantity;
            manageSales(id, quantity);    
        } 
		else if (choice == 3) 
		{
            system("cls");
            Header();
            cout << "Main Menu> Add New Product" << endl;
            cout << "----------------------------------------------------" << endl;
            addMedicine();
        } 
		else if (choice == 4)
		 {
            system("cls");
            Header();
            cout << "Main Menu> Check All Medicines" << endl;
            cout << "----------------------------------------------------" << endl;
            displayAll();
        }
		 else if (choice == 5) 
		 {
            saveToFile();
            return 0;
        } 
		else 
		{
            cout << "Invalid choice." << endl;
        }
        cout << endl;
    }

    return 0;
}
