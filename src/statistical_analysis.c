/**
 * @file statistical_analysis.c
 * @brief 统计分析功能实现文件
 * @note 实现各种统计分析功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "statistical_analysis.h"
#include "config.h"
#include "globals.h"
#include "io_utils.h"
#include "math_utils.h"
#include "student_io.h"
#include "student_crud.h"
#include "student_search.h"
#include "student_sort.h"

/**
 * @brief 显示课程统计信息
 * @details 统计并显示所有课程的详细信息，包括每门课程的人数、最高分、最低分、平均分和及格率
 *          自动收集系统中所有不重复的课程名称，并为每门课程计算统计数据
 * @note 显示内容包括：
 *       - 课程名称
 *       - 选课人数
 *       - 最高分、最低分、平均分
 *       - 及格率（基于PASS_SCORE阈值）
 * @warning 如果没有学生数据或课程数据，将显示相应警告信息
 */
void displayCourseStatistics()
{
    clearScreen();
    printHeader("课程统计信息");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    // 收集所有课程名称
    char courses[MAX_STUDENTS * MAX_COURSES][MAX_COURSE_NAME_LENGTH];
    int courseCount = 0;

    for (int i = 0; i < studentCount; i++)
    {
        for (int j = 0; j < students[i].courseCount; j++)
        {
            bool exists = false;
            for (int k = 0; k < courseCount; k++)
            {
                if (strcmp(courses[k], students[i].courses[j]) == 0)
                {
                    exists = true;
                    break;
                }
            }
            if (!exists)
            {
                strncpy(courses[courseCount], students[i].courses[j], MAX_COURSE_NAME_LENGTH - 1);
                courses[courseCount][MAX_COURSE_NAME_LENGTH - 1] = '\0';
                courseCount++;
            }
        }
    }

    if (courseCount == 0)
    {
        printWarning("暂无课程数据！");
        pauseSystem();
        return;
    }

    printf("\n");
    printf("%-14s %-8s %-11s %-11s %-11s %-11s\n",
           "课程名称", "人数", "最高分", "最低分", "平均分", "及格率");
    printf("========================================\n");

    for (int i = 0; i < courseCount; i++)
    {
        CourseStats stats = calculateCourseStats(courses[i]);
        printf("%-12s %-6d %-8.2f %-8.2f %-8.2f %-7.2f%%\n",
               courses[i], stats.studentCount, stats.maxScore,
               stats.minScore, stats.averageScore, stats.passRate);
    }

    pauseSystem();
}

/**
 * @brief 计算课程统计信息
 * @details 计算指定课程的详细统计数据，包括选课人数、分数统计和及格率
 * @param courseName 要统计的课程名称
 * @return CourseStats 包含课程统计信息的结构体
 * @note 统计内容包括：
 *       - studentCount: 选课学生数量
 *       - maxScore, minScore: 最高分和最低分
 *       - totalScore, averageScore: 总分和平均分
 *       - passRate: 及格率（百分比）
 * @warning 如果课程不存在，返回全零的统计结构体
 */
CourseStats calculateCourseStats(const char *courseName)
{
    CourseStats stats = {0};
    float scores[MAX_STUDENTS];
    int count = 0;

    // 收集该课程的所有分数
    for (int i = 0; i < studentCount; i++)
    {
        for (int j = 0; j < students[i].courseCount; j++)
        {
            if (strcmp(students[i].courses[j], courseName) == 0)
            {
                scores[count] = students[i].scores[j];
                count++;
                break;
            }
        }
    }

    if (count == 0)
        return stats;

    stats.studentCount = count;
    stats.maxScore = scores[0];
    stats.minScore = scores[0];
    stats.totalScore = 0;

    int passCount = 0;

    for (int i = 0; i < count; i++)
    {
        if (scores[i] > stats.maxScore)
            stats.maxScore = scores[i];
        if (scores[i] < stats.minScore)
            stats.minScore = scores[i];
        stats.totalScore += scores[i];

        if (scores[i] >= PASS_SCORE)
            passCount++;
    }

    stats.averageScore = stats.totalScore / count;
    stats.passRate = (float)passCount / count * 100;

    return stats;
}

/**
 * @brief 显示分数分布
 * @details 统计并显示学生平均分的分布情况，按分数段进行分类统计
 *          显示各分数段的人数和百分比，以及总体及格情况
 * @note 分数段划分：
 *       - 90-100分：优秀
 *       - 80-89分：良好
 *       - 70-79分：中等
 *       - 60-69分：及格
 *       - 0-59分：不及格
 * @warning 如果没有学生数据，将显示警告信息
 */
void displayScoreDistribution()
{
    clearScreen();
    printHeader("分数分布统计");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    // 使用缓存的分数分布数据
    ScoreDistribution dist = getCachedScoreDistribution();

    printf("\n分数段分布：\n");
    printSeparator();
    printf("90-100分: %d人 (%.2f%%)\n", dist.excellent,
           (float)dist.excellent / studentCount * 100);
    printf("80-89分:  %d人 (%.2f%%)\n", dist.good,
           (float)dist.good / studentCount * 100);
    printf("70-79分:  %d人 (%.2f%%)\n", dist.medium,
           (float)dist.medium / studentCount * 100);
    printf("60-69分:  %d人 (%.2f%%)\n", dist.pass,
           (float)dist.pass / studentCount * 100);
    printf("0-59分:   %d人 (%.2f%%)\n", dist.fail,
           (float)dist.fail / studentCount * 100);

    printf("\n总体统计：\n");
    printf("总人数: %d\n", studentCount);
    printf("及格人数: %d (%.2f%%)\n",
           studentCount - dist.fail,
           (float)(studentCount - dist.fail) / studentCount * 100);
    printf("不及格人数: %d (%.2f%%)\n",
           dist.fail, (float)dist.fail / studentCount * 100);

    pauseSystem();
}

/**
 * @brief 计算分数分布
 * @details 根据学生的平均分计算各分数段的人数分布
 * @return ScoreDistribution 包含各分数段人数的结构体
 * @note 分数段定义：
 *       - excellent: 90-100分
 *       - good: 80-89分
 *       - medium: 70-79分
 *       - pass: 60-69分
 *       - fail: 0-59分
 */
ScoreDistribution calculateScoreDistribution()
{
    ScoreDistribution dist = {0};

    for (int i = 0; i < studentCount; i++)
    {
        float avgScore = students[i].averageScore;

        if (avgScore >= 90)
        {
            dist.excellent++;
        }
        else if (avgScore >= 80)
        {
            dist.good++;
        }
        else if (avgScore >= 70)
        {
            dist.medium++;
        }
        else if (avgScore >= 60)
        {
            dist.pass++;
        }
        else
        {
            dist.fail++;
        }
    }

    return dist;
}

/**
 * @brief 显示学生排名
 * @details 按学生平均分进行降序排序，显示学生排名列表
 *          包括排名、学号、姓名、总分和平均分信息
 * @note 排序规则：按平均分从高到低排序
 * @note 显示格式：排名 | 学号 | 姓名 | 总分 | 平均分
 * @warning 如果没有学生数据，将显示警告信息
 */
void displayStudentRanking()
{
    clearScreen();
    printHeader("学生排名");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    // 使用缓存的排名数据
    StudentRank rankings[MAX_STUDENTS];
    int rankingCount = getCachedStudentRankings(rankings);

    printf("\n");
    // 调整中文表头的对齐格式，考虑中文字符的显示宽度
    printf("%-7s %-12s %-12s %-10s %-8s\n",
           "排名", "学号", "姓名", "总分", "平均分");
    printf("==========================================\n");

    for (int i = 0; i < rankingCount; i++)
    {
        int idx = rankings[i].studentIndex;
        printf("%-5d %-10s %-12s %-8.2f %-8.2f\n",
               i + 1,
               students[idx].studentID,
               students[idx].name,
               students[idx].totalScore,
               students[idx].averageScore);
    }

    pauseSystem();
}

/**
 * @brief 显示系统总体统计
 * @details 显示系统的综合统计信息，包括学生信息统计、成绩统计和课程统计
 *          提供系统整体数据的全面概览
 * @note 统计内容包括：
 *       - 学生信息：总数、性别分布、平均年龄
 *       - 成绩统计：最高/最低/平均分、标准差
 *       - 课程统计：总课程数、平均课程数
 * @warning 如果没有学生数据，将显示警告信息
 */
void displayOverallStatistics()
{
    clearScreen();
    printHeader("系统总体统计");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    // 使用缓存的总体统计数据
    OverallStats stats = getCachedOverallStats();

    printf("\n学生信息统计：\n");
    printSeparator();
    printf("总学生数: %d\n", stats.totalStudents);
    printf("男学生数: %d (%.2f%%)\n", stats.maleCount,
           (float)stats.maleCount / stats.totalStudents * 100);
    printf("女学生数: %d (%.2f%%)\n", stats.femaleCount,
           (float)stats.femaleCount / stats.totalStudents * 100);
    printf("平均年龄: %.1f岁\n", stats.averageAge);

    printf("\n成绩统计：\n");
    printSeparator();
    printf("最高平均分: %.2f\n", stats.highestAverage);
    printf("最低平均分: %.2f\n", stats.lowestAverage);
    printf("全体平均分: %.2f\n", stats.overallAverageScore);
    printf("标准差: %.2f\n", stats.standardDeviation);

    printf("\n课程统计：\n");
    printSeparator();
    printf("总课程数: %d\n", stats.totalCourses);
    printf("平均课程数/人: %.1f\n", stats.averageCoursesPerStudent);

    pauseSystem();
}

/**
 * @brief 计算系统总体统计
 * @details 计算系统的综合统计数据，包括学生、成绩和课程的各项统计指标
 * @return OverallStats 包含系统总体统计信息的结构体
 * @note 计算内容包括：
 *       - 学生统计：总数、性别分布、平均年龄
 *       - 成绩统计：最高/最低/平均分、标准差
 *       - 课程统计：总课程数、人均课程数
 * @note 标准差计算使用总体标准差公式
 */
OverallStats calculateOverallStats()
{
    OverallStats stats = {0};

    if (studentCount == 0)
        return stats;

    stats.totalStudents = studentCount;

    float totalAge = 0;
    float totalAverage = 0;
    int totalCourseCount = 0;

    // 收集所有课程名称
    char courses[MAX_STUDENTS * MAX_COURSES][MAX_COURSE_NAME_LENGTH];
    int uniqueCourseCount = 0;

    stats.highestAverage = students[0].averageScore;
    stats.lowestAverage = students[0].averageScore;

    for (int i = 0; i < studentCount; i++)
    {
        // 性别统计
        if (students[i].gender == GENDER_MALE)
        {
            stats.maleCount++;
        }
        else if (students[i].gender == GENDER_FEMALE)
        {
            stats.femaleCount++;
        }

        // 年龄统计
        totalAge += students[i].age;

        // 成绩统计
        totalAverage += students[i].averageScore;
        totalCourseCount += students[i].courseCount;

        if (students[i].averageScore > stats.highestAverage)
        {
            stats.highestAverage = students[i].averageScore;
        }
        if (students[i].averageScore < stats.lowestAverage)
        {
            stats.lowestAverage = students[i].averageScore;
        }

        // 课程统计
        for (int j = 0; j < students[i].courseCount; j++)
        {
            bool exists = false;
            for (int k = 0; k < uniqueCourseCount; k++)
            {
                if (strcmp(courses[k], students[i].courses[j]) == 0)
                {
                    exists = true;
                    break;
                }
            }
            if (!exists)
            {
                strncpy(courses[uniqueCourseCount], students[i].courses[j], MAX_COURSE_NAME_LENGTH - 1);
                courses[uniqueCourseCount][MAX_COURSE_NAME_LENGTH - 1] = '\0';
                uniqueCourseCount++;
            }
        }
    }

    stats.averageAge = totalAge / studentCount;
    stats.overallAverageScore = totalAverage / studentCount;
    stats.totalCourses = uniqueCourseCount;
    stats.averageCoursesPerStudent = (float)totalCourseCount / studentCount;

    // 计算标准差
    float variance = 0;
    for (int i = 0; i < studentCount; i++)
    {
        float diff = students[i].averageScore - stats.overallAverageScore;
        variance += diff * diff;
    }
    variance /= studentCount;
    stats.standardDeviation = sqrt(variance);

    return stats;
}

/**
 * @brief 查找最高分学生
 * @details 查找并显示平均分最高的学生信息
 *          遍历所有学生，找出平均分最高者并显示其详细信息
 * @note 比较依据：学生的平均分（averageScore）
 * @warning 如果没有学生数据，将显示警告信息
 */
void findTopStudent()
{
    clearScreen();
    printHeader("最高分学生");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    int topIndex = 0;
    for (int i = 1; i < studentCount; i++)
    {
        if (students[i].averageScore > students[topIndex].averageScore)
        {
            topIndex = i;
        }
    }

    printf("\n最高平均分学生：\n");
    displayStudentInfo(&students[topIndex]);

    pauseSystem();
}

/**
 * @brief 查找最低分学生
 * @details 查找并显示平均分最低的学生信息
 *          遍历所有学生，找出平均分最低者并显示其详细信息
 * @note 比较依据：学生的平均分（averageScore）
 * @warning 如果没有学生数据，将显示警告信息
 */
void findBottomStudent()
{
    clearScreen();
    printHeader("最低分学生");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    int bottomIndex = 0;
    for (int i = 1; i < studentCount; i++)
    {
        if (students[i].averageScore < students[bottomIndex].averageScore)
        {
            bottomIndex = i;
        }
    }

    printf("\n最低平均分学生：\n");
    displayStudentInfo(&students[bottomIndex]);

    pauseSystem();
}

/**
 * @brief 按课程查找最高分
 * @details 在指定课程中查找并显示最高分学生的信息
 *          用户输入课程名称，系统查找该课程的最高分获得者
 * @note 查找过程：
 *       1. 用户输入课程名称
 *       2. 遍历所有学生的该课程成绩
 *       3. 找出最高分及对应学生
 *       4. 显示学生信息和分数
 * @warning 如果课程不存在，将显示错误信息
 */
void findTopScoreInCourse()
{
    clearScreen();
    printHeader("课程最高分查询");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    char courseName[MAX_COURSE_NAME_LENGTH];
    printf("\n");
    safeInputString("请输入课程名称", courseName, MAX_COURSE_NAME_LENGTH);

    float maxScore = -1;
    int maxIndex = -1;

    for (int i = 0; i < studentCount; i++)
    {
        for (int j = 0; j < students[i].courseCount; j++)
        {
            if (strcmp(students[i].courses[j], courseName) == 0)
            {
                if (students[i].scores[j] > maxScore)
                {
                    maxScore = students[i].scores[j];
                    maxIndex = i;
                }
            }
        }
    }

    if (maxIndex == -1)
    {
        printError("未找到该课程！");
    }
    else
    {
        printf("\n课程 \"%s\" 最高分：\n", courseName);
        printSeparator();
        printf("学号: %s\n", students[maxIndex].studentID);
        printf("姓名: %s\n", students[maxIndex].name);
        printf("分数: %.2f\n", maxScore);
    }

    pauseSystem();
}

/**
 * @brief 计算学生统计信息
 * @details 计算指定学生的总分和平均分
 *          根据学生的所有课程成绩计算统计数据
 * @param student 指向要计算统计信息的学生结构体的指针
 * @note 计算内容：
 *       - totalScore: 所有课程成绩的总和
 *       - averageScore: 平均成绩（总分/课程数）
 * @note 如果学生没有课程，总分和平均分都设为0
 * @warning 传入的student指针不能为NULL
 */
void calculateStudentStats(Student *student)
{
    if (student->courseCount == 0)
    {
        student->totalScore = 0;
        student->averageScore = 0;
        return;
    }

    student->totalScore = 0;
    for (int i = 0; i < student->courseCount; i++)
    {
        student->totalScore += student->scores[i];
    }

    student->averageScore = student->totalScore / student->courseCount;
}

/**
 * @brief 更新全局统计缓存
 * @details 更新系统的全局统计缓存变量，包括全体平均分、最高分和最低分
 *          当学生数据发生变化时调用此函数更新缓存
 * @note 更新的全局变量：
 *       - overallAverageScore: 全体学生平均分
 *       - highestScore: 最高平均分
 *       - lowestScore: 最低平均分
 *       - statsNeedUpdate: 统计更新标志（设为false）
 * @note 如果没有学生数据，所有统计值都设为0
 * @see overallAverageScore, highestScore, lowestScore, statsNeedUpdate
 */
void updateGlobalStats()
{
    if (studentCount == 0)
    {
        overallAverageScore = 0;
        highestScore = 0;
        lowestScore = 0;
        statsNeedUpdate = false;
        return;
    }

    float total = 0;
    highestScore = students[0].averageScore;
    lowestScore = students[0].averageScore;

    for (int i = 0; i < studentCount; i++)
    {
        total += students[i].averageScore;

        if (students[i].averageScore > highestScore)
        {
            highestScore = students[i].averageScore;
        }
        if (students[i].averageScore < lowestScore)
        {
            lowestScore = students[i].averageScore;
        }
    }

    overallAverageScore = total / studentCount;
    statsNeedUpdate = false;
    
    // 使统计缓存无效
    invalidateCache();
}

// ==================== 缓存管理函数实现 ====================

/**
 * @brief 初始化统计缓存
 * @details 初始化统计缓存系统，清空所有缓存数据
 * @note 在系统启动时调用，确保缓存处于干净状态
 */
// 快速排序辅助函数：分区
int partitionRankings(StudentRank arr[], int low, int high) {
    float pivot = arr[high].averageScore;
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        // 降序排列：如果当前元素大于等于基准值
        if (arr[j].averageScore >= pivot) {
            i++;
            StudentRank temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    StudentRank temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// 快速排序主函数
void quickSortRankings(StudentRank arr[], int low, int high) {
    if (low < high) {
        int pi = partitionRankings(arr, low, high);
        quickSortRankings(arr, low, pi - 1);
        quickSortRankings(arr, pi + 1, high);
    }
}

void initStatisticsCache()
{
    statsCache.isValid = false;
    statsCache.lastStudentCount = 0;
    statsCache.lastDataHash = 0;
    memset(&statsCache.overallStats, 0, sizeof(OverallStats));
    memset(&statsCache.scoreDistribution, 0, sizeof(ScoreDistribution));
    memset(statsCache.rankings, 0, sizeof(statsCache.rankings));
}

/**
 * @brief 检查缓存是否有效
 * @details 检查统计缓存是否仍然有效，通过比较学生数量和数据哈希值
 * @return bool 如果缓存有效返回true，否则返回false
 * @note 当学生数据发生变化时，缓存会被标记为无效
 */
bool isCacheValid()
{
    if (!statsCache.isValid) {
        return false;
    }
    
    // 检查学生数量是否变化
    if (statsCache.lastStudentCount != studentCount) {
        return false;
    }
    
    // 检查数据哈希值是否变化
    unsigned long currentHash = calculateDataHash();
    if (statsCache.lastDataHash != currentHash) {
        return false;
    }
    
    return true;
}

/**
 * @brief 更新统计缓存
 * @details 重新计算并更新所有统计缓存数据
 * @note 当缓存无效时调用，重新计算所有统计信息并更新缓存
 * @note 包括总体统计、分数分布和学生排名的缓存更新
 */
void updateStatisticsCache()
{
    if (studentCount == 0) {
        initStatisticsCache();
        return;
    }
    
    // 更新总体统计缓存
    statsCache.overallStats = calculateOverallStats();
    
    // 更新分数分布缓存
    statsCache.scoreDistribution = calculateScoreDistribution();
    
    // 更新学生排名缓存
    for (int i = 0; i < studentCount; i++) {
        statsCache.rankings[i].studentIndex = i;
        statsCache.rankings[i].averageScore = students[i].averageScore;
        statsCache.rankings[i].totalScore = students[i].totalScore;
    }
    
    // 使用快速排序按平均分排序（降序）
    quickSortRankings(statsCache.rankings, 0, studentCount - 1);
    
    // 更新缓存状态
    statsCache.isValid = true;
    statsCache.lastStudentCount = studentCount;
    statsCache.lastDataHash = calculateDataHash();
}

/**
 * @brief 使缓存无效
 * @details 将统计缓存标记为无效，强制下次访问时重新计算
 * @note 当学生数据被修改时调用，确保统计数据的准确性
 */
void invalidateCache()
{
    statsCache.isValid = false;
}

/**
 * @brief 计算数据哈希值
 * @details 计算当前学生数据的哈希值，用于检测数据变化
 * @return unsigned long 当前数据的哈希值
 * @note 基于学生数量、学号、成绩等关键数据计算哈希值
 */
unsigned long calculateDataHash()
{
    unsigned long hash = 5381; // DJB2 哈希算法初始值
    
    // 包含学生数量
    hash = ((hash << 5) + hash) + studentCount;
    
    for (int i = 0; i < studentCount; i++) {
        // 包含学号
        for (int j = 0; students[i].studentID[j] != '\0'; j++) {
            hash = ((hash << 5) + hash) + students[i].studentID[j];
        }
        
        // 包含总分和平均分
        hash = ((hash << 5) + hash) + (unsigned long)(students[i].totalScore * 100);
        hash = ((hash << 5) + hash) + (unsigned long)(students[i].averageScore * 100);
        
        // 包含课程数量
        hash = ((hash << 5) + hash) + students[i].courseCount;
        
        // 包含各科成绩
        for (int j = 0; j < students[i].courseCount; j++) {
            hash = ((hash << 5) + hash) + (unsigned long)(students[i].scores[j] * 100);
        }
    }
    
    return hash;
}

/**
 * @brief 获取缓存的总体统计
 * @details 获取缓存的总体统计数据，如果缓存无效则先更新缓存
 * @return OverallStats 总体统计数据
 * @note 优先使用缓存数据，提高查询效率
 */
OverallStats getCachedOverallStats()
{
    if (!isCacheValid()) {
        updateStatisticsCache();
    }
    return statsCache.overallStats;
}

/**
 * @brief 获取缓存的分数分布
 * @details 获取缓存的分数分布数据，如果缓存无效则先更新缓存
 * @return ScoreDistribution 分数分布数据
 * @note 优先使用缓存数据，避免重复计算
 */
ScoreDistribution getCachedScoreDistribution()
{
    if (!isCacheValid()) {
        updateStatisticsCache();
    }
    return statsCache.scoreDistribution;
}

/**
 * @brief 获取缓存的学生排名
 * @details 获取缓存的学生排名数据，如果缓存无效则先更新缓存
 * @param rankings 输出参数，存储排名数据的数组
 * @return int 返回排名数据的数量
 * @note 排名按平均分降序排列，优先使用缓存数据
 */
int getCachedStudentRankings(StudentRank* rankings)
{
    if (!isCacheValid()) {
        updateStatisticsCache();
    }
    
    if (rankings != NULL && studentCount > 0) {
        memcpy(rankings, statsCache.rankings, studentCount * sizeof(StudentRank));
    }
    
    return studentCount;
}