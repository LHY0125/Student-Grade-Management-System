/**
 * @file statistical_analysis.h
 * @brief 统计分析功能头文件
 * @note 包含各种统计分析功能的函数声明
 */

#ifndef STATISTICAL_ANALYSIS_H
#define STATISTICAL_ANALYSIS_H

#include "types.h"

// 主要统计分析函数

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
void displayCourseStatistics();

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
void displayScoreDistribution();

/**
 * @brief 显示学生排名
 * @details 按学生平均分进行降序排序，显示学生排名列表
 *          包括排名、学号、姓名、总分和平均分信息
 * @note 排序规则：按平均分从高到低排序
 * @note 显示格式：排名 | 学号 | 姓名 | 总分 | 平均分
 * @warning 如果没有学生数据，将显示警告信息
 */
void displayStudentRanking();

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
void displayOverallStatistics();

// 查找功能

/**
 * @brief 查找最高分学生
 * @details 查找并显示平均分最高的学生信息
 *          遍历所有学生，找出平均分最高者并显示其详细信息
 * @note 比较依据：学生的平均分（averageScore）
 * @warning 如果没有学生数据，将显示警告信息
 */
void findTopStudent();

/**
 * @brief 查找最低分学生
 * @details 查找并显示平均分最低的学生信息
 *          遍历所有学生，找出平均分最低者并显示其详细信息
 * @note 比较依据：学生的平均分（averageScore）
 * @warning 如果没有学生数据，将显示警告信息
 */
void findBottomStudent();

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
void findTopScoreInCourse();

// 计算函数

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
CourseStats calculateCourseStats(const char* courseName);

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
ScoreDistribution calculateScoreDistribution();

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
OverallStats calculateOverallStats();

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
void calculateStudentStats(Student* student);

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
void updateGlobalStats();

// 缓存管理函数

/**
 * @brief 初始化统计缓存
 * @details 初始化统计缓存系统，清空所有缓存数据
 * @note 在系统启动时调用，确保缓存处于干净状态
 */
void initStatisticsCache();

/**
 * @brief 检查缓存是否有效
 * @details 检查统计缓存是否仍然有效，通过比较学生数量和数据哈希值
 * @return bool 如果缓存有效返回true，否则返回false
 * @note 当学生数据发生变化时，缓存会被标记为无效
 */
bool isCacheValid();

/**
 * @brief 更新统计缓存
 * @details 重新计算并更新所有统计缓存数据
 * @note 当缓存无效时调用，重新计算所有统计信息并更新缓存
 * @note 包括总体统计、分数分布和学生排名的缓存更新
 */
void updateStatisticsCache();

/**
 * @brief 使缓存无效
 * @details 将统计缓存标记为无效，强制下次访问时重新计算
 * @note 当学生数据被修改时调用，确保统计数据的准确性
 */
void invalidateCache();

/**
 * @brief 计算数据哈希值
 * @details 计算当前学生数据的哈希值，用于检测数据变化
 * @return unsigned long 当前数据的哈希值
 * @note 基于学生数量、学号、成绩等关键数据计算哈希值
 */
unsigned long calculateDataHash();

/**
 * @brief 获取缓存的总体统计
 * @details 获取缓存的总体统计数据，如果缓存无效则先更新缓存
 * @return OverallStats 总体统计数据
 * @note 优先使用缓存数据，提高查询效率
 */
OverallStats getCachedOverallStats();

/**
 * @brief 获取缓存的分数分布
 * @details 获取缓存的分数分布数据，如果缓存无效则先更新缓存
 * @return ScoreDistribution 分数分布数据
 * @note 优先使用缓存数据，避免重复计算
 */
ScoreDistribution getCachedScoreDistribution();

/**
 * @brief 获取缓存的学生排名
 * @details 获取缓存的学生排名数据，如果缓存无效则先更新缓存
 * @param rankings 输出参数，存储排名数据的数组
 * @return int 返回排名数据的数量
 * @note 排名按平均分降序排列，优先使用缓存数据
 */
int getCachedStudentRankings(StudentRank* rankings);

// 排序优化函数

/**
 * @brief 快速排序分区函数
 * @details 对学生排名数组进行分区操作，用于快速排序
 * @param arr 要分区的学生排名数组
 * @param low 分区的起始索引
 * @param high 分区的结束索引
 * @return int 分区点的索引
 */
int partitionRankings(StudentRank arr[], int low, int high);

/**
 * @brief 快速排序函数
 * @details 对学生排名数组按平均分进行快速排序（降序）
 * @param arr 要排序的学生排名数组
 * @param low 排序的起始索引
 * @param high 排序的结束索引
 */
void quickSortRankings(StudentRank arr[], int low, int high);

#endif // STATISTICAL_ANALYSIS_H