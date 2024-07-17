/* https://kosenjp.sharepoint.com/:p:/r/sites/17toyama/gsmp/isp/_layouts/15/Doc.aspx */

#include <stdio.h>
#include <stdlib.h>

#define VAR_COUNT 15
#define TOPS 0, 3, 6, 8
#define TOPS_COUNT 4

int inc(int vars[VAR_COUNT], const int tops[TOPS_COUNT]);
int verify(const int vars[VAR_COUNT]);
void print_vars(const int vars[VAR_COUNT]);

int main()
{
    const int tops[TOPS_COUNT] = {TOPS};
    int vars[VAR_COUNT] = {0};

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
    int num1 = vars[0] * 100 + vars[1] * 10 + vars[2];
    int num2 = vars[3] * 100 + vars[4] * 10 + vars[5];
    int num3 = vars[6] * 100 + 50 + vars[7];
    int num4 = vars[8] * 100 + vars[9] * 10 + vars[10];
    int num5 = 500 + vars[11] * 10 + vars[12];
    int num6 = 55500 + vars[13] * 10 + vars[14];

    return num1 * vars[5] == num3    /**/
           && num1 * vars[4] == num4 /**/
           && num1 * vars[3] == num5 /**/
           && num1 * num2 == num6;   /**/
}

void print_vars(const int vars[VAR_COUNT])
{
    char text[61];
    int i = 0;
    i = sprintf(text, "    %d %d %d\n", vars[0], vars[1], vars[2]);
    i += sprintf(text + i, "  × %d %d %d\n", vars[3], vars[4], vars[5]);
    i += sprintf(text + i, "    %d 5 %d\n", vars[6], vars[7]);
    i += sprintf(text + i, "  %d %d %d\n", vars[8], vars[9], vars[10]);
    i += sprintf(text + i, "5 %d %d\n", vars[11], vars[12]);
    i += sprintf(text + i, "5 5 5 %d %d\n\n", vars[13], vars[14]);
}