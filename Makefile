# 学生成绩管理系统 Makefile
# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -g -Iinclude

# 目标文件
TARGET = student_system

# 源文件
SOURCES = src/main.c src/globals.c src/main_menu.c src/user_manage.c src/core_handlers.c src/statistical_analysis.c src/student_io.c src/student_crud.c src/student_search.c src/student_sort.c src/io_utils.c src/validation.c src/string_utils.c src/file_utils.c src/math_utils.c src/system_utils.c src/security_utils.c

# 头文件
HEADERS = include/config.h include/globals.h include/main_menu.h include/user_manage.h include/core_handlers.h include/statistical_analysis.h include/student_io.h include/student_crud.h include/student_search.h include/student_sort.h include/io_utils.h include/validation.h include/string_utils.h include/file_utils.h include/math_utils.h include/system_utils.h include/security_utils.h include/types.h

# 默认目标
all: $(TARGET)

# 直接编译链接（不生成.o文件）
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

# 清理编译文件
clean:
	-del /Q $(TARGET).exe 2>nul
	-del /Q *.exe 2>nul
	-del /Q *.o 2>nul

# 创建必要的目录
setup:
	mkdir -p data
	mkdir -p backup

# 运行程序
run: $(TARGET)
	./$(TARGET)

# Windows 特定目标
windows: CFLAGS += -DWINDOWS
windows: $(TARGET)

# 调试版本
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# 发布版本
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# 安装（可选）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# 帮助信息
help:
	@echo "可用的目标："
	@echo "  all      - 编译程序（默认）"
	@echo "  clean    - 清理编译文件"
	@echo "  setup    - 创建必要的目录"
	@echo "  run      - 编译并运行程序"
	@echo "  windows  - 编译Windows版本"
	@echo "  debug    - 编译调试版本"
	@echo "  release  - 编译发布版本"
	@echo "  install  - 安装程序到系统"
	@echo "  help     - 显示此帮助信息"

.PHONY: all clean setup run windows debug release install help