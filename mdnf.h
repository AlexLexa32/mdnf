#pragma once
#include <vector>
#include <set>
#include "table.h"

void rec(std::vector<std::vector<Node>>& a, std::set<std::set<std::string>>& ans, std::set<std::string>& s, int i = 1, int tt = 3) {
    if (i == a.size()) {
        ans.insert(s);
        return;
    }
    bool flag = true;
    for (int j = 1; j < a[0].size(); ++j) {
        if (a[i][j].t == 0) {
            flag = false;
            int qq = 2;
            std::string str;
            str.push_back('(');
            a[i][j].tin = tt;
            for (int k = 0; k < a[i][j].s.size(); ++k) {
                if (a[i][j].s[k] == '0') {
                    str += "!";
                    str += a[0][j].s[k];
                    qq += 2;
                } else {
                    str += a[0][j].s[k];
                    qq++;
                }
            }
            str.push_back(')');
            bool check = s.find(str) == s.end();
            s.insert(str);
            rec(a, ans, s, i+1, tt+1);
            if (check) {
                s.erase(str);
            }
            a[i][j].tout = tt;
        }
    }
    if (flag) {
        rec(a, ans, s, i+1);
    }
}

std::set<std::set<std::string>> answer(std::vector<std::vector<Node>>& a) {
    std::set<std::set<std::string>> ans;
    std::set<std::string> s;
    rec(a, ans, s);
    return ans;
}