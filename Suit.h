#ifndef SUIT_H_INCLUDED
#define SUIT_H_INCLUDED

class Suit {
private:
    char suit;
    // 's'pades   ♠
    // 'h'earts   ♥
    // 'd'iamonds ♦
    // 'c'lubs    ♣

public:
    Suit();

    Suit& operator=(Suit &x);

    void setSuit(char Suit);
    void setSuit(int Suit);

    void display();
};

Suit::Suit() {
    suit = '0';
}

Suit& Suit::operator=(Suit &x) {
    suit = x.suit;
    return *this;
}

void Suit::setSuit(char Suit) {
    if ( Suit!='s' && Suit!='h' && Suit!='d' && Suit!='c' )
       { cout << "error: at.Suit" << endl;
         return;
       }
    suit = Suit;
}

void Suit::setSuit(int Suit) {
    char ans;
    switch ( Suit )
           { case 1:
                 ans = 's';
                 break;
             case 2:
                 ans = 'h';
                 break;
             case 3:
                 ans = 'd';
                 break;
             case 4:
                 ans = 'c';
                 break;
             default:
                 ans = '*';
                 break;
           }

    setSuit(ans);
}

void Suit::display() {
    if ( suit=='s' )
       { cout << "<S>";
         return;
       }
    if ( suit=='h' )
       { cout << "<H>";
         return;
       }
    if ( suit=='d' )
       { cout << "<D>";
         return;
       }
    if ( suit=='c' )
       { cout << "<C>";
         return;
       }
    cout << "error: at.Suit" << endl;
}

#endif // SUIT_H_INCLUDED
