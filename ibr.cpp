#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

enum Direction
{
    Top = 1,
    Down,
    Right,
    Left
};

struct Map
{
    int Width, Height, FruitX, FruitY;
} map1;

struct Snake
{
    int HeadX, HeadY, Tail_N, Tail_X[50], Tail_Y[50];
    Direction Dir;
} snake1;

struct Player
{
    int Score;
    bool Lose;
} player1;

void shift_right(int arr[], int size);
void generate_fruit();
void setup();
void draw();
void input();
void move();

int main()
{
    setup();
    while (!player1.Lose)
    {
        draw();
        input();
        move();
        // Sleep(50);
    }
    cout << endl;
    system("pause");
    return 0;
}

void shift_right(int arr[], int size)
{
    for (int i = size - 2; i >= 0; i--)
        arr[i + 1] = arr[i];
}

void generate_fruit()
{
    srand(time(NULL));
    map1.FruitX = rand() % (map1.Width - 2) + 1;
    map1.FruitY = rand() % (map1.Height - 2) + 1;
}

void setup()
{
    map1.Width = 40;
    map1.Height = 20;
    generate_fruit();

    snake1.HeadX = map1.Width / 2;
    snake1.HeadY = map1.Height / 2;
    snake1.Tail_N = 0;

    player1.Score = 0;
    player1.Lose = false;
}

void draw()
{
    system("cls");
    for (int i = 0; i < map1.Height; i++)
    {
        for (int j = 0; j < map1.Width; j++)
        {
            if (i == 0 || i == map1.Height - 1)
                cout << "#";
            else if (j == 0 || j == map1.Width - 1)
                cout << "#";
            else if (i == snake1.HeadY && j == snake1.HeadX)
                cout << "O";
            else if (i == map1.FruitY && j == map1.FruitX)
                cout << "@";
            else
            {
                bool printed = false;
                for (int z = 0; z < snake1.Tail_N; z++)
                {
                    if (snake1.Tail_X[z] == j && snake1.Tail_Y[z] == i)
                    {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }
                if (!printed)
                    cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Player Score :  " << player1.Score;
}

void input()
{
    if (_kbhit)
    {
        char c = _getch();
        switch (c)
        {
        case 'w':
            snake1.Dir = Top;
            break;
        case 's':
            snake1.Dir = Down;
            break;
        case 'd':
            snake1.Dir = Right;
            break;
        case 'a':
            snake1.Dir = Left;
            break;
        case 'x':
            exit(0);

        default:
            break;
        }
    }
}

void move()
{
    shift_right(snake1.Tail_X, 50);
    shift_right(snake1.Tail_Y, 50);
    snake1.Tail_X[0] = snake1.HeadX;
    snake1.Tail_Y[0] = snake1.HeadY;

    switch (snake1.Dir)
    {
    case Top:
        snake1.HeadY--;
        break;
    case Down:
        snake1.HeadY++;
        break;
    case Right:
        snake1.HeadX++;
        break;
    case Left:
        snake1.HeadX--;
        break;
    }

    if (snake1.HeadY >= map1.Height || snake1.HeadY <= 0 || snake1.HeadX >= map1.Width || snake1.HeadX <= 0)
        player1.Lose = true;
    if (snake1.HeadX == map1.FruitX && snake1.HeadY == map1.FruitY)
    {
        generate_fruit();
        player1.Score += 1;
        snake1.Tail_N++;
    }
    
