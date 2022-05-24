#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __tempcheck
{
    char date[20];
    int total;
    int total_die;
    int today;
    struct __tempcheck *prev;
    struct __tempcheck *next;
} Tempcheck;

void PrintData(Tempcheck *x, Tempcheck *head);
int Select(int a);
void Search(Tempcheck *x, Tempcheck *head);
void Delete(Tempcheck *x, Tempcheck *head);

int main(void)
{
    FILE *fp = fopen("data.csv", "r");
    int select = 0;
    printf("最新のデータを読み込んでいます・・・\n");
    system("python3 get_data.py"); //pythonを実行

    Tempcheck *dummy = malloc(1 * sizeof(Tempcheck));
    Tempcheck *head = dummy;
    Tempcheck *tail = dummy;
    dummy->prev = dummy->next = dummy;
    Tempcheck *x = malloc(1 * sizeof(Tempcheck));

    x = malloc(1 * sizeof(Tempcheck));
    while (fscanf(fp, "%s %d %d %d", x->date, &x->today, &x->total, &x->total_die) != EOF)
    {
        x->next = tail->next;
        x->prev = tail;
        tail->next->prev = x;
        tail->next = x;
        tail = tail->next;
        x = malloc(1 * sizeof(Tempcheck));
    }
    remove("data.csv");
    fclose(fp);
    PrintData(x, head);
    FILE *filep = fopen("data.csv", "w+");

    while (1)
    {
        select = Select(select);
        switch (select)
        {
        case 1:
            PrintData(x, head);
            break;
        case 2:
            printf("---------------検索を行います---------------\n");
            Search(x, head);
            break;
        case 3:
            Delete(x, head);
            break;
        case 4:
            for (x = head->next; x != head; x = x->next)
            {
                fprintf(filep, "%s %d %d %d\n", x->date, x->today, x->total, x->total_die);
            }
            exit(1);
        default:
            printf("********* 値が無効です *********\n");
            break;
        }
        /* code */
    }

    fclose(filep);
    return 0;
}

/*---一覧表示スクリプト-----*/
void PrintData(Tempcheck *x, Tempcheck *head)
{
    printf("-----日付---------新規感染者数---累計感染者数-----累計死亡者数----\n");
    for (x = head->next; x != head; x = x->next)
    {
        printf("%17s %11d %16d %14d\n", x->date, x->today, x->total, x->total_die);
    }
}

int Select(int a)
{
    printf("どのような操作をしますか？ 1:一覧表示, 2:日付検索, 3:削除, 4:終了 -> ");
    scanf("%d", &a);
    return a;
}

void Search(Tempcheck *x, Tempcheck *head)
{
    /*searchスクリプト*/

    int search_year;
    int search_month;
    int search_day;
    printf("何年のことを調べますか？");
    scanf("%d", &search_year);
    printf("何月のことを調べますか？");
    scanf("%d", &search_month);
    printf("何日のことを調べますか？");
    scanf("%d", &search_day);
    char search[20];
    sprintf(search, "%d年%d月%d日", search_year, search_month, search_day); //文字列に結合
    printf("%s\n", search);

    printf("検索します・・・・\n");
    int i = 0; //フラグの設定
    for (x = head->next; x != head; x = x->next)
    {
        if (strcmp(x->date, search) == 0)
        {
            printf("%sの新規感染者数は%d人, 累計感染者数は%d, 累計死亡者数は%dです。\n", x->date, x->today, x->total, x->total_die);
            printf("発見したデータに対応する構造体のアドレスは以下の通り。\n");
            printf("dete : %p\n", &x->date);
            printf("today : %p\n", &x->today);
            printf("total : %p\n", &x->total);
            printf("total_die : %p\n", &x->total_die);
            i++;
            break;
        }
    }
    if (i == 0)
    {
        printf("****** データが見つかりませんでした ******\n");
    }

    /*searchスクリプト*/
}


void Delete(Tempcheck *x, Tempcheck *head)
{
    /*searchスクリプト*/

    int search_year;
    int search_month;
    int search_day;
    printf("何年のデータですか？");
    scanf("%d", &search_year);
    printf("何月のデータですか？");
    scanf("%d", &search_month);
    printf("何日のデータですか？");
    scanf("%d", &search_day);
    char search[20];
    sprintf(search, "%d年%d月%d日", search_year, search_month, search_day); //文字列に結合
    int i = 0; //フラグの設定
    for (x = head->next; x != head; x = x->next)
    {
        if (strcmp(x->date, search) == 0)
        {
            int a;
            
            printf("***************%sのデータを本当に削除しますか？ (1/0) ***************** ->", x->date); scanf("%d", &a);
            if (a == 1) 
            {
                printf("%sのデータを削除します。\n",x->date);
                free(x); //メモリを開放
                x->next->prev= x->prev;
                x->prev->next= x->next;
            }
            else{
                printf("削除メニューを終了します\n");
            }
            i++;
            break;
        }
    }
    if (i == 0)
    {
        printf("****** データが見つかりませんでした ******\n");
    }

    /*searchスクリプト*/
}