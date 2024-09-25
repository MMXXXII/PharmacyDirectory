#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // Для форматированного вывода
#include <algorithm> // Для сортировки
#include <filesystem>

using namespace std;
namespace fs = std::filesystem; // Сокращение для удобства

struct Medicine {
    string name;           // Название лекарства
    string company;        // Фирма производитель
    string country;        // Страна производитель
    string purpose;        // Назначение
    bool prescription;     // Требуется рецепт
    string form;           // Форма выпуска
};


// Добавление нового лекарства
void addNewMedicine(vector<Medicine>& catalog) {
    Medicine med;
    cout << "Введите название лекарства: ";
    cin >> med.name;
    cout << "Введите фирму-производителя: ";
    cin >> med.company;
    cout << "Введите страну-производителя: ";
    cin >> med.country;
    cout << "Введите назначение лекарства: ";
    cin >> med.purpose;
    cout << "Требуется ли рецепт (1 - да, 0 - нет): ";
    cin >> med.prescription;
    cout << "Введите форму выпуска лекарства: ";
    cin >> med.form;

    catalog.push_back(med);
    cout << "Лекарство успешно добавлено." << endl;
}

// Редактирование лекарства по названию
void editMedicine(vector<Medicine>& catalog, const string& name) {
    for (auto& med : catalog) {
        if (med.name == name) {
            cout << "Редактирование лекарства \"" << name << "\":" << endl;
            cout << "Текущее название: " << med.name << ". Новое название (или оставьте пустым для сохранения): ";
            string newName;
            cin.ignore();
            getline(cin, newName);
            if (!newName.empty()) med.name = newName;

            cout << "Текущая фирма: " << med.company << ". Новая фирма (или оставьте пустым): ";
            string newCompany;
            getline(cin, newCompany);
            if (!newCompany.empty()) med.company = newCompany;

            cout << "Текущая страна: " << med.country << ". Новая страна (или оставьте пустым): ";
            string newCountry;
            getline(cin, newCountry);
            if (!newCountry.empty()) med.country = newCountry;

            cout << "Текущее назначение: " << med.purpose << ". Новое назначение (или оставьте пустым): ";
            string newPurpose;
            getline(cin, newPurpose);
            if (!newPurpose.empty()) med.purpose = newPurpose;

            cout << "Текущий рецепт (1 - да, 0 - нет): " << med.prescription << ". Новый рецепт: ";
            bool newPrescription;
            cin >> newPrescription;
            med.prescription = newPrescription;

            cout << "Текущая форма: " << med.form << ". Новая форма (или оставьте пустым): ";
            string newForm;
            cin.ignore();
            getline(cin, newForm);
            if (!newForm.empty()) med.form = newForm;

            cout << "Лекарство успешно отредактировано." << endl;
            return;
        }
    }
    cout << "Лекарство с названием \"" << name << "\" не найдено." << endl;
}

// Удаление лекарства по названию
void deleteMedicine(vector<Medicine>& catalog, const string& name) {
    auto it = find_if(catalog.begin(), catalog.end(), [&name](const Medicine& med) {
        return med.name == name;
        });

    if (it != catalog.end()) {
        catalog.erase(it); // Удаляем лекарство из вектора
        cout << "Лекарство \"" << name << "\" успешно удалено." << endl;
    }
    else {
        cout << "Лекарство с названием \"" << name << "\" не найдено." << endl;
    }
}




// Функция для вывода информации о лекарстве
void printMedicineInfo(const Medicine& med) {
    cout << left << setw(15) << med.name << setw(20) << med.company
        << setw(15) << med.country << setw(20) << med.purpose
        << setw(10) << (med.prescription ? "Да" : "Нет") << setw(15) << med.form << endl;
}

// Запись данных в файл
void saveToFile(const vector<Medicine>& catalog, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    for (const auto& med : catalog) {
        file << med.name << ";" << med.company << ";" << med.country << ";"
            << med.purpose << ";" << med.prescription << ";" << med.form << endl;
    }
    file.close();
    cout << "Данные успешно сохранены в файл." << endl;
}

// Чтение данных из файла
void loadFromFile(vector<Medicine>& catalog, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    catalog.clear();
    string line;
    while (getline(file, line)) {
        Medicine med;
        size_t pos = 0;
        pos = line.find(';'); med.name = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(';'); med.company = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(';'); med.country = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(';'); med.purpose = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(';'); med.prescription = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        med.form = line;
        catalog.push_back(med);
    }
    file.close();
    cout << "Данные успешно загружены из файла." << endl;
}

// Просмотр всех данных
void displayAllMedicines(const vector<Medicine>& catalog) {
    cout << left << setw(15) << "Название" << setw(20) << "Фирма"
        << setw(15) << "Страна" << setw(20) << "Назначение"
        << setw(10) << "Рецепт" << setw(15) << "Форма" << endl;
    for (const auto& med : catalog) {
        printMedicineInfo(med);
    }
}

// Поиск лекарства по названию
void findMedicineByName(const vector<Medicine>& catalog, const string& name) {
    for (const auto& med : catalog) {
        if (med.name == name) {
            printMedicineInfo(med);
            return;
        }
    }
    cout << "Лекарство с названием \"" << name << "\" не найдено." << endl;
}

// Лекарства одной фирмы производителя
void listMedicinesByCompany(const vector<Medicine>& catalog, const string& company) {
    cout << "Лекарства фирмы \"" << company << "\":" << endl;
    for (const auto& med : catalog) {
        if (med.company == company) {
            printMedicineInfo(med);
        }
    }
}

// Все болеутоляющие без рецепта
void findPainkillersNoPrescription(const vector<Medicine>& catalog) {
    cout << "Болеутоляющие средства без рецепта:" << endl;
    for (const auto& med : catalog) {
        if (med.purpose == "болеутоляющее" && !med.prescription) {
            printMedicineInfo(med);
        }
    }
}

// Сортировка данных по любому полю
void sortCatalog(vector<Medicine>& catalog, const string& field) {
    if (field == "name") {
        sort(catalog.begin(), catalog.end(), [](const Medicine& a, const Medicine& b) { return a.name < b.name; });
    }
    else if (field == "company") {
        sort(catalog.begin(), catalog.end(), [](const Medicine& a, const Medicine& b) { return a.company < b.company; });
    }
    else if (field == "country") {
        sort(catalog.begin(), catalog.end(), [](const Medicine& a, const Medicine& b) { return a.country < b.country; });
    }
    else if (field == "purpose") {
        sort(catalog.begin(), catalog.end(), [](const Medicine& a, const Medicine& b) { return a.purpose < b.purpose; });
    }
    else if (field == "form") {
        sort(catalog.begin(), catalog.end(), [](const Medicine& a, const Medicine& b) { return a.form < b.form; });
    }
    cout << "Данные отсортированы по полю \"" << field << "\"." << endl;
}

// Вывод информации о программе
void aboutProgram() {
    cout << "Аптечный справочник v1.0\n";
    cout << "Последние изменения: 25 сентября 2024\n";
    cout << "Автор: Иван Иванов\n";
    cout << "Контакты: ivan@example.com\n";
}

// Загрузка руководства пользователя
void loadUserGuide(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла справки!" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Функция создания файла через консоль с проверкой существования
string createFile() {
    string filename;
    while (true) {
        cout << "Введите имя файла (с расширением .txt): ";
        cin >> filename;

        // Добавляем расширение .txt, если его нет
        if (filename.find(".txt") == string::npos) {
            filename += ".txt";
        }

        // Проверка существования файла
        if (fs::exists(filename)) {
            cout << "Файл \"" << filename << "\" уже существует." << endl;
            cout << "1. Введите новое название файла." << endl;
            cout << "2. Выйти." << endl;
            int choice;
            cout << "Ваш выбор: ";
            cin >> choice;

            if (choice == 2) {
                cout << "Выход..." << endl;
                return "";
            }
            else if (choice == 1) {
                continue; // Возвращаемся к вводу нового названия файла
            }
            else {
                cout << "Неверный ввод, попробуйте снова." << endl;
            }
        }
        else {
            // Создаем файл
            ofstream file(filename);
            if (!file) {
                cerr << "Ошибка создания файла!" << endl;
            }
            else {
                cout << "Файл \"" << filename << "\" успешно создан." << endl;
                file.close();
                return filename; // Возвращаем имя созданного файла
            }
        }
    }
}

// Главное меню
void mainMenu(vector<Medicine>& catalog) {
    string currentFilename = "medicines.txt";
    loadFromFile(catalog, currentFilename); // Загрузка данных из файла при старте программы

    while (true) {
        cout << "\nГлавное меню:\n";
        cout << "1. Просмотреть все лекарства\n";
        cout << "2. Найти лекарство по названию\n";
        cout << "3. Сформировать перечень лекарств одной фирмы\n";
        cout << "4. Найти болеутоляющие средства без рецепта\n";
        cout << "5. Сортировать лекарства\n";
        cout << "6. Создать новый файл\n";
        cout << "7. О программе\n";
        cout << "8. Руководство пользователя\n";
        cout << "9. Задание\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            saveToFile(catalog, currentFilename);
            cout << "Выход из программы..." << endl;
            break;
        }

        switch (choice) {
        case 1:
            displayAllMedicines(catalog);
            break;
        case 2: {
            string name;
            cout << "Введите название лекарства: ";
            cin >> name;
            findMedicineByName(catalog, name);
            break;
        }
        case 3: {
            string company;
            cout << "Введите название фирмы: ";
            cin >> company;
            listMedicinesByCompany(catalog, company);
            break;
        }
        case 4:
            findPainkillersNoPrescription(catalog);
            break;
        case 5: {
            string field;
            cout << "Введите поле для сортировки (name, company, country, purpose, form): ";
            cin >> field;
            sortCatalog(catalog, field);
            break;
        }
        case 6:
            currentFilename = createFile();
            break;
        case 7:
            aboutProgram();
            break;
        case 8:
            loadUserGuide("user_guide.txt");
            break;
        case 9:
            cout << "Программа «Аптечный справочник» позволяет искать лекарства, просматривать их и сортировать по различным критериям.\n";
            break;
        default:
            cout << "Неверный ввод, попробуйте снова." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Medicine> catalog;
    mainMenu(catalog);
    return 0;
}
