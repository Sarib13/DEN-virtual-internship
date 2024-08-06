#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class HistoricalWeatherSystem {
private:
    string apiKey;
    string baseURL;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

public:
    HistoricalWeatherSystem(const string& apiKey, const string& baseURL)
        : apiKey(apiKey), baseURL(baseURL) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    ~HistoricalWeatherSystem() {
        curl_global_cleanup();
    }

    string fetchHistoricalData(const string& location, const string& startDate, const string& endDate) {
        // Fetch historical data from the API
        // ...
    }

    void displayHistoricalData(const string& historicalData) {
        // Parse and display the historical data
        // ...
    }

    void exportToCSV(const string& historicalData, const string& filename) {
        json parsedData = json::parse(historicalData);
        ofstream csvFile(filename);

        if (csvFile.is_open()) {
            csvFile << "Date,Temperature\n";
            for (const auto& entry : parsedData["data"]) {
                csvFile << entry["date"] << "," << entry["temperature"] << "\n";
            }
            csvFile.close();
            cout << "Historical data exported to " << filename << " in CSV format." << endl;
        } else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void exportToJSON(const string& historicalData, const string& filename) {
        json parsedData = json::parse(historicalData);
        ofstream jsonFile(filename);

        if (jsonFile.is_open()) {
            jsonFile << parsedData.dump(4);
            jsonFile.close();
            cout << "Historical data exported to " << filename << " in JSON format." << endl;
        } else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};

int main() {
    HistoricalWeatherSystem weatherSystem("YOUR_API_KEY", "https://api.weather.com/historical");

    string location = "New York";
    string startDate = "2022-01-01";
    string endDate = "2022-01-31";

    string historicalData = weatherSystem.fetchHistoricalData(location, startDate, endDate);
    weatherSystem.displayHistoricalData(historicalData);

    weatherSystem.exportToCSV(historicalData, "historical_data.csv");
    weatherSystem.exportToJSON(historicalData, "historical_data.json");

    return 0;
}