#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <windows.h>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::find;


// Класс самого колеса фортуны
class Wheel {
public:
    vector<int> points = {50, 100, 111, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 750, 777, 800, 850, 900, 950};

    // функция "прокрутки" колеса
    int spin() {
        return points[rand() % points.size()];
    }
};

// Класс игрока
class Player {
public:
    string name;
    int score = 0;
    Player(string n) : name(n) {}

    void addScore(int points) {
        score += points;
    }

    string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }



    void doubleScore() {
        score *= 2;
    }
};

// Класс игры
class Game {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Словарь игры
    vector<string> words = {"yakubovich", "konsta", "project", "programming", "wheel", "development", "excellent", "lyceum", "hse", "github", "deadline", "creative",
        "game", "polechudes", "holidays", "algorithm", "player", "prize", "sector", "point", "letters", "word" };
    // Словарь игроков
    vector<Player> players;
    // Класс колеса
    Wheel wheel;
    // Слово в игре
    string word;
    // Буквы, которые уже были загаданы игроком
    vector<char> guessedLetters;
    // Индекс игрока в игре
    int currentPlayerIndex = 0;

    // Функция для преобразования больших букв в маленькие
    char toLowerBuckva(char c) {
        return tolower(c);
    }

public:
    // инициализация игры
    Game() {
    }

    // Добавление игрока
    void addPlayer(Player p) {
        players.push_back(p);
    }

    // Сектор приз
    void sectorPriz(Player &p){
        SetConsoleTextAttribute(hConsole, 30); // настройка цвета текста
        cout << "Сектор приз! Вы выиграли автомобиль! Ваши очки удваиваются!\n";
        p.doubleScore();
    }

    // Вывод слова
    void displayWord() {
        for (char c : word) {
            if (find(guessedLetters.begin(), guessedLetters.end(), toLowerBuckva(c)) != guessedLetters.end()) {
                SetConsoleTextAttribute(hConsole, 10); // настройка цвета текста
                cout << c << " ";
            } else {
                SetConsoleTextAttribute(hConsole, 7); // настройка цвета текста
                cout << "_ ";
            }
        }
        cout << endl;
    }

    // Цикл всей игры
    void play(){
        SetConsoleTextAttribute(hConsole, 11); // настройка цвета текста
        cout << "Приветствуем в игре поле чудес!\n";
        cout << "Игра состоит из 3х туров, выигрывает тот игрок, который наберёт больше очков!\n";
        for(int i = 0; i < 3; ++i){
            SetConsoleTextAttribute(hConsole, 11); // настройка цвета текста
            cout << "Начало " << i + 1 << " тура!\n";
            word = words[rand() % words.size()];
            // Запуск тура
            playTur();
        }
        showResultsGame();
    }

    // Цикл игры тура
    void playTur() {
        while (true) {
            Player& p = players[currentPlayerIndex];
            SetConsoleTextAttribute(hConsole, 11); // настройка цвета текста
            cout << "\nИгрок: " << p.name << " (Очки: " << p.score << ")\n";
            displayWord();

            int spin = wheel.spin();
            SetConsoleTextAttribute(hConsole, 7); // настройка цвета текста
            cout << "Выпал сектор: " << spin << endl;

            if (spin == 777 || spin == 111) {
                sectorPriz(p);
                continue;
            }

            playerPlay(p, spin);
            bool guessed = true;
            for (char c : word) {
                if (find(guessedLetters.begin(), guessedLetters.end(), toLowerBuckva(c)) == guessedLetters.end()) {
                    guessed = false;
                    break;
                }
            }

            if (guessed) {
                SetConsoleTextAttribute(hConsole, 31); // настройка цвета текста
                cout << "\nПоздравлем! Слово было: " << word << endl;
                p.addScore(2000);
                showResultsTur();
                currentPlayerIndex = 0;
                guessedLetters = {};
                break;
            }
        }
        
    }

    // Цикл игры игрока
    void playerPlay(Player &p, int spin){
        while (true) {
            SetConsoleTextAttribute(hConsole, 7); // настройка цвета текста
            cout << "Введите букву: ";
            char letter;
            cin >> letter;

            letter = toLowerBuckva(letter);

            if (!isalpha(letter)) {
                SetConsoleTextAttribute(hConsole, 12); // настройка цвета текста
                cout << "Игра идёт только на английском языке!\n";
                continue;
            }

            if (find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
                SetConsoleTextAttribute(hConsole, 12); // настройка цвета текста
                cout << "Буква уже была введена!\n";
                continue;
            }

            guessedLetters.push_back(letter);

            if (word.find(letter) != string::npos) {
                int count = 0;
                for (char c : word) if (toLowerBuckva(c) == letter) count++;

                int points = spin * count;
                p.addScore(points);
                SetConsoleTextAttribute(hConsole, 2); // настройка цвета текста
                cout << "Найдено " << count << " '" << letter << "' букв! +" << points << " очков\n";
                displayWord();

                bool guessed = true;
                for (char c : word) {
                    if (find(guessedLetters.begin(), guessedLetters.end(), toLowerBuckva(c)) == guessedLetters.end()) {
                        guessed = false;
                        break;
                    }
                }
    
                if (guessed) {
                    break;
                }

            } else {
                SetConsoleTextAttribute(hConsole, 7); // настройка цвета текста
                cout << "Буква не найдена!\n";
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                break;
            }
        }
    }
    
    // Отображение результатов тура
    void showResultsTur() {
        SetConsoleTextAttribute(hConsole, 11); // настройка цвета текста
        cout << "\nРезультаты тура:\n";
        for (auto& p : players) {
            cout << p.name << ": " << p.score << " очков\n";
        }
    }

    // Отображение результатов игры
    void showResultsGame() {
        SetConsoleTextAttribute(hConsole, 11); // настройка цвета текста
        cout << "\nРезультаты игры:\n";
        for (auto& p : players) {
            cout << p.name << ": " << p.score << " очков\n";
        }
    }
};

int main() {
    // Настройка нормального рандомайзера
    srand(time(0));

    // Инициализация игры
    Game game;
    // Добавление игроков
    game.addPlayer(Player("Подопытный 1"));
    game.addPlayer(Player("Испытуемый 2"));

    // Запуск игры
    game.play();

    return 0;
}