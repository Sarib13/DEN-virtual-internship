#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Contact {
public:
	string Name;
	string phNumber;
};

void NewContact(vector<Contact> &cont) {
	Contact NewCont;
	cout << "Enter contact name: " ;
	getline(cin, NewCont.Name);
	
	cout << "Enter Phone Number: ";
	getline(cin, NewCont.phNumber);
	
	cont.push_back(NewCont);
	cout << "\nContact added successfully!\n" << endl;
}

void ViewContacts(vector<Contact> &cont) {
	if(cont.empty()){
		cout << "No contact to show.\n" << endl;
		return;
	}
	cout << "\nContacts list\n" << endl;
	for(size_t i = 0; i < cont.size(); i++){
		cout << i + 1<<". " << cont[i].Name << "-" << cont[i].phNumber << endl;
	}
}

void DeleteContact(vector<Contact> &cont) {
	if(cont.empty()){
		cout << "\nNo contacts to delete\n" <<endl;
	return;
	}
	int loc;
	cout << "Enter contact number to delete: ";
	cin >> loc;
	cin.ignore();
	
	if(loc < 1 || loc > cont.size()) {
		cout << "Invalid number" << endl;
		return;
	}
	cont.erase(cont.begin() + loc - 1);
	cout << "Contact deleted\n" << endl;
}

int main(){
	vector<Contact> cont;
	int number;
	do{

	cout << "\n\tCONTACT MANAGEMENT SYSTEM  \n\n\t\t***MENU***\n\n";
	cout << "\t\t1. Add New Contact\n";
	cout << "\t\t2. View Contacts\n";
	cout << "\t\t3. Delete Contact\n";
	cout << "\t\t4. Exit program\n" << endl;
	cout << "Select appropriate number: ";
	cin >> number;
	cin.ignore();

		switch (number) {
		case 1:
			NewContact(cont);
			break;
		case 2:
			ViewContacts(cont);
			break;
    	case 3:
			DeleteContact(cont);
			break;
		case 4:
			cout << "Exiting. . . " << endl;
			break;
		default:
			cout << "Enter appropriate number i.e; 1 to 4" << endl;
		}
		cout << "-------------------------------------------------------------------------------------" << endl;
	} while(number != 4);
}
