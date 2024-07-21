/* https://kosenjp.sharepoint.com/:p:/r/sites/17toyama/gsmp/isp/_layouts/15/Doc.aspx */

#include <stdio.h>
#include <stdlib.h>

#define VAR_COUNT 6
#define TOPS 0, 3
#define TOPS_COUNT 2

int inc(int vars[VAR_COUNT], const int tops[TOPS_COUNT]);
int verify(const int vars[VAR_COUNT]);
void print_vars(const int vars[VAR_COUNT]);

int main()
{
    struct rusage r;
    struct timeval start, end;
    long res;
    const int tops[TOPS_COUNT] = {TOPS};
    int vars[VAR_COUNT] = {0};

    getrusage(RUSAGE_SELF, &r);
    start = r.ru_utime;

    for (size_t i = 0; i < TOPS_COUNT; i++)
        vars[tops[i]]++; /* 最上桁を1にする */

    do
    {
        if (verify(vars))
        {
            print_vars(vars);
            break;
        }

    } while (!inc(vars, tops));

    getrusage(RUSAGE_SELF, &r);
    end = r.ru_utime;
    res = ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;
    printf("%ldus\n", res);

    return 0;
}

/**
 * @brief 配列をインクリメントする。
 * @details 「使う数字は、5以外」、「最上位桁には0は入れない」について考慮する。
 * @param vars: 数字の配列
 * @param tops: 最上桁の指標
 * @return 最後まで到達していた場合1を返す。
 */
int inc(int vars[VAR_COUNT], const int tops[TOPS_COUNT])
{
    int fin = 1; /* 終了フラグ */

    for (size_t i = 0; i < VAR_COUNT; i++)
    {
        if (++vars[i] == 5)
            vars[i]++;

        if (vars[i] > 9)
        {
            vars[i] = 0;
            for (size_t j = 0; j < TOPS_COUNT; j++)
                if (i == j)
                    vars[i]++;
        }
        else
        {
            fin = 0;
            break;
        }
    }

    return fin;
}

/**
 * @brief 値が解を満たしているか検証する。
 * @details 「使う数字は、5以外」、「最上位桁には0は入れない」については検証しない。
 * @param vars: 検証する数字の配列。左上から右に向かって詰めていく。
 */
int verify(const int vars[VAR_COUNT])
{
    const int num1 = vars[0] * 100 + vars[1] * 10 + vars[2];
    const int num2 = vars[3] * 100 + vars[4] * 10 + vars[5];
    const int num3 = num1 * vars[5];
    const int num4 = num1 * vars[4];
    const int num5 = num1 * vars[3];
    const int num6 = num1 * num2;

    if (num3 > 1000 || num4 > 1000 || num5 > 1000 || num6 > 55600)
        return 0;

    if (num3 / 100 == 5 || num3 / 100 == 0 || (num3 / 10) % 10 != 5 || num3 % 10 == 5)
        return 0;

    if (num4 / 100 == 5 || num4 / 100 == 0 || (num4 / 10) % 10 == 5 || num4 % 10 == 5)
        return 0;

    if (num5 / 100 != 5 || (num5 / 10) % 10 == 5 || num5 % 10 == 5)
        return 0;

    if (55500 >= num6 || (num6 / 10) % 10 == 5 || num6 % 10 == 5)
        return 0;

    return 1;
}

void print_vars(const int vars[VAR_COUNT])
{
    const int num1 = vars[0] * 100 + vars[1] * 10 + vars[2];
    const int num2 = vars[3] * 100 + vars[4] * 10 + vars[5];
    const int num3 = num1 * vars[5];
    const int num4 = num1 * vars[4];
    const int num5 = num1 * vars[3];
    const int num6 = num1 * num2;
    char text[61];
    int i = 0;

    i = sprintf(text, "  %d\n", num1);
    i += sprintf(text + i, "x %d\n", num2);
    i += sprintf(text + i, "  %d\n", num3);
    i += sprintf(text + i, " %d\n", num4);
    i += sprintf(text + i, "%d\n", num5);
    sprintf(text + i, "%d\n", num6);

    puts(text);
}
