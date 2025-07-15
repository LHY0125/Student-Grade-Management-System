/**
 * @file statistical_analysis.h
 * @brief 统计分析功能头文件
 * @note 包含各种统计分析功能的函数声明
 */

#ifndef STATISTICAL_ANALYSIS_H
#define STATISTICAL_ANALYSIS_H

#include "config.h"

// 课程统计结构体
typedef struct {
    int studentCount;
    float maxScore;
    float minScore;
    float totalScore;
    float averageScore;
    float passRate;
} CourseStats;

// 分数分布结构体
typedef struct {
    int excellent;  // 90-100分
    int good;       // 80-89分
    int medium;     // 70-79分
    int pass;       // 60-69分
    int fail;       // 0-59分
} ScoreDistribution;

// 学生排名结构体
typedef struct {
    int studentIndex;
    float averageScore;
    float totalScore;
} StudentRank;

// 总体统计结构体
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

// 主要统计分析函数
void displayCourseStatistics();             // 显示课程统计信息
void displayScoreDistribution();            // 显示分数分布
void displayStudentRanking();               // 显示学生排名
void displayOverallStatistics();            // 显示系统总体统计

// 查找功能
void findTopStudent();                       // 查找最高分学生
void findBottomStudent();                    // 查找最低分学生
void findTopScoreInCourse();                 // 按课程查找最高分

// 计算函数
CourseStats calculateCourseStats(const char* courseName);
ScoreDistribution calculateScoreDistribution();
OverallStats calculateOverallStats();
void calculateStudentStats(Student* student);
void updateGlobalStats();

#endif // STATISTICAL_ANALYSIS_H