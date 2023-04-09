#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// ��������� ��� �������� ���������� � ����������
struct Employee {
    int id;
    char name[10];
    int hours;
};

// ������� ��� ������ ������ � ����������� �� ��������� �����
vector<Employee> readEmployees(const string& filename) {
    vector<Employee> employees;
    ifstream file(filename, ios::in | ios::binary);
    if (!file) {
        cout << "������ ��� �������� ����� readEmployees" << endl;
        return employees;
    }
    Employee employee;

    while (file.read((char*)&employee, sizeof(employee))) {
        employees.push_back(employee);
    }
    file.close();
    return employees;
}

// ������� ��� ���������� �������� ����������
double calculateSalary(const Employee& employee, double hourlyRate) {
    return employee.hours * hourlyRate;
}

// ������� ��� ������ ������ � ����
void writeReport(const string& filename, const vector<Employee>& employees, double hourlyRate) {
    ofstream file(filename);
    if (!file) {
        cout << "������ ��� �������� ����� writeReport" << endl;
        return;
    }
    file << "����� �� ����� \"" << filename << "\"" << endl;
    file << std::left << std::setw(10) << "�����"
        << std::setw(10) << "���"
        << std::setw(10) << "����"
        << std::setw(10) << "��������" << std::endl;
    for (const Employee& employee : employees) {
        double salary = calculateSalary(employee, hourlyRate);
        file << std::left << std::setw(10) << employee.id
            << std::setw(10) << employee.name
            << std::setw(10) << employee.hours
            << std::setw(10) << salary << std::endl;
    }
    file.close();
}

// ������� ��� ��������� ����������� �� ������
bool compareEmployeesById(const Employee& employee1, const Employee& employee2) {
    return employee1.id < employee2.id;
}

int main(int argc, char* argv[]) {

    cout << "!Reporter process start!" << endl;

    setlocale(LC_ALL, "Russian");

    //��������� ���������� ���������� ��������� ������
    if (argc != 4) {
        cerr << "�������������: Reporter <�������� ����> <���� ������> <������ �� ��� ������>" << endl;
        return 1;
    }

    //�������� ��������� ��������� ������
    string inputFilename = argv[1];
    string outputFilename = argv[2];
    double hourlyRate = atof(argv[3]);

    // ������ ������ � ����������� �� ��������� �����
    vector<Employee> employees = readEmployees(inputFilename);

    // ��������� ����������� �� ������
    sort(employees.begin(), employees.end(), compareEmployeesById);

    // ���������� ����� � ����
    writeReport(outputFilename, employees, hourlyRate);

    return 0;
}
