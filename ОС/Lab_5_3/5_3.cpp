#include "main_dll.h"
using namespace std;
CRITICAL_SECTION cs; // Объект критического раздела.

int main()
{
    InitializeCriticalSection(&cs); // Инициализирует объект критического раздела.
    try
    {
        HANDLE ThreadOne = CreateThread( // Функция CreateThread создает поток, который выполняется в пределах виртуального адресного пространства вызывающего процесса.
            NULL,                        // Дескриптор защиты. Если lpThreadAttributes является значением ПУСТО (NULL), дескриптор не может быть унаследован.
            0,                           // Начальный размер стека. Если это значение нулевое, новый поток использует по умолчанию размер стека исполняемой программы.
            thread1,                     // Функция потока. Указатель на определяемую программой функцию типа LPTHREAD_START_ROUTINE, код которой исполняется потоком и обозначает начальный адрес потока.
            NULL,                        // Параметр потока. Указатель на переменную, которая передается в поток.
            0,                           // Опции создания. Если это значение нулевое, поток запускается немедленно после создания. В это время, никакие другие значения не поддерживаются.
            NULL);                       // Идентификатор потока. Указатель на переменную, которая принимает идентификатор потока. Если этот параметр имеет значение ПУСТО (NULL), идентификатор потока не возвращается.
        if (!ThreadOne)
            throw 1;
        HANDLE ThreadTwo = CreateThread(
            NULL,
            0,
            thread2,
            NULL,
            0,
            NULL);
        if (!ThreadTwo)
            throw 1;
        HANDLE threads[2] = {ThreadOne, ThreadTwo};
        if (!threads)
            throw 1;
        if (WaitForMultipleObjects(         // Ожидает, пока один или все указанные объекты не перейдут в сигнальное состояние или не истечет интервал ожидания. Если функция завершается успешно, возвращаемое значение указывает на событие, вызвавшее возврат функции.
                2,                          // Количество дескрипторов объектов в массиве, на которые указывает lpHandles.
                threads,                    // Массив дескрипторов объектов.
                TRUE,                       // Если этот параметр имеет значение TRUE, то функция возвращает состояние всех объектов в массиве lpHandles.
                INFINITE) != WAIT_OBJECT_0) // INFINITE - Интервал ожидания в миллисекундах. WAIT_OBJECT_0 - Если bWaitAll имеет значение TRUE, возвращаемое значение указывает, что состояние всех указанных объектов сигнализируется.
            throw 1;
        DeleteCriticalSection(&cs); // Освобождает все ресурсы, используемые неизвестным объектом критического раздела.
    }
    catch (...)
    {
        cout << "Error number: " << GetLastError() << endl;
        return 0;
    }
    return 0;
}

DWORD WINAPI thread1(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        EnterCriticalSection(&cs); // Ожидает получения права собственности на указанный объект критического сечения. Функция возвращается, когда вызывающему потоку предоставляется право собственности.
        cout << "F";
        Sleep(100);
        cout << "i";
        Sleep(100);
        cout << "r";
        Sleep(100);
        cout << "s";
        Sleep(100);
        cout << "t";
        Sleep(100);
        cout << " ";
        Sleep(100);
        cout << "t";
        Sleep(100);
        cout << "h";
        Sleep(100);
        cout << "r";
        Sleep(100);
        cout << "e";
        Sleep(100);
        cout << "a";
        Sleep(100);
        cout << "d" << endl;
        Sleep(100);
        LeaveCriticalSection(&cs); // Освобождает право собственности на указанный объект критического раздела.
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI thread2(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        EnterCriticalSection(&cs);
        cout << "S";
        Sleep(100);
        cout << "e";
        Sleep(100);
        cout << "c";
        Sleep(100);
        cout << "o";
        Sleep(100);
        cout << "n";
        Sleep(100);
        cout << "d";
        Sleep(100);
        cout << " ";
        Sleep(100);
        cout << "t";
        Sleep(100);
        cout << "h";
        Sleep(100);
        cout << "r";
        Sleep(100);
        cout << "e";
        Sleep(100);
        cout << "a";
        Sleep(100);
        cout << "d" << endl;
        Sleep(100);
        LeaveCriticalSection(&cs);
        Sleep(1);
    }
    return 0;
}
