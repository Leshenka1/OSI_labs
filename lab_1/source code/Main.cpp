#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<string>
#include <tchar.h>
#include <fstream>
#include <algorithm>



using namespace std;

void coutBinFile(const string& fileName) {
    // Открываем файл в бинарном режиме

    ifstream file(fileName, ios::in | ios::binary);
    if (!file) {
        cout << fileName << endl;
        cout << "Ошибка при открытии файла" << endl;
        return;
    }

    // Определяем размер файла
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);

    // Создаем буфер для чтения файла
    char* buffer = new char[size];

    // Читаем файл в буфер
    file.read(buffer, size);

    // Выводим содержимое файла на консоль
    for (int i = 0; i < size; i++) {
        cout << buffer[i];
    }

    // Освобождаем память и закрываем файл
    delete[] buffer;
    file.close();
}

void coutTxtFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file)
    {
        std::cout << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::cout << "Содержимое файла " << filename << ":" << std::endl;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "!Main process start!" << endl;

    STARTUPINFO sti = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    DWORD exitcode;


    string fileName;
    string recordNum;
    cout << "Enter name of the file and amount of records" << endl;
    cin >> fileName >> recordNum;


    std::string command = ("Creator.exe " + std::string(fileName) + std::string(" ") + std::string(recordNum));
    TCHAR commandLine[MAX_PATH];
    _tcscpy_s(commandLine, MAX_PATH, command.c_str());

    if (!CreateProcess(NULL, commandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &sti, &pi)) {
        cout << "Unable to generate Creator process" << endl;
        return -1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    GetExitCodeProcess(pi.hProcess, &exitcode);
    if (exitcode != STILL_ACTIVE) {
        cout << "!Creator process is done!" << endl;
    }
    else {
        cout << "!Creator process still running!" << endl;
    }

    cout << "Содержимое " << fileName + ":" << endl;
    coutBinFile(fileName);
    cout << endl;


    string employeeData;
    string reportName;
    string salary;      //per hour

    cout << "Enter name of the employee data file, report and salary per hour" << endl;
    cin >> employeeData >> reportName >> salary;
    reportName += ".txt";
     
    ZeroMemory(&sti, sizeof(sti));
    sti.cb = sizeof(sti);
    ZeroMemory(&pi, sizeof(pi));

    command = "Reporter.exe " + std::string(employeeData) + std::string(" ") + reportName + std::string(" ") + std::string(salary);
    _tcscpy_s(commandLine, MAX_PATH, command.c_str());

    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &pi))
    {
        std::cerr << "Error creating process" << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    GetExitCodeProcess(pi.hProcess, &exitcode);
    if (exitcode != STILL_ACTIVE) {
        cout << "Reporter process is done" << endl;
    }
    else {
        cout << "Reporter process still running" << endl;
    }

    cout <<"Cодержимое " << reportName << ":" << endl;
    coutTxtFile(reportName);

    cout << "Press any key to end Main process" << endl;

    _getch();
}