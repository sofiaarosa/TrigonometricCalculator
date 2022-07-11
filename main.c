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
void cursor(int);
int SetColor(char);

//function headers 
int mainMenu();
int measureMenu();
int menuSelection(int, int);
int reprocessing();
double getValue();
double convertMeasure(int, double);
double calculate(double);
void printHeader();
void printCalculus(double, double);


//global variables
int measure, operation;

int main() {
	setlocale(LC_CTYPE, "Portuguese"); 
	cursor(0);
    
	int out = 0;
    double value, result;

	do{
		value = 0; result = 0;
		operation = mainMenu();
	    measure = measureMenu();
	
		value = getValue();
	
	    printCalculus(value, calculate(value));
	    getch();
	    
		out = reprocessing();	
	}while(out != 2); 

    return 0;
}

void printHeader(){
    system("cls");
    gotoxy(15,1); printf("CALCULADORA TRIGONOMETRICA");
}

int mainMenu() {
    printHeader();

	gotoxy(3,3); printf("Selecione a operação a ser realizada: ");
    gotoxy(3,4); printf("Seno");
    gotoxy(3,5); printf("Cosseno");
    gotoxy(3,6); printf("Tangente");
    gotoxy(3,7); printf("Cossecante");
    gotoxy(3,8); printf("Secante");
    gotoxy(3,9); printf("Cotangente");
    gotoxy(3,10); printf("Arcoseno");
    gotoxy(3,11); printf("Arcocosseno");
    gotoxy(3,12); printf("Arcotangente");

    return menuSelection(4,12);
}

int measureMenu(){
    printHeader();

	gotoxy(3,3);
	if(operation<7)printf("Ângulo de entrada medido em: ");
	else printf("Resultado em: ");
	
    gotoxy(3,4);printf("Radianos");
    gotoxy(3,5);printf("Graus");

    return menuSelection(4,5);
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

double convertMeasure(int direction, double angle){
	
	if(direction == 1) angle *= M_PI / 180;
	else angle *= 180 / M_PI;
    
    return angle;
}

double getValue(){
    double v;

    printHeader();
    gotoxy(0,3); printf("Insira o valor: ");
    scanf(" %lf", &v);
    
    //if operation is asin, acos, atg => doesn't convert at all
    if(operation >= 7){
    	return v;
	}
    
    //if angle given in degrees convert to radians
	if(measure != 1) {
		v = convertMeasure(1, v);	
	}
	
    return v;
}

double calculate(double angle) {
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

void printCalculus(double value, double result) {
	//if degrees selected in first place, convert from rad back to degrees
	//but only if operation isn't any of arc functions
	if(measure != 1) {
		if(operation < 7)
			value = convertMeasure(0, value);
		else 
			result = convertMeasure(0,result);
	}
    switch (operation) {
        case 1:
            /* seno */
            gotoxy(0,3); printf("Seno de %.2lf: %.3lf\n", value, result);
            break;
        case 2:
            /* cosseno */
            gotoxy(0,3); printf("Cosseno de %.2lf: %.3lf\n", value, result);
            break;
        case 3:
            /* tangente */
            gotoxy(0,3); printf("Tangente de %.2lf: %.3lf\n", value, result);
            break;
        case 4:
            /* cossecante */
            gotoxy(0,3); printf("Cossecante de %.2lf: %.3lf\n", value, result);
            break;
        case 5:
            /* secante */
            gotoxy(0,3); printf("Secante de %.2lf: %.3lf\n", value, result);
            break;
        case 6:
            /* cotangente */
            gotoxy(0,3); printf("Cotangente de %.2lf: %.3lf\n", value, result);
            break;
        case 7:
            /* arco seno */
            gotoxy(0,3); printf("arco seno de %.2lf: %.3lf\n", value, result);
            break;
        case 8:
            /* arco cosseno */
            gotoxy(0,3); printf("arco cosseno de %.2lf: %.3lf\n", value, result);
            break;
        case 9:
            /* arco tangente */
            gotoxy(0,3); printf("Arco tangente de %.2lf: %.3lf\n", value, result);
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
