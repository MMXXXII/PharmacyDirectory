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
#include <cctype>
#include <codecvt>



using namespace std;
namespace fs = std::filesystem; // Сокращение для удобства

struct Medicine {
    string name;           // Название лекарства
    string company;        // Фирма производитель
    string country;        // Страна производитель
    string purpose;        // Назначение
    string prescription;     // Требуется рецепт
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
    size_t max_form_length = 12;        // Максимальная длина для формы выпуска
    size_t max_prescription_length = 14; // Максимальная длина для рецепта

    // Вектор с возможными формами выпуска
    vector<string> validForms = {
        "Таблетки", "Капсулы", "Сироп", "Раствор", "Порошок", "Суппозитории", "Пластыри"
    };

    // Печать заголовка таблицы
    cout << "ID | " << setw(max_name_length) << left << "Название лекарства" << " | "
        << setw(max_company_length) << left << "Фирма" << " | "
        << setw(max_country_length) << left << "Страна" << " | "
        << setw(max_purpose_length) << left << "Назначение" << " | "
        << setw(max_prescription_length) << left << "Требуется рецепт" << " | "
        << setw(max_form_length) << left << "Форма" << endl;

    // Печать разделителя
    cout << setfill('-') << setw(4 + max_name_length + max_company_length + max_country_length +
        max_purpose_length + max_prescription_length + max_form_length) << "-" << endl;

    // Печать данных о лекарствах
    for (size_t i = 0; i < catalog.size(); ++i) {
        int formIndex = -1;
        for (size_t j = 0; j < validForms.size(); ++j) {
            if (validForms[j] == catalog[i].form) {
                formIndex = j;
                break;
            }
        }

        if (formIndex == -1) {
            cerr << "Ошибка: недопустимая форма выпуска для лекарства \"" << catalog[i].name << "\"" << endl;
            continue; // Пропускаем этот элемент
        }

        cout << setfill(' ') << setw(2) << right << i + 1 << " | "
            << setw(max_name_length) << left << catalog[i].name << " | "
            << setw(max_company_length) << left << catalog[i].company << " | "
            << setw(max_country_length) << left << catalog[i].country << " | "
            << setw(max_purpose_length) << left << catalog[i].purpose << " | "
            << setw(max_prescription_length) << left << (catalog[i].prescription == "да" ? "Да" : "Нет") << " | "
            << setw(max_form_length) << left << catalog[i].form << endl;
    }

    cout << setfill(' ') << endl; // Дополнительная пустая строка в конце
}



bool isValidMedicineFirm(const string& name) {
    if (name.empty()) return false;

    // Проверка, что первая буква заглавная
    if (!isupper(name[0])) return false;

    bool allLowerAfterFirst = true;
    bool allUpperAfterFirst = true;

    for (size_t i = 1; i < name.size(); ++i) {
        char c = name[i];

        // Допустимые символы: только буквы
        if (!isalpha(c)) return false;

        // Проверка на строчные и заглавные буквы после первой
        if (islower(c)) {
            allUpperAfterFirst = false;
        }
        else {
            allLowerAfterFirst = false;
        }
    }

    // Либо все буквы после первой строчные, либо все заглавные
    return allLowerAfterFirst || allUpperAfterFirst;
}



void addNewMedicine(vector<Medicine>& catalog) {
    Medicine med;
    cin.ignore();

    // Ввод названия лекарства
    while (true) {
        cout << "Введите название лекарства: ";
        getline(cin, med.name);
        med.name = trim(med.name);

        if (med.name.empty()) {
            cout << "Ошибка: название лекарства не может быть пустым. Пожалуйста, введите название заново." << endl;
        }
        else if (!isValidMedicineName(med.name)) {
            cout << "Ошибка: название лекарства должно начинаться с заглавной буквы, не иметь цифр и специальных знаков." << endl;
        }
        else {
            cout << "Лекарство успешно добавлено в каталог." << endl;
            break;
        }
    }

    // Ввод названия фирмы
    while (true) {
        cout << "Введите название фирмы: ";
        getline(cin, med.company);
        med.company = trim(med.company);

        if (!isValidMedicineFirm(med.company)) {
            cout << "Ошибка: название фирмы должно начинаться с заглавной буквы, либо все буквы должны быть заглавными и не иметь цифр и специальных знаков" << endl;
        }
        else {
            cout << "Фирма успешно добавлена в каталог." << endl;
            break;
        }
    }

    // Ввод названия страны
    while (true) {
        cout << "Введите название страны: ";
        getline(cin, med.country);
        med.country = trim(med.country);

        if (!isValidCountryName(med.country)) {
            cout << "Ошибка: название страны должно начинаться с заглавной буквы." << endl;
        }
        else {
            cout << "Страна успешно добавлена в каталог." << endl;
            break;
        }
    }

    // Ввод назначения лекарства
    vector<string> validPurposes = {
    "Болеутоляющие", "Противовоспалительные", "Антибиотики", "Противовирусные",
    "Противогрибковые", "Противоаллергические", "Антидепрессанты",
    "Антипсихотики", "Снотворные"
    };

    while (true) {
        cout << "Выберите назначение лекарства (введите номер):" << endl;
        for (size_t i = 0; i < validPurposes.size(); ++i) {
            cout << i + 1 << " - " << validPurposes[i] << endl;
        }

        string input;
        cout << "Ваш выбор: ";
        cin >> input;

        // Проверка, является ли ввод числом
        if (input.find_first_not_of("0123456789") != string::npos) {
            cout << "Ошибка: введите число." << endl;
            cin.clear(); // Сброс флага ошибки
            cin.ignore(); // Очистка буфера ввода
            continue;
        }

        int choice = stoi(input);

        if (choice >= 1 && choice <= validPurposes.size()) {
            med.purpose = validPurposes[choice - 1];
            cout << "Назначение успешно добавлено: " << med.purpose << endl;
            break;
        }
        else {
            cout << "Ошибка: недопустимый номер. Пожалуйста, выберите из предложенных вариантов." << endl;
            cin.clear(); // Сброс флага ошибки
            cin.ignore(); // Очистка буфера ввода
        }
    }

    // Ввод информации о рецепте
    while (true) {
        cout << "Требуется ли рецепт (Да/Нет): ";
        cin >> med.prescription;

        if (med.prescription == "Да" || med.prescription == "Нет") {
            break;
        }
        else {
            cout << "Ошибка: введите 'Да' или 'Нет' с заглавной буквы." << endl;
        }
    }

    cin.ignore(); // Очистка буфера после ввода

    // Ввод формы выпуска
    vector<string> validForms = {
    "Таблетки", "Капсулы", "Сироп", "Раствор", "Порошок", "Суппозитории", "Пластыри"
    };

    while (true) {
        cout << "Выберите форму выпуска лекарства (введите номер):" << endl;
        for (size_t i = 0; i < validForms.size(); ++i) {
            cout << i + 1 << " - " << validForms[i] << endl;
        }

        string input;
        cout << "Ваш выбор: ";
        cin >> input;

        // Проверка, является ли ввод числом
        if (input.find_first_not_of("0123456789") != string::npos) {
            cout << "Ошибка: введите число." << endl;
            cin.clear(); // Сброс флага ошибки
            cin.ignore(); // Очистка буфера ввода
            continue;
        }

        int choice = stoi(input);

        if (choice >= 1 && choice <= validForms.size()) {
            med.form = validForms[choice - 1];
            break;
        }
        else {
            cout << "Ошибка: недопустимый номер. Пожалуйста, выберите из предложенных вариантов." << endl;
            cin.clear(); // Сброс флага ошибки
            cin.ignore(); // Очистка буфера ввода
        }
    }

    catalog.push_back(med); // Добавляем лекарство в каталог

    // Проверка введенных данных
    bool dataEnteredCorrectly = false;
    while (!dataEnteredCorrectly) {
        printMedicineTable(catalog); // Печать таблицы с лекарствами

        cout << endl << "Данные введены верно?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;

        string input;
        cout << "Ваш выбор: ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "да" || input == "1") {
            cout << "Лекарство успешно добавлено." << endl;
            dataEnteredCorrectly = true;
        }
        else if (input == "нет" || input == "2") {
            // Изменение данных лекарства
            string fieldChoice;
            cout << "Какой параметр вы хотите изменить?" << endl;
            cout << "1. Название лекарства" << endl;
            cout << "2. Название фирмы" << endl;
            cout << "3. Название страны" << endl;
            cout << "4. Назначение" << endl;
            cout << "5. Требуется ли рецепт" << endl;
            cout << "6. Форма выпуска" << endl;
            cout << "Ваш выбор: ";
            cin >> fieldChoice;

            cin.ignore(); // Очистка буфера

            if (fieldChoice == "1") {
                while (true) {
                    cout << "Введите новое название лекарства: ";
                    getline(cin, med.name);
                    med.name = trim(med.name);

                    if (med.name.empty()) {
                        cout << "Ошибка: название лекарства не может быть пустым. Пожалуйста, введите название заново." << endl;
                    }
                    else if (!isValidMedicineName(med.name)) {
                        cout << "Ошибка: название лекарства должно начинаться с заглавной буквы, а остальные буквы должны быть строчными." << endl;
                    }
                    else {
                        catalog.back().name = med.name; // Обновляем название в каталоге
                        break;
                    }
                }
            }
            else if (fieldChoice == "2") {
                while (true) {
                    cout << "Введите новое название фирмы: ";
                    getline(cin, med.company);
                    med.company = trim(med.company);

                    if (!isValidMedicineName(med.company)) {
                        cout << "Ошибка: название фирмы должно начинаться с заглавной буквы." << endl;
                    }
                    else {
                        catalog.back().company = med.company; // Обновляем название фирмы в каталоге
                        break;
                    }
                }
            }
            else if (fieldChoice == "3") {
                while (true) {
                    cout << "Введите новое название страны: ";
                    getline(cin, med.country);
                    med.country = trim(med.country);

                    if (!isValidCountryName(med.country)) {
                        cout << "Ошибка: название страны должно начинаться с заглавной буквы." << endl;
                    }
                    else {
                        catalog.back().country = med.country; // Обновляем название страны в каталоге
                        break;
                    }
                }
            }
            else if (fieldChoice == "4") {
                while (true) {
                    cout << "Введите новое назначение лекарства: ";
                    getline(cin, med.purpose);

                    if (find(validPurposes.begin(), validPurposes.end(), med.purpose) != validPurposes.end()) {
                        catalog.back().purpose = med.purpose; // Обновляем назначение в каталоге
                        break;
                    }
                    else {
                        cout << "Ошибка: недопустимое назначение. Пожалуйста, попробуйте снова." << endl;
                    }
                }
            }
            else if (fieldChoice == "5") {
                while (true) {
                    cout << "Требуется ли рецепт (1 - да, 0 - нет): ";
                    string input;
                    getline(cin, input);

                    if (input == "0" || input == "1") {
                        med.prescription = input[0] - '0';
                        catalog.back().prescription = med.prescription; // Обновляем информацию о рецепте в каталоге
                        break;
                    }
                    else {
                        cout << "Ошибка: введите 1 для 'да' или 0 для 'нет'." << endl;
                    }
                }
            }
            else if (fieldChoice == "6") {
                while (true) {
                    cout << "Введите новую форму выпуска: ";
                    getline(cin, med.form);
                    med.form = trim(med.form);

                    if (find(validForms.begin(), validForms.end(), med.form) != validForms.end()) {
                        catalog.back().form = med.form; // Обновляем форму выпуска в каталоге
                        break;
                    }
                    else {
                        cout << "Ошибка: недопустимая форма выпуска. Пожалуйста, выберите из предложенных вариантов." << endl;
                    }
                }
            }
        }
    }
}




void editMedicine(vector<Medicine>& catalog, const string& name) {
    for (auto& med : catalog) {
        if (med.name == name) {
            cout << "Редактирование лекарства \"" << name << "\":" << endl;

            // Редактирование названия лекарства
            while (true) {
                cout << "Текущее название: " << med.name << ". Новое название (или оставьте пустым для сохранения): ";
                string newName;
                cin.ignore();
                getline(cin, newName);
                newName = trim(newName);

                if (newName.empty()) {
                    break; // Если строка пустая, сохраняем текущее название
                }

                if (newName == med.name) {
                    break; // Если новое название совпадает с текущим, принимаем его без проверки
                }

                if (!isValidMedicineName(newName)) {
                    cout << "Ошибка: название лекарства должно начинаться с заглавной буквы, а остальные буквы должны быть строчными." << endl;
                }
                else {
                    cout << "Вы уверены, что хотите изменить название лекарства с \"" << med.name << "\" на \"" << newName << "\"? (1 - Да, 0 - Нет): ";
                    int confirm;
                    cin >> confirm;
                    if (confirm == 1) {
                        med.name = newName;  // Меняем название только после подтверждения
                    }
                    else {
                        cout << "Название лекарства не изменено." << endl;
                    }
                    break;
                }
            }

            // Редактирование названия фирмы
            while (true) {
                cout << "Текущая фирма: " << med.company << ". Новая фирма (или оставьте пустым): ";
                string newCompany;
                cin.ignore();
                getline(cin, newCompany);
                newCompany = trim(newCompany);

                if (newCompany.empty()) {
                    break; // Если строка пустая, сохраняем текущую фирму
                }

                if (!isValidMedicineName(newCompany)) {
                    cout << "Ошибка: название фирмы должно начинаться с заглавной буквы." << endl;
                }
                else {
                    med.company = newCompany;
                    break;
                }
            }

            // Редактирование названия страны
            while (true) {
                cout << "Текущая страна: " << med.country << ". Новая страна (или оставьте пустым): ";
                string newCountry;
                getline(cin, newCountry);
                newCountry = trim(newCountry);

                if (newCountry.empty()) {
                    break; // Если строка пустая, сохраняем текущую страну
                }

                if (!isValidCountryName(newCountry)) {
                    cout << "Ошибка: название страны должно начинаться с заглавной буквы." << endl;
                }
                else {
                    med.country = newCountry;
                    break;
                }
            }

            // Редактирование назначения лекарства
            vector<string> validPurposes = {
                "Болеутоляющие", "Противовоспалительные", "Антибиотики", "Противовирусные",
                "Противогрибковые", "Противоаллергические", "Антидепрессанты",
                "Антипсихотики", "Снотворные"
            };

            while (true) {
                cout << "Текущее назначение: " << med.purpose << ". Выберите новое назначение (введите номер):" << endl;
                for (size_t i = 0; i < validPurposes.size(); ++i) {
                    cout << i + 1 << " - " << validPurposes[i] << endl;
                }

                string input;
                cout << "Ваш выбор: ";
                cin >> input;

                // Проверка, является ли ввод числом
                if (input.find_first_not_of("0123456789") != string::npos) {
                    cout << "Ошибка: введите число." << endl;
                    cin.clear(); // Сброс флага ошибки
                    cin.ignore(); // Очистка буфера ввода
                    continue;
                }

                int choice = stoi(input);

                if (choice >= 1 && choice <= validPurposes.size()) {
                    med.purpose = validPurposes[choice - 1];
                    cout << "Назначение успешно изменено: " << med.purpose << endl;
                    break;
                }
                else {
                    cout << "Ошибка: недопустимый номер. Пожалуйста, выберите из предложенных вариантов." << endl;
                    cin.clear(); // Сброс флага ошибки
                    cin.ignore(); // Очистка буфера ввода
                }
            }

            // Редактирование информации о рецепте
            while (true) {
                cout << "Текущий рецепт (1 - да, 0 - нет): " << med.prescription << ". Новый рецепт: ";
                string input;
                cin >> input;

                if (input == "0" || input == "1") {
                    med.prescription = input[0] - '0';
                    break;
                }
                else {
                    cout << "Ошибка: введите 1 для 'да' или 0 для 'нет'." << endl;
                }
            }

            cin.ignore(); // Очистка буфера после ввода

            // Редактирование формы выпуска
            vector<string> validForms = {
                "Таблетки", "Капсулы", "Сироп", "Раствор", "Порошок", "Суппозитории", "Пластыри"
            };

            while (true) {
                cout << "Текущая форма: " << med.form << ". Выберите новую форму выпуска (введите номер):" << endl;
                for (size_t i = 0; i < validForms.size(); ++i) {
                    cout << i + 1 << " - " << validForms[i] << endl;
                }

                string input;
                cout << "Ваш выбор: ";
                cin >> input;

                // Проверка, является ли ввод числом
                if (input.find_first_not_of("0123456789") != string::npos) {
                    cout << "Ошибка: введите число." << endl;
                    cin.clear(); // Сброс флага ошибки
                    cin.ignore(); // Очистка буфера ввода
                    continue;
                }

                int choice = stoi(input);

                if (choice >= 1 && choice <= validForms.size()) {
                    med.form = validForms[choice - 1];
                    cout << "Форма выпуска успешно изменена: " << med.form << endl;
                    break;
                }
                else {
                    cout << "Ошибка: недопустимый номер. Пожалуйста, выберите из предложенных вариантов." << endl;
                    cin.clear(); // Сброс флага ошибки
                    cin.ignore(); // Очистка буфера ввода
                }
            }

            cout << "Лекарство успешно отредактировано." << endl;
            return;
        }
    }
    cout << "Лекарство с названием \"" << name << "\" не найдено." << endl;
}


void deleteMedicine(vector<Medicine>& catalog, const string& name) {
    auto it = find_if(catalog.begin(), catalog.end(), [&name](const Medicine& med) {
        return med.name == name;
        });

    if (it != catalog.end()) {
        cout << "Вы уверены, что хотите удалить лекарство \"" << name << "\"? (1 - Да, 0 - Нет): ";
        int confirm;
        cin >> confirm;

        if (confirm == 1) {
            catalog.erase(it); // Удаляем лекарство из вектора
            cout << "Лекарство \"" << name << "\" успешно удалено." << endl;
        }
        else {
            cout << "Удаление лекарства \"" << name << "\" отменено." << endl;
        }
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

    string line;
    while (getline(file, line)) {
        Medicine med;
        size_t pos = 0;

        // Чтение названия лекарства
        pos = line.find(';');
        if (pos == string::npos) {
            cerr << "Ошибка формата строки (нет разделителя ';'): " << line << endl;
            continue;
        }
        med.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение компании
        pos = line.find(';');
        if (pos == string::npos) {
            cerr << "Ошибка формата строки (нет разделителя ';'): " << line << endl;
            continue;
        }
        med.company = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение страны
        pos = line.find(';');
        if (pos == string::npos) {
            cerr << "Ошибка формата строки (нет разделителя ';'): " << line << endl;
            continue;
        }
        med.country = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение назначения
        pos = line.find(';');
        if (pos == string::npos) {
            cerr << "Ошибка формата строки (нет разделителя ';'): " << line << endl;
            continue;
        }
        med.purpose = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Чтение рецепта (требуется или нет)
        pos = line.find(';');
        if (pos == string::npos) {
            cerr << "Ошибка формата строки (нет разделителя ';'): " << line << endl;
            continue;
        }
        med.prescription = line.substr(0, pos); // Сохраняем как строку
        line.erase(0, pos + 1);

        // Чтение формы выпуска (последнее поле, не требуется разделитель)
        if (!line.empty()) {
            med.form = line;
        }
        else {
            cerr << "Ошибка формата строки (форма выпуска отсутствует): " << line << endl;
            continue;
        }

        // Добавление прочитанного лекарства в каталог
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
void findMedicineByName(const vector<Medicine>& catalog, const string& searchName) {
    string trimmedSearchName = trim(searchName);
    vector<Medicine> foundMedicines; // Вектор для хранения найденных лекарств

    for (const auto& medicine : catalog) {
        if (medicine.name.find(trimmedSearchName) != string::npos) { // Поиск по частичному совпадению
            foundMedicines.push_back(medicine); // Добавляем найденное лекарство в вектор
        }
    }

    // Печатаем результаты
    if (!foundMedicines.empty()) {
        cout << "Найденные лекарства:" << endl;
        cout << "-------------------" << endl;
        printMedicineTable(foundMedicines); // Выводим найденные лекарства в виде таблицы
    }
    else {
        cout << "Лекарство с названием \"" << trimmedSearchName << "\" не найдено." << endl;
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

string toLowerCase(const string& str) {
    string result = str;
    locale loc("ru_RU.UTF-8");  // Устанавливаем локаль для работы с русскими буквами
    for (auto& ch : result) {
        ch = tolower(ch, loc);
    }
    return result;
}

void findPainkillersNoPrescription(const vector<Medicine>& catalog) {
    vector<Medicine> filteredCatalog;

    // Фильтрация лекарств
    for (const auto& med : catalog) {
        if (med.purpose == "Болеутоляющие" && (med.prescription == "Нет" || med.prescription == "нет")) {
            filteredCatalog.push_back(med);
        }
    }

    // Проверка, есть ли лекарства после фильтрации
    if (filteredCatalog.empty()) {
        cout << "Нет болеутоляющих без рецепта." << endl;
        return;
    }

    // Вывод отфильтрованных лекарств с использованием существующей функции
    printMedicineTable(filteredCatalog);
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
    else {
        cout << "Ошибка: поле \"" << field << "\" не существует." << endl;
        return;  // Выход из функции, если поле не существует
    }

    cout << "Данные отсортированы по полю \"" << field << "\"." << endl;
    printMedicineTable(catalog);
}

// Вывод информации о программе
void aboutProgram() {
    cout << "Аптечный справочник v1.0\n";
    cout << "Последние изменения: September 2024\n";
    cout << "Автор: Name Surname\n";
    cout << "Контакты: ...\n";
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
        // Преобразуем строку из UTF-8 в UTF-16
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, line.c_str(), -1, NULL, 0);
        wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, line.c_str(), -1, &wstrTo[0], size_needed);

        // Выводим строку в консоль
        wcout << wstrTo << endl;
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


void showSortFieldMenu(vector<Medicine>& catalog) {
    int choice;
    cout << "Выберите поле для сортировки:\n";
    cout << "1. Название (name)\n";
    cout << "2. Фирма (company)\n";
    cout << "3. Страна (country)\n";
    cout << "4. Назначение (purpose)\n";
    cout << "5. Форма (form)\n";
    cout << "0. Выход\n";

    while (true) {
        cout << "Ваш выбор: ";
        cin >> choice;

        // Check for invalid input
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(); // Discard invalid input
            cout << "Пожалуйста, введите число." << endl;
            cin.ignore();
            continue; // Restart the loop
        }

        // Check the range of choice
        if (choice < 0 || choice > 5) {
            cout << "Неверный выбор. Попробуйте снова." << endl;
            continue; // Restart the loop
        }

        string field;

        switch (choice) {
        case 1:
            field = "name";
            break;
        case 2:
            field = "company";
            break;
        case 3:
            field = "country";
            break;
        case 4:
            field = "purpose";
            break;
        case 5:
            field = "form";
            break;
        case 0:
            return; // Выход из меню
        }

        sortCatalog(catalog, field); // Вызываем функцию сортировки
        break; // Exit the loop after valid input
    }
}

bool dataSaved = false; // Flag to track if data has been saved

// Function to save data (placeholder for your actual save logic)
void saveData() {
    // Your save logic goes here
    dataSaved = true; // Mark data as saved
    cout << "Данные сохранены." << endl;
}

// Function to check if data is saved before exiting
bool confirmExit() {
    char choice;
    cout << "Вы не сохранили данные. Вы уверены, что хотите выйти? (y/n): ";
    cin >> choice;

    // Validate the choice
    while (choice != 'y' && choice != 'n') {
        cout << "Неверный выбор. Пожалуйста, введите 'y' или 'n': ";
        cin >> choice;
    }

    return (choice == 'y'); // Return true if user wants to exit
}

void displayMedicineInfo(const vector<Medicine>& catalog, const string& name) {
    // Определение максимальной длины для каждого столбца на основе заголовков
    size_t max_name_length = 20;        // Максимальная длина для названия лекарства
    size_t max_company_length = 20;     // Максимальная длина для фирмы
    size_t max_country_length = 15;     // Максимальная длина для страны
    size_t max_purpose_length = 25;     // Максимальная длина для назначения
    size_t max_form_length = 12;        // Максимальная длина для формы выпуска

    for (const auto& medicine : catalog) {
        if (medicine.name == name) {
            // Печать заголовка таблицы
            cout << setfill(' ') << setw(2) << left << " " << " | "
                << setw(max_name_length) << left << "Наименование" << " | "
                << setw(max_company_length) << left << "Фирма" << " | "
                << setw(max_country_length) << left << "Страна" << " | "
                << setw(max_purpose_length) << left << "Назначение" << " | "
                << setw(max_form_length) << left << "Форма" << endl;

            // Печать разделителя
            cout << setfill('-') << setw(2 + max_name_length + max_company_length +
                max_country_length + max_purpose_length + max_form_length) << "-" << endl;

            // Печать данных о лекарстве
            cout << setfill(' ') << setw(2) << left << " " << " | "
                << setw(max_name_length) << left << medicine.name << " | "
                << setw(max_company_length) << left << medicine.company << " | "
                << setw(max_country_length) << left << medicine.country << " | "
                << setw(max_purpose_length) << left << medicine.purpose << " | "
                << setw(max_form_length) << left << medicine.form << endl;

            cout << setfill(' ') << endl; // Дополнительная пустая строка в конце
            return;
        }
    }
    cout << "Лекарство с названием \"" << name << "\" не найдено." << endl;
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
        cout << "7. Выдать справочную информацию по наименованию лекарства\n"; // Новый пункт
        cout << "8. Сформировать перечень лекарств одной фирмы\n";
        cout << "9. Найти болеутоляющие средства без рецепта\n";
        cout << "10. Сортировка лекарств\n";
        cout << "11. Сохранить в файл\n";
        cout << "12. О программе\n";
        cout << "13. Руководство пользователя\n";
        cout << "14. Выход\n"; // Изменил номер пункта "Выход"
        cout << "Выберите действие: ";

        int choice;
        while (!(cin >> choice)) {
            cout << "Ошибка: введите число." << endl;
            cin.clear(); // Очистка флага ошибки
            cin.ignore(10000, '\n'); // Очистка буфера ввода
            cout << "Выберите действие: ";
        }

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

            // Проверяем, было ли что-то введено
            if (name.empty()) {
                cout << "Название не было введено!" << endl;
            }
            else {
                findMedicineByName(catalog, name);
            }
            break;
        }
        case 7: { // Новый пункт
            string name;
            cout << "Введите название лекарства для справочной информации: ";
            cin >> name;

            // Проверяем, было ли что-то введено
            if (name.empty()) {
                cout << "Название не было введено!" << endl;
            }
            else {
                displayMedicineInfo(catalog, name); // Вызываем новую функцию
            }
            break;
        }
        case 8: {
            string company;
            cout << "Введите название фирмы: ";
            cin >> company;
            listMedicinesByCompany(catalog, company);
            break;
        }
        case 9:
            findPainkillersNoPrescription(catalog);
            break;
        case 10: {
            showSortFieldMenu(catalog); // Вызываем меню сортировки
            break;
        }
        case 11:
            saveToNewFile(catalog);
            break;
        case 12:
            aboutProgram();
            break;
        case 13:
            loadUserGuide("C:\\Users\\PC\\Desktop\\Учеба\\Курсовой\\Делаю\\PharmacyDirectory\\PharmacyDirectory\\Руководство пользователя.txt");
            break;
        case 14: { // Изменил номер пункта "Выход"
            if (!dataSaved) {
                if (confirmExit()) {
                    cout << "Выход из программы..." << endl;
                    return; // Завершение программы
                }
            }
            else {
                cout << "Выход из программы..." << endl;
                return; // Завершение программы
            }
            break;
        }
        default:
            cout << "Неверный ввод, попробуйте снова." << endl;
        }
    }
}



int main() {


    setlocale(LC_ALL, "Russian_Russia.1251");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "Вариант 27" << endl;
    cout << "27. Написать программу «Аптечный справочник», позволяющий найти средство, например от"
        "головной боли. В справочнике должна содержаться информация : название лекарства, фирма и страна изготовитель,"
        "назначение(жаропонижающее, болеутоляющее и т.д.), отпускается по рецепту врача или нет, форма выпуска"
        "(таблетки, капсулы, раствор и т.д.). Выдать справочную информацию по наименованию лекарства. Сформировать перечень"
        "лекарств одной фирмы производителя. Найти все отпускаемые без рецепта врача болеутоляющие средства.";
    cout << " " << endl;

    vector<Medicine> catalog;
    mainMenu(catalog);
    return 0;
}