//
// Created by Gebruiker on 2-11-2021.
//

#ifndef SNAKEPROJECT_GRID_H
#define SNAKEPROJECT_GRID_H

class Grid{
private:
    int height = 20;
    int width = 20;
public:
    Grid(int height, int width){
        this -> height = height;
        this -> width = width;
    };
    int get_height();
    int get_width();
    void draw_grid();

};

int Grid::get_height() {
    return height;
}
int Grid::get_width() {
    return width;
}

void Grid::draw_grid(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j <= width; j++) {
            if(j != width){
                cout << "[ ]";
            }
            else{
                cout << endl;
            }
        }


    }
}

#endif //SNAKEPROJECT_GRID_H
