#include "goods.h"

// 全局链表头指针，代表购物车
struct node *shopping_cart_head = NULL;

// 添加商品到购物车
void add_to_cart(struct mar goods, int num) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }
    new_node->buy = goods;
    new_node->number = num;
    new_node->next = shopping_cart_head;
    shopping_cart_head = new_node;
}

// 打印购物车信息
void print_shopping_cart_info(void) {
    struct node *p = shopping_cart_head;
    if (p == NULL) {
        printf("购物车为空\n");
        return;
    }
    printf("购物车内容如下：\n");
    printf("货号\t\t品名\t\t购买数量\n");
    while (p != NULL) {
        printf("%s\t\t%s\t\t%d\n", p->buy.ID, p->buy.brand, p->number);
        p = p->next;
    }
}

// 清空购物车
void clear_shopping_cart(void) {
    struct node *p = shopping_cart_head;
    struct node *temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
    shopping_cart_head = NULL;
}