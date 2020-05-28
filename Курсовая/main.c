#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#define MAXLEN 24
#define MAXSTR 128
#ifdef __linux__
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

const char *subjects[] = {"Maths" , "Computer science", "English", "Russian", "Physics"};
typedef struct
    {
        // �������� �����
        char *name; // ���
        char *subject; // �������
        int price; // ���� �� ���
        char qual; // ������������
        float rating; // ������� �������������
    } tutor; // ���������� � ����������
typedef struct tutor_elem
    {
        tutor info;
        struct tutor_elem *prev;
        struct tutor_elem *next;
    } Node; // ������� ������
typedef struct
    {
        int count;
        Node *first;
        Node *last;
    } Head; // ������ ����������� ������

// �������������������
void pause(); // ������ ������� ��������� �����
void clean_stdin(); // ������ ������� ������� �������� ������ (fflush)
// ��������� �������� �������� //
char *get_string(); // ��������� ������
int get_int(); // ��������� ������ �����
float get_float(); // ��������� ����� � ��������� �������
char *get_subject(); // ��������� �������� ��������
// ������ �� ������� //
void fill_node(tutor *list); // ���������� �������������� ����� � ����������
Head *make_head(); // ������������� ������ ������
void add_item(Head *HEAD); // �������� ������� � ������
Node *create_node(); // ������� ������� ������
void *add_first(Head *my_head, Node *new_node); // �������� ������� � ������ ������
void *add_last(Head *my_head, Node *new_node); // �������� ������� � ����� ������
void insert(Head *my_head, Node *new_node); // ������� � ������������ �����
void swap(Head *HEAD, int first, int second); // ������������ ���� ���������
void sort(Head *HEAD); // ���������� ������ �� ������ �� �����
void remove_node(Head *my_head); // �������� ��������
Node *copy_node(Node *NODE); // ����������� ��������
void print_tutors(Head *my_head); // ������ ������ � ���� �������
Head *selected(Head *my_head); // ������� ����������
Node *clean_node(Node *); // ������� ������ ��� ����� ������
Head *clean_list(Head *HEAD); // �������� ������ ��� ������
// ������ � ������
void clear_str_array(char **str, int n); // ������� ���������������� ������� �����
char **simple_split(char *str, int length, char sep); // �������������� ������ ����� � ������ �� ����� ���������
int get_database(Head *HEAD, int MODE); // ������ ������ �� ������
int write_to_file(Head *HEAD, int MODE); // ������ � ����
Node *convert_to_node(char **s2); // ���������� ��������� ��� ������ ���������������� ������� ����� �� simple_split

int Menu();
void Help();

int main()
{
    Head *HEAD = NULL, *NEW_HEAD = NULL; // ������ ��������� � ��������������� �������
    Node *p = NULL; // ����� ������� ������
    HEAD = make_head();
    int Q, Q1, Q5, Q52, Q12, Q3, output = 0; // ���������� ��� ����������� ����
    int first, second, buff=1, // ����� �������� ������
        valid_file; // �������� ���������� ������
    do {
        Q = Menu(0);
        switch (Q)
        {
            case 1:     //input
                output = 0;
                if (HEAD->count) // ���� �������������� ������
                {
                    HEAD = clean_list(HEAD);
                    HEAD = make_head();
                    if (NEW_HEAD)
                        NEW_HEAD = clean_list(NEW_HEAD);
                }
                do
                {
                    Q1 = Menu(1);
                    switch (Q1)
                    {
                        case 1:
                            add_item(HEAD);
                            printf("Successful input.\n");
                            Q1=0;
                            break;
                        case 2:
                            do
                            {
                                Q12 = Menu(12);
                                switch (Q12)
                                {
                                    case 1:
                                        valid_file = get_database(HEAD, 0); // database.txt
                                        if (valid_file==1)
                                            printf("Successful input.\n");
                                        else if (valid_file == 0)
                                            printf("Error: Nonexistent file.\n");
                                        else if (valid_file == 2)
                                            printf("Error, file is empty.\n");
                                        else
                                            printf("Error reading from file.\n");
                                        Q12 = 0;
                                        break;
                                    case 2:
                                        valid_file = get_database(HEAD, 1); // enter the path of file
                                        if (valid_file==1)
                                            printf("Successful input.\n");
                                        else if (valid_file == 0)
                                            printf("Error: Nonexistent file.\n");
                                        else if (valid_file == 2)
                                            printf("Error, file is empty.\n");
                                        else
                                            printf("Error reading from file.\n");
                                        Q12 = 0;
                                        break;
                                    case 0:
                                        break;
                                    default:
                                        puts("Error, try again.\n");
                                }
                            } while (Q12 != 0);

                            Q1=0;
                            break;
                        case 0:
                            break;
                        default:
                            puts("Try again.");
                    }
                } while(Q1 != 0);

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
                                        do
                                        {
                                            system(CLEAR);
                                            printf("Do you want see list of tutors? Enter 1 if you want or enter any number otherwise\n");
                                            buff = get_int();
                                            if (buff == 1)
                                                print_tutors(HEAD);
                                            printf("Enter first item number [from 1 to %d]: ", HEAD->count);
                                            first = get_int();
                                            printf("Enter second item number [from 1 to %d]: ", HEAD->count);
                                            second = get_int();
                                        } while ((first<1 || second>HEAD->count) || (second<1 || first>HEAD->count));
                                        if (first>second)
                                            {
                                                buff = first;
                                                first = second;
                                                second = buff;
                                            }
                                        swap(HEAD, first, second);
                                        puts("Once more swap? Enter 1 - Yes, enter any number - No");
                                        buff = get_int();
                                    } while (buff == 1);
                                else
                                {
                                    Q3=0;
                                    puts("The list must have more than one item.");
                                }
                                break;
                            case 2:
                                remove_node(HEAD);
                                break;
                            case 3:
                                sort(HEAD);
                                puts("Successfully sorted.");
                                pause();
                                break;
                            case 4:
                                add_item(HEAD);
                                break;
                            case 5:
                                valid_file = write_to_file(HEAD, 1);
                                if (valid_file == 1)
                                    puts("Successful write to file");
                                else
                                    puts("Error write to file");
                                pause();
                                break;
                            case 0:
                                Q3=0;
                                break;
                            default:
                                puts("Try again!");
                                break;
                        }
                    } while (Q3 != 0 && HEAD->count);
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
                    do
                    {
                        Q5 = Menu(5);
                        switch (Q5)
                        {
                            case 1:
                                if (NEW_HEAD->count) print_tutors(NEW_HEAD);
                                else printf("Tutors not found.\n");
                                Q5=0;
                                break;
                            case 2:
                                do
                                {
                                    Q52 = Menu(52);
                                    switch (Q52)
                                    {
                                        case 1:
                                            if (NEW_HEAD->count) valid_file = write_to_file(NEW_HEAD, 0);
                                            else printf("Tutors not found.\n");
                                            if (valid_file == 1)
                                                puts("Successful write to file.");
                                            else
                                                puts("Error writing to file.");
                                            Q52 = 0;
                                            break;
                                        case 2:
                                            if (NEW_HEAD->count) valid_file = write_to_file(NEW_HEAD, 1);
                                            else printf("Tutors not found.\n");
                                            if (valid_file == 1)
                                                puts("Successful write to file.");
                                            else
                                                puts("Error writing to file.");
                                            Q52 = 0;
                                            break;
                                        case 0:
                                            break;
                                        default:
                                            puts("Error, try again.\n");
                                    }
                                } while (Q52 != 0);

                                Q5=0;
                                break;
                            case 0:
                                break;
                            default:
                                puts("Try again.");
                        }
                    } while(Q5 != 0);
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
        pause();
    } while (Q);
    // ������� ����� ������
    if (HEAD->count != 0)
        HEAD = clean_list(HEAD);
    if (NEW_HEAD)
        NEW_HEAD = clean_list(NEW_HEAD);

    return 0;
}

// ������ ���������� ��������
void pause()
{
    puts("\nPress Enter to continue");
    getchar();
}

// ������ ������� ������� �������� ������ (fflush)
void clean_stdin()
{
    char c;
    while ( scanf("%c", &c) == 1 && c != '\n');
}

void clear_str_array(char **str, int n)
{
    int i; // ����� �������� ������
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
    char **str_array=NULL; // ��������� �� ������ �����
    int i,j,k,m; // ����������� ������
    int key,count; // ����������� ������ ���������
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

int get_database(Head *HEAD, int MODE)
{
    Node *p; // ����� ������� ������
    int slen,i,count,flag=1, // ����������� ���������� ���������
        valid_file; // ��� ������ ��� �� ��������� ������ �� �����: 1-�������, 0-�������������� ����, -1-������ ������ �����, 2-������ ����
    char sep; // ������ ����������� ����� � ��������
    char s1[MAXSTR]; // ��������� ������, �������� ���� ������� ������
    char **s2=NULL; // ��������� �� ������ ����� ���������

    FILE *df; // ������������ ����
    if (MODE)
    {
        char *path;
        puts("Type path to file or his name: ");
        path = get_string();
        df = fopen(path, "r");
        free(path);
    }
    else df = fopen("database.txt", "r");

    if(df!=NULL)
    {
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
                p = convert_to_node(s2);
                add_last(HEAD, p);
                count++;
                i++;

                clear_str_array(s2,5);
            }
            else
            {
                flag=0;
                valid_file = -1;
                puts("Row data not available!");
            }
        }
        if (fclose(df)!=EOF)
            if (i==0)
                valid_file = 2;
            else
                valid_file = 1;
    }
    else
        valid_file = 0;

    return valid_file;
}

int write_to_file(Head *HEAD, int MODE)
{
	FILE *file; // ��������� �� ���������, � ������� ������� ����� ������������� ������ � ����
	int valid_file = 1; // ������������ ��� �������
	if (MODE)
    {
        char *path;
        puts("Type path to file or his name: ");
        path = get_string();
        file = fopen(path, "w");
        free(path);
    }
    else file = fopen("output.txt", "w");

	if (file == NULL)
	{
		printf("Error opening file!\n");
		valid_file = -1;
	}
	else
    {
        int i;
        Node *p=NULL;

        p = HEAD->first;
        for (i = 0; i < HEAD->count; i++)
        {
            fprintf(file, "%s;", (p->info).name);
            fprintf(file, "%s;", (p->info).subject);
            fprintf(file, "%d;", (p->info).price);
            fprintf(file, "%c;", (p->info).qual);
            fprintf(file, "%.2f", (p->info).rating);
            if (i<HEAD->count-1)
                fprintf(file, "\n");
            p = p->next;
        }

        if (fclose(file) == EOF)
            valid_file = 0;
	}
	return valid_file;
}

Node *convert_to_node(char **s2)
{
    Node *p = NULL; // ����� ������� ������
    int len1, len2; // ����� ��������� ����� �������� ������
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
char *get_string() // ������� ��������� ������
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

int get_int()  // ������� ��������� ������ �����
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

float get_float() // ������� ��������� ����� � ��������� �������
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

char *get_subject() // ������� ������ �������� �������� �� �������� �������
{
    char *choice = NULL; // ��������� �� ������ ���������� ��������
    int q, i; // ����������� �����
    for (i=0; i<(int)sizeof(subjects)/sizeof(char*); i++)
        printf("%d. %s\n", i+1, subjects[i]);
    do
    {
        q = get_int();
        if (q <= 0 || q > (int)sizeof(subjects)/sizeof(char*))
            printf("This item doesn't exist. Try again.\n");
    } while (q <= 0 || q > (int)sizeof(subjects)/sizeof(char*));

    choice = (char*)malloc(MAXLEN*sizeof(char));
    strcpy(choice, subjects[q-1]);
    printf("Your chosen %s\n", choice);
    return choice;
}

void fill_node(tutor *list) // �������� ������� � ������
{
    system(CLEAR);
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
        clean_stdin();
        do
        {
            printf("Enter tutor's rating: \n");
            list->rating = get_float();
        } while (list->rating <= 0 || list->rating > 5);
    }
}

Head *make_head() // ������������� ������
    {
        Head *ph=NULL; // ��������� �� "������" ������
        ph=(Head*)malloc(sizeof(Head));
        if(ph!=NULL)
        {
            ph->count=0;
            ph->first=NULL;
            ph->last=NULL;
        }
        return ph;
    }
void add_item(Head *HEAD) // ���������� ���� � ������
{
    Node *p=NULL; // ��������� �� ����� ������� ������
    int buff; // ����������� �����a
    do
    {
        printf("Enter 1 - Add node to start, 2 - Add node to end, 3 - Insert node\nEnter 0 to stop\n");
        buff = get_int();
        if (buff != 0) p = create_node();
        switch (buff)
        {
            case 1:
                add_first(HEAD, p);
                break;
            case 2:
                add_last(HEAD, p);
                break;
            case 3:
                insert(HEAD, p);
                break;
            case 0:
                break;
            default:
                puts("Error, try again.\n");
        }
    } while (buff != 0);
}
Node *create_node() // ������� ���� ������
    {
        Node *new_node=NULL; // ��������� �� ����� ������� ������
        new_node = (Node*)malloc(sizeof(Node));
        if(new_node)
        {
            fill_node(&(new_node->info));
        }
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
    }

void *add_first(Head *my_head, Node *new_node) // �������� ����� ������ ������ � ������
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

void *add_last(Head *my_head, Node *new_node) // �������� ����� ������ ��������� � ������
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

void insert(Head *my_head, Node *new_node) // ������� � ����� �����
    {
        int i, // ����������� �����
        pos; // ����� �������
        Node *p; // ��������� �� ����� ������� ������

        do
        {
            printf("What position? [From 1 to %d]\n", my_head->count+1);
            pos = get_int();
        } while (pos < 1 || pos > my_head->count+1);

        if(my_head&&new_node)
            {
                if (!(my_head->count)) // �������� �� ������ ������
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
                        for (i=1; i<pos-1; i++) { // ����������� �� ������� ����� ����������� ���������
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

void remove_node(Head *my_head)
{
    Node *p; // ��������� �� ����� ������� ������
    int i, pos; // ����������� ����� � ����� �������
    int buff=1; // ���� ����������� ������

    do
    {
        system(CLEAR);
        printf("Do you want see list of tutors? Enter 1 if you want or enter any number otherwise\n");
        buff = get_int();
        if (buff == 1)
            print_tutors(my_head);
        do
        {
            printf("Remove element with number [from 1 to %d]: ", my_head->count);
            pos = get_int();
        } while (pos<1 || pos>my_head->count);

        p = my_head->first;
        if (my_head->count > 1)
        {
            for (i=1; i<pos; i++) // ����������� �� ���������� ��������
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

        if (my_head->count > 0)
        {
            printf("Delete more? Enter 0 - No, any number - Yes\n");
            buff = get_int();
        }
        else
            buff=0;
    } while (buff != 0 && my_head->count>0);
}

void swap(Head *HEAD, int first, int second)
{
    int i; // ����
    Node *p_one, *p_two; // ��������� �� ��������� ��������
    Node *buff_one, *buff_two; // ��������� ��������� �� ����� �������� ������

    p_one = HEAD->first;
    for (i=1; i<first-1; i++)
        p_one = p_one->next; // ������� ����� ����������� ��������
    p_two = HEAD->first;
    for (i=1; i<second-1; i++) // ������� ����� ����������� ��������
        p_two = p_two->next;

    if (first != 1)
    {
        buff_one = p_one->next; // ����� ������� ��������
        buff_two = p_two->next; // ����� ������� ��������
        p_one->next = buff_two;
        p_two->next = buff_one;
        buff_two->prev = p_one; // ���������� ��� ������� �������� - ���������� ��� ������� ��������
        buff_one->prev = p_two; // ���������� ��� ������� �������� - ���������� ��� ������� ��������
        p_one = buff_one->next; // ����� �������� ���������� �� ������
        p_two = buff_two->next; // ����� �������� ���������� �� ������
        buff_one->next = p_two;
        buff_two->next = p_one;
        if (buff_two == HEAD->last)
            HEAD->last = buff_one;
        else
            p_two->prev = buff_one;
    }
    else
    {
        buff_two = p_two->next; // ����� ������� ��������
        buff_one = p_one; // ����� ������� ��������
        HEAD->first = buff_two;
        p_two->next = buff_one;
        buff_two->prev = p_one;
        buff_one->prev = p_two;
        p_one = buff_one->next; // ����� ���������� ��������
        p_two = buff_two->next; // ����� ���������� ��������
        buff_one->next = p_two;
        buff_two->next = p_one;
        if (buff_two == HEAD->last)
            HEAD->last = buff_one;
        else
            p_two->prev = buff_one;
    }
}
// ���������� 1, ���� left>right, -1 - ���� left>right, 0 - � ������ ���������
int compare(Node *left, Node *right, int type)
{
    int result; //��������� ���������

    switch (type)
    {
        case 1:
            result = strcmp((left->info).name, (right->info).name);
            break;
        case 2:
            result = strcmp((left->info).subject, (right->info).subject);
            break;
        case 3:
            if ((left->info).price > (right->info).price)
                result = 1;
            else if ((left->info).price < (right->info).price)
                result = -1;
            else
                result = 0;
            break;
        case 4:
            if ((left->info).qual > (right->info).qual)
                result = 1;
            else if ((left->info).qual < (right->info).qual)
                result = -1;
            else
                result = 0;
            break;
        case 5:
            if ((left->info).rating > (right->info).rating)
                result = 1;
            else if ((left->info).rating < (right->info).rating)
                result = -1;
            else
                result = 0;
            break;
    }

    return result;
}

void sort(Head *HEAD)
{
    int i, j, // ��������� ����� ��� �������� ���������
        type; // ��� ����, �� �������� ����������� ������
    int decrease; // �� �������� (==1) ��� �� �� ����������� (!=1)
    Node *p=NULL, *buff=NULL, *temp = NULL; // ��������� �� ����� ������� ������, ��������� �������� ��������� ������

    do
    {
        printf("Enter the field number to sort[from 1 to 5]\n");
        printf("1 - Name, 2 - Subject, 3 - Price, 4 - Qualification, 5 - Rating\n");
        type = get_int();
    } while (type<1 || type>5);
    printf("Sort Descending? Enter 1 - Yes, any number - Sort Ascending\n");
    decrease = get_int();

    p = HEAD->first;
    for (i=1; i<=HEAD->count-1; i++)
    {
        buff = p->next;
        for (j=i+1; j<=HEAD->count; j++)
        {

            if ((decrease==1) ? (compare(buff, p, type) > 0) : (compare(buff, p, type) < 0)) // ���� buff > p, �� �������� �� �������
            {
                swap(HEAD, i, j);
                temp = p;
                p = buff;
                buff = temp->next;
            }
            else
                buff = buff->next;
        }
        p = p->next;
    }
}

Node *copy_node(Node *NODE)
{
    int i; // ����������� �����
    Node *p=NULL; // ��������� �� ����� ������� ������

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

void print_tutors(Head *my_head)
{
    int i;
    Node *p; // ��������� �� ������� ������
    printf("|Num|     Tutor`s name     |     Subject    | Price per hour |Qualification| Rating |\n");
    printf("|___|______________________|________________|________________|_____________|________|\n");
    p = my_head->first;
    for (i = 0; i < my_head->count; i++)
    {
        printf("|%3d|%22.22s|%16.16s|%16d|%13c|%8.2f|\n", i+1, (p->info).name, (p->info).subject, (p->info).price, (p->info).qual, (p->info).rating);
        printf("|___|______________________|________________|________________|_____________|________|\n");
        p = p->next;
    }
}

Head *selected(Head *my_head)
{
    Head *NEW_HEAD = NULL; // ��������� �� ����� "������" ������
    Node *p = NULL, *copy_p = NULL; // ��������� �� ����� ������� ������ � ��� �����
    int i; // �������� �����
    int maxPrice = 0; // ����������� ���������� ����
    float minRating = 0; // ���������� ���������� �������
    char *subject = NULL; // ������� ��������
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
// ������� ��� ���������� ������
Node *clean_node(Node *node)
{
    free((node->info).subject);
    free((node->info).name);
    (node->info).subject = NULL;
    (node->info).name = NULL;
    free(node);
    return NULL;
}
// ������� ����� ������
Head *clean_list(Head *HEAD)
{
    Node *p, *temp; // ��������� �� ������� ������ � ��������� ���������
    int i; // ����������� �����

    p = HEAD->first;
    for (i = 0; i < HEAD->count; i++)
    {
        temp = p;
        p = p->next;
        temp->next = NULL;
        temp->prev = NULL;
        temp = clean_node(temp);
    }
    HEAD->count = 0;
    free(HEAD);
    return NULL;
}

int Menu(int q)
	{
	    int Q; // ����� ������������
        system(CLEAR);
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
            case 1:
                puts("1 - Input from console");
                puts("2 - Input from file");
                puts("0 - Come back");
                break;
            case 12:
                puts("1 - Input from default file (database.txt)");
                puts("2 - Select a file");
                puts("0 - Come back");
                break;
            case 3:
                puts("1 - Swap any items");
                puts("2 - Remove any items");
                puts("3 - Sort database");
                puts("4 - Add item");
                puts("5 - Save changes to file");
                puts("0 - Come back");
                break;
            case 5:
                puts("1 - Console output");
                puts("2 - Output in file");
                puts("0 - Come back");
                break;
            case 52:
                puts("1 - Write to file by default(output.txt)");
                puts("2 - Select a file");
                puts("0 - Come back");
        }

		printf("Select menu item - ");
		Q = get_int();
		printf("\n");
		return Q;
	}

void Help()
{
    system(CLEAR);
    printf("\tHELP\n");
    printf("  We'll help you chosen a tutor. At first, upload(Enter)\ndatabase using menu item 1. Filter database using menu item 4.\n");
    printf("  To get the result of program use menu item 5.\n  To finish work use menu item 0.\n");
}
