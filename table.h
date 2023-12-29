#pragma once
#include <QApplication>
#include <vector>
#include <string>
#define int uint64_t
#include "globals.h"

const std::string letters = "abcdef";

bool cmp(const std::string& a, const std::string& b) {
    if (a.size() == b.size()) {
        return a < b;
    }
    return a.size() < b.size();
}

std::vector<int> numbers(std::string& my_letters, std::string& silly_letters) {
    std::vector<int> ans;
    for (int i = 0; i < (int)my_letters.size(); ++i) {
        for (auto silly_elem : silly_letters) {
            if (silly_elem == my_letters[(int)my_letters.size()-i-1]) {
                ans.push_back(i);
            }
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

void f(std::string& s, std::vector<std::string>& v, int16_t i = 0) {
    if (i == s.size()) {
        return;
    }
    int sz = (int)v.size();
    for (int j = 0; j < sz; ++j) {
        v.push_back(v[j]+s[i]);
    }
    f(s, v, ++i);
}

std::vector<std::vector<Node>> build(std::vector<std::string>& scary_letters,
                                     std::string& my_letters, int16_t n, uint64_t x = 0) {
    std::vector<std::vector<Node>> ans((1 << n) + 1, std::vector<Node>((1 << n)));
    ans[0][0].s = "f";
    for (int16_t i = 1; i < 1<<n; ++i) {
        ans[0][i].s = scary_letters[i-1];
    }//🐠🐟
    for (int i = 1<<n; i > 0; --i) {
        ans[i][0].s.push_back('0'+(x&1));
        x >>= 1;
    }
    for (int16_t i = 0; i < 1<<n; ++i) {
        for (int16_t j = 1; j <= 1<<n; ++j) {
            auto nums = numbers(my_letters, ans[0][j].s);//ааааааа я не понимаю как называть переменые ааааоаоаооаоаоао
            for (auto elem : nums) {
                ans[i+1][j].s.push_back('0'+(i>>elem&1));
            }
        }
    }
    return ans;
}

int16_t w(std::string s) {
    int16_t ans = 0;
    for (int i = 0; i < 6; ++i) {
        for (auto elem : s) {
            if (elem == letters[i]) {
                ans |= (int16_t)1<<i;
            }
        }
    }
    return ans;
}

void g(std::vector<std::vector<Node>>& ans) {
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i][0].s == "0") {
            for (int j = 1; j < ans[i].size(); ++j) {
                ans[i][j].t = 1;
                for (int k = 1; k < ans.size(); ++k) {
                    if (ans[k][j].s == ans[i][j].s && ans[k][j].t == 0) {
                        ans[k][j].t = 2;
                    }
                }
            }
        }
    }
    for (int i = 1; i < ans.size(); ++i) {
        for (int j = 1; j < ans[0].size(); ++j) {
            if (ans[i][j].t == 0) {
                for (int k = 1; k < ans[0].size(); ++k) {
                    if (j != k && ans[i][k].t == 0 && (w(ans[0][j].s) & w(ans[0][k].s)) == w(ans[0][j].s)) {
                        ans[i][k].t = 3;
                    }
                }
            }
        }
    }

}

std::vector<std::vector<Node>> new_table(const int16_t& n, const uint64_t& x) {
    std::string my_letters = letters;
    for (int16_t i = 0; i < 6-n; ++i) {
        my_letters.pop_back();
    }
    std::vector<std::string> scary_letters = {""};
    f(my_letters, scary_letters);
    std::reverse(scary_letters.begin(), scary_letters.end());
    scary_letters.pop_back();
    std::sort(scary_letters.begin(), scary_letters.end(), cmp);
    auto ans = build(scary_letters, my_letters, n, x);
    g(ans);
    return ans;
}
