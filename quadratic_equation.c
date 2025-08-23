#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 1e-6;
int roots = 0;

//                 ПРОТОТИПЫ
double absolute(double a);
int is_zero(double x);
int linear(double b, double c, double* x);
int processing(double a, double b, double c,
               double* x1_r, double* x2_r, double* x_c);
int output(double x1_r, double x2_r, double x_c);
int input(double* a, double* b, double* c);
void run_tests();


//                 MAIN
int main() {
    printf("Выберите режим:\n1 - Запуск юнит-тестов\n2 - Решение уравнения вручную\n");
    int mode = 0;
    scanf("%d", &mode);

    if (mode == 1) {
        run_tests();
    }
    else if (mode == 2) {
        double a=0, b=0, c=0, x1=0, x2=0, xc=0;
        input(&a, &b, &c);
        processing(a, b, c, &x1, &x2, &xc);
        output(x1, x2, xc);
    }
    else {
        printf("Ошибка: учитесь читать.\n");
        return 0;
    }

    return 0;
}

//                       ФУНКЦИИ

// возвращает абсолютное значение числа double
double absolute(double a) {
    return (a < 0) ? -a : a;
}

// проверка близости к нулю
int is_zero(double x) {
    return absolute(x) < EPSILON;
}

// Решение линейного уравнения
int linear(double b, double c, double* x) {
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

// Решение квадратного уравнения
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
        *x_c = 0;
    }
    else if (is_zero(D)) {
        roots = 1;
        *x1_r = -b / (2*a);
        *x2_r = *x1_r;
        *x_c = 0;
    }
    else {
        roots = 2;
        *x1_r = *x2_r = -b/(2*a);
        *x_c  = sqrt(-D)/(2*a);
    }
    return 0;
}

// Вывод решения
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

// Ввод коэффициентов
int input(double* a, double* b, double* c) {
    printf("Введите коэффициенты квадратного уравнения (a b c):\n");
    int cnt = scanf("%lf %lf %lf", a, b, c);
    assert(cnt == 3);
    return 0;
}


//                             ЮНИТ-ТЕСТЫ 
void run_tests() {
    double x1, x2, xc;

    // Квадратное уравнение с двумя корнями
    processing(1, -3, 2, &x1, &x2, &xc);
    if(roots == 2 && is_zero(x1-2) && is_zero(x2-1)){
        printf("TEST 1: OK \n");
    }
    else{
        printf("TEST 1: FAILED. processing(1, -3, 2, &x1, &x2, &xc) \
        has roots == 2 && x1 == 2 && x2 == 1 \n");
    }

    // Квадратное уравнение
    processing(1, 2, 1, &x1, &x2, &xc);
    if (roots == 1 && is_zero(x1+1)){
        printf("TEST 2: OK \n");
    }
    else{
        printf("TEST 2: FAILED.  processing(1, 2, 1, &x1, &x2, &xc) has roots == 1 && x1 == -1 \n");
    };

    // Уравнение с двумя комплексными корнями
    processing(1, 0, 1, &x1, &x2, &xc);
    if(roots == 2 && is_zero(x1-0) && is_zero(x2-0) && is_zero(xc-1)){
        printf("TEST 3: OK \n");
    }
    else{
        printf("TEST 3: FAILED. processing(1, 0, 1, &x1, &x2, &xc) \
        has roots x1 = i, x2 = -i \n");
    };

    // Линейное
    processing(0, 2, -4, &x1, &x2, &xc);
    if(roots == 1 && is_zero(x1-2)){
        printf("TEST 4: OK \n");
    }
    else{
        printf("TEST 4: FAILED. processing(0, 2, -4, &x1, &x2, &xc) has roots == 1 && x1 == 2 \n");
    };

    // Линейное без корней
    processing(0, 0, 5, &x1, &x2, &xc);
    if(roots == 0){
        printf("TEST 5: OK \n");
    }
    else{
        printf("TEST 5: FAILED. processing(0, 0, 5, &x1, &x2, &xc) has no roots \n");
    }


    //линейное с inf sol
    processing(0, 0, 0, &x1, &x2, &xc);
    if(roots == -1){
        printf("TEST 6: OK \n");
    }
    else{
        printf("TEST 6: FAILED. processing(0, 0, 0, &x1, &x2, &xc) has roots == INF \n");
    }


    //Квадратное с одним корнем
    processing(1, -8, 16, &x1, &x2, &xc);
    if(roots == 1 && is_zero(x1 - 4)){
        printf("TEST 7: OK \n");
    }
    else{
        printf("TEST 7: FAILED. processing(1, -8, 16, &x1, &x2, &xc) has roots == 1 && x1 == 4 \n");
    }

    //Такое же уравнение домноженное на -1
    processing(-1, 8, -16, &x1, &x2, &xc);
    if(roots == 1 && is_zero(x1 - 4)){
        printf("TEST 8: OK \n");
    }
    else{
        printf("TEST 8: FAILED. processing(-1, 8, -16, &x1, &x2, &xc) has roots == 1 && x1 == 4 \n");
    }


 }

