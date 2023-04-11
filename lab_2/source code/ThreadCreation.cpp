#include <iostream>
#include <Windows.h>
#include <process.h>

using namespace std;

const int MAX_SIZE = 100;

int arr[MAX_SIZE];
int arraySize;
int min_elem, max_elem;
double avg_elem;

unsigned __stdcall min_max(void* pArguments)
{
    min_elem = arr[0];
    max_elem = arr[0];

    for (int i = 1; i < arraySize; i++)
    {
        if (arr[i] < min_elem)
        {
            min_elem = arr[i];
        }

        if (arr[i] > max_elem)
        {
            max_elem = arr[i];
        }

        Sleep(7);
    }

    cout << "Min element: " << min_elem << endl;
    cout << "Max element: " << max_elem << endl;

    return 0;
}

unsigned __stdcall average(void* pArguments)
{
    int sum = 0;

    for (int i = 0; i < arraySize; i++)
    {
        sum += arr[i];
        Sleep(12);
    }

    avg_elem = (double)sum / arraySize;

    cout << "Average element: " << avg_elem << endl;

    return 0;
}

int main()
{
    cout << "Enter size of array: ";
    cin >> arraySize;

    cout << "Enter elements of array: ";
    for (int i = 0; i < arraySize; i++)
    {
        cin >> arr[i];
    }

    HANDLE hMinMax = (HANDLE)_beginthreadex(NULL, 0, &min_max, NULL, 0, NULL);
    HANDLE hAverage = (HANDLE)_beginthreadex(NULL, 0, &average, NULL, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    for (int i = 0; i < arraySize; i++)
    {
        if (arr[i] == min_elem || arr[i] == max_elem)
        {
            arr[i] = avg_elem;
        }

        cout << arr[i] << " ";
    }
    cout << endl;

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    return 0;
}
