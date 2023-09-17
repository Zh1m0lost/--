
#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    MEMORYSTATUS ms;
    while(GetAsyncKeyState(0x51) != -32767) // 0x51 - это q(для выхода из консоли) и -32767 возвращает функция GetAsyncKeyState при нажатии нужной клавиши(в данном случаи q)
    {
    GlobalMemoryStatus(&ms);
    cout << "Total memory: " << (ms.dwTotalPhys/(1024*1024)) << endl; // Объем реальной физической памяти в байтах
    cout << "Loaded: " << ms.dwMemoryLoad << endl; // Число от 0 до 100, указывающее приблизительный процент используемой физической памяти.
    cout << "Available: " << (ms.dwAvailPhys/(1024*1024)) << endl; // Объем доступной в настоящее время физической памяти в байтах.
    cout <<"\n\n";
    for(int i=0; i<100; i++) // в счётчик 100*10 в Sleep = 1000ms = 1s цикл повторяется каждую секунду и идёт бесконечно, до нажатии клавиши q
    {
        if(GetAsyncKeyState(0x51) != -32767)
            {Sleep(100);
        }else {
        return 0;
        }
    }
    }

    return 0;
}
