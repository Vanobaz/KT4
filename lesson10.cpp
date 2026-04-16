#include <iostream>
using namespace std;
#include <string>
#include <fstream>


const int SIZE = 20;
enum level{lux, half_lux, standart, eco, armyanskiy_lux};

struct options {
    bool hasBalcony = false;
    bool hasAirConditioner = false;
    bool hasMinibar = false;
};

struct apartment {
	string name = "";
	int apart_num = 0;
	level lv = eco;
	int pers_num = 1;
	double price = 0.0;
	options opts;
};

apartment* init() {
	apartment* apartments = new apartment[SIZE];
    apartments[0] = { "VICTORIA hotel", 456, standart, 2, 4568.0, {true, false, false} };
	apartments[1] = { "Vectop", 45, lux, 2, 12430.0, {true, true, true} };
	apartments[2] = { "IRIS palace", 4, lux, 2, 10200.0, {true, true, true} };
	apartments[3] = { "AVANGARD", 123, standart, 2, 3200, {true, false, false} };
	apartments[4] = { "PRIMAL WEST", 746, standart, 2, 4800.0, {true, false, false} };
	apartments[5] = { "KORD hotel", 23, eco, 5, 2300.0, {false, false, false} };
	apartments[6] = { "Kirin hotel", 112, eco, 2, 1200.0, {false, false, false} };
	apartments[7] = { "Britanika", 312, half_lux, 2, 5780.0, {true, false, false} };
	apartments[8] = { "NizhkA", 737, standart, 2, 3456.0, {false, false, true} };
	apartments[9] = { "Armen hotel", 265, armyanskiy_lux, 2, 15600.0, {true, true, true} };
	apartments[10] = { "Venture hotel", 177, standart, 2, 3600.0, {false, false, false} };
	apartments[11] = { "AMAZONKA", 3, standart, 2, 4120.0, {true, false, false} };
	apartments[12] = { "Lapland", 23, lux, 2, 13870.0, {true, true, true} };
	apartments[13] = { "ESCALATE", 457, half_lux, 2, 9200.0, {true, true, true} };
	apartments[14] = { "BRIM", 637, standart, 2, 3999.0, {false, true, false} };
	apartments[15] = { "Last Accord", 7, lux, 2, 98999.0, {true, true, true} };
	apartments[16] = { "Cool Vibrations", 13, standart, 2, 560.0, {true, false, true} };
	apartments[17] = { "PANZERCAT hotel", 1488, standart, 2, 6666.0, {false, true, true} };
	apartments[18] = { "Kirby", 1, standart, 2, 5780.0, {true, true, false} };
	apartments[19] = { "Lightning MCentosh", 76, eco, 2, 2100.0, {false, false, false} };
	return apartments;
}



bool endsWithHotel(string name) {
    if (name.length() < 5) return false;
    string ending = name.substr(name.length() - 5);
    for (char& ch : ending) if (ch >= 'A' && ch <= 'Z') ch += 32;
    return ending == "hotel";
}



string levelToString(level c) {
    switch (c) {
    case lux: return "люкс";
    case half_lux: return "полулюкс";
    case standart: return "стандарт";
    case eco: return "эконом";
    case armyanskiy_lux: return "армяне";
    default: return "неизвестно";
    }
}

level stringToLevel(string lv) {
    if (lv == "0" || lv == "lux") return lux;
    if (lv == "1" || lv == "half_lux") return half_lux;
    if (lv == "2" || lv == "standart") return standart;
    if (lv == "3" || lv == "eco") return eco;
    if (lv == "4" || lv == "armyanskiy_lux") return armyanskiy_lux;
    return eco;
}


int filterByHotel(apartment* source, apartment* dest, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (endsWithHotel(source[i].name)) {
            dest[count] = source[i];
            count++;
        }
    }
    return count;
}


void sortByPrice(apartment* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].price > arr[j + 1].price) {
                apartment temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void printRoom(apartment room) {
    std::cout << "Гостиница: " << room.name << endl;
    std::cout << "Номер: " << room.apart_num << endl;
    std::cout << "Комфорт: " << levelToString(room.lv) << endl;
    std::cout << "Количество человек: " << room.pers_num << endl;
    std::cout << "Стоимость: " << room.price << " руб." << endl;
    std::cout << "Опции: балкон=" << (room.opts.hasBalcony ? "да" : "нет");
    std::cout << ", кондиционер=" << (room.opts.hasAirConditioner ? "да" : "нет");
    std::cout << ", мини-бар=" << (room.opts.hasMinibar ? "да" : "нет") << endl;
    std::cout << "------------------------" << endl;
}


int findRoom(apartment* arr, int size, string name, int apart_num) {
    for (int i = 0; i < size; i++) {
        if (arr[i].name == name && arr[i].apart_num == apart_num) {
            return i;
        }
    }
    return -1;
}


void print3CheapestMissing(apartment* arr, int size) {
    std::cout << "\n=== 3 самых дешевых номера и отсутствующие опции ===" << endl;

    int count = (size < 3) ? size : 3;

    for (int i = 0; i < count; i++) {
        std::cout << "\n" << arr[i].name << ", номер " << arr[i].apart_num << endl;
        std::cout << "Цена: " << arr[i].price << " руб." << endl;
        std::cout << "Отсутствуют опции: ";

        bool hasMissing = false;

        if (!arr[i].opts.hasBalcony) {
            std::cout << "балкон"; hasMissing = true;
        }
        if (!arr[i].opts.hasAirConditioner) {
            if (hasMissing) std::cout << ", ";
            std::cout << "кондиционер"; hasMissing = true;
        }
        if (!arr[i].opts.hasMinibar) {
            if (hasMissing) std::cout << ", ";
            std::cout << "мини-бар"; hasMissing = true;
        }

        if (!hasMissing) std::cout << "нет (все опции есть)";
        std::cout << endl << "\n\n";
    }
}


void changeRoom(apartment* arr, int size) {
    string hotelName;
    int roomNum;

    std::cout << "\nВведите название гостиницы: ";
    getline(cin, hotelName);
    std::cout << "Введите номер комнаты: ";
    cin >> roomNum;
    cin.ignore();

    int index = findRoom(arr, size, hotelName, roomNum);

    if (index == -1) {
        std::cout << "Номер не найден!" << endl;
        return;
    }

    std::cout << "\nВведите новые данные:" << endl;
    std::cout << "Комфорт (0-люкс, 1-полулюкс, 2-стандарт, 3-эконом): ";
    int comfort;
    cin >> comfort;
    arr[index].lv = (level)comfort;

    std::cout << "Количество человек: ";
    cin >> arr[index].pers_num;

    std::cout << "Стоимость: ";
    cin >> arr[index].price;

    std::cout << "Есть балкон (1-да, 0-нет): ";
    cin >> arr[index].opts.hasBalcony;

    std::cout << "Есть кондиционер (1-да, 0-нет): ";
    cin >> arr[index].opts.hasAirConditioner;

    std::cout << "Есть мини-бар (1-да, 0-нет): ";
    cin >> arr[index].opts.hasMinibar;

    std::cout << "Данные изменены!" << endl;

    printRoom(arr[index]);
}



bool checkBalcony(apartment w) {return w.opts.hasBalcony;}
bool checkAirConditioner(apartment w) {return w.opts.hasAirConditioner;}
bool checkMinibar(apartment w) {return w.opts.hasMinibar;}
bool checkLux(apartment w) {return w.lv == lux;}
bool checkEco(apartment w) {return w.lv == eco;}


void print(apartment* arr, int size, bool (*y)(apartment), string description) {
    std::cout << "\n=== " << description << " ===" << endl;

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (y(arr[i])) {
            printRoom(arr[i]);
            count++;
        }
    }

    if (count == 0) {
        std::cout << "Нет записей, соответствующих фильтру" << endl;
    }
    else {
        std::cout << "Найдено записей: " << count << endl;
    }
}

int filterByBalcony(apartment* source, apartment* dest, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (checkBalcony(source[i])) {
            dest[count] = source[i];
            count++;
        }
    }
    return count;
}


bool updatePersNumFromFile(apartment* arr, int size, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "не удалось открыть файл: " << filename << endl;
        return false;
    }

    string line; int updated = 0;
    while (getline(fin, line)) {
        size_t pos = line.find('|');
        if (pos == string::npos) continue;

        string name = line.substr(0, pos);
        int newPers = stoi(line.substr(pos + 1));

        for (int i = 0; i < size; i++) {
            if (arr[i].name == name) {
                arr[i].pers_num = newPers;
                cout << "Обновлено: " << name << "кол-во человек = " << newPers << endl;
                updated++;
                break;
            }
        }
    }
    fin.close();
    cout << "Обновлено записей: " << updated << endl;
    return true;
}

bool saveToTextFile(apartment* arr, int size, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Ошибка записи в файл: " << filename << endl;
        return false;
    }

    
    fout << "# name|apart_num|comfort|pers_num|price|balcony|ac|minibar\n";
    for (int i = 0; i < size; i++) {
        fout << arr[i].name << "|"
            << arr[i].apart_num << "|"
            << arr[i].lv << "|"
            << arr[i].pers_num << "|"
            << arr[i].price << "|"
            << arr[i].opts.hasBalcony << "|"
            << arr[i].opts.hasAirConditioner << "|"
            << arr[i].opts.hasMinibar << "\n";
    }
    fout.close();
    cout << "Данные сохранены в текстовый файл: " << filename << "\n";
    return true;
}


bool saveToBinaryFile(apartment* arr, int size, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        cout << "Ошибка записи бинарного файла: " << filename << endl;
        return false;
    }

    fout.write((char*)&size, sizeof(size));
    fout.write((char*)arr, sizeof(apartment) * size);

    fout.close();
    cout << "Бинарный файл создан: " << filename << " (" << size << " записей)\n";
    return true;
}


bool loadFromBinaryFile(apartment* arr, int& size, const string& filename, int maxSize) {
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cout << "Не удалось открыть бинарный файл: " << filename << endl;
        return false;
    }

    
    fin.read((char*)&size, sizeof(size));
    if (size > maxSize) {
        cout << "В файке больше записей (" << size
            << "), чем размер массива (" << maxSize << ")\n";
        size = maxSize;
    }

    
    fin.read((char*)arr, sizeof(apartment) * size);
    fin.close();

    cout << "Загружено из бинарного файла: " << size << " записей\n";
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    apartment* apartments = init();
  
    apartment* filtered_apartments = new apartment[SIZE];
    int hotelCount = filterByHotel(apartments, filtered_apartments, SIZE);
    cout << "Найдено номеров с окончанием 'hotel': " << hotelCount << endl << endl;

    sortByPrice(filtered_apartments, hotelCount);
    cout << "Массив отсортирован по возрастанию стоимости" << endl << endl;

    cout << "\n=== Все номера с окончанием 'hotel' (отсортированные) ===" << endl;
    for (int i = 0; i < hotelCount; i++) {
        printRoom(filtered_apartments[i]);
    }

    cout << "\n=== Поиск конкретного номера ===" << endl;
    int idx = findRoom(filtered_apartments, hotelCount, "VICTORIA hotel", 456);
    if (idx != -1) {
        cout << "\nНайден номер:" << endl;
        printRoom(filtered_apartments[idx]);
    }
    else {
        cout << "Номер не найден" << endl;
    }

    print3CheapestMissing(filtered_apartments, hotelCount);


    apartment* balconyRooms = new apartment[SIZE];
    int balconyCount = filterByBalcony(apartments, balconyRooms, SIZE);
    cout << "\n=== Номера с балконом: " << balconyCount << " ===" << endl;
    for (int i = 0; i < balconyCount; i++) {
        printRoom(balconyRooms[i]);
    }
    
    
    print(apartments, SIZE, checkAirConditioner, "Номера с кондиционером");
    print(apartments, SIZE, checkLux, "Люкс номера");


    {
        ofstream test("update_pers.txt");
        test << "VICTORIA hotel|4\nKirin hotel|3\nArmen hotel|5\n";
        test.close();
    }
    cout << "\nОбновление вместимости из текстового файла" << endl;
    updatePersNumFromFile(apartments, SIZE, "update_pers.txt");

    cout << "\nБинарный файл" << endl;

    saveToBinaryFile(filtered_apartments, hotelCount, "hotels_binary.dat");

    apartment* loaded = new apartment[SIZE]();
    int loadedSize = 0;
    if (loadFromBinaryFile(loaded, loadedSize, "hotels_binary.dat", SIZE)) {
        cout << "\nПроверка загрузки: первые 2 записи из бинарного файла:\n";
        for (int i = 0; i < min(2, loadedSize); i++) printRoom(loaded[i]);
    }
    delete[] loaded;

    saveToTextFile(filtered_apartments, hotelCount, "hotels_export.txt");

    cout << "\n\n" << "=== Измененние данных ===" << endl;
    changeRoom(apartments, SIZE);

    delete[] apartments;
    delete[] filtered_apartments;
    delete[] balconyRooms;

    system("pause");
    return 0;
}
