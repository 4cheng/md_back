#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class String
{
public:
    String(const char* str="") :_str(new char[strlen(str) + 1 + 4])
    {
        cout << "String ()" << endl;
        _str += 4;                      // 前 4 个字节来存放引用计数
        GetCount() = 1;                 // 引用计数的初始值设置成 1
        strcpy(_str, str);
    }

    String(const String& s) :_str(s._str)
    {
        cout << "String(const String&)" << endl;
        GetCount()++;
    }

    String& operator=(const String& s)
    {
        cout << "String& operator=" << endl;
        
        if (this != &s)
        {
            Release();
            _str = s._str;
            GetCount()++;
        }
        return *this;
    }

    ~String()
    {
        cout << "~String"<< endl;
        Release();
    }

public:
    char& operator[](size_t index)
    {
        if (GetCount() == 1)
        {
            return _str[index];
        }
        GetCount()--;
        char *tmp = _str;
        _str = new char[strlen(tmp) + 1 + 4];
        _str += 4;
        strcpy(_str, tmp);
        GetCount() = 1;
        return _str[index];
    }


private:
    int& GetCount()
    {
        return *(int *)(_str - 4);
    }

    void Release()
    {
        if (--GetCount() == 0)
        {
            cout << "relase" << endl;
            delete[](_str - 4);
            _str = NULL;
        }
    }

private:
    char *_str;
};


int main()
{
    String s1 = "hello";
    String s2 = s1;
    cout << &s1 << endl;
    cout << &s2<< endl;

    s1[1] = 'q';
    s2[1] = 'w';
    cout << &s1 << endl;
    cout << &s2 << endl;
    return 0;
}