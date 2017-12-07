#include "stdio.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <memory>

#define N  100         // maximum number of digits supported
#define NN (2*N + 1)   // number of digits allocated
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

class XP {
private:
    unsigned char digits[NN];
    int len;

public:
    XP(char* str) {
        len = 0;
        for (char* it = str; *it; ++it) {
            len++;
        }

        for (int i = len-1, j=0; i>=0; i--,j++) {
            digits[j] = str[i] - '0';
        }
    }

    int isOdd() {
        return len > 0 ? digits[0] % 2 == 1 : 0;
    }

    int isEven() {
        return len > 0 ? digits[0] % 2 == 0 : 1;
    }

    void add(XP b) {
        int minLen = MIN(len, b.len);
        char carry = 0;
        int i = 0;
        for (; i<minLen; i++) {
            char d = digits[i] + b.digits[i] + carry;
            if (d > 9) {
                carry = 1;
                d = d - 10;
            } else {
                carry = 0;
            }
            // printf("%c + %c = %c , %c\n", digits[i] + '0', b.digits[i] + '0', d+'0', carry+'0');
            digits[i] = d;
        }

        if (len > b.len) {
            digits[i] += carry;
        } else if (b.len > len) {
            digits[i] = b.digits[i] + carry;
            i++;
            for (; i<b.len; i++) {
                digits[i] = b.digits[i];
            }
            len = b.len;
        } else {
            if (carry > 0) {
                digits[i] = carry;
                len++;
            }
        }
    }

    void print() {
        for (int i = len-1; i>=0; i--) {
            printf("%c", digits[i] + '0');
        }
    }

    static unique_ptr<XP> rand(int len) {
        char str[NN];
        int i=0;
        for(; i<MIN(len, NN); i++) {
            str[i] = '0' + std::rand() % 10;
        }
        str[i] = '\0';
        return unique_ptr<XP>( new XP(str) );
    }
};

void testIsOdd() {
    unique_ptr<XP> x = XP::rand(20);
    x->print();
    printf(" is %s \n", x->isOdd() ? "Odd" : "Even" );
}

int main(int argc, char** argv) {
    srand(time(NULL));

    for(int i=3; i<=argc; i+=2) {
        XP a(argv[i-1]);
        XP b(argv[i-2]);

        printf("Test:\n  %s\n+ %s\n", argv[i-1], argv[i-2]);
        a.add(b);
        printf("= ");
        a.print();
        printf("\n");


    }

    if(argc == 1) {
        testIsOdd();

        printf("RANDOM NUMBER:\n");
        unique_ptr<XP> x = XP::rand(10); // unique_ptr<XP>( new XP("1234567890") );
        x->print();
        printf("\n");
    }

    return 0;
}
