/* Автозапчасти
 * 20ви2 Рябцев Никита Олегович
  доп функции
  -поиск по марке,по типу детали.
  -Список по выбранной части автомобиля(подвеска, двигатель…)
  содержание
  -Марка автомобиля,
  -часть автомобиля,
  -тип детали,
  -производитель,
  -стоимость
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;


// основная структура автозапчасти
struct AutoDetails
{
    string brand_car;
    string part_auto;
    string view_detail;
    string maker;
    double price;
};

// структура, создающая список из структур автозапчасти
struct Node
{
    AutoDetails auto_details;
    Node *pointer_in_next;
    Node *pointer_in_preview;

};

struct Stack
{
    AutoDetails auto_details;
    Stack *pointer;
};
Stack *create_first_element_in_stack();
AutoDetails pop_in_stack(Stack **top);

//######################################################################################
//__________________________
//создание первого элемента
Node *create_first_element();
//__________________________


//__________________________________________________________
// добавление элемента в список
void addDetail(Node **pointer_end, AutoDetails auto_details);
//__________________________________________________________

//________________________
// функции создания интерфейса
void printNiceInterface();
void print_command();
//________________________



//___________________
// функция поиска по выбранной детали по типу и марки автомобиля
int searchElement(Node *const pointer_begin, string,string);
//___________________

//__________________
// функция сохранения в текстовый файл
void save_in_text_file(Node **pointer_begin);
//__________________

//__________________________________
// печать списка
void printList(Node **pointer_begin);
//__________________________________

//_________________________
// печать списка по выбранной части
void pushInStackByChangedPart(Node *const pointer_begin, string part_auto, Stack **top);
//________________________

//___________________________________________________________________________________________
// метод вставки элемента
bool insertElement(Node **pointer_end);
//___________________________________________________________________________________________


//_________________________________________________________________________
// метод удаления элементов
bool removeChangedElement(Node **pointer_begin, Node **pointer_end, string);
//_________________________________________________________________________


//_______________________________________________________
// important function
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);

    //  print interface
    printNiceInterface();
    print_command();
    cout<<""<<endl;

    // create chain of list
    // создание элемента с нулевыми значениями
    Node *pointer_begin = create_first_element();
    Node *pointer_end = pointer_begin;

    // variable for work with functions
    string brand;

    // variable main while
    bool run = true;

    // variable changing command
    int number_command;



    // main while console app
    while (run)
    {
        cout<<"Введите номер операции: ";
        cin>>number_command;
        switch(number_command)
        {
            case 1:
            {
                ifstream file("C:\\Users\\User\\CLionProjects\\rescurs\\details.txt");
                //readerTextFile.open("C:\\Users\\hyppe\\Downloads\\curs-20211030T133325Z-001\\curs\\d.txt");
                AutoDetails *new_detail = new AutoDetails();
                // checking
                string  line;
                if (!file.is_open())
                {
                    cout << "File is not found ! " << endl;
                    run = false;

                }
                else
                {
                    cout<<"\t\t\tFile is opened"<<endl;
                    cout<<"###Data are written from line###"<<endl;
                    while (getline(file,line) ){
                        istringstream iss(line);
                        cout<<line<<endl;
                        iss>>new_detail->brand_car
                           >> new_detail->part_auto
                           >> new_detail->view_detail
                           >> new_detail->maker
                           >> new_detail->price;
                        addDetail(&pointer_end, *new_detail);
                        cout<<"\tМарка авто: "<<new_detail->brand_car<<endl;
                        cout<<"\tЧасть авто: "<<new_detail->part_auto<<endl;
                        cout<<"\tТип детали: "<<new_detail->view_detail<<endl;
                        cout<<"\tПроизводитель: "<<new_detail->maker<<endl;
                        cout<<"\tЦена: "<<new_detail->price<<endl;

                        cout<<""<<endl;
                    }
                    print_command();
                }
                file.close();
                cout<<"\n"<<endl;
                break;
            }
            case 2:
            {
                bool check;
                cout<<"\n"<<endl;
                check = insertElement(&pointer_end);
                if (check == 0)
                {
                    cout<<"Error inserting !"<<endl;
                    print_command();
                    break;
                }
                else
                {
                    cout<<"! New element is added !"<<endl;
                    print_command();
                    break;
                }
            }
            case 3:
            {
                string part_auto;
                cout << "--Введите выбранную часть авто: ";
                cin >> part_auto;
                cout<<"\n"<<endl;
                AutoDetails detail;
                Stack *top = create_first_element_in_stack();
                pushInStackByChangedPart(pointer_begin, part_auto, &top);
                while (top)
                {
                    detail = pop_in_stack(&top);
                    if (detail.price > 0)
                    {
                        cout<<"\tМарка авто: "<<detail.brand_car<<endl;
                        cout<<"\tВид детали: "<<detail.view_detail<<endl;
                        cout<<"\tЧасть авто: "<<detail.part_auto<<endl;
                        cout<<"\tПроизводитель: "<<detail.maker<<endl;
                        cout<<"\tЦена:"<<detail.price;
                        cout<<"\n"<<endl;
                    }
                    else
                    {
                        break;
                    }

                }
                print_command();
                break;
            }
            case 4:
            {
                string view_detail;
                int result;
                cout<<"--Введите марку автомобиля: ";
                cin>>brand;
                cout<<"--Введите тип детали: ";
                cin>>view_detail;
                cout<<"\n"<<endl;
                result = searchElement(pointer_begin, brand,view_detail);
                if (result == 0)
                {
                    cout<<"\t\tSearching was ended with error  :("<<endl;
                    print_command();
                    break;
                }
                else
                {
                    print_command();
                    break;
                }


            }
            case 5:
            {
                string changed_part_auto;
                bool res;
                cout << "--Выберите часть автомобиля: ";
                cin >> changed_part_auto;
                cout<<"\n"<<endl;
                res = removeChangedElement(&pointer_begin, &pointer_end, changed_part_auto);

                if (res)
                {
                    cout<<"\n"<<endl;
                    cout<<"!This elements with changed part is deleted!"<<endl;
                    cout<<"\n"<<endl;
                    print_command();
                    break;
                }
                else
                {
                    cout<<"Error deleting !"<<endl;
                    print_command();
                    cout<<"\n"<<endl;
                    break;
                }
            }
            case 6:
                printList(&pointer_begin);
                print_command();
                break;
            case 7:
                cout<<"--Сохранение списка в файл"<<endl;
                save_in_text_file(&pointer_begin);
                cout<<"!!Список сохранен в файл new_details.txt !!"<<endl;
                cout<<"\n"<<endl;
                print_command();
                break;
            case 8:
                cout<<"Exit...."<<endl;
                run = false;
                break;
            default:
                cout<<"!!!!!!!!!!!!!!!!!!Error!!!!!!!!!!!!!!!!"<<endl;
                run = false;
        }
    }

    system("pause");
    return 0;
}
//__________________________________________________________

//__________________________________________________________
// main description functions
void printNiceInterface(){
    cout<<"###############################################################################################"<<endl;
    cout<<"##########################**######:##############:###### №№№№№№№№№№№№№№№ ######################"<<endl;
    cout<<"#########################*#*######:##############:##############*###############() ############"<<endl;
    cout<<"########################*##*######:##############:##############*##############(###)###########"<<endl;
    cout<<"#######################*###*######:##############:##############*#############(#####)##########"<<endl;
    cout<<"######################*####*######:##############:##############*############(#######)#########"<<endl;
    cout<<"#####################*#####*######:##############:##############*###########(#########)########"<<endl;
    cout<<"####################*######*######:##############:##############*###########(#########)########"<<endl;
    cout<<"###################*#######*######:##############:##############*###########(#########)########"<<endl;
    cout<<"##################*########*######:##############:##############*###########(#########)########"<<endl;
    cout<<"#################***********######:##############:##############*###########(#########)########"<<endl;
    cout<<"################*##########*######:##############:##############*###########(#########)########"<<endl;
    cout<<"###############*###########*#######:############:###############*###########(#########)########"<<endl;
    cout<<"##############*############*#######:############:###############*###########(#########)########"<<endl;
    cout<<"#############*#############*#######:############:###############*###########(#########)########"<<endl;
    cout<<"############*##############*#######:############:###############*###########(#########)########"<<endl;
    cout<<"###########*###############*########:##########:################*###########(#########)########"<<endl;
    cout<<"##########*################*########:##########:################*############(########)########"<<endl;
    cout<<"#########*#################*########:##########:################*#############(#######)########"<<endl;
    cout<<"########*##################*########:##########:################*##############(######)########"<<endl;
    cout<<"#######*###################*########::::::::::::################*###############(####)#########"<<endl;
    cout<<"###############################################################################################"<<endl;
    cout<<"\n"<<endl;
    cout<<"\t\t\t############### :Автозапчасти: #############"<<endl;
    cout<<"\t\tОсновные параметры автозапчасти:"<<endl;
    cout<<"1. Марка автомобиля (Пример марки: Hynday-Solaris"<<endl;
    cout<<"2. Часть автомобиля (Пример части автомобиля: Brake-system"<<endl;
    cout<<"3. Тип детали (Пример типа детали: Oil-seals"<<endl;
    cout<<"4. Производитель (Пример производителя: Nissan"<<endl;
    cout<<"5. Стоимость в российских рублях (Пример цены: 799)"<<endl;
    cout<<"\n"<<endl;

}
void print_command(){
    cout<<"\t\t############### :Функции для работы с параметрами: ##########"<<endl;
    cout<<"1. Чтение из файла в консоль"<<endl;
    cout<<"2. Добавление нового элемента"<<endl;
    cout<<"3. Список элементов по выбранной части авто"<<endl;
    cout<<"4. Поиск по марке автомобиля и типу детали"<<endl;
    cout<<"5. Удаление элементов по выбранной части автомобиля"<<endl;
    cout<<"6. Печать текущего списка в консоль "<<endl;
    cout<<"7. Сохранить список в текстовый файл"<<endl;
    cout<<"8. Выход из консольного приложения"<<endl;
    cout<<"\n"<<endl;
}
Stack *create_first_element_in_stack()
{
    Stack *pv = new Stack;
    pv->auto_details.brand_car = "";
    pv->auto_details.part_auto = "";
    pv->auto_details.view_detail = "";
    pv->auto_details.maker ="";
    pv->auto_details.price = 0;
    return pv;
}
AutoDetails pop_in_stack(Stack **top)
{
    AutoDetails temp_detail = (*top)->auto_details;
    Stack *pv = *top;
    *top = (*top)->pointer;
    delete pv;
    return temp_detail;
}
int searchElement(Node *const pointer_begin, string brand_car, string view){
    int flag = 0;
    Node *pointer_preview = pointer_begin;
    cout<<"\t\tНайденные записи по марке и типу детали: "<<endl;
    while (pointer_preview)
    {
        if (pointer_preview->auto_details.brand_car == brand_car && pointer_preview->auto_details.view_detail == view )
        {
            cout<<"\tМарка автомобиля: "<<pointer_preview->auto_details.brand_car<<endl;
            cout<<"\tЧасть автомобиля: "<<pointer_preview->auto_details.part_auto<<endl;
            cout<<"\tТип детали: "<<pointer_preview->auto_details.view_detail<<endl;
            cout<<"\tПроизводитель: "<<pointer_preview->auto_details.maker<<endl;
            cout<<"\tЦена: "<<pointer_preview->auto_details.price<<endl;
            cout<<"\n"<<endl;
            flag++;
        }
        pointer_preview=pointer_preview->pointer_in_next;
    }
    return flag;
}
void pushInStackByChangedPart(Node *const pointer_begin, string part_auto, Stack **top){
    Node *pointer_preview = pointer_begin;

    cout<<"\t\tСписок по выбранной части: "<<endl;
    while (pointer_preview)
    {
        if (pointer_preview->auto_details.part_auto == part_auto) {



            // добавление элемента в стек
            Stack *pointer_pv_stack = new Stack;
            pointer_pv_stack->auto_details.brand_car = pointer_preview->auto_details.brand_car;
            pointer_pv_stack->auto_details.part_auto = pointer_preview->auto_details.part_auto;
            pointer_pv_stack->auto_details.view_detail = pointer_preview->auto_details.view_detail;
            pointer_pv_stack->auto_details.maker = pointer_preview->auto_details.maker;
            pointer_pv_stack->auto_details.price = pointer_preview->auto_details.price;
            pointer_pv_stack->pointer = *top;
            *top = pointer_pv_stack;

        }
        pointer_preview = pointer_preview->pointer_in_next;
    }
}

void addDetail(Node **pointer_end, AutoDetails auto_details){

    // создание нового узла
    Node *pointer_var = new Node;

    // заполнение узла новыми значениями, переданными в функцию
    pointer_var->auto_details.brand_car = auto_details.brand_car;
    pointer_var->auto_details.maker = auto_details.maker;
    pointer_var->auto_details.view_detail = auto_details.view_detail;
    pointer_var->auto_details.part_auto = auto_details.part_auto;
    pointer_var->auto_details.price = auto_details.price;

    // обнуление ссылки на следующий узел
    pointer_var->pointer_in_next = 0;

    // присваивание новому узлу, текущей ссылки, ссылки конечной
    pointer_var->pointer_in_preview = *pointer_end;

    // присваивание конечному узлу новый узел
    (*pointer_end)->pointer_in_next = pointer_var;
    *pointer_end = pointer_var;
}
bool insertElement(Node **pointer_end){
        bool res = true;
        Node *pointer_pv = new Node;
        cout<<"Введите марку авто:";
        cin>>pointer_pv->auto_details.brand_car;
        cout<<"Введите часть авто: ";
        cin>>pointer_pv->auto_details.part_auto;
        cout<<"Введите тип детали: ";
        cin>>pointer_pv->auto_details.view_detail;
        cout<<"Введите производителя: ";
        cin>>pointer_pv->auto_details.maker;
        cout<<"Введите цену детали: ";
        cin>>pointer_pv->auto_details.price;

        cout<<"\n";
        pointer_pv->pointer_in_next = 0 ;
        pointer_pv->pointer_in_preview = *pointer_end;
       (*pointer_end)->pointer_in_next = pointer_pv;
       if (pointer_pv->pointer_in_next == 0)
       {
           res = true;
       }
       else
       {
           res = false;
       }
    return res;
}

void save_in_text_file(Node **pointer_begin)
{
    Node *pointer_view = *pointer_begin;
    ofstream writer;
    writer.open("C:\\Users\\User\\CLionProjects\\rescurs\\new_details.txt", ios::out);
    while (pointer_view)
    {
        writer<<pointer_view->auto_details.brand_car<<" "<<
                pointer_view->auto_details.part_auto<<" "<<
                pointer_view->auto_details.view_detail<<" "<<
                pointer_view->auto_details.maker<<" "<<
                pointer_view->auto_details.price<<"\n ";
        pointer_view = pointer_view->pointer_in_next;
    }

}
// simple printing list in console
void printList(Node **pointer_begin){
    Node *pointer_view = *pointer_begin;
    while(pointer_view){
        cout<<"\tМарка авто: "<<pointer_view->auto_details.brand_car<<endl;
        cout<<"\tЧасть авто: "<<pointer_view->auto_details.part_auto<<endl;
        cout<<"\tТип детали: "<<pointer_view->auto_details.view_detail<<endl;
        cout<<"\tПроизводитель: "<<pointer_view->auto_details.maker<<endl;
        cout<<"\tЦена: "<<pointer_view->auto_details.price<<endl;
        cout<<""<<endl;
        pointer_view = pointer_view->pointer_in_next;
    }
}

// constructor for list
Node * create_first_element(){
    // создание первого элемента с нулевыми значениями
    Node *pointer_first = new Node;
    pointer_first->auto_details.brand_car = "";
    pointer_first->auto_details.view_detail="";
    pointer_first->auto_details.maker = "";
    pointer_first->auto_details.part_auto ="";
    pointer_first->auto_details.price=0;
    return pointer_first;
}
bool removeChangedElement(Node **pointer_begin, Node **pointer_end, string part){
    Node *pointer_view = *pointer_begin;
    bool res;
    while (pointer_view)
    {
        if (pointer_view->auto_details.part_auto == part) {
            if (pointer_view == *pointer_begin) {
                // присваиваем начальному элементу указатель на следующий
                *pointer_begin = (*pointer_begin)->pointer_in_next;
                (*pointer_begin)->pointer_in_preview->auto_details.brand_car = "";
                (*pointer_begin)->pointer_in_preview->auto_details.part_auto = "";
                (*pointer_begin)->pointer_in_preview->auto_details.view_detail = "";
                (*pointer_begin)->pointer_in_preview->auto_details.maker = "";
                (*pointer_begin)->pointer_in_preview->auto_details.price = 0;
            }
            else if (pointer_view == *pointer_end)
            {
                *pointer_end = (*pointer_end)->pointer_in_preview;
                *pointer_begin = (*pointer_begin)->pointer_in_next;
                (*pointer_begin)->pointer_in_next->auto_details.brand_car = "";
                (*pointer_begin)->pointer_in_next->auto_details.part_auto = "";
                (*pointer_begin)->pointer_in_next->auto_details.view_detail = "";
                (*pointer_begin)->pointer_in_next->auto_details.maker = "";
                (*pointer_begin)->pointer_in_next->auto_details.price = 0;
            }
            else
            {
                (pointer_view->pointer_in_preview)->pointer_in_next = pointer_view->pointer_in_next;
                (pointer_view->pointer_in_next)->pointer_in_preview = pointer_view->pointer_in_preview;
            }
            delete pointer_view;
            res = true;
        }
        else
        {

        }
        pointer_view = pointer_view->pointer_in_next;
    }
    return res;
}





