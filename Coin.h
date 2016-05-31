#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

class Coin {
private:
    static const int def = 20;
    int coin;

public:
    Coin();

    int getCoin();
    void setZero();

    Coin& operator=(int x);
    Coin& operator=(const Coin &x);
    Coin& operator+(const Coin &x);
    Coin& operator-(const Coin &x);

    Coin& operator+=(int x);
    Coin& operator-=(int x);
    Coin& operator+=(Coin &x);
    Coin& operator-=(Coin &x);
};

Coin::Coin() {
    coin = def;
}

int Coin::getCoin() {
    return coin;
}

void Coin::setZero() {
    coin = 0;
}

Coin& Coin::operator=(int x) {
    coin = x;
    return *this;
}

Coin& Coin::operator=(const Coin &x) {
    coin = x.coin;
    return *this;
}

Coin& Coin::operator+(const Coin &x) {
    static Coin ans;
    ans.coin = coin + x.coin;
    return ans;
}

Coin& Coin::operator-(const Coin &x) {
    static Coin ans;
    ans.coin = coin - x.coin;
    return ans;
}

Coin& Coin::operator+=(int x) {
    if ( x<0 )
       { cout << "error: at.Coin" << endl;
         return *this;
       }
    coin += x;
    return *this;
}

Coin& Coin::operator-=(int x) {
    if ( x<0 )
       { cout << "error: at.Coin" << endl;
         return *this;
       }
    if ( x>coin )
       { cout << "error: at.Coin" << endl;
         return *this;
       }
    coin -= x;
    return *this;
}

Coin& Coin::operator+=(Coin &x) {
    *this += x.getCoin();
    return *this;
}

Coin& Coin::operator-=(Coin &x) {
    *this -= x.getCoin();
    return *this;
}

#endif // COIN_H_INCLUDED
