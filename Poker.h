#ifndef POKER_H_INCLUDED
#define POKER_H_INCLUDED

class Poker {
private:
    static const int num = 52;
    Card ary[num];
    int top;

public:
    Poker();

    static const int getNum();
    Card& getCard(int Number);

    Card& payCard();

    void checkEnough();

    void shuffle();
    void shuffle(int Time);
    void display();
};

Poker::Poker() {
    for ( int t=0, i=1 ; i<=4 ; ++i )
        { for ( int j=1 ; j<=13 ; ++j, ++t )
              { ary[t].setCard(j, i);
              }
        }
    top = 0;
}

const int Poker::getNum() {
    return num;
}

Card& Poker::getCard(int Number) {
    if ( Number<1 )
       { cout << "error: at.Poker" << endl;
         return ary[top];
       }
    if ( Number>num-top )
       { cout << "error: at.Poker" << endl;
         return ary[top];
       }
    return ary[top+Number-1];
}

Card& Poker::payCard() {
    ++top;
    return ary[top-1];
}

void Poker::checkEnough() {
    if ( top*2 >= num )
       { shuffle();
       }
}

void Poker::shuffle() {
    for ( int i=1 ; i<=1000 ; ++i )
        { int x = rand()%num;
          int y = rand()%num;
          Card temppp;
          temppp = ary[x];
          ary[x] = ary[y];
          ary[y] = temppp;
        }
    top = 0;
}

void Poker::shuffle(int Time) {
    if ( Time<1 )
       { cout << "error: at.Poker" << endl;
         return;
       }
    for ( int i=1 ; i<=Time ; ++i )
        { shuffle();
        }
}

void Poker::display() {
    for ( int i=top ; i<num ; ++i )
        { ary[i].display();
          cout << endl;
        }
}

#endif // POKER_H_INCLUDED
