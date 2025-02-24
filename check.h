#ifndef CHECK_H
#define CHECK_H
#include<QString>
int Check_Password_Right(QString s);//检查输入的字符是否正确
int Check_EmailBox_Input(QString s);//检查邮箱格式是否正确
bool Check_Phone_Input(const std::string& phone);//检查手机号格式是否正确
int Check_Mon_Once(QString mon);//检查是不是只添加了一次这个月的信息
bool Check_Double(QString qurry);//判断要查询的是不是有效的浮点数

#endif // CHECK_H
