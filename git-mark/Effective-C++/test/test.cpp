#include<iostream>
#include<string.h>
using namespace std;

#if 0 
/* Describe: 条款03,运用const operator[]实现出non-const版本
 * Time:     2017-11-27 17:25  
 * Author:   thomas
 * Title:    Tools_03
 */
class A1
{
public: 
    A1(char *str){
        strcpy(arr,str);
    }
    const char &operator[](std::size_t pos)const{
        return arr[pos];
    }
    char &operator[](std::size_t pos){
        return const_cast<char&>(static_cast<const A1&>(*this)[pos]);
    }
private:
    char arr[100];
};

int main()
{
    char str[100] = "hello";
    class A1 a(str);

    char aa_1 = a[1];
    cout << aa_1 << endl;

    const char aa_2 = a[1];
    cout << aa_2 << endl;

    return 0;
}
#endif

#if 1
/* Describe: 条款07:为多态基类声明virtual析构函数
 * Time:     2017年12月5日17:35:51
 * Author:   thomas
 * Title:    Tool_07
 */

class base_class
{
public:
    base_class()
    {
        cout << "Construction base class" << endl;
    }
    //virtual ~base_class()
    ~base_class()
    {
        cout << "DeConstruction base class" << endl;
    }
};

class drive_class :  public base_class
{
public:
    drive_class()
    {
        cout << "Construction drive class" << endl;
    }
    ~drive_class()
    {
        cout << "DeConstruction drive class" << endl;
    }
};

class most_drive_class : public drive_class
{
public:
    most_drive_class()
    {
        cout << "Construction most drive class" << endl;
    }
    ~most_drive_class()
    {
        cout << "DeConstruction most drive class" << endl;
    }
};

void test()
{
    cout << "================" << endl;
    //base_class *ba = new drive_class;
    base_class *ba = new most_drive_class;
    delete ba;
    cout << "================" << endl;
}

int main()
{
    test();
    return 0;
}
#endif
