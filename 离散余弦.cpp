#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#pragma warning (disable:4996);//解决出现如“scanf、fopen等要替换为scanf_s、fopen_s等类似问题

int main()
{
    int r = 8, c = 8, x = 0, y = 0;
    int u = 0, v = 0;
    //矩阵a为原始矩阵，矩阵b的所有元素值为n
    int a[8][8] = { {52,55,61,66,70,61,64,73},
                    {63,59,55,90,109,85,69,72},
                    {62,59,68,113,144,104,66,73},
                    {63,58,71,122,154,106,70,69},
                    {67,61,68,104,126,88,68,70},
                    {79,65,60,70,77,68,58,75},
                    {85,71,64,59,55,61,65,83},
                    {87,79,69,68,65,76,78,94} };
    int b[8][8], g[8][8];
    double G[8][8];
    double pai = 3.1415926;
    double a_u = 0., a_v = 0.;
    /*printf("输入矩阵的行与列: ");
    scanf_s("%d %d", &r, &c);*/

    //b矩阵
    for (x = 0; x < r; x++){
        for (y = 0; y < c; y++)
        {
            b[x][y] = 128;
        }
    }

    //存储矩阵a的元素
    /*printf("输入矩阵a元素:\n");
    for (x = 0; x < r; x++){
        for (y = 0; y < c; y++)
        {
            printf("输入元素 a%d%d: ", x + 1, y + 1);
            scanf_s("%d", &a[x][y]);
        }
    }*/

    //显示原矩阵 a[][] 
    printf("\n原矩阵: \n\n");
    for (x = 0; x < r; x++){
        for (y = 0; y < c; y++)
        {
            printf("%4d  ", a[x][y]);
            if (y == c - 1)
                printf("\n");
        }
    }

    //数值移位，变成-128~127
    for (x = 0; x < r; x++){
        for (y = 0; y < c; y++) {
            g[x][y] = a[x][y] - b[x][y];
        }
    }

    //显示数值移位后的矩阵 g
    printf("\n数值移位后的矩阵:\n\n");
    for (x = 0; x < c; x++){
        for (y = 0; y < r; y++)
        {
            printf("%4d  ", g[x][y]);
            if (y == r - 1)
                printf("\n");
        }
    }

    //根据DCT变换公式计算
    /*printf("a_u:\n");*/
    for (u = 0; u < r; u++){
        for (v = 0; v < c; v++) {
            double cos_product = 0.;
            //u,v各有两种不同情况，所以a_u,a_v各有两个不同的值
            if (u == 0) {
                a_u = 1. / sqrt((double)r); //本题涉及的是8*8矩阵，所以N用行数r来代替
            }
            else {
                a_u = sqrt(2. / (double)r);
            }
            if (v == 0) {
                a_v = 1. / sqrt((double)r);
            }
            else {
                a_v = sqrt(2. / (double)r);
            }
            //输出a_u做测试用
            /*printf("a_u:\n");
            printf("%3.2f  ", a_u);
            if (v == c - 1)
                printf("\n");*/
            for (x = 0; x < r; x++)
                for (y = 0; y < c; y++) {
                    cos_product += (double)g[x][y] * cos(((2. * (double)x + 1.) * (double)u * pai) / (2. * (double)r))
                        * cos(((2. * (double)y + 1.)* (double)v * pai) / (2. * (double)r));
                }
            G[u][v] = a_u * a_v * cos_product;
        }
    }

    //显示DCT变换后的矩阵G
    printf("\nDCT变换后的矩阵G:\n\n");
    for (u = 0; u < r; u++){
        for (v = 0; v < c; v++) {
            printf("%9.2f  ", G[u][v]);
            if (v == c - 1)
                printf("\n");
        }
    }

    //量化,Q为量化表
    int B[8][8], Q[8][8] = { {16,11,10,16,24,40,51,61},
                    {12,12,14,19,26,58,60,55},
                    {14,13,16,24,40,57,69,56},
                    {14,17,22,29,51,87,80,62},
                    {18,22,37,56,68,109,103,77},
                    {24,35,55,64,81,104,113,92},
                    {49,64,78,87,103,121,120,101},
                    {72,92,95,98,112,100,103,99} };
    printf("\n量化后矩阵B:\n\n");
    for (x = 0; x < r; x++) {
        for (y = 0; y < c; y++) {
            B[x][y] = round(G[x][y] / Q[x][y]);//round函数，四舍五入
            printf("%6d  ", B[x][y]);
            if (y == c - 1)
                printf("\n");
        }
    }

    //解码,根据量化表Q恢复
    int B_L[8][8];
    printf("\n恢复量化后矩阵B_L:\n\n");
    for (x = 0; x < r; x++) {
        for (y = 0; y < c; y++) {
            B_L[x][y] = B[x][y] * Q[x][y];
            printf("%6d  ", B_L[x][y]);
            if (y == c - 1)
                printf("\n");
        }
    }

    //反离散余弦变换
    double  B_L_D[8][8] = { 0 };
    for (x = 0; x < r; x++) {
        for (y = 0; y < c; y++) {
            for (u = 0; u < r; u++)
                for (v = 0; v < c; v++) {
                    //u,v各有两种不同情况，所以a_u,a_v各有两个不同的值
                    if (u == 0) {
                        a_u = 1. / sqrt((double)r); //本题涉及的是8*8矩阵，所以N用行数r来代替
                    }
                    else {
                        a_u = sqrt(2. / (double)r);
                    }
                    if (v == 0) {
                        a_v = 1. / sqrt((double)r);
                    }
                    else {
                        a_v = sqrt(2. / (double)r);
                    }
                    //为保证精度，使用double类型
                    B_L_D[x][y] += a_u * a_v * (double)B_L[u][v] * cos(((2. * (double)x + 1.) * (double)u * pai) / (2. * (double)r))
                        * cos(((2. * (double)y + 1.)* (double)v * pai) / (2. * (double)r));
                }
        }
    }

    //显示反离散余弦变换后的矩阵B_L_D
    printf("\n反离散余弦变换后的矩阵B_L_D:\n\n");
    for (u = 0; u < r; u++) {
        for (v = 0; v < c; v++) {
            printf("%6d  ", (int)B_L_D[u][v]);//将double类型的数组强制转化为int类型输出
            if (v == c - 1)
                printf("\n");
        }
    }

    //数值右移127，恢复原始数据
    int B_L_D_R[8][8];
    printf("\n数据右移后的矩阵B_L_D_R:\n\n");
    for (x = 0; x < r; x++) {
        for (y = 0; y < c; y++) {
            B_L_D_R[x][y] = (int)B_L_D[x][y] + b[x][y];
            printf("%6d  ", B_L_D_R[x][y]);
            if (y == c - 1)
                printf("\n");
        }
    }
    
    return 0;
}