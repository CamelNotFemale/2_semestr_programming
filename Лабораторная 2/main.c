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
        struct tutor_elem *next;
    } Node; // Элемент списка
typedef struct
    {
        int count;
        Node *first;
        Node *last;
    } Head; // Головаодносвязного списка

// Получение валидных значений
char *get_string(); // Получение строки
int get_int(); // Получение целого числа
float get_float(); // ПОлучение числа с плавающей запятой
char *get_subject(); // Получение учебного предмета
// Работа со списком
void *add_item(tutor *list); // Заполнение информационных полей у репетитора
Head *make_head(); // Инициализация головы списка
Node *create_node(); // Создать элемент списка
void *add_first(Head *my_head, Node *new_node); // Добавить элемент в начало списка
void *add_last(Head *my_head, Node *new_node); // Добавить элемент в конец списка
void insert(Head *my_head, Node *new_node); // Вставка в произвольное место
void swap(Head *HEAD); // Перестановка двух элементов
void remove_node(Head *my_head); // Удаление элемента
Node *copy_node(Node *NODE); // Копирование элемента
void print_tutors(Head *my_head); // Печать списка в виде таблицы
Head *selected(Head *my_head); // Процесс фильтрации
Node *clean_node(Node *); // Очистка памяти для одной записи
Head *clean_list(Head *HEAD); // Очистить память под список
// Интерфейс
int Menu(); // Вывод меню и выбор его пункта
void Help(); // Справка

int main()
{
    Head *HEAD = NULL, *NEW_HEAD = NULL;
    Node *p = NULL;
    HEAD = make_head();
    int Q, Q3, output = 0;
    char c = 0;
    do {
        Q = Menu(0);
        switch (Q)
        {
            case 1:     //input
                output = 0;
                if (HEAD->count) // Если перезаписываем список
                {
                    clean_list(HEAD);
                    if (NEW_HEAD)
                        NEW_HEAD = clean_list(NEW_HEAD);
                    HEAD->count = 0;
                    HEAD->first=NULL;
                    HEAD->last=NULL;
                }
                do
                {
                    printf("Press 1 - Add node to start, 2 - Add node to end, 3 - Insert node\nPress Enter to stop\n");
                    c = getch();
                    if (c != 13 && (c>=49 && c<=51)) p = create_node();
                    switch (c)
                    {
                        case 49:
                            add_first(HEAD, p);
                            break;
                        case 50:
                            add_last(HEAD, p);
                            break;
                        case 51:
                            insert(HEAD, p);
                            break;
                        case 13:
                            printf("Successful input.\n");
                            break;
                        default:
                            puts("Error, try again.\n");
                    }
                } while (c != 13);
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
                    do
                    {
                        Q3 = Menu(3);
                        switch (Q3)
                        {
                            case 1:
                                if (HEAD->count > 1)
                                    do
                                    {
                                        swap(HEAD);
                                        puts("Once more swap? Press Enter - No, press any key - Yes");
                                        c = getch();
                                    } while (c != 13);
                                else
                                {
                                    Q3=0;
                                    puts("The list must have more than one item.");
                                }
                                break;
                            case 2:
                                remove_node(HEAD);
                                break;
                            case 0:
                                Q3=0;
                                break;
                            default:
                                puts("Try again!");
                                break;
                        }
                    } while (Q3 != 0);
                }
                else
                    printf("No input to actions!\n");
                break;
            case 4:     //process
                if (HEAD->count)
                {
                    NEW_HEAD = selected(HEAD);
                    output = 1;
                }
                else
                    printf("No input to process!\n");
                break;
            case 5:     //output result
                if (output)
                    if (NEW_HEAD->count) print_tutors(NEW_HEAD);
                    else printf("Tutors not found.\n");
                else
                    printf("No processed data to output!\n");
                break;
            case 6:     //help
                Help();
                break;
            case 0:     //exit
                printf("Good buy, see you soon!\n");
                break;
            default:
                printf("Error! Try again!\n");
                break;
        }
        system("pause");
    } while (Q);
    // Очистка всего мусора
    HEAD = clean_list(HEAD);
    if (NEW_HEAD)
        NEW_HEAD = clean_list(NEW_HEAD);
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
    printf("Your chosen %s\n", choice = subjects[q-1]);
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
        printf("Enter price per 1 hour(RUB): \n");
        list->price = get_int();
        printf("Enter qualifications: \n");
        scanf("%c", &(list->qual));
        while ((c=getchar()) != '\n' && c != EOF);
        do
        {
            printf("Enter tutor's rating: \n");
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
                new_node->next = my_head->first;
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
            if (my_head->count)
                (my_head->last)->next = new_node;
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
                        new_node->next = p->next;
                        p->next = new_node;
                        my_head->count++;
                    }
                }
            }
    }

void swap(Head *HEAD)
{
    int i, first, second;
    Node *p_one, *p_two;
    Node *buff_one, *buff_two;

    do
    {
        printf("Enter first item number [from 1 to %d]: ", HEAD->count);
        first = get_int();
        printf("Enter second item number [from 1 to %d]: ", HEAD->count);
        second = get_int();
        if (first>second)
            puts("The first number must be less that the second.");
    } while (first<1 || second>HEAD->count || first>=second);

    p_one = HEAD->first;
    for (i=1; i<first-1; i++)
        p_one = p_one->next; // Получим адрес предыдущего элемента
    p_two = HEAD->first;
    for (i=1; i<second-1; i++) // Получим адрес предыдущего элемента
        p_two = p_two->next;

    if (first != 1)
    {
        buff_one = p_one->next; // Адрес первого элемента
        buff_two = p_two->next; // Адрес второго элемента
        p_one->next = buff_two;
        p_two->next = buff_one;
        p_one = buff_one->next; // Адрес следующего элемента
        p_two = buff_two->next; // Адрес следующего элемента
        buff_one->next = p_two;
        buff_two->next = p_one;
        if (buff_two == HEAD->last)
            HEAD->last = buff_one;
    }
    else
    {
        buff_two = p_two->next; // Адрес второго элемента
        buff_one = p_one; // Адрес первого элемента
        HEAD->first = buff_two;
        p_two->next = buff_one;
        p_one = buff_one->next; // Адрес следующего элемента
        p_two = buff_two->next; // Адрес следующего элемента
        buff_one->next = p_two;
        buff_two->next = p_one;
        if (buff_two == HEAD->last)
            HEAD->last = buff_one;
    }

}

void remove_node(Head *my_head)
{
    Node *p, *buff;
    int i, pos;
    char c;

    printf("Do you want see list of tutors? Press 1 if you want or press any key otherwise\n");
    c = getch();
    if (c == 49)
        print_tutors(my_head);
    do
    {
        do
        {
            printf("Remove element with number [from 1 to %d]: ", my_head->count);
            pos = get_int();
        } while (pos<1 || pos>my_head->count);

        p = my_head->first;
        if (my_head->count > 1)
        {
            for (i=1; i<pos-1; i++) // Проматываем до элемента перед удаляемым
            {
                p = p->next;
            }
            if (pos==1)
            {
                my_head->first = p->next;
            }
            else if (pos==my_head->count)
            {
                buff = p;
                my_head->last = buff;
                p = p->next;
                buff->next = NULL;
            }
            else
            {
                buff = p;
                p = p->next;
                buff->next = (buff->next)->next;
            }
        }
        else
        {
            my_head->first = NULL;
            my_head->last = NULL;
        }
        my_head->count--;
        clean_node(p);

        if (my_head->count > 0)
        {
            printf("Delete more? Press 1 - Yes, any key - No\n");
            c = getch();
        }
        else
            c=49;
    } while (c==49 && my_head->count>0);
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
        strcpy((p->info).subject, (NODE->info).name);
        (p->info).price = (NODE->info).price;
        (p->info).qual = (NODE->info).qual;
        (p->info).rating = (NODE->info).rating;
    }

    return p;
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

Head *selected(Head *my_head)
{
    Head *NEW_HEAD = NULL;
    Node *p = NULL;
    int i; // Параметр цикла
    int maxPrice = 0;
    float minRating = 0;
    char *subject = NULL;
    NEW_HEAD = make_head();

    printf("Select subject that you need:\n");
    subject = get_subject();
    printf("Select max price per hour(RUB): ");
    maxPrice = get_int();
    printf("Select min tutor`s rating: ");
    minRating = get_float();

    p = my_head->first;
    for (i=0; i<my_head->count; i++)
    {
        if (((p->info).price <= maxPrice) && ((p->info).rating >= minRating) && (strcmp((p->info).subject, subject)==0))
        {
            add_last(NEW_HEAD, copy_node(p));
        }
        p = p->next;
    }

    return NEW_HEAD;
}
// Очистка для конкретной записи
Node *clean_node(Node *node)
{
    free((node->info).subject);
    free((node->info).name);
    (node->info).subject = NULL;
    (node->info).name = NULL;
    //free(node);
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

    }
    return NULL;
}

int Menu(int q)
	{
	    int Q; // Выбор пользователя
        system("cls");
        puts("MENU");
        switch(q)
        {
            case 0:
                puts("1 - Input data");
                puts("2 - Output data");
                puts("3 - Actions with the database");
                puts("4 - Filter");
                puts("5 - Output result");
                puts("6 - Help");
                puts("0 - Exit");
                break;
            case 3:
                puts("1 - Swap any items");
                puts("2 - Remove any items");
                puts("0 - Come back");
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
    printf("  We'll help you chosen a tutor. At first, upload(Enter)\ndatabase using menu item 1. Filter database using menu item 3.\n");
    printf("  To get the result of program use menu item 4.\n  To finish work use menu item 0.\n");
}
