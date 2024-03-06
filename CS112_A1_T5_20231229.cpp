/*
 Program: Game 3 purpose: this is a 2 game player
 This game's purpose it that each player removes a pile of non-zero square coins and the winner
 is the player who removes tha last coin.
 Author: Maria Atef Edward
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


// allow comuter to generate the random number itself
int get_Random_Number(int min, int max) {
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    int randomNumber = min + static_cast<int>((max - min + 1) * (rand() * fraction));
    return randomNumber;
}
// uses the get_random_number to genreate a random number also it makes sure that the inout is not 0 & not sqaured number
int random_not_square(int min, int max) {
    while (true) {
        int num = get_Random_Number(min, max);
        int sqrtNum = static_cast<int>(sqrt(num));
        if (sqrtNum * sqrtNum != num)
            return num;
    }
} 
// gets the valid moves for the user
vector<int> get_valid_moves(int pile) {
    vector<int> valid_moves;
    for (int i = 1; i * i <= pile; ++i)
        valid_moves.push_back(i * i);
    return valid_moves;
}
// allow the user to enter a valid non 0 and non sqaure number between 1 and 1000
int manual() {
    while (true) {
        int choice;
        cout << "Please enter a number between 1 and 1000: ";
        cin >> choice;
        // make sure that the input is not an invalid number like 0 or sqaured number or negative numbers
        if (choice <= 0 || (static_cast<int>(sqrt(choice)) * static_cast<int>(sqrt(choice)) == choice) || choice > 1000 ||cin.fail()) {
            cout << "Invalid number, please try again" << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return choice;
        }
    }
}

int player1(int pile) {
    vector<int> valid_moves = get_valid_moves(pile);
    int move;
    while (true) {
        cout << "Player 1, remove a number of coins: ";
        cin >> move;
        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Check if the move is valid
        if (find(valid_moves.begin(), valid_moves.end(), move) == valid_moves.end() || move > pile || cin.fail()) {
            cout << "Invalid input. Please pick a non-zero, square number of coins within the valid range" << "\n";
        } else {
            return move;
        }
    }   
}

int player2(int pile) {
    vector<int> valid_moves = get_valid_moves(pile);
    int move;
    while (true) {
        cout << "Player 2, remove a number of coins: ";
        cin >> move;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (find(valid_moves.begin(), valid_moves.end(), move) == valid_moves.end() || move > pile || cin.fail()) {
            cout << "Invalid input. Please pick a non-zero, square number of coins within the valid range" << "\n";
        } else {
            return move;
        }
    }   
}

int main() {
    srand(time(nullptr));
    
    while (true) {
        int pile = 0;

        cout << "Subtract a square game" << "\n";
        cout << "A generate a random number, B to choose a number between 1 and 1000: ";
        char choice2;
        cin >> choice2;
        // used to allow the user to input both upper and lower case letters (A or a or B or b)
        choice2 = tolower(choice2);

        if (choice2 == 'a') {
            int pileSize = random_not_square(100, 500);
            pile = pileSize;
            cout << "Initial pile size: " << pileSize << "\n";
        } else if (choice2 == 'b') {
            int pileSize = manual();
            pile = pileSize;
            cout << "Initial pile size: " << pileSize << "\n";
        } else {
            cout << "Invalid choice. Please choose 'A' or 'B'." << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; 
        }

        while (pile > 0) {
            cout << "Player 1's turn" << "\n";
            int coins_removed_player1 = player1(pile);
            pile -= coins_removed_player1;
            cout << "Pile size after Player 1's turn: " << pile << "\n";
            if (pile <= 0) {
                cout << "Player 1 wins!" << "\n";
                break;
            }

            cout << "Player 2's turn" << "\n";
            int coins_removed_player2 = player2(pile);
            pile -= coins_removed_player2;
            cout << "Pile size after Player 2's turn: " << pile << "\n";
            if (pile <= 0) {
                cout << "Player 2 wins!" << "\n";
                break;
            }
        }
         char play_again;
        while (true) {
            cout << "Do you want to play again? (Y/N): ";
            cin >> play_again;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (play_again == 'y') {
                pile = 0;
                break;
            } else if (play_again == 'n') {
                cout << "Game Over" << "\n";
                return 0; 
            } else {
                cout << "Invalid input. Please enter 'Y' or 'N'" << "\n";
            }
        }
    }

    return 0;
}

    
