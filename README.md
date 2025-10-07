# 学生成绩管理系统

一个功能完整的C语言学生成绩管理系统，支持学生信息管理、成绩统计分析、用户权限控制等功能。采用高度模块化设计，代码结构清晰，易于维护和扩展。

## 📋 目录

- [功能特性](#功能特性)
- [系统架构](#系统架构)
- [安装与编译](#安装与编译)
- [使用说明](#使用说明)
- [数据格式](#数据格式)
- [项目结构](#项目结构)
- [开发指南](#开发指南)
- [贡献指南](#贡献指南)

## ✨ 功能特性

### 🎯 核心功能
- **学生信息管理**：添加、删除、修改、查询学生信息
- **成绩管理**：支持多门课程成绩录入和管理
- **数据持久化**：CSV格式存储，便于查看和编辑
- **统计分析**：课程分析、成绩分布、排名统计等
- **用户管理**：多用户登录、权限控制

### 🔧 技术特性
- **标准化目录结构**：v4.1.0版本采用业界标准的include/src目录布局
- **统一类型管理**：v4.0.0版本创建types.h统一管理所有数据结构
- **全局变量优化**：排序参数和统计缓存移至全局作用域，提升性能
- **高度模块化**：v2.2版本完成深度模块化重构，功能模块职责清晰
- **工具库分离**：独立的IO、验证、字符串、文件、数学、系统工具模块
- **输入验证**：完善的数据校验机制
- **错误处理**：友好的错误提示和异常处理
- **彩色输出**：美观的控制台界面
- **编译优化**：支持直接编译，无需生成中间.o文件
- **跨平台**：支持Windows、Linux、macOS

## 🏗️ 系统架构

```
学生成绩管理系统 (v4.1.0 标准化目录架构)
├── 用户界面层 (UI Layer)
│   ├── 主菜单 (src/main_menu.c)
│   └── 学生IO操作 (src/student_io.c)
├── 业务逻辑层 (Business Layer)
│   ├── 核心处理器 (src/core_handlers.c)
│   ├── 学生CRUD操作 (src/student_crud.c)
│   ├── 学生搜索 (src/student_search.c)
│   ├── 学生排序 (src/student_sort.c)
│   ├── 统计分析 (src/statistical_analysis.c)
│   └── 用户管理 (src/user_manage.c)
├── 工具库层 (Utility Layer)
│   ├── IO工具 (src/io_utils.c)
│   ├── 验证工具 (src/validation.c)
│   ├── 字符串工具 (src/string_utils.c)
│   ├── 文件工具 (src/file_utils.c)
│   ├── 数学工具 (src/math_utils.c)
│   ├── 系统工具 (src/system_utils.c)
│   └── 安全工具 (src/security_utils.c)
├── 数据访问层 (Data Layer)
│   ├── CSV文件操作
│   └── 数据验证
├── 安装包管理层 (Installer Layer)
│   ├── 安装脚本目录 (installer/)
│   ├── Inno Setup脚本 (installer/installer.iss)
│   ├── NSIS脚本 (installer/installer.nsi)
│   └── 安装包输出 (installer/dist/)
└── 配置层 (Config Layer)
    ├── 头文件目录 (include/) - v4.1.0标准化
    ├── 统一类型定义 (include/types.h)
    ├── 系统配置 (include/config.h)
    └── 全局变量 (include/globals.h)
```

## 🚀 安装与编译

### 环境要求
- GCC编译器 4.8+
- C99标准支持
- 操作系统：Windows/Linux/macOS

### 编译步骤

1. **克隆项目**
```bash
git clone <repository-url>
cd Stu_scores_system
```

2. **使用GCC编译**
```bash
gcc -Wall -Wextra -std=c17 -g -Iinclude -o student_system src/main.c src/core_handlers.c src/file_utils.c src/globals.c src/io_utils.c src/main_menu.c src/math_utils.c src/security_utils.c src/statistical_analysis.c src/string_utils.c src/student_crud.c src/student_io.c src/student_search.c src/student_sort.c src/system_utils.c src/user_manage.c src/validation.c
```

3. **使用Makefile编译（v4.0.0优化版）**
```bash
make
```

> **注意**: v4.0.0版本在v2.2直接编译模式基础上，进一步优化了类型管理和依赖关系，编译更加高效，并增强了系统安全性。

4. **运行程序**
```bash
./student_system.exe    # Windows
./student_system        # Linux/macOS
```

## 📖 使用说明

### 登录系统
系统提供两个默认用户：
- **管理员**：用户名 `admin`，密码 `123456`（拥有所有权限）
- **教师**：用户名 `teacher`，密码 `password`（基本权限）

### 主要功能

#### 1. 基本功能管理
- **添加学生**：录入学生基本信息和课程成绩
- **删除学生**：根据学号删除学生记录
- **修改学生**：更新学生信息和成绩
- **查询学生**：按学号或姓名查找学生
- **显示所有学生**：列出所有学生信息
- **排序功能**：按学号、姓名、总分、平均分排序

#### 2. 统计分析功能
- **课程分析**：各科目成绩统计
- **成绩分布**：分数段分布统计
- **成绩区间**：优秀、良好、及格、不及格统计
- **综合分析**：整体成绩概况

#### 3. 管理功能（仅管理员）
- **用户管理**：添加、删除用户
- **密码修改**：修改用户密码
- **权限控制**：管理用户权限级别

## 📊 数据格式

### CSV文件结构
学生数据以CSV格式存储在 `data/students.csv`：

```csv
学号,姓名,年龄,性别,课程数量,课程1,成绩1,课程2,成绩2,...,总分,平均分
2021001,张三,20,M,3,数学,85.50,英语,92.00,物理,78.50,258.00,86.00
```

### 用户数据
用户信息存储在 `data/users.txt`：
```
用户名:密码:权限级别
admin:123456:1
teacher:password:0
```

详细格式说明请参考：[CSV格式文档](../CSV_FORMAT.md)

## 📁 项目结构

```
Stu_scores_system/ (v4.1.0 标准化目录结构)
├── 📁 data/                   # 数据文件目录
│   ├── students.csv          # 学生数据（CSV格式）
│   └── users.txt            # 用户数据
├── 📁 include/               # 头文件目录
│   ├── config.h             # 系统配置
│   ├── core_handlers.h      # 核心处理器
│   ├── file_utils.h         # 文件操作工具库
│   ├── globals.h            # 全局变量管理
│   ├── io_utils.h           # IO工具库
│   ├── main_menu.h          # 菜单系统
│   ├── math_utils.h         # 数学计算工具库
│   ├── security_utils.h     # 安全工具库
│   ├── statistical_analysis.h # 统计分析功能
│   ├── string_utils.h       # 字符串工具库
│   ├── student_crud.h       # 学生CRUD操作
│   ├── student_io.h         # 学生IO操作
│   ├── student_search.h     # 学生搜索功能
│   ├── student_sort.h       # 学生排序功能
│   ├── system_utils.h       # 系统工具库
│   ├── types.h              # 统一数据类型定义
│   ├── user_manage.h        # 用户管理
│   └── validation.h         # 数据验证工具库
├── 📁 installer/             # 安装包管理目录
│   ├── installer.iss        # Inno Setup安装脚本
│   ├── installer.nsi        # NSIS安装脚本
│   └── 📁 dist/             # 安装包输出目录
│       ├── StudentGradeSystem_Inno_Setup.exe  # Inno Setup安装包
│       └── StudentGradeSystem_NSIS_Setup.exe  # NSIS安装包
├── 📁 src/                   # 源文件目录
│   ├── core_handlers.c      # 核心处理器
│   ├── file_utils.c         # 文件操作工具库
│   ├── globals.c            # 全局变量管理
│   ├── io_utils.c           # IO工具库
│   ├── main.c               # 主程序入口
│   ├── main_menu.c          # 菜单系统
│   ├── math_utils.c         # 数学计算工具库
│   ├── security_utils.c     # 安全工具库
│   ├── statistical_analysis.c # 统计分析功能
│   ├── string_utils.c       # 字符串工具库
│   ├── student_crud.c       # 学生CRUD操作
│   ├── student_io.c         # 学生IO操作
│   ├── student_search.c     # 学生搜索功能
│   ├── student_sort.c       # 学生排序功能
│   ├── system_utils.c       # 系统工具库
│   ├── user_manage.c        # 用户管理
│   └── validation.c         # 数据验证工具库
├── 📁 MD/                    # 文档目录
│   └── CSV_FORMAT.md        # CSV格式说明
├── 📁 TXT/                   # 文本文档目录
│   ├── 系统说明文档.txt       # 系统详细说明
│   ├── 代码统计报告.txt       # 代码统计分析
│   └── 要求.txt             # 需求文档
├── 📄 .gitignore             # Git忽略文件配置
├── 📄 LICENSE                # 许可证文件
├── 📄 Makefile               # 编译配置（v4.1.0优化版）
├── 📄 README.md              # 项目说明文档
└── 📄 student_system.exe     # 编译生成的可执行文件
```

## 🛠️ 开发指南

### 代码规范
- 使用C99标准
- 函数命名采用驼峰命名法
- 变量命名使用有意义的英文单词
- 每个函数都有详细的注释说明
- 模块化设计，职责分离

### 添加新功能
1. 在 `src/` 目录的相应模块文件中添加函数实现
2. 在 `include/` 目录的对应头文件中添加函数声明
3. 在菜单系统中添加选项
4. 更新配置文件（如需要）
5. 使用 `make clean && make` 重新编译
6. 编写测试用例

### 目录结构说明
- **src/**：存放所有 `.c` 源文件，包含函数的具体实现
- **include/**：存放所有 `.h` 头文件，包含函数声明和数据结构定义
- **data/**：存放程序运行时的数据文件（CSV、TXT等）
- **MD/**：存放Markdown格式的文档文件
- **TXT/**：存放文本格式的说明文档

### 核心数据结构

#### 学生信息结构体
```c
typedef struct {
    char studentID[MAX_ID_LENGTH];          // 学号
    char name[MAX_NAME_LENGTH];             // 姓名
    int age;                                // 年龄
    char gender;                            // 性别 ('M'/'F')
    char courses[MAX_COURSES][MAX_COURSE_NAME_LENGTH]; // 课程名称
    float scores[MAX_COURSES];              // 各科成绩
    int courseCount;                        // 课程数量
    float totalScore;                       // 总分
    float averageScore;                     // 平均分
} Student;
```

#### 用户信息结构体
```c
typedef struct {
    char username[MAX_USERNAME_LENGTH];     // 用户名
    char password[MAX_PASSWORD_LENGTH];     // 密码
    bool isAdmin;                           // 是否为管理员
} User;
```

#### 统计分析结构体
```c
// 课程统计信息
typedef struct {
    int studentCount;                       // 学生人数
    float maxScore;                         // 最高分
    float minScore;                         // 最低分
    float totalScore;                       // 总分
    float averageScore;                     // 平均分
    float passRate;                         // 及格率
} CourseStats;

// 分数分布统计
typedef struct {
    int excellent;                          // 优秀(90-100分)
    int good;                               // 良好(80-89分)
    int medium;                             // 中等(70-79分)
    int pass;                               // 及格(60-69分)
    int fail;                               // 不及格(0-59分)
} ScoreDistribution;

// 总体统计信息
typedef struct {
    int totalStudents;                      // 学生总数
    int maleCount;                          // 男生人数
    int femaleCount;                        // 女生人数
    float averageAge;                       // 平均年龄
    float highestAverage;                   // 最高平均分
    float lowestAverage;                    // 最低平均分
    float overallAverageScore;              // 总体平均分
    float standardDeviation;                // 标准差
    int totalCourses;                       // 课程总数
    float averageCoursesPerStudent;         // 人均课程数
} OverallStats;
```

## 🔧 配置说明

### 系统参数（config.h）
```c
#define MAX_STUDENTS 1000           // 最大学生数量
#define MAX_COURSES 10              // 每个学生最多课程数
#define MAX_USERS 50                // 最大用户数量
#define MAX_LOGIN_ATTEMPTS 3        // 最大登录尝试次数
```

### 文件路径
```c
#define STUDENTS_FILE "data/students.csv"   // 学生数据文件
#define USERS_FILE "data/users.txt"         // 用户数据文件
#define BACKUP_DIR "backup/"                // 备份目录
```

## 🚨 注意事项

1. **数据安全**：定期备份数据文件
2. **权限管理**：谨慎分配管理员权限
3. **输入验证**：系统会自动验证输入数据的合法性
4. **文件编码**：CSV文件使用UTF-8编码，支持中文
5. **并发访问**：当前版本不支持多用户同时操作

## 🐛 常见问题

### Q: 编译时出现错误怎么办？
A: 确保源文件在 `src/` 目录下，头文件在 `include/` 目录下，并检查GCC版本是否支持C17标准。使用 `make clean && make` 重新编译。

### Q: 数据文件损坏怎么办？
A: 可以从backup目录恢复备份文件，或者手动编辑CSV文件修复数据。

### Q: 忘记管理员密码怎么办？
A: 可以直接编辑 `data/users.txt` 文件重置密码。

### Q: 如何导入现有的学生数据？
A: 按照CSV格式要求编辑 `data/students.csv` 文件，程序会自动读取。

## 🤝 贡献指南

欢迎提交Issue和Pull Request！

1. Fork本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启Pull Request

## 📄 许可证

本项目采用MIT许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 👥 作者

- **开发者** - 学生成绩管理系统
- **联系方式** - [3364451258@qq.com]

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者！

---

**版本**: v4.2.0  
**最后更新**: 2025年  
**状态**: 稳定版本

## 🆕 v4.2.0 更新内容

### 📁 标准化目录结构
- **目录重组**：将源文件和头文件分别组织到 `src/` 和 `include/` 目录
- **编译优化**：更新 Makefile 以支持新的目录结构，添加 `-Iinclude` 编译选项
- **项目标准化**：采用业界标准的C项目目录布局，提升项目专业性
- **维护性提升**：清晰的文件组织结构，便于代码管理和团队协作

### 🔧 编译系统改进
- **GCC命令更新**：编译命令适配新的目录结构，包含完整的编译选项
- **Makefile增强**：支持跨平台编译，Windows兼容性改进
- **文档同步**：README.md项目结构图完全更新，反映最新的目录组织