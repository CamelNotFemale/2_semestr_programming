#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define MAXLEN 24

const char *subjects[] = {"Maths" , "Computer science", "English", "Russian", "Physics"};
typedef struct
    {
        // Описание полей
        char *name; // Имя
        char *subject; // Предмет
        int price; // Цена за час
        char qual; // Квалификация
        float rating; // рейтинг преподавателя
    } tutor; // Информация о репетиторе
typedef struct tutor_elem
    {
        tutor info;
        struct tutor_elem *prev;
        struct tutor_elem *next;
    } Node; // Элемент списка
typedef struct
    {
        int count;
        Node *first;
        Node *last;
    } Head; // Голова двусвязного списка

// Получение валидных значений //
char *get_string(); // Получение строки
int get_int(); // Получение целого числа
float get_float(); // ПОлучение числа с плавающей запятой
char *get_subject(); // Получение учебного предмета
// Работа со списком //
void *add_item(tutor *list); // Заполнение информационных полей у репетитора
Head *make_head(); // Инициализация головы списка
Node *create_node(); // Создать элемент списка
void *add_first(Head *my_head, Node *new_node); // Добавить элемент в начало списка
void *add_last(Head *my_head, Node *new_node); // Добавить элемент в конец списка
void remove_node(Head *my_head, int pos); // Удаление элемента
Node *copy_node(Node *NODE); // Копирование элемента
void print_tutors(Head *my_head); // Печать списка в виде таблицы
Node *clean_node(Node *); // Очистка памяти для одной записи
void get_item(Head *HEAD, Node *p); // Вывод элемента и его удаление
Head *clean_list(Head *HEAD); // Очистить память под список
// Интерфейс //
int Menu(); // Вывод меню и выбор его пункта
void Help(); // Справка

int main()
{
    Head *HEAD = NULL, *NEW_HEAD = NULL;
    Node *p = NULL;
    HEAD = make_head();
    int Mode, Q, Q3,output = 0;
    int first, second;
    char c = 0;
    do
    {
        Mode = Menu(-1);
        switch (Mode)
        {
            case 1: // Queue
                do {
                    puts("QUEUE MODE");
                    Q = Menu(0);
                    switch (Q)
                    {
                        case 1:     //input
                            p = create_node();
                            add_last(HEAD, p);
                            printf("Successful input.\n");
                            break;
                        case 2:     //output
                            if (HEAD->count)
                                print_tutors(HEAD);
                            else
                                printf("No input to print!\n");
                            break;
                        case 3:
                            if (HEAD->count != 0)
                            {
                                get_item(HEAD, HEAD->first);
                            }
                            else
                                printf("No input to actions!\n");
                            break;
                        case 4:     //process
                            if (HEAD->count)
                            {
                                remove_node(HEAD, 1);
                                puts("First in the queue was deleted successfully");
                            }
                            else
                                printf("No input to remove!\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Error! Try again!\n");
                            break;
                    }
                    system("pause");
                } while (Q);
                break;
            case 2: // Stack
                do {
                    puts("STACK MODE");
                    Q = Menu(0);
                    switch (Q)
                    {
                        case 1:     //input
                            p = create_node();
                            add_first(HEAD, p);
                            printf("Successful input.\n");
                            break;
                        case 2:     //output
                            if (HEAD->count)
                                print_tutors(HEAD);
                            else
                                printf("No input to print!\n");
                            break;
                        case 3:
                            if (HEAD->count != 0)
                            {
                                get_item(HEAD, HEAD->first);
                            }
                            else
                                printf("No input to actions!\n");
                            break;
                        case 4:     //process
                            if (HEAD->count)
                            {
                                remove_node(HEAD, 1);
                                puts("First item successfully deleted");
                            }
                            else
                                printf("No input to remove!\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Error! Try again!\n");
                            break;
                    }
                    system("pause");
                } while (Q);
                break;
            case 3:
                Help();
            case 0:     //exit
                printf("Good buy, see you soon!\n");
                break;
        }
    } while (Mode);

    // Очистка всего мусора
    if (HEAD)
        HEAD = clean_list(HEAD);
    return 0;
}

char *get_string() // Функция получения строки
{
    char c, *string = (char*)malloc(MAXLEN*sizeof(char));
    int i=0;
    do
    {
        while ((c=getchar()) != '\n' && i < MAXLEN-1) string[i++] = c;
        string[i] = '\0';
        if (i < 1) printf("Error. You entered empty string. Please, try again.\n");
    } while (i < 1);
    if (i >= MAXLEN-1)
        while ((c = getchar()) != '\n' && c != EOF);
    return string;
}

int get_int()  // Функция получения целого числа
{
    char line[MAXLEN];   //buffer
    char curChar = ' ';
    int temp, result;
    do {
        line[MAXLEN - 1] = '\n';
        fgets(line, MAXLEN - 1, stdin);
        temp = sscanf(line, "%d%c", &result, &curChar);
        temp = !temp || temp < 0 || (curChar != '\n' && curChar != ' ');
        if (temp)
            printf("Error reading number. Please, try again.\n");
    } while (temp); //not a number actually
    if (line[MAXLEN - 1] != '\n') //clear all iput
        while ((curChar = getchar()) != '\n' && curChar != EOF);
    return result;
}

float get_float() // Функция получения числа с плавающей запятой
{
    char line[MAXLEN];   //buffer
    char curChar = ' ';
    int temp;
    float result;
    do {
        line[MAXLEN - 1] = '\n';
        fgets(line, MAXLEN - 1, stdin);
        temp = sscanf(line, "%f%c", &result, &curChar);
        temp = !temp || temp < 0 || (curChar != '\n' && curChar != ' ');
        if (temp)
            printf("Error reading number. Please, try again.\n");
    } while (temp); //not a number actually
    if (line[MAXLEN - 1] != '\n') //clear all iput
        while ((curChar = getchar()) != '\n' && curChar != EOF);
    return result;
}

char *get_subject() // Функция выбора Учебного предмета из заданных заранее
{
    char *choice = NULL, c;
    int q, i;
    for (i=0; i<(int)sizeof(subjects)/sizeof(char*); i++)
        printf("%d. %s\n", i+1, subjects[i]);
    do
    {
        scanf("%d", &q);
        if (q <= 0 || q > (int)sizeof(subjects)/sizeof(char*))
            printf("This item doesn't exist. Try again.\n");
    } while (q <= 0 || q > (int)sizeof(subjects)/sizeof(char*));
    while ((c = getchar()) != '\n' && c != EOF);
    choice = (char*)malloc(MAXLEN*sizeof(char));
    strcpy(choice, subjects[q-1]);
    printf("Your chosen %s\n", choice);

    return choice;
}

void *add_item(tutor *list) // Добавить элемент в список
{
    system("cls");
    char c;
    list->name = (char*)malloc(MAXLEN*sizeof(char));
    list->subject = (char*)malloc(MAXLEN*sizeof(char));
    if (list->subject && list->name)
    {
        printf("Enter tutor's name: \n");
        list->name = get_string();
        printf("Enter academic subject: \n");
        list->subject = get_subject();
        do
        {
            printf("Enter price per 1 hour(RUB): \n");
            list->price = get_int();
        } while (list->price < 0);
        printf("Enter qualifications: \n");
        scanf("%c", &(list->qual));
        while ((c=getchar()) != '\n' && c != EOF);
        do
        {
            printf("Enter tutor's rating[From 0 to 5]: \n");
            list->rating = get_float();
        } while (list->rating <= 0 || list->rating > 5);
    }
}

Head *make_head() // Инициализация головы
    {
        Head *ph=NULL;
        ph=(Head*)malloc(sizeof(Head));
        if(ph!=NULL)
        {
            ph->count=0;
            ph->first=NULL;
            ph->last=NULL;
        }
        return ph;
    }

Node *create_node() // Создать заполненную запись
    {
        Node *new_node=NULL;
        new_node = (Node*)malloc(sizeof(Node));
        if(new_node)
        {
            add_item(&(new_node->info));
        }
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
    }

void *add_first(Head *my_head, Node *new_node) // Добавить новую запись первой в список
    {
        if(my_head&&new_node)
        {
            if (!(my_head->count))
                my_head->last = new_node;
            else
            {
                (my_head->first)->prev = new_node;
                new_node->next = my_head->first;
            }
            my_head->first = new_node;
            my_head->count++;
        }
    }

void *add_last(Head *my_head, Node *new_node) // Добавить новую запись последней в список
    {
        if(my_head&&new_node)
        {
            if (!(my_head->count))
                my_head->first = new_node;
            else
            {
                (my_head->last)->next = new_node;
                new_node->prev = my_head->last;
            }
            my_head->last = new_node;
            my_head->count++;
        }
    }

void insert(Head *my_head, Node *new_node) // Вставка в любое место
    {
        int i, pos;
        Node *p;

        do
        {
            printf("What position? [From 1 to %d]\n", my_head->count+1);
            pos = get_int();
        } while (pos < 1 || pos > my_head->count+1);

        if(my_head&&new_node)
            {
                if (!(my_head->count)) // Проверка на пустой список
                {
                    my_head->first = new_node;
                    my_head->last = new_node;
                    my_head->count++;
                }
                else if (pos > 0 && pos < my_head->count+2)
                {
                    if (pos==1)
                        add_first(my_head, new_node);
                    else if (pos == my_head->count + 1)
                        add_last(my_head, new_node);
                    else {
                        p = my_head->first;
                        for (i=1; i<pos-1; i++) { // Проматываем до позиции перед вставляемым элементом
                            p = p->next;
                        }
                        new_node->prev = p;
                        new_node->next = p->next;
                        (p->next)->prev = new_node;
                        p->next = new_node;
                        my_head->count++;
                    }
                }
            }
    }

void remove_node(Head *my_head, int pos)
{
    Node *p;
    int i;
    char c;

    p = my_head->first;
    if (my_head->count > 1)
    {
        for (i=1; i<pos; i++) // Проматываем до удаляемого элемента
        {
            p = p->next;
        }
        if (pos==1)
        {
            my_head->first = p->next;
            (p->next)->prev = NULL;
        }
        else if (pos==my_head->count)
        {
            my_head->last = p->prev;
            (p->prev)->next = NULL;
        }
        else
        {
            (p->prev)->next = p->next;
            (p->next)->prev = p->prev;
        }
    }
    else
    {
        my_head->first = NULL;
        my_head->last = NULL;
    }
    my_head->count--;
    clean_node(p);
}

Node *copy_node(Node *NODE)
{
    int i;
    Node *p=NULL;

    p = (Node*)malloc(sizeof(Node));
    (p->info).name = (char*)malloc(MAXLEN*sizeof(char));
    (p->info).subject = (char*)malloc(MAXLEN*sizeof(char));

    if((p->info).subject!=NULL && (p->info).name!=NULL)
    {
        strcpy((p->info).name, (NODE->info).name);
        strcpy((p->info).subject, (NODE->info).subject);
        (p->info).price = (NODE->info).price;
        (p->info).qual = (NODE->info).qual;
        (p->info).rating = (NODE->info).rating;
    }

    return p;
}

void get_item(Head *HEAD, Node *p)
{

    printf("  %s\n  %s teacher\n  Price per hour(RUB): %d\n  Qualification: %c\n  Rating: %.2f\n", (p->info).name, (p->info).subject, (p->info).price, (p->info).qual, (p->info).rating);

    if (p->next == NULL)
        remove_node(HEAD, HEAD->count);
    else
        remove_node(HEAD, 1);


}

void print_tutors(Head *my_head)
{
    int i;
    Node *p;
    printf("|     Tutor`s name     |     Subject    |Price per hour(RUB)|Qualification| Rating |\n");
    printf("|______________________|________________|___________________|_____________|________|\n");
    p = my_head->first;
    for (i = 0; i < my_head->count; i++)
    {
        printf("|%22.22s|%16.16s|%19d|%13c|%8.2f|\n", (p->info).name, (p->info).subject, (p->info).price, (p->info).qual, (p->info).rating);
        printf("|______________________|________________|___________________|_____________|________|\n");
        p = p->next;
    }
}

// Очистка для конкретной записи
Node *clean_node(Node *node)
{
    free((node->info).subject);
    free((node->info).name);
    (node->info).subject = NULL;
    (node->info).name = NULL;
    node->next = NULL;
    node->prev = NULL;
    free(node);
    return NULL;
}
// Очистка всего мусора
Head *clean_list(Head *HEAD)
{
    Node *p, *temp;
    int i;
    p = HEAD->first;
    for (i = 0; i < HEAD->count; i++)
    {
        free((p->info).subject);
        free((p->info).name);
        temp = p;
        p = p->next;
        free(temp->next);
        free(temp->prev);

    }
    free(HEAD->first);
    free(HEAD->last);
    return NULL;
}

int Menu(int q)
	{
	    int Q; // Выбор пользователя
        system("cls");
        switch(q)
        {
            case -1:
                puts("MENU");
                puts("1 - Queue Mode");
                puts("2 - Stack Mode");
                puts("3 - Help");
                puts("0 - Exit");
                break;
            case 0:
                puts("1 - Add item");
                puts("2 - Output data");
                puts("3 - Get item");
                puts("4 - Delete item");
                puts("0 - To the Main menu");
                break;
        }

		printf("Select menu item - ");
		scanf("%d", &Q);
		printf("\n");
		fflush(stdin);
		return Q;
	}

void Help()
{
    system("cls");
    printf("\tHELP\n");
    puts("  To work, you need to select the mode: queue or stack.");
    puts("  You can add an item (1 menu item), see the entire list (2 menu item),");
    puts("   view information about an item and delete it (3 menu item),");
    puts("   and also delete the item without viewing the content (4 menu item).");
    puts("  To exit the program, select the Exit menu item.\n");
    system("pause");
}
