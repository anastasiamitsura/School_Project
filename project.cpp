#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

class Wheel {
public:
    Wheel() {
    }

    int spin() {
        // функция возвращающая рандомное число
        return 0;
    }
};

class Player {
public:
    Player(string name) : name(name), score(0) {}

    string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }

    void addScore(int points) {
        score += points;
    }

    void doubleScore() { 
        // функция удваивания очков
    }

private:
    string name;
    int score;
};

class Game {
public:
    Game() {
        words = {"программирование", "конста", "игра", "поле", "чудес"}; // словарь слов
        word = chooseWord();
    }

    void play() {
        cout << "Добро пожаловать в тестирование игры 'Выживи или умри'!" << endl;

        while (true) {
            Player& currentPlayer = getCurrentPlayer();
            cout << "Текущий игрок: " << currentPlayer.getName() << endl;
            displayWord();

            int spinResult = wheel.spin();
            cout << "Вы крутите колесо и выпадает: " << spinResult << endl;

            if (spinResult == 777 || spinResult == 111) {
                sectorPrize();
            } else if (spinResult > 0) {
                char letter;
                cout << "Назовите букву: ";
                cin >> letter;

                while(checkLetter(letter)) {
                    cout << "Данная буква уже была загаданна, введите другую букву";
                    cin >> letter;
                }

                if (guessLetter(letter)) {
                    int count = countSign(letter);
                    currentPlayer.addScore(spinResult * count);
                    displayWord();
                    fullWord();
                    chengePlayer();
                    continue;
                } else {
                    displayWord();
                    chengePlayer();
                    continue;
                }
            }
        }
    }

    void addPlayer(const Player& player) {
        players.push_back(player);
    }

private:
    vector<string> words;
    vector<Player> players;
    Wheel wheel;
    string word;
    vector<char> letters;
    string fullGuess;

    Player& getCurrentPlayer(){
        // возвращает текущего игрока
    }

    void endGame(){
        // выводит результаты игры
    }

    void chengePlayer(){
        // переключение игрока
    }

    bool checkLetter(char letter) {
        // функция, проверяет была ли данная буква уже заганада или нет
        return true;
    }

    void sectorPrize() {
        // функция сектор приз
    }

    void win() {
        // функция победы
        endGame();
    }

    void lose() {
        // функция проигрыша
        endGame();
    }

    void fullWord() {
        // функция угадать всё слово
        cout << "Хотите назвать слово целиком? (да/нет): ";
    }

    string chooseWord() {
        // функция, выберающая свово из словаря
        return "";
    }

    void displayWord() {
        // функция, выводящая слова в виде маски с угаданными буквами
    }

    bool guessLetter(char letter) {
        // функция возвращаюсая, была ли угадана буква
        return true;
    }

    int countSign(char letter) {
        // количество угаданных букв за раз
        return 0;
    }

    bool guessWord(const string& guess) {
        // Функция проверяющая было ли слово угаданно
        return true;
    }
};

int main() {
    srand(static_cast<unsigned int>(time (0)));
    Game game;
    game.addPlayer(Player("Игрок 1"));
    game.addPlayer(Player("Игрок 2"));
    game.play();
    return 0;
}