#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>

double StrToDouble(std::string s) {
    std::regex r("[+-]?\\d+");
    std::smatch m;
    auto pos = s.cbegin();

    double d;
    std::regex_search(pos, s.cend(), m, r);
    d = std::stoi(m.str());
    pos = m.suffix().first;

    std::regex_search(pos, s.cend(), m, r);
    d += double(std::stoi(m.str())) / pow(10, m.str().size());
    pos = m.suffix().first;

    std::regex_search(pos, s.cend(), m, r);
    if (!m.str().empty()) {
        d *= double(pow(10, std::stoi(m.str())));
    }


    return d;
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    std::ifstream file("regex.txt");
    if (!file) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> integers;
    std::vector<double> realNumbers;
    std::vector<std::string> strings;

    std::regex stringPattern("\"(.*?)\"");
    std::regex realNumberPattern("[-+]?[0-9]+\\.[0-9]+([eE][-+]?[0-9]+)?");
    std::regex integerPattern("[-+]?[0-9]+");
    while (std::getline(file, line)) {
        std::cout << line << '\n';

        std::smatch m;
        auto pos = line.cbegin();
        auto end = line.cend();
        for (; std::regex_search(pos, end, m, stringPattern); pos = m.suffix().first) {
            strings.push_back(m.str(1));
        }
        line = std::regex_replace(line, stringPattern, "");

        pos = line.cbegin();
        end = line.cend();
        for (; std::regex_search(pos, end, m, realNumberPattern); pos = m.suffix().first) {
            double d = StrToDouble(m.str());
            realNumbers.push_back(d);
        }
        line = std::regex_replace(line, realNumberPattern, "");

        pos = line.cbegin();
        end = line.cend();
        for (; std::regex_search(pos, end, m, integerPattern); pos = m.suffix().first) {
            integers.push_back(std::stoi(m.str()));
        }
    }

    // Вычисляем суммы
    int sumIntegers = 0;
    for (int num : integers) {
        sumIntegers += num;
    }

    double sumRealNumbers = 0.0;
    for (double num : realNumbers) {
        sumRealNumbers += num;
    }

    // Выводим результаты
    std::cout << "Сумма целых чисел: " << sumIntegers << std::endl;
    std::cout << "Сумма действительных чисел: " << std::fixed << sumRealNumbers << std::endl;
    std::cout << "Строки: " << std::endl;
    for (const std::string& str : strings) {
        std::cout << str << std::endl;
    }

    return 0;
}