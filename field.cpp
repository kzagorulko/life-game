#include "field.h"

/**
* @brief Field::check_neighbors - функция, определения количества соседей клетки. сектора
* определяются следующим образом: (X - клетка с координатами х,у) 0 1 2
*                                                                 3 Х 4
*                                                                 5 6 7.
* @param x - горизонтальная координата клетки
* @param y - вертикальная координата клетки
* @return возвращает колчиство живых сеседей
*/
int Field::check_neighbors(int x, int y)
{
    bool sectors[8];
    sectors[0] = (x > 0) && (y > 0) && (field[y-1][x-1] > 0);
    sectors[1] = (y > 0) && (field[y-1][x] > 0);
    sectors[2] = (x < widthOfField - 1) && (y > 0) && (field[y-1][x+1] > 0);
    sectors[3] = (x > 0) && (field[y][x-1] > 0);
    sectors[4] = (x < widthOfField - 1) && (field[y][x+1] > 0);
    sectors[5] = (x > 0) && (y < heightOfField - 1) && (field[y+1][x-1] > 0);
    sectors[6] = (y < heightOfField - 1) && (field[y+1][x] > 0);
    sectors[7] = (x < widthOfField - 1) && (y < heightOfField - 1) && (field[y+1][x+1] > 0);

    int sum = 0;
    for(auto item : sectors) {
        sum += item;
    }

    return sum;
}

/**
 * @brief Field::Field - конструктор класса, который создаёт поле, для хранения данных о поколении
 * клетки и словарь для удобного просмотра.
 * @param startingNumberOfLive - количество живых клеток на поле
 * @param heightOfField - высота поля
 * @param widthOfField - длинна поля
 */
Field::Field(int startingNumberOfLive, int heightOfField, int widthOfField)
{
    // Инициализируется поле, для хранение данных о состоянии клетки
    field = new int*[heightOfField];
    for(int i = 0; i < heightOfField; i++) {
        field[i] = new int[widthOfField];
    }
    this->heightOfField = heightOfField;
    this->widthOfField  = widthOfField;

    srand(unsigned(time(0)));
    while(startingNumberOfLive-- > 0) {

        /**
         * Случайное присвоение уникальных координат. Имеет плохую сложность при количестве живых
         * клеток близких к произведению высоты поля на его ширину. Следовало бы продумать более
         * эффективный алгоритм.
         */
        int value;
        bool flag;
        do {
            flag = true;
            value = rand() % (heightOfField * widthOfField);
            for(auto item = aliveCells.begin(); (item != aliveCells.end())&&flag; item++) {
                if(value == item->first) {
                    flag = false;
                }
            }
        } while(!flag);

        aliveCells.insert(pair<int,int>(value, 1));
        field[value / widthOfField][value % widthOfField] = 1;
    }
}

/**
 * @brief Field::draw_field - метод отображения поля в консольном отображении.
 * @param showGeneration - прдоставляет возможность отображать поколение клетки true = отображать
 * false = не отображать.
 */
void Field::draw_field(bool showGeneration)
{
    for(int i = 0; i < widthOfField + 2; i++) {
        cout << '#';
    }
    cout << endl << '#';
    for(int i = 0; i < heightOfField; i++) {
        for(int j = 0; j < widthOfField; j++) {
            cout << (field[i][j] ? (showGeneration ? to_string(field[i][j]) : "*") : " ");
        }
        cout << '#' << endl << '#';
    }
    for(int i = 0; i < widthOfField+1; i++) {
        cout << '#';
    }
    cout << endl;
}
/**
 * @brief Field::print_alive - метод, выводящий на экран словарь с живыми клетками
 */
void Field::print_alive()
{
    cout << "Живые клетки:" << endl;
    for(auto &item : aliveCells) {
        cout << "x = " << item.first % widthOfField << " y = " << item.first / widthOfField <<
                " Поколение: " << item.second << endl;
    }
    cout << endl;
}

/**
 * @brief Field::next_generation - метод перехода на следующее поколение
 */
void Field::next_generation()
{
    int newGeneration[heightOfField][widthOfField];
    for(int i = 0; i < heightOfField; i++) {
        for(int j = 0; j < widthOfField; j++) {
            newGeneration[i][j] = 0;
        }
    }
    aliveCells.clear();
    print_alive();
    for(int i = 0; i < heightOfField; i++) {
        for(int j = 0; j < widthOfField; j++) {
            int numberOfNeighbors = check_neighbors(j, i);
            if ((field[i][j] > 0) && (numberOfNeighbors > 1) && (numberOfNeighbors < 4)) {
                newGeneration[i][j] = ++field[i][j];
            } else if ((field[i][j] == 0)&&(numberOfNeighbors == 3)) {
                newGeneration[i][j] = 1;
            }
            if (field[i][j] > 0) {
                aliveCells.insert(pair<int, int>(i * widthOfField + j, field[i][j]));
            }
        }
    }

    for(int i = 0; i < heightOfField; i++) {
        for(int j = 0; j < widthOfField; j++) {
            field[i][j] = newGeneration[i][j];
        }
    }
}
