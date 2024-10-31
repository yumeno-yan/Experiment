#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// 写入文件的辅助类
class Co_handler
{
public:
    int init(string_view file_path);
    Co_handler& operator<<(string_view str);
private:
    ofstream fout;      // 文件句柄
    string dir_path;    // 文件夹路径
};

extern Co_handler coh;

// 读取文件的辅助类
class Ci_handler
{
public:
    static int read_number(const string& file_path, string& number);
};