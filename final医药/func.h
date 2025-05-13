// func.h
#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goods.h"

unsigned int system_menu(void);
int manager_menu(void);
void mangager_menu(void);
void add_shop_info(void);
void edit_shopping_cart(void);
void display_all_goods(void);
int update_goods_storage(struct mar goods, int num);
int is_goods_expired(struct mar goods);
void checkout_shopping_cart(void);

#endif