#ifndef GOODS_H
#define GOODS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 商品结构体
struct mar {
    char ID[12];
    char brand[22];
    double inprice;
    double outprice;
    int storage;
    char date[13];
};

// 购物车节点结构体
struct node {
    struct mar buy;
    int number;
    struct node *next;
};

// 全局链表头指针
extern struct node *shopping_cart_head;

// 函数声明
void add_to_cart(struct mar goods, int num);
void print_shopping_cart_info(void);
void clear_shopping_cart(void);

#endif