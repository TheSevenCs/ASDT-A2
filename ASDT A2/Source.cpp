#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;

    STUDENT_DATA(const std::string& first, const std::string& last)
        : firstName(first), lastName(last) {}
};

int main() {
    std::string filename = "StudentData.txt";
    std::vector<STUDENT_DATA> students;
    std::ifstream inputFile(filename);
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    while (std::getline(inputFile, line)) {
        std::istringstream ss(line);
        std::string firstName, lastName;


        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName)) {
            firstName.erase(0, firstName.find_first_not_of(" \n\r\t"));
            firstName.erase(firstName.find_last_not_of(" \n\r\t") + 1);
            lastName.erase(0, lastName.find_first_not_of(" \n\r\t"));
            lastName.erase(lastName.find_last_not_of(" \n\r\t") + 1);

            students.emplace_back(firstName, lastName);
        }
    }

    inputFile.close();


#ifdef _DEBUG
    // Print all student information for debugging
    std::cout << "Loaded Student Data:\n";
    for (std::size_t i = 0; i < students.size(); ++i) {
        std::cout << "First Name: " << students[i].firstName
            << ", Last Name: " << students[i].lastName << std::endl;
    }
#endif
    return 0;
}