//
// Created by Gebruiker on 2-11-2021.
//

#ifndef SNAKEPROJECT_FRUITS_H
#define SNAKEPROJECT_FRUITS_H
#include "grid.h"

class Fruits{
private:
    int xcor;
    int ycor;
public:
    void spawn_fruit(int xcor, int ycor);
    int get_xcor();
    int get_ycor();

};


int Fruits::get_xcor(){
    return xcor;
}
int Fruits::get_ycor(){
    return ycor;
}

void Fruits::spawn_fruit(int xcor, int ycor) {
    this -> xcor = randint(0, 20);
    this -> ycor = randint(0, 20);


}
#endif //SNAKEPROJECT_FRUITS_H
