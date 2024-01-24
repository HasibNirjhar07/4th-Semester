#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
    // Open a file for writing
    std::ofstream outputFile("E:\\CSE-4410-Database-Management-Systems-II-Lab\\Lab2\\data.sql");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing\n";
        return 1;
    }

    // Generate data for Department table
    for (int i = 1; i <= 20; ++i) {
        outputFile << "INSERT INTO Department (ID, Name) VALUES\n";
        outputFile << "  (" << i << ", 'Department" << i << "')";
        outputFile << (i < 20 ? ";\n" : ";\n\n");
    }

    // Generate data for Student table
    for (int i = 1; i <= 2000; ++i) {
        outputFile << "\nINSERT INTO Student (ID, name, dept_ID) VALUES\n";
        outputFile << "  (" << i << ", 'Student" << i << "', " << std::rand() % 20 + 1 << ")";
        outputFile << (i < 2000 ? ";\n" : ";\n\n");
    }

    // Generate data for Course table
    for (int i = 1; i <= 300; ++i) {
        outputFile << "\nINSERT INTO Course (course_code, name, credit, offered_by_dept_ID) VALUES\n";
        outputFile << "  ('C" << i << "', 'Course" << i << "', " << std::rand() % 5 + 1 << ", " << std::rand() % 20 + 1 << ")";
        outputFile << (i < 300 ? ";\n" : ";\n\n");
    }

    // Close the file
    outputFile.close();

    std::cout << "Data has been saved to file\n";

    return 0;
}
