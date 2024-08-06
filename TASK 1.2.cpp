#include <iostream>
#include <string>

using namespace std;

class WeatherVariables{
private: 
    static const int MaxVariable = 100;
    struct Variable{
        string name;
        double value;
    };
public:
    Variable variables[MaxVariable] ;
    int variablecount;
    WeatherVariables() : variablecount (0) {}

    void defineVariable(const string& name, double value){
        if(variablecount < MaxVariable){
            variables[variablecount].name = name;
            variables[variablecount].value = value;
            variablecount++;
        }else{
            cout << "Error: Maximum number of variables reached." << endl;
        }

    }
    void listVariables() const {
        if(variablecount == 0){
            cout << "No variables defined." << endl;
        } else{
            cout << "Defined Variables:" << endl;
            for(int i = 0; i < variablecount; i++){
                cout << variables[i].name << ": " << variables[i].value << endl;
            }
        }
    }
    };
    
int main() {
    WeatherVariables weather;
    weather.defineVariable("Temperature", 20.5);
    weather.defineVariable("Humidity", 70.0);
    weather.defineVariable("Wind Speed", 15.0);

    cout << "Weather Variables:"  << endl;
    weather.listVariables();

    return 0;
}