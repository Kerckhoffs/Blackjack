#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void round(int*, int, int, int&, int&);
void round_s1(int*, int*, int*, int&, int&, int&, int, int&, int&, int&, int&);
void round_s2(int*, int*, int*, int&, int&, int&, int, int&, int&, int&, int&);

void hit_p(int*, int*, int*, int&, int&, int&, int, int&, int&, int);
void hit_d(int*, int*, int*, int&, int&,       int, int&, int&, int);

void endCheck_A(int, int, int&, int&, int);
void endCheck(int&, int&, int, int win, float); // win= 0:閒家, 1:莊家, 2:平

void deal(int*, int*, int&, int&);
void reset(int*, int);
int checkPoint(int*);
int checkPoint(int*, int);

void showCard(int*, int, bool); // bool= 1:全部顯示, 0:暗牌
void checkCin(int&, int, int); // 檢查, 下限(含), 上限(含)
void checkCin(char&);

int main()
{
    const int card_gn = 1;          // 牌組數
    const int card_cn = card_gn*52; // 總牌數

    int* A=new int[card_cn];

    const int Coin = 20; // 初始金額
    int coin_d = Coin;   // 莊家
    int coin_p = Coin;   // 閒家

    int CardCount = 0;                            // 牌堆計數器
    round(A, CardCount, card_gn, coin_d, coin_p); // 開始遊戲

    delete [] A;
    return 0;
}

void round(int* A, int cc, int card_n, int &coin_d, int &coin_p) // 牌堆, 牌堆計數器, 牌組數, 莊家籌碼, 閒家籌碼
{
    if ( cc > card_n*52/2 || cc == 0 )
       { cc = 0;  reset(A, card_n);
       }

    const int TheMaxCard = 12;
    int* Ad=new int[TheMaxCard]; // 莊家手牌
    int* Ap=new int[TheMaxCard]; // 閒家手牌
    for ( int i=0 ; i<TheMaxCard ; ++i )
        { Ad[i] = 0;  Ap[i] = 0;
        }
    int cd = 0, cp = 0; // 手牌計數器

    int token = 1, token_d = 0;

    round_s1(A, Ad, Ap, cc, cd, cp, TheMaxCard, coin_d, coin_p, token_d, token);

    round_s2(A, Ad, Ap, cc, cd, cp, TheMaxCard, coin_d, coin_p, token_d, token);

    hit_p(A, Ad, Ap, cc, cd, cp, TheMaxCard, coin_d, coin_p, token_d);

    delete [] Ad;
    delete [] Ap;

    if ( coin_d*coin_p <= 0 )
       { cout << endl << "遊戲結束" << endl;
         return;
       }

    char Continue;
    cout << endl << "是否再來一局 (y/n)? ";
    cin >> Continue;  checkCin(Continue);
    if ( Continue=='y' )
       { round(A, cc, card_n, coin_d, coin_p);
       }
    return;
}

void round_s1(int* A, int* Ad, int* Ap, int &cc, int &cd, int &cp, int TheMaxCard, int &coin_d, int &coin_p, int &token_d, int &token)
{
    cout << endl << "莊家的籌碼: " << coin_d << ", 您的籌碼: " << coin_p << endl;

    const int max_token = coin_p;
    const int min_token = 1;
    cout << "請下第一注開局 (可下 " << min_token << " ~ " << max_token << "): ";
    cin  >> token;  checkCin(token, min_token, max_token);
    coin_p  -= token;
    token_d += token;

    cout << endl << "發牌..." << endl;
    deal(A, Ap, cc, cp);
    deal(A, Ad, cc, cd);

    cout << "莊家的牌:";
    showCard(Ad, TheMaxCard, 0);
    cout << "手中的牌:";
    showCard(Ap, TheMaxCard, 1);
    return;
}

void round_s2(int* A, int* Ad, int* Ap, int &cc, int &cd, int &cp, int TheMaxCard, int &coin_d, int &coin_p, int &token_d, int &token)
{
    cout << endl << "莊家的籌碼: " << coin_d << ", 您的籌碼: " << coin_p << endl;

    const int max_token = coin_p;
    const int min_token = token;
    if   ( max_token < min_token )
         { cout << "因籌碼不足, 系統自動下注, 遊戲照常進行." << endl;
           token = max_token;
         }
    else { cout << "請下注 (可下 " << min_token << " ~ " << max_token << "): ";
           cin  >> token;  checkCin(token, min_token, max_token);
         }
    coin_p  -= token;
    token_d += token;

    cout << endl << "發牌..." << endl;
    deal(A, Ap, cc, cp);
    deal(A, Ad, cc, cd);

    cout << "莊家的牌:";
    showCard(Ad, TheMaxCard, 0);
    cout << "手中的牌:";
    showCard(Ap, TheMaxCard, 1);
    return;
}

void hit_p(int* A, int* Ad, int* Ap, int &cc, int &cd, int &cp, int TheMaxCard, int &coin_d, int &coin_p, int token_d)
{
    for ( ; true ; )
        { char hit;
          cout << "要牌 Hit/停牌 Stand (h/s)? ";
          cin >> hit;
          if      ( hit=='h' )
                  { deal(A, Ap, cc, cp);
                    cout << "手中的牌: ";  showCard(Ap, TheMaxCard, 1);
                    const int point = checkPoint(Ap, 0);
                    if ( point > 21 )
                       { cout << "爆煲! " << point << " 點" << endl;
                         endCheck(coin_d, coin_p, token_d, 1, 0);
                         return;
                       }
                  }
          else if ( hit=='s' )
                  { cout << endl << "莊家要牌..." << endl;
                    hit_d(A, Ad, Ap, cc, cd, TheMaxCard, coin_d, coin_p, token_d);
                    return;
                  }
          else    { cout << "請輸入 h 或 s, ";
                  }
        }
}

void hit_d(int* A, int* Ad, int* Ap, int &cc, int &cd, int TheMaxCard, int &coin_d, int &coin_p, int token_d)
{
    for ( ; true ; )
        { const int point = checkPoint(Ad);
          if      ( point < 17 )
                  { deal(A, Ad, cc, cd);
                    cout << "莊家要牌: ";  showCard(Ad, TheMaxCard, 0);
                  }
          else if ( point > 21 )
                  { cout << "莊家爆煲! " << point << " 點" << endl;
                    showCard(Ad, TheMaxCard, 1);
                    endCheck(coin_d, coin_p, token_d, 0, 1);
                    return;
                  }
          else    { cout << endl << "雙方皆未爆煲, 開牌:" << endl;
                    const int point_d = checkPoint(Ad);
                    const int point_p = checkPoint(Ap);
                    cout << "莊家的牌: ";  showCard(Ad, TheMaxCard, 1);
                    cout << "手中的牌: ";  showCard(Ap, TheMaxCard, 1);
                    cout << "莊家點數 " << point_d << ", 您的點數 " << point_p << endl;
                    endCheck_A(point_d, point_p, coin_d, coin_p, token_d);
                    return;
                  }
        }
}

void endCheck_A(int pd, int pp, int &cd, int &cp, int t)
{
    if      ( pd > pp )
            { endCheck(cd, cp, t, 1, 0);
            }
    else if ( pd < pp )
            { endCheck(cd, cp, t, 0, 1.5);
            }
    else    { endCheck(cd, cp, t, 2, 0);
            }
    return;
}

void endCheck(int &coin_d, int &coin_p, int token_d, int win, float odds)
{
    if      ( win==0 )
            { cout << endl << "本局閒家獲勝!" << endl;
              const int pay = token_d*odds;
              coin_d -= pay;
              coin_p += token_d;
              coin_p += pay;
            }
    else if ( win==1 )
            { cout << endl << "本局莊家獲勝!" << endl;
			  coin_d += token_d;
            }
    else    { cout << endl << "本局平手!" << endl;
              coin_p += token_d;
            }
    if      ( coin_d <= 0 )
            { cout << endl << "莊家已失去所有籌碼, 您贏了!" << endl;
            }
    else if ( coin_p <=0 )
            { cout << endl << "您已失去所有籌碼, 您輸了!" << endl;
            }
    else    { cout << "莊家的籌碼: " << coin_d << ", 您的籌碼: " << coin_p << endl;
            }
    return;
}

void deal(int* A, int* Ax, int &cc, int &cx)
{
    Ax[cx] = A[cc];
    A [cc] = 0;
    ++cx;  ++cc;
    return;
}

void reset(int* A, int n)
{
    cout << "重新洗牌..." << endl;
    int c = 0;
    for ( int i=1 ; i<=n ; ++i )
        { for ( int j=1 ; j<=4 ; ++j )
              { for ( int k=1 ; k<=13 ; ++k )
                    { A[c] = k;  ++c;
                    }
              }
        }
    const int nc = n*52;
    const int nn = nc*nc;
    srand( (unsigned)time(NULL) );
    for ( int i=1 ; i<=nn ; ++i )
        { int x = rand()%nc;
          int y = rand()%nc;
          int t=A[x];
          A[x]=A[y];
          A[y]=t;
        }
    return;
}

int checkPoint(int* A)
{
    int sum = 0, doubleA = 0;
    for ( int i=0 ; true ; ++i )
        { if ( A[i]==0 )
             { break;
             }
          if      ( A[i]==1 )
                  { sum += 11;
                    ++doubleA;
                  }
          else if ( A[i]>=2 && A[i]<=9 )
                  { sum += A[i];
                  }
          else    { sum += 10;
                  }
        }

    if ( doubleA > 1)
       { sum -= 10*(doubleA-1);
       }

    if   ( sum > 21 )
         { const int point = checkPoint(A, 0);
           return point;
         }
    else { return sum;
         }
}

int checkPoint(int* A, int n)
{
    if ( A[n]==0 )
       { return 0;
       }
    if   ( A[n]>=1 && A[n]<=10 )
         { return A[n] + checkPoint(A, n+1);
         }
    else { return  10  + checkPoint(A, n+1);
         }
}

void showCard(int* A, int n, bool Switch)
{
    if   ( Switch )
         { for ( int i=0 ; i<n ; ++i )
               { if ( A[i]==0 )
                    { break;
                    }
                 cout << setw(3) << A[i];
               }
         }
    else { cout << "  *";
           for ( int i=1 ; i<n ; ++i )
               { if ( A[i]==0 )
                    { break;
                    }
                 cout << setw(3) << A[i];
               }
         }
    cout << endl;
    return;
}

void checkCin(int &x, int a, int b)
{
    for ( ; true ; )
        { if   ( x>=a && x<=b )
               { return;
               }
          else { cout << "提醒, 下注範圍 " << a << " ~ " << b << ": ";
                 cin >> x;
               }
        }
}

void checkCin(char &x)
{
    for ( ; true ; )
        { if   ( x=='y' || x=='n' )
               { return;
               }
          else { cout << "請輸入 y 或 n: ";
                 cin >> x;
               }
        }
}
