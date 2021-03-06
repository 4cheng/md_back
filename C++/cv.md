
# C++
### C++ 封装类
### 函数重载原理
### 多态机制
### 强制类型转换
### 异常机制
### 动态静态链接库
### 智能指针
### 写时拷贝 Copy On Write `COW`
简而言之：“写的时候才去分配空间”。是一种延时拷贝。
实现原理：通过“引用计数”实现。在分配空间时多分配 4 个字节，用来记录有多少个指针指向这块空间，当有新指针指向时 +1，释放空间时 -1，如果引用计数等于 0，才彻底释放这块空间。如果有指针要修改这块空间，则再为这个指针分配自己的空间（此时，旧计数 -1，新计数 +1）.
使用 `COW` 实现 `String` 类:
```C++
class String
{
public:
    String(const char str="") :_str(new char[strlen(str) + 1 + 4])
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
}
```



### STL容器