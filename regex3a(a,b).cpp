#include <iostream>
#include <regex>

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    std::regex original("^(.+\\s+)?(весна|лето|осень|зима)(\\s+.+\\s+|\\s+)((максимальная|макс\\.)|средняя темература)(\\s+.+\\s+|\\s+)(\\d+)(\\s+.+)?$");


    std::regex fullStr("^(.+\\s+)?(spring|summer|autumn|winter)(\\s+.+\\s+|\\s+)((maximal|max\\.)|average temperature)(\\s+.+\\s+|\\s+)(\\d+)(\\s+.+)?$");  //a)
    
    std::regex subStr("(.+\\s+)?(spring|summer|autumn|winter)(\\s+.+\\s+|\\s+)((maximal|max\\.)|average temperature)(\\s+.+\\s+|\\s+)(\\d+)(\\s+.+)?");     //b)

    std::string data;
    //std::getline(std::cin, data);
    data = "flijjfse spring jflkaj ibeeeilbf selib average temperature fjlka;je ioini ae;oa flkndklasdmca;j 25  fljijslekfn";
    std::cout << data << "\n\n";

    if (std::regex_match(data.cbegin(), data.cend(), subStr)) {
        std::cout << "match: YES\n\n";
    }
    else {
        std::cout << "match: NO\n\n";
    }

    std::smatch m;
    if (std::regex_search(data.cbegin(), data.cend(), m, subStr)) {
        std::cout << "search: YES\n";
        std::cout << "substr: " << m.str();
    }
    else {
        std::cout << "search: NO\n";
    }

    return 0;
}