#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define MAXLEN 24
#define MAXSTR 128

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

char *get_string();
int get_int();
float get_float();
char *get_subject();
void *add_item(tutor *list);
Head *make_head();
Node *create_node();
void *add_first(Head *my_head, Node *new_node);
void *add_last(Head *my_head, Node *new_node);
void insert(Head *my_head, Node *new_node, int pos);
void print_tutors(Head *my_head);
Head *selected(Head *my_head);
Node *clean_node(Node *node);
Head *clean_list(Head *HEAD);
// Работа с файлом
void clear_str_array(char **str, int n);
char **simple_split(char *str, int length, char sep);
void get_database(Head *HEAD);
Node *fill_node(char **s2);

int Menu();
void Help();

int main()
{
    Head *HEAD = NULL, *NEW_HEAD = NULL;
    Node *p = NULL;

    HEAD = make_head();

    get_database(HEAD);

    return 0;
}

void clear_str_array(char **str, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;
}

char **simple_split(char *str, int length, char sep)
{
    char **str_array=NULL;
    int i,j,k,m;
    int key,count;
    for(j=0,m=0;j<length;j++)
    {
        if(str[j]==sep) m++;
    }

    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]!=NULL) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else
                {
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
        }
        else
        {
            clear_str_array(str_array,count);
        }
     }
     return str_array;
}

void get_database(Head *HEAD)
{
    Node *p;
    int slen,i,count,flag=1;
    char sep;
    char s1[MAXSTR];
    char **s2=NULL;
    FILE *df;

    df=fopen("database.txt","r");
    if(df!=NULL)
    {
/* Reading data from file and filling structures */

        sep=';';
        count=0;
        i=0;
        while(fgets(s1,MAXSTR,df) != NULL && flag)
        {
            slen=strlen(s1);
            s1[slen-1]='\0';
            slen=strlen(s1);

            s2=simple_split(s1,slen,sep);
            if(s2!=NULL)
            {
                p = fill_node(s2);
                add_last(HEAD, p);
                count++;
                i++;


                clear_str_array(s2,5);
            }
            else
            {
                flag=0;
                puts("Row data not available!");
            }
        }
        fclose(df);
    }

    print_tutors(HEAD);
}

Node *fill_node(char **s2)
{
    Node *p = NULL;
    int len1, len2;
    p = (Node*)malloc(sizeof(Node));
    p->next = NULL;
    p->prev = NULL;

    len1=strlen(s2[0]);
    len2=strlen(s2[1]);

    (p->info).name=(char*)malloc((len1+1)*sizeof(char));
    (p->info).subject=(char*)malloc((len2+1)*sizeof(char));

    if(((p->info).name!=NULL)&&((p->info).subject!=NULL))
    {
        strcpy((p->info).name,s2[0]);
        strcpy((p->info).subject,s2[1]);
        (p->info).price=atoi(s2[2]);
        (p->info).qual=s2[3][0];
        (p->info).rating=atof(s2[4]);
    }
    else
    {
        puts("Out if memory! Program terminated");
        p = NULL;
    }

    return p;
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

void insert(Head *my_head, Node *new_node, int pos) // Вставка в любое место
    {
        int i;
        Node *p;
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
            add_last(NEW_HEAD, p);
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

int Menu()
	{
	    int Q; // Выбор пользователя
        system("cls");
        puts("MENU");
        puts("1 - Input data");
        puts("2 - Output data");
        puts("3 - Remove any element");
        puts("4 - Filter");
        puts("5 - Output result");
        puts("6 - Help");
        puts("0 - Exit");
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
    printf("  We'll help you chosen a tutor. At first, upload(Enter)\ndatabase using menu item 1. Filter database using menu item 4.\n");
    printf("  To get the result of program use menu item 5.\n  To finish work use menu item 0.\n");
}
