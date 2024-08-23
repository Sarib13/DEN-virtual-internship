#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int compressor(const string &inputFile, const string &outputFile ) {

    ifstream in(inputFile);
    ofstream out(outputFile);

    if(!in.is_open() || !out.is_open()) {
        cout << "Failed to open file/s" << endl;
        return 1;
    }
    char first_char, next_char;
    int count = 1;

    in.get(first_char);
    while(in.get(next_char)) {
        if(first_char == next_char) {
            count++ ;
        }
        else {
            out.put(first_char);
            out << count;
            first_char = next_char;
            count = 1;
        }
    }

    out.put(first_char);
    out << count;

    in.close();
    out.close();

    cout << "successfully compressed the given file" << endl;
    return 0;
} 

void decompressor(const string &inputFile, const string &outputFile) {

    ifstream in(inputFile);
    ofstream out(outputFile);

    if(!in.is_open() && !out.is_open()) {
        cout << "Failed to open file/s" << endl;
        return;
    }

    char first_char;
    int count;

    while (in.get(first_char) && in >> count){

        for(int i = 0; i < count; i++){
            out.put(first_char);
        }
    }
    in.close();
    out.close();

    cout << "successfully decompressed the file" << endl;
    return;
}

int main () {
    string name;
cout << "Enter the name of file you want to compress. remember to add \".txt\" after file name." << endl;
cin >> name;
string originalFile = name;
string compressedFile = "compressed_"+name;
string decompressedFile = "decompressed_"+name;

int r = compressor(originalFile, compressedFile);
if(r == 1){
    cout << "Try again";
    return 0;
}

char choice;
cout << "Do you want to decompress file?" << endl;
cout << "if yes enter y" << endl;
cin >> choice;
if(choice = 'y'){
decompressor(compressedFile, decompressedFile);
}
}