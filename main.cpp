#include "lib_std_facilities.h"
#include "grid.h"
#include "snake.h"
#include "fruits.h"
#include "conio.h"
#include "windows.h"

//Global variables
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100]; //snake coordinates
int n_tail;
enum eDirection {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls
eDirection dir;

void Setup(){
    gameover = false;
    dir = STOP;
    //display fruit in a random place
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#"; //walls
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; //walls

            if (i == y && j == x)
                cout << "*"; // snake head
            else if (i == fruit_y && j == fruit_x)
                cout << "%"; // fruit
            else {
                bool print = false;
                for (int k = 0; k < n_tail; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        cout << "8"; //snake tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; //play area

            }
            if (j == width - 1)
                cout << "#"; //walls
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) {
        cout << "#"; //walls
    }
    cout << endl;
    cout << "Score:" << score << endl;
}

void game() {
    //assigning the x and y coordinates to the snake, to reference to them later when using the wall detection
    //and in the AI part of the code
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev_2x, prev_2y;
    tail_x[0] = x;
    tail_y[0] = y;
    for (int i = 1; i < n_tail; i++){
        prev_2x = tail_x[i];
        prev_2y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;
    }
    //Stating what the directions are the snake can move and what these directions do
    switch (dir){
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
    if (x >= width){
        x = 0;
    } else if (x < 0){
        x = width - 1;
    }
    if (y >= height){
        y = 0;
    } else if (y < 0){
        y = height - 1;
    }

    //respawning the fruit at a random place on the board when it's eaten
    //also growing the snake tail
    if (x == fruit_x && y == fruit_y){
        score += 10;
        fruit_x = rand() % width;
        fruit_y = rand() % height;
        n_tail++;
    }
    //gameover statements
    for (int i = 0; i < n_tail; i++){
        if (tail_x[i] == x && tail_y[i] == y){
            gameover = true;
            cout << "Game over! Your final score = " << score;
        }
    }
    if (tail_x[0] == width -1 || tail_y[0] == width -1){
        gameover = true;
        cout << "Game over! Your final score = " << score;
    }
    if (tail_x[0] == height -1 || tail_y[0] == height -1){
        gameover = true;
        cout << "Game over! Your final score = " << score;
    }
}

void Input(){
    //Using kbhit and getch from the conio library to register keyboard hits and
    //their respective functions.
    if (_kbhit ()){
        switch (_getch ()){
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
                dir = DOWN;
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
}

void search_algorithm() {
    int current_x = tail_x[0];
    int current_y = tail_y[0];
    int snake_coor[2] = {current_x, current_y};
    int fruit_coor[2] = {fruit_x, fruit_y};
    int target_coor[2] = {fruit_coor[0] - snake_coor[0], fruit_coor[1] - snake_coor[1]};
    //For development, these coordinates were printed on the screen so I could see if
    //everthing was going well

    //cout << "X_fruit : " << fruit_coor[0] << "Y_fruit : " << fruit_coor[1] << endl;
    //cout << "snake_x : " << snake_coor[0] << "snake_y : " << snake_coor[1] << endl;
    //cout << "path_x : " << target_coor[0] << "path_y : " << target_coor[1] << endl;

        //To figure out where the snake should move, it looks at the target coordinates
        //and performs logic based actions according to those coordinates
        if (target_coor[0] < -1){
            if (tail_x[0] - 1 != 0 && tail_x[0] - 1 != width + 2) {
                dir = LEFT;
            }
            else{
                dir = RIGHT;
            }
        }
        if (target_coor[0] > -1){
            if (tail_x[0] + 1 != 0 && tail_x[0] + 1 != width + 2) {
                dir = RIGHT;
            }
            else{
                dir = LEFT;
            }
        }
        if (target_coor[0] == 1 && target_coor[1] != 0) {
            if (target_coor[1] < 1){
                if (tail_y[0] + 1 != -1 && tail_y[1] + 1 != height + 2) {
                    dir = UP;
                }
                else{
                    dir = DOWN;
                }
            }
            if (target_coor[1] > 1){
                if (tail_y[1] + 1 != -1 && tail_y[1] + 1 != height + 2){
                    dir = DOWN;
                }
                else {
                    dir = UP;
                }
            }
        }
}

int main(){
    Setup();
    cout << "Do you want to let the AI play snake? (yes/no) " << endl;
    string choice;
    cin >> choice;

    if (choice == "yes") {
        while (!gameover) {
            Draw();
            Input();
            game();
            search_algorithm();
            Sleep(200);

        }
    }
    if (choice == "no"){
        while (!gameover) {
            Draw();
            Input();
            game();
            Sleep(200);

        }

    }


    return 0;

}


