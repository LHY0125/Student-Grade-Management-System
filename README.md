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
- **统一类型管理**：v3.0.0版本创建types.h统一管理所有数据结构
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
学生成绩管理系统 (v3.0.0 统一类型管理架构)
├── 用户界面层 (UI Layer)
│   ├── 主菜单 (main_menu.c)
│   └── 学生IO操作 (student_io.c)
├── 业务逻辑层 (Business Layer)
│   ├── 核心处理器 (core_handlers.c)
│   ├── 学生数据管理 (stu_data.c)
│   ├── 学生CRUD操作 (student_crud.c)
│   ├── 学生搜索 (student_search.c)
│   ├── 统计分析 (statistical_analysis.c)
│   └── 用户管理 (user_manage.c)
├── 工具库层 (Utility Layer)
│   ├── IO工具 (io_utils.c)
│   ├── 验证工具 (validation.c)
│   ├── 字符串工具 (string_utils.c)
│   ├── 文件工具 (file_utils.c)
│   ├── 数学工具 (math_utils.c)
│   └── 系统工具 (system_utils.c)
├── 数据访问层 (Data Layer)
│   ├── CSV文件操作
│   └── 数据验证
└── 配置层 (Config Layer)
    ├── 统一类型定义 (types.h) - v3.0.0新增
    ├── 系统配置 (config.h)
    └── 全局变量 (globals.c/h)
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
gcc -o student_system.exe main.c stu_data.c student_crud.c student_search.c user_manage.c main_menu.c student_io.c core_handlers.c statistical_analysis.c io_utils.c validation.c string_utils.c file_utils.c math_utils.c system_utils.c globals.c
```

3. **使用Makefile编译（v3.0.0优化版）**
```bash
make
```

> **注意**: v3.0.0版本在v2.2直接编译模式基础上，进一步优化了类型管理和依赖关系，编译更加高效。

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
Stu_scores_system/ (v3.0.0 统一类型管理结构)
├── 📁 data/                    # 数据文件目录
│   ├── students.csv           # 学生数据（CSV格式）
│   └── users.txt             # 用户数据
├── 📁 backup/                 # 备份目录
├── 📁 MD/                     # 文档目录
│   ├── README.md             # 项目说明
│   └── CSV_FORMAT.md         # CSV格式说明
├── 📁 TXT/                    # 文本文档目录
│   ├── 系统说明文档.txt        # 系统详细说明
│   └── 代码统计报告.txt        # 代码统计分析
├── 📄 main.c                  # 主程序入口
├── 📄 types.h                 # 统一数据类型定义（v3.0.0新增）
├── 📄 config.h                # 系统配置
├── 📄 globals.c/h             # 全局变量
├── 📄 stu_data.c/h            # 学生数据管理
├── 📄 student_crud.c/h        # 学生CRUD操作
├── 📄 student_search.c/h      # 学生搜索功能
├── 📄 student_io.c/h          # 学生IO操作
├── 📄 statistical_analysis.c/h # 统计分析
├── 📄 user_manage.c/h         # 用户管理
├── 📄 main_menu.c/h           # 菜单系统
├── 📄 core_handlers.c/h       # 核心处理器
├── 📄 io_utils.c/h            # IO工具库
├── 📄 validation.c/h          # 验证工具库
├── 📄 string_utils.c/h        # 字符串工具库
├── 📄 file_utils.c/h          # 文件工具库
├── 📄 math_utils.c/h          # 数学工具库
├── 📄 system_utils.c/h        # 系统工具库
├── 📄 Makefile                # 编译配置（v2.2优化版）
└── 📄 要求.txt                # 需求文档
```

## 🛠️ 开发指南

### 代码规范
- 使用C99标准
- 函数命名采用驼峰命名法
- 变量命名使用有意义的英文单词
- 每个函数都有详细的注释说明
- 模块化设计，职责分离

### 添加新功能
1. 在相应的模块文件中添加函数实现
2. 在对应的头文件中添加函数声明
3. 在菜单系统中添加选项
4. 更新配置文件（如需要）
5. 编写测试用例

### 数据结构
```c
typedef struct {
    char studentID[MAX_ID_LENGTH];          // 学号
    char name[MAX_NAME_LENGTH];             // 姓名
    int age;                                // 年龄
    char gender;                            // 性别
    char courses[MAX_COURSES][MAX_COURSE_NAME_LENGTH]; // 课程
    float scores[MAX_COURSES];              // 成绩
    int courseCount;                        // 课程数量
    float totalScore;                       // 总分
    float averageScore;                     // 平均分
} Student;
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
A: 确保所有源文件都在同一目录下，并检查GCC版本是否支持C99标准。

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

**版本**: v3.0.0  
**最后更新**: 2025年  
**状态**: 稳定版本

## 🆕 v3.0.0 更新内容

### 🏗️ 统一类型管理系统
- **types.h创建**：集中管理所有数据结构定义，包括Student、User、CourseStats、ScoreDistribution、StudentRank、OverallStats、StatisticsCache
- **重复定义消除**：移除config.h、globals.h、statistical_analysis.h中的重复结构体定义
- **依赖关系优化**：简化头文件包含关系，避免循环依赖问题

### 🔧 全局变量优化
- **排序参数全局化**：将currentSortCriteria和currentSortOrder移至全局作用域
- **统计缓存全局化**：将statsCache移至全局管理，提升性能和数据一致性
- **架构一致性**：统一全局变量管理策略，提高代码可维护性

### ⚡ 编译和维护性提升
- **编译效率优化**：减少头文件依赖，加快编译速度
- **代码一致性**：统一的数据类型管理，降低维护成本
- **扩展性增强**：为后续功能扩展奠定坚实的架构基础

## 🆕 v2.2.0 更新内容

### 🔧 模块化重构
- **auxiliary.c完全拆分**：原有的辅助功能模块已完全模块化，拆分为6个专门的工具库
- **新增工具库模块**：
  - `io_utils`: 输入输出工具函数
  - `validation`: 数据验证工具函数
  - `string_utils`: 字符串处理工具函数
  - `file_utils`: 文件操作工具函数
  - `math_utils`: 数学计算工具函数
  - `system_utils`: 系统相关工具函数
- **功能模块细分**：
  - `student_crud`: 学生增删改操作
  - `student_search`: 学生查询功能
  - `student_io`: 学生数据输入输出

### ⚡ 编译优化
- **Makefile优化**：采用直接编译模式，不再生成中间.o文件
- **编译效率提升**：简化编译流程，减少文件管理复杂度
- **更清洁的构建**：避免.o文件堆积，保持项目目录整洁

### 📈 代码质量提升
- **模块职责更清晰**：每个模块功能单一，便于维护
- **代码复用性增强**：工具库函数可在多个模块间共享
- **依赖关系优化**：减少模块间的耦合度
