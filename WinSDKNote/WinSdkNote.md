# Windows API学习笔记
><details><summary>约定</summary>
>
>1. 路径符号约定    
>     + %path% - 两个%之间的内容表示一个路径变量    
>     + [path1|path2] - 表示可能存在path1或者path2路径中任何一个路径中  
>2. 开发环境约定 
>     + 开发IDE visual studio community 2022  
>     + 操作系统 window 10及以上  
1. ## 应用程序分类  
    <details>

    1. ### 分类
        <details>

        + 控制台应用程序 - **Dos程序本身没有窗口,通过windows窗口执行。**  
        + 窗口程序 - **拥有自己的窗口,可与用户交互。**  
        + 库程序 - **存放代码、数据的程序，执行文件可以从中取出代码和获取数据。**  
          <details>

          + 静态库 - **扩展名lib,在编译程序时,将代码放到执行文件中。**  
          + 动态库 - **扩展名dll,在执行时从中获取代码。**  

    2. ### 区别  
        <details>

        + 入口函数  
          <details>

          + 控制台程序 - **main**
          + 窗口程序 - **WinMain、wWinMain**
          + 动态链接库程序 - **DllMain**
          + 静态链接库程序 - **无入口函数**
        + 文件存在的方式
          <details>

          + 可执行程序(控制台、窗口) - **.exe**  
          + 动态链接库 - **.dll**  
          + 静态链接库 - **.lib**  
    3. ### 相关项目示例  
        <details>

        + WinConsole - 控制台程序示例 
        + WinWindow - 窗口程序示例 
        + WinStatic - 静态库示例  
        + WinDll - 动态库示例
2. ## 开发工具和库  
    <details>

    1. ### 编译工具  
        <details>

        + 编译器(cl.exe) - 将源文件编译成目标文件.obj
        + 链接接器(link.exe) - 将目标文件文件和库文件链接成最终文件  
        + 资源编译器(rc.exe) - 将资源文件编译,并通过链接器存入最终文件  
          <details><summary>备注</summary>

          + **编译器(cl.exe)** 和 **链接器(link.exe)** 路径 - ``` %VS_ROOT%\VC\Tools\MSVC\%MSVC_VER%\bin\[Hostx64|Hostx86]\[x64|x86] ```  
            <details><summary>示例</summary>  

            >设  
            >``` VS_ROOT = C:\\Program Files\\Microsoft Visual Studio\\2022\\Community ``` 
            >``` MSVC_VER = 14.36.32532 ```  
            >则 **cl.exe** 和 **link.exe** 可能将在以下目录存在或同时存在  
            >+ ``` C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\bin\Hostx64\x64 ```  
            >+ ``` C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\bin\Hostx64\x86 ```  
            >+ ``` C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\bin\Hostx86\x64 ```  
            >+ ``` C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\bin\Hostx86\x86 ```  
          + **资源编译器(rc.exe)** 路径 - ``` %WSDK_ROOT%\bin\%WSDK_VER%\[arm64|x64|x86] ```  
            <details><summary>示例</summary>  

            >设  
            >``` WSDK_ROOT=C:\Program Files (x86)\Windows Kits\10 ```  
            >``` WSDK_VER=10.0.22000.0 ```  
            >则 **rc.exe** 可能在以下目录存在或同时存在  
            >+ ``` C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\arm64 ```  
            >+ ``` C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x64 ```  
            >+ ``` C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x86 ```  
    2. ### 库和头文件  
        <details>

        1. #### Windows库  
            <details>

            + kernel32.dll - **提供了核心API,例如进程、线程、内存管理等**  
            + user32.dll - **提供了窗口、消息等API**  
            + gdi32.dll - **绘图相关API**  
            <details><summary>备注</summary>  

            + 库文件路径 - ```C:\\Windows\\System32 ``` 
        2. #### 头文件
            <details>

            + windows.h - **所有windows头文件集合**  
            + windef.h - **windows数据类型**  
            + winbase.h - **kernel32的API**   
            + wingdi.h - **gdi32的API**   
            + winuser.h - **user32的API**   
            + winnt.h - **unicode字符集的支持**   
            <details><summary>备注</summary>

            + 头文件路径 - ```%WSDK_ROOT%\Include\%WSDK_VER%\um``` 
            <details><summary>示例</summary>
              
            >设  
            >``` WSDK_ROOT=C:\Program Files (x86)\Windows Kits\10 ```  
            >``` WSDK_VER=10.0.22000.0 ```  
            >则头文件可能在以下路径存在  
            >```C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\um```  
        3. #### 相关函数  
            <details>

            + 应用程序入口点
              <details>

              ```  
              int APIENTRY   WinMain(
              [in] HINSTANCE hInstance,     //应用程序的当前实例的句柄。
              [in] HINSTANCE hPrevInstance, //应用程序的上一个实例的句柄。
              [in] LPSTR     lpCmdLine,     //应用程序的命令行，不包括程序名称。 
              [in] int       nShowCmd       //控制窗口的显示方式。
              );                            //如果函数成功，在收到 WM_QUIT 消息时终止。
              ```  
            + 消息框  
              <details>  

              ```
              int MessageBox(  
                    [in, optional] HWND    hWnd,      //要创建的消息框的所有者窗口的句柄。
                    [in, optional] LPCTSTR lpText,    //要显示的消息。  
                    [in, optional] LPCTSTR lpCaption, //对话框标题。  
                    [in]           UINT    uType      //对话框的内容和行为。  
              );                                      //返回点击按钮的ID。
              ```  

3. ## 第一个windows窗口程序  
    <details>
    
    1. ### 窗口创建过程  
        <details>

        1. 定义WinMain函数  
        2. 定义窗口处理函数(自定义,处理消息)  
        3. 注册窗口类(向操作系统写入一些数据)  
        4. 创建窗口(内存中创建窗口)  
        5. 显示窗口(绘制窗口的图像) 
        6. 消息循环(获取/翻译/派发消息)  
        7. 消息处理  
    2. ### 相关项目示例
       <details>

       + WinBase - windows 窗口应用程序基本程序  
4. ## 字符编码
    <details>

    1. ### 计算机编码历史背景
        <details>

        1. 标准ASCII - 美国信息交换标准代码,使用7位代表一个字符,共128个字符
        2. 扩展ASCII - 使用8位代表一个字符,共256个字符
        3. ANSI/DBCS - 2个字节表示,前128个字符与标准ASCII码相同,采用一个字节,后128个字符各个国家扩展,超出部分2个字节表示,并通过代码页区分,比如中国为GB开头
        4. UNICODE - 万国码,实现方式编码由UTF-8(变长),UTF-16(定长2字节或者4字节),windows采用的是UTF-16
    2. ### 宽字符集
       <details>
       
       + ```wchar_t``` - 双字节字符类型,实际为unsigned short,定义时候需要加"L",用于通知编译器按照双字节编译字符,采用UNICODE编码
       + ```wchar_t*``` - 宽字节字符串
       + 需要使用支持wchar_t的函数来操作字节字符串
       + ```TCHAR``` - 一个宏,如果定义了UNICODE宏则使用宽字符集,没有定义则使用单字符集  
       + ```wprintf``` - 直接打印汉字会乱码,必须设置本地化
       + ```writeConsole``` - 用于在控制台输出文字,用于替代```wprintf```
       + ```UNICODE```宏 - 如果项目属性设置为UNICODE宏,系统将自动添加UNICODE宏定义
    3. ### WSDK字符串数据类型映射
       <details>

       + LPSTR --> char*
       + LPCSTR -->const char*
       + LPWSTR -->wchar_t*
       + LPCWSTR -->const wchar_t*
       + LPTSTR -->TCHAR*
       + LPCTSTR -->const TCHAR*
    3. ### 相关项目 
        <details>
        + WinChar - 字符串操作项目
5. ## 注册窗口类 
    <details>

    1. ### 窗口类的概念
        <details>
        
        + 窗口类是包含了窗口各种参数的数据结构
        + 每个窗口都有窗口类,基于窗口类创建窗口
        + 每个窗口类都具有一个名称,使用前必须注册到系统

    2. ### 窗口类的分类
        <details>

        + 系统窗口类  - 系统已经定义好的窗口类,所有应用程序可以直接使用
        + 应用程序全局窗口类 - 由用户自己定义,当前应用程序所有模块都可以使用
        + 应用程序局部窗口类 - 由用户自己定义,当前应用程序当前模块可用
    3. ### 系统窗口类
        <details>

        + 不需要注册,直接使用即可。系统已经注册好了。

    4. ### 全局及局部窗口类
        <details>

        + style窗口类风格
          <details>

            + 应用程序全局窗口类的注册,需要在窗口类的style中加上CS_GLOBALCLASS
            + 应用程序局部窗口类的注册,在Style中不加CS_GLOBALCLASS 
    5. ### 相关项目实例
        <details>

        + WinWndClass - 注册窗口类示例项目
6. ## 注册窗口
    <details>

    1. ### API - CreateWindow/CreateWindowEx
        <details>

        + 函数原型
          <details>

          ```
            HWND CreateWindowEx(                      //用于创建窗口到内存
              [in]           DWORD     dwExStyle,     //窗口的扩展风格
              [in, optional] LPCTSTR   lpClassName,   //窗口的类名
              [in, optional] LPCTSTR   lpWindowName,  //窗口的名称
              [in]           DWORD     dwStyle,       //窗口的基本风格
              [in]           int       X,             //窗口左上角的水平位置
              [in]           int       Y,             //窗口左上角的垂直位置
              [in]           int       nWidth,        //窗口的宽度
              [in]           int       nHeight,       //窗口的高度
              [in, optional] HWND      hWndParent,    //父窗口句柄
              [in, optional] HMENU     hMenu,         //菜单句柄
              [in, optional] HINSTANCE hInstance,     //应用程序实例句柄
              [in, optional] LPVOID    lpParam        //窗口创建时,附加参数
            );                                        //创建成功返回窗口句柄

          ```
        + 实现原理
          <details>

          1. 系统根据传入的窗口类名称,在应用程序局部窗口类中进行查找,如果找到了执行2,未找到执行3。
          2. 比较局部窗口类与创建窗口时传入的Instance。如果发现相等,创建和注册的窗口在同个模块,创建窗口返回.如果不相等执行3。
          3. 在应用程序全局窗口类中进行查找,如果找到执行4,未找到执行5。
          4. 使用找到的窗口类信息,创建窗口并返回。
          5. 在系统类中查找窗口类,如果找到了,创建并返回,否则创建窗口失败。
        + 创建子窗口
          <details>

          + 创建的时候要设置父窗口句柄
          + 创建风格要加上WS_CHILD|WS_VISIBLE

7. ## 消息的概念和作用
    <details>

    1. 消息的组成(windows下) 
        <details>

        + 窗口句柄
        + 消息ID
        + 消息的两个参数(两个附带信息)
        + 消息产生的时间
        + 消息产生的鼠标位置
    2. 消息的作用  
        当系统通知窗口的时候,就采用消息的方式派发给窗口。
    3. 窗口处理函数  
       当系统通知窗口的时候,会调用窗口处理函数,同时将消息ID和消息参数传递给消息处理函数。
       在窗口处理函数中,不处理消息,使用缺省窗口处理函数。如DefWIndowProc。

        <details>

        ```
        LRESULT CALLBACK WindowProc(
          HWND hwnd,                         //窗口句柄
          UINT  msgID,                       //消息ID
          WPARAM wParam,                     //消息参数
          LPARAM  lParam                     //消息参数
          );    
        ```
    4. 消息相关函数
       <details>

       + GetMessage - 获取消息
        ```
          BOOL GetMessageW(
                _Out_ LPMSG lpMsg,        //存放获取到的消息buffer
                _In_opt_ HWND hWnd,       //窗口句柄
                _In_ UINT wMsgFilterMin,  //获取到消息的最小ID
                _In_ UINT wMsgFilterMax   //获取到消息的最大ID
                );
        ```  

        + TranslateMessage - 翻译消息  
          将按键消息翻译成字符消息,如果不是按键消息直接退出
        ```
          BOOL TranslateMessage(
            _In_ CONST MSG *lpMsg   //要翻译消息的地址             
          );
        ```
    5. 常见消息
        <details>  
        
        + WM_DESTORY - 窗口被销毁的时候产生
          
          >附带信息:  
          >>wParam:0  
          lParam:0
          >
          >常用于窗口销毁时做资源和内存最后处理  
        + WM_SYSCOMMAND - 当窗口点击最大化、最小化、关闭等按钮的时候产生该消息  
          
          >附带信息:  
          >>wParam:具体点击的位置,例如SC_CLOSE等  
          >>lParam:鼠标光标的位置  
          >>>LOWORD(lParam):x坐标  
          >>>HIWORD(lParam):y坐标  
          >
          >常用于窗口关闭的时候,提示用户保存  
        + WM_CREATE - 窗口创建成功,但是还未显示阶段  

          >附带信息:
          >> wParam:0  
          >> lParam:CREATESTRUTC类型指针，该指针可以获取到CreateWindowEx中的全部12个参数信息  
          >  
          >该消息常用于初始化窗口的参数、资源等等,包括创建子窗口  
        + WM_SIZE - 在窗口大小发生变化的时候产生  

          >附带信息:  
          >>wParam:窗口大小变化的原因  
          >>lParam:窗口变化后的大小  
          >>>LOWORD(lparam):变化后的宽度
          >>>HIWORD(lParam):变化后的高度

        + WM_QUIT - 程序员发送  

          >附带信息  
          >> wParam:PostQuitMessage 函数传递的参数  
          >> lParam:0
          >
          >>> 用于结束消息循环,当GetMessage收到这个消息,会返回FALSE,结束while处理,退出消息循环  

        + WM_PAINT - 绘图消息。当窗口需要绘制,且GetMessage未获取到其他消息的时候产生。  
          >附带信息  
          >> wParam:0  
          >> lParam:0  
          >  
          > 该消息专职于绘图。  

      6. 消息循环的原理  
          <details>  

          1. 消息循环的阻塞  
              + GetMessage - 从系统中获取消息,将消息从系统中移除,阻塞函数。当系统中无消息的时候,会等候下一个消息。
              + PeekMessage - 以查看的方式从系统获取消息,可以不将消息从系统中移除,非阻塞函数。当系统无消息的时候,返回FALSE。继续执行代码。
                ```
                  BOOL
                  PeekMessage(
                    _Out_ LPMSG lpMsg,        //消息信息
                    _In_opt_ HWND hWnd,       //窗口句柄
                    _In_ UINT wMsgFilterMin,  //第一个消息
                    _In_ UINT wMsgFilterMax,  //最后一个消息
                    _In_ UINT wRemoveMsg      //移除标志 PM_REMOVE/PM_NOREMOVE
                    );
                ```

          2. 发送消息
               <details>

                + SendMessage - 发送消息,会等候消息处理的结果。
                  ```
                  LRESULT SendMessageW(
                      _In_ HWND hWnd,                             //消息发送的目的窗口
                      _In_ UINT Msg,                              //消息ID
                      _Pre_maybenull_ _Post_valid_ WPARAM wParam, //消息参数
                      _Pre_maybenull_ _Post_valid_ LPARAM lParam  //消息参数
                    );
                  ```

                + PostMessage - 投递消息,消息发送后立即返回,不等待消息的结果。
                  ```
                  LRESULT PostMessage(
                      _In_ HWND hWnd,                             //消息发送的目的窗口
                      _In_ UINT Msg,                              //消息ID
                      _Pre_maybenull_ _Post_valid_ WPARAM wParam, //消息参数
                      _Pre_maybenull_ _Post_valid_ LPARAM lParam  //消息参数
                    );
                  ```
                + 消息分类  
                  <details>

                  + 系统消息-ID范围(0-0x03FF)  
                    由系统定义好的,可以在程序中直接使用  
                  + 用户自定义消息- ID范围(0x0400-0x7FFF)  
                    由用户自己定义的消息,满足用户自己的需求。由用户自己发送消息，并响应处理。  
                    自定义消息宏 WM_USER  
      7. 消息队列  
          <details>  

          1. 消息队列的概念  
              <details>

              + 消息队列是用来存放消息的队列  
              + 消息在队列中先入先出  
              + 所有窗口程序都具有消息队列  
              + 程序可以从消息队列中获取消息  
          2. 消息队列分类  
              <details>

              + 系统消息队列  
                由系统维护的消息队列。存放系统产生的消息,例如鼠标、键盘等。
              + 程序消息队列  
                属于每一个程序(线程)的消息队列。由应用程序(线程)维护。  
          3. 消息和消息队列的关系  
              <details>  

              + 消息和消息队列的关系  
                1. 当鼠标、键盘产生消息时,会将消息存放到系统消息队列。  
                2. 系统会根据存放的信息,找到程序对应的消息队列。 
                3. 将消息投递到程序的消息队列中。  
              
              + 根据消息和消息队列之间的关系,将消息分为两类:
                1. 队列消息 - 消息的发送和获取,都是通过队列完成的。   
                   消息发送后,首先放入消息队列,然后通过消息循环,从队列中获取。  
                   GetMessage - 从消息队列中获取消息。  
                   PostMessage - 将消息投递到消息队列中  
                   常见的队列消息: WM_PAINT、键盘、鼠标、定时器  

                2. 非队列消息 - 消息的发送和获取,是直接调用消息的窗口处理完成。  
                   消息发送时,首先查找消息接收窗口的窗口处理函数,直接调用处理函数,完成消息。  
                   SendMessage - 直接将消息发送给窗口的处理函数,并等候处理结果。  
                   常见消息: WM_CREATE/WM_SIZE等  
                3. 深谈GetMessage  

                   + 在程序(线程)消息队列中查找消息,如果队列有消息,检查消息是否满足指定条件(hWnd,ID)。否则从队列取出消息返回。
                   + 如果程序消息队列没有消息,向系统消息队列获取本程序的消息。如果系统的当前消息属于本程序，系统会将消息队列转发到程序的消息队列中。  
                   + 如果系统的消息队列也没有消息,检查当前程序的所有窗口需要重新绘制的区域,如果有需要绘制的区域,产生WM_PAINT消息,取得消息返回处理。
                   + 如果没有重新绘制的区域,检查定时器,如果有到时的定时器,产生WM_TIMER,返回处理执行。
                   + 如果没有到时的定时器,整理资源、内存等等。  
                   + GetMessage会继续等候下一条消息。PeekMessage会返回FALSE,交出程序的控制权。
                   > 注意:GetMessge获取到的是WM_QUIT,函数会返回FALSE。 
        
      8. WM_Paint消息  
          <details>
            
          1. WM_PAINT - 绘图消息。当窗口需要绘制,且GetMessage未获取到其他消息的时候产生。  
          >附带信息  
          >> wParam:0  
          >> lParam:0  
          >  
          > 该消息专职于绘图。  
             
          2. InvalidateRect函数 - 窗口无效区域,需要重新绘制的区域。  
             ```
              BOOL WINAPI InvalidateRect(
                  _In_opt_ HWND hWnd,           // 窗口句柄
                  _In_opt_ CONST RECT *lpRect,  // 区域的矩形坐标   
                  _In_ BOOL bErase              // 重绘前是否需要擦除  
                  );
             ```
          3. 消息处理步骤   
             1. 开始绘制
                ```
                  HDC WINAPI BeginPaint(
                      _In_ HWND hWnd,             //绘图窗口  
                      _Out_ LPPAINTSTRUCT lpPaint //绘图参数的BUFF  
                      );                          //返回绘图设备句柄HDC  
                ```
              2. 正式绘图   
              3. 结束绘图  
                 ```
                  BOOL WINAPI EndPaint(
                     _In_ HWND hWnd,                  //绘图窗口  
                     _In_ CONST PAINTSTRUCT *lpPaint  //绘图参数的指针BeginPaint  
                     );
                 ```
      9. 键盘消息  
          <details>

          1. WM_KEYDOWN - 按键被按下的时候产生  
          1. WM_KEYUP - 按键被放开的时候产生  
          3. WM_SYSTEMKEYDOWN - 系统按键按下的时候产生,比如(ALT,F10)  
          4. WM_SYSTEMUP - 系统按键放开的时候产生  
              <details>

              > 附带信息  
              >> WPARAM - 按键的virtual key    
              >> LPARAM - 按键的参数,例如按下的次数 
          
          5. 字符消息     
              <details>

              1. TranslateMessage - 在转换WM_KEYDOWN消息时,对于可见字符转换成WM_CHAR消息,不可见字符无此消息  
                  > 附带信息  
                  >> WPARAM : 输入字符的ASCII编码值  
                  >> LPARAM : 按键的相关参数   
      10. 鼠标消息  
          <details>

          1. 鼠标消息的分类
              1. 鼠标基本消息     
                  + WM_LBUTTONDOWN - 鼠标左键按下  
                  + WM_LBUTTONUP - 鼠标左键弹起   
                  + WM_RBUTTONDOWN - 鼠标右键按下  
                  + WM_RBUTTONUP - 鼠标右键弹起  
                  + WM_MOUSEMOVE - 鼠标移动  
                    > 附加消息  
                    >>WPARAM : 其他按键状态,例如Ctrl/shift  
                    >>LPARAM : 鼠标的位置,窗口客户区区域  
                    >>> LOWORD(LPARAM):鼠标X坐标  
                    >>> HIWORD(LPARAM):鼠标Y坐标    

                  一般情况下鼠标按下/抬起成对出现。在鼠标移动过程中,会根据移动速度产生一系列MOUSMOVE消息。  

              1. 双击消息  
                  + WM_LBUTTONDBCLICK - 鼠标左键双击  
                  + WM_RBUTTONDBCLICK - 鼠标右键双击

                    > 附加消息:  
                    >>WPARAM : 其他按键状态,例如Ctrl/shift  
                    >>LPARAM : 鼠标的位置,窗口客户区区域  
                    >>> LOWORD(LPARAM):鼠标X坐标  
                    >>> HIWORD(LPARAM):鼠标Y坐标      
                   
                    >消息产生顺序(左键为例):  
                    >>WM_LBUTTONDOWN                 
                    >>WM_LBUTTONUP                 
                    >>WM_LBUTTONDBCLICK                   
                    >>WM_LBUTTONUP                   

                    使用的时候需要在注册窗口类加上CS_DBLCLKS风格  
              1. 滚轮消息  
                  + WM_MOUSEWHEEL - 鼠标中键滚动  

                    > 附加消息:  
                    >>WPARAM :
                    >>> LOWORD(WPARAM) - 其他按键状态  
                    >>> HIWORD(WPARAM) - 鼠标的偏移量,通过正负值表示滚轮的方向   
                    >>>> 正:向前滚动  
                    >>>> 负:向后滚动 

                    >> LPARAM:鼠标当前的位置,屏幕坐标系  
                    >>> LOWORD(LPARAM) ：X坐标  
                    >>> HOWORD(LPARAM) : Y坐标  
                  + 使用:通过偏移量获取滚动的方向和距离  
      11. 定时器消息  
          <details>   

          1. 定时器的介绍  
            + 产生时间:  
              在程序中创建定时器,当达到时间间隔的时,定时器会发送一个WM_TIMER消息。定时器的精确的是毫秒,
              但是准确度很低。例如设置1000ms,但是会在非1000ms达到消息。

            + 附加消息:  
              + WPARAM:定时器ID 
              + PARAM:定时器处理函数的指针  
          2. SetTimer - 创建定时器  
             
             ```
             WINUSERAPI UINT_PTR WINAPI SetTimer(
              _In_opt_ HWND hWnd,                 //定时器句柄  
              _In_ UINT_PTR nIDEvent,             //定时器ID
              _In_ UINT uElapse,                  //时间间隔  
              _In_opt_ TIMERPROC lpTimerFunc      //定时器函数处理指针(一般不使用,为NULL)
              );                                  //创建成功,返回非0   
             ```
          3. 销毁定时器   
8. ## 菜单资源   
   <details>

   1. 菜单的分类  
      + 窗口的顶层菜单  
      + 弹出菜单  
      + 系统菜单  
      HMENU表示菜单,ID表示菜单项   

   1. 资源相关  

   1. 菜单资源的使用  
      + 添加菜单资源  
      + 加载菜单资源  
        + 注册窗口类的时设置菜单  
        + 创建窗口传参设置菜单  
        + 在主窗口WM_CREATE中利用SetMenu设置菜单  
        ```
          WINUSERAPI HMENU WINAPI  LoadMenuW(
            _In_opt_ HINSTANCE hInstance,     //要处理的模块句柄  
            _In_ LPCWSTR lpMenuName           //菜单名称   
            
            );
        ``` 
   1. WM_COMMAND - 命令消息处理  
      > 附加信息  
      >> 1. WPARAM 
      >>    + HIWORD(WPARAM):对于菜单为0   
      >>    + LOWORD(WPARAM):菜单项的ID  
      >> 1. LPARAM :0 
   1. 菜单项状态  
   1. 上下文菜单  
      1. TrackPopupMenu - 显示上下文菜单  
          该函数是阻塞函数  
          ```
          WINUSERAPI BOOL WINAPI TrackPopupMenu(
              _In_ HMENU hMenu,                   //菜单句柄
              _In_ UINT uFlags,                   //显示方式  
              _In_ int x,                         //水平位置,屏幕坐标系  
              _In_ int y,                         //垂直位置,屏幕坐标系  
              _Reserved_ int nReserved,           //保留,必须0   
              _In_ HWND hWnd,                     //处理菜单窗口的消息句柄  
              _Reserved_ CONST RECT *prcRect      //NULL,忽略  
              );                                  
          ```
      1. WM_RBUTTONUP  
        鼠标右键弹起的是客户区窗口X,Y坐标,需要将其转换为屏幕坐标ClientToScreen  
      1. WM_ContextMenu - 上下文菜单弹出消息,专门处理上下文菜单的消息    
         
         >  附加消息  
         >> WPARAM :右键点击的窗口句柄   
         >> LPARAM :
         >> + LOWORD(LPARAM) - x坐标,屏幕坐标系 
         >> + HIWORD(LPARAM) - y坐标,屏幕坐标系 
1. ## 其他资源   
   <details>

   1. 图标资源  
      + 添加资源   
        注意图标的大小,一个图标文件中,可以有多个不同大小的图标。
      + LoadIcon - 加载图标  
        ```
          WINUSERAPI HICON WINAPI LoadIconW(
            _In_opt_ HINSTANCE hInstance,     //应用程序实例句柄  
           _In_ LPCWSTR lpIconName            //图标资源ID   
           );
        ```
      + 在注册窗口类中进行图标设置     
   1. 光标资源  
      + 添加光标资源  
        光标大小是32x32,每个光标都有HotPot,是当前光标的热点   
      + LoadCursor 加载资源  
        ```
          WINUSERAPI HCURSOR WINAPI LoadCursorW(
           _In_opt_ HINSTANCE hInstance,          //当前应用程序实例句柄  
           _In_ LPCWSTR lpCursorName              //光标资源ID
           );
        ``` 
      + 设置资源  
        + 在注册窗口的时候设置  
        + 调用SetCursor进行设置   
          ```
            WINUSERAPI HCURSOR WINAPI SetCursor(
            _In_opt_ HCURSOR hCursor            //光标资源句柄   
            );
          ```
          该函数只能在WM_SETCURSOR消息中进行调用  
        + WM_SETCURSOR  - 鼠标移动的时候就会出现  
          + wParam - 当前使用的光标句柄   
          + lParam   
            + LOWORD(lParam):当前的区域代码(HTCLIENT/HTCAPTION)  
            + HIWORD(lParam):当前鼠标的ID  
   1. 字符串资源  
      + 添加字符串资源  
        添加字符串表,在表中增加字符串   
      + LoadString - 字符资源的使用  
        ```
        WINUSERAPI int WINAPI LoadStringW(
          _In_opt_ HINSTANCE hInstance,                               //应用程序句柄  
          _In_ UINT uID,                                              //字符串资源ID 
          _Out_writes_to_(cchBufferMax,return + 1) LPWSTR lpBuffer,   //存放字符串的BUffer
          _In_ int cchBufferMax                                       //字符串BUFFER长度  
        );                                                            //成功返回字符串长度,失败返回0
        ```
    1. 加速键资源  
       + 添加 资源添加加速键表,增加命令ID对应的加速键  
       + LoadAccelerators - 使用加速键  
         ```
         WINUSERAPI HACCEL WINAPI LoadAccelerators(
            _In_opt_ HINSTANCE hInstance,            //应用程序实例句柄  
            _In_ LPCWSTR lpTableName                 //加速键表名称  
         );                                          //返回加速键表名称  
         ```
       +  翻译加速表  
          
          ```
          WINUSERAPI int WINAPI TranslateAcceleratorW(
                _In_ HWND hWnd,                       //处理消息的窗口句柄  
                _In_ HACCEL hAccTable,                //加速键表句柄  
                _In_ LPMSG lpMsg                      //消息
          );                                          //如果是加速键,返回非零。
          ```  
          加速键应该放在TranslateMessage前面。           

10. ## 绘图资源  
    <details>  

    1. 绘图基础         
        + 绘图设备DC(Device Context),绘图上下文描述表   
        + HDC - DC句柄,表示绘图设备   
        + GDI - (windows graphics device interface)Windows API绘图接口  
        + 颜色 - 计算机使用红(R)、绿(G)、蓝(B)每个点使用3个字节24位保存(0-2<sup>24</sup>-1)  
    1. 颜色的使用  
        + COLORREF - 实际DWORD,如COLORREF nColor=0  
        + 赋值使用RGB宏,如nColor=RGB(0,0,255);   
        + 获取RGB值 GetRValue/GetGValue/GetBValue  
          BYTE nRed=GetRValue(nColor);  
    1. 基本绘图函数   
        <details>

        + 设置指定点颜色  
          ```
          COLORREF SetPixel(
              HDC hdc,          //设置DC
              int x,            //x坐标
              int y,            //y坐标  
              COLORREF crColor  //设置的颜色 
          )                     //返回原来的颜色  
          ```
        + 线的使用(直线、弧线)  
          MoveToEx - 指明窗口当前点  
          LineTo  - 从窗口当前点到指定点绘制一条直线  
          当前点 : 上一次点绘图时的最后一个点,初始点(0,0)点。  
        + 封闭图形 - 能够用画刷填充的图形     
          Retangle/Ellipse   
        + GDI的绘图对象  
          1. 画笔
             + 画笔的作用  
               描述线的颜色、线型、线粗。  
               HPEN - 画笔的句柄。
             + 画笔的使用  
               1. 创建画笔  
               ```
               WINGDIAPI HPEN    WINAPI CreatePen( 
                _In_ int iStyle,                    //画笔的样式  
                _In_ int cWidth,                    //画笔的宽度 
                _In_ COLORREF color                 //画笔的颜色  
                );                                  //返回画笔句柄  
               ```
                  PS_SOILD - 实心线,可以支持多个像素宽,其他线性只能支持一个像素宽。  
               2. 将画笔应用到DC中  
                  ```
                   WINGDIAPI HGDIOBJ WINAPI SelectObject(
                    _In_ HDC hdc,                         //绘图设备  
                     _In_ HGDIOBJ h                       //GDI绘图设备句柄,画笔句柄   
                     );                                   //返回原来绘图对象的句柄,用于保存  
                  ```
                3. 绘图  
                4. 取出DC中的画笔  
                   将原来的画笔,使用selectObject重新放入DC中,并获取新样式的画笔,恢复案发现场  
                5. 释放画笔  
                   ```
                   WINGDIAPI BOOL WINAPI DeleteObject(
                       _In_ HGDIOBJ ho  //需要释放的绘图对象 
                       );
                   ``` 
                  只能删除不被DC使用的画笔,所以在释放前,必须将画笔从DC中取出.  
            2. 画刷 
               + 作用:给封闭图形填充图案   
                 HBRUSH 画刷句柄  
               + 画刷的使用,与画笔类似  
                 1. 创建画刷  
                    CreateSolidBrush - 创建实心画刷    
                    CreateHateBrush -创建纹理画刷  
                 2. 将画刷应用到DC中,selectObejct
                 3. 绘图  
                 4. 将画刷从DC中取出  
                 5. 删除画刷  
               + 其他  
                 + GetStockObject可以获取到系统画刷,画笔等。 
                   如果不使用画刷填充,可以用NULL_BRUSH参数,获取到不填充的画刷。 
                   GetStockObject返回的画刷不需要DelectObject  
      1. 位图  
         + 位图相关  
           + 光栅图像 - 记录图像每一点的颜色信息。  
           + 矢量图像 - 记录图像的算法,指令等。  
           + HBITMAP - 位图句柄  
         + 位图的使用 
           1. 在资源中添加位图资源  
           2. 从资源中加载位图LoadBitmap  
           3. 创建一个与当前DC相匹配的DC   
              ```
              CreateCompatibleDCWINGDIAPI HDC     WINAPI CreateCompatibleDC(
                   _In_opt_ HDC hdc     //当前设备DC,可以为NULL,使用屏幕DC    
                   );                  //返回创建好的DC句柄  

              ```        
            4. 使用SelectObject将位图载入内存DC中  
            5. 成像(1:1)  
            ```
             WINGDIAPI BOOL  WINAPI BitBlt( //1:1成像   
                    _In_ HDC hdc,           //目的DC
                    _In_ int x,             //目的左上角X坐标  
                    _In_ int y,             //目的左上角Y坐标
                    _In_ int cx,            //目的的宽度  
                    _In_ int cy,            //目的的高度   
                    _In_opt_ HDC hdcSrc,    //源DC   
                    _In_ int x1,            //源左上角X坐标  
                    _In_ int y1,            //源左上角Y坐标  
                    _In_ DWORD rop          //成像方式  
                    );
            ```  
            ```
             WINGDIAPI BOOL  WINAPI StretchBlt( //缩放成像  
                _In_ HDC hdcDest,               //目标设备上下文的句柄。
                _In_ int xDest,                //目标矩形左上角的 x 坐标（以逻辑单位为单位）。
                _In_ int yDest,                //目标矩形左上角的 y 坐标（以逻辑单位为单位）。
                _In_ int wDest,                //目标矩形的宽度（以逻辑单元表示）。
                _In_ int hDest,                //目标矩形的高度（以逻辑单元表示）。
                _In_opt_ HDC hdcSrc,           //源设备上下文的句柄。
                _In_ int xSrc,                 //源矩形左上角的 x 坐标（以逻辑单位为单位）。
                _In_ int ySrc,                  //源矩形左上角的 y 坐标（以逻辑单位为单位）。
                _In_ int wSrc,                  //源矩形的宽度（以逻辑单元表示）。
                _In_ int hSrc,                  //源矩形的高度（以逻辑单元表示）。
                _In_ DWORD rop                  //要执行的光栅操作。 
                );
            ```

            6. 取出位图SelectObject  
            7. 释放位图DeleteObject  
            8. 释放虚拟DC DeleteDC    
    1. 字符串绘制 
        + TextOut  

          ```
           WINGDIAPI BOOL  WINAPI TextOutW(
             _In_ HDC hdc,                  //设备hdc   
             _In_ int x,                    //绘制开始X坐标  
             _In_ int y,                    //绘制开始Y坐标 
             _In_reads_(c) LPCWSTR lpString,//要绘制的字符串  
             _In_ int c                     //指向字符串的长度  
             );
          ``` 
        + DrawText
          ```
          int DrawTextW(
            [in]      HDC     hdc,        //设备上下文的句柄。
            [in, out] LPCWSTR lpchText,   //指向指定要绘制的文本的字符串的指针。
            [in]      int     cchText,    //字符串的长度
            [in, out] LPRECT  lprc,       //指向 RECT 结构的指针
            [in]      UINT    format      //设置文本格式的方法。
            );
          ```

        + 文字的颜色和背景  
          文字颜色 : SetTextColor  
          文字背景 : SetBkColor  
          文字背景模式 : SetBkMode(OPAQUE/TRANSPARENT)  

        + 字体  
          + 字体相关  
            Windows常用字体格式为TrueType格式的字体文件   
            HFONT-字体句柄  
          + 字体的使用  
            1. 创建字体  
              ```
                HFONT CreateFontW(
                  [in] int     cHeight,      //字体高度
                  [in] int     cWidth,       //字体宽度
                  [in] int     cEscapement,  //字符串倾斜度 
                  [in] int     cOrientation, //字符串旋转角度  
                  [in] int     cWeight,      //字体粗细 
                  [in] DWORD   bItalic,      //斜体 
                  [in] DWORD   bUnderline,   //字符下划线  
                  [in] DWORD   bStrikeOut,   //删除线  
                  [in] DWORD   iCharSet,     //字符集  
                  [in] DWORD   iOutPrecision,//输出精度  
                  [in] DWORD   iClipPrecision,//剪切精度  
                  [in] DWORD   iQuality,      //输出质量  
                  [in] DWORD   iPitchAndFamily,//匹配字体  
                  [in] LPCWSTR pszFaceName    //字体名称    
              );
              ```
1. ## 对话框  
   <details>

   + 对话框分类  
     模式对话框 - 当对话框显示的的时候,会禁止其他对话框和用户交互  
     无模式对话框 - 当对话框显示的时候,其他窗口仍然可以进行交互 

   + 对话框的基本使用  
     1. 对话框的处理函数  
     2. 注册窗口类(不使用)  
     3. 创建对话框  
     4. 对话框关闭  
   + 对话框处理函数(并非真正的对话框处理函数)  
     ```
     INT_PTR CALLBACK DialogProc(
        HWND hwndDlg,         //窗口句柄  
        UINT uMsg,            //消息ID  
        WPARAM wParam,        //消息参数  
        LPARAM lParam         //消息参数  
     );                       //返回TRUE,缺省函数不需要处理。返回FALSE,交给缺省函数处理。不需要调用缺省对话框处理函数，
     ```
    + 模式对话框  
      + 创建对话框 - DialogBox  
        ```
        void DialogBoxA(
          [in, optional] HINSTANCE hInstance,   //应用程序实例句柄  
          [in]           LPCTSTR lpTemplate,    //对话框资源  
          [in, optional] HWND hWndParent,       //对话框父窗口  
          [in, optional] DLGPROC lpDialogFunc   //自定义函数  
        );
         ```
      DialogBox是一个阻塞函数,只有当对话框关闭后,才会返回,继续执行后续代码,返回值是通过EndDialog设置  
      + 关闭模式对话框  
        ```
        BOOL EndDialog(
        [in] HWND    hDlg,
        [in] INT_PTR nResult
        );
        ```
        关闭模式对话框,只能使用EndDialog,不能使用DestoryWindow等函数。nResult是DialogBox退出返回值(DestoryWindow只能销毁窗口,但是不能解除阻塞)  
        WM_INITDIALOG产生时机为对话框创建之后,显示之前,通知对话框显示窗口,可以完成自己的初始化工作,对标普通窗口WM_CREATE  
    + 无模式对话框  
        + 创建无模式对话框 
          ```
          void CreateDialogW(
            [in, optional] HINSTANCE  hInstance,  //应用程序窗口实例句柄
            [in]          LPCTSTR  lpName,        //模板资源ID
            [in, optional] HWND hWndParent,       //父窗口
            [in, optional] DLGPROC lpDialogFunc   //自定义函数  
            );                                    //非阻塞函数,创建成功返回窗口句柄,需要使用showWindow函数使用对话框  
          ```  
        + 对话框关闭  
          关闭的时候使用DestoryWindow函数,不能使用EndDialog函数    
1. ## 静态库  
      <details>

    + 静态库特点  
      + 运行不存在  
      + 静态库程序被链接到调用程序中  
      + 目标程序的归档  
    + c静态库  
      + c静态库的创建  
        1. 创建一个静态库程序 
        2. 添加库程序,源文件使用C文件   
      + c静态库的使用
        库路径设置,可以使用pragma关键字设置  
        pragma comment(lib,"../lib/clib.lib")  
    + CPP静态库  
      1. C++静态库的创建  
         + C++ 创建一个静态库项目  
         + 添加库程序,源文件使用Cpp  
      2. C++静态库的使用  
        库路径设置,可以使用pragma关键字设置  
        pragma comment(lib,"../lib/clib.lib")  
1. ## 动态库 
      <details>
      
     + 动态库特点 
       1. 运行时独立存在  
       2. 运行时不会链接到程序  
       3. 使用时候加载(使用的时候必须使动态库执行) 
     + 与静态库比较 
       1. 由于运行时,静态库是将代码嵌入到使用程序中,多个程序使用的时候,会有多份代码,所以代码体积会增大,动态库的代码只需要存在一份,其他程序是通过函数地址进行调用,所以代码体积小。
       2. 静态库发生变化后,新的代码需要重新链接到程序中,动态库发生变化后,如果库中函数定义未变化,其他使用DLL的函数不需要重新链接。
     + 动态库的创建  
       1. 创建动态库项目  
       2. 添加库程序  
       3. 库程序导出 - 提供给使用者库中函数等信息 
          1. 声明导出,使用_declspec(dllexport)导出函数,注意动态库编译链接后也会有lib文件,是作为动态库库函数映射使用,与静态库不完全相同。
          1. 模块定义文件.def,例如
              + LIBARY DllFunc //库  
              + EXPORTS //库导出表  
              + Dll_Mul //导出的函数  
       4. 动态库的使用  
          1. 显示链接(程序员自己负责使用动态库执行)  
             1. 定义函数指针类型typedef
             1. 加载动态库
                ```
                HMOUDLE LoadLibry(
                  LPCTSTR lpFileName//动态库文件名或者全路径 
                  )  //返回DLL实例句柄(HINSTANCE)
                ```
              1. 获取函数地址  
                  ```
                  FARPROC GetProcAddress(
                      HMOUDLE hMoudle,     //DLL句柄          
                      LPCSTR lpProcName    //函数名称  
                  )                        //成功返回函数地址       
                  ```
              1. 使用函数  
              1. 卸载动态库  
                  ```
                  BOOL FreeLibary(
                    HMOUDLE hMoudle    //DLL实例句柄  
                  )
                  ```
                 
          1. 动态库隐式链接  
             1. 头文件和函数原型  
                可以在函数原型的前面增加_declspec(dllimport)
             1. 导入动态库的lib文件  
             1. 在程序中使用  
             1. 隐式链接情况,dll文件可以存放的路径  
                + 与执行文件同一目录下 
                + 当前工作目录  
                + Windows目录 
                + Windows/System32目录  
                + Windows/System
                + 环境变量Path指定的目录  
          1. 动态库中封装类  
             + 在类前面增加_declspec(dllexport)定义,如  
               ```
                class _declspec(dllexport) CMath{
                  ...
                }
               ```
             + 通常使用预编译头切换类的导入导出  
               ```
               # ifdef DLLCLASS_EXPORTS
               # define EXT_CLASS   _declspec(dllexport)  //dll 
               # else 
               # define EXT_CLASS _declspec(dllimport)  //使用者 
               # endif
               class  EXT_CLASS CMath{
                ...
               }
               ```
1. ## 线程  
   <details>

   1. 线程基础   
      <details>

      Windows线程是可以执行代码的实例。进程是以线程为单位调度程序。一个程序当中可以有多个线程,实现多任务处理。
      1. windows线程特点  
        1. 线程都具有ID  
        1. 每个线程都具有自己的内存栈  
        1. 同一进程中的线程使用同一内存空间  
      1. 线程的调度  
        将CPU执行的时间划分成时间片,依次根据时间片执行不同的线程。  
        线程轮询:线程A>线程B>线程A...  
    1. 创建线程  
        <details>

       1. 创建线程  
          ```
          HANDLE CreateThread(
            [in, optional]  LPSECURITY_ATTRIBUTES   lpThreadAttributes,   //安全属性 
            [in]            SIZE_T                  dwStackSize,          //线程的栈大小  
            [in]            LPTHREAD_START_ROUTINE  lpStartAddress,       //线程处理函数的线程地址  
            [in, optional]  __drv_aliasesMem LPVOID lpParameter,          //传递给线程处理函数的参数  
            [in]            DWORD                   dwCreationFlags,      //线程的创建方式  
            [out, optional] LPDWORD                 lpThreadId            //创建成功,返回线程的ID  
            );                                                            //创建成功,返回线程的句柄   
          ```
        1. 定义线程的处理函数  
            ```
            DWORD WINAPI ThreadProc(
              LPVOID lpParameter    //创建线程时,传递给线程的参数  
            )
            ```
        1. 销毁线程  
           + 挂起  
             ```
             DWORD SuspendThread(
              HANDLE hThread      //线程句柄  
             )
             ```
           + 唤醒  
              ```
              DOWRD ResumeThread(){
                HANDLE hThread   //线程句柄 
              }
              ```
           + 结束线程  
             + 结束指定线程  
               ```
                BOOL TerminateThread(
                  [in, out] HANDLE hThread,    //线程句柄 
                  [in]      DWORD  dwExitCode  //线程退出码,注意退出码并非无意义,可以通过GetExitCodeThread获取到状态    
                );
               ```
             +  结束函数所在的线程(当前线程)   
                ```
                void ExitThread(
                    [in] DWORD dwExitCode   //退出码   
                );
                ```  
   1. 线程相关操作  
      + 获取当前线程的ID  
        GetCurrentThreadId  
      + 获取当前线程的句柄  
        GetCurrentThread
      + 等候单个线程句柄有信号  
        ```
        VOID WaitForSingleObject(
          HANDLE handle,              //句柄BUFF的地址  
          DWORD  dwMillions           //等候的时间间隔  
        )
        ```
      + 同时等候多个句柄有信号  
        ```
        DWORD WaitForMultipleObjects(
          [in] DWORD        nCount,         //句柄数量  
          [in] const HANDLE *lpHandles,     //句柄buff地址  
          [in] BOOL         bWaitAll,       //等候方式  
          [in] DWORD        dwMilliseconds  //等候时间  
        );                                  
        ```
        > bWaitAll等候方式:  
          TRUE - 表示所有句柄有信号,才结束等候   
          FALSE - 表示句柄中只要有一个有信号,就结束等候   
   1. 线程的同步操作  
      + 原子锁  
        + 相关问题  
          多个线程对同一个数据进行原子操作,会产生结果丢失。比如++运输的时候。  
        + 错误代码分析  
          当线程A执行G_Value++的时候,如果线程切换时间正好是在线程A将值保存到g_Value之前,线程B继续执行g_Value++,那么
          当线程A再次被切换回来之后,会将原来线程A保存的值保存到g_Value上面,线程B的加法操作会被覆盖。
        + 使用原子锁   
          InterlockedIncrement  
          InterlockedDecrement  
          InterlockedCompareExchange  
          InterlockedExchange  
          ......     
          原子锁的实现:直接对内存的所在内存操作,并且在任何一个瞬间只能有一个线程访问  
      + 互斥锁 
        + 相关问题  
          多线程下代码或资源的共享使用  
        + 互斥的使用  
          1. 创建互斥  
             ```
              HANDLE CreateMutexW(
                [in, optional] LPSECURITY_ATTRIBUTES lpMutexAttributes,   //安全属性  
                [in]           BOOL                  bInitialOwner,       //初始的拥有者,TRUE或FALSE
                [in, optional] LPCWSTR               lpName               //命名
              );                                                          //创建成功返回互斥句柄  
             ```
            >互斥特性  
            任何一个时间点上只能一个线程拥有一个互斥,其他线程等待  
          1. 等候互斥  
             WaitFor... 互斥遵循谁先等候谁先获取   
          1. 释放互斥 
             ```
             BOOL ReleaseMutex(
              [in] HANDLE hMutex
             );
             ```
          1. 关闭互斥  
             CloseHandle  
       + 事件  
         + 相关问题 
         程序之间的通知问题  
         + 事件的使用  
           1. 创建事件   
              ```
              HANDLE CreateEventW(
                [in, optional] LPSECURITY_ATTRIBUTES lpEventAttributes, //安全属性
                [in]           BOOL                  bManualReset,//事件复位方式,TRUE手动,FALSE自动
                [in]           BOOL                  bInitialState,//事件初始状态,TRUE为有信号  
                [in, optional] LPCWSTR               lpName        //事件命名  
              );          //创建成功返回事件句柄  
              ```
            1. 等候事件  
               WaitForSingleObject/WaitForMultipleObjects
            1. 触发事件(将信号设置成有信号状态)  
               ```
               BOOL SetEvent(
                  HANDLE hEvent //处理事件  

               )
               ```
            1. 复位事件(将信号设置成无信号状态)  
              BOOL RestEvent(
                HANDLE hEvent //处理事件  
              )
            1. 关闭事件  
               CloseEvent 
            1. 小心事件的死锁   
       + 信号量  
         + 相关问题  
           类似于事件,解决通知相关问题。但提供一个计数器,可以设置次数。  
         + 信号量的使用  
           1. 创建信号量  
              ```
              HANDLE CreateSemaphoreA(
                [in, optional] LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,//安全属性 
                [in]           LONG                  lInitialCount,         //初始化信号量数量 
                [in]           LONG                  lMaximumCount,         //信号量的最大值 
                [in, optional] LPCSTR                lpName                 //命名
              );                                                            //创建成功返回信号量句柄  
              ``` 
           1. 等候信号量  
              WaitFor  每通过一次,信号量信号值减1,知道为0阻塞
           1. 给信号量指定计数值  
              ```
              BOOL ReleaseSemaphore(
                  [in]            HANDLE hSemaphore,    //信号量句柄  
                  [in]            LONG   lReleaseCount, //释放数量  
                  [out, optional] LPLONG lpPreviousCount//释放前原来信号量数量  
                  );
              ```
            1. 关闭句柄  
               CloseHandle  