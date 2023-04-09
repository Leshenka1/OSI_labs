#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

bool isNumber(const string& str) //Проверка вводимого пользователем ID на пренадлежение int
{
    try
    {
        int num = std::stoi(str);
    }
    catch (const invalid_argument&)
    {
        return false;
    }
    return true;
}

// Структура для хранения информации о сотруднике
struct employee
{
    int id;            // идентификационный номер сотрудника
    char name[10];      // имя сотрудника
    int hours;       // количество отработанных часов
};



int main(int argc, char* argv[])
{
    cout << "!Creator process start!" << endl;

    // Проверяем, было ли передано имя файла и количество записей в командной строке
    if (argc < 3)
    {
        cout << "Using: " << argv[0] << " <file name> <records amount>" << endl;
        return 1;
    }

    // Получаем имя файла и количество записей из командной строки
    string fileName = argv[1];
    int num_records = atoi(argv[2]);

    // Открываем файл для записи в двоичном режиме
    ofstream outfile(fileName, ios::binary);
    if (!outfile)
    {
        cout << "Could not open file for writing: " << fileName << endl;
        return 1;
    }

    // Запрашиваем информацию о каждом сотруднике и записываем ее в файл
    for (int i = 0; i < num_records; i++)
    {
        employee record;
        std::cout << "Enter the details of employee " << i + 1 << ":" << std::endl;
        std::cout << "ID: ";
        std::cin >> record.id;
        std::cout << "Name: ";
        std::cin >> record.name;
        std::cout << "Hours: ";
        std::cin >> record.hours;
        outfile.write(reinterpret_cast<char*>(&record), sizeof(record));

        // Записываем информацию о сотруднике в файл
    }

    // Закрываем файл
    outfile.close();

    return 0;
}
