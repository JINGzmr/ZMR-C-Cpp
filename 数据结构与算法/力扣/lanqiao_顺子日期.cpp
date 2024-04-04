#include <iostream>
#include <string>
using namespace std;

int main() {
    int num = 0;
    for (int i = 20220101; i <= 20221231; i++) {
        string str = to_string(i);
        for(int j=3;j<=5;j++){
            if(str[j]+1==str[j+1]&&str[j]+2==str[j+2]){
                num++;
                cout << str << endl;//因为填空题，再手动筛出符合的日期即可
            }
        }
    }
    cout << num;

    return 0;
}