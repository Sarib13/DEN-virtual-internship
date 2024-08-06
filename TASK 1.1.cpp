#include <iostream>
#include <string>
using namespace std;

class location{
public:
    string name;
    double longitude;
    double latitude;
};

class locationmanager{
private:
    static const int max_loc = 100;
    location locations[max_loc];
    int loc_count;

public:
    locationmanager() : loc_count(0) {}
    void addLocation(const string& name, double longitude, double latitude){
        if(loc_count < max_loc){
            locations[loc_count].name = name;
            locations[loc_count].longitude = longitude;
            locations[loc_count].latitude = latitude;
            loc_count++;
        }
        else{
            cout << "Maximum number of locations reached!" << endl;
        }
    }
    void removeloc(const string& name){
        int index = -1;
        for(int i = 0; i < loc_count; i++){
            if(locations[i].name == name){
                index = i;
                break;
            }
        }
        if(index!= -1){
            for(int i = index; i < loc_count - 1; i++){
                locations[i] = locations[i + 1];
            }
            loc_count--;
        }
        else{
            cout << "Location not found!" << endl;
        }
    }
    void listLocations() const{
        if(loc_count == 0){
            cout << "No locations added!" << endl;
            return;
        }
        cout << "List of Locations:" << endl;
        for(int i = 0; i < loc_count; i++){
            cout << locations[i].name << " (" << locations[i].longitude << ", " << locations[i].latitude << ")" << endl;
        }
    }
};
int main(){
    locationmanager lm;
    int choice;
    string name;
    double longitude, latitude;

    do{
        cout << "\nLocation Manager Menu" << endl;
        cout << "1. Add Location" << endl;
        cout << "2. Remove Location" << endl;
        cout << "3. List Locations" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter location name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter longitude: ";
                cin >> longitude;
                cout << "Enter latitude: ";
                cin >> latitude;
                lm.addLocation(name, longitude, latitude);
                break;
            case 2:
                cout << "Enter location name to remove: ";
                cin.ignore();
                getline(cin, name);
                lm.removeloc(name);
                break;
            case 3:
                lm.listLocations();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;  
    }
}while(choice != 4);
return 0;
}