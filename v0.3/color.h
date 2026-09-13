#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
void enableVT() 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void setBG(int color) 
{
    cout << "\033[48;5;" << color << "m";
}

void setFG(int color) 
{
    cout << "\033[38;5;" << color << "m";
}

void reset() 
{
    cout << "\033[0m";
}

void surprise()
{
	system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");
}