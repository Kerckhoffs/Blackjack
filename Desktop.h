#ifndef DESKTOP_H_INCLUDED
#define DESKTOP_H_INCLUDED

class Desktop {
private:
    Coin coin;
    Coin tokn;

public:
    Desktop();

    int getCoin();
    int getToken();
    void setZero();

    Coin payCoin();

    void recCoin(Coin Cash);
    void recCoin(int  Cash);
};

Desktop::Desktop() {
    setZero();
}

int Desktop::getCoin() {
    return coin.getCoin();
}

int Desktop::getToken() {
    return tokn.getCoin();
}

void Desktop::setZero() {
    coin.setZero();
    tokn.setZero();
}

Coin Desktop::payCoin() {
    Coin ans = coin + tokn;
    setZero();
    return ans;
}

void Desktop::recCoin(Coin Cash) {
    coin += tokn;
    tokn = Cash;
}

void Desktop::recCoin(int Cash) {
    coin += tokn;
    tokn = Cash;
}

#endif // DESKTOP_H_INCLUDED
