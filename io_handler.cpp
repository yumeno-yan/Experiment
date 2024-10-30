#define _CRT_SECURE_NO_WARNINGS
#include "io_handler.h"
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

/**
 * @brief 读取文件中的字符串，这里只读取一行
 * @param file_path 文件路径
 */
int Ci_handler::read_number(const string& file_path, string& number)
{
    ifstream in(file_path);
    if (!in.is_open())
    {
        cerr << "open file error\n";
        return -1;
    }
    getline(in, number);
    return 0;
}

Co_handler coh;

/**
 * @brief 绑定一个目录的路径，在其中创建一个文件保存算式和输出的结果
 */
int Co_handler::init(const string& path)
{
    // 先关闭文件句柄
    if (this->fout.is_open())
    {
        this->fout.close();
    }
    // 使用当前时间作为文件名
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    stringstream ss;
    // 使用put_time格式化输出
    // 这里区分一下windows和linux
    string split;
#ifdef _WIN32
    split = "\\";
#else
    split = "/";
#endif
    ss << path << split
        << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H-%M-%S")
        << ".txt";
    string file_name(ss.str());
    this->fout.open(file_name);
    if (!this->fout.is_open())
    {
        cerr << "open file error!\n";
        return -1;
    }
    return 0;
}

Co_handler& Co_handler::operator<<(const string& str)
{
    cout << str;
    if (this->fout.is_open())
        this->fout << str;
    return *this;
}
