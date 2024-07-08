# C语言贪吃蛇（控制台版）

这是一个简单的控制台版贪吃蛇游戏，使用C语言编写。

## 项目架构

- `main.c`： 主程序
- `game.h`: 游戏主逻辑
- `menu.h`: 菜单显示
- `snake.h`： 贪吃蛇逻辑实现
- `structs.h`: 数据结构定义
- `utils.h`: 工具函数定义
- `settings.h`: 设置项
- `stats.h`: 数据统计
- `macros.h`: 基本宏定义

## TODO
- [x] 添加多平台支持
- [x] 添加游戏菜单
- [x] 可变大小地图
- [x] 随机地形
- [x] 贪吃蛇速度控制
- [x] 步数统计
- [x] 等宽字符
- [ ] Windows性能优化
- [ ] 更友好的设置菜单

## 说明

### 利用CMake构建

#### 1 安装CMake & Tools

从[官网安装](https://cmake.org/download/)。

#### 2 设置VSCode的generator

由于项目使用到了`unistd.h`，在Windows平台上也需要使用MinGW编译。  
可以用以下命令安装：
```bash
choco install mingw
```

然后将VSCode的设置项`cmake.generator`设置为`MinGW Makefiles`.

