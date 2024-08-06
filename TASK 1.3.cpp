#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

using namespace std;

class WeatherDataFetcher {
private:
    string openWeatherMapApiKey;
    string openWeatherMapBaseUrl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t newLength = size * nmemb;
        size_t oldLength = s->size();
        try {
            s->resize(oldLength + newLength);
        } catch (bad_alloc &e) {
            // Handle memory problem
            return 0;
        }
        copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
        return size * nmemb;
    }

    Json::Value parseWeatherDataJson(const string& jsonData) {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(jsonData, root);
        if (!parsingSuccessful) {
            // Handle parsing error
            cerr << "Failed to parse JSON response." << endl;
            return Json::Value();
        }
        return root;
    }

public:
    WeatherDataFetcher(const string& apiKey, const string& baseUrl)
        : openWeatherMapApiKey(apiKey), openWeatherMapBaseUrl(baseUrl) {}

    string fetchWeatherData(const string& location) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if(curl) {
            string url = openWeatherMapBaseUrl + "?q=" + location + "&appid=" + openWeatherMapApiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                // Handle API request error
                cerr << "Failed to fetch weather data: " << curl_easy_strerror(res) << endl;
            }
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    void displayWeatherData(const string& data) {
        Json::Value root = parseWeatherDataJson(data);
        if (!root.isNull()) {
            // Extract and display specific weather data fields
            double temperature = root["main"]["temp"].asDouble();
            double humidity = root["main"]["humidity"].asDouble();
            string description = root["weather"][0]["description"].asString();

            cout << "Temperature: " << temperature << " K" << endl;
            cout << "Humidity: " << humidity << "%" << endl;
            cout << "Description: " << description << endl;
        }
    }
};

int main() {
    // Weather Data Fetcher
    std::string openWeatherMapApiKey = "your_actual_api_key"; // Replace with your actual API key
    std::string openWeatherMapBaseUrl = "https://api.openweathermap.org/data/2.5/weather";
    WeatherDataFetcher weatherFetcher(openWeatherMapApiKey, openWeatherMapBaseUrl);
    std::string weatherData = weatherFetcher.fetchWeatherData("New York");
    weatherFetcher.displayWeatherData(weatherData);

    return 0;
}