#include"base_lei.h"
#include"io_base.h"
#include"FindUser.h"


double Salary::getSalary_Performance() {  // 计算绩效>（从外部调用）
    Employee per = FindUserByidInEmp(id);
    double department_coefficient = FindDept_co(per.Dept,per.Position);
    salary_Performance = (basic_salary+salary_position) * 0.15 * department_coefficient;
    return (basic_salary+salary_position) * 0.15 * department_coefficient;
}
double Salary::getHouse()
{
    Employee per = FindUserByidInEmp(id);
    if(per.Position == 2)
    {
        House = 1000;
    }
    else
        House = 800;
    return House;
}
double Salary::getReward() {  // 计算奖励>（从外部调用）
    Attendance attend = FindAttend_user_Mon(id,time.mon,time.year);
    if(attend.id == "")
    {
        reward = 0.0;
        return 0.0;
    }
    else
    {
        reward = attend.overtime * 30.0;
        return attend.overtime * 30.0; // 加班一小时奖励30
    }
}
double Salary::getPay_salary()//计算应发工资>
{
    pay_salary = basic_salary + salary_position + salary_Performance + House + reward;
    return pay_salary;
}

double Salary::getFund() // 计算公积金>
{
    fund = pay_salary * 0.05;//
    return fund;
};
double Salary::getTax() {  // 计算扣税>
    double tax_rate;
    double taxable_income = pay_salary;

    // 根据工资范围确定税率
    if (taxable_income <= 5000) {
        tax_rate = 0; // 5000元以下免税
    } else if (taxable_income > 5000 && taxable_income <= 8000) {
        tax_rate = 0.03; // 5000-8000元之间税率3%
    } else if (taxable_income > 8000 && taxable_income <= 17000) {
        tax_rate = 0.10; // 8000-17000元之间税率10%
    } else if (taxable_income > 17000 && taxable_income <= 30000) {
        tax_rate = 0.20; // 17000-30000元之间税率20%
    } else {
        // 超出范围，需要一个默认税率或者错误处理
        tax_rate = 0.20; // 使用最高税率
    }

    // 计算扣税金额
    tax = taxable_income * tax_rate;

    // 考虑到可能存在免税额度（例如：5000元以下免税），需要调整扣税金额
    if (taxable_income > 5000) {
        // 只对超过5000元的部分征税
        tax = (taxable_income - 5000) * tax_rate;
    }

    // 返回扣税金额
    return tax;
}
double Salary::getAttend_redu()
{
    Attendance attend = FindAttend_user_Mon(id,time.mon,time.year);
    if(attend.id == "")
    {
        attend_redu = 0;
        return 0.0;
    }
    else
    {
        attend_redu = (attend.late + attend.exit_early)*50;
        return (attend.late + attend.exit_early)*50; // 迟到早退一次扣50
    }
}
double Salary::getReal_salary()  //   计算实发工资>
{
    real_salary = pay_salary - fund - tax - attend_redu;
    return real_salary;
};
