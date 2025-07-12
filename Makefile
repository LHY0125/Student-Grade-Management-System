# 学生成绩管理系统 Makefile
# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# 目标文件
TARGET = student_system

# 源文件
SOURCES = main.c globals.c auxiliary.c main_menu.c user_manage.c stu_data.c statistical_analysis.c

# 目标文件
OBJECTS = $(SOURCES:.c=.o)

# 头文件
HEADERS = config.h globals.h auxiliary.h main_menu.h user_manage.h stu.data.h statistical_analysis.h

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# 编译源文件
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译文件
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.exe

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