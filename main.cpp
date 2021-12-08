#include "lib_std_facilities.h"
#include "grid.h"
#include "graphics.h"
#include "snake.h"
#include "fruits.h"
#include "conio.h"
#include <Windows.h>


bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100]; //snake coordinates
int nTail;
enum eDirection {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls
eDirection dir;

void Setup(){
    gameover = false;
    dir = STOP;
    //x = width / 2;
    //y = height / 2;
    //display fruit in a random place
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    score = 0;



}

void Draw(){
    system("cls");
    for(int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl ;
    for (int i = 0; i < height ; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; //walls
            if (i == y && j == x)
                cout << "*"; // snake tail
            else if (i == fruit_y && j == fruit_x )
                cout << "%"; // change it to change the fruit
            else {
                bool print = false;
                for (int k = 0; k< nTail ; k++) {
                    if (tail_x [k] == j && tail_y [k] == i) {
                        cout << "8";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width -1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i< width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl ;
}

void Input(){
    if (_kbhit ()) {
        switch (_getch ()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN ;
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
}

void algorithm() {
    int prevX = tail_x[0];
    int prevY = tail_y[0];
    int prev2X, prev2Y;
    tail_x[0] = x;
    tail_y[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tail_x[i];
        prev2Y = tail_y[i];
        tail_x[i] = prevX;
        tail_y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x >= width) {
        x = 0;
    } else if (x < 0) {
        x = width - 1;
    }
    if (y >= height) {
        y = 0;
    } else if (y < 0) {
        y = height - 1;
    }

    if (x == fruit_x && y == fruit_y) {
        score += 10;
        fruit_x = rand() % width;
        fruit_y = rand() % height;
        nTail++;
    }
    //gameover statements
    for (int i = 0; i < nTail; i++) {
        if (tail_x[i] == x && tail_y[i] == y) {
            gameover = true;
        }
    }
    if (tail_x[0] == width -1 || tail_y[0] == width -1){
        gameover = true;
    }
    if (tail_x[0] == height -1 || tail_y[0] == height -1){
        gameover = true;
    }


}


void search_algorithm() {
    int current_x = tail_x[0];
    int current_y = tail_y[0];
    int target_x = fruit_x;
    int target_y = fruit_y;
    int snake_coor[2] = {current_x, current_y};
    int fruit_coor[2] = {fruit_x, fruit_y};
    int target_coor[2] = {fruit_coor[0] + snake_coor[0], fruit_coor[1] + snake_coor[1]};
    cout << "X_fruit : " << fruit_coor[0] << "Y_fruit : " << fruit_coor[1] << endl;
    cout << "snake_x : " << snake_coor[0] << "snake_y : " << snake_coor[1] << endl;
    cout << "path_x : " << target_coor[0] << "target_y : " << target_coor[1] << endl;
    bool variable_match = target_coor[0] == snake_coor[0];
    cout << variable_match;

    if (target_coor[0] != 0) {
        while (target_coor[0] != 0) {
            if (target_coor[0] < 0) {
                dir = LEFT;
                break;
            }
            if (target_coor[0] > 0) {
                dir = RIGHT;
                break;
            }
            break;
        }
    } else if (target_coor[0] == 0 && target_coor[1] != 0) {
        while (target_coor[1] != 0) {
            if (target_coor[1] < 0) {
                dir = DOWN;
                break;
            }
            if (target_coor[1] > 0) {
                dir = UP;
                break;
            }
            break;
        }
    }
}














int main(){
    Setup();

    while (!gameover) {
        Draw();
        Input ();
        algorithm ();
        search_algorithm();
        Sleep(200);

    }

    return 0;

}
// 20x20 grid
//
