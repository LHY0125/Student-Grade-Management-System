/**
 * @file types.h
 * @brief 统一的数据类型定义文件
 * @note 集中管理所有结构体定义，提高代码可维护性和一致性
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include "config.h"
#include "security_utils.h"

// 核心数据结构

/**
 * @brief 学生信息结构体
 * @note 包含学生的基本信息、课程和成绩数据
 */
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

/**
 * @brief 用户信息结构体
 * @note 包含用户登录信息和权限设置
 */
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char passwordHash[SHA256_HEX_LENGTH];  // 存储SHA-256哈希值
    bool isAdmin;  // 是否为管理员
} User;

// 统计分析相关结构体

/**
 * @brief 课程统计结构体
 * @note 包含单门课程的统计信息
 */
typedef struct {
    int studentCount;
    float maxScore;
    float minScore;
    float totalScore;
    float averageScore;
    float passRate;
} CourseStats;

/**
 * @brief 分数分布结构体
 * @note 按分数段统计学生人数分布
 */
typedef struct {
    int excellent;  // 90-100分
    int good;       // 80-89分
    int medium;     // 70-79分
    int pass;       // 60-69分
    int fail;       // 0-59分
} ScoreDistribution;

/**
 * @brief 学生排名结构体
 * @note 用于学生排名功能
 */
typedef struct {
    int studentIndex;
    float averageScore;
    float totalScore;
} StudentRank;

/**
 * @brief 总体统计结构体
 * @note 包含系统整体的统计信息
 */
typedef struct {
    int totalStudents;
    int maleCount;
    int femaleCount;
    float averageAge;
    float highestAverage;
    float lowestAverage;
    float overallAverageScore;
    float standardDeviation;
    int totalCourses;
    float averageCoursesPerStudent;
} OverallStats;

/**
 * @brief 统计缓存结构体
 * @note 用于缓存统计计算结果，提高性能
 */
typedef struct {
    bool isValid;                    // 缓存是否有效
    OverallStats overallStats;       // 总体统计缓存
    ScoreDistribution scoreDistribution; // 分数分布缓存
    StudentRank rankings[MAX_STUDENTS];   // 排名缓存
    int lastStudentCount;            // 上次缓存时的学生数量
    unsigned long lastDataHash;     // 数据哈希值，用于检测数据变化
} StatisticsCache;

#endif // TYPES_H