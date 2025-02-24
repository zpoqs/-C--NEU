#include<iostream>
#include"check.h"
#include<QStringList>
#include<regex>
#include<io_base.h>
int Check_Password_Right(QString s)//检查密码格式对不对
{
    int size = s.size();
    int right = 1;//判断正确性
    for(int i = 0;i < size;i++)
    {
        if((s[i] <='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')||(s[i]>='0'&&s[i]<='9'))
        {
            continue;
        }
        else
        {
            right = 0;
            break;
        }
    }
    return right;
}
int Check_EmailBox_Input(QString s)//检查邮箱格式对不对
{
    if(s == "")
    {
        return 1;
    }
    int size = s.size();
    if (!(s[0] >= 'a' && s[0] <= 'z') && !(s[0] >= 'A' && s[0] <= 'Z') && !(s[0] >= '0' && s[0] <= '9'))
    {
        return 0;
    }
    int position = 0;
    for(int i = 1;i < size;i++)
    {
        if (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= '0' && s[i] <= '9'))
        {
            if(s[i] == '@')
            {
                position = i+1;
                break;
            }
            else
            {
                return 0;
            }
        }
    }
    if(!position)
    {
        return 0;
    }
    QStringList SS = s.split("@");
    if(SS.size() != 2)
    {
        return 0;
    }
    if(SS[1] != "qq.com")
    {
        return 0;
    }
    return 1;//检查邮箱格式对不对
}
bool Check_Phone_Input(const std::string& phone)
{
    std::regex pattern("^1[3-9]\\d{9}$");// 定义一个正则表达式来匹配中国手机号
    return std::regex_match(phone, pattern);// 使用std::regex_match来判断字符串是否与正则表达式匹配
}
int Check_Mon_Once(QString mon)//检查是不是只添加了一次这个月的信息
{
    QVector<Salary> sal = ReadSalary();
    for(int i = 0 ;i < sal.size();i++)
    {
        if(sal[i].time.mon == mon)
        {
            return 1;
        }
    }
    return 0;
}

bool Check_Double(QString qurry)//判断要查询的是不是有效的浮点数
{
    bool ok;
    qurry.toDouble(&ok);
    return ok;
}
