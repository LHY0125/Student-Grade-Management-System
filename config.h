/**
 * @file config.h
 * @brief 学生成绩管理系统参数配置头文件
 * @note 本文件集中定义了学生成绩管理系统的所有参数配置，便于统一管理和修改
 */

#ifndef CONFIG_H
#define CONFIG_H

// 系统配置参数
#define MAX_STUDENTS 1000           // 最大学生数量
#define MAX_COURSES 10              // 每个学生最多课程数
#define MAX_USERS 50                // 最大用户数量
#define MAX_LOGIN_ATTEMPTS 3        // 最大登录尝试次数

// 字符串长度限制
#define MAX_ID_LENGTH 20            // 学号最大长度
#define MAX_NAME_LENGTH 50          // 姓名最大长度
#define MAX_COURSE_NAME_LENGTH 50   // 课程名称最大长度
#define MAX_USERNAME_LENGTH 30      // 用户名最大长度
#define MAX_PASSWORD_LENGTH 30      // 密码最大长度

// 分数相关配置
#define MIN_SCORE 0.0               // 最低分数
#define MAX_SCORE 100.0             // 最高分数
#define PASS_SCORE 60.0             // 及格分数
#define EXCELLENT_SCORE 90.0        // 优秀分数

// 文件路径配置
#define STUDENTS_FILE "data/students.csv"   // 学生数据文件
#define USERS_FILE "data/users.txt"         // 用户数据文件
#define BACKUP_DIR "backup/"                // 备份目录

// 菜单选项定义
#define MENU_EXIT 0
#define MENU_BASIC_FUNCTIONS 1
#define MENU_STATISTICS 2
#define MENU_ADMIN 3

// 基本功能菜单选项
#define BASIC_BACK 0
#define BASIC_ADD_STUDENT 1
#define BASIC_DELETE_STUDENT 2
#define BASIC_MODIFY_STUDENT 3
#define BASIC_SEARCH_BY_ID 4
#define BASIC_SEARCH_BY_NAME 5
#define BASIC_DISPLAY_ALL 6
#define BASIC_SORT_STUDENTS 7

// 统计功能菜单选项
#define STATS_BACK 0
#define STATS_COURSE_ANALYSIS 1
#define STATS_SCORE_DISTRIBUTION 2
#define STATS_SCORE_RANGES 3
#define STATS_OVERALL_ANALYSIS 4

// 管理功能菜单选项
#define ADMIN_BACK 0
#define ADMIN_ADD_USER 1
#define ADMIN_DELETE_USER 2
#define ADMIN_MODIFY_PASSWORD 3
#define ADMIN_VIEW_USERS 4

// 排序选项
#define SORT_BY_ID 1
#define SORT_BY_NAME 2
#define SORT_BY_TOTAL_SCORE 3
#define SORT_BY_AVERAGE_SCORE 4

// 排序顺序
#define SORT_ASCENDING 1
#define SORT_DESCENDING 2

// 性别定义
#define GENDER_MALE 'M'
#define GENDER_FEMALE 'F'

// 颜色代码（用于美化输出）
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// 系统消息
#define MSG_SUCCESS "操作成功！"
#define MSG_FAILURE "操作失败！"
#define MSG_NOT_FOUND "未找到相关记录！"
#define MSG_INVALID_INPUT "输入无效，请重新输入！"
#define MSG_FILE_ERROR "文件操作错误！"

// 数据结构定义
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

#endif // CONFIG_H