#include <time.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;


void wait( int seconds )
{
    clock_t end_wait;
    end_wait = clock() + seconds * CLOCKS_PER_SEC;
    while( clock() < end_wait ) { }
}

void gotoxy(const int x, const int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(hCon, coord);
}

int main()
{
    cout <<"\t\t\t\t\t\tOff-Comp"<<endl<<endl<<endl;

    string names[3];
    names[0] = "hours";
    names[1] = "minutes";
    names[2] = "seconds";

    string input[3];
    int units[3];
    string ex_zeroes[3];
    int y = 11;
    bool input_repeat;

    for(int i=0; i<3; i++)
    {
        do
        {
            input_repeat = false;
            if (i > 0)
                cout <<"(Stage "<<i+1<<"/3"<<") "<<"Insert a number of "<<names[i]<<" (0-59)"<<": ";
            else
                cout <<"(Stage "<<i+1<<"/3"<<") "<<"Insert a number of "<<names[i]<<" (0-99)"<<": ";
            cin >> input[i];
            try
            {
                units[i] = stoi(input[i]);
            }

            catch(invalid_argument& e )
            {
                cout << "Invalid input!"<<endl<<endl;
                y += 3;
                input_repeat = true;
            }

            if (!input_repeat)
            {
                if (units[i] < 0 || (units[i] > 59 && i > 0) || (units[i] > 99 && i == 0))
                {
                    cout << "Out of range!"<<endl<<endl;
                    y += 3;
                    input_repeat = true;
                }
            }

        }while(input_repeat == true);

    }

    for(int i=3600*units[0] + 60*units[1] + units[2]; i > 0; i--)
    {
        gotoxy(0, y);

        for(int j=0; j<3; j++)
        {
            if (units[j] < 10)
                ex_zeroes[j] = "0";
            else
                ex_zeroes[j] = "";
        }


        cout <<"The computer will be shut down in: "<<ex_zeroes[0]<<units[0]<<":"<<ex_zeroes[1]<<units[1]<<":"<<ex_zeroes[2]<<units[2];

        units[2] -= 1;
        if (units[2] < 0)
        {
            units[1] -= 1;
            if (units[1] < 0)
            {
                units[0] -= 1;
                units[1] += 60;
            }
            units[2] += 60;
        }

        wait( 1 );
    }

    gotoxy(0, y);
    cout <<"The computer will be shut down in: 00:00:00"<<endl;
    system("shutdown -f -s");
    getch();
}
