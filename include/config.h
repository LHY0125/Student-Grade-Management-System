/**
 * @file config.h
 * @brief 学生成绩管理系统参数配置头文件
 * @note 本文件集中定义了学生成绩管理系统的所有参数配置，便于统一管理和修改
 */

#ifndef CONFIG_H
#define CONFIG_H

// 系统配置参数
// 定义系统中各种实体的数量限制，确保内存使用可控
#define MAX_STUDENTS 1000           // 最大学生数量 - 系统可以存储的学生记录上限
#define MAX_COURSES 10              // 每个学生最多课程数 - 限制单个学生可选修的课程数量
#define MAX_USERS 50                // 最大用户数量 - 系统支持的用户账户上限
#define MAX_LOGIN_ATTEMPTS 3        // 最大登录尝试次数 - 防止暴力破解，超过次数将锁定账户

// 字符串长度限制
// 定义各种字符串字段的最大长度，防止缓冲区溢出并优化内存分配
#define MAX_ID_LENGTH 20            // 学号最大长度 - 包含终止符，实际可用19个字符
#define MAX_NAME_LENGTH 50          // 姓名最大长度 - 支持中文姓名，包含终止符
#define MAX_COURSE_NAME_LENGTH 50   // 课程名称最大长度 - 支持完整的课程名称描述
#define MAX_USERNAME_LENGTH 30      // 用户名最大长度 - 登录系统使用的用户名
#define MAX_PASSWORD_LENGTH 30      // 密码最大长度 - 用户密码的字符数限制

// 分数相关配置
// 定义成绩评价体系的分数范围和等级标准
#define MIN_SCORE 0.0               // 最低分数 - 成绩的下限值
#define MAX_SCORE 100.0             // 最高分数 - 成绩的上限值，采用百分制
#define PASS_SCORE 60.0             // 及格分数 - 判断学生是否通过课程的分数线
#define EXCELLENT_SCORE 90.0        // 优秀分数 - 判断学生成绩是否优秀的分数线

// 年龄相关配置
// 定义学生年龄的合理范围，用于数据验证
#define MIN_AGE 10                  // 最小年龄 - 考虑到最年轻的学生可能年龄
#define MAX_AGE 100                 // 最大年龄 - 考虑到继续教育等特殊情况的年龄上限

// 文件路径配置
// 定义系统使用的数据文件和目录路径
#define STUDENTS_FILE "data/students.csv"   // 学生数据文件 - 存储所有学生信息的CSV格式文件
#define USERS_FILE "data/users.txt"         // 用户数据文件 - 存储系统用户账户信息
#define BACKUP_DIR "backup/"                // 备份目录 - 数据备份文件的存储位置

// 菜单选项定义
// 主菜单的选项编号，用于用户界面导航
#define MENU_EXIT 0                 // 退出系统
#define MENU_BASIC_FUNCTIONS 1      // 基本功能菜单 - 学生信息的增删改查
#define MENU_STATISTICS 2           // 统计分析菜单 - 成绩统计和数据分析
#define MENU_ADMIN 3                // 管理功能菜单 - 用户管理和系统设置

// 基本功能菜单选项
// 学生信息管理的具体操作选项
#define BASIC_BACK 0                // 返回主菜单
#define BASIC_ADD_STUDENT 1         // 添加学生信息
#define BASIC_DELETE_STUDENT 2      // 删除学生记录
#define BASIC_MODIFY_STUDENT 3      // 修改学生信息
#define BASIC_SEARCH_BY_ID 4        // 按学号查找学生
#define BASIC_SEARCH_BY_NAME 5      // 按姓名查找学生
#define BASIC_DISPLAY_ALL 6         // 显示所有学生信息
#define BASIC_SORT_STUDENTS 7       // 学生信息排序功能

// 统计功能菜单选项
// 成绩统计和数据分析的功能选项
#define STATS_BACK 0                // 返回主菜单
#define STATS_COURSE_ANALYSIS 1     // 课程成绩分析 - 分析各门课程的成绩情况
#define STATS_SCORE_DISTRIBUTION 2  // 成绩分布统计 - 显示成绩的分布情况
#define STATS_SCORE_RANGES 3        // 成绩区间统计 - 按分数段统计学生人数
#define STATS_OVERALL_ANALYSIS 4    // 综合分析 - 整体成绩趋势和统计信息

// 管理功能菜单选项
// 系统管理员专用的用户管理功能
#define ADMIN_BACK 0                // 返回主菜单
#define ADMIN_ADD_USER 1            // 添加新用户账户
#define ADMIN_DELETE_USER 2         // 删除用户账户
#define ADMIN_MODIFY_PASSWORD 3     // 修改用户密码
#define ADMIN_VIEW_USERS 4          // 查看所有用户信息

// 排序选项
// 定义学生信息的排序依据
#define SORT_BY_ID 1                // 按学号排序
#define SORT_BY_NAME 2              // 按姓名排序
#define SORT_BY_TOTAL_SCORE 3       // 按总分排序
#define SORT_BY_AVERAGE_SCORE 4     // 按平均分排序

// 排序顺序
// 定义排序的方向
#define SORT_ASCENDING 1            // 升序排列 - 从小到大
#define SORT_DESCENDING 2           // 降序排列 - 从大到小

// 性别定义
// 使用字符常量表示学生性别，便于数据存储和处理
#define GENDER_MALE 'M'             // 男性标识
#define GENDER_FEMALE 'F'           // 女性标识

// 颜色代码（用于美化输出）
// ANSI转义序列，用于在终端中显示彩色文本，提升用户体验
#define COLOR_RESET "\033[0m"       // 重置颜色 - 恢复默认颜色
#define COLOR_RED "\033[31m"        // 红色 - 通常用于错误信息
#define COLOR_GREEN "\033[32m"      // 绿色 - 通常用于成功信息
#define COLOR_YELLOW "\033[33m"     // 黄色 - 通常用于警告信息
#define COLOR_BLUE "\033[34m"       // 蓝色 - 通常用于信息提示
#define COLOR_MAGENTA "\033[35m"    // 洋红色 - 用于特殊标记
#define COLOR_CYAN "\033[36m"       // 青色 - 用于标题或重要信息
#define COLOR_WHITE "\033[37m"      // 白色 - 用于普通文本

// 系统消息
// 预定义的系统提示信息，保证消息的一致性和易于维护
#define MSG_SUCCESS "操作成功！"           // 操作成功时的提示信息
#define MSG_FAILURE "操作失败！"           // 操作失败时的通用错误信息
#define MSG_NOT_FOUND "未找到相关记录！"    // 查询无结果时的提示信息
#define MSG_INVALID_INPUT "输入无效，请重新输入！" // 用户输入格式错误时的提示
#define MSG_FILE_ERROR "文件操作错误！"     // 文件读写操作失败时的错误信息

#endif // CONFIG_H