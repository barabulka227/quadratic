#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 1e-6;
int roots = 0;


// возвращает абсолютное значение числа double
double absolute(double a) {
    if(a < 0){
        return -a;
    }
    return a;
}

// проверка близости к нулю
int is_zero(double x) {
    return absolute(x) < EPSILON;
}

//ВВОД ДАННЫХ
int input(double* a, double* b, double* c) {

    printf("Это программа для решения квадратных уравнений вида ax^2+bx+c=0.\n");
    printf("Введите коэффициенты квадратного уравнения (a b c):\n");

    int cnt = scanf("%lf%lf%lf", a, b, c);

    // проверка на то что ввели 3 числа
    assert(cnt == 3);

    return 0;
}

//Решение линейного уравнения
int linear(double b, double c, double* x) {

    printf("Вы ввели линейное уравнение.\n");

    if (is_zero(b) && is_zero(c)) {
        roots = -1; // бесконечно много решений
    } else if (is_zero(b) && !is_zero(c)) {
        roots = 0; // нет решений
    } else {
        roots = 1;
        *x = -c / b;
    }

    return 0;
}

//Решение квадратного уравнения
int processing(double a, double b, double c,
               double* x1_r, double* x2_r, double* x_c) {


    if (is_zero(a)) {
        linear(b, c, x1_r);
        return 0;
    }

    double D = b*b - 4*a*c;

    if (D > EPSILON) {
        roots = 2;
        *x1_r = (-b + sqrt(D))/(2*a);
        *x2_r = (-b - sqrt(D))/(2*a);
    }
    else if (is_zero(D)) {
        roots = 1;
        *x1_r = -b / (2*a);
    }
    else {
        roots = 2;
        *x1_r = *x2_r = -b/(2*a);
        *x_c  = sqrt(-D)/(2*a);
    }

    return 0;
}

//ВЫВОД
int output(double x1_r, double x2_r, double x_c) {
    switch (roots) {
        case -1:
            printf("Бесконечно много решений.\n");
            break;

        case 0:
            printf("Нет корней.\n");
            break;

        case 1:
            printf("Единственный корень: x = %f\n", x1_r);
            break;

        case 2:
            if (is_zero(x_c)) {
                printf("Два действительных корня:\n");
                printf("x1 = %f\n", x1_r);
                printf("x2 = %f\n", x2_r);
            }
            else {
                printf("Два комплексных корня:\n");
                printf("x1 = %f + %fi\n", x1_r, x_c);
                printf("x2 = %f - %fi\n", x2_r, x_c);
            }
            break;

        default:
            printf("Ошибка: неизвестное количество корней (%d)\n", roots);
            assert(0);
    }
    return 0;
}

int main() {
    double a = 0, b = 0, c = 0;
    //коэффициенты квадратного уравнения
    double x1_real = 0, x2_real = 0, x_c = 0;
    //   x1_real и x2_real - вещественные части от двух возможных корней
    //   x_c - возможная мнимая часть у двух корней. Поскольку коэффициенты уравнения вещественные,
    //   то достаточно одной переменной в силу формулы для решения квадратного уравнения.

    input(&a, &b, &c);
    processing(a, b, c, &x1_real, &x2_real, &x_c);
    output(x1_real, x2_real, x_c);

    return 0;
}



