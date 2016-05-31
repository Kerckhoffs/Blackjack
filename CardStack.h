#ifndef CARDSTACK_H_INCLUDED
#define CARDSTACK_H_INCLUDED

class CardStack {
private:
    int tot;
    Card* ary;
    int top;

public:
    CardStack();

    void place(const Card &x);
    void out();
    void outAll();

    int calPoint();
    void display(bool ALL);

    ~CardStack();

private:
    void inOverflow();
};

CardStack::CardStack() {
    tot = 2;
    ary = new Card[tot];
    top = -1;
}

void CardStack::place(const Card &x) {
    if ( top==tot-1 )
       { inOverflow();
       }
    ++top;
    ary[top] = x;
}

void CardStack::out() {
    if ( top==-1 )
       { cout << "error: at.CardStack" << endl;
         return;
       }
    --top;
}

void CardStack::outAll() {
    for ( ; top != -1 ; )
        { out();
        }
}

int CardStack::calPoint() {
    if ( top==-1 )
       { return 0;
       }


    int* c = new int[top+1];
    for ( int i=0 ; i<top+1 ; ++i )
        { if ( ary[i].getNum()>10 )
             { c[i] = 10;
               continue;
             }
          c[i] = ary[i].getNum();
        }


    int point = 0, one = 0;
    for ( int i=0 ; i<top+1 ; ++i )
        { if ( c[i]==1 )
             { ++one;
             }
          point += c[i];
        }
    delete [] c;


    for ( ; true ; --one )
        { if ( one==0 )
             { break;
             }
          if ( point <= 11 )
             { point += 10;
               continue;
             }
          break;
        }
    return point;
}

void CardStack::display(bool ALL) {
    for ( int i = !ALL ; i<=top ; ++i )
        { ary[i].display();
          cout << " ";
        }
}

CardStack::~CardStack() {
    delete [] ary;
}

void CardStack::inOverflow() {
    int tmp_tot = tot * 2;
    Card* tmp_ary = new Card[tmp_tot];
    for ( int i=0 ; i<=top ; ++i )
        { tmp_ary[i] = ary[i];
        }
    delete [] ary;
    ary = tmp_ary;
    tot = tmp_tot;
}

#endif // CARDSTACK_H_INCLUDED
