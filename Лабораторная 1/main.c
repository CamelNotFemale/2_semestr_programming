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
    } tutor;

char *get_string();
int get_int();
float get_float();
char *get_subject();
void *add_item(tutor *);
tutor *add_items(int *);
void print_tutors(tutor *, int);
tutor *selected(tutor *, int, int *);
int Menu();
void Help();

int main()
{
    setlocale(LC_ALL, "RUS");
    tutor *data = NULL, *result = NULL;
    int k, count, Q, input = 0, output = 0;
    do {
        Q = Menu();
        switch (Q)
        {
            case 1:     //input
                k = 0;
                data = add_items(&k);
                if (data != NULL)
                    input = 1;
                else
                    printf("Error occured when trying to get memory for array! Please retry.\n");
                break;
            case 2:     //output
                if (input)
                    print_tutors(data, k);
                else
                    printf("No input to print!\n");
                break;
            case 3:     //process
                if (input)
                    result = selected(data, k, &count);
                if ((count <= k) && (count == -1 || result != NULL))
                {
                    printf("Successful selection.\n");
                    output = 1;
                }
                else
                    printf("No input to process!\n");
                break;
            case 4:     //output result
                if (output)
                    if (count > 0) print_tutors(result, count);
                    else printf("Tutors not found.\n");
                else
                    printf("No processed data to output!\n");
                break;
            case 5:     //help
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
    for (Q = 0; Q < k; Q++)
    {
        free((data + Q)->subject);
        free((data + Q)->name);
    }
    for (Q = 0; Q < count; Q++)
    {
        free((result + Q)->subject);
        free((result + Q)->name);
    }
    free(data);
    free(result);
    return 0;
}

char *get_string()
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

int get_int()
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

float get_float()
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

char *get_subject()
{
    char *choice = NULL, c;
    int q, i;
    for (i=0; i<(int)sizeof(subjects)/sizeof(char*); i++)
        printf("%d. %s\n", i+1, subjects[i]);
    do
    {
        q = get_int();
        if (q <= 0 || q > (int)sizeof(subjects)/sizeof(char*))
            printf("This item doesn't exist. Try again.\n");
    } while (q <= 0 || q > (int)sizeof(subjects)/sizeof(char*));
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Your chosen %s\n", choice = subjects[q-1]);
    return choice;
}

void *add_item(tutor *list)
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

tutor *add_items(int *count)
{
    tutor *data = NULL; // База репетиторов
    char exit = '1', c;
    *count = 0;
    do
    {
        data = (tutor*)realloc(data, (*count+1)*sizeof(tutor));
        if (data)

        {
            add_item(data + ++(*count) - 1);
            printf("Press 'Enter' to stop, press any key to continue.\n");
            exit = getch();
        }
        else exit = 13;
    } while (exit != 13);
    return data;
}

void print_tutors(tutor *list, int count)
{
    int i;
    printf("|     Tutor`s name     |     Subject    |Price per hour(RUB)|Qualification| Rating |\n");
    printf("|______________________|________________|___________________|_____________|________|\n");
    for (i = 0; i < count; i++)
    {
        printf("|%22.22s|%16.16s|%19d|%13c|%8.2f|\n", (list+i)->name, (list+i)->subject, (list+i)->price, (list+i)->qual, (list+i)->rating);
        printf("|______________________|________________|___________________|_____________|________|\n");
    }
}

tutor *selected(tutor *data, int k, int *count)
{
    tutor *result = NULL, *temp = NULL;
    int i; // Параметр цикла
    int maxPrice = 0;
    float minRating = 0;
    char *subject = NULL;
    *count = 0;
    printf("Select subject that you need:\n");
    subject = get_subject();
    printf("Select max price per hour(RUB): ");
    maxPrice = get_int();
    printf("Select min tutor`s rating: ");
    minRating = get_float();
    for (i=0; i<k; i++)
    {
        if (((data+i)->price <= maxPrice) && ((data+i)->rating >= minRating) && (strcmp((data+i)->subject, subject)==0))
        {
            temp = result;
            result = (tutor*)realloc(result, (*count+1)*sizeof(tutor));
            if (result)
                *(result + ++(*count) - 1) = *(data+i);
            else
            {
                free(temp);
                i = *count = k + 1;
            }
        }
    }
    if (*count==0) *count = -1;
    return result;
}
//Функция меню
//Возвращает номер пункта меню.
int Menu()
	{
	    int Q; // Выбор пользователя
        system("cls");
        puts("MENU");
        puts("1 - Input data");
        puts("2 - Output data");
        puts("3 - Filter");
        puts("4 - Output result");
        puts("5 - Help");
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
    printf("  We'll help you chosen a tutor. At first, upload(Enter)\ndatabase using menu item 1. Filter database using menu item 3.\n");
    printf("  To get the result of program use menu item 4.\n  To finish work use menu item 0.\n");
}
