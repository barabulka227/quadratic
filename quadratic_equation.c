#include <TXLib.h>
#include <stdio.h>
#include <math.h>
double epsilon = 0.000001;

double absolute(double a){
    if(a < 0){
        return -a;
    }
    return a;
}

int linear(double b, double c){         //функция которая решает линейное уравнение
    printf("Вы ввели линейное уравнение \n");
        if(absolute(b) < epsilon && absolute(c) < epsilon){
            printf("x - любое \n");
        }
        else if(absolute(b) < epsilon && absolute(c) >= epsilon){
            printf("Нет решений \n");
        }
        else{
            printf("Корень уравнения x = %lf \n", -c/b);
        }
        return 0;

}

int main(){
    double a_coof = 0, b_coof = 0, c_coof = 0;
    printf("Это программа для решения квадратных уравнений. \n");
    printf("На следующей строке введите коэфициенты квадратного уравнения: \n");
    scanf("%lf%lf%lf", &a_coof, &b_coof, &c_coof);


    //условие на то что коэфициент перед x^2 равен 0
    if(absolute(a_coof) < epsilon){
        linear(b_coof, c_coof);
        return 0;
    }


    double D = b_coof*b_coof - 4*a_coof*c_coof;

    if(D >= epsilon){
        printf("У уравнения два реальных корня:\n");
        printf("x1 = %f \n", (-b_coof+sqrt(D))/(2*a_coof));
        printf("x2 = %f \n", ((-b_coof-sqrt(D))/(2*a_coof)));
    }
    else if(absolute(D) < epsilon){
        printf("У уравнения 1 корень x = %f \n", -b_coof/(2*a_coof));
    }
    else{
        double real_part = -b_coof/(2*a_coof);    //реальная часть
        double comp_part = sqrt(-D)/(2*a_coof);   //мнимая часть
        printf("У уравнения 2 комплексных корня: \n");
        printf("x1 = %f + %f*i \n", real_part, comp_part);
        printf("x2 = %f - %f*i \n", real_part, comp_part);
    }

    return 0;
}


