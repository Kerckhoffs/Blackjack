#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "Suit.h"

class Card {
private:
    int  num;
    Suit sui;

public:
    Card();
    Card(int Number, char Suit);
    Card(int Number, int Suit);

    Card& operator=(Card &x);

    int getNum();
    void setCard(int Number, char Suit);
    void setCard(int Number, int Suit);

    void display();
};

Card::Card() {
    num = 0;
}

Card::Card(int Number, char Suit) {
    setCard(Number, Suit);
}

Card::Card(int Number, int Suit) {
    setCard(Number, Suit);
}

Card& Card::operator=(Card &x) {
    num = x.num;
    sui = x.sui;
    return *this;
}

int Card::getNum() {
    return num;
}

void Card::setCard(int Number, char Suit) {
    if ( Number<1 )
       { cout << "error: at.Card" << endl;
         return;
       }
    if ( Number>13 )
       { cout << "error: at.Card" << endl;
         return;
       }
    num = Number;
    sui.setSuit(Suit);
}

void Card::setCard(int Number, int Suit) {
    if ( Number<1 )
       { cout << "error: at.Card" << endl;
         return;
       }
    if ( Number>13 )
       { cout << "error: at.Card" << endl;
         return;
       }
    num = Number;
    sui.setSuit(Suit);
}

void Card::display() {
    sui.display();
    cout << setw(2) << num;
}

#endif // CARD_H_INCLUDED
