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

int linear(double b, double c){
    printf("�� ����� �������� ��������� \n");
        if(absolute(b) < epsilon && absolute(c) < epsilon){
            printf("x - ����� \n");
        }
        else if(absolute(b) < epsilon && absolute(c) >= epsilon){
            printf("��� ������� \n");
        }
        else{
            printf("������ ��������� x = %lf \n", -c/b);
        }
        return 0;

}

int main(){
    double a_coof = 0, b_coof = 0, c_coof = 0;
    printf("��� ��������� ��� ������� ���������� ���������. \n");
    printf("�� ��������� ������ ������� ����������� ����������� ���������: \n");
    scanf("%lf%lf%lf", &a_coof, &b_coof, &c_coof);


    if(absolute(a_coof) < epsilon){
        linear(b_coof, c_coof);
        return 0;

    }


    double D = b_coof*b_coof - 4*a_coof*c_coof;

    if(D >= epsilon){
        printf("� ��������� ��� �������� �����:\n");
        printf("x1 = %f \n", (-b_coof+sqrt(D))/(2*a_coof));
        printf("x2 = %f \n", ((-b_coof-sqrt(D))/(2*a_coof)));
    }
    else if(absolute(D) < epsilon){
        printf("� ��������� 1 ������ x = %f \n", -b_coof/(2*a_coof));

    }
    else{
        double real_part = -b_coof/(2*a_coof);    //�������� �����
        double comp_part = sqrt(-D)/(2*a_coof);   //������ �����
        printf("� ��������� 2 ����������� �����: \n");
        printf("x1 = %f + %f*i \n", real_part, comp_part);
        printf("x2 = %f - %f*i \n", real_part, comp_part);
    }

    return 0;
}
