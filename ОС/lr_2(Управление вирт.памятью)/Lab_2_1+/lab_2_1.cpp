
#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    MEMORYSTATUS ms;
    while(GetAsyncKeyState(0x51) != -32767) // 0x51 - ��� q(��� ������ �� �������) � -32767 ���������� ������� GetAsyncKeyState ��� ������� ������ �������(� ������ ������ q)
    {
    GlobalMemoryStatus(&ms);
    cout << "Total memory: " << (ms.dwTotalPhys/(1024*1024)) << endl; // ����� �������� ���������� ������ � ������
    cout << "Loaded: " << ms.dwMemoryLoad << endl; // ����� �� 0 �� 100, ����������� ��������������� ������� ������������ ���������� ������.
    cout << "Available: " << (ms.dwAvailPhys/(1024*1024)) << endl; // ����� ��������� � ��������� ����� ���������� ������ � ������.
    cout <<"\n\n";
    for(int i=0; i<100; i++) // � ������� 100*10 � Sleep = 1000ms = 1s ���� ����������� ������ ������� � ��� ����������, �� ������� ������� q
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
