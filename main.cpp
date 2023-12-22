#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string fullname;
    int course;
    string group;
};

/// Функция для сравнения студентов по фамилии (по алфавиту)
bool compareBySurname(const Student &a, const Student &b) {
    //фамилия студента идет первым словом в ФИО
    istringstream issA(a.fullname);
    istringstream issB(b.fullname);

    string surnameA, surnameB;
    issA >> surnameA;
    issB >> surnameB;

    return surnameA < surnameB;
}

/// Функция для сравнения студентов по курсу и группе (по курсу, затем по группе)
bool compareByCourseAndGroup(const Student &a, const Student &b) {
    if (a.course != b.course) {
        return a.course < b.course;
    } else {
        return a.group < b.group;
    }
}

int main() {
    ifstream inputFile("Studens.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return 1;
    }

    vector<Student> students;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        Student student;
        getline(ss, student.fullname, ';');
        ss >> student.course;
        ss.ignore(); //пропуск раздел.
        getline(ss, student.group);
        students.push_back(student);
    }
    inputFile.close();

    ///Сортируем по фамилии
    sort(students.begin(), students.end(), compareBySurname);

    ///Записываем отсортированных студентов в файл "Fio.txt"
    ofstream fioFile("Fio.txt");
    if (!fioFile.is_open()) {
        cout << "Ошибка создания файла Fio.txt." << endl;
        return 1;
    }

    for (const auto &student : students) {
        fioFile << student.fullname << ';' << student.course << ';' << student.group << '\n';
    }
    fioFile.close();




    ///Сортируем по курсу и группе
    sort(students.begin(), students.end(), compareByCourseAndGroup);

    ///Записываем отсортированных студентов в файл "Groups.txt"
    ofstream groupsFile("Groups.txt");
    if (!groupsFile.is_open()) {
        cout << "Ошибка создания файла Groups.txt." << endl;
        return 1;
    }

    for (const auto &student : students) {
        groupsFile << student.fullname << ';' << student.course << ';' << student.group << '\n';
    }
    groupsFile.close();

    cout << "Файлы Fio.txt и Groups.txt созданы." << endl;

    return 0;
}

