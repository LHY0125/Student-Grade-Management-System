# 学生成绩管理系统 Makefile
# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# 目标文件
TARGET = student_system

# 源文件
SOURCES = main.c globals.c main_menu.c user_manage.c core_handlers.c statistical_analysis.c student_io.c student_crud.c student_search.c student_sort.c io_utils.c validation.c string_utils.c file_utils.c math_utils.c system_utils.c

# 头文件
HEADERS = config.h globals.h main_menu.h user_manage.h core_handlers.h statistical_analysis.h student_io.h student_crud.h student_search.h student_sort.h io_utils.h validation.h string_utils.h file_utils.h math_utils.h system_utils.h

# 默认目标
all: $(TARGET)

# 直接编译链接（不生成.o文件）
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

# 清理编译文件
clean:
	rm -f $(TARGET)
	rm -f *.exe
	rm -f *.o

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