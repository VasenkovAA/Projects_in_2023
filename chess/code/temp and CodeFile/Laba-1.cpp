#include <iostream>

using namespace std;

//перечисление какие фигуры у нас есть.
enum TFigure_type{pawn,rook,knight,bishop,queen,king};//пешка, ладья, конь, слон, королева, король
enum TFigure_color{black,withe};//цвет фигуры
//Класс координат
class TCoord{
private:
short int x;
short int y;
public:
void set_x(int _x){};
void set_y(int _y){};
short int get_x(){return x;};
short int get_y(){return y;};
};

//массив координат, координату в него можно добавлять с помощю add_cooия новойrd(), кула вы передаете
//или координаты x,y по отдельности либо обьктом TCoord. Сейчас функционала у него нет, но потом он появится.
//на данном этапе вам нужна только функции добавления новой координаты
class TCoordMass{
private:
short int count;
TCoord* mass;
public:
void add_coord(TCoord&_tmp){add_coord(_tmp.get_x(),_tmp.get_y());}
void add_coord(short int x,short int y){
TCoord *tmp_mass = new TCoord[count+1];
for (short int i = 0;i<count;i++){tmp_mass[i] = mass[i];}
tmp_mass[count].set_x(x);
tmp_mass[count].set_y(y);
delete [] mass;
mass = tmp_mass;}
TCoordMass(){}
TCoordMass(TCoordMass&){}
~TCoordMass(){delete [] mass;}
};



//класс - общий предок всех фигур, нужен для того чтобы хранить все фигуры в одном массиве.
class TFigure{
short int id;//Уникальный номер фигуры на поле (от 0 до 31). Задается в конструкторе наследников.
TFigure_type type;//Тип фигуры задается в конструкторе наследующих классов.
TCoord coord;//координата фигуры, если фигура съедена - (-1,-1)
TFigure_color color;//цвет фигуры
};
//Класс пешка
class TPawn:public TFigure{
private:
bool fitrst_move;
public:
TPawn():fitrst_move(false){};//конструктор по умолчанию
TPawn(TPawn&tmp){};//конструктор копирования
~TPawn(){};//деструктор

TCoordMass& get_list_coord(){};//возвращает список координат, куда фигура может сдвинуться, начальные координаты берет от свего обьекта.
bool check_move(TCoord& coord_last){};//возвращает true если фигура может передвинуться на переданные координаты.
void move_to(TCoord& coord_last){};//пердвигает фигуру на переданные координаты без проверки(просто меняет свое поле TCoord). 
};
//Класс король
class TKing:public TFigure{
public:
TKing(){};//конструктор по умолчанию
TKing(TKing&tmp){};//конструктор копирования
~TKing(){};//деструктор

TCoordMass& get_list_coord(){};//возвращает список координат, куда фигура может сдвинуться, начальные координаты берет от свего обьекта.
bool check_move(TCoord& coord_last){};//возвращает true если фигура может передвинуться на переданные координаты.
void move_to(TCoord& coord_last){};//пердвигает фигуру на переданные координаты без проверки(просто меняет свое поле TCoord). 
};
//Класс королева
class TQueen:public TFigure{
public:
TQueen(){};//конструктор по умолчанию
TQueen(TQueen&tmp){};//конструктор копирования
~TQueen(){};//деструктор

TCoordMass& get_list_coord(){};//возвращает список координат, куда фигура может сдвинуться, начальные координаты берет от свего обьекта.
bool check_move(TCoord& coord_last){};//возвращает true если фигура может передвинуться на переданные координаты.
void move_to(TCoord& coord_last){};//пердвигает фигуру на переданные координаты без проверки(просто меняет свое поле TCoord). 
};
//Класс ладья
class TRook:public TFigure{
public:
TRook(){};//конструктор по умолчанию
TRook(TRook&tmp){};//конструктор копирования
~TRook(){};//деструктор

TCoordMass& get_list_coord(){};//возвращает список координат, куда фигура может сдвинуться, начальные координаты берет от свего обьекта.
bool check_move(TCoord& coord_last){};//возвращает true если фигура может передвинуться на переданные координаты.
void move_to(TCoord& coord_last){};//пердвигает фигуру на переданные координаты без проверки(просто меняет свое поле TCoord). 
};
//Класс слон
class TBishop:public TFigure{
public:
TBishop(){};//конструктор по умолчанию
TBishop(TBishop&tmp){};//конструктор копирования
~TBishop(){};//деструктор

TCoordMass& get_list_coord(){};//возвращает список координат, куда фигура может сдвинуться, начальные координаты берет от свего обьекта.
bool check_move(TCoord& coord_last){};//возвращает true если фигура может передвинуться на переданные координаты.
void move_to(TCoord& coord_last){};//пердвигает фигуру на переданные координаты без проверки(просто меняет свое поле TCoord). 
};
//Класс конь
class TKnight:public TFigure{
public:
TKnight(){};//конструктор по умолчанию
TKnight(TKnight&tmp){};//конструктор копирования
~TKnight(){};//деструктор

TCoordMass& get_list_coord(){};//возвращает список координат, куда фигура может сдвинуться, начальные координаты берет от свего обьекта.
bool check_move(TCoord& coord_last){};//возвращает true если фигура может передвинуться на переданные координаты.
void move_to(TCoord& coord_last){};//пердвигает фигуру на переданные координаты без проверки(просто меняет свое поле TCoord). 
};
//класс поля, содержит в себе массивы ссылок на координаты и массивы ссылок на фигур
class TDeck{
public:


};


















