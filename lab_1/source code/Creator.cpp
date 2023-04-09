#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

bool isNumber(const string& str) //�������� ��������� ������������� ID �� ������������� int
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

// ��������� ��� �������� ���������� � ����������
struct employee
{
    int id;            // ����������������� ����� ����������
    char name[10];      // ��� ����������
    int hours;       // ���������� ������������ �����
};



int main(int argc, char* argv[])
{
    cout << "!Creator process start!" << endl;

    // ���������, ���� �� �������� ��� ����� � ���������� ������� � ��������� ������
    if (argc < 3)
    {
        cout << "Using: " << argv[0] << " <file name> <records amount>" << endl;
        return 1;
    }

    // �������� ��� ����� � ���������� ������� �� ��������� ������
    string fileName = argv[1];
    int num_records = atoi(argv[2]);

    // ��������� ���� ��� ������ � �������� ������
    ofstream outfile(fileName, ios::binary);
    if (!outfile)
    {
        cout << "Could not open file for writing: " << fileName << endl;
        return 1;
    }

    // ����������� ���������� � ������ ���������� � ���������� �� � ����
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

        // ���������� ���������� � ���������� � ����
    }

    // ��������� ����
    outfile.close();

    return 0;
}
