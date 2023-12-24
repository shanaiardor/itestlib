#ifndef __74hc138_H__
#define __74hc138_H__

#include <reg52.h>

typedef unsigned long u32;
typedef unsigned int u16;
typedef unsigned char u8;

// 定义 address input
#define LSA P22
#define LSB P23
#define LSC P24
// 定义 数码管驱动管脚
#define DATA_138 P0

u8 buff[8]; // 显示缓冲数组

// 分别显示0 1 2 3 4 5 6 7 8 9  空
u8 font[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};

void delay_ms(u16 t)
{
    u16 i, j;
    for (i = 0; i < t; i++) {
        for (j = 0; j < 120; j++)
            ;
    }
}

void Delay200us() //@11.0592MHz
{
    unsigned char i, j;

    i = 3;
    j = 35;
    do {
        while (--j)
            ;
    } while (--i);
}

void Delay100us() //@11.0592MHz
{
    unsigned char i, j;

    i = 2;
    j = 15;
    do {
        while (--j)
            ;
    } while (--i);
}

// 更新缓冲数组
void update(u32 val)
{
    int i;
    for (i = 0; i < 8; i++) {

        if (val == 0) {
            buff[i] = 10;
        } else {
            buff[i] = val % 10;
        }
        val /= 10;
    }
}

void flush(void)
{
    u8 n;
    for (n = 0; n < 8; n++) {
        switch (n) // 先位选
        {
            case 0:
                LSC = 0;
                LSB = 0;
                LSA = 0;
                break;
            case 1:
                LSC = 0;
                LSB = 0;
                LSA = 1;
                break;
            case 2:
                LSC = 0;
                LSB = 1;
                LSA = 0;
                break;
            case 3:
                LSC = 0;
                LSB = 1;
                LSA = 1;
                break;
            case 4:
                LSC = 1;
                LSB = 0;
                LSA = 0;
                break;
            case 5:
                LSC = 1;
                LSB = 0;
                LSA = 1;
                break;
            case 6:
                LSC = 1;
                LSB = 1;
                LSA = 0;
                break;
            case 7:
                LSC = 1;
                LSB = 1;
                LSA = 1;
                break;
        }
        DATA_138 = font[buff[n]]; // 后发送段数据
        delay_ms(1);              // 小延时
    }
}

void display(void) // 8位数码管显示函数
{
    for (size_t i = 0; i < 10; i++) {
        flush();
    }
}

#endif
