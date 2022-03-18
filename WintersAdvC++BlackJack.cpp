/* Jackson Trainer 12/15/2021 jttrainer@dmacc.edu
 * Aaron Winters 12/15/2021 jttrainer@dmacc.edu
 * Bailey Reyes 12/15/2021 jttrainer@dmacc.edu
 *
 * This application has been created to allow a user
 * to play blackjack against the computer. The user
 * is able to place a bet, hit, stand, and continue
 * playing until they are done. The program tracks
 * win/loss for both player and dealer. This is saved
 * to a file and then displayed at the end of play.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

//Struct Creation for use in creating a game deck
struct Deck {
    string face;
    int value;
    string suite;
};

//Function Prototype
void DeckSetup(vector<Deck>& gameDeck);
void RoundEvaluation(int playerRoundSum, int dealerRoundSum, int& playerRoundsWon, int& dealerRoundsWon, int& bank, int betAmount);
int DealerPlay(int tableValue);
void DisplayRules();
void HitOrStand(int& pRoundsWon, int& dRoundsWon, bool dealerDone, bool playerDone, vector<Deck>& gameDeck, int& bank, int betAmount);
void DealerWin(int& dw, int pw);
void PlayerWin(int& pw, int dw);
void DisplayWinner();
int Bank(bool playerWon, bool dealerWon, int bankAmount, int betAmount);

int main()
{
    //Variable Declaration
    vector<Deck> gameDeck;
    bool playerDone = false;
    bool dealerDone = false;
    bool newRound = true;
    int input;
    int playerTotalRoundsWon = 0;
    int dealerTotalRoundsWon = 0;
    int playerBank = 500;
    int betAmount = 0;
    int numRounds = 1;

    //Randomize Function
    //Information on how to create found at https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector post by user703016 and post by Mehmet Fide.
    auto seedForRandomizer = chrono::system_clock::now().time_since_epoch().count();
    auto randomizer = default_random_engine{ seedForRandomizer };

    //Calls function that displays the rules for the player
    DisplayRules();
    cout << "Let the games begin!" << endl << endl;

    //Continuous play until user indicates they no longer want to play.
    while (newRound == true) {
        //Call fuction to setup the deck.
        DeckSetup(gameDeck);
        //Shufffels the deck vector.
        shuffle(begin(gameDeck), end(gameDeck), randomizer);

        cout << "Round: " << numRounds << endl << endl;
        //User prompt to get bet amount.

        cout << "Enter your bet amount: $";
        cin >> betAmount;
        //Validate User Input and prompt for appropriate value.
        while (cin.fail() || betAmount > playerBank) {
            cout << "The character(s) you entered is not valid. Please enter a number less than or equal to :" << playerBank << endl;
            cout << "Enter your bet amount: $";

            //Clear cin buffer
            cin.clear();

            //Discard bad input
            cin.ignore(255, '\n');

            cin >> betAmount;
            cout << endl;
        }

        //Calss function with the game play.
        HitOrStand(playerTotalRoundsWon, dealerTotalRoundsWon, dealerDone, playerDone, gameDeck, playerBank, betAmount);

        cout << "Remaining Bank: $" << playerBank << endl;

        //Prompt user to play again.
        cout << "Play again? (1 - Yes, 2 - No): ";
        cin >> input;

        //Validate User Input and prompt for appropriate value.
        while (cin.fail() || input < 1 || input > 2) {
            cout << "The character(s) you entered is not valid. Please enter 1 for yes or 2 for no." << endl;
            cout << "Play again? (1 - Yes, 2 - No): ";

            //Clear cin buffer
            cin.clear();

            //Discard bad input
            cin.ignore(255, '\n');

            cin >> input;
            cout << endl;
        }

        cout << endl;
        //Set trigger for next round based on user input.
        if (input == 1) {
            newRound = true;
            //Increments the number of rounds for display
            ++numRounds;
        }
        else if (input == 2) {
            newRound = false;
        }
    }

    //Calls function to display the winner.
    DisplayWinner();

    return 0;
}

//Jackson Functions
//Deck creation
void DeckSetup(vector<Deck>& gameDeck) {
    const int SIZE_SUITE = 13;
    //Deck Setup
    //Clubs
    for (int i = 0; i < SIZE_SUITE; ++i) {
        Deck card;
        if (i == 0) {
            card.face = "Ace";
            card.value = 1;
            card.suite = "Clubs";
        }
        else if (i == 10) {
            card.face = "Jack";
            card.value = 10;
            card.suite = "Clubs";
        }
        else if (i == 11) {
            card.face = "Queen";
            card.value = 10;
            card.suite = "Clubs";
        }
        else if (i == 12) {
            card.face = "King";
            card.value = 10;
            card.suite = "Clubs";
        }
        else {
            card.face = to_string(i + 1);
            card.value = i + 1;
            card.suite = "Clubs";
        }

        //Adds new card to game deck.
        gameDeck.push_back(card);
    }

    //Diamond
    for (int i = 0; i < SIZE_SUITE; ++i) {
        Deck card;
        if (i == 0) {
            card.face = "Ace";
            card.value = 1;
            card.suite = "Diamond";
        }
        else if (i == 10) {
            card.face = "Jack";
            card.value = 10;
            card.suite = "Diamond";
        }
        else if (i == 11) {
            card.face = "Queen";
            card.value = 10;
            card.suite = "Diamond";
        }
        else if (i == 12) {
            card.face = "King";
            card.value = 10;
            card.suite = "Diamond";
        }
        else {
            card.face = to_string(i + 1);
            card.value = i + 1;
            card.suite = "Diamond";
        }

        //Adds new card to game deck.
        gameDeck.push_back(card);
    }

    //Hearts
    for (int i = 0; i < SIZE_SUITE; ++i) {
        Deck card;
        if (i == 0) {
            card.face = "Ace";
            card.value = 1;
            card.suite = "Hearts";
        }
        else if (i == 10) {
            card.face = "Jack";
            card.value = 10;
            card.suite = "Hearts";
        }
        else if (i == 11) {
            card.face = "Queen";
            card.value = 10;
            card.suite = "Hearts";
        }
        else if (i == 12) {
            card.face = "King";
            card.value = 10;
            card.suite = "Hearts";
        }
        else {
            card.face = to_string(i + 1);
            card.value = i + 1;
            card.suite = "Hearts";
        }

        //Adds new card to game deck.
        gameDeck.push_back(card);
    }

    //Spades
    for (int i = 0; i < SIZE_SUITE; ++i) {
        Deck card;
        if (i == 0) {
            card.face = "Ace";
            card.value = 1;
            card.suite = "Spades";
        }
        else if (i == 10) {
            card.face = "Jack";
            card.value = 10;
            card.suite = "Spades";
        }
        else if (i == 11) {
            card.face = "Queen";
            card.value = 10;
            card.suite = "Spades";
        }
        else if (i == 12) {
            card.face = "King";
            card.value = 10;
            card.suite = "Spades";
        }
        else {
            card.face = to_string(i + 1);
            card.value = i + 1;
            card.suite = "Spades";
        }

        //Adds new card to game deck.
        gameDeck.push_back(card);
    }
}

//Round Evaluation Function
void RoundEvaluation(int playerRoundSum, int dealerRoundSum, int& playerRoundsWon, int& dealerRoundsWon, int& bank, int betAmount) {
    //Local variable decleartion
    //Set contstant for bust threashold to avoid magic numbers
    const int BUST = 21;
    bool playerWon;
    bool dealerWon;

    cout << endl;

    cout << "Dealers score: " << dealerRoundSum << endl;
    cout << "Players score: " << playerRoundSum << endl;

    //Evaluation logic for who the winner is.
    //Evaluates a tie
    if (playerRoundSum == dealerRoundSum) {
        cout << "Tie no winner :(" << endl;

        //Evaluates dealer win if player socre is over 21
    }
    else if (playerRoundSum > BUST) {
        DealerWin(dealerRoundsWon, playerRoundsWon);
        dealerWon = true;
        cout << "Dealer Wins :(" << endl;
        //Evaluates player win if player socre is over 21
    }
    else if (dealerRoundSum > BUST) {
        PlayerWin(playerRoundsWon, dealerRoundsWon);
        cout << "Player Wins!! :)" << endl;
        playerWon = true;

        //Evaluates player win if dealer socre is more than the players
    }
    else if (playerRoundSum < dealerRoundSum) {
        DealerWin(dealerRoundsWon, playerRoundsWon);
        dealerWon = true;
        cout << "Dealer Wins :(" << endl;

        //Evaluates player win if player socre is more than the dealers
    }
    else if (playerRoundSum > dealerRoundSum) {
        PlayerWin(playerRoundsWon, dealerRoundsWon);
        cout << "Player Wins!! :)" << endl;
        playerWon = true;
    }

    //Updates bank to the new value.
    bank = Bank(playerWon, dealerWon, bank, betAmount);
}

//Dealer Play
int DealerPlay(int tableValue) {
    //Set contstant for dealer stand threashold to avoid magic numbers
    const int DEALER_STAND = 17;
    //Logic for if the dealer will hit or stand.
    if (tableValue < DEALER_STAND) {
        return 1;
    }
    else {
        return 2;
    }
}

//Aarons Functions
//Rule displayed to screen
void DisplayRules() {
    cout << "Object of the Game:" << endl;
    cout << "Each participant attempts to beat the dealer by getting a count as close to 21 as possible, without going over 21." << endl;
    cout << endl;
    cout << endl;
    cout << "Card Values/Scoring:" << endl;
    cout << "It is up to each individual player if an ace is worth 1 or 11. Face cards are 10 and any other card is its pip value." << endl;
    cout << endl;
    cout << endl;
    cout << "The Play:" << endl;
    cout << "The player goes first and must decide whether to 'Stand' (not ask for another card) or 'Hit'" << endl;
    cout << "(ask for another card in an attempt to get closer to a count of 21, or even hit 21 exactly)." << endl;
    cout << "Thus, a player may stand on the two cards originally dealt to them, or they may ask the dealer for additional" << endl;
    cout << "cards, one at a time, until deciding to stand on the total(if it is 21 or under), or goes 'bust'" << endl;
    cout << "(if it is over 21).In the latter case, the player losesand the dealer collects the bet wagered." << endl;
    cout << endl;
    cout << endl;
    cout << "The Dealers Play:" << endl;
    cout << "When the dealer has served every player, the dealers face-down card is turned up. If the total is 17 or more," << endl;
    cout << "it must stand.If the total is 16 or under, they must take a card.The dealer must continue to take cards" << endl;
    cout << "until the total is 17 or more, at which point the dealer must stand." << endl << endl;

}

//Fuction for playing the game
void HitOrStand(int& pRoundsWon, int& dRoundsWon, bool dealerDone, bool playerDone, vector<Deck>& gameDeck, int& bank, int betAmount) {

    //locatl variable decleration
    int pHitStand = 0;
    int pHandSum = 0;
    int dHitStand = 0;
    int dHandSum = 0;
    int currentCardValue = 0;

    //Flow for player and dealer hit/stand until both have stood.
    while (dealerDone == false || playerDone == false)
    {
        //If dealer has not stood, follows hit/stand flow.
        if (playerDone == false)
        {

            //Get user input for hit or stand
            cout << "Would you like to hit? (1 - Yes, 2 - No)\n";
            cin >> pHitStand;

            //Validate User Input and prompt for appropriate value.
            while (cin.fail() || pHitStand < 1 || pHitStand > 2) {
                cout << "The character(s) you entered is not valid. Please enter 1 for yes or 2 for no." << endl;
                cout << "Would you like to hit? (1 - Yes, 2 - No)";

                //Clear cin buffer
                cin.clear();

                //Discard bad input
                cin.ignore(255, '\n');

                cin >> pHitStand;
                cout << endl;
            }

            //Draw card path when 1 is entered.
            if (pHitStand == 1)
            {
                //Draws card
                currentCardValue = gameDeck.back().value;

                //Removes card from deck
                gameDeck.pop_back();

                //Calculate current hand value
                pHandSum = pHandSum + currentCardValue;

                //if the player hand is greater than 21 roun evaluation is called.
                if (pHandSum > 21)
                {
                    //Calls the round evaluation function
                    RoundEvaluation(pHandSum, dHandSum, pRoundsWon, dRoundsWon, bank, betAmount);
                    return;
                }
            }
            //Set playerDone to true when 2 is entered.
            if (pHitStand == 2)
            {
                playerDone = true;
            }
        }

        //If dealer has not stood, follows hit/stand flow.
        if (dealerDone == false)
        {
            //Calls dealer play function to determine if to hit or stand
            dHitStand = DealerPlay(dHandSum);

            //Draw card path when 1 is entered.
            if (dHitStand == 1)
            {
                //Draws card
                currentCardValue = gameDeck.back().value;

                //Removes card from deck
                gameDeck.pop_back();

                //Calculate current hand value
                dHandSum = dHandSum + currentCardValue;

                //if the dealer hand is greater than 21 roun evaluation is called.
                if (dHandSum > 21)
                {
                    //Calls the round evaluation function
                    RoundEvaluation(pHandSum, dHandSum, pRoundsWon, dRoundsWon, bank, betAmount);
                    return;
                }
            }
            //Set dealerDone to true when 2 is entered.
            if (dHitStand == 2)
            {
                dealerDone = true;
            }
        }

        //Output current hand values
        cout << "Dealer's hand is " << dHandSum << endl;
        cout << "Player hand is: " << pHandSum << endl;

        //When both player and dealer stand round evaluation begins
        if ((playerDone == true && dealerDone == true))
        {
            //Calls the round evaluation function
            RoundEvaluation(pHandSum, dHandSum, pRoundsWon, dRoundsWon, bank, betAmount);

            //Resets hand sums for next round
            pHandSum = 0;
            dHandSum = 0;
        }

    }
}

//Bailey Reyes
//File generation/update for dealer win using append.
void DealerWin(int& dw, int pw) {
    //Creates the file stream to prep for writing.
    ofstream winnerFile;

    //Incremenets the player wins variable for tracking and writing to file.
    ++dw;

    //Opening the winners.txt file for writing.
    winnerFile.open("../blackjack_logic/winners.txt");

    //If unable to open file an error is displayed.
    if (!winnerFile.is_open()) {
        cout << "Unable to open File" << endl;
    }

    //If the file opened information is written to the file overriding whatever was there before.
    if (winnerFile.is_open()) {
        std::string dealerWin = std::to_string(dw);
        winnerFile << "Dealer: " + dealerWin << endl;

        std::string playerWin = std::to_string(pw);
        winnerFile << "Player: " + playerWin;
    }

    //Closes file
    winnerFile.close();
}

//File generation/update for player win using append.
void PlayerWin(int& pw, int dw) {
    //Creates the file stream to prep for writing.
    ofstream winnerFile;

    //Incremenets the player wins variable for tracking and writing to file.
    ++pw;

    //Opening the winners.txt file for writing.
    winnerFile.open("../blackjack_logic/winners.txt");

    //If unable to open file an error is displayed.
    if (!winnerFile.is_open()) {
        cout << "Unable to open File" << endl;
    }

    //If the file opened information is written to the file overriding whatever was there before.
    if (winnerFile.is_open()) {
        std::string dealerWin = std::to_string(dw);
        winnerFile << "Dealer: " + dealerWin << endl;

        std::string playerWin = std::to_string(pw);
        winnerFile << "Player: " + playerWin;
    }

    //Closes file
    winnerFile.close();
}

//Reads from file and displays amount of wins at the end of the game.
void DisplayWinner() {
    //Creates the file stream to prep for reading.
    fstream winnerFile;

    //Opening the winners.txt file for reading.
    winnerFile.open("../blackjack_logic/winners.txt", ios::in);

    //If unable to open file an error is displayed.
    if (!winnerFile.is_open()) {
        cout << "Unable to open File" << endl;
    }

    //If the tile opened sucessfully prints out to screen each line of the file.
    if (winnerFile.is_open()) {
        string line;
        while (getline(winnerFile, line)) {
            cout << line << endl;
        }
    }

    //Closes file
    winnerFile.close();
}

//Funtion to keep track of winnings.
int Bank(bool playerWon, bool dealerWon, int bankAmount, int betAmount) {
    int winnings = bankAmount;

    //Evaluates weather to add or subtract the bet bet from the back and return the new bank amount.
    if (playerWon == true) {
        winnings = betAmount + winnings;
    }
    else if (dealerWon == true) {
        winnings = winnings - betAmount;
    }

    return winnings;
}



/**************Testing Information****************
All Pass/Normal
Input:
200
1
1
2
2

Expected Output:
Enter your bet amount: $200
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 7
Player hand is: 2
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 17
Player hand is: 12
Would you like to hit? (1 - Yes, 2 - No)
2
Dealer's hand is 17
Player hand is: 12

Dealers score: 17
Players score: 12
Dealer Wins :(
Remaining Bank: $300
Play again? (1 - Yes, 2 - No): 2

Dealer: 1
Player: 0

Actual Output:
Enter your bet amount: $200
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 7
Player hand is: 2
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 17
Player hand is: 12
Would you like to hit? (1 - Yes, 2 - No)
2
Dealer's hand is 17
Player hand is: 12

Dealers score: 17
Players score: 12
Dealer Wins :(
Remaining Bank: $300
Play again? (1 - Yes, 2 - No): 2

Dealer: 1
Player: 0

User Input Valdation Test
Input:
sad
600
123
mad
12
bad
12
1

Expected Output:
Enter your bet amount: $sad
The character(s) you entered is not valid. Please enter a number less than or equal to :500
Enter your bet amount: $600

The character(s) you entered is not valid. Please enter a number less than or equal to :500
Enter your bet amount: $123

Would you like to hit? (1 - Yes, 2 - No)
mad
The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)12

The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)bad

The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)12

The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)1

Dealer's hand is 8
Player hand is: 5
Would you like to hit? (1 - Yes, 2 - No)
2
Dealer's hand is 13
Player hand is: 5

Dealers score: 22
Players score: 5
Player Wins!! :)
Remaining Bank: $623
Play again? (1 - Yes, 2 - No): 2

Dealer: 0
Player: 1

Actual Output:
Enter your bet amount: $sad
The character(s) you entered is not valid. Please enter a number less than or equal to :500
Enter your bet amount: $600

The character(s) you entered is not valid. Please enter a number less than or equal to :500
Enter your bet amount: $123

Would you like to hit? (1 - Yes, 2 - No)
mad
The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)12

The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)bad

The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)12

The character(s) you entered is not valid. Please enter 1 for yes or 2 for no.
Would you like to hit? (1 - Yes, 2 - No)1

Dealer's hand is 8
Player hand is: 5
Would you like to hit? (1 - Yes, 2 - No)
2
Dealer's hand is 13
Player hand is: 5

Dealers score: 22
Players score: 5
Player Wins!! :)
Remaining Bank: $623
Play again? (1 - Yes, 2 - No): 2

Dealer: 0
Player: 1

Multi Round Testing
Input:
150
1
1
2
1
345
1
1
1
1
120
1
1
1
2
Expected Output:
Enter your bet amount: $150
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 8
Player hand is: 10
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 18
Player hand is: 20
Would you like to hit? (1 - Yes, 2 - No)
2
Dealer's hand is 18
Player hand is: 20

Dealers score: 18
Players score: 20
Player Wins!! :)
Remaining Bank: $650
Play again? (1 - Yes, 2 - No): 1

Round: 2

Enter your bet amount: $345
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 4
Player hand is: 10
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 14
Player hand is: 15
Would you like to hit? (1 - Yes, 2 - No)
1

Dealers score: 14
Players score: 24
Dealer Wins :(
Remaining Bank: $305
Play again? (1 - Yes, 2 - No): 1

Round: 3

Enter your bet amount: $120
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 7
Player hand is: 10
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 17
Player hand is: 14
Would you like to hit? (1 - Yes, 2 - No)
1

Dealers score: 17
Players score: 24
Dealer Wins :(
Remaining Bank: $185
Play again? (1 - Yes, 2 - No): 2

Dealer: 2
Player: 1

Actual Output:
Enter your bet amount: $150
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 8
Player hand is: 10
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 18
Player hand is: 20
Would you like to hit? (1 - Yes, 2 - No)
2
Dealer's hand is 18
Player hand is: 20

Dealers score: 18
Players score: 20
Player Wins!! :)
Remaining Bank: $650
Play again? (1 - Yes, 2 - No): 1

Round: 2

Enter your bet amount: $345
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 4
Player hand is: 10
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 14
Player hand is: 15
Would you like to hit? (1 - Yes, 2 - No)
1

Dealers score: 14
Players score: 24
Dealer Wins :(
Remaining Bank: $305
Play again? (1 - Yes, 2 - No): 1

Round: 3

Enter your bet amount: $120
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 7
Player hand is: 10
Would you like to hit? (1 - Yes, 2 - No)
1
Dealer's hand is 17
Player hand is: 14
Would you like to hit? (1 - Yes, 2 - No)
1

Dealers score: 17
Players score: 24
Dealer Wins :(
Remaining Bank: $185
Play again? (1 - Yes, 2 - No): 2

Dealer: 2
Player: 1
*************End Testing Information**************/
