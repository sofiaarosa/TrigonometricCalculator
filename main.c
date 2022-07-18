#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include "conio_functions.h" /*substitution of conio.c*/
#include <stdlib.h>
#include <locale.h>

#define downArrow 80
#define upArrow 72
#define esc 27
#define enter 13
#define f1 59

#define screenColumns 90
#define horizontalCenter 45
#define screenRows 40
#define verticalCenter 20

//function headers 
int startMenu();
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
int exitProgram = 0;

int main() {
	system("mode con:cols=90 lines=20");
	SetConsoleTitle("Calculadora Trigonometrica");
	setlocale(LC_CTYPE, "Portuguese"); 
	cursor(0);
    
	int out = 0, action = 0;
    double value, result;

	do{
	    while(action != 1){
	        action = startMenu();
    	    if(action == 2) infoSystem();
    	    else if(action == 3) return 0;
        }
	    
		value = 0; result = 0;
		operation = mainMenu();
		if(exitProgram > 0) break;
	    measure = measureMenu();
	    if(exitProgram > 0) break;
		value = getValue();
	
	    printCalculus(value, calculate(value));
	    getch();
	    
		out = reprocessing();
        if(exitProgram > 0) break;	
	}while(out != 2 && exitProgram == 0); 

    return 0;
}

void printHeader(){
	textbackground(15);
	textcolor(0);
	
    system("cls");
    int i;
    for(i=0;i<screenColumns;i++){
	    gotoxy(i,1);
    	textbackground(14);printf(" ");
    }
    
    gotoxy(horizontalCenter - 13,1); printf("CALCULADORA TRIGONOMÉTRICA");
    textbackground(15);
}

int startMenu(){
    printHeader();

	gotoxy(3,3); printf("Opções do programa: ");
    gotoxy(3,5); printf("Iniciar calculadora");
    gotoxy(3,6); printf("Info do sistema");
    gotoxy(3,7); printf("Sair");

    return menuSelection(5,7);
}

int infoSystem(){
    printHeader();
    gotoxy(3, 3);
    printf("Trabalho 1 de algoritmos - 2022");
    gotoxy(3,4); printf("Alunos desenvolvedores: ");
    gotoxy(3, 5); printf("221025588 - Sofia Azevedo Rosa");
    gotoxy(3, 6); printf("221026321 - Vinicius Casimiro da Silveira");
    gotoxy(10,10); printf("Pressione qualquer tecla para prosseguir.");
    getch();
}

int mainMenu() {
    printHeader();

	gotoxy(3,3); printf("Selecione a operação a ser realizada: ");
    gotoxy(3,5); printf("Seno");
    gotoxy(3,6); printf("Cosseno");
    gotoxy(3,7); printf("Tangente");
    gotoxy(3,8); printf("Cossecante");
    gotoxy(3,9); printf("Secante");
    gotoxy(3,10); printf("Cotangente");
    gotoxy(3,11); printf("Arcoseno");
    gotoxy(3,12); printf("Arcocosseno");
    gotoxy(3,13); printf("Arcotangente");

    return menuSelection(5,13);
}

int measureMenu(){
    printHeader();

	gotoxy(3,3);
	if(operation<7) printf("Ângulo de entrada medido em: ");
	else printf("Resultado em: ");
	
    gotoxy(3,5);printf("Radianos");
    gotoxy(3,6);printf("Graus");

    return menuSelection(5,6);
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
            	break;
           	case esc:
           	    exitProgram = 1;
           	    gotoxy(0, 15);
           	    return;
       	        
		}
        gotoxy(0,aux); printf(" >");
    }
    
    return choice;
}

double convertMeasure(int direction, double angle){
	//float M_PI = 3.141596;
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
    double rawValue = value;


    if(measure != 1) {
		if(operation < 7)
			value = convertMeasure(0, value);
			
		else 
			result = convertMeasure(0,result);
	}
	
    
    gotoxy(0,3); 
    switch (operation) {
        case 1:
            /* seno */
            printf("Seno de %.2lf: %.3lf\n", value, result);
            break;
        case 2:
            /* cosseno */
            printf("Cosseno de %.2lf: %.3lf\n", value, result);
            break;
        case 3:
            /* tangente */            
            if(cos(rawValue) > pow(10, -25) && cos(rawValue) < pow(10, 25)){
                printf("Tangente de %.2lf não existe.\n", value);
            }
            else printf("Tangente de %.2lf: %.3lf\n", value, result);
            break;
        case 4:
            /* cossecante */
            if(sin(rawValue) == 0){
                printf("Cossecante de %.2lf não existe.\n", value);
            }
            else printf("Cossecante de %.2lf: %.3lf\n", value, result);
            break;
        case 5:
            /* secante */
            if(cos(rawValue) > pow(10, -25) && cos(rawValue) < pow(10, 25)){
                printf("Secante de %.2lf não existe.\n", value);
            }
            else printf("Secante de %.2lf: %.3lf\n", value, result);
            break;
        case 6:
            /* cotangente */
            if(sin(rawValue) == 0){
                printf("Cotangente de %.2lf não existe.\n", value);
            }
            else printf("Cotangente de %.2lf: %.3lf\n", value, result);
            break;
        case 7:
            /* arco seno */
            printf("arco seno de %.2lf: %.3lf\n", value, result);
            break;
        case 8:
            /* arco cosseno */
            printf("arco cosseno de %.2lf: %.3lf\n", value, result);
            break;
        case 9:
            /* arco tangente */
            printf("Arco tangente de %.2lf: %.3lf\n", value, result);
            break;
    }
    
    gotoxy(10,5); printf("Pressione qualquer tecla para prosseguir.");
}

int reprocessing(){
	printHeader();
	gotoxy(3,3);printf("Deseja calcular novamente?");
	gotoxy(3,5);printf("Sim");
    gotoxy(3,6);printf("Não");
    
    return menuSelection(5,6);
}
