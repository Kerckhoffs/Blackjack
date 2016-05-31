#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

// source: Templates_01_Stack

template <typename T>
class Stack {
private:
    int tot;
    T* ary;
    int top;

public:
    Stack();
    Stack(Stack<T> &x);

    Stack<T>& operator=(const Stack<T> &x);

    void push(const T &x);
    void pop();
    void popAll();

    const T& getTop();
    bool getEmpty();
    void display();

    // Card
    int calPoint();
    void display(bool ALL);

    ~Stack();

private:
    void overflow();
};

template <typename T>
Stack<T>::Stack() {
    tot = 2;
    ary = new T[tot];
    top = -1;
}

template <typename T>
Stack<T>::Stack(Stack<T> &x) {
    tot = x.tot;
    top = x.top;
    ary = new T[tot];
    for ( int i=0 ; i<=top ; ++i )
        { ary[i] = x.ary[i];
        }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &x) {
    delete [] ary;
    tot = x.tot;
    top = x.top;
    ary = new T[tot];
    for ( int i=0 ; i<=top ; ++i )
        { ary[i] = x.ary[i];
        }
    return *this;
}

template <typename T>
void Stack<T>::push(const T &x) {
    if ( top==tot-1 )
       { overflow();
       }
    ++top;
    ary[top] = x;
}

template <typename T>
void Stack<T>::pop() {
    if ( getEmpty() )
       { cout << "error" << endl;
         return;
       }
    --top;
}

template <typename T>
void Stack<T>::popAll() {
    for ( ; !getEmpty() ; )
        { pop();
        }
}

template <typename T>
const T& Stack<T>::getTop() {
    if ( getEmpty() )
       { static T t;
         cout << "error" << endl;
         return t;
       }
    return ary[top];
}

template <typename T>
bool Stack<T>::getEmpty() {
    if ( top==-1 )
       { return true;
       }
    return false;
}

template <typename T>
void Stack<T>::display() {
    for ( int i=0 ; i<=top ; ++i )
        { cout << ary[i] << " ";
        }
    cout << endl;
}

template <typename T>
int Stack<T>::calPoint() {
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

template <typename T>
void Stack<T>::display(bool ALL) {
    for ( int i = !ALL ; i<=top ; ++i )
        { ary[i].display();
          cout << " ";
        }
}

template <typename T>
Stack<T>::~Stack() {
    delete [] ary;
}

template <typename T>
void Stack<T>::overflow() {
    int tmp_tot = tot * 2;
    T* tmp_ary = new T[tmp_tot];
    for ( int i=0 ; i<=top ; ++i )
        { tmp_ary[i] = ary[i];
        }
    delete [] ary;
    ary = tmp_ary;
    tot = tmp_tot;
}

#endif // STACK_H_INCLUDED
