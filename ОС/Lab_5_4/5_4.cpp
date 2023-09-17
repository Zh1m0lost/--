#include <iostream>
#include <Windows.h>
using namespace std;
DWORD WINAPI thread1(LPVOID);
DWORD WINAPI thread2(LPVOID);
HANDLE hMutex;

int main()
{

    try
    {
        hMutex = CreateMutex( // Создает или открывает именованный или неназванный объект мьютекса.
            NULL,             // Указатель на структуру SECURITY_ATTRIBUTES. Если этот параметр равен NULL, дескриптор не может быть унаследован дочерними процессами.
            FALSE,            // Если это значение равно FALSE вызывающий поток не получает права собственности на мьютекс.
            NULL);            // Имя объекта мьютекса. Если значение lpName равно NULL, то объект мьютекса создается без имени.
        if (hMutex == NULL)
            throw 1;
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
        if (WaitForMultipleObjects(      // Ожидает, пока один или все указанные объекты не перейдут в сигнальное состояние или не истечет интервал ожидания. Если функция завершается успешно, возвращаемое значение указывает на событие, вызвавшее возврат функции.
                2,                       // Количество дескрипторов объектов в массиве, на которые указывает lpHandles.
                threads,                 // Массив дескрипторов объектов.
                TRUE,                    // Если этот параметр имеет значение TRUE, то функция возвращает состояние всех объектов в массиве lpHandles.
                10000) != WAIT_OBJECT_0) // 10000 - Интервал ожидания в миллисекундах. WAIT_OBJECT_0 - Если bWaitAll имеет значение TRUE, возвращаемое значение указывает, что состояние всех указанных объектов сигнализируется.
            throw 1;
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
        WaitForSingleObject( // Ожидает, пока указанный объект не окажется в сигнальном состоянии или не истечет интервал ожидания.
            hMutex,
            INFINITE);
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
        ReleaseMutex(hMutex); // Освобождает право собственности на указанный объект мьютекса.
    }
    return 0;
}

DWORD WINAPI thread2(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        WaitForSingleObject(
            hMutex,
            INFINITE);
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
        ReleaseMutex(hMutex);
    }
    return 0;
}
