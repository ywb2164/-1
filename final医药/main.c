#include <stdio.h>
#include "goods.h"
#include "func.h"

int main() {
    unsigned int choice = system_menu();
    switch (choice) {
        case 1:
            if (manager_menu()) {
                mangager_menu();
            }
            break;
        case 2:
            edit_shopping_cart();
            break;
        case 3:
            return 0;
    }
    return 0;
}