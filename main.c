#include <stdio.h>
#include <math.h>
#include <gconio.h>

int mainMenu();
int measureMenu();
int menuSelection(int, int);

int main() {

    int operation, measure; 
    operation = mainMenu();
    measure = measureMenu();
    return 0;
}

int mainMenu() {
    clrscr();
    
    gotoxy(15,1); printf("CALCULADORA TRIGONOMETRICA\n\n");

    gotoxy(3,3); printf("Seno");
    gotoxy(3,4); printf("Cosseno");
    gotoxy(3,5); printf("Tangente");
    gotoxy(3,6); printf("Secante");
    gotoxy(3,7); printf("Cossecante");
    gotoxy(3,8); printf("Cotangente");
    
    return menuSelection(3,4);
}

int measureMenu(){
    clrscr();

    gotoxy(15,1); printf("CALCULADORA TRIGONOMETRICA\n\n");

    gotoxy(3,3);printf("Radianos");
    gotoxy(3,4);printf("Graus");

    return menuSelection(3,4);
}

int menuSelection(int rowMin, int rowMax){
    int choice = 0;
    int aux = rowMin;
    char cursor;

    gotoxy(0,aux); printf("> ");
    while (!choice) {
        cursor = getch();
        if (cursor == '\033') { // if the first value is esc
            getch(); // skip the [
            cursor = getch();
            gotoxy(0,aux); printf("  ");
            switch(cursor) { // the real value
                case 'A':
                    if(aux == rowMin) aux = rowMax;
                    else aux --;
                    break;
                case 'B':
                    if(aux == rowMax) aux = rowMin;
                    else aux++;
                    break;
            }
        }
        else if(cursor == 10){
            choice = aux-rowMin+1;
        }
        gotoxy(0,aux); printf("> ");
    }
    
    return choice;
}
