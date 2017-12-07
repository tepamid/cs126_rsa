#include "stdio.h"

#define N  100         // maximum number of digits supported
#define NN (2*N + 1)   // number of digits allocated

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

    void add(XP b) {
        int minLen = len > b.len ? b.len : len;
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
};

// void test1() {
//     XP a("123456789");
//     XP b("54545454");

//     a.add(b);
//     printf("OR: ");
//     a.print();
//     printf("\n");
//     printf("ER: 178002243\n");
// }

// void test2() {
//     XP a("54545454");
//     XP b("123456789");

//     a.add(b);
//     printf("OR: ");
//     a.print();
//     printf("\n");
//     printf("ER: 178002243\n");
// }

// void test3() {
//     XP a("5");
//     XP b("5");

//     a.add(b);
//     printf("OR: ");
//     a.print();
//     printf("\n");
//     printf("ER: 10\n");
// }

// void test4() {
//     XP a("123456789123456789123456789123456789123456789123456789");
//     XP b("123456789123456789123456789123456789123456789123456789");

//     a.add(b);
//     printf("OR: ");
//     a.print();
//     printf("\n");
//     printf("ER: ?\n");
// }

int main(int argc, char** argv) {

    for(int i=3; i<=argc; i+=2) {
        XP a(argv[i-1]);
        XP b(argv[i-2]);

        printf("Test:\n  %s\n+ %s\n", argv[i-1], argv[i-2]);
        a.add(b);
        printf("= ");
        a.print();
        printf("\n");
    }

    return 0;
}
