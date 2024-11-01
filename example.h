#pragma once
#include "io_handler.h"
#include "BigDecimal.h"

using namespace std;

void example()
{
    // 从文件读取两个数字
    string num1, num2;
    if (Ci_handler::read_number("num1.txt", num1) != 0)
    {
        return;
    }
    if (Ci_handler::read_number("num2.txt", num2) != 0)
    {
        return;
    }
    // 用这两个数字初始化BigDecimal变量，也可以直接用字符串初始化，不读取文件
    BigDecimal a(num1);
    BigDecimal b(num2);
    /* 加法 */
    auto add_res = a + b;
    cout<<"add_res: ";
    add_res.show();
    /* 减法 */
    auto sub_res = a - b;
    cout<<"\nsub_res: ";
    sub_res.show();
    /* 乘法 */
    pf.equation_output = true;  // 乘法同时输出算式
    auto mul_res = a * b;
    cout<<"\nmul_res: ";
    mul_res.show();
    // 数字太大可以使用科学计数法，significant_digits代表几位有效数字
    pf.significant_digits = 10;
    mul_res.format_show();  // format输出科学计数法的结果
    cout<<"\n\n";
    /* 除法 */
    pf.equation_output = true;  // 除法同时输出算式
    auto div_res = a / b;
    cout<<"\ndiv_res: ";
    div_res.show();
    // 幂运算，这里可以传字符串，也可以传BigDecimal对象
    auto pow_res = a.pow("99"); // 幂运算的指数最好不要超过100
    pf.significant_digits = 10;
    cout<<"\npow_res: ";
    pow_res.format_show();  // 保留10位有效数字输出结果，直接输出会很大
    // 算算术平方根
    auto sqrt_res = a.sqrt();
    cout<<"\nsqrt_res: ";
    sqrt_res.show();
}
