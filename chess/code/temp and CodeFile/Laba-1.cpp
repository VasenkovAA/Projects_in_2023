//перечисление какие фигуры у нас есть.
enum TFigure_type{pawn,rook,knight,bishop,queen,king}//пешка, ладья, конь, слон, королева, король
enum TFigure_color{black,withe}//цвет фигуры
//Класс координат
class TCoord{
short int x;
short int y;
TFigure *figure; // ссылка на ту фигуру,которая стоит на этой клетке. Если ее нет - nullptr.
public:
set_x(int _x){};
set_y(int _y){};
set_figure(TFigure& _figure){};
get_x(){};
get_y(){};
get_figure(){};
};
//класс - общий предок всех фигур, нужен для того чтобы хранить все фигуры в одном массиве.
class TFigure{
short int id;//Уникальный номер фигуры на поле (от 0 до 31). Задается в конструкторе наследников.
TFigure_type type;//Тип фигуры задается в конструкторе наследующих классов.
TFcoord *coord;//ссылка на координату фигуры, если фигура съедена - nullptr
TFigure_color color;//цвет фигуры
};
//Класс пешка
class TPawn:public TFigure{
public:
TMass<TCoord>& get_list_coord(TDesk&tmp){};//возвращает список координат, кда фигура может сдвинуться
bool set_coord(TCoord&_coord,TDesk&tmp){};//возвращает true если фигура подвинулась на переданные координаты
};
//Класс король
class TKing:public TFigure{
public:
TMass<TCoord>& get_list_coord(TDesk&tmp){};//возвращает список координат, кда фигура может сдвинуться
bool set_coord(TCoord&_coord,TDesk&tmp){};//возвращает true если фигура подвинулась на переданные координаты
};
//Класс королева
class TQueen:public TFigure{
public:
TMass<TCoord>& get_list_coord(TDesk&tmp){};//возвращает список координат, кда фигура может сдвинуться
bool set_coord(TCoord&_coord,TDesk&tmp){};//возвращает true если фигура подвинулась на переданные координаты
};
//Класс ладья
class TRook:public TFigure{
public:
TMass<TCoord>& get_list_coord(TDesk&tmp){};//возвращает список координат, кда фигура может сдвинуться
bool set_coord(TCoord&_coord,TDesk&tmp){};//возвращает true если фигура подвинулась на переданные координаты
};
//Класс слон
class TBishop:public TFigure{
public:
TMass<TCoord>& get_list_coord(TDesk&tmp){};//возвращает список координат, кда фигура может сдвинуться
bool set_coord(TCoord&_coord,TDesk&tmp){};//возвращает true если фигура подвинулась на переданные координаты
};
//Класс конь
class TKnight:public TFigure{
public:
TMass<TCoord>& get_list_coord(TDesk&tmp){};//возвращает список координат, кда фигура может сдвинуться
bool set_coord(TCoord&_coord,TDesk&tmp){};//возвращает true если фигура подвинулась на переданные координаты
};
//класс поля, содержит в себе массивы ссылок на координаты и массивы ссылок на фигур
class TDeck{
public:
TMass<TCoord> coords;
TMass<TFigure>figures;
};



















