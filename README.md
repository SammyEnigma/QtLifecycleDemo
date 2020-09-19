# QtLifecycleDemo
(仿Android)fragmentmanager+lifecycle+pimpl+livedata实现mvvm设计模式

这是一个Qt框架下仿照Android实现的mvvm设计模式，示例中实现了view和viewmodel的分离，并增加了页面管理类fragmentmanager，关于model框架：
- 数据库模型框架：[QtSql](https://github.com/daonvshu/QtDao) 
- 网络模型框架：（待实现）

## LifeCycleWidget
LifeCycleWidget为配合fragmentmanager类使用的子页面基类，并且使用了pImpl模式，其中包含了6个生命周期函数，选择使用这些：
- 创建时：(构造函数)
- 第一次显示时：onViewLoad()
- 再次显示时：onReshow()
- 隐藏时：onHidden()
- 窗口大小变化时：onResizeWindow()
- 销毁时：(析构函数)

同时LifeCycleWidget包含3个通知函数：
- navigateTo：创建跳转到指定名称的页面并传递参数
- navigateBack：返回当前页面并传递参数
- finish：关闭当前页面并从页面栈中移除

实现一个类继承LifeCycleWidget，其中模板参数LaunchMode为子页面创建方式，pagename为页面创建一个名称。例如：
```c++
#include "ui_SubForm.h"
#include "../../lifecycle/LifeCycleWidget.h" 

const char subpage[] = "subpage";
class SubPage : public LifeCycleWidget<Mode_SingleTop, subpage> {

public:
    SubPage(QWidget* parent);
    ~SubPage();

private:
    Ui::SubForm ui;
};
```
可以使用宏Q_DECLARE_PRIVATE来使用pImpl模式

## fragmentmanager
fragmentmanager是子页面页面栈管理的一个简单类，用于管理实现LifeCycleWidget的子页面，其中装载页面使用的容器为QStackedWidget，因此创建和注册页面使用以下方式：
```c++
fragmentManager = new FragmentManager(ui.stackedWidget);
fragmentManager->registerPage<SubPage, SubPage2>();
```
与LifeCycleWidget类似，包含3个工具函数创建页面：
- navigateTo：创建跳转到指定名称的页面并传递参数
- replaceTo：替换当前页面为指定名称的页面并传递参数
- navigateBack：返回上一个页面并传递参数

fragmentmanager跳转子页面是通过字符串方式创建对应子页面，接收子页面的跳转请求通过信号槽的机制

## livedata
livedata用于变量-控件绑定工具类，对变量赋值view同时更新，用户对view设置值变量自动赋值，借助信号槽可以在子线程中修改变量在主线程中更新view，其中更新控件是使用控件propertyname属性方式进行赋值，因此需要指定属性，默认为"text"属性。通过加号运算符"+"绑定控件。
- 绑定控件：
```c++
data + ui->lineEdit + ui->lineEdit_2;
```
- 指定属性：
```c++
data + "styleSheet";
```
- 指定自定义类型转换器：
```c++
//自定义结构体
struct StrT {
    QString data;
    int a;
};

//自定义转换器
QVariant srtTConvert(const StrT& src) {
    return src.data;
}

//连接到转换器
data + srtTConvert;
```
- 添加双向绑定
```c++
#include "../../livedata/LineEditNotify.h"

//连接到lineEdit文字改变信号
data + lineEdit_textChanged;

//如果是自定义类型，需要实现view转换器viewDataConverter
template<>
inline void viewDataConverter(StrT& data, const QString& src) {
    data.data = src;
}
```
- 由于“+”重载后返回自身，因此可以连写
```c++
data + "styleSheet" + ui->lineEdit + ui->lineEdit_2 + srtTConvert + lineEdit_textChanged;
```
- livedata重载了“=”用于赋值：
```c++
StrT s;
s.data = ui->lineEdit_3->text();
s.a = 1;
data = s;
```
- livedata重载了“()”用于取值
```c++
StrT s = data();
```

AbstractModelHelpter
AbstractModelHelpter用于自定义结构体与QTableView（或QListView）的数据绑定的工具类，未使用livedata，但能够方便的将自定义结构体与模型行绑定，具有以下工具函数：
- reset：清空数据与视图
- update：将视图编辑后的数据更新到自定义数据中
- append：添加一行到视图
- editRow：编辑指定行的数据
