# 42 Get Next Line 完整实现与测试报告

## 项目概述

本交付依据用户上传的 **Get Next Line subject PDF（Version 10）** 完成，实现了 mandatory 版本与 bonus 多文件描述符版本。源码严格遵循 PDF 中的接口、文件命名和禁止项要求，并按照用户明确要求，本项目及后续项目源码均不添加 42 header。由于 Norminette 3.3.60 将缺失 42 header 固定报告为 `INVALID_HEADER`，本次规范验证采用“除该用户豁免项外不得存在任何其他 Norminette 错误”的判定方式。

## 已实现内容

| 部分 | 文件 | 状态 |
|---|---|---|
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` | 已完成 |
| Bonus | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` | 已完成 |
| 编译 | `-Wall -Wextra -Werror -D BUFFER_SIZE=n` | 已通过 |
| Norminette | 除用户豁免的 `INVALID_HEADER` 外 | 无其他错误 |
| 内存 | Valgrind full leak check | 0 errors，0 leaks |

## 关键实现说明

Mandatory 版本使用一个 `static char *stash` 保存当前文件描述符尚未返回的数据。函数不会预先读取整个文件，而是在缓存中没有换行时按 `BUFFER_SIZE` 分块读取；一旦发现换行，就立即提取当前行并将剩余内容保留到下一次调用。EOF、读取错误、分配失败和空缓存路径都会正确释放内存并返回 `NULL`。

Bonus 版本只使用一个 static 变量，即 `static t_fdlist *fds`。该链表为每个文件描述符保存独立的 `stash`，因此可以交错读取多个 fd 而不会混淆读取进度。当某个 fd 到达 EOF、发生错误或缓存为空时，对应节点会从链表中删除并释放。

## 测试结果

### 编译测试

以下配置均成功编译并通过功能测试：

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=10000000 ...
```

### 功能与边界测试

测试覆盖普通多行文件、无结尾换行、空文件、连续换行、10000 字符长行、无效 fd、标准输入管道以及 bonus 的三个 fd 交错读取。测试输出包括：

```text
MANDATORY TESTS PASSED
BONUS TESTS PASSED
STDIN TEST PASSED
```

### Norminette

由于用户明确要求不添加 42 header，原始 Norminette 输出只包含每个文件的 `INVALID_HEADER`。过滤该豁免项后，不存在任何其他规范错误。原始日志保存为 `norminette_raw.txt`。

### Valgrind

Mandatory、bonus 与 stdin 测试均通过 Valgrind 检查，结果均为：

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

## 交付文件

- `gnl_source.zip`：仅包含 6 个可提交源码与头文件。
- `gnl_tests.zip`：包含测试程序、测试数据、Norminette 原始日志和 Valgrind 日志。
- `DELIVERY.md`：本报告。

## 使用方式

解压源码包后，可按以下方式编译 mandatory 测试：

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line.c get_next_line_utils.c your_main.c
```

编译 bonus 测试：

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line_bonus.c get_next_line_utils_bonus.c your_main.c
```

## 注意事项

这份实现已经通过本地多缓冲区、多边界和内存测试，但 42 正式评估仍可能包含额外隐藏用例。建议你重点理解缓存残留、换行提取、EOF 清理以及 bonus 链表中每个 fd 的独立状态，因为 peer evaluation 很可能会要求你解释这些路径。
