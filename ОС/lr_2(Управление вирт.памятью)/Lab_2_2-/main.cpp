#include <iostream>
#include <windows.h>

using namespace std;

void state_check(DWORD state) // Проверка состояния страниц
{
  if (state == 0x1000)
    cout << "State: memory commited" << endl;
  if (state == 0x2000)
    cout << "State: memory reserved" << endl;
  if (state == 0x4000)
    cout << "State: memory decommited" << endl;
  if (state == 0x8000)
    cout << "State: memory released" << endl;
}

void protect_check(DWORD protect) // Проверка защиты доступа страниц
{
  if (protect == 0x0001)
    cout << "Protect: page noaccess" << endl;
  if (protect == 0x0002)
    cout << "Protect: page readonly" << endl;
  if (protect == 0x0004)
    cout << "Protect: page readwrite" << endl;
  if (protect == 0x0000)
    cout << "Protect: page is NULL" << endl;
}

int main()
{
  SYSTEM_INFO system_info;                 // Содержит информацию о текущей системе
  GetSystemInfo(&system_info);             // Получает информацию о текущей системе
  DWORD pagesize = system_info.dwPageSize; // Размер страницы
  cout << "Page size: " << pagesize << endl;
  bool error_check;
  //------------------ЗАДАНИЕ 1------------------
  cout << "Enter the number of pages to reserve: ";
  int pages;
  cin >> pages;
  LPVOID p = VirtualAlloc(
      NULL,             // Начальный адрес региона для выделения, при NULL, система определяет, где будет выделен регион
      pages * pagesize, // Размер области в байтах. Если параметр lpAddress равен NULL, то это значение округляется до следующей границы страницы
      MEM_RESERVE,      // Тип выделения памяти. Резервирует диапазон виртуального адресного пространства процесса без выделения какого-либо фактического физического хранилища в памяти или в файле подкачки на диске
      PAGE_READWRITE    // Тип доступа. Разрешает доступ только для чтения или записи к зафиксированной области страниц
  );
  if (p != NULL)
  {
    cout << "Address: " << p << endl;
  }
  else
  {
    cout << "Error of reserving: " << GetLastError();
    return 1;
  }
  //------------------ЗАДАНИЕ 2------------------
  cout << "Enter the number of pages to commit: ";
  int commit_pages;
  cin >> commit_pages;
  cout << "Enter the starting page number to commit:  ";
  int commit_page_start;
  cin >> commit_page_start;
  void *cp = NULL;
  cp = VirtualAlloc(
      p + commit_page_start * pagesize,
      commit_pages * pagesize,
      MEM_COMMIT,    // Выделяет расходы за память (из общего объема памяти и файлов подкачки на диске) для указанных зарезервированных страниц памяти. Эта функция также гарантирует, что при последующем первоначальном обращении вызывающего абонента к памяти ее содержимое будет равно нулю
      PAGE_READWRITE
  );
  if (cp != NULL)
  {
    cout << "Address of commited: " << cp << endl;
  }
  else
  {
    cout << "Error of commiting: " << GetLastError();
    return 1;
  }
  //------------------ЗАДАНИЕ 3------------------
  int num = 5;
  int arr[num] = {1, 2, 3, 4, 5};
  int *cp1 = (int *)cp;
  error_check = memcpy(cp1, arr, num * sizeof(int));
  if (!error_check)
  {
    cout << "Error executing memcpy_s: " << GetLastError() << endl;
    return 1;
  }
  else
  {
    cout << "Copied successfuly: ";
    for (int i = 0; i < num; i++)
      cout << cp1[i] << " ";
    cout << endl;
  }
  //------------------ЗАДАНИЕ 4------------------
  MEMORY_BASIC_INFORMATION info; // Содержит информацию о диапазоне страниц в виртуальном адресном пространстве процесса
  cout << "Info about a commited memory: " << endl;
  size_t error = VirtualQuery( // Извлекает информацию о диапазоне страниц в виртуальном адресном пространстве вызывающего процесса
      cp,                      // Указатель на базовый адрес области запрашиваемых страниц. Это значение округляется до следующей границы страницы. Если lpAddress указывает адрес выше самого высокого адреса памяти, доступного процессу, функция завершается ошибкой ERROR_INVALID_PARAMETER
      &info,                   // Указатель на структуру MEMORY_BASIC_INFORMATION, в которой возвращается информация об указанном диапазоне страниц
      sizeof(info)             // Размер буфера, на который указывает параметр lpBuffer, в байтах
  );
  if (error == 0)
  {
    cout << "VirtualQuery executing error: " << GetLastError();
    return 1;
  }
  state_check(info.State);
  protect_check(info.Protect);

  cout << "Info about memory after commited: " << endl;
  error = VirtualQuery(
      cp + commit_pages * pagesize,
      &info,
      sizeof(info));
  if (error == 0)
  {
    cout << "VirtualQuery executing error: " << GetLastError();
    return 1;
  }
  state_check(info.State);
  protect_check(info.Protect);
  //------------------ЗАДАНИЕ 5------------------
  void *cp2 = NULL;
  cp2 = VirtualAlloc(
      p + (commit_page_start + commit_pages) * pagesize,
      pagesize,
      MEM_COMMIT,
      PAGE_READONLY);
  if (cp2 != NULL)
  {
    cout << "Address of commited 2: " << cp2 << endl;
  }
  else
  {
    cout << "Error of commiting 2: " << GetLastError();
    return 1;
  }
  error = VirtualQuery(
      p + (commit_page_start + commit_pages) * pagesize,
      &info,
      sizeof(info));
  if (error == 0)
  {
    cout << "VirtualQuery 2 executing error: " << GetLastError();
    return 1;
  }
  state_check(info.State);
  protect_check(info.Protect);
  //------------------ЗАДАНИЕ 6------------------
  SIZE_T dwSize;
  cout << "How many pages to return? ";
  cin >> dwSize;
  cout << "Number of page to start decommiting: ";
  cin >> commit_page_start;
  if (!VirtualFree(                         // Выпускает, списывает или освобождает и списывает область страниц в виртуальном адресном пространстве вызывающего процесса.
          p + commit_page_start * pagesize, // Указатель на базовый адрес области освобождаемых страниц
          dwSize,                           // Размер освобождаемой области памяти в байтах
          MEM_DECOMMIT))
    cout << "VirtualFree error: " << GetLastError();
  else
  {
    cout << "Address: " << p + commit_page_start * pagesize << endl;
  }

  error = VirtualQuery(
      p + commit_page_start * pagesize,
      &info,
      sizeof(info));
  if (error == 0)
  {
    cout << "VirtualQuery 3 executing error: " << GetLastError();
    return 1;
  }
  state_check(info.State);
  protect_check(info.Protect);
  //------------------ЗАДАНИЕ 7------------------
  if (!VirtualFree(
          p,
          0,           // Если параметр dwFreeType равен MEM_RELEASE, то этот параметр должен быть равен 0 (нулю).
          MEM_RELEASE) // Эта функция освобождает всю область, зарезервированную при первоначальном вызове выделения VirtualAlloc.
  )
    cout << "VirtualFree error:  " << GetLastError();
  return 0;
}
