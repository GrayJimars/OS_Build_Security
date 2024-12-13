# 编译
- 首先装载可执行文件，可以在`./command`中执行`sudo make`和`sudo make install`，也可以直接在根目录执行`sudo ./com_install.sh`
- 然后在根目录执行`sudo make image`
- 最后就可以直接`bochs`开启模拟

# 可执行文件
- atk：执行`atk [filename]`可以让被攻击可执行文件无法实现自身功能，并且输出"i m infected!"
- echo：执行`echo [string]`，在终端打印string的内容
- ls：执行`ls`，在终端列出当前目录全部文件
- poc：执行`poc`，在终端显示一连串A，最终显示=>，表示栈溢出
- pwd：执行`pwd`，显示/，表示当前为根目录
- rm：执行`rm [filename]`，删除[filename]文件
- str：执行`str %d,%d,%d,%d,···`，会输出三到四个0之后开输出堆栈区域的内容，说明存在格式化字符串漏洞
- touch：执行`touch [filename]`，创建[filename]文件