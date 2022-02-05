#include <iostream>
#include <map>

using namespace std;

int main() {
    map<char, int> a;

    cout << a['a'] << endl;
    a['a']++;
    cout << a['a'] << endl;

    

    return 0;
}