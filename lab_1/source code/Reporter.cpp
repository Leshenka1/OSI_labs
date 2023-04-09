#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Структура для хранения информации о сотруднике
struct Employee {
    int id;
    char name[10];
    int hours;
};

// Функция для чтения данных о сотрудниках из бинарного файла
vector<Employee> readEmployees(const string& filename) {
    vector<Employee> employees;
    ifstream file(filename, ios::in | ios::binary);
    if (!file) {
        cout << "Ошибка при открытии файла readEmployees" << endl;
        return employees;
    }
    Employee employee;

    while (file.read((char*)&employee, sizeof(employee))) {
        employees.push_back(employee);
    }
    file.close();
    return employees;
}

// Функция для вычисления зарплаты сотрудника
double calculateSalary(const Employee& employee, double hourlyRate) {
    return employee.hours * hourlyRate;
}

// Функция для записи отчета в файл
void writeReport(const string& filename, const vector<Employee>& employees, double hourlyRate) {
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка при открытии файла writeReport" << endl;
        return;
    }
    file << "Отчет по файлу \"" << filename << "\"" << endl;
    file << std::left << std::setw(10) << "Номер"
        << std::setw(10) << "Имя"
        << std::setw(10) << "Часы"
        << std::setw(10) << "Зарплата" << std::endl;
    for (const Employee& employee : employees) {
        double salary = calculateSalary(employee, hourlyRate);
        file << std::left << std::setw(10) << employee.id
            << std::setw(10) << employee.name
            << std::setw(10) << employee.hours
            << std::setw(10) << salary << std::endl;
    }
    file.close();
}

// Функция для сравнения сотрудников по номеру
bool compareEmployeesById(const Employee& employee1, const Employee& employee2) {
    return employee1.id < employee2.id;
}

int main(int argc, char* argv[]) {

    cout << "!Reporter process start!" << endl;

    setlocale(LC_ALL, "Russian");

    //Проверяем количество аргументов командной строки
    if (argc != 4) {
        cerr << "Использование: Reporter <исходный файл> <файл отчета> <оплата за час работы>" << endl;
        return 1;
    }

    //Получаем аргументы командной строки
    string inputFilename = argv[1];
    string outputFilename = argv[2];
    double hourlyRate = atof(argv[3]);

    // Читаем данные о сотрудниках из бинарного файла
    vector<Employee> employees = readEmployees(inputFilename);

    // Сортируем сотрудников по номеру
    sort(employees.begin(), employees.end(), compareEmployeesById);

    // Записываем отчет в файл
    writeReport(outputFilename, employees, hourlyRate);

    return 0;
}
