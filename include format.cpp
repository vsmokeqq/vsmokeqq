#include <iostream>
#include <format>

int main() {
    setlocale(LC_ALL, "RUSSIAN");

    //1. :.количество_знаков.
    double sum{ 100.2567 };
    std::cout << "1)" << std::format("sum = {:.5}", sum) << std::endl;

    //2. {}: "{} + {} = {}".
    int a{ 10 };
    int b{ 7 };
    std::cout << "2)" << std::format("{} + {} = {}", a, b, a + b) << std::endl;

    //3. символьное заполнение.
    int c{ 2 };
    int d{ 5 };
    int e{ -8 };
    std::cout << "3)" << std::format("c = {:07}", c) << std::endl;
    std::cout << "3)" << std::format("d = {:7}", d) << std::endl;
    std::cout << "3)" << std::format("e = {:07}", e) << std::endl;

    //4. Переопределение порядка аргументов
    int f{ 10 }; //0:
    int g{ 20 }; //1:
    int h{ 30 }; //2:
    std::cout << "4)" << std::format("{2:} {1:} {0:}", f, g, h) << std::endl;    // 30 20 10

    //5. Выравнивание

    std::cout << "5)" << std::format("{:>7}|{:>7}|{:>7}|{:>7}|\n", 1, -.2, 3, 4);
    std::cout << "5)" << std::format("{:<7}|{:<7}|{:7}|{:<7}|\n", 1, -.2, "3", 4);
    std::cout << "5)" << std::format("{:^7}|{:^7}|{:^7}|{:^7}|\n", 1, -.2, 3, 4);

    return 0;
}