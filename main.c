#include <stdio.h>
#include <math.h>
#include <gconio.h>

//function headers 
int mainMenu();
int measureMenu();
int menuSelection(int, int);
int reprocessing();
double getAngle();
double convertMeasure(double);
double calculate(int, double);
void printHeader();
void printCalculus(int, double, double);

//global variables
int measure;

int main() {

    int operation;
    double angle, result;

    operation = mainMenu();
    measure = measureMenu();

    angle = getAngle();

    printCalculus(operation, angle, calculate(operation, angle));   

    return 0;
}

void printHeader(){
    clrscr();
    gotoxy(15,1); printf("CALCULADORA TRIGONOMETRICA");
}

int mainMenu() {
    printHeader();

    gotoxy(3,3); printf("Seno");
    gotoxy(3,4); printf("Cosseno");
    gotoxy(3,5); printf("Tangente");
    gotoxy(3,6); printf("Cossecante");
    gotoxy(3,7); printf("Secante");
    gotoxy(3,8); printf("Cotangente");
    gotoxy(3,9); printf("Arcoseno");
    gotoxy(3,10); printf("Arcocosseno");
    gotoxy(3,11); printf("Arcotangente");

    return menuSelection(3,11);
}

int measureMenu(){
    printHeader();

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
        if (cursor == '\033') {
            getch();
            cursor = getch();
            gotoxy(0,aux); printf("  ");
            switch(cursor) {
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

double convertMeasure(double angle){
    angle *= M_PI / 180;

    return angle;
}

double getAngle(){
    double angle;

    printHeader();
    gotoxy(0,3); printf("Insira o valor: ");
    scanf("%lf", &angle);
    if(measure != 1) angle = convertMeasure(angle);

    return angle;
}

double calculate(int operation, double angle) {
    switch (operation) {
        case 1:
            /* seno */
            return sin(angle);
        case 2:
            /* cosseno */
            return cos(angle);
        case 3:
            /* tangente */
            return tan(angle);
        case 4:
            /* cossecante */
            return 1/sin(angle);
        case 5:
            /* secante */
            return 1/cos(angle);
        case 6:
            /* cotangente */
            return 1/tan(angle);
        case 7:
            /* arco seno */
            return asin(angle);
        case 8:
            /* arco cosseno */
            return acos(angle);
        case 9:
            /* arco tangente */
            return atan(angle);

    }
}

void printCalculus(int operation, double angle, double result) {
    switch (operation) {
        case 1:
            /* seno */
            gotoxy(0,3); printf("Seno de %.5lf: %.3lf\n", angle, result);
            break;
        case 2:
            /* cosseno */
            gotoxy(0,3); printf("Cosseno de %.5lf: %.3lf\n", angle, result);
            break;
        case 3:
            /* tangente */
            gotoxy(0,3); printf("Tangente de %.5lf: %.3lf\n", angle, result);
            break;
        case 4:
            /* cossecante */
            gotoxy(0,3); printf("Cossecante de %.5lf: %.3lf\n", angle, result);
            break;
        case 5:
            /* secante */
            gotoxy(0,3); printf("Secante de %.5lf: %.3lf\n", angle, result);
            break;
        case 6:
            /* cotangente */
            gotoxy(0,3); printf("Cotangente de %.5lf: %.3lf\n", angle, result);
            break;
        case 7:
            /* arco seno */
            gotoxy(0,3); printf("arco seno de %.5lf: %.3lf\n", angle, result);
            break;
        case 8:
            /* arco cosseno */
            gotoxy(0,3); printf("arco cosseno de %.5lf: %.3lf\n", angle, result);
            break;
        case 9:
            /* arco tangente */
            gotoxy(0,3); printf("Arco tangente de %.5lf: %.3lf\n", angle, result);
            break;
    }
}

