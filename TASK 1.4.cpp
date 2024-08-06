#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

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
        CURL* curl = curl_easy_init();
        string readBuffer;

        if (curl) {
            string url = baseURL + "?location=" + location + "&startDate=" + startDate + "&endDate=" + endDate + "&apiKey=" + apiKey;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            }

            curl_easy_cleanup(curl);
        }

        return readBuffer;
    }

    void displayHistoricalData(const string& historicalData) {
        // Parse and display the historical data here
        // Assuming the data is in JSON format, you can use a JSON parsing library like nlohmann/json
        // Example:
        // json parsedData = json::parse(historicalData);
        // for (const auto& entry : parsedData["data"]) {
        //     cout << "Date: " << entry["date"] << ", Temperature: " << entry["temperature"] << endl;
        // }
    }
};

int main() {
    HistoricalWeatherSystem weatherSystem("YOUR_API_KEY", "https://api.weather.com/historical");

    string location = "New York";
    string startDate = "2022-01-01";
    string endDate = "2022-01-31";

    string historicalData = weatherSystem.fetchHistoricalData(location, startDate, endDate);
    weatherSystem.displayHistoricalData(historicalData);

    return 0;
}