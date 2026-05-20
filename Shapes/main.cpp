#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "Shape.h"

using namespace std;

struct Cell {
    int x;
    int y;
};

struct Result {
    int rectangleCount;
    int circleCount;
    int triangleCount;
    int noiseCount;
    double totalArea;
    double landArea;
};

// Считаем, сколько раз последовательность меняет направление роста.
// Это помогает отличать треугольник от произвольной каракули.
int countChanges(const vector<int>& a) {
    int changes = 0;
    int last = 0;

    for (size_t i = 0; i + 1 < a.size(); i++) {
        int diff = a[i + 1] - a[i];
        int now = 0;

        if (diff > 0) {
            now = 1;
        } else if (diff < 0) {
            now = -1;
        }

        if (now != 0) {
            if (last != 0 && now != last) {
                changes++;
            }
            last = now;
        }
    }

    return changes;
}

// Если пользователь не указал имя результата, создаем понятное имя автоматически:
// input1.dat  result_input1.txt.
string makeOutputFileName(const string& inputFileName) {
    size_t start = inputFileName.find_last_of("/\\");

    if (start == string::npos) {
        start = 0;
    } else {
        start++;
    }

    size_t end = inputFileName.find_last_of('.');

    if (end == string::npos || end < start) {
        end = inputFileName.size();
    }

    return "result_" + inputFileName.substr(start, end - start) + ".txt";
}

// Обрабатывает один файл 200x200. Ищет фигуры, классифицирует их
// и складывает найденные объекты в вектор указателей Shape*.
bool solveFile(const string& fileName, Result& result) {
    ifstream fin(fileName);

    if (!fin.is_open()) {
        cout << "Файл не открылся: " << fileName << endl;
        return false;
    }

    vector<string> field;
    string line;

    while (fin >> line) {
        field.push_back(line);
    }

    if (field.size() == 0) {
        cout << "Пустой файл: " << fileName << endl;
        return false;
    }

    int n = field.size();
    int m = field[0].size();

    for (int i = 0; i < n; i++) {
        if ((int)field[i].size() != m) {
            cout << "Некорректный размер строк во входном файле: " << fileName << endl;
            return false;
        }
    }

    vector<vector<int> > used(n, vector<int>(m, 0));
    vector<Shape*> shapes;

    int rectangleCount = 0;
    int circleCount = 0;
    int triangleCount = 0;
    int noiseCount = 0;

    // Проходим по всем клеткам поля. Когда встречаем еще не посещенную единицу,
    // запускаем обход связной компоненты — это одна нарисованная область.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != '1' || used[i][j]) {
                continue;
            }

            vector<Cell> q;
            vector<Cell> points;
            q.push_back({i, j});
            used[i][j] = 1;

            // Обычный BFS по четырем соседям. вверх, вниз, влево, вправо.
            size_t head = 0;

            while (head < q.size()) {
                Cell cur = q[head];
                head++;
                points.push_back(cur);

                int dx[4] = {1, -1, 0, 0};
                int dy[4] = {0, 0, 1, -1};

                for (int k = 0; k < 4; k++) {
                    int ni = cur.x + dx[k];
                    int nj = cur.y + dy[k];

                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        if (field[ni][nj] == '1' && !used[ni][nj]) {
                            used[ni][nj] = 1;
                            q.push_back({ni, nj});
                        }
                    }
                }
            }

            int pixels = points.size();

            // По условию короткие черточки и точки в расчет не принимаются.
            if (pixels < 15) {
                continue;
            }

            // Bounding box нужен для грубой оценки формы
            // ширины, высоты и степени заполненности прямоугольной рамки.
            int minX = points[0].x;
            int maxX = points[0].x;
            int minY = points[0].y;
            int maxY = points[0].y;

            for (size_t k = 0; k < points.size(); k++) {
                if (points[k].x < minX) {
                    minX = points[k].x;
                }
                if (points[k].x > maxX) {
                    maxX = points[k].x;
                }
                if (points[k].y < minY) {
                    minY = points[k].y;
                }
                if (points[k].y > maxY) {
                    maxY = points[k].y;
                }
            }

            int h = maxX - minX + 1;
            int w = maxY - minY + 1;
            double fill = (double)pixels / (h * w);

            // Почти полностью заполненный bounding box считаем прямоугольником.
            if (fill > 0.95) {
                rectangleCount++;
                shapes.push_back(new Rectangle(w, h));
                continue;
            }

            // У круга ширина и высота почти равны, а заполненность близка к pi/4.
            if (abs(h - w) <= 2 && fill >= 0.62 && fill <= 0.8) {
                circleCount++;
                shapes.push_back(new Circle((double)(h < w ? h : w) / 2.0));
                continue;
            }

            // Для треугольников смотрим, как меняется ширина по строкам
            // и высота по столбцам. У нормального треугольника эти изменения
            // более упорядоченные, чем у произвольной каракули.
            vector<int> rowWidth(h, 0);
            vector<int> colHeight(w, 0);
            vector<int> left(h, m);
            vector<int> right(h, -1);
            vector<int> top(w, n);
            vector<int> bottom(w, -1);

            for (size_t k = 0; k < points.size(); k++) {
                int row = points[k].x - minX;
                int col = points[k].y - minY;

                if (points[k].y < left[row]) {
                    left[row] = points[k].y;
                }
                if (points[k].y > right[row]) {
                    right[row] = points[k].y;
                }
                if (points[k].x < top[col]) {
                    top[col] = points[k].x;
                }
                if (points[k].x > bottom[col]) {
                    bottom[col] = points[k].x;
                }
            }

            for (int x = 0; x < h; x++) {
                if (right[x] != -1) {
                    rowWidth[x] = right[x] - left[x] + 1;
                }
            }

            for (int y = 0; y < w; y++) {
                if (bottom[y] != -1) {
                    colHeight[y] = bottom[y] - top[y] + 1;
                }
            }

            int rowChanges = countChanges(rowWidth);
            int colChanges = countChanges(colHeight);
            int maxChanges = rowChanges > colChanges ? rowChanges : colChanges;

            double aspect = (double)(h > w ? h : w) / (h < w ? h : w);
            bool isTriangle = false;

            if (pixels >= 30 && fill >= 0.18 && aspect < 7.0) {
                isTriangle = true;
            } else if (pixels >= 17 && fill >= 0.18 && aspect < 7.0 && (h < w ? h : w) >= 3 && maxChanges <= 3) {
                isTriangle = true;
            }

            if (isTriangle) {
                triangleCount++;
                shapes.push_back(new Triangle(w, h, true));
            } else {
                noiseCount++;
            }
        }
    }

    double totalArea = 0;

    // Здесь используется полиморфизм. в одном векторе лежат разные фигуры,
    // но у каждой через Shape* вызывается ее собственная формула calc_area().
    for (size_t i = 0; i < shapes.size(); i++) {
        totalArea += shapes[i]->calc_area();
    }

    // Площадь участка считается отдельно по координатам многоугольника из файла.
    Polygon land("granitsy-uchastka2.txt");
    double landArea = land.calc_area();

    if (landArea > 0) {
        result.landArea = landArea;
    }

    for (size_t i = 0; i < shapes.size(); i++) {
        delete shapes[i];
    }

    result.rectangleCount = rectangleCount;
    result.circleCount = circleCount;
    result.triangleCount = triangleCount;
    result.noiseCount = noiseCount;
    result.totalArea = totalArea;

    return true;
}

// Записываем результат в файл, чтобы после запуска сразу появились готовые отчеты.
bool writeResult(const string& outputFileName, const Result& result) {
    ofstream fout(outputFileName.c_str());

    if (!fout.is_open()) {
        cout << "Выходной файл не открылся: " << outputFileName << endl;
        return false;
    }

    fout.setf(ios::fixed);
    fout.precision(2);
    fout << "Rectangle = " << result.rectangleCount << endl;
    fout << "Circle = " << result.circleCount << endl;
    fout << "Triangle = " << result.triangleCount << endl;
    fout << "Noise = " << result.noiseCount << endl;
    fout << "Total area = " << result.totalArea << endl;

    if (result.landArea > 0) {
        fout << "Land area = " << result.landArea << endl;
    }

    return true;
}

// Полный цикл для одного входа - распознать фигуры и сохранить результат.
bool runOneFile(const string& inputFileName, const string& outputFileName) {
    Result result = {0, 0, 0, 0, 0, 0};

    if (!solveFile(inputFileName, result)) {
        return false;
    }

    if (!writeResult(outputFileName, result)) {
        return false;
    }

    cout << inputFileName << " -> " << outputFileName << endl;
    return true;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // Если файл передан аргументом, обрабатываем только его.
    // Если имя результата не передано, программа создаст его сама.
    if (argc >= 2) {
        string inputFileName = argv[1];
        string outputFileName;

        if (argc >= 3) {
            outputFileName = argv[2];
        } else {
            outputFileName = makeOutputFileName(inputFileName);
        }

        return runOneFile(inputFileName, outputFileName) ? 0 : 1;
    }

    // Без аргументов автоматически прогоняем все демо-файлы из проекта.
    vector<string> inputFiles;
    inputFiles.push_back("ГенераторФигур/Demo-task/input1.dat");
    inputFiles.push_back("ГенераторФигур/Demo-task/input2.dat");
    inputFiles.push_back("ГенераторФигур/Demo-task/input3.dat");

    bool ok = true;

    for (size_t i = 0; i < inputFiles.size(); i++) {
        string outputFileName = makeOutputFileName(inputFiles[i]);

        if (!runOneFile(inputFiles[i], outputFileName)) {
            ok = false;
        }
    }

    return ok ? 0 : 1;
}
