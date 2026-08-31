# Get Next Line 要求摘要（来源：/home/ubuntu/upload/en.subject.pdf，Version 10）

## 通用要求
- C 语言实现，遵守 Norminette；bonus 文件也参与规范检查。
- 不允许意外崩溃、double free 或内存泄漏。
- 编译使用 `cc -Wall -Wextra -Werror -D BUFFER_SIZE=n`。
- 禁止 libft、`lseek()`、全局变量。
- 外部函数仅允许 `read`, `malloc`, `free`。
- 用户特别要求：本项目和以后所有函数不添加 42 header。

## Mandatory
- 文件：`get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`。
- 原型：`char *get_next_line(int fd);`
- 每次调用返回一行；读到 EOF 或错误返回 `NULL`。
- 返回行包含结尾 `\n`，除非 EOF 前没有换行。
- 必须支持普通文件和标准输入。
- 不应一次读取整个文件；遇到换行应尽快返回。
- `BUFFER_SIZE` 可能为 1、42、9999、10000000 等。

## Bonus
- 文件：`get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`。
- 只能使用一个 static 变量。
- 必须同时管理多个 fd，交错读取不能串线。
