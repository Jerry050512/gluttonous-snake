# C语言贪吃蛇（控制台版）

这是一个简单的控制台版贪吃蛇游戏，使用C语言编写。

## 项目架构

- `game.c`： 游戏主程序
- `snake.h`： 贪吃蛇逻辑实现
- `structs.h`: 数据结构定义
- `utils.h`: 工具函数定义

## TODO
- [ ] 添加多平台支持
- [ ] 添加游戏菜单
- [ ] 可变大小地图
- [ ] 随机地形
- [ ] 贪吃蛇速度控制
- [ ] 步数统计
- [ ] 等宽字符

## 说明

### 本地化

为了显示等宽字符，我们需要有中文输出功能，从而在更大的字符集上找到适合当做墙和蛇身体。

```c
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "utils.h"


int main() {
    setlocale(LC_ALL, "");
    clearScreen();
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            if(i < 2 || i > 7 || j < 2 || j > 7) {
                gotoxy(i*2, j);
                wprintf(L"口");
            }
        }
    }
    wprintf(L"\n");
}
```
注意这里用的是`gotoxy(i*x, j);`

编译命令
```bash
gcc test.c utils.c -o test
```

