#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

int Score=0;

void PrintGame(int Array[4][4])
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i=0, j=0, n=14;
    for (int y=0; (i<4&&j<4); y++)
    {
        SetConsoleTextAttribute(hConsole, n-=2);
        for (int x=0; x<33; x++)
            cout << "-";
        cout << endl;
        cout << "|   " << Array[i][j]  << "   |   " << Array[i][j+1] << "   |   " << Array[i][j+2] << "   |   " << Array[i][j+3] << "   |" << endl;
        j=0;
        i++;
    }
    for (int x=0; x<33; x++)
        cout << "-";
    SetConsoleTextAttribute(hConsole, 13);
    cout << endl << "Score: " << Score << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl << "Use these to move number -_- :" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "     w" << endl << " a   s   d" << endl;
    SetConsoleTextAttribute(hConsole, 14);
    cout << "Press M to Exit the game :(" << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void GenerateNumber(int Array[4][4])
{
    bool flag = true;
    while(flag)
    {
        flag = false;
        int RandomI1 = rand() % 4;
        int RandomJ1 = rand() % 4;
        int RandomI2 = rand() % 4;
        int RandomJ2 = rand() % 4;
        int Random2to4 = rand() % 5;

        bool flags [4][4] = {0};

        if ((Random2to4 < 4) && Array[RandomI1][RandomJ1]==0)
        {
            Array[RandomI1][RandomJ1]=2;
            return;
        }
        else
        {
            flag = true;
            flags[RandomI1][RandomJ1] = true;
        }
        if ((Random2to4 == 4) && Array[RandomI2][RandomJ2]==0)//I2 and J2 are changed
        {
            Array[RandomI2][RandomJ2]=4;
            return;
        }
        else
        {
            flag = true;
            flags [RandomI2][RandomJ2] = true;
        }
        for(int i=0 ; i< 4 ; i++)
        {
            for(int j = 0 ; j< 4 ; j++)
            {
                if(!flags[i][j])
                {
                    flag = true;
                }
                else
                {
                    flag = false;
                }
            }
        }
    }
}

int MoveUpDown(char Key, int Array[4][4])
{
    int Switcher=1;
    if (Key=='w')
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                if(!Array[j][i])
                    for(int k=j+1; k<4; k++)
                        if(Array[k][i])
                        {
                            Array[j][i]=Array[k][i];
                            Array[k][i]=0;
                            break;
                        }

        //Update the table :P
        for(int i=0; i<4; i++)
            for(int j=0; j<3; j++)
                if(Array[j][i]&&Array[j][i]==Array[j+1][i])
                {
                    Switcher=0;
                    Array[j][i]+=Array[j+1][i];
                    Array[j+1][i]=0;
                    Score+=(((log2(Array[j][i]))-1)*Array[j][i]);
                }
    }

    if (Key=='s')
    {
        for(int i=0; i<4; i++)
            for(int j=3; j>=0; j--)
                if(!Array[j][i])
                    for(int k=j-1; k>=0; k--)
                        if(Array[k][i])
                        {
                            Array[j][i]=Array[k][i];
                            Array[k][i]=0;
                            break;
                        }
        //Update the table :P
        for(int i=0; i<4; i++)
            for(int j=3; j>0; j--)
                if(Array[j][i]&&Array[j][i]==Array[j-1][i])
                {
                    Switcher=0;
                    Array[j][i]+=Array[j-1][i];
                    Array[j-1][i]=0;
                    Score+=(((log2(Array[j][i]))-1)*Array[j][i]);
                }
    }
}

void MoveRightLeft(char Key, int Array[4][4])
{
    int Switcher=1;
    if (Key=='a')
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                if(!Array[i][j])
                    for(int k=j+1; k<4; k++)
                        if(Array[i][k])
                        {
                            Array[i][j]=Array[i][k];
                            Array[i][k]=0;
                            break;
                        }
        //Update the table :P
        for(int i=0; i<4; i++)
            for(int j=0; j<3; j++)
                if(Array[i][j]&&Array[i][j]==Array[i][j+1])
                {
                    Switcher=0;
                    Array[i][j]+=Array[i][j+1];
                    Array[i][j+1]=0;
                    Score+=((log2(Array[i][j]))-1)*Array[i][j];
                }
    }
    if (Key=='d')
    {
        for(int i=0; i<4; i++)
            for(int j=3; j>=0; j--)
                if(!Array[i][j])
                    for(int k=j-1; k>=0; k--)
                        if(Array[i][k])
                        {
                            Array[i][j]=Array[i][k];
                            Array[i][k]=0;
                            break;
                        }
        //Update the table :P
        for(int i=0; i<4; i++)
            for(int j=3; j>0; j--)
                if(Array[i][j]&&Array[i][j]==Array[i][j-1])
                {
                    Switcher=0;
                    Array[i][j]+=Array[i][j-1];
                    Array[i][j-1]=0;
                    Score+=(((log2(Array[i][j]))-1)*Array[i][j]);
                }
    }
}

void SelectionSort(int Array[], int Size)
{
    for (int i=0; i<Size; i++)
        for (int j=0; j<Size; j++)
            if (Array[i]>Array[j])
                swap (Array[i], Array[j]);
}
bool Lost (char Key, int Array[4][4])
{
    int Array1[4][4]= {0}, Array2[4][4]= {0};
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            Array2[i][j] = Array[i][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            Array1[i][j] = Array[i][j];
    Key='w';
    MoveUpDown(Key, Array1);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (Array2[i][j]!=Array1[i][j])
                return false;
    //===================================================================
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            Array2[i][j] = Array1[i][j];
    Key='s';
    MoveUpDown(Key, Array1);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (Array2[i][j]!=Array1[i][j])
                return false;
    //===================================================================
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            Array2[i][j] = Array1[i][j];
    Key='a';
    MoveRightLeft(Key, Array1);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (Array2[i][j]!=Array1[i][j])
                return false;
    //===================================================================
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            Array2[i][j] = Array1[i][j];
    Key='d';
    MoveRightLeft(Key, Array1);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (Array2[i][j]!=Array[i][j])
                return false;
    return true;
}

void Scoreboard(int Score)
{
    int x=0, sum[9]= {0};
    string line;
    int lines [100] = {0};
    ifstream iHighScores("Scores.txt", ios::app);
    if (iHighScores.is_open())
    {
        cout << "HighScores: " << endl;
        int i = 0;
        while(getline(iHighScores,line))
        {
//            cout << i+1 <<". "<< line << endl;
            stringstream convert;
            convert << line;
            convert >> lines[i];
            i++;
        }
        SelectionSort(lines, 100);
        for (int i=0; i<10; i++)
            cout << i+1 << ". " << lines[i] << endl;
        iHighScores.close();
    }

    else
        cout << "Unable to open the file" << endl;

}

void Gameplay()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int Array[4][4]= {0};
//    Array[0][0]=2;
//    Array[1][0]=2;
//    Array[2][0]=2;
//    Array[3][0]=2;
    char Key;


    GenerateNumber(Array);
    while(1)
    {

        if(Lost(Key, Array))
        {
            ofstream HighScores("Scores.txt", ios::app);
            if(HighScores.is_open())
            {
                HighScores << Score << endl;
                HighScores.close();
            }
            else
                cout << "Unable to open file" << endl;
            SetConsoleTextAttribute(hConsole, 10);
            cout << "Your Score is: " << Score << endl;
            cout << "Still a NOOB =)) " << endl;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "Game Over!" << endl;
            //exit(0);
            while(true);
        }

        GenerateNumber(Array);
        PrintGame(Array);
        Key=getch();



        if (Key=='w')
        {
            MoveUpDown(Key, Array);
            system("cls");
        }
        else if (Key=='s')
        {
            MoveUpDown(Key, Array);
            system("cls");
        }
        else if (Key=='a')
        {
            MoveRightLeft(Key, Array);
            system("cls");
        }
        else if (Key=='d')
        {
            MoveRightLeft(Key, Array);
            system("cls");
        }
        else if (Key=='m')
        {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "Thanks for Playing! Good Luck :)"<< endl;
            exit(1);
        }
        else
        {
            PrintGame(Array);
            system("cls");
        }
    }
//    system("cls");
}

void StartUpMenu()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int num, MenuList;
    SetConsoleTextAttribute(hConsole, 14);
    cout << "WELCOME TO 2048 GAME :)" << endl;
    cout << "Choose what to do:" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "1. Play Game" << endl << "2. HighScores" << endl << "3. Quit" << endl;
    num=getch();
    while(1)
    {
        switch(num)
        {
        case '0':
        {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "Thanks for Playing! Good Luck :)"<< endl;
            exit(0);
            break;
        }
        case '1':
            system("cls");
            Gameplay();
            break;
        case '2':
            system("cls");
            cout << "   HIGHSCORE Menu" << endl;
            Scoreboard(Score);
            SetConsoleTextAttribute(hConsole, 14);
            cout << "Press 0 to go back to Main Menu" << endl;
            cout << "   1. Play !" << endl;
            cout << "   3. Exit !" << endl;
            num=getch();
            if(MenuList == 1)
                num = 1;
            if(MenuList == 3)
                num = 3;
            if (MenuList == 0)
                num = 0;
            break;
        case '3':
            SetConsoleTextAttribute(hConsole, 10);
            cout << "Thanks for Playing! Good Luck :)"<< endl;
            exit(1);
            break;
        default:
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Invalid Number :|" << endl ;
            num=getch();
        }
        }
    }
}

int main()
{
    srand(time(NULL));
    StartUpMenu();
//    for (int i=0; i<4; i++)
//        for (int j=0; j<4; j++)
//            cout << "Array[" << i <<"][" << j <<"]=" << ArrayNumber[i][j]<< endl;

    return 0;
}
