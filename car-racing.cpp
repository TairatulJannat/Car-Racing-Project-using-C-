#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;

int point = 0,TotalMove = 0;
int matrix[8][20];
void drawPoint(int x, int y);
void gotoXY(int x, int y);

class Enemy_Car
{
public:
    int xPos;
    int yPos;
    Enemy_Car()  //Constractor
    {
        xPos=2;
        yPos=-3;
    }

    void appear();
    void draw();
    void move()
    {
        yPos++;
    }
};

class My_Car
{
public:
    int xPos;
    int yPos;
    My_Car()
    {
        xPos=2;
        yPos=16;
    }
    void draw();
    void moveLeft()
    {
        xPos=2;
        TotalMove++;
    }
    void moveRight()
    {
        xPos=5;
        TotalMove++;
    }
    void checkCollusion(Enemy_Car *EC, bool *running);
};

void Enemy_Car::appear()
{
    if(yPos==20)
    {
        int randomNo=rand()%2;
        if(randomNo==0)
        {
            xPos=2;
        }
        else
        {
            xPos=5;
        }
        yPos=-3;
    }
}

void Enemy_Car::draw()
{
    drawPoint(xPos,yPos);
    drawPoint(xPos-1,yPos+1);
    drawPoint(xPos+1,yPos+1);
    drawPoint(xPos,yPos+1);
    drawPoint(xPos,yPos+2);
    drawPoint(xPos-1,yPos+3);
    drawPoint(xPos+1,yPos+3);
    drawPoint(xPos,yPos+3);
}

void My_Car::draw()
{
    drawPoint(xPos,yPos);
    drawPoint(xPos-1,yPos+1);
    drawPoint(xPos+1,yPos+1);
    drawPoint(xPos,yPos+1);
    drawPoint(xPos,yPos+2);
    drawPoint(xPos-1,yPos+3);
    drawPoint(xPos+1,yPos+3);
    drawPoint(xPos,yPos+3);
}

void My_Car::checkCollusion(Enemy_Car *EC, bool *running)
{
    if(EC->xPos==xPos & EC->yPos>13)
        *running=false;

    else
        point++;
}

void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // cursor er possition change nge kore notun possi
}

void drawPoint(int x, int y)
{
    if(y<20 & y>=-0)
    {
        matrix[x][y]=1;
    }
}

void resetBoard()
{
    for(int j=0; j<20; j++)
    {
        for(int i=1; i<7; i++)
        {
            matrix[i][j]=0;
        }
    }
}

void myListener(My_Car *point)
{
    while(1)
    {
        if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0))
            point->moveLeft();

        else if (GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0))
            point->moveRight();
    }
}

void Credit()
{
    gotoXY(24,10);
    cout<<"Womama Islam Ananna"<<endl;
    cout<<"\t\t\t2016-2-60-033"<<endl<<endl;
    gotoXY(24,13);
    cout<<"Tairatul Jannat Tamima"<<endl;
    cout<<"\t\t\t2016-3-60-008"<<endl<<endl;
    gotoXY(24,16);
    cout<<"Bibi Joynab"<<endl;
    cout<<"\t\t\t2017-3-60-031"<<endl;
    gotoXY(20,19);
    cout<<"Press Any Key/Enter TO Return in the Main Menu"<<endl;
    char n;
    gotoXY(20,20);
    cin>>n;
}

void startGame()
{
    My_Car mycar = My_Car();
    Enemy_Car myEnmCar=Enemy_Car();

    thread mySecondThread(myListener, &mycar);  //Thread For My_Car

    bool running=true;
    while(running)             //Game Loop
    {
        gotoXY(10,1);
        cout<<"Total Move: "<<TotalMove;
        gotoXY(10,2);
        cout<<"Your Score: "<<(point-16)/23;
        resetBoard();
        myEnmCar.appear();
        myEnmCar.draw();
        myEnmCar.move();
        mycar.draw();
        mycar.checkCollusion(&myEnmCar,&running);

        for(int j=0; j<20; j++)
        {
            for(int i=0; i<8; i++)
            {
                if(i==0 | i==7)
                {
                    gotoXY(i,j);
                    cout<<"*";
                }
                else if(matrix[i][j]==1)
                {
                    gotoXY(i,j);
                    cout<<"0";
                }
                else
                {
                    gotoXY(i,j);
                    cout<<" ";
                }
            }
        }
        if(TotalMove>10)
            Sleep(250);
        else if(TotalMove>20)
            Sleep(250);
        else
            Sleep(250);

    }
    //The game end
    gotoXY(20,5);
    cout<<"GAME OVER!!! Your Score is: "<<(point-16)/23;
    gotoXY(20,8);
    cout<<"Developed By:\n"<<endl;
    Credit();

    mySecondThread.detach(); // To Kill second thread
}

void main_menu()
{
    gotoXY(6,2);
    cout<<"WELCOME TO OUR SAVE YOUR CAR GAME\n\t\tPress 1 to start the Game.\n\t\t\tUse Right & Left Button to Save Your Car";
}

int main()
{
    int users_choice;
    main_menu();
    while(1)
    {
        gotoXY(8,6);
        cout<<"1. Start Game"<<endl<<"\t2. Exit"<<endl<<"\t3. Developed By"<<endl;
        gotoXY(8,9);
        cin>>users_choice;

        switch(users_choice)
        {
        case 1:
            system("cls");
            startGame();
            system("cls");
            break;
        case 2:
            exit(0);
            break;
        case 3:
            Credit();
            system("cls");
            break;
        default:
            system("cls");
            cout<<"Sorry Wrong Number!!!! Try Again"<<endl;
            break;
        }
    }
    return 0;
}

