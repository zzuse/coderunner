//
//  main.cpp
//  getAges
//
//  Created by Zhen.Zhang on 13-11-22.
//  Copyright (c) 2013 zz. All rights reserved.
//

#include <iostream>
#include <time.h>

class Date
{
  public:
    Date(int y = 1, int m = 1, int d = 1)
    {
        day = d;
        month = m;
        year = y;
    }
    friend int cal(Date a, Date b, std::string);

  private:
    int day;
    int month;
    int year;
};

int leap(int year)
{
    return ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) ? 1 : 0;
}

int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int cal(Date a, Date b, std::string name)
{
    int years = 0, months = 0, days = 0;
    years = a.year - b.year;
    if (years < 0)
    {
        printf("%s 错误日期\n", name.c_str());
        return -1;
    }
    days = a.day - b.day;
    if (days < 0)
    {
        months--;
        days = a.day + month[b.month - 1] - b.day;
        if (leap(b.year) && (b.month - 1 == 1))
        {
            days++;
        }
    }
    months += a.month - b.month;
    if (months < 0)
    {
        years--;
        months += 12;
    }
    printf("%s是%d岁%d个月%d天\n", name.c_str(), years, months, days);
    return 0;
}

int main(int argc, const char *argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    printf("Local Date is: %d-%d-%d %d:%d:%d\n", 1900 + local->tm_year, 1 + local->tm_mon, local->tm_mday,
           local->tm_hour, local->tm_min, local->tm_sec);
    std::cout << std::endl;
    Date sysdate(1900 + local->tm_year, 1 + local->tm_mon, local->tm_mday);

    Date zhangzhen(1981, 10, 30);
    Date zhangjinyang(2011, 07, 02);
    Date jiaowei(1984, 10, 25);
    Date yuefu(1958, 2, 21);
    Date yuemu(1960, 8, 3);
    Date mama(1955, 10, 10);
    Date baba(1953, 11, 07);
    Date meimei(1990, 3, 28);

    Date weddingday(2010, 11, 5);
    //cal(sysdate, testday, "test");
    cal(sysdate, zhangzhen, "张臻年龄");
    cal(sysdate, zhangjinyang, "张晋扬年龄");
    cal(sysdate, jiaowei, "焦威年龄");
    cal(sysdate, meimei, "张锦年龄");

    std::cout << std::endl;
    cal(zhangjinyang, zhangzhen, "儿子和我年龄差");
    cal(jiaowei, zhangzhen, "张臻和焦威年龄差");
    cal(meimei, zhangzhen, "妹妹和张臻年龄差");
    cal(sysdate, weddingday, "结婚天数是");
    std::cout << std::endl;
    cal(sysdate, yuefu, "岳父年龄");
    cal(sysdate, yuemu, "岳母年龄");
    std::cout << std::endl;
    cal(sysdate, baba, "爸爸年龄");
    cal(sysdate, mama, "妈妈年龄");
    std::cout << std::endl;
    cal(mama, baba, "妈妈爸爸年龄差");
    cal(yuefu, mama, "岳父妈妈年龄差");
    cal(yuemu, yuefu, "岳母岳父年龄差");
    return 0;
}
