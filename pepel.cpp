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
using std::find;

class Wheel {
    public:
        vector<int> points;
        Wheel() {
            points = {0, 50, 100, 111, 150, 200, 250, 300, 350, 400, 450, 500, 600, 650, 700, 750, 777, 800, 850, 950, 1000};
        }
    
        int spin() {
            return points[rand() % points.size()];
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
        score *= 2;
    }

private:
    string name;
    int score;
};

class Game {
public:
    Game() {
        words = {"программирование", "конста", "игра", "поле", "чудеса"};
        word = chooseWord();
        CurrentPlayerIndex = 0;
    }

    void play() {
        cout << "Добро пожаловать в игру 'Поле чудес'!" << endl;

        while (true) {
            Player& currentPlayer = getCurrentPlayer();
            cout << "Текущий игрок: " << currentPlayer.getName() << endl;
            displayWord();

            int spinResult = wheel.spin();
            cout << "Вы крутите колесо и выпадает: " << spinResult << endl;

            if (spinResult == 777 || spinResult == 111) {
                sectorPrize();
            } else if (spinResult > 0) {
                cout << "Назовите букву: ";
                enterLetter();

                while (checkLetter()) {
                    cout << "Данная буква уже была загаданна, введите другую букву: ";
                    enterLetter();
                }

                if (guessLetter()) {
                    int count = countSign();
                    currentPlayer.addScore(spinResult * count);
                    cout << "Ваша буква встретилась " << count << " раз," << " вы получаете " << spinResult * count << " очков!" << '\n';
                    displayWord();
                    if (isWordGuessed()) {
                        win();
                        return;
                    }
                    fullWord();
                    continue;
                } else {
                    changePlayer();
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
    char letter;
    string word;
    vector<char> letters = {};
    string fullGuess;
    int CurrentPlayerIndex;

    Player& getCurrentPlayer() {
        return players[CurrentPlayerIndex];
    }

    void endGame() {
        cout << "Игра окончена! Результаты: " << endl;
        for (const auto& player : players) {
            cout << player.getName() << " набрал " << player.getScore() << " очков" << endl;
        }
    }

    void changePlayer() {
        CurrentPlayerIndex = (CurrentPlayerIndex + 1) % players.size();
    }

    void enterLetter() {
        char a;
        cin >> a;
        letter = a;
    }

    bool checkLetter() {
        return find(letters.begin(), letters.end(), letter) != letters.end();
    }

    void sectorPrize() {
        cout << "Сектор приз на барабане! Вы выиграли автомобиль!" << '\n';
    }

    void win() {
        cout << "Поздравляем! Вы угадали слово!" << '\n';
        endGame();
    }

    void fullWord() {
        string decision;
        cout << "Хотите назвать слово целиком? (да/нет): ";
        cin >> decision;
        if (decision == "да") {
            cout << "Введите слово: ";
            cin >> fullGuess;
            if (guessWord(fullGuess)) {
                win();
            } else {
                cout << "Неверно!" << endl;
                changePlayer();
            }
        } else {
            changePlayer();
        }
    }

    string chooseWord() {
        return words[rand() % words.size()];
    }

    void displayWord() {
        for (char letter : word) {
            if (find(letters.begin(), letters.end(), letter) != letters.end()) {
                cout << letter;
            } else {
                cout << '_';
            }
        }
        cout << endl; 
    }

    bool guessLetter() {
        letters.push_back(letter);
        if (find(word.begin(), word.end(), letter) != word.end()) {
            cout << "Вы угадали букву!" << endl;
            return true;
        } else {
            cout << "Вы не угадали букву :(" << '\n';
            return false;
        }
    }

    int countSign() {
        return count(word.begin(), word.end(), letter);
    }

    bool guessWord(const string& guess) {
        return guess == word;
    }

    bool isWordGuessed() {
        for (char letter : word) {
            if (find(letters.begin(), letters.end(), letter) == letters.end()) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Game game;
    game.addPlayer(Player("Игрок 1"));
    game.addPlayer(Player("Игрок 2"));
    game.play();
    return 0;
}