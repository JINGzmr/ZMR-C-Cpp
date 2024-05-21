#include <iostream>
#include <map>
#include <string>
using namespace std;

class Solution {
   public:
    bool is_all_have(map<char, int> M) {
        for (const auto& pair : M) {
            int value = pair.second;

            if (value == 0) {
                return false;  // 如果有一个值等于零，可以立即退出循环
            }
        }
        return true;  // 说明都有
    }

    string minWindow(string s, string t) {
        int min = 1000000;
        int left = -1, right = 0;
        int l, r;  // 用于保存min对应的两个指针位置
        if (s.length() < t.length()) {
            return "";
        }
        map<char, int> M;

        for (char ch : t) {
            M[ch] = 0;
        }

        while (right + 1 <= s.length()) {
            // bool a = is_all_have(M);
            // cout << a;
            // 只要当前窗口内还有没置1的，右指针就不断右移
            while (is_all_have(M) == false && right + 1 <= s.length()) {
                // 说明当前字符在t中有
                if (M.find(s[right]) != M.end()) {
                    // 有的话就将键对应的值++
                    M[s[right]] += 1;
                }
                right++;
            }

            while (is_all_have(M) == true) {
                left++;
                if (M.find(s[left]) != M.end()) {
                    // 有的话就将键对应的值--
                    M[s[left]] -= 1;
                }
                 
            }

            r = right-1;
            l = left-1;
            if (right - left < min)
                min = right - left;
        }
        // cout << l << " " << r;
        string result = s.substr(l + 1, min);

        return result;
    }
};

int main() {
    Solution solution;
    string str = solution.minWindow("a", "b");
    cout << str << endl;
}
