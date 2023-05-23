#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

class Student {
private:
    std::string Nazwisko;
    std::string Imie;
    std::string NrAlbumu;
    std::string Grupa;
    int Rok;

public:
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Nazwisko: " << student.Nazwisko << std::endl;
        os << "Imie: " << student.Imie << std::endl;
        os << "Nr albumu: " << student.NrAlbumu << std::endl;
        os << "Grupa: " << student.Grupa << std::endl;
        os << "Rok: " << student.Rok << std::endl;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Student& student) {
        std::cout << "Podaj nazwisko: ";
        is >> student.Nazwisko;
        std::cout << "Podaj imie: ";
        is >> student.Imie;
        std::cout << "Podaj nr albumu: ";
        is >> student.NrAlbumu;
        std::cout << "Podaj grupe: ";
        is >> student.Grupa;
        std::cout << "Podaj rok: ";
        is >> student.Rok;
        return is;
    }
    friend std::ofstream& operator<<(std::ofstream& ofs, const Student& student) {
        ofs << student.Nazwisko << " "
            << student.Imie << " "
            << student.NrAlbumu << " "
            << student.Grupa << " "
            << student.Rok << std::endl;
        return ofs;
    }
    friend std::ifstream& operator>>(std::ifstream& ifs, Student& student) {
        ifs >> student.Nazwisko >> student.Imie >> student.NrAlbumu >> student.Grupa >> student.Rok;
        return ifs;
    }
    bool operator==(const Student& other) const {
        return NrAlbumu == other.NrAlbumu;
    }
    static bool isThirdYear(const Student& student) {
        return student.Rok == 3;
    }
};

int main() {
    std::vector<Student> students;
    std::ofstream outfile("students.txt");
    if (outfile.is_open()) {
        Student student;
        while (std::cin >> student) {
            outfile << student;
            students.push_back(student);
            std::cout << "Student dodany.\n";
            std::cout << "Dodaj kolejnego studenta (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice != 'y')
                break;
        }
        outfile.close();
    }
    std::ifstream infile("students.txt");
    if (infile.is_open()) {
        Student student;
        std::cout << "\nWczytywanie studentow:\n";
        while (infile >> student) {
            std::cout << student;
        }
        infile.close();
    }
    std::cout << "\nWszyscy studenci:\n";
    std::for_each(students.begin(), students.end(), [](const Student& student) {
        std::cout << student << std::endl;
    });
    int count = std::count_if(students.begin(), students.end(), Student::isThirdYear);
    std::cout << "\nLiczba studentow 3 roku: " << count << std::endl;
    return 0;
}