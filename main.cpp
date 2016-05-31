#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits>
using namespace std;

#include "Stack.h"

#include "Card.h"
#include "CardStack.h"

#include "Poker.h"
#include "PokerGrp.h"

#include "Coin.h"

#include "Desktop.h"
#include "Player.h"

void round(PokerGrp&, Player& dealer, Player& player);

const bool bust = true;
bool roundHitP(PokerGrp&, Player& player);
bool roundHitD(PokerGrp&, Player& dealer);

void winPlayer(Desktop&, Player& winer, Player& loser); // winner: Player
void winDealer(Desktop&, Player& winer, Player& loser); // winner: Dealer
void winDraw  (Desktop&, Player& dealer, Player& player);

void check(int&, int, int);
void check(char&, char, char);

int main()
{
    srand( (unsigned)time(NULL) );


    PokerGrp card(2);
    card.shuffle(3);

    char name[7] = "Player";
    Player dealer(true), player(name);


    round(card, dealer, player);
    return 0;
}

void round(PokerGrp &card, Player &dealer, Player &player)
{
    Desktop desk;  int token;  card.checkEnough();
    cout << "開局." << endl << endl;

    cout << "莊家的籌碼: " << dealer.getCoin()
         << ", 您的籌碼: " << player.getCoin()
         << endl;


    // Round 01
    int maxToken = player.getCoin();
    int minToken = 1;
    cout << "請下第一注 (range " << minToken << " ~ " << maxToken << "): ";
    cin >> token;  check(token, minToken, maxToken);  cout << endl;

    player.payCoinTo(desk, token);


    cout << "發牌..." << endl << endl;
    dealer.recCardFm(card);
    player.recCardFm(card);

    cout << "莊家的牌: ";  dealer.display(false);
    cout << "手中的牌: ";  player.display(true);
    cout << endl;


    // Round 02
    cout << "莊家的籌碼: " << dealer.getCoin()
         << ", 您的籌碼: " << player.getCoin()
         << endl;


    maxToken = player.getCoin();
    minToken = desk.getToken();
    if   ( maxToken<=minToken )
         { cout << "[籌碼未高於上一注, 系統將自動下注]" << endl << endl;
           player.payCoinTo(desk, maxToken);
         }
    else { cout << "請下注 (range " << minToken << " ~ " << maxToken << "): ";
           cin >> token;  check(token, minToken, maxToken);  cout << endl;

           player.payCoinTo(desk, token);
         }


    cout << "發牌..." << endl << endl;
    dealer.recCardFm(card);
    player.recCardFm(card);

    cout << "莊家的牌: ";  dealer.display(false);
    cout << "手中的牌: ";  player.display(true);
    cout << endl;


    // Round Hit
    bool hp, hd;
    hp = roundHitP(card, player);

    if ( hp!=bust )
       { cout << "[莊家要牌]" << endl
              << "莊家的牌: ";  dealer.display(false);
         hd = roundHitD(card, dealer);
       }


    // Round End Check
    if      ( hp==bust )
            { winDealer(desk, dealer, player);
            }
    else if ( hd==bust )
            { winPlayer(desk, player, dealer);
            }
    else    { cout << "莊家的牌(" << dealer.getPoint() << "點): ";  dealer.display(true);
              cout << "手中的牌(" << player.getPoint() << "點): ";  player.display(true);
              cout << endl;
              if      ( player.getPoint()<dealer.getPoint() )
                      { winDealer(desk, dealer, player);
                      }
              else if ( player.getPoint()>dealer.getPoint() )
                      { winPlayer(desk, player, dealer);
                      }
              else    { winDraw(desk, dealer, player);
                      }
            }


    // Next Round
    if ( player.getCoin()==0 )
       { cout << "您已失去所有籌碼, 您輸了!!!" << endl;
         return;
       }
    if ( dealer.getCoin()==0 )
       { cout << "莊家失去所有籌碼, 您贏了!!!" << endl;
         return;
       }

    char choice;
    cout << "是否再來一局 (y/n)? ";
    cin >> choice;  check(choice, 'y', 'n');  cout << endl;
    if ( choice=='n' )
       { return;
       }
    return round(card, dealer, player);
}

bool roundHitP(PokerGrp &card, Player &player)
{
    char choice;
    cout << "要牌 Hit/停牌 Stand (h/s)? ";
    cin >> choice;  check(choice, 'h', 's');  cout << endl;


    if ( choice=='s' )
       { return !bust;
       }

    player.recCardFm(card);
    cout << "手中的牌: ";  player.display(true);  cout << endl;

    if ( player.getPoint() > 21 )
       { cout << "[爆煲: " << player.getPoint() << " 點]" << endl << endl;
         return bust;
       }
    return roundHitP(card, player);
}

bool roundHitD(PokerGrp &card, Player &dealer)
{
    if ( dealer.getPoint() >= 17 )
       { cout << "[Finish]" << endl << endl;
         return !bust;
       }

    dealer.recCardFm(card);
    if ( dealer.getPoint() > 21 )
       { cout << "莊家的牌: ";  dealer.display(true);
         cout << "[莊家爆煲: " << dealer.getPoint() << " 點]" << endl << endl;
         return bust;
       }
    cout << "莊家的牌: ";  dealer.display(false);
    return roundHitD(card, dealer);
}

void winPlayer(Desktop &desk, Player &winer, Player &loser)
{
    winer.awyCard();
    loser.awyCard();

    int cash = desk.getCoin() + desk.getToken();
        cash = cash * 1.5;

    loser.payCoinTo(winer, cash);
    winer.recCoinFm(desk);

    cout << "您贏了本局!!" << endl
         << "莊家的籌碼: " << loser.getCoin()
         << ", 您的籌碼: " << winer.getCoin()
         << endl << endl;
    return;
}

void winDealer(Desktop &desk, Player &winer, Player &loser)
{
    winer.awyCard();
    loser.awyCard();

    winer.recCoinFm(desk);

    cout << "您輸掉本局!!" << endl
         << "莊家的籌碼: " << winer.getCoin()
         << ", 您的籌碼: " << loser.getCoin()
         << endl << endl;
    return;
}

void winDraw(Desktop &desk, Player &dealer, Player &player)
{
    dealer.awyCard();
    player.awyCard();

    player.recCoinFm(desk);

    cout << "本局為平手!!" << endl
         << "莊家的籌碼: " << dealer.getCoin()
         << ", 您的籌碼: " << player.getCoin()
         << endl << endl;
    return;
}

void check(int &x, int Min, int Max)
{
    if ( x>=Min && x<=Max && !(cin.fail()) )
       { return;
       }

    cout << "range error, try again: ";
    cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> x;

    return check(x, Min, Max);
}

void check(char &x, char a, char b)
{
    if ( (x==a || x==b) && !(cin.fail()) )
       { return;
       }

    cout << "answer error, try again: ";
    cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> x;

    return check(x, a, b);
}
