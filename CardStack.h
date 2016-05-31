#ifndef CARDSTACK_H_INCLUDED
#define CARDSTACK_H_INCLUDED

class CardStack {
private:
    Stack<Card> ary;

public:
    void place(const Card &x);
    void out();
    void outAll();

    int calPoint();
    void display(bool ALL);
};

void CardStack::place(const Card &x) {
    ary.push(x);
}

void CardStack::out() {
    if ( ary.getEmpty() )
       { cout << "error: at.CardStack" << endl;
         return;
       }
    ary.pop();
}

void CardStack::outAll() {
    ary.popAll();
}

int CardStack::calPoint() {
    return ary.calPoint();
}

void CardStack::display(bool ALL) {
    ary.display(ALL);
}

#endif // CARDSTACK_H_INCLUDED
