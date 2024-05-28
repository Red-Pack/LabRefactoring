#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция для ввода координат точек
vector<pair<float, float>> inputPoints(int numPoints) {
    vector<pair<float, float>> points(numPoints);
    for (int i = 0; i < numPoints - 1; i++) {
        cout << "Введите координаты " << i + 1 << "-ой точки множества (через пробел): ";
        cin >> points[i].first >> points[i].second;
    }
    cout << "Введите координаты точки, которая не входит в множество (через пробел): ";
    cin >> points[numPoints - 1].first >> points[numPoints - 1].second;
    return points;
}

// Функция для вычисления коэффициента наклона и длины отрезка
void calculateSegment(float x1, float y1, float x2, float y2, float& slope, float& length) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    slope = dx / dy;
    length = sqrt(dx * dx + dy * dy);
}

// Основная логика для подсчета троек точек, образующих параллелограмм
int countParallelograms(const vector<pair<float, float>>& points) {
    const int numPoints = points.size();
    int parallelogramCount = 0;

    for (int i = 0; i < numPoints - 3; i++) {
        for (int j = i + 1; j < numPoints - 2; j++) {
            float slope1, length1, slope4, length4;
            calculateSegment(points[i].first, points[i].second, points[j].first, points[j].second, slope1, length1);
            calculateSegment(points[i].first, points[i].second, points[numPoints - 1].first, points[numPoints - 1].second, slope4, length4);

            for (int p = j + 1; p < numPoints - 1; p++) {
                float slope2, length2, slope3, length3;
                calculateSegment(points[p].first, points[p].second, points[numPoints - 1].first, points[numPoints - 1].second, slope2, length2);
                calculateSegment(points[j].first, points[j].second, points[p].first, points[p].second, slope3, length3);

                if (((length1 == length2) && (slope1 == slope2)) || ((length3 == length4) && (slope3 == slope4))) {
                    parallelogramCount++;
                }
            }
        }
    }

    return parallelogramCount;
}

int main() {
    setlocale(LC_ALL, "");

    cout << "Введите количество точек в множестве: ";
    int pointCount;
    cin >> pointCount;

    const int totalPoints = pointCount + 1;  // +1 для точки, которая не входит в множество
    vector<pair<float, float>> points = inputPoints(totalPoints);

    int result = countParallelograms(points);

    cout << "Кол-во различных троек точек, образующих параллелограмм: " << result << endl;

    system("pause");
    return 0;
}