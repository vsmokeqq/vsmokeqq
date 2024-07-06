#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>

class film {
public:
	char filmName[16] = "               ";
	int year = 0;
	int duration = 0;
	char type[6] = "     ";
	int studioCode = 0;
	char actor[21] = "                    ";
	char studio[16] = "               ";
	
	film() = default;

	film(const film& other) : year(other.year), duration(other.duration), studioCode(other.studioCode) {
		int i;
		for (i = 0; other.filmName[i] != '\0'; i++) {
			filmName[i] = other.filmName[i];
		}
		filmName[i] = other.filmName[i];

		for (i = 0; other.actor[i] != '\0'; i++) {
			actor[i] = other.actor[i];
		}
		actor[i] = other.actor[i];

		for (i = 0; other.studio[i] != '\0'; i++) {
			studio[i] = other.studio[i];
		}
		studio[i] = other.studio[i];

		for (i = 0; other.type[i] != '\0'; i++) {
			type[i] = other.type[i];
		}
		type[i] = other.type[i];
	}
	 
	film operator = (const film& other) {
		year = other.year;
		duration = other.duration;
		studioCode = other.studioCode;

		int i;
		for (i = 0; other.filmName[i] != '\0'; i++) {
			filmName[i] = other.filmName[i];
		}
		filmName[i] = other.filmName[i];

		for (i = 0; other.actor[i] != '\0'; i++) {
			actor[i] = other.actor[i];
		}
		actor[i] = other.actor[i];

		for (i = 0; other.studio[i] != '\0'; i++) {
			studio[i] = other.studio[i];
		}
		studio[i] = other.studio[i];

		for (i = 0; other.type[i] != '\0'; i++) {
			type[i] = other.type[i];
		}
		type[i] = other.type[i];

		return *this;
	}



	bool operator > (film const& st) const {
		if (studioCode > st.studioCode) return true;
		else if (studioCode == st.studioCode) {
			if (std::string(filmName) > std::string(st.filmName)) return true;
			else if (std::string(filmName) == std::string(st.filmName)) {
				if (year > st.year) return true;
				else if (year == st.year) {
					if (duration > st.duration) return true;
					else if (duration == st.duration) {
						if (std::string(type) > std::string(st.type)) return true;
						else if (std::string(type) == std::string(st.type)) {
							if (std::string(actor) > std::string(st.actor)) return true;
							else if (std::string(actor) == std::string(st.actor)) {
								if (std::string(studio) > std::string(st.studio)) return true;
								else return false;
							}
							else return false;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}

	bool operator == (film const& st) {
		return year == st.year && std::string(filmName) == std::string(st.filmName) && duration == st.duration && std::string(type) == std::string(st.type) && studioCode == st.studioCode && std::string(actor) == std::string(st.actor) && std::string(studio) == std::string(st.studio);
	}

	bool operator <= (film const& st) {
		return !(*this > st);
	}

	bool operator != (film const& st) {
		return !(*this == st);
	}

	bool operator < (film const& st) {
		return !(*this > st) && (*this != st);
	}

	bool operator >= (film const& st) {
		return (*this > st) || (*this == st);
	}

	friend std::ifstream& operator >> (std::ifstream& file, film& st) {
		file.read((char*)&st, sizeof(st));

		return file;
	}

	friend std::ofstream& operator << (std::ofstream& file, film const& st) {
		file.write((char*)&st, sizeof(st));
		return file;
	}

};

template <typename T>
size_t file_Size(T& fin) {
	std::streamoff pos = fin.tellg();  //return current position in file
	fin.seekg(0, std::ios_base::end); //делает текущим конец файла
	size_t n2 = fin.tellg();
	fin.seekg(0);
	size_t n1 = fin.tellg();

	return n2 - n1;
}

void TXTtoBIN(const std::string& txtFilename, const std::string& binFilename) {
	std::ifstream fin(txtFilename);
	std::ofstream fout(binFilename, std::ios::binary | std::ios::out);

	if (fin.is_open() && fout.is_open()) {
		std::string buffer;
		while (std::getline(fin, buffer)) {
			film a;
			std::istringstream sin(buffer);
			std::vector <std::string> data;
			std::string d;
			while (std::getline(sin, d, '\t')) {
				data.push_back(d);
			}

			if (data.size() == 2) {
				a.studioCode = std::stoi(data[0]);
				for (int i = 0; i < data[1].size(); i++) {
					a.studio[i] = data[1][i];
				}
				a.studio[10] = '\0';
			}
			else {
				for (int i = 0; i < data[0].size(); i++) {
					a.filmName[i] = data[0][i];
				}
				a.year = std::stoi(data[1]);
				a.duration = std::stoi(data[2]);
				for (int i = 0; i < data[3].size(); i++) {
					a.type[i] = data[3][i];
				}
				a.studioCode = std::stoi(data[4]);

				for (int i = 0; i < data[5].size(); i++) {
					a.actor[i] = data[5][i];
				}
			}

			fout << a;
		}
		fin.close();
		fout.close();
	}
	else if (!fin.is_open()) {
		std::cerr << "Error4573: не удалось открыть файл " << txtFilename << '\n';
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл " << binFilename << '\n';
	}

}


void BINtoTXT(const std::string& binFilename, const std::string& txtFilename) {
	std::ifstream fin(binFilename, std::ios::binary | std::ios::in);
	std::ofstream fout(txtFilename);

	if (fin.is_open() && fout.is_open()) {
		size_t n = file_Size(fin) / sizeof(film);
		for (size_t i = 0; i < n; i++) {
			film a;
			fin >> a;
			if (std::string(a.filmName) != "               ") {
				fout << a.filmName << '\t';
			}
			if (a.year) {
				fout << a.year << '\t';
			}
			if (a.duration) {
				fout << a.duration << '\t';
			}
			if (std::string(a.type) != "     ") {
				fout << a.type << '\t';
			}
			if (a.studioCode) {
				fout << a.studioCode << '\t';
			}
			if (std::string(a.actor) != "                    ") {
				fout << a.actor << '\t';
			}
			if (std::string(a.studio) != "               ")
				fout << a.studio;
			fout << '\n';
		}
		fin.close();
		fout.close();
	}
	else if (!fin.is_open()) {
		std::cerr << "Error4573: не удалось открыть файл " << binFilename << '\n';
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл " << txtFilename << '\n';
	}

}


void CreateNewSortedFile() {
	//Сортировка товаров через оперативную память
	std::fstream fin("film.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	size_t filmSize = file_Size(fin) / sizeof(film);
	std::vector <film> films(filmSize);
	if (fin.is_open()) {
		for (size_t i = 0; i < filmSize; i++) {
			fin.read((char*)&films[i], sizeof(films[0]));
		}
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл film.bin" << '\n';
		return;
	}

	for (int i = 0; i < filmSize; i++) {
		for (int j = i + 1; j < filmSize; j++) {
			if (films[i] > films[j]) {
				std::swap(films[i], films[j]);
			}
		}
	}

	fin.close();
	fin.open("studio.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);

	size_t studioSize = file_Size(fin) / sizeof(film);
	for (size_t i = 0; i < studioSize; i++) {
		for (size_t j = i + 1; j < studioSize; j++) {
			film s1, s2;
			fin.seekg(i * sizeof(s1));
			fin.read((char*)&s1, sizeof(s1));
			fin.seekg(j * sizeof(s2));
			fin.read((char*)&s2, sizeof(s2));

			if (s1 > s2) {
				fin.seekg(i * sizeof(s1));
				fin.write((char*)&s2, sizeof(s1));

				fin.seekg(j * sizeof(s2));
				fin.write((char*)&s1, sizeof(s1));
			}
		}
	}

	std::ofstream fout("M1.bin");
	size_t i = 0;
	size_t j = 0;
	while (i < studioSize || j < filmSize) {
		film a;
		fin.seekg(i * sizeof(a));
		fin.read((char*)&a, sizeof(a));

		while ((j == filmSize && i < studioSize) || (i < studioSize && a.studioCode < films[j].studioCode)) {
			i++;
			fin.seekg(i * sizeof(a));
			fin.read((char*)&a, sizeof(a));
		}

		while ((i == studioSize && j < filmSize) || (j < filmSize && films[j].studioCode < a.studioCode)) j++;

		if (j < filmSize && a.studioCode == films[j].studioCode) {
			for (int k = 0; k < 15; k++) {
				films[j].studio[k] = a.studio[k];
			}
			fout << films[j];

			j++;
		}

	}

	fout.close();
	fin.close();
}

void deleteSpaces(char* c, int size) {
	int j = size - 1;
	while (c[j] == ' ' || c[j] == '\0') {
		c[j] = '\0';
		j--;
	}
}

void solution() {
	std::fstream m("M1.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	std::vector <film> films(file_Size(m) / sizeof(film));

	for (int i = 0; i < films.size(); i++) {
		m.read((char*)&films[i], sizeof(films[0]));

		deleteSpaces(films[i].filmName, 15);
		deleteSpaces(films[i].actor, 20);
		deleteSpaces(films[i].studio, 15);
		deleteSpaces(films[i].type, 5);
	}

	int move = -1;
CONTINUE_PROGRAMM:
	while (move != 0) {
		std::cout << "Выберите действие, указав соответствующую цифру:\n"
			<< "1. Показать все фильмы.\n"
			<< "2. Показать самый длинный фильм.\n"
			<< "3. Обновить актёра в фильме.\n"
			<< "4. Удалить записи, в которых название фильма начинается на букву \"М\".\n"
			<< "5. Поменять местами записи с минимальным и максимальным годами выпуска.\n"
			<< "6. Упорядочить по названию фильма в порядке убывания.\n"
			<< "7. Записать данные в текстовый файл.\n"
			<< "8. Записать данные в бинарный файл.\n"
			<< "0. Закрыть программу.\n\n";

//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> move;
		std::cout << '\n';
		std::ofstream fout;
		film pr;
		std::string s;
		int j = 14;

		switch (move) {
		case 0:
			goto CLOSE_PROGRAMM;
			break;

		case 1:
			for (int i = 0; i < films.size(); i++) {
				std::cout << "Фильм - " << films[i].filmName << ",\t" << "год выпуска - " << films[i].year << ",\t" << "Длительность - " << films[i].duration << ",\t" << "Актёр - " << films[i].actor << '\n';
			}
			std::cout << '\n';
			break;

		case 2:
			for (int i = 0; i < films.size(); i++) {
				if (films[i].duration > pr.duration) {
					pr = films[i];
				}
			}
			std::cout << "Самый длинный фильм - " << pr.filmName << " от фирмы \"" << pr.filmName << "\"\n";
			std::cout << "Его год выпуска, длительность и тип плёнки соответственно:\t" << pr.year << ",\t" << pr.duration << ",\t" << pr.type << "\n\n";
			break;

		case 3:
			std::cout << "Введите название фильма (до 15-ти символов): ";
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, s);
			for (int i = 0; i < s.size(); i++) {
				pr.filmName[i] = s[i];
			}
			deleteSpaces(pr.filmName, 20);


			std::cout << '\n';

			for (int i = 0; i < films.size(); i++) {
				if (std::string(films[i].filmName) == std::string(pr.filmName)) {
					pr = films[i];
					auto it = films.begin();
					std::advance(it, i);
					i--;
					films.erase(it);
				}

			}
			int n;
			std::cout << "Актёров снималось в фильме: ";
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> n;
			for (int i = 0; i < n; i++) {
				std::string name;
				std::cout << "Введите имя актёра: ";
//				std::cin.clear();
//				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, name);

				for (int j = 0; j < 20; j++) {
					if (j < name.size()) {
						pr.actor[j] = name[j];
					}
					else {
						pr.actor[j] = '\0';
					}
				}

				films.push_back(pr);
			}

			std::cout << '\n';
			break;

		case 4:
			for (int i = 0; i < films.size(); i++) {
				if (films[i].filmName[0] == 'М') {
					auto it = films.begin();
					std::advance(it, i);
					films.erase(it);
					i--;
				}
			}
			std::cout << "Ненужные фильмы удалены.\n\n";
			break;

		case 5:
			int min, max;
			min = 0;
			max = 0;
			for (int i = 0; i < films.size(); i++) {
				if (films[i].year > films[max].year) {
					max = i;
				}

				if (films[i].year < films[min].year) {
					min = i;
				}
			}

			std::swap(films[min], films[max]);

			break;


		case 6:
			for (int i = 0; i < films.size(); i++) {
				for (int j = i + 1; j < films.size(); j++) {
					if (films[i] < films[j]) {
						std::swap(films[i], films[j]);
					}
				}
			}
			std::cout << "\n";
			break;

		case 7:
			fout.open("M2.txt");
			for (int i = 0; i < films.size(); i++) {
				fout << films[i].filmName << '\t' << films[i].year << '\t' << films[i].duration << '\t' << films[i].type << '\t' << films[i].studioCode << '\t' << films[i].actor << '\t' << films[i].studio << "\n";
			}
			std::cout << '\n';
			break;

		case 8:
			fout.open("M2.bin");
			for (int i = 0; i < films.size(); i++) {
				fout << films[i];
			}
			std::cout << '\n';
			break;

		}



	}

CLOSE_PROGRAMM:
	m.open("M2.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	for (int i = 0; i < films.size(); i++) {
		m.write((char*)&films[i], sizeof(films[0]));
	}
	system("cls");
}


int main() {
	setlocale(LC_ALL, "RUSSIAN");
	std::string TXTfirm = "film.txt";
	std::string TXTstuff = "studio.txt";
	std::string BINfirm = "film.bin";
	std::string BINstuff = "studio.bin";

	TXTtoBIN(TXTfirm, BINfirm);
	TXTtoBIN(TXTstuff, BINstuff);

	CreateNewSortedFile();

	solution();

	return 0;
}