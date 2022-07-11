#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

#define downArrow 80
#define upArrow 72
#define esc 27
#define enter 13
#define f1 59


//conio.c function headers
void gotoxy (int, int);
int SetColor(char);

//function headers 
int mainMenu();
int measureMenu();
int menuSelection(int, int);
int reprocessing();
double getAngle(int);
double convertMeasure(int, double);
double calculate(int, double);
void printHeader();
void printCalculus(int, double, double);
void cursor(int);

//global variables
int measure;

int main() {
	setlocale(LC_ALL, "Portuguese"); 
	cursor(0);
    
	int operation, out = 0;
    double angle, result;

	do{
		operation = mainMenu();
	    measure = measureMenu();
	
		if (operation < 7) angle = getAngle(1);
		else getAngle(0);
	
	    printCalculus(operation, angle, calculate(operation, angle));
	    getch();
	    
		out = reprocessing();	
	}while(!out); 

    return 0;
}

void printHeader(){
    system("cls");
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

    gotoxy(0,aux); printf(" >");
    while (!choice) {
        cursor = getch();
        gotoxy(0,aux); printf("  ");
        
        switch(cursor){
        	case upArrow:
        		if(aux == rowMin) aux = rowMax;
                    else aux --;
                    break;
            case downArrow:
            	if(aux == rowMax) aux = rowMin;
                    else aux++;
                    break;
            case enter:
            	choice = aux-rowMin+1;
		}
        
        gotoxy(0,aux); printf(" >");
    }
    
    return choice;
}

double convertMeasure(int operation, double angle){
    angle = operation ? angle * M_PI / 180 : angle * 180 / M_PI;
    
    return angle;
}

double getAngle(int op){
    double angle;

    printHeader();
    gotoxy(0,3); printf("Insira o valor: ");
    scanf("%lf", &angle);
    if(!op) {
    	return angle;	
	}
	if(measure != 1) angle = convertMeasure(1, angle);
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
	if(measure != 1 && operation < 7) angle = convertMeasure(0, angle);
    switch (operation) {
        case 1:
            /* seno */
            gotoxy(0,3); printf("Seno de %.2lf: %.3lf\n", angle, result);
            break;
        case 2:
            /* cosseno */
            gotoxy(0,3); printf("Cosseno de %.2lf: %.3lf\n", angle, result);
            break;
        case 3:
            /* tangente */
            gotoxy(0,3); printf("Tangente de %.2lf: %.3lf\n", angle, result);
            break;
        case 4:
            /* cossecante */
            gotoxy(0,3); printf("Cossecante de %.2lf: %.3lf\n", angle, result);
            break;
        case 5:
            /* secante */
            gotoxy(0,3); printf("Secante de %.2lf: %.3lf\n", angle, result);
            break;
        case 6:
            /* cotangente */
            gotoxy(0,3); printf("Cotangente de %.2lf: %.3lf\n", angle, result);
            break;
        case 7:
            /* arco seno */
            gotoxy(0,3); printf("arco seno de %.2lf: %.3lf\n", angle, result);
            break;
        case 8:
            /* arco cosseno */
            gotoxy(0,3); printf("arco cosseno de %.2lf: %.3lf\n", angle, result);
            break;
        case 9:
            /* arco tangente */
            gotoxy(0,3); printf("Arco tangente de %.2lf: %.3lf\n", angle, result);
            break;
    }
    
    gotoxy(10,5); printf("Pressione qualquer tecla para prosseguir.");
}

int reprocessing(){
	printHeader();
	gotoxy(3,3);printf("Deseja calcular novamente?");
	gotoxy(3,4);printf("Sim");
    gotoxy(3,5);printf("Não");
    return menuSelection(4,5);
}

//conio.c functions
//-------------------------------------------------------------------------
void gotoxy (int x, int y) {
  COORD pos = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//-------------------------------------------------------------------------
int SetColor (char color) {
  HANDLE h;
  h = GetStdHandle (STD_OUTPUT_HANDLE);
  return SetConsoleTextAttribute (h,color);
}
//-------------------------------------------------------------------------
void cursor (int x) {
	switch (x) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}
