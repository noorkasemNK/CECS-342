// due 1020
//I used claude code for debugging and helping with compiling, I sed previous notes, and previous files, I asked google questions and used answers from gemini overvoew, I used w3schools, stack overflow
//I sued macOS, vs code, downlaoded the compiler on extension/vscode, c++ apple clang, c++17, C# .NET SDK, homebrew to downdlaod and install
//all of my libraries
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


struct Person {
    std:: string name;
    int age;

};

template <typename T, typename Compare = std::less<T>>
std:: vector<T> genericSort(std::vector<T> values, Compare comesBefore = Compare{})
{
    std::sort(values.begin(), values.end(), comesBefore);
    return values;
}
//ascesnsion
using NumbersAscending = std::less<double>;

bool byName(const Person& a, const Person& b) {
    return a.name < b.name;
}

bool byAgeDescThenName(const Person& a, const Person& b) {
    if (a.age != b.age) { 
        return a.age > b.age; 
    }
    return a.name < b.name; 

}


void printHeader(const std::string& title) {
    std::cout << "\n" << title << "\n" << std::string(title.size(), '-') << "\n";
}

void print(const std::vector<double>& numbers) {
    std::cout <<std::fixed << std::setprecision(2);
    for (std::size_t i=0; i<numbers.size(); ++i) 
        std::cout << (i ? "," : "") << numbers [i];
    std::cout <<"\n";
    //question mark means if-else
}

void print(const std::vector<Person>& people) {
    for (const auto& p : people)
    std::cout << " " << std::left << std::setw(10) << p.name <<p.age << "\n";

}

//run it all in main
int main() {
    const std:: vector<double> numbers = {
        645.41, 37.59, 76.41, 5.31, -34.23, 1.11,
        1.10, 23.46, 635.47, -876.32, 467.83, 62.25
    };
    const std::vector<Person> people = {
         {"Hal", 20},      {"Susann", 31},  {"Dwight", 19},   {"Kassandra", 21},
        {"Lawrence", 25}, {"Cindy", 22},   {"Cory", 27},     {"Mac", 19},
        {"Romana", 27},   {"Doretha", 32}, {"Danna", 20},    {"Zara", 23},
        {"Rosalyn", 26},  {"Risa", 24},    {"Benny", 28},    {"Juan", 33},
        {"Natalie", 25}
    };

    std::cout << "=== Generic sorting in C++ ===\n";

    printHeader("1) Numbers - ascending");
    print(genericSort(numbers, NumbersAscending{}));

    printHeader("2) People - alphabetical by name");
    print(genericSort(people, byName));
    printHeader("3) People -age descending then alphabetical by name");
    print(genericSort(people, byAgeDescThenName));

    return 0;
    }
