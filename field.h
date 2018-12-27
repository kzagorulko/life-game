#ifndef FIELD_H
#define FIELD_H

#include <map>
#include <ctime>
#include <iostream>
using namespace std;

class Field
{
private:
    // размеры поля по ширине и высоте
    int heightOfField, widthOfField;
    // двумерный массив, в котором будет храниться информация о живых и неживых клетках
    int **field;
    // словарь значений с координатыми живых клеток и индексами
    map<int, int> aliveCells;

    int check_neighbors(int x, int y);

public:
    Field(int startingNumberOfLive, int heightOfField, int widthOfField);
    void draw_field(bool showGeneration = false);
    void print_alive();
    void next_generation();

};

#endif // FIELD_H
