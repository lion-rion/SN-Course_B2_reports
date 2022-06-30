#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct __tempcheck
{
    char date[20];
    int total;
    int total_die;
    int today;
} Tempcheck;

void PrintData(Tempcheck *x, int nx);
void quick_sort(Tempcheck *arr, int left, int right);
void bubble_sort(Tempcheck *arr, int n);
int Select(int a);

//do quick sort


int main(void)
{
    clock_t start, end; //計測用の時間を格納する変数
    FILE *fp = fopen("data.csv", "r");
    Tempcheck test[1000];
    int select = 0;
    printf("データを読み込んでいます・・・\n");
    int i = 0;
    while (fscanf(fp, "%s %d %d %d", test[i].date, &test[i].today, &test[i].total, &test[i].total_die) != EOF)
    {
        i++;
    }
    fclose(fp);
    int nx = i;
    PrintData(test, nx);
    printf("\n");
    while (1)
    {
        select = Select(select);
        switch (select)
        {
        case 1:
            PrintData(test, nx);
            break;
        case 2:
            printf("---------------降順にクイックソートを行います---------------\n");
               //クイックソートの時間を計測する
            
            start = clock();
            quick_sort(test, 0, nx - 1);
             /* 処理終了時の時間と、開始時の時間の差(経過した時間…msec単位)を取得 */
            end = clock();
            /* 経過時間を表示 */
            printf("クイックソートの時間: %f msec\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

            PrintData(test, nx);
           
            break;
        case 3:
            printf("---------------降順にバブルソートを行います---------------\n");
            start = clock();
            bubble_sort(test, nx);
            /* 処理終了時の時間と、開始時の時間の差(経過した時間…msec単位)を取得 */
            end = clock();
            /* 経過時間を表示 */
            printf("バブルソートの時間: %f msec\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
            
            PrintData(test, nx);
            break;
        case 4:
            printf("---------------新規感染者数を上位表示します---------------\n");
            quick_sort(test, 0, nx - 1);
            //上位表示
            printf("-----日付------新規感染者数---累計感染者数-----累計死亡者数----\n");
            for (i = 0; i < 3; i++)
            {
                
                printf("%10s %10d %16d %14d\n", test[i].date, test[i].today, test[i].total, test[i].total_die);
            }
            break;
        case 5:
            //testをcsvに書き込み
            fp = fopen("data.csv", "w");
            for (i = 0; i < nx; i++)
            {
                fprintf(fp, "%s %d %d %d\n", test[i].date, test[i].today, test[i].total, test[i].total_die);
            }
            fclose(fp);
            
            exit(1);
        default:
            printf("********* 値が無効です *********\n");
            break;
        }
        /* code */
    }
    return 0;
    
}

void PrintData(Tempcheck *x, int nx)
{
    printf("-----日付------新規感染者数---累計感染者数-----累計死亡者数----\n");
    for (int i = 0; i < nx; i++)
    {
        printf("%10s %10d %16d %14d\n", x[i].date, x[i].today, x[i].total, x[i].total_die);
    }
}

int Select(int a)
{
    printf("どのような操作をしますか？ 1:一覧表示, 2:降順にクイックソート, 3:降順にバブルソート, 4:新規感染者数を上位表示, 5:終了 -> ");
    scanf("%d", &a);
    return a;
}
//降順にクイックソート
void quick_sort(Tempcheck *arr, int left, int right)

{
    int i = left, j = right;
    Tempcheck tmp[1];
    int pivot = arr[(left + right) / 2].today;
    while (i <= j)
    {
        while (arr[i].today > pivot)
            i++;
        while (arr[j].today < pivot)
            j--;
        if (i <= j)
        {
            tmp[0] = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp[0];
            i++;
            j--;
        }
    };
    if (left < j)
        quick_sort(arr, left, j);
    if (i < right)
        quick_sort(arr, i, right);

    
}

//do bubble sort
void bubble_sort(Tempcheck *arr, int n)
{
    int i, j;
    Tempcheck tmp[1];
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].today < arr[j + 1].today)
            {
                tmp[0] = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp[0];
            }
        }
    }
}