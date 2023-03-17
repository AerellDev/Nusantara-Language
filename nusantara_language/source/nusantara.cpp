#include <iostream>
#include <string>
#include <algorithm>
#include <exception>
#include <fstream>
#include <cstdlib>

using namespace std;

//Fungsi untuk mengubah string menjadi lower case
void toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c){ return tolower(c); });
}

//Fungsi untuk mengubah string menjadi upper case
void toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c){ return toupper(c); });
}

int main(int argc, char const *argv[])
{
    //Nama toupper file
    const string nusantaraExtensionFile = ".nl";

    //Nama file
    const string nameFile = argv[1];
    
    //mengubah nama file ke lowercase
    toLowerCase(nameFile);

    //Cek apakah ekstensi file benar
    if(nameFile.find(nusantaraExtensionFile) == string::npos) {
        try
        {
            throw runtime_error("Error : File harus berekstensi .nl");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    //Membaca file perline
    ifstream file(nameFile);

    //Membuat file c++
    ofstream outfile("nusantara_output.cpp");

    if(!file.is_open()) {
        cout << "Error : tidak dapat membuka file" << endl;
        return 1;
    }

    if(!outfile.is_open()) {
        cout << "Error : tidak dapat membuka file" << endl;
        return 1;
    }

    //Menulis file C++
    outfile << "#include <iostream>" << endl;
    outfile << "#include <string>" << endl;
    outfile << "using namespace std;" << endl;
    outfile << "int main() {" << endl;

    string baris;
    while (getline(file, baris)) {

        //Mengabaikan tanda komentar single line
        if(baris.substr(0, 2) != "//") {
            
            //Mengubah angkadesimal menjadi float
            if(baris.substr(0, 12) == "angkadesimal") {
                baris.replace(baris.find("angkadesimal"), 12, "float");
                outfile << baris << endl;
                continue;
            }

            //Mengubah angka menjadi int
            if(baris.substr(0, 5) == "angka") {
                baris.replace(baris.find("angka"), 5, "int");
                outfile << baris << endl;
                continue;
            }

            //Mengubah teks menjadi string
            if(baris.substr(0, 4) == "teks") {
                baris.replace(baris.find("teks"), 4, "string");
                outfile << baris << endl;
                continue;
            }

            //Mengubah karakter menjadi char
            if(baris.substr(0, 8) == "karakter") {
                baris.replace(baris.find("karakter"), 8, "char");
                outfile << baris << endl;
                continue;
            }

            //Mengubah benarsalah menjadi bool
            if(baris.substr(0, 10) == "benarsalah") {
                baris.replace(baris.find("benarsalah"), 10, "bool");
                try
                {
                    if(baris.substr(baris.find("benar"), baris.find("benar") + 5) == "benar;") baris.replace(baris.find("benar"), baris.find("benar") + 4, "true;");
                }
                catch(const std::exception& e)
                {
                    if(baris.substr(baris.find("salah"), baris.find("salah") + 5) == "salah;") baris.replace(baris.find("salah"), baris.find("salah") + 4, "false;");
                }
                outfile << baris << endl;
                continue;
            }

            //Mengubah masukkekonsol(object) menjadi println();
            if(baris.substr(0, 13) == "masukkekonsol") {
                baris.replace(baris.find("masukkekonsol"), 14, "cout << ");
                baris.replace(baris.find(");"), 2, "<< endl;");
                outfile << baris << endl;
                continue;
            }

        }
    }

    outfile << "    return 0;" << endl;
    outfile << "}" << endl;

    file.close();
    outfile.close();

    std::system("g++ ./nusantara_output.cpp -o nusantara_output.exe");
    std::system(".\\nusantara_output.exe");
    std::system("del .\\nusantara_output.cpp");

    return 0;
}