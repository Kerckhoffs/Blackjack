#ifndef POKERGRP_H_INCLUDED
#define POKERGRP_H_INCLUDED

class PokerGrp {
private:
    int num;
    Card* ary;
    int top;

public:
    PokerGrp();
    PokerGrp(int Number);

    Card& getCard(int Number);

    Card& payCard();

    void checkEnough();

    void shuffle(int Time);
    void display();

    ~PokerGrp();

private:
    void shuffle();
};

PokerGrp::PokerGrp() {
    num = top = 0;
    ary = NULL;
}

PokerGrp::PokerGrp(int Number) {
    if ( Number<1 )
       { cout << "error: at.PokerGrp" << endl;
         return;
       }
    num = Number;

    ary = new Card[num*Poker::getNum()];  Poker exa;
    for ( int t=0, i=1 ; i<=num ; ++i )
        { for ( int j=1 ; j<=Poker::getNum() ; ++j, ++t )
              { ary[t] = exa.getCard(j);
              }
        }

    top = 0;
}

Card& PokerGrp::getCard(int Number) {
    if ( Number<1 )
       { cout << "error: at.PokerGrp" << endl;
         return ary[top];
       }
    if ( Number>num*Poker::getNum()-top )
       { cout << "error: at.PokerGrp" << endl;
         return ary[top];
       }
    return ary[top+Number-1];
}

Card& PokerGrp::payCard() {
    ++top;
    return ary[top-1];
}

void PokerGrp::checkEnough() {
    if ( top*2 >= num*Poker::getNum() )
       { shuffle(1);
       }
}

void PokerGrp::shuffle(int Time) {
    if ( Time<1 )
       { cout << "error: at.PokerGrp" << endl;
         return;
       }
    cout << "[洗牌]" << endl << endl;
    for ( int i=1 ; i<=Time ; ++i )
        { shuffle();
        }
}

void PokerGrp::display() {
    int all = num * Poker::getNum();
    for ( int i=top ; i<all ; ++i )
        { ary[i].display();
          cout << endl;
        }
}

PokerGrp::~PokerGrp() {
    delete [] ary;
}

void PokerGrp::shuffle() {
    const int t = 1000*num;
    const int r = num*Poker::getNum();
    for ( int i=1 ; i<=t ; ++i )
        { int x = rand()%r;
          int y = rand()%r;
          Card temppp;
          temppp = ary[x];
          ary[x] = ary[y];
          ary[y] = temppp;
        }
    top = 0;
}

#endif // POKERGRP_H_INCLUDED
