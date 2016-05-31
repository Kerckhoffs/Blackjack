#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player {
private:
    static const int maxName = 9;
    bool identity; // 0: 閒家 (def), 1: 莊家
    char name[maxName];
    Coin coin;
    CardStack card;
    int point;

public:
    Player();
    Player(bool Dealer);
    Player(char* Name);

    static const int getMaxName();
    bool getIdentity();
    int getCoin();
    int getPoint();

    void payCoinTo(Player  &x, int Cash);
    void payCoinTo(Desktop &x, int Cash);

    void recCoinFm(Desktop  &x);
    void recCardFm(Poker    &x);
    void recCardFm(PokerGrp &x);

    void recCoin(Coin Cash);
    void recCoin(int  Cash);

    void awyCard();
    void display(bool ALL);

private:
    void setFirst();
    void setDealer();
    void setName(char* Name);

    void calPoint();
};

Player::Player() {
    setFirst();
}

Player::Player(bool Dealer) {
    setFirst();
    setDealer();
}

Player::Player(char* Name) {
    setFirst();
    setName(Name);
}

const int Player::getMaxName() {
    return maxName;
}

bool Player::getIdentity() {
    return identity;
}

int Player::getCoin() {
    return coin.getCoin();
}

int Player::getPoint() {
    return point;
}

void Player::payCoinTo(Player &x, int Cash) {
    if ( Cash<0 )
       { cout << "error: at.Player" << endl;
         return;
       }
    if ( Cash>coin.getCoin() )
       { Cash = coin.getCoin();
       }
    coin -= Cash;
    x.recCoin(Cash);
}

void Player::payCoinTo(Desktop &x, int Cash) {
    if ( Cash<0 )
       { cout << "error: at.Player" << endl;
         return;
       }
    if ( Cash>coin.getCoin() )
       { cout << "error: at.Player" << endl;
         return;
       }
    coin -= Cash;
    x.recCoin(Cash);
}

void Player::recCoinFm(Desktop &x) {
    recCoin( x.payCoin() );
}

void Player::recCardFm(Poker &x) {
    card.place( x.payCard() );
    calPoint();
}

void Player::recCardFm(PokerGrp &x) {
    card.place( x.payCard() );
    calPoint();
}

void Player::recCoin(Coin Cash) {
    coin += Cash;
}

void Player::recCoin(int Cash) {
    coin += Cash;
}

void Player::awyCard() {
    card.outAll();
    calPoint();
}

void Player::display(bool ALL) {
    if ( !ALL )
       { cout << "  *  " << " ";
       }
    card.display(ALL);
    cout << endl;
}

void Player::setFirst() {
    identity = 0;
    name[0] = '\0';
    point = 0;
}

void Player::setDealer() {
    identity = 1;
    char t[maxName] = "Dealer";
    setName(t);
}

void Player::setName(char* Name) {
    strcpy(name, Name);
}

void Player::calPoint() {
    point = card.calPoint();
}

#endif // PLAYER_H_INCLUDED
