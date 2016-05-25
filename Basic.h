#ifndef BASIC_H_INCLUDED
#define BASIC_H_INCLUDED

void sortSelectSB(int* ary, int n)  // Selection Sort
{
    for ( int i=0 ; i<n-1 ; ++i )
        { int m = i;
          for ( int j=i+1 ; j<n ; ++j )
              { if ( ary[j]<ary[m] )
                   { m = j;
                   }
              }
          int t = ary[m];
          ary[m] = ary[i];
          ary[i] = t;
        }
    return;
}

void sortSelectBS(int* ary, int n)
{
    for ( int i=0 ; i<n-1 ; ++i )
        { int m = i;
          for ( int j=i+1 ; j<n ; ++j )
              { if ( ary[j]>ary[m] )
                   { m = j;
                   }
              }
          int t = ary[m];
          ary[m] = ary[i];
          ary[i] = t;
        }
    return;
}

#endif // BASIC_H_INCLUDED
