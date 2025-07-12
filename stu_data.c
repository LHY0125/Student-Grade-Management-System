/**
 * @file stu_data.c
 * @brief 学生数据管理实现文件
 * @note 实现学生信息的增删改查功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stu.data.h"
#include "config.h"
#include "globals.h"
#include "auxiliary.h"
#include "statistical_analysis.h"

/**
 * @brief 从CSV文件加载学生数据
 */
void loadStudentsFromFile() {
    FILE* file = fopen(STUDENTS_FILE, "r");
    if (file == NULL) {
        studentCount = 0;
        printInfo("学生数据文件不存在，将创建新文件。");
        return;
    }
    
    char line[1024];
    studentCount = 0;
    
    // 跳过CSV头部
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        studentCount = 0;
        return;
    }
    
    // 读取学生数据
    while (fgets(line, sizeof(line), file) != NULL && studentCount < MAX_STUDENTS) {
        Student* student = &students[studentCount];
        memset(student, 0, sizeof(Student));
        
        // 解析CSV行
        char* token = strtok(line, ",");
        if (token == NULL) continue;
        
        // 学号
        strncpy(student->studentID, token, MAX_ID_LENGTH - 1);
        
        // 姓名
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(student->name, token, MAX_NAME_LENGTH - 1);
        
        // 年龄
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        student->age = atoi(token);
        
        // 性别
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        student->gender = token[0];
        
        // 课程数量
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        student->courseCount = atoi(token);
        
        // 课程和成绩
        for (int i = 0; i < student->courseCount && i < MAX_COURSES; i++) {
            // 课程名称
            token = strtok(NULL, ",");
            if (token == NULL) break;
            strncpy(student->courses[i], token, MAX_COURSE_NAME_LENGTH - 1);
            
            // 成绩
            token = strtok(NULL, ",");
            if (token == NULL) break;
            student->scores[i] = atof(token);
        }
        
        // 总分
        token = strtok(NULL, ",");
        if (token != NULL) {
            student->totalScore = atof(token);
        }
        
        // 平均分
        token = strtok(NULL, ",");
        if (token != NULL) {
            student->averageScore = atof(token);
        }
        
        studentCount++;
    }
    
    fclose(file);
    
    // 更新统计信息
    statsNeedUpdate = true;
}

/**
 * @brief 将学生数据保存到CSV文件
 */
void saveStudentsToFile() {
    FILE* file = fopen(STUDENTS_FILE, "w");
    if (file == NULL) {
        printError("无法保存学生数据！");
        return;
    }
    
    // 写入CSV头部
    fprintf(file, "学号,姓名,年龄,性别,课程数量");
    for (int i = 0; i < MAX_COURSES; i++) {
        fprintf(file, ",课程%d,成绩%d", i+1, i+1);
    }
    fprintf(file, ",总分,平均分\n");
    
    // 写入学生数据
    for (int i = 0; i < studentCount; i++) {
        Student* student = &students[i];
        
        // 基本信息
        fprintf(file, "%s,%s,%d,%c,%d",
                student->studentID,
                student->name,
                student->age,
                student->gender,
                student->courseCount);
        
        // 课程和成绩
        for (int j = 0; j < MAX_COURSES; j++) {
            if (j < student->courseCount) {
                fprintf(file, ",%s,%.2f", student->courses[j], student->scores[j]);
            } else {
                fprintf(file, ",,");  // 空的课程和成绩
            }
        }
        
        // 总分和平均分
        fprintf(file, ",%.2f,%.2f\n", student->totalScore, student->averageScore);
    }
    
    fclose(file);
    dataModified = false;
    
    printSuccess("学生数据已保存到CSV文件！");
}

/**
 * @brief 添加学生信息
 */
void addStudent() {
    clearScreen();
    printHeader("添加学生信息");
    
    if (studentCount >= MAX_STUDENTS) {
        printError("学生数量已达上限！");
        pauseSystem();
        return;
    }
    
    Student newStudent;
    memset(&newStudent, 0, sizeof(Student));
    
    printf("\n");
    
    // 输入学号
    while (1) {
        safeInputString("请输入学号", newStudent.studentID, MAX_ID_LENGTH);
        
        if (!isValidStudentID(newStudent.studentID)) {
            printError("学号格式无效！");
            continue;
        }
        
        // 检查学号是否已存在
        bool exists = false;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].studentID, newStudent.studentID) == 0) {
                printError("学号已存在！");
                exists = true;
                break;
            }
        }
        
        if (!exists) break;
    }
    
    // 输入姓名
    while (1) {
        safeInputString("请输入姓名", newStudent.name, MAX_NAME_LENGTH);
    if (isValidName(newStudent.name)) break;
        printError("姓名格式无效！");
    }
    
    // 输入年龄
    newStudent.age = safeInputInt("请输入年龄", 10, 100);
    
    // 输入性别
    while (1) {
        printf("请输入性别 (M/F): ");
        char gender;
        scanf(" %c", &gender);
        clearInputBuffer();
        
        if (isValidGender(gender)) {
            newStudent.gender = gender;
            break;
        }
        printError("性别输入无效！请输入 M 或 F");
    }
    
    // 输入课程信息
    printf("\n开始输入课程信息：\n");
    newStudent.courseCount = 0;
    
    while (newStudent.courseCount < MAX_COURSES) {
        printf("\n第 %d 门课程：\n", newStudent.courseCount + 1);
        
        safeInputString("课程名称", 
                       newStudent.courses[newStudent.courseCount], 
                       MAX_COURSE_NAME_LENGTH);
        
        newStudent.scores[newStudent.courseCount] = 
            safeInputFloat("课程分数", MIN_SCORE, MAX_SCORE);
        
        newStudent.courseCount++;
        
        if (newStudent.courseCount < MAX_COURSES) {
            printf("\n是否继续添加课程？(y/n): ");
            char choice;
            scanf(" %c", &choice);
            clearInputBuffer();
            
            if (choice != 'y' && choice != 'Y') {
                break;
            }
        }
    }
    
    // 计算总分和平均分
    calculateStudentStats(&newStudent);
    
    // 添加到数组
    students[studentCount] = newStudent;
    studentCount++;
    
    // 标记数据已修改
    dataModified = true;
    statsNeedUpdate = true;
    
    printSuccess("学生信息添加成功！");
    printf("学号: %s\n", newStudent.studentID);
    printf("姓名: %s\n", newStudent.name);
    printf("总分: %.2f\n", newStudent.totalScore);
    printf("平均分: %.2f\n", newStudent.averageScore);
    
    pauseSystem();
}

/**
 * @brief 删除学生信息
 */
void deleteStudent() {
    clearScreen();
    printHeader("删除学生信息");
    
    if (studentCount == 0) {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }
    
    char studentID[MAX_ID_LENGTH];
    printf("\n");
    safeInputString("请输入要删除的学生学号", studentID, MAX_ID_LENGTH);
    
    // 查找学生
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, studentID) == 0) {
            printf("\n找到学生信息：\n");
            printf("学号: %s\n", students[i].studentID);
            printf("姓名: %s\n", students[i].name);
            
            printf("\n确认删除？(y/n): ");
            char choice;
            scanf(" %c", &choice);
            clearInputBuffer();
            
            if (choice == 'y' || choice == 'Y') {
                // 移动后面的学生向前
                for (int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                
                dataModified = true;
                statsNeedUpdate = true;
                
                printSuccess("学生信息删除成功！");
            } else {
                printInfo("删除操作已取消。");
            }
            
            pauseSystem();
            return;
        }
    }
    
    printError("未找到该学号的学生！");
    pauseSystem();
}

/**
 * @brief 修改学生信息
 */
void modifyStudent() {
    clearScreen();
    printHeader("修改学生信息");
    
    if (studentCount == 0) {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }
    
    char studentID[MAX_ID_LENGTH];
    printf("\n");
    safeInputString("请输入要修改的学生学号", studentID, MAX_ID_LENGTH);
    
    // 查找学生
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, studentID) == 0) {
            printf("\n找到学生信息：\n");
            printf("学号: %s\n", students[i].studentID);
            printf("姓名: %s\n", students[i].name);
            printf("年龄: %d\n", students[i].age);
            printf("性别: %c\n", students[i].gender);
            
            printf("\n修改选项：\n");
            printf("1. 修改姓名\n");
            printf("2. 修改年龄\n");
            printf("3. 修改性别\n");
            printf("4. 修改课程成绩\n");
            printf("0. 返回\n");
            
            int choice = safeInputInt("请选择修改项", 0, 4);
            
            switch (choice) {
                case 1: // 修改姓名
                    safeInputString("请输入新姓名", students[i].name, MAX_NAME_LENGTH);
                    break;
                case 2:
                    students[i].age = safeInputInt("请输入新年龄", 10, 100);
                    break;
                case 3:
                    while (1) {
                        printf("请输入新性别 (M/F): ");
                        char gender;
                        scanf(" %c", &gender);
                        clearInputBuffer();
                        
                        if (isValidGender(gender)) {
                            students[i].gender = gender;
                            break;
                        }
                        printError("性别输入无效！");
                    }
                    break;
                case 4:
                    printf("\n当前课程列表：\n");
                    for (int j = 0; j < students[i].courseCount; j++) {
                        printf("%d. %s: %.2f\n", j + 1, students[i].courses[j], students[i].scores[j]);
                    }
                    
                    printf("\n修改选项：\n");
                    printf("1. 修改现有课程成绩\n");
                    printf("2. 添加新课程\n");
                    printf("3. 删除课程\n");
                    printf("0. 返回\n");
                    
                    int courseChoice = safeInputInt("请选择操作", 0, 3);
                    switch (courseChoice) {
                        case 1: // 修改现有课程成绩
                            if (students[i].courseCount == 0) {
                                printWarning("该学生没有课程记录！");
                                break;
                            }
                            
                            int courseIndex = safeInputInt("请选择要修改的课程", 1, students[i].courseCount) - 1;
                            students[i].scores[courseIndex] = safeInputFloat("新成绩", MIN_SCORE, MAX_SCORE);
                            break;
                            
                        case 2: // 添加新课程
                            if (students[i].courseCount >= MAX_COURSES) {
                                printWarning("课程数量已达上限！");
                                break;
                            }
                            
                            safeInputString("课程名称", students[i].courses[students[i].courseCount], MAX_COURSE_NAME_LENGTH);
                            students[i].scores[students[i].courseCount] = safeInputFloat("课程成绩", MIN_SCORE, MAX_SCORE);
                            students[i].courseCount++;
                            break;
                            
                        case 3: // 删除课程
                            if (students[i].courseCount == 0) {
                                printWarning("该学生没有课程记录！");
                                break;
                            }
                            
                            courseIndex = safeInputInt("请选择要删除的课程", 1, students[i].courseCount) - 1;
                            
                            // 移动数组元素
                            for (int k = courseIndex; k < students[i].courseCount - 1; k++) {
                                strcpy(students[i].courses[k], students[i].courses[k + 1]);
                                students[i].scores[k] = students[i].scores[k + 1];
                            }
                            students[i].courseCount--;
                            break;
                    }
                    break;
                case 0:
                    return;
            }
            
            if (choice == 4) {
                calculateStudentStats(&students[i]);
            }
            
            dataModified = true;
            statsNeedUpdate = true;
            
            printSuccess("学生信息修改成功！");
            pauseSystem();
            return;
        }
    }
    
    printError("未找到该学号的学生！");
    pauseSystem();
}

/**
 * @brief 修改学生课程成绩
 */
/**
 * @brief 按学号查找学生
 */
void searchStudentByID() {
    clearScreen();
    printHeader("按学号查找学生");
    
    if (studentCount == 0) {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }
    
    char studentID[MAX_ID_LENGTH];
    printf("\n");
    safeInputString("请输入学号", studentID, MAX_ID_LENGTH);
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, studentID) == 0) {
            displayStudentInfo(&students[i]);
            pauseSystem();
            return;
        }
    }
    
    printError("未找到该学号的学生！");
    pauseSystem();
}

/**
 * @brief 按姓名查找学生
 */
void searchStudentByName() {
    clearScreen();
    printHeader("按姓名查找学生");
    
    if (studentCount == 0) {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }
    
    char name[MAX_NAME_LENGTH];
    printf("\n");
    safeInputString("请输入姓名（支持模糊查找）", name, MAX_NAME_LENGTH);
    
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, name) != NULL) {
            if (!found) {
                printf("\n找到以下匹配的学生：\n");
                printSeparator();
                found = true;
            }
            displayStudentInfo(&students[i]);
            printf("\n");
        }
    }
    
    if (!found) {
        printError("未找到匹配的学生！");
    }
    
    pauseSystem();
}

/**
 * @brief 显示所有学生信息
 */
void displayAllStudents() {
    clearScreen();
    printHeader("所有学生信息");
    
    if (studentCount == 0) {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }
    
    printf("\n");
    // 调整中文表头的对齐格式，考虑中文字符的显示宽度
    printf("%-10s %-12s %-6s %-6s %-8s %-8s\n", 
           "学号", "姓名", "年龄", "性别", "总分", "平均分");
    printf("========================================\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%-10s %-12s %-6d %-6c %-8.2f %-8.2f\n",
               students[i].studentID,
               students[i].name,
               students[i].age,
               students[i].gender,
               students[i].totalScore,
               students[i].averageScore);
    }
    
    printf("\n总学生数: %d\n", studentCount);
    pauseSystem();
}

/**
 * @brief 显示单个学生详细信息
 */
void displayStudentInfo(const Student* student) {
    printf("\n学生详细信息：\n");
    printSeparator();
    printf("学号: %s\n", student->studentID);
    printf("姓名: %s\n", student->name);
    printf("年龄: %d\n", student->age);
    printf("性别: %c\n", student->gender);
    printf("课程数量: %d\n", student->courseCount);
    
    if (student->courseCount > 0) {
        printf("\n课程成绩：\n");
        for (int i = 0; i < student->courseCount; i++) {
            printf("  %s: %.2f分\n", 
                   student->courses[i], 
                   student->scores[i]);
        }
        printf("\n总分: %.2f\n", student->totalScore);
        printf("平均分: %.2f\n", student->averageScore);
    }
}

/**
 * @brief 排序学生信息
 */
void sortStudents(int criteria, int order) {
    if (studentCount <= 1) return;
    
    // 使用冒泡排序
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - 1 - i; j++) {
            bool shouldSwap = false;
            
            switch (criteria) {
                case SORT_BY_ID:
                    shouldSwap = (order == SORT_ASCENDING) ? 
                        strcmp(students[j].studentID, students[j + 1].studentID) > 0 :
                        strcmp(students[j].studentID, students[j + 1].studentID) < 0;
                    break;
                case SORT_BY_NAME:
                    shouldSwap = (order == SORT_ASCENDING) ? 
                        strcmp(students[j].name, students[j + 1].name) > 0 :
                        strcmp(students[j].name, students[j + 1].name) < 0;
                    break;
                case SORT_BY_TOTAL_SCORE:
                    shouldSwap = (order == SORT_ASCENDING) ? 
                        students[j].totalScore > students[j + 1].totalScore :
                        students[j].totalScore < students[j + 1].totalScore;
                    break;
                case SORT_BY_AVERAGE_SCORE:
                    shouldSwap = (order == SORT_ASCENDING) ? 
                        students[j].averageScore > students[j + 1].averageScore :
                        students[j].averageScore < students[j + 1].averageScore;
                    break;
            }
            
            if (shouldSwap) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    dataModified = true;
}