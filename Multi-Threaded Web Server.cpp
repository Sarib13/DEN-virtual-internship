#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

using namespace std;

void handleClient(int clientSocket) {
  char buffer[1024];
  int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

  string request(buffer, bytesRead);
  cout << "Client Request: " << request << endl;

  string filename =
      request.substr(request.find("GET ") + 4, request.find(" HTTP") - 4);
  if (filename == "/")
    filename = "index.html";

  ifstream file("public/" + filename);

  if (file.is_open()) {
    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
    string response =
        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + content;
    send(clientSocket, response.c_str(), response.size(), 0);
    file.close();
  } else {
    string response =
        "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "<title>404 Not Found</title>\n"
        "</head>\n"
        "<body>\n"
        "<h1>404 Not Found</h1>\n"
        "<p>The requested resource was not found.</p>\n"
        "</body>\n"
        "</html>";
    send(clientSocket, response.c_str(), response.size(), 0);
  }

  close(clientSocket);
}

int main() {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    cerr << "Error creating socket" << endl;
    return 1;
  }

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(8080);
  if (bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) ==
      -1) {
    cerr << "Error binding socket" << endl;
    return 1;
  }

  if (listen(serverSocket, 5) == -1) {
    cerr << "Error listening on socket" << endl;
    return 1;
  }

  cout << "Server listening on port 8080..." << endl;

  while (true) {
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocket =
        accept(serverSocket, (sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocket == -1) {
      cerr << "Error accepting client connection" << endl;
      continue;
    }

    thread clientThread(handleClient, clientSocket);
    clientThread.detach();
  }

  close(serverSocket);
  return 0;
}