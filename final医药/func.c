// func.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "goods.h"
#include "func.h"

// 系统主页
unsigned int system_menu(void) {
    unsigned int se = 0;
    printf("**************************************\r\n");
    printf("      Ciallo～(∠.ω< )⌒☆\r\n");
    printf("   欢迎进入中医药商品交易平台    \r\n");
    printf("\r\n");
    printf("请选择下面的数字表明你的身份：\r\n");
    printf("1.管理员\r\n");
    printf("2.顾客\r\n");
    printf("3.退出系统\r\n");
    printf("**************************************\r\n");
    printf("--------------------------------------\r\n");
    printf("请选择对应的数字1~3\r\n");
    // 等待输入
start:
    scanf("%d", &se);
    if (se <= 0 || se > 3) {
        printf("输入错误，请重新输入\r\n");
        goto start;
    }
    return se;
}

// 输入页码界面
int manager_menu(void) {
    char input[20] = {0};
    char passwd[20] = {0};
    int err = 0, err_psd = 0;
    while (1) {
        printf("请输入管理员编号\r\n");
        scanf("%s", input);
        if (0 == strcmp("1234", input)) {
            printf("请输入管理员密码\r\n");
            scanf("%s", passwd);
            if (0 == strcmp("123456", passwd)) {
                return 1;
            } else {
                printf("管理员密码错误\r\n");
                if (++err_psd > 3) {
                    err_psd = 0;
                    return 0; // 输入错误超过三次，直接退出
                }
            }
        } else {
            printf("管理员编号错误\r\n");
            if (++err > 3) {
                return 0; // 输入错误超过三次，直接退出
            }
        }
    }
}

// 管理员界面
void mangager_menu(void) {
    int sel;
    while (1) {
        printf("请选择下面的数字进行操作:\r\n");
        printf("---------------------------\r\n");
        printf("1.录入商品信息:\r\n");
        printf("2.显示所有商品信息:\r\n");
        printf("3.返回上一层:\r\n");
        printf("4.退出程序:\r\n");
        printf("---------------------------\r\n");
        printf("请选择对应的数字1~4\r\n");
        scanf("%d", &sel);
        switch (sel) {
            case 1:
                add_shop_info();
                break;
            case 2: {
                FILE *fp = fopen("goods.txt", "r");
                if (fp == NULL) {
                    printf("打开文件失败\n");
                    break;
                }
                struct mar shop_info;
                printf("商品ID\t\t商品名称\t\t进价\t\t售价\t\t数量\t\t保质期\n");
                double inprice, outprice;
                while (fscanf(fp, "%11s  %21s  %lf %lf %d %12s", shop_info.ID, shop_info.brand, &inprice, &outprice, &shop_info.storage, shop_info.date) != EOF) {
                    shop_info.inprice = (int)round(inprice);
                    shop_info.outprice = (int)round(outprice);
                    printf("%s\t\t%s\t\t%.2lf\t\t%.2lf\t\t%d\t\t%s\n", shop_info.ID, shop_info.brand, (double)shop_info.inprice, (double)shop_info.outprice, shop_info.storage, shop_info.date);
                }
                fclose(fp);
                break;
            }
            case 3:
                return;
            case 4:
                exit(0);
            default:
                printf("输入错误，请重新输入\r\n");
        }
    }
}

// 录入商品信息
void add_shop_info(void) {
    int num = 0, i = 0, store_num = 0;
    struct mar shop_info[10];
    FILE *fp = NULL;
    printf("请输入需要录入的商品个数\r\n");
    scanf("%d", &num);
    printf("请依次输入商品信息\r\n");
    printf("---------------------------------------------\r\n");
    store_num = num;
    double inprice, outprice;
    while (num) {
        printf("第%d个商品\r\n", i + 1);
        printf("商品ID: ");
        scanf("%s", shop_info[i].ID);
        printf("商品名称：");
        scanf("%s", shop_info[i].brand);
        printf("进价：");
        scanf("%lf", &inprice);
        shop_info[i].inprice = (int)round(inprice);
        printf("售价：");
        scanf("%lf", &outprice);
        shop_info[i].outprice = (int)round(outprice);
        printf("数量：");
        scanf("%d", &shop_info[i].storage);
        printf("保质期：");
        scanf("%s", shop_info[i].date);
        i++;
        num--;
    }
    fp = fopen("goods.txt", "w");
    if (fp == NULL) {
        printf("打开文件失败");
        return;
    }
    i = 0;
    while (store_num) {
        fprintf(fp, "%11s  %21s  %.2lf %.2lf %d %12s\n", shop_info[i].ID, shop_info[i].brand, (double)shop_info[i].inprice, (double)shop_info[i].outprice, shop_info[i].storage, shop_info[i].date);
        i++;
        store_num--;
    }
    fclose(fp);
}

// 显示所有商品信息
void display_all_goods(void) {
    FILE *fp = fopen("goods.txt", "r");
    if (fp == NULL) {
        printf("打开文件失败\n");
        return;
    }
    struct mar shop_info;
    printf("商品ID\t\t商品名称\t\t进价\t\t售价\t\t数量\t\t\t保质期\n");
    double inprice, outprice;
    while (fscanf(fp,  "%11s    %21s    %lf    %lf    %d    %12s", shop_info.ID, shop_info.brand, &inprice, &outprice, &shop_info.storage, shop_info.date) != EOF) {
        shop_info.inprice = (int)round(inprice);
        shop_info.outprice = (int)round(outprice);
        printf("%s\t\t%s\t\t\t%.2lf\t\t%.2lf\t\t%d\t\t\t%s\n", shop_info.ID, shop_info.brand, (double)shop_info.inprice, (double)shop_info.outprice, shop_info.storage, shop_info.date);
    }
    fclose(fp);
}

// 更新商品库存
int update_goods_storage(struct mar goods, int num) {
    FILE *fp = fopen("goods.txt", "r");
    if (fp == NULL) {
        printf("打开文件失败\n");
        return 0;
    }
    struct mar shop_info;
    struct mar temp_info[100];
    int i = 0;
    int found = 0;
    double inprice, outprice;
    char goods_id_trimmed[12];
    sscanf(goods.ID, "%s", goods_id_trimmed); // 去除传入goods.ID的前后空格

    while (fscanf(fp, "%11s  %21s  %lf %lf %d %12s", shop_info.ID, shop_info.brand, &inprice, &outprice, &shop_info.storage, shop_info.date) != EOF) {
        shop_info.inprice = (int)round(inprice);
        shop_info.outprice = (int)round(outprice);
        
        char current_id_trimmed[12];
        sscanf(shop_info.ID, "%s", current_id_trimmed); // 去除文件中的ID前后空格

        if (strcmp(current_id_trimmed, goods_id_trimmed) == 0) {
            if (shop_info.storage < num) {
                printf("库存不足，无法购买\n");
                fclose(fp);
                return 0;
            }
            shop_info.storage -= num;
            found = 1;
        }
        temp_info[i++] = shop_info;
    }
    fclose(fp);
    if (!found) {
        printf("未找到该商品\n");
        return 0;
    }
    fp = fopen("goods.txt", "w");
    if (fp == NULL) {
        printf("打开文件失败\n");
        return 0;
    }
    for (int j = 0; j < i; j++) {
        fprintf(fp, "%11s  %21s  %.2lf %.2lf %d %12s\n", temp_info[j].ID, temp_info[j].brand, (double)temp_info[j].inprice, (double)temp_info[j].outprice, temp_info[j].storage, temp_info[j].date);
    }
    fclose(fp);
    return 1;
}

// 检查商品是否过期
int is_goods_expired(struct mar goods) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    int year, month, day;
    sscanf(goods.date, "%d-%d-%d", &year, &month, &day);
    struct tm exp_date = {0};
    exp_date.tm_year = year - 1900;
    exp_date.tm_mon = month - 1;
    exp_date.tm_mday = day;
    exp_date.tm_hour = 23;
    exp_date.tm_min = 59;
    exp_date.tm_sec = 59;
    time_t exp_time = mktime(&exp_date);
    return difftime(exp_time, now) < 0;
}

void checkout_shopping_cart(void) {
    struct node *p = shopping_cart_head;
    double total_price = 0;
    if (p == NULL) {
        printf("购物车为空，无需结算\n");
        return;
    }

    // 一次性读取所有商品到内存
    FILE *fp = fopen("goods.txt", "r");
    if (fp == NULL) {
        printf("打开文件失败\n");
        return;
    }
    struct mar temp_info[1000];
    int count = 0;
    double inprice, outprice;
    while (fscanf(fp, "%11s  %21s  %lf %lf %d %12s",
                temp_info[count].ID, temp_info[count].brand, &inprice, &outprice,
                &temp_info[count].storage, temp_info[count].date) != EOF) {
        temp_info[count].inprice = (int)round(inprice);
        temp_info[count].outprice = (int)round(outprice);
        count++;
    }
    fclose(fp);

    // 遍历购物车，更新内存中的库存
    printf("结算信息如下：\n");
    printf("货号\t\t品名\t\t单价\t\t购买数量\t\t总价\n");
    p = shopping_cart_head;
    while (p != NULL) {
        if (is_goods_expired(p->buy)) {
            printf("商品 %s 过期还买\n", p->buy.brand);
            p = p->next;
            continue;
        }

        // 去除商品ID前后空格以匹配
        char goods_id_trimmed[12];
        sscanf(p->buy.ID, "%s", goods_id_trimmed);

        int found = 0;
        for (int i = 0; i < count; i++) {
            char current_id_trimmed[12];
            sscanf(temp_info[i].ID, "%s", current_id_trimmed);

            if (strcmp(current_id_trimmed, goods_id_trimmed) == 0) {
                if (temp_info[i].storage >= p->number) {
                    temp_info[i].storage -= p->number;
                    found = 1;
                    break;
                } else {
                    printf("商品 %s 卖完啦QAQ\n", p->buy.brand);
                    break;
                }
            }
        }

        if (found) {
            double item_total = (double)p->buy.outprice * p->number;
            printf("%s\t\t%s\t\t%.2lf\t\t%d\t\t%.2lf\n", 
                   p->buy.ID, p->buy.brand, (double)p->buy.outprice, p->number, item_total);
            total_price += item_total;
        } else {
            printf("商品 %s 未找到或库存不足\n", p->buy.brand);
        }

        p = p->next;
    }

    // 将更新后的数据一次性写入文件
    fp = fopen("goods.txt", "w");
    if (fp == NULL) {
        printf("打开文件失败\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%11s  %21s  %.2lf %.2lf %d %12s\n",
                temp_info[i].ID, temp_info[i].brand,
                (double)temp_info[i].inprice, (double)temp_info[i].outprice,
                temp_info[i].storage, temp_info[i].date);
    }
    fclose(fp);

    printf("总金额：%.2lf\n", total_price);
    printf("--------------------------------------\n");
    printf("一次买够！\n"); 
    printf("--------------------------------------\n");
    

    clear_shopping_cart();
}

// 顾客购物车编辑界面
void edit_shopping_cart(void) {
    struct mar goods;
    int number;
    int choice;
    char confirm;
    while (1) {
        printf("\n顾客购物车操作界面\n");
        printf("1. 添加商品到购物车\n");
        printf("2. 查看购物车信息\n");
        printf("3. 清空购物车\n");
        printf("4. 查看商店物品内容\n");
        printf("5. 结算购物车\n");
        printf("6. 退出编辑\n");
        printf("7. 一次买够（所有商品各买一份并结算）\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        switch (choice) {
		      case 1: {
		        printf("请输入商品货号: ");
		        char search_id[12];
		        scanf("%s", search_id);
		        
		        FILE* fp = fopen("goods.txt", "r");
		        if (fp == NULL) {
		            printf("商品库文件不存在\n");
		            break;
		        }
		        
		        int found = 0;
		        double inprice, outprice;
		        while (fscanf(fp, "%11s  %21s  %lf %lf %d %12s",
		                    goods.ID, goods.brand, &inprice, &outprice,
		                    &goods.storage, goods.date) != EOF) {
		            goods.inprice = (int)round(inprice);
		            goods.outprice = (int)round(outprice);
		            
		            char current_id[12];
		            sscanf(goods.ID, "%s", current_id); // 去除文件中的ID空格
		            if (strcmp(current_id, search_id) == 0) {
		                found = 1;
		                break;
		            }
		        }
		        fclose(fp);
                
                if (!found) {
                    printf("未找到该商品\n");
                    break;
                }
                
                printf("请输入购买数量: ");
                scanf("%d", &number);
                printf("是否确认购买该商品？(y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    add_to_cart(goods, number);
                }
                break;
            }
            case 2:
                print_shopping_cart_info();
                break;
            case 3:
                printf("是否确认清空购物车？(y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    clear_shopping_cart();
                    printf("购物车已清空喵\n");
                }
                break;
            case 4:
                display_all_goods();
                break;
            case 5:
                printf("是否确认结算购物车？(y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    checkout_shopping_cart();
                }
                break;
            case 6:
                return;
            case 7: {
            printf("确认一次购买所有商品各一份？当前购物车将被清空。(y/n): ");
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                clear_shopping_cart();  // 清空现有购物车
                
                // 读取所有商品并添加到购物车
                FILE *fp = fopen("goods.txt", "r");
                if (fp == NULL) {
                    printf("商品库文件不存在\n");
                    break;
                }
                double inprice, outprice;
                int added_count = 0;
                while (fscanf(fp, "%11s  %21s  %lf %lf %d %12s",
                            goods.ID, goods.brand, &inprice, &outprice,
                            &goods.storage, goods.date) != EOF) {
                    goods.inprice = (int)round(inprice);
                    goods.outprice = (int)round(outprice);
                    
                    // 检查库存和保质期
                    if (goods.storage >= 1 && !is_goods_expired(goods)) {
                        add_to_cart(goods, 1);  // 每个商品添加1份
                        added_count++;
                    } else {
                        printf("商品 [%s] 库存不足或已过期，跳过\n", goods.brand);
                    }
                }
                fclose(fp);
                
                if (added_count > 0) {
                    printf("已添加 %d 种商品到购物车，正在结算...\n", added_count);
                    checkout_shopping_cart();  // 自动进入结算
                } else {
                    printf("没有可购买的商品\n");
                }
            }
            break;
            }
            default:
                printf("输入错误，请重新输入\n");
        }
    }
}