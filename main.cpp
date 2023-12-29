//#pragma once
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include "mdnf.h"
//#define int
//
//void next() {
//    ++tt;
//}
//
//void last() {
//    --tt;
//}

int32_t main(int32_t argc, char *argv[]) {
    int16_t n;
    uint64_t x;
    std::cin >> n >> x;
    auto table = new_table(n, x);
    QApplication a(argc, argv);
    QTableWidgetItem* ptwi = new QTableWidgetItem();
    QTableWidget tbl((int)table.size(), (int)table[0].size());
    for (int i = 0; i < (int)table.size(); ++i) {
        for (int j = 0; j < (int)table[0].size(); ++j) {
            ptwi = new QTableWidgetItem(QString::fromStdString(table[i][j].s));
            if (table[i][j].t == 0) {
                ptwi->setBackground(Qt::gray);
            } else if  (table[i][j].t == 1) {
                ptwi->setBackground(Qt::green);
            } else if (table[i][j].t == 2) {
                ptwi->setBackground(Qt::red);
            } else if (table[i][j].t == 3) {
                ptwi->setBackground(Qt::blue);
            }
            tbl.setItem(i, j, ptwi);
        }
    }
    auto mdnf = answer(table);
    int mn_sz = 100;
    for (auto elem : mdnf) {
        mn_sz = std::min(mn_sz, (int)elem.size());
    }
    for (auto elem : mdnf) {
        if (elem.size() == mn_sz) {
            bool flag = false;
            for (auto s: elem) {
                if (flag) {
                    std::cout << '|';
                }
                flag = true;
                std::cout << s;
            }
            std::cout << '\n';
        }
    }
    tbl.setGeometry(QRect(0,0,300,250));
    tbl.show();
    return a.exec();
//    QApplication a(argc, argv);
//
//    App convertor(825, 160);
//    convertor.render();
//
//    return a.exec();
}
