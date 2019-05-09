// Problem: 11062 - Andy's Second Dictionary
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2003
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <set>
using namespace std;

#define MAX 10000

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    set<string> myset;

    char str[MAX];
    int n = 0;
    char ch;
    while (true) {
        ch = getchar();
        if (ch == EOF)
            break;

        if (ch >= 'A' && ch <= 'Z')
            ch += 32; // to lowercase

        if (ch >= 'a' && ch <= 'z') {
            str[n++] = ch;
        } else if (ch == '-') {
            ch = getchar();
            if (ch != '\n') { // the word with special characters -> not hyphenation word
                str[n++] = '-';

                if (ch >= 'A' && ch <= 'Z')
                    ch += 32; // to lowercase
                str[n++] = ch;
            }
        } else {
            if (n > 0) {
                str[n] = '\0'; // end of string
                myset.insert(string(str)); // add to myset
                n = 0; // reset n = 0
            }
        }
    }

    for (set<string>::iterator it = myset.begin(); it != myset.end(); ++it) {
        cout << *it << endl;
    }

	return 0;
}
