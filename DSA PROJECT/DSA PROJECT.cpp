// DSA PROJECT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <iomanip>
#include<fstream>
using namespace std;
enum OrderStatus { PROCESSING, DELIVERED };
struct Item {
 string itemName;
 double itemPrice;
 int quantity;
 Item* nextItem;
};
struct Invoice {
 int invoiceNumber;
 string customerName;
 string receiverName;
 OrderStatus status;
 Item* itemsList;
 Invoice* nextInvoice;
};
class BillingSystem {
private:
 Invoice* head;
 int nextInvoiceID;
public:
 BillingSystem() : head(nullptr), nextInvoiceID(1) {}
 ~BillingSystem() {
 while (head != nullptr) {
 Invoice* tempInvoice = head;
 head = head->nextInvoice;
 while (tempInvoice->itemsList != nullptr) {
 Item* tempItem = tempInvoice->itemsList;
 tempInvoice->itemsList = tempItem->nextItem;
 delete tempItem;
 }
 delete tempInvoice;
 }
 }
 void addInvoice(string customerName, string receiverName) {
 Invoice* newInvoice = new Invoice;
 newInvoice->invoiceNumber = nextInvoiceID++;
 newInvoice->customerName = customerName;
 newInvoice->receiverName = receiverName;
 newInvoice->status = PROCESSING; // Default status
 newInvoice->itemsList = nullptr;
 newInvoice->nextInvoice = head;
 head = newInvoice;
 
 }
 void addItemToInvoice(int invoiceNumber, string itemName, double itemPrice, 
int quantity) {
 Invoice* currentInvoice = findInvoice(invoiceNumber);
 if (currentInvoice) {
 Item* newItem = new Item;
 newItem->itemName = itemName;
 newItem->itemPrice = itemPrice;
 newItem->quantity = quantity;
 newItem->nextItem = currentInvoice->itemsList;
 currentInvoice->itemsList = newItem;
 }
 else {
 cout << "Invoice not found." << endl;
 }
 }
 Invoice* findInvoice(int invoiceNumber) {
 Invoice* currentInvoice = head;
 while (currentInvoice && currentInvoice->invoiceNumber != 
invoiceNumber) {
 currentInvoice = currentInvoice->nextInvoice;
 }
 return currentInvoice;
 }
 void displayInvoice(int invoiceNumber) {
 Invoice* currentInvoice = findInvoice(invoiceNumber);
 if (currentInvoice) {
 cout << "Invoice Number: " << currentInvoice->invoiceNumber << endl;
 cout << "Customer Name: " << currentInvoice->customerName << endl;
 cout << "Cashier Name : " << currentInvoice->receiverName << endl;
 cout << "Order Status: " << (currentInvoice->status == PROCESSING ? 
"Processing" : "Delivered") << endl;
 cout << "Items:" << endl;
 Item* currentItem = currentInvoice->itemsList;
 double totalAmount = 0.0;
 while (currentItem) {
 cout << " Item: " << currentItem->itemName << ", Price: " <<
currentItem->itemPrice
 << ", Quantity: " << currentItem->quantity << endl;
 totalAmount += currentItem->itemPrice * currentItem->quantity;
 currentItem = currentItem->nextItem;
 }
 cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount <<
endl;
 }
 else {
 cout << "Invoice not found." << endl;
 }
 system("pause");
 }
 void searchByCustomerName(string customerName) {
 Invoice* currentInvoice = head;
 while (currentInvoice) {
 if (toLowerCase(currentInvoice->customerName) ==
toLowerCase(customerName)) {
 displayInvoice(currentInvoice->invoiceNumber);
 return;
 }
 currentInvoice = currentInvoice->nextInvoice;
 }
 cout << "RECORD NOT FOUND" << endl;
 system("pause");
 }
 void searchByReceiverName(string receiverName) {
 Invoice* currentInvoice = head;
 while (currentInvoice) {
 if (toLowerCase(currentInvoice->receiverName) ==
toLowerCase(receiverName)) {
 displayInvoice(currentInvoice->invoiceNumber);
 return;
 }
 currentInvoice = currentInvoice->nextInvoice;
 }
 cout << "RECORD NOT FOUND" << endl;
 system("pause");
 }
 void searchByInvoiceNumber(int invoiceNumber) {
 Invoice* currentInvoice = findInvoice(invoiceNumber);
 if (currentInvoice) {
 displayInvoice(invoiceNumber);
 return;
 }
 else {
 cout << "Invoice not found." << endl;
 }
 system("pause");
 }
 void updateOrderStatus(int invoiceNumber, OrderStatus newStatus) {
 Invoice* currentInvoice = findInvoice(invoiceNumber);
 if (currentInvoice) {
 currentInvoice->status = newStatus;
 cout << "Order status updated successfully." << endl;
 }
 else {
 cout << "Invoice not found." << endl;
 }
 system("pause");
 }
private:
 string toLowerCase(const string& str) {
 string lowerStr = str;
 for (char& c : lowerStr) {
 c = tolower(c);
 }
 return lowerStr;
 }
 public:
 void saveToFile() const {
	 ofstream file;
	 file.open("E:Billing_History.txt", ios::app);
	 if (file.is_open()) {
		 Invoice* currentInvoice = head;
		 while (currentInvoice) {
			 file <<"Invoice NO." << currentInvoice->invoiceNumber << "\tCustomer Name: " << currentInvoice->customerName << "\tCashier Name: "
				 << currentInvoice->receiverName << "\tOrder Status: " << currentInvoice->status << endl;

			 Item* currentItem = currentInvoice->itemsList;
			 while (currentItem) {
				 file << "Item," << currentItem->itemName << "\titem price :$" << currentItem->itemPrice
					 << "\titem Quantity," << currentItem->quantity << endl;
				 currentItem = currentItem->nextItem;
			 }

			 currentInvoice = currentInvoice->nextInvoice;
		 }
	 }
	 else {
		 cout << "Unable to open file." << endl;
	 }
 }
};
void printMenu() {
 cout << "\t\t\t*************************************************";
 cout << "\n \t\t\t\t WORLD WIDE WISHES STORE \n";
 cout << "\t\t\t*************************************************" <<
endl;
 cout << "1. Add Invoice\n";
 cout << "2. Add Item to Invoice\n";
 cout << "3. Display Invoice\n";
 cout << "4. Search by Customer Name\n";
 cout << "5. Search by Cashier Name\n";
 cout << "6. Search by Invoice Number\n";
 cout << "7. Update Order Status\n";
 cout << "8. Exit\n";
 cout << "Enter your choice: ";
}
int main() {
	BillingSystem billingSystem;
	int choice;
	string customerName, receiverName, itemName;
	double itemPrice;
	int quantity, invoiceNumber;
	int newStatus;
	do {
		system("cls");
		printMenu();
		cin >> choice;
		cin.ignore(); 
		switch (choice) {
		case 1:
			cout << "Enter Customer Name: ";
			cin >> customerName;
			cout << "Enter Cashier Name: ";
			cin >> receiverName;
			billingSystem.addInvoice(customerName, receiverName);
			cout << "Invoice added successfully." << endl;
			system("pause");
			break;
		case 2:
			cout << "Enter Invoice Number: ";
			cin >> invoiceNumber;
			cin.ignore();
			cout << "Enter Item Name: ";
			getline(cin, itemName);
			cout << "Enter Item Price: ";
			cin >> itemPrice;
			cout << "Enter Quantity: ";
			cin >> quantity;
			billingSystem.addItemToInvoice(invoiceNumber, itemName, itemPrice,
				quantity);
			cout << "Item added to the invoice successfully." << endl;
			
			system("pause");
			break;
		case 3:
			cout << "Enter Invoice Number: ";
			cin >> invoiceNumber;
			billingSystem.displayInvoice(invoiceNumber);
			break;
		case 4:
			cout << "Enter Customer Name: ";
			getline(cin, customerName);
			billingSystem.searchByCustomerName(customerName);
			break;
		case 5:
			cout << "Enter Receiver Name: ";
			getline(cin, receiverName);
			billingSystem.searchByReceiverName(receiverName);
			break;
		case 6:
			cout << "Enter Invoice Number: ";
			cin >> invoiceNumber;
			billingSystem.searchByInvoiceNumber(invoiceNumber);
			break;
		case 7:
			cout << "Enter Invoice Number: ";
			cin >> invoiceNumber;
			cout << "Enter New Order Status (0 for Processing, 1 for Delivered): ";
			cin >> newStatus;
			billingSystem.updateOrderStatus(invoiceNumber, newStatus == 1 ?
				DELIVERED : PROCESSING);
			billingSystem.saveToFile();
			break;
		case 8:
			cout << "Exiting the program." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

	} while (choice != 8);
	
	return 0;
}
