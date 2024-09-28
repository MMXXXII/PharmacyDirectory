/*1. программа должна иметь модульную структуру, т.е. должна состоятьиз отдельных функций +
2. формирование файла (запись введенных данных в файл); +
3. редактирование данных (добавление, удаление, изменение сведений);
4. использование отдельного диалога для ввода и проверка корректности
всех входных данных;
5. вывод исходных данных (просмотр всех сведений) и реализация всех
указанных в задании действий по сортировке и выборке данных;
6. использование главного и контекстного меню;
7. результаты расчетов и поиска должны быть оформлены в соответствующем виде (с использованием форматированного вывода);
8. наличие в главном меню раздела «О программе», в котором указать
версию программного продукта, дату внесения последних изменений в программе и координаты автора;
9. наличие в главном меню раздела «Руководство пользователя (Справка)», содержание которого загружается из текстового файла;
10. наличие в главном меню раздела «Задание», содержащего постановку
задачи.
11. корректная обработка диалога работы с файлами (например, запрет открытия несуществующего файла, либо запрос на перезапись уже существующего файла, настройка фильтров и др.);
12. проверка сохранения сведений в файле при выходе из программы;
13. сортировка выводимой информации по любому из полей записи (критерий сортировки указывается в меню), используя одну процедуру сортировки
для всех пунктов меню;
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // Для форматированного вывода
#include <algorithm> // Для сортировки
#include <filesystem>
#include <windows.h>
#include <regex>
#include <limits>
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



string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return ""; // строка состоит только из пробелов
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool isValidMedicineName(const string& name) {
    // Регулярное выражение для проверки:
    // Название должно начинаться с заглавной буквы,
    // за ней могут следовать строчные буквы
    // Каждое слово должно начинаться с заглавной буквы
    return regex_match(name, regex(R"(^[A-ZА-ЯЁ][a-zа-яё]*(\s+[A-ZА-ЯЁ][a-zа-яё]*)*$)"));
}


bool isValidCountryName(const string& name) {
    // Регулярное выражение для проверки:
    // Название должно начинаться с заглавной буквы,
    // за ней могут следовать любые буквы (как заглавные, так и строчные)
    return regex_match(name, regex(R"(^[A-ZА-ЯЁ][a-zа-яё]*(\s+[A-ZА-ЯЁ][a-zа-яё]*)*$)"));
}


void addNewMedicine(vector<Medicine>& catalog) {
    Medicine med;
    cin.ignore();
    while (true) {
        cout << "Введите название лекарства: ";
        getline(cin, med.name);
        med.name = trim(med.name); // Убираем пробелы

        // Проверка на пустую строку
        if (med.name.empty()) {
            cout << "Ошибка: название лекарства не может быть пустым. Пожалуйста, введите название заново." << endl;
            continue; // Запрашиваем ввод снова
        }


        // Проверка на корректность названия лекарства
        if (isValidMedicineName(med.name)) {
            catalog.push_back(med); // Добавляем лекарство в каталог
            cout << "Лекарство успешно добавлено в каталог." << endl;
            break; // Название лекарства корректно, выходим из цикла
        }

        else {
            cout << "Ошибка: название лекарства должно начинаться с заглавной буквы, а все остальные буквы — строчные. Пожалуйста, введите название заново." << endl;
        }
    }


    // Ввод названия фирмы
    do {
        cout << "Введите название фирмы: ";
        getline(cin, med.company);
        med.company = trim(med.company); // Убираем пробелы

        if (!isValidMedicineName(med.company)) {
            cout << "Ошибка: название фирмы должно начинаться с заглавной буквы." << endl;
        }
    } while (!isValidMedicineName(med.company));

    cout << "Фирма успешно добавлена в каталог" << endl;



    do {
        cout << "Введите название страны: ";
        getline(cin, med.country); // Используем getline для ввода с пробелами
        med.country = trim(med.country); // Убираем пробелы

        if (!isValidCountryName(med.country)) {
            cout << "Ошибка: название страны должно начинаться с заглавной буквы." << endl;
        }
    } while (!isValidCountryName(med.country));

    cout << "Страна успешно добавлена в каталог." << endl;


    vector<string> validPurposes = {
        "Болеутоляющие",
        "Противовоспалительные",
        "Антибиотики",
        "Противовирусные",
        "Противогрибковые",
        "Противоаллергические",
        "Антидепрессанты",
        "Антипсихотики",
        "Снотворные"
    };

    while (true) {
        cout << "Введите назначение лекарства (доступные варианты):" << endl;

        // Вывод всех доступных вариантов
        for (const auto& purpose : validPurposes) {
            cout << "- " << purpose << endl;
        }

        // Запрос ввода
        string input;
        cout << "Ваш ввод: ";
        getline(cin, input);

        // Здесь можно добавить проверку на допустимость ввода
        // Например, можно проверить, содержится ли введенное назначение в validPurposes

        if (find(validPurposes.begin(), validPurposes.end(), input) != validPurposes.end()) {
            cout << "Назначение успешно добавлено: " << input << endl;
            break; // Выходим из цикла, если ввод корректен
        }
        else {
            cout << "Ошибка: недопустимое назначение. Пожалуйста, попробуйте снова." << endl;
        }
    }


    while (true) {
        cout << "Требуется ли рецепт (1 - да, 0 - нет): ";
        string input;
        cin >> input; // Читаем ввод как строку

        // Проверка на ввод цифры
        if (input.length() != 1 || (input[0] != '0' && input[0] != '1')) {
            cout << "Ошибка: введите 1 для 'да' или 0 для 'нет'." << endl;
            cin.clear(); // Очищаем состояние cin
            
        }
        else {
            // Если ввод корректен, преобразуем строку в число
            med.prescription = input[0] - '0'; // '0' -> 0, '1' -> 1
            break; // Ввод корректен, выходим из цикла
        }
    }

    cout << " " << endl;

    vector<string> validForms = {
        "Таблетки",
        "Капсулы",
        "Сироп",
        "Раствор",
        "Порошок",
        "Суппозитории",
        "Пластыри"
    };

    while (true) {
        cout << "Введите форму выпуска лекарства (доступные варианты):" << endl;
        for (const auto& form : validForms) {
            cout << "- " << form << endl;
        }

        // Запрос ввода формы
        cout << "Ваш ввод: ";
        getline(cin >> ws, med.form); // Используем getline для ввода с пробелами и очищаем пробелы

        // Проверка на допустимость введенной формы
        bool valid = false;
        for (const auto& validForm : validForms) {
            if (med.form == validForm) {
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << "Ошибка: недопустимая форма выпуска. Пожалуйста, выберите из предложенных вариантов." << endl;
        }
        else {
            break; // Форма введена корректно
        }
    }

    catalog.push_back(med);
    cout << "Лекарство успешно добавлено." << endl;
}



void printMedicineTable(const vector<Medicine>& catalog) {
    if (catalog.empty()) {
        cout << "Список лекарств пуст." << endl;
        return;
    }

    // Определение максимальной длины для каждого столбца на основе заголовков
    size_t max_name_length = 20;        // Максимальная длина для названия лекарства
    size_t max_company_length = 20;     // Максимальная длина для фирмы
    size_t max_country_length = 15;     // Максимальная длина для страны
    size_t max_purpose_length = 25;     // Максимальная длина для назначения
    size_t max_form_length = 10;        // Максимальная длина для формы выпуска
    size_t max_prescription_length = 15; // Максимальная длина для рецепта

    // Печать заголовка таблицы
    cout << "ID | " << setw(max_name_length) << left << "Название лекарства" << " | "
        << setw(max_company_length) << left << "Фирма" << " | "
        << setw(max_country_length) << left << "Страна" << " | "
        << setw(max_purpose_length) << left << "Назначение" << " | "
        << setw(max_form_length) << left << "Форма" << " | "
        << setw(max_prescription_length) << left << "Требуется рецепт" << endl;

    // Печать разделителя
    cout << setfill('-') << setw(4 + max_name_length + max_company_length + max_country_length +
        max_purpose_length + max_form_length + max_prescription_length) << "-" << endl;

    // Печать данных о лекарствах
    for (size_t i = 0; i < catalog.size(); ++i) {
        cout << setfill(' ') << setw(2) << right << i + 1 << " | "
            << setw(max_name_length) << left << catalog[i].name << " | "
            << setw(max_company_length) << left << catalog[i].company << " | "
            << setw(max_country_length) << left << catalog[i].country << " | "
            << setw(max_purpose_length) << left << catalog[i].purpose << " | "
            << setw(max_form_length) << left << catalog[i].form << " | "
            << setw(max_prescription_length) << left << (catalog[i].prescription ? "Да" : "Нет") << endl;
    }

    cout << setfill(' ') << endl; // Дополнительная пустая строка в конце
}

void editMedicine(vector<Medicine>& catalog, const string& name) {

    for (auto& med : catalog) {
        if (med.name == name) {
            cout << "Редактирование лекарства \"" << name << "\":" << endl;
            cout << "Текущее название: " << med.name << ". Новое название (или оставьте пустым для сохранения): ";
            string newName;
            cin.ignore();
            getline(cin, newName);

            if (!newName.empty()) {
                cout << "Вы уверены, что хотите изменить название лекарства с \"" << med.name << "\" на \"" << newName << "\"? (1 - Да, 0 - Нет): ";
                int confirm;
                cin >> confirm;
                if (confirm == 1) {
                    med.name = newName;  // Меняем название только после подтверждения
                }
                else {
                    cout << "Название лекарства не изменено." << endl;
                }
            }

            cout << "Текущая фирма: " << med.company << ". Новая фирма (или оставьте пустым): ";
            string newCompany;
            cin.ignore();
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


// Функция для сохранения в новый файл с проверкой существования
void saveToNewFile(const vector<Medicine>& catalog) {
    string filename;
    while (true) {
        cout << "Введите название файла для сохранения (с расширением .txt): ";
        cin >> filename;

        // Проверка на наличие расширения .txt
        if (filename.find(".txt") == string::npos) {
            cout << "Ошибка: файл должен иметь расширение .txt." << endl;
            continue; // Запрашиваем ввод заново
        }

        // Проверка существования файла
        if (fs::exists(filename)) {
            cout << "Файл \"" << filename << "\" уже существует." << endl;
            cout << "1. Перезаписать файл." << endl;
            cout << "2. Ввести другое название файла." << endl;
            cout << "3. Выйти без сохранения." << endl;
            int choice;
            cout << "Ваш выбор: ";
            cin >> choice;

            if (choice == 3) {
                cout << "Выход из меню сохранения..." << endl;
                return;
            }
            else if (choice == 2) {
                continue; // Возвращаемся к вводу нового названия файла
            }
            else if (choice != 1) {
                cout << "Неверный ввод, попробуйте снова." << endl;
                continue; // Запрашиваем ввод заново
            }
        }

        // Сохраняем в файл (или перезаписываем, если он существует)
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка создания файла!" << endl;
        }
        else {
            for (const auto& med : catalog) {
                file << med.name << ";" << med.company << ";" << med.country << ";"
                    << med.purpose << ";" << med.prescription << ";" << med.form << endl;
            }
            cout << "Данные успешно сохранены в файл \"" << filename << "\"." << endl;
            file.close();
        }
        return;
    }
}

// Чтение данных из файла
void loadFromFile(vector<Medicine>& catalog, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << filename << endl;
        return;
    }
    cout << "Файл открыт успешно: " << filename << endl;

    catalog.clear();
    string line;

    while (getline(file, line)) {
        Medicine med;
        size_t pos = 0;

        // Чтение названия лекарства
        pos = line.find(';');
        med.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение компании
        pos = line.find(';');
        med.company = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение страны
        pos = line.find(';');
        med.country = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение назначения
        pos = line.find(';');
        med.purpose = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение формы выпуска
        pos = line.find(';');
        med.form = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение рецепта (требуется или нет)
        med.prescription = (line == "Да");

        catalog.push_back(med);
    }

    file.close();
    cout << "Данные успешно загружены из файла." << endl;
}

// Просмотр всех данных
void displayAllMedicines(const vector<Medicine>& catalog) {
    if (catalog.empty()) { // Проверка на пустой каталог
        cout << "Нет лекарств для отображения." << endl;
        return;
    }

    printMedicineTable(catalog); // Используем новую таблицу для вывода всех лекарств
}

// Поиск лекарства по названию
void findMedicineByName(const vector<Medicine>& catalog, const string& name) {
    vector<Medicine> foundMedicines;
    for (const auto& med : catalog) {
        if (med.name == name) {
            foundMedicines.push_back(med);
        }
    }

    if (foundMedicines.empty()) {
        cout << "Лекарство с названием \"" << name << "\" не найдено." << endl;
    }
    else {
        printMedicineTable(foundMedicines); // Выводим найденные лекарства
    }
}

// Лекарства одной фирмы производителя
void listMedicinesByCompany(const vector<Medicine>& catalog, const string& company) {
    vector<Medicine> companyMedicines;
    for (const auto& med : catalog) {
        if (med.company == company) {
            companyMedicines.push_back(med);
        }
    }

    if (companyMedicines.empty()) {
        cout << "Нет лекарств фирмы \"" << company << "\"." << endl;
    }
    else {
        cout << "Лекарства фирмы \"" << company << "\":" << endl;
        printMedicineTable(companyMedicines); // Выводим лекарства данной фирмы
    }
}

void findPainkillersNoPrescription(const vector<Medicine>& catalog) {
    vector<Medicine> painkillers;

    for (const auto& med : catalog) {
        // Приводим строку к нижнему регистру для корректного сравнения
        string purpose_lower = med.purpose;
        transform(purpose_lower.begin(), purpose_lower.end(), purpose_lower.begin(), ::tolower);

        if (purpose_lower == "болеутоляющее" && !med.prescription) {
            painkillers.push_back(med);
        }
    }

    if (painkillers.empty()) {
        cout << "Нет болеутоляющих средств без рецепта." << endl;
    }
    else {
        cout << "Болеутоляющие средства без рецепта:" << endl;
        printMedicineTable(painkillers); // Выводим болеутоляющие средства без рецепта
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
    string currentFilename;

    while (true) {
        cout << "\nГлавное меню:\n";
        cout << "1. Импортировать данные из файла\n";
        cout << "2. Ввести информацию о лекарстве\n";
        cout << "3. Редактировать лекарство\n";
        cout << "4. Удалить лекарство\n";
        cout << "5. Просмотреть все лекарства\n";
        cout << "6. Найти лекарство по названию\n";
        cout << "7. Сформировать перечень лекарств одной фирмы\n";
        cout << "8. Найти болеутоляющие средства без рецепта\n";
        cout << "9. Сортировка лекарств\n";
        cout << "10. Сохранить в файл\n";
        cout << "11. О программе\n";
        cout << "12. Руководство пользователя\n";
        cout << "13. Выход\n";
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введите имя файла для загрузки (с расширением .txt): ";
            cin >> currentFilename;
            loadFromFile(catalog, currentFilename);
            break;
        }
        case 2:
            addNewMedicine(catalog);
            break;
        case 3: {
            if (catalog.empty()) {
                cout << "Нет лекарств для редактирования." << endl;
                break;
            }
            string name;
            cout << "Введите название лекарства для редактирования: ";
            cin >> name;
            editMedicine(catalog, name);
            break;
        }
        case 4: {
            if (catalog.empty()) {
                cout << "Нет лекарств для удаления." << endl;
                break;
            }
            string name;
            cout << "Введите название лекарства для удаления: ";
            cin >> name;
            deleteMedicine(catalog, name);
            break;
        }
        case 5:
            displayAllMedicines(catalog);
            break;
        case 6: {
            string name;
            cout << "Введите название лекарства для поиска: ";
            cin >> name;
            findMedicineByName(catalog, name);
            break;
        }
        case 7: {
            string company;
            cout << "Введите название фирмы: ";
            cin >> company;
            listMedicinesByCompany(catalog, company);
            break;
        }
        case 8:
            findPainkillersNoPrescription(catalog);
            break;
        case 9: {
            string field;
            cout << "Введите поле для сортировки (name, company, country, purpose, form): ";
            cin >> field;
            sortCatalog(catalog, field);
            break;
        }
        case 10:
            saveToNewFile(catalog);
            break;
        case 11:
            aboutProgram();
            break;
        case 12:
            loadUserGuide("C:\\Users\\PC\\Desktop\\Учеба\\Курсовой\\Делаю\\PharmacyDirectory\\PharmacyDirectory\\Руководство пользователя.txt");
            break;
        case 13:
            cout << "Выход из программы..." << endl;
            return; // Завершение программы
        default:
            cout << "Неверный ввод, попробуйте снова." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    vector<Medicine> catalog;
    mainMenu(catalog);
    return 0;
}