/**
 * @file statistical_analysis.c
 * @brief 统计分析功能实现文件
 * @note 实现各种统计分析功能
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include "statistical_analysis.h"
 #include "config.h"
 #include "globals.h"
 #include "auxiliary.h"
 #include "stu.data.h"
 
 /**
  * @brief 显示课程统计信息
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
     
     for (int i = 0; i < studentCount; i++) {
         for (int j = 0; j < students[i].courseCount; j++) {
             bool exists = false;
             for (int k = 0; k < courseCount; k++) {
                 if (strcmp(courses[k], students[i].courses[j]) == 0) {
                     exists = true;
                     break;
                 }
             }
             if (!exists) {
                 strcpy(courses[courseCount], students[i].courses[j]);
                 courseCount++;
             }
         }
     }
     
     if (courseCount == 0) {
         printWarning("暂无课程数据！");
         pauseSystem();
         return;
     }
     
     printf("\n");
     printf("%-20s %-8s %-8s %-8s %-8s %-8s\n", 
            "课程名称", "人数", "最高分", "最低分", "平均分", "及格率");
     printSeparator();
     
     for (int i = 0; i < courseCount; i++) {
         CourseStats stats = calculateCourseStats(courses[i]);
         printf("%-20s %-8d %-8.2f %-8.2f %-8.2f %-8.2f%%\n",
                courses[i], stats.studentCount, stats.maxScore, 
                stats.minScore, stats.averageScore, stats.passRate);
     }
     
     pauseSystem();
 }
 
 /**
  * @brief 计算课程统计信息
  */
 CourseStats calculateCourseStats(const char* courseName) {
     CourseStats stats = {0};
     float scores[MAX_STUDENTS];
     int count = 0;
     
     // 收集该课程的所有分数
     for (int i = 0; i < studentCount; i++) {
         for (int j = 0; j < students[i].courseCount; j++) {
             if (strcmp(students[i].courses[j], courseName) == 0) {
                 scores[count] = students[i].scores[j];
                 count++;
                 break;
             }
         }
     }
     
     if (count == 0) return stats;
     
     stats.studentCount = count;
     stats.maxScore = scores[0];
     stats.minScore = scores[0];
     stats.totalScore = 0;
     
     int passCount = 0;
     
     for (int i = 0; i < count; i++) {
         if (scores[i] > stats.maxScore) stats.maxScore = scores[i];
         if (scores[i] < stats.minScore) stats.minScore = scores[i];
         stats.totalScore += scores[i];
         
         if (scores[i] >= PASS_SCORE) passCount++;
     }
     
     stats.averageScore = stats.totalScore / count;
     stats.passRate = (float)passCount / count * 100;
     
     return stats;
 }
 
 /**
  * @brief 显示分数分布
  */
 void displayScoreDistribution() {
     clearScreen();
     printHeader("分数分布统计");
     
     if (studentCount == 0) {
         printWarning("暂无学生数据！");
         pauseSystem();
         return;
     }
     
     ScoreDistribution dist = calculateScoreDistribution();
     
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
  */
 ScoreDistribution calculateScoreDistribution() {
     ScoreDistribution dist = {0};
     
     for (int i = 0; i < studentCount; i++) {
         float avgScore = students[i].averageScore;
         
         if (avgScore >= 90) {
             dist.excellent++;
         } else if (avgScore >= 80) {
             dist.good++;
         } else if (avgScore >= 70) {
             dist.medium++;
         } else if (avgScore >= 60) {
             dist.pass++;
         } else {
             dist.fail++;
         }
     }
     
     return dist;
 }
 
 /**
  * @brief 显示学生排名
  */
 void displayStudentRanking() {
     clearScreen();
     printHeader("学生排名");
     
     if (studentCount == 0) {
         printWarning("暂无学生数据！");
         pauseSystem();
         return;
     }
     
     // 创建排名数组
     StudentRank rankings[MAX_STUDENTS];
     for (int i = 0; i < studentCount; i++) {
         rankings[i].studentIndex = i;
         rankings[i].averageScore = students[i].averageScore;
         rankings[i].totalScore = students[i].totalScore;
     }
     
     // 按平均分排序（降序）
     for (int i = 0; i < studentCount - 1; i++) {
         for (int j = 0; j < studentCount - 1 - i; j++) {
             if (rankings[j].averageScore < rankings[j + 1].averageScore) {
                 StudentRank temp = rankings[j];
                 rankings[j] = rankings[j + 1];
                 rankings[j + 1] = temp;
             }
         }
     }
     
     printf("\n");
     // 调整中文表头的对齐格式，考虑中文字符的显示宽度
     printf("%-5s %-10s %-12s %-8s %-8s\n", 
            "排名", "学号", "姓名", "总分", "平均分");
     printf("========================================\n");
     
     for (int i = 0; i < studentCount; i++) {
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
  */
 void displayOverallStatistics() {
     clearScreen();
     printHeader("系统总体统计");
     
     if (studentCount == 0) {
         printWarning("暂无学生数据！");
         pauseSystem();
         return;
     }
     
     OverallStats stats = calculateOverallStats();
     
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
  */
 OverallStats calculateOverallStats() {
     OverallStats stats = {0};
     
     if (studentCount == 0) return stats;
     
     stats.totalStudents = studentCount;
     
     float totalAge = 0;
     float totalAverage = 0;
     int totalCourseCount = 0;
     
     // 收集所有课程名称
     char courses[MAX_STUDENTS * MAX_COURSES][MAX_COURSE_NAME_LENGTH];
     int uniqueCourseCount = 0;
     
     stats.highestAverage = students[0].averageScore;
     stats.lowestAverage = students[0].averageScore;
     
     for (int i = 0; i < studentCount; i++) {
         // 性别统计
         if (students[i].gender == GENDER_MALE) {
             stats.maleCount++;
         } else if (students[i].gender == GENDER_FEMALE) {
             stats.femaleCount++;
         }
         
         // 年龄统计
         totalAge += students[i].age;
         
         // 成绩统计
         totalAverage += students[i].averageScore;
         totalCourseCount += students[i].courseCount;
         
         if (students[i].averageScore > stats.highestAverage) {
             stats.highestAverage = students[i].averageScore;
         }
         if (students[i].averageScore < stats.lowestAverage) {
             stats.lowestAverage = students[i].averageScore;
         }
         
         // 课程统计
         for (int j = 0; j < students[i].courseCount; j++) {
             bool exists = false;
             for (int k = 0; k < uniqueCourseCount; k++) {
                 if (strcmp(courses[k], students[i].courses[j]) == 0) {
                     exists = true;
                     break;
                 }
             }
             if (!exists) {
                 strcpy(courses[uniqueCourseCount], students[i].courses[j]);
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
     for (int i = 0; i < studentCount; i++) {
         float diff = students[i].averageScore - stats.overallAverageScore;
         variance += diff * diff;
     }
     variance /= studentCount;
     stats.standardDeviation = sqrt(variance);
     
     return stats;
 }
 
 /**
  * @brief 查找最高分学生
  */
 void findTopStudent() {
     clearScreen();
     printHeader("最高分学生");
     
     if (studentCount == 0) {
         printWarning("暂无学生数据！");
         pauseSystem();
         return;
     }
     
     int topIndex = 0;
     for (int i = 1; i < studentCount; i++) {
         if (students[i].averageScore > students[topIndex].averageScore) {
             topIndex = i;
         }
     }
     
     printf("\n最高平均分学生：\n");
     displayStudentInfo(&students[topIndex]);
     
     pauseSystem();
 }
 
 /**
  * @brief 查找最低分学生
  */
 void findBottomStudent() {
     clearScreen();
     printHeader("最低分学生");
     
     if (studentCount == 0) {
         printWarning("暂无学生数据！");
         pauseSystem();
         return;
     }
     
     int bottomIndex = 0;
     for (int i = 1; i < studentCount; i++) {
         if (students[i].averageScore < students[bottomIndex].averageScore) {
             bottomIndex = i;
         }
     }
     
     printf("\n最低平均分学生：\n");
     displayStudentInfo(&students[bottomIndex]);
     
     pauseSystem();
 }
 
 /**
  * @brief 按课程查找最高分
  */
 void findTopScoreInCourse() {
     clearScreen();
     printHeader("课程最高分查询");
     
     if (studentCount == 0) {
         printWarning("暂无学生数据！");
         pauseSystem();
         return;
     }
     
     char courseName[MAX_COURSE_NAME_LENGTH];
     printf("\n");
     safeInputString("请输入课程名称", courseName, MAX_COURSE_NAME_LENGTH);
     
     float maxScore = -1;
     int maxIndex = -1;
     
     for (int i = 0; i < studentCount; i++) {
         for (int j = 0; j < students[i].courseCount; j++) {
             if (strcmp(students[i].courses[j], courseName) == 0) {
                 if (students[i].scores[j] > maxScore) {
                     maxScore = students[i].scores[j];
                     maxIndex = i;
                 }
             }
         }
     }
     
     if (maxIndex == -1) {
         printError("未找到该课程！");
     } else {
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
  */
 void calculateStudentStats(Student* student) {
     if (student->courseCount == 0) {
         student->totalScore = 0;
         student->averageScore = 0;
         return;
     }
     
     student->totalScore = 0;
     for (int i = 0; i < student->courseCount; i++) {
         student->totalScore += student->scores[i];
     }
     
     student->averageScore = student->totalScore / student->courseCount;
 }
 
 /**
  * @brief 更新全局统计缓存
  */
 void updateGlobalStats() {
     if (studentCount == 0) {
         overallAverageScore = 0;
         highestScore = 0;
         lowestScore = 0;
         statsNeedUpdate = false;
         return;
     }
     
     float total = 0;
     highestScore = students[0].averageScore;
     lowestScore = students[0].averageScore;
     
     for (int i = 0; i < studentCount; i++) {
         total += students[i].averageScore;
         
         if (students[i].averageScore > highestScore) {
             highestScore = students[i].averageScore;
         }
         if (students[i].averageScore < lowestScore) {
             lowestScore = students[i].averageScore;
         }
     }
     
     overallAverageScore = total / studentCount;
     statsNeedUpdate = false;
 }