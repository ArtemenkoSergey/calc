#include <stdio.h>      // printf(), putchar(), fprintf(), fgets()
#include <stdlib.h>     // exit()

#define DEBUG 0
#define VERBOSE 1

// Константы определяющие тип элемента списка.
#define OPERAND_TYPE 0x0000
#define PARENTHESIS_TYPE  0x0001
#define PARENTHESIS_OPEN_SYMVOL 0x28     // '('
#define PARENTHESIS_CLOSE_SYMVOL 0x29    // ')'

#define PRIORITY_01_OPERATIONS 0x0100
#define UNARY_PLUS_SYMVOL 0x2B        // '+'
#define UNARY_PLUS_TYPE 0x012B        // 0x0100 + 0x002B
#define UNARY_MIMUS_SYMVOL 0x2D       // '-'
#define UNARY_MINUS_TYPE 0x012D       // 0x0100 + 0x002D

#define PRIORITY_02_OPERATIONS 0x0200

#define PRIORITY_04_OPERATIONS 0x0400
#define MULTIOLICATION_SYMVOL 0x2A      // '*'
#define MULTIOLICATION_TYPE 0x042A
#define DIVISION_SYMVOL 0x2F            // '/'
#define DIVISION_TYPE 0x042F
#define MODULO_SYMVOL 0x25              // '%'
#define MODULO_TYPE 0x0425

#define PRIORITY_08_OPERATIONS 0x0800
#define BINARY_PLUS_SYMVOL 0x2B         // '+'
#define BINARY_PLUS_TYPE 0x082B
#define BINARY_MINUS_SYMVOL 0x2D        // '/'
#define BINARY_MINUS_TYPE 0x082D



// структура узла двусвязаного списка
struct ListItem
{
    struct ListItem *LeftItem;  // ссылка на предидущий элемент списка
    struct ListItem *RightItem; // ссылка на следующи элемент списка
    int Type;                   // тип элемента списка
    int Value;                  // значение элемента списка
    struct ListItem* (*Exe)(struct ListItem*); // исполняемая функция связаная с этим элементом
};


//  Функция содает новый элемент в конце списка.
//  требует указатель на один из элементов списка
//  возвращает указатель но товый элемент списка
struct ListItem* AddNewItemToList(struct ListItem *);
//  Функция выводнит на стандартный вывод подробную информацию о элементе списка
//  требует указатель на элемент и строку из которой создавался список.
void ShowListItem(struct ListItem *, char* );
//  Функция выводит значене элемента списка на стандартный вывод
//  требует указатель на элемент и строку из которой создавался список.
void PrintItem(struct ListItem *, char* );
//  Функция удаляет элемент из списка
//  требует указатель на элемент списка
void DeleteItem(struct ListItem *);

//  Функция для перехода к первому элементу списка
//  требует указатель на один из элементов списка
//  возвращает указатель на первый элемент списка
struct ListItem* GotoHead(struct ListItem* );
//  Функция для перехода к последнему элементу списка
//  требует указатель на один из элементов списка
//  возвращает указатель на последний элемент списка
struct ListItem* GotoTail(struct ListItem* );
//  Функция выводит значения элементов списка на стандартный вывод
//  требует указатель на элемент и строку из которой создавался список.
void PrintList(struct ListItem *, char* );
//  Функция удаляет список
//  требует указатель на один из элементов списка
//  возвращает количество удаленных элементов
int DeleteList(struct ListItem *);

//  Функция распознает и добавляет в список операнды и операции вычисляемого выражения
//  требует исходную строку
//  возвращает указатель на один из элементов списка.
struct ListItem* CalcParser(char* );
//  Функция проверяет правильность введенного выражения
//  требует указатель на элемент и строку из которой создавался список.
//  в случае нахождения ошибки вызывает аварийное завершение программы.
void CalcCheker(struct ListItem *, char* );
//  Функция выполняет вычисление выражения переведенного в список
//  требует указатель на один из элементов списка и строку из которой создавался список.
//  возвращает указатель на элемент списка в котором сохранен  результат вычислений.
struct ListItem* CalcExecute(struct ListItem *, char *);

//  Функция вычисляет выражение сохранненое в строке
//  вызывается рекруссивно для вычисления выражений в скобках
//  требует исходную строку
//  возвращает указатель на элемент списка в котором сохранен  результат вычислений.
struct ListItem * Calc(char* );

// Фукция составления строки из массива строк
// требует длинну массива строк, указатель на массив строк
// указатель на массив символов, максимальную длинну строки
// возвращает длинну строки
int StrFromArg(int, char**, char*, int);
// Функция для ввода строки с устройсва стандартного ввода
// требует указатель на массив символов и максимаьлную длинну строки
void InputStr(char*, int);

// Функция проверяет является ли символ цифрой
// требует проверяемый символ
// возвращает 1 если утверждение истино и 0 если ложно.
int isDigit(char);
// Функция проверяет является ли символ оператором
// требует проверяемый символ
// возвращает 1 если утверждение истино и 0 если ложно.
int isOperation(char);

//  Функции обеспечивающие выполнение операций
//  требуют указатель на элемент списка с оператором
//  указатель на элемент с результом операции
//  операнды участвующиее в операции удаляются из списка.
struct ListItem* UnaryPlus(struct ListItem *);
struct ListItem* UnaryMinus(struct ListItem *);
struct ListItem* BinaryPlus(struct ListItem *);
struct ListItem* BinaryMinus(struct ListItem *);
struct ListItem* Muliplication(struct ListItem *);
struct ListItem* Division(struct ListItem *);
struct ListItem* Modulo(struct ListItem *);
struct ListItem* Operand(struct ListItem *);

int main(int argc, char **argv)
{
    const int MAX_STR_LEN = 1024;
    char str[MAX_STR_LEN];

    if (argc > 1) StrFromArg(argc-1, argv+1, str, MAX_STR_LEN);
    else InputStr(str, MAX_STR_LEN);
    printf("Вычислям выражение: %s\n", str);
    struct ListItem * list = Calc(str);
#if DEBUG
    printf("+++++++++++++++++++\n");
    PrintList(list, str);
    printf("+++++++++++++++++++\n");
    // ShowListItem(list, str);
#endif
    printf("Результат вычисления выражения равен: ");
    PrintItem(list, str);
    putchar('\n');
    DeleteList(list);
    return 0;
}

struct ListItem* Calc(char* str)
{

    struct ListItem * list = CalcParser(str);
    #if DEBUG
        printf("CalcParser OK\n");
    #endif
    list = GotoHead(list);
    #if VERBOSE
        printf("Вычисляем выражение : ");
        PrintList(list, str);
    #endif

    CalcCheker(list, str);
    #if DEBUG
        printf("CalcCheker OK\n");
    #endif

    // struct ListItem *tmp = GotoHead(list);
    // do
    // {
    //     ShowListItem(tmp, str);
    //     tmp = tmp->RightItem;
    // } while(tmp != NULL);

    list = CalcExecute(list, str);
    #if DEBUG
        printf("CalcExecute OK\n");
    #endif

    return list;
}

struct ListItem* CalcParser(char* str)
{
    int i,l,c;
    char tempch;
    struct ListItem *list = NULL;
    #if DEBUG
        printf("%s\n", str);
    #endif
    for(i=0;str[i]!='\0';i++)
    {
        if (str[i]==' ') continue;
        //if (str[i]==PARENTHESIS_CLOSE_SYMVOL) continue;
        list = AddNewItemToList(list);
        if (isDigit(str[i]))
        {
            l=0;
            while (isDigit(str[i+l]))l++;
            list->Type = OPERAND_TYPE;
            tempch = str[i+l];
            str[i+l]='\0';
            list->Value = atoi(str+i);
            str[i+l] = tempch;
            i+=l-1;
            list->Exe = Operand;
            continue;
        }
        if (str[i]==PARENTHESIS_OPEN_SYMVOL)
        {
            list->Type = PARENTHESIS_TYPE;
            list->Value = i;
            l=1, c=1;
            do {
                if (str[i+l]==PARENTHESIS_OPEN_SYMVOL) c++;
                if (str[i+l]==PARENTHESIS_CLOSE_SYMVOL) c--;
            } while(c>0 && str[i+l++]!='\0');
            if (c>0)
            {
                printf("%*s\n", i+1,"^");
                fprintf(stderr, "Нет пары для скобки\n");
                exit(EXIT_FAILURE);
            }
            i+=l;
            continue;
        }

        list -> Value = i;
        switch (str[i])
        {
            case MULTIOLICATION_SYMVOL:
                list->Type = MULTIOLICATION_TYPE;
                list->Exe = Muliplication;
                continue;
            case DIVISION_SYMVOL:
                list->Type = DIVISION_TYPE;
                list->Exe = Division;
                continue;
            case MODULO_SYMVOL:
                list->Type = MODULO_TYPE;
                list->Exe = Modulo;
                continue;
            case UNARY_PLUS_SYMVOL:
            case UNARY_MIMUS_SYMVOL:
                if (list->LeftItem != NULL)
                    {
                        if (list->LeftItem->Type < PRIORITY_01_OPERATIONS)
                        {
                            list->Type = PRIORITY_08_OPERATIONS+str[i];
                            if (str[i]==BINARY_MINUS_SYMVOL) list->Exe = BinaryMinus;
                            else list->Exe = BinaryPlus;
                            continue;
                        }
                    }
                list->Type = PRIORITY_01_OPERATIONS+str[i];
                if (str[i]==UNARY_MIMUS_SYMVOL) list->Exe = UnaryMinus;
                else list->Exe = UnaryPlus;
                continue;
        }
        DeleteItem(list);
        printf("%*s\n", i+1,"^");
        fprintf(stderr, "Ошибка расапознования на %d символе в строке\n\'%c\'  не является цифрой или операцией\n", i, str[i]);
        exit(EXIT_FAILURE);
    }
    return list;
}

void CalcCheker(struct ListItem * item, char* str)
{
    struct ListItem *t = GotoHead(item);
    struct ListItem *l;
    struct ListItem *r;
    int i;
    do
    {
        item = t;
        l = t->LeftItem;
        r = t->RightItem;
        if ((t->Type < PRIORITY_01_OPERATIONS) && (r!=NULL && r->Type<PRIORITY_01_OPERATIONS))
        {
            printf("\n%s\n", str);
            if (l) i = l->Value+3;
            else i = 0;
            printf("%*s\n", i,"^");
            fprintf(stderr, "Ошибка выражения. Два операнда подряд\n");
            exit(EXIT_FAILURE);
        }
        if ((t->Type & PRIORITY_01_OPERATIONS) && (r == NULL || r->Type>=PRIORITY_02_OPERATIONS))
        {
            printf("\n%s\n", str);
            printf("%*s\n", t->Value+1 ,"^");
            fprintf(stderr, "Ошибка выражения. Нет операнда у унарной операции\n");
            exit(EXIT_FAILURE);
        }
        if ((t->Type > PRIORITY_02_OPERATIONS) && ( l==NULL || r==NULL || l->Type>PRIORITY_01_OPERATIONS  || r->Type >=PRIORITY_02_OPERATIONS))
        {
            printf("\n%s\n", str);
            printf("%*s\n", t->Value+1, "^");
            fprintf(stderr, "Ошибка выражения. Нет одного из операндов у бинарной операции\n");
            exit(EXIT_FAILURE);
        }
        t = r;
    }
    while(t!=NULL);

}

struct ListItem* CalcExecute(struct ListItem * item, char *str)
{
    item = GotoHead(item);
    struct ListItem * t;
    struct ListItem * o;
    int l,c;
    // printf("0x%04X\n", PARENTHESIS_TYPE);
    for(t=item;t!=NULL;t=t->RightItem)
    {
         if (t->Type == PARENTHESIS_TYPE)
         {
             #if VERBOSE
                printf("Вычисляем выражение в скобках:\n");
                // PrintItem(t, str);
             #endif
             l=0, c=1;
             do {
                 l++;
                 if (str[t->Value+l]==PARENTHESIS_OPEN_SYMVOL) c++;
                 if (str[t->Value+l]==PARENTHESIS_CLOSE_SYMVOL) c--;
             } while(c>0);
             c = str[t->Value+l];
             str[t->Value+l]='\0';
             o = Calc(str+t->Value+1);
             str[t->Value+l]=c;
             t -> Value = o -> Value;
             t -> Type = OPERAND_TYPE;
             DeleteList(o);
         }
         item = t;
    }

    // printf("0x%04X\n", PRIORITY_01_OPERATIONS);
    t = GotoTail(item);
    do
    {
        item = t;
        if (t->Type & PRIORITY_01_OPERATIONS)
        {
            // printf("exe:  ");
            t = t->Exe(t);
        }
        else
        {
            t = t-> LeftItem;
        }
    }
    while(t!=NULL);
    int k;
    for(k=PRIORITY_02_OPERATIONS; k<=PRIORITY_08_OPERATIONS; k<<=1)
    {
        // printf("0x%04X\n", k);
        item = GotoHead(item);
        for(t=item;t!=NULL;t=t->RightItem)
        {
            if (t->Type & k)
            {
                //printf("exe:  ");
                t = t->Exe(t);
            }
            item=t;
        }
    }
    return item;
}

struct ListItem *AddNewItemToList(struct ListItem *item)
{
    struct ListItem *new = (struct ListItem*)malloc(sizeof (struct ListItem));

    if (item == NULL)
    {
        new->RightItem = NULL;
        new->LeftItem = NULL;
        return new;
    }
    if (item->RightItem != NULL) item = GotoTail(item);
    new->LeftItem = item;
    new->RightItem = NULL;
    item->RightItem = new;
    return new;
}

struct ListItem* GotoHead(struct ListItem* item)
{
    while (item->LeftItem != NULL) item = item->LeftItem;
    return item;
}

struct ListItem* GotoTail(struct ListItem* item)
{
    // printf("goto -- %p\n", item);
    while (item->RightItem != NULL)
    {
        item = item->RightItem;
        // printf("goto -- %p\n", item);
    }
    return item;
}

void DeleteItem(struct ListItem *item)
{
    if (item->LeftItem != NULL) item->LeftItem->RightItem = item->RightItem;
    if (item->RightItem != NULL) item->RightItem->LeftItem = item->LeftItem;
    free(item);
}

int DeleteList(struct ListItem *list)
{
    int d=0;
    while (list->RightItem!=NULL || list->LeftItem != NULL)
    {

        if (list->RightItem != NULL ) DeleteItem(list->RightItem);
        if (list->LeftItem != NULL) DeleteItem(list->LeftItem);
        d++;
    }
    DeleteItem(list);
    d++;
    return d;
}

void PrintList(struct ListItem *item, char* str)
{
    #if DEBUG
        printf("\tList -> ");
    #endif
    do
    {
        PrintItem(item, str);
        putchar(' ');
        item = item->RightItem;
    } while(item != NULL);
    putchar('\n');
}

void ShowListItem(struct ListItem *item, char* str)
{
    printf("\nЭлемент списка %p", item);
    printf("\nСтроковое представление: ");
    PrintItem(item, str);
    printf("\n");
    char* s;
    switch (item->Type)
    {
        case OPERAND_TYPE: s = "Операнд"; break;
        case PARENTHESIS_TYPE: s = "Скобки"; break;
        case MULTIOLICATION_TYPE: s = "Умножение"; break;
        case DIVISION_TYPE: s = "Деление"; break;
        case MODULO_TYPE: s = "Остаток от деления"; break;
        case UNARY_PLUS_TYPE: s = "Унарный плюс"; break;
        case UNARY_MINUS_TYPE: s = "Унарный минус"; break;
        case BINARY_PLUS_TYPE: s = "Сложение"; break;
        case BINARY_MINUS_TYPE: s = "Вычитание"; break;
        default: s = "ERROR";
    }
    printf("Тип: %04X\t%s\n", item->Type, s);
    if (item->Type == OPERAND_TYPE) printf("Значение: %d\n", item->Value);
    printf("Left %p\n",item->LeftItem);
    printf("Rigt %p\n",item->RightItem);
}


void PrintItem(struct ListItem *item, char* str)
{
    switch (item->Type)
    {
        case OPERAND_TYPE:
            printf("%d", item->Value);
            break;
        case PARENTHESIS_TYPE:
        {
            int c = 1;
            int i = 0;
            putchar(str[item->Value+i++]);
            do
            {
                if (str[item->Value+i] == PARENTHESIS_OPEN_SYMVOL) c++;
                if (str[item->Value+i] == PARENTHESIS_CLOSE_SYMVOL) c--;
                putchar(str[item->Value+i++]);
            } while(c>0);
            break;
        }
        default: putchar(str[item->Value]);
    }
}

struct ListItem* UnaryPlus(struct ListItem * item)
{
    item -> Value = item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %c %d = %d\n", item->Type, item->RightItem->Value, item->Value);
    #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* UnaryMinus(struct ListItem * item)
{
    item -> Value = -1 * item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %c %d = %d\n", item->Type, item->RightItem->Value, item->Value);
    #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* BinaryPlus(struct ListItem * item)
{
    item->Value = item->LeftItem->Value + item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %d %c %d = %d\n", item->LeftItem->Value, item->Type, item->RightItem->Value, item->Value);
    #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->LeftItem);
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* BinaryMinus(struct ListItem * item)
{
    item->Value = item->LeftItem->Value - item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %d %c %d = %d\n", item->LeftItem->Value, item->Type, item->RightItem->Value, item->Value);
        #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->LeftItem);
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* Muliplication(struct ListItem * item)
{
    item -> Value = item->LeftItem->Value * item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %d %c %d = %d\n", item->LeftItem->Value, item->Type, item->RightItem->Value, item->Value);
    #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->LeftItem);
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* Division(struct ListItem * item)
{
    item -> Value = item->LeftItem->Value / item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %d %c %d = %d\n", item->LeftItem->Value, item->Type, item->RightItem->Value, item->Value);
    #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->LeftItem);
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* Modulo(struct ListItem * item)
{
    item -> Value = item->LeftItem->Value % item->RightItem->Value;
    #if VERBOSE
        printf("Вычисляем: %d %c %d = %d\n", item->LeftItem->Value, item->Type, item->RightItem->Value, item->Value);
    #endif
    item -> Type = OPERAND_TYPE;
    DeleteItem(item->LeftItem);
    DeleteItem(item->RightItem);
    return item;
}

struct ListItem* Operand(struct ListItem * item)
{
    return item;
}


// Функция проверяет является ли символ цифрой
// требует проверяемый символ
// возвращает 1 если утверждение истино и 0 если ложно.
int isDigit(char c)
{
    return (c>='0' && c<='9');
}

int isOperation(char c)
{
    return PARENTHESIS_OPEN_SYMVOL==c || PARENTHESIS_CLOSE_SYMVOL==c || MULTIOLICATION_SYMVOL==c || DIVISION_SYMVOL==c || \
           MODULO_SYMVOL==c || BINARY_PLUS_SYMVOL==c || BINARY_MINUS_SYMVOL==c || UNARY_PLUS_SYMVOL, UNARY_PLUS_SYMVOL;
}


// Функция для ввода строки с устройсва стандартного ввода
// требует указатель на массив символов и максимаьлную
// длинну строки
void InputStr(char* str, int MAX_STR_LEN)
{
    printf("введите строку\n> ");
    fgets(str, MAX_STR_LEN+1, stdin);
    int i;
    for (i = 0; str[i]!='\0' && str[i]!='\n'; ++i);
    str[i]='\0';
}

// Фукция составления строки из массива строк
// требует длинну массива строк, указатель на массив строк
// указатель на массив символов, максимальную длинну строки
// возвращает длинну строки
int StrFromArg(int argc, char** argv, char* str, int MAX_STR_LEN)
{
    int i;
    int k=0,l;
    for(i=0;(i<argc)&&(k<MAX_STR_LEN);i++)
    {
        l=0;
        while(argv[i][l]!='\0' && k<MAX_STR_LEN)
            str[k++]=argv[i][l++];
        str[k++]=' ';
    }
    str[--k]='\0';
    return k;
}
