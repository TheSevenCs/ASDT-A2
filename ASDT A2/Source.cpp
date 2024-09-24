#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;

#ifdef PRE_RELEASE
    std::string email;

    STUDENT_DATA(const std::string& first, const std::string& last, const std::string& email)
        : firstName(first), lastName(last), email(email) {}
#else
    STUDENT_DATA(const std::string& first, const std::string& last)
        : firstName(first), lastName(last) {}
#endif
};

int main() {
#ifdef PRE_RELEASE
    std::cout << "Running in Pre-Release mode.\n";
    std::string filename = "StudentData_Emails.txt"; // File for pre-release
#else
    std::cout << "Running in Standard mode.\n";
    std::string filename = "StudentData.txt"; // File for standard
#endif

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

#ifdef PRE_RELEASE
        std::string email; // For pre-release mode, we need to read emails
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName, ',') && std::getline(ss, email)) {
#else
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName)) {
#endif
            // Trim whitespace
            firstName.erase(0, firstName.find_first_not_of(" \n\r\t"));
            firstName.erase(firstName.find_last_not_of(" \n\r\t") + 1);
            lastName.erase(0, lastName.find_first_not_of(" \n\r\t"));
            lastName.erase(lastName.find_last_not_of(" \n\r\t") + 1);

#ifdef PRE_RELEASE
            email.erase(0, email.find_first_not_of(" \n\r\t"));
            email.erase(email.find_last_not_of(" \n\r\t") + 1);
            students.emplace_back(firstName, lastName, email);
#else
            students.emplace_back(firstName, lastName);
#endif
        }
        }

    inputFile.close();

#ifdef _DEBUG
    // Print all student information for debugging
    std::cout << "Loaded Student Data:\n";
    for (std::size_t i = 0; i < students.size(); ++i) {
        std::cout << "First Name: " << students[i].firstName
            << ", Last Name: " << students[i].lastName;

#ifdef PRE_RELEASE
        std::cout << ", Email: " << students[i].email;
#endif
        std::cout << std::endl;
    }
#endif

    return 0;
    }
