#include <iostream>
#include "field.h"
#define DEFAULT_NUMBER 8
using namespace std;


int main(int argc, char *argv[])
{
    // Определение начальных параметров игры
    int startingNumberOfLive;
    int heightOfField;
    int widthOfField;

    if (argc > 1) {
        startingNumberOfLive = stoi(argv[1]);
        if(argc > 2) {
            heightOfField = stoi(argv[2]);
            if(argc > 3) {
                widthOfField = stoi(argv[3]);
            } else {
                widthOfField = DEFAULT_NUMBER;
            }
        } else {
            widthOfField = DEFAULT_NUMBER;
            heightOfField = DEFAULT_NUMBER;
        }
    } else {
        widthOfField = DEFAULT_NUMBER;
        heightOfField = DEFAULT_NUMBER;
        startingNumberOfLive = DEFAULT_NUMBER;
    }
    cout << "Живых клеток на старте: " << startingNumberOfLive << endl <<
            "Размер поля в высоту: "   << heightOfField        << endl <<
            "Размер поля в ширину: "   << widthOfField         << endl << endl;

    Field field(startingNumberOfLive, heightOfField, widthOfField);
    field.print_alive();
    field.draw_field();
    field.next_generation();
    field.print_alive();
    field.draw_field(true);
    return 0;
}
