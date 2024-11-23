#include <iostream>
#include <cmath>
#include <ctime>   
using namespace std;
int SIZE = 5;

double f(double x)
{
    return log(x)/x;
}
double Left_Rect(double a, double b){  //вычисление интегралла методом левых прямоугольников
    int n = 10000;
    double length = (b - a) / n; //длина прямоугольника
    double sum = 0.0;
    for(int i = 0; i <= n-1; i++){
        sum+=length*f(a+i*length);
    }
    return sum;
}


double monteCarloMethod(double xMin, double xMax, double yMin, double yMax, int N, int& inBox)
{
    inBox = 0;
    for (int i = 0; i < N; i++)
    {
        double rnd1 = (double)rand() / (double)RAND_MAX; //генереруем случайное число в диапазоне от 0.0 до 1.0
        double rnd2 = (double)rand() / (double)RAND_MAX;

        double xCoord = xMin + rnd1 * (xMax - xMin); //случайные значение для х
        double yCoord = yMin + rnd2 * (yMax - yMin); //случайные значение для y

        if (yCoord <= f(xCoord)) //проверяем, попала ли точка под график
            inBox++; //Увеличиваем счётчик, если точка попала под график 
    }

    double density = (double)inBox / N; //плотность точек 
    return (xMax - xMin) * (yMax - yMin) * density; //возращаем посчитанный интегралл
}



int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int N[SIZE] = { 100, 500, 1000, 3000, 10000 }; //количество случайных точек
    double error[SIZE];
    double integralValue[SIZE];
    int pointsInBox[SIZE];
    double xMin, xMax, yMin = 0, yMax;
    int inBox = 0;
    wcout << L"\tВычисление значения интеграла методом Монте-Карло" << endl << endl;;
    wcout << L"Введите значение левой границы интегрирования: " << endl;;
    cin >> xMin;
    wcout << L"Введите значение правой границы интегрирования: " << endl;;
    cin >> xMax;
    wcout << L"Введите высоту прямоугольника, в пределах которого будут генерироваться точки: " << endl;;
    cin >> yMax;

    for (int i = 0; i < SIZE; i++)
    {
        int n = N[i];
        integralValue[i] = monteCarloMethod(xMin, xMax, yMin, yMax, n, inBox);
        error[i] = fabs(integralValue[i] - Left_Rect(xMin,xMax)) / Left_Rect(xMin,xMax);
        pointsInBox[i] = inBox;
    }

    cout << endl;

    for (int i = 0; i < SIZE; i++)
    {
        wcout << i + 1 << L") Число сгенерированных точек: " << N[i] << endl;
        wcout << L"Значение интеграла: " << integralValue[i] << endl;
        wcout << L"Величина абсолютной ошибки: " << error[i] << endl;
        wcout << L"Число точек, попавших под график функции: " << pointsInBox[i] << endl;
    }

    return 0;
}