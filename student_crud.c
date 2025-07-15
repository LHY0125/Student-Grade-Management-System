/**
 * @file student_crud.c
 * @brief 学生数据增删改操作实现
 * @note 负责学生信息的添加、删除、修改等CRUD操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "globals.h"
#include "io_utils.h"
#include "validation.h"
#include "statistical_analysis.h"

/**
 * @brief 输入并验证学生学号
 * @details 循环输入学号直到格式正确且不重复
 * @param student 指向要填充的学生结构体的指针
 */
static void inputStudentID(Student *student)
{
    while (1)
    {
        safeInputString("请输入学号", student->studentID, MAX_ID_LENGTH);
        
        if (!isValidStudentId(student->studentID))
        {
            printError("学号格式无效！");
            continue;
        }
        
        // 检查学号是否已存在
        bool exists = false;
        for (int i = 0; i < studentCount; i++)
        {
            if (strcmp(students[i].studentID, student->studentID) == 0)
            {
                printError("学号已存在！");
                exists = true;
                break;
            }
        }
        
        if (!exists)
            break;
    }
}

/**
 * @brief 输入并验证学生基本信息
 * @details 输入学生的姓名、年龄和性别信息
 * @param student 指向要填充的学生结构体的指针
 */
static void inputBasicInfo(Student *student)
{
    // 输入姓名
    while (1)
    {
        safeInputString("请输入姓名", student->name, MAX_NAME_LENGTH);
        if (isValidName(student->name))
            break;
        printError("姓名格式无效！");
    }
    
    // 输入年龄
    student->age = safeInputInt("请输入年龄", 10, 100);
    
    // 输入性别
    while (1)
    {
        printf("请输入性别 (M/F): ");
        char gender;
        scanf(" %c", &gender);
        clearInputBuffer();
        
        if (isValidGender(gender))
        {
            student->gender = gender;
            break;
        }
        printError("性别输入无效！请输入 M 或 F");
    }
}

/**
 * @brief 输入学生课程信息
 * @details 循环输入课程名称和成绩，支持添加多门课程
 * @param student 指向要填充的学生结构体的指针
 */
static void inputCourseInfo(Student *student)
{
    printf("\n开始输入课程信息：\n");
    student->courseCount = 0;
    
    while (student->courseCount < MAX_COURSES)
    {
        printf("\n第 %d 门课程：\n", student->courseCount + 1);
        
        safeInputString("课程名称",
                        student->courses[student->courseCount],
                        MAX_COURSE_NAME_LENGTH);
        
        student->scores[student->courseCount] =
            safeInputFloat("课程分数", MIN_SCORE, MAX_SCORE);
        
        student->courseCount++;
        
        if (student->courseCount < MAX_COURSES)
        {
            printf("\n是否继续添加课程？(y/n): ");
            char choice;
            scanf(" %c", &choice);
            clearInputBuffer();
            
            if (choice != 'y' && choice != 'Y')
            {
                break;
            }
        }
    }
}

/**
 * @brief 显示添加成功的学生信息
 * @details 显示新添加学生的基本信息和统计数据
 * @param student 指向学生结构体的指针
 */
static void displayAddedStudentInfo(const Student *student)
{
    printSuccess("学生信息添加成功！");
    printf("学号: %s\n", student->studentID);
    printf("姓名: %s\n", student->name);
    printf("总分: %.2f\n", student->totalScore);
    printf("平均分: %.2f\n", student->averageScore);
}

/**
 * @brief 添加学生信息
 * @details 交互式地添加新学生信息，包括基本信息和课程成绩
 *          验证学号唯一性、姓名格式、年龄范围等
 *          自动计算总分和平均分
 * @note 会检查学生数量是否已达上限MAX_STUDENTS
 * @note 学号必须唯一，不能与现有学生重复
 * @warning 如果学生数量已满，会显示错误信息并返回
 * @see MAX_STUDENTS, isValidStudentId(), isValidName()
 */
void addStudent()
{
    clearScreen();
    printHeader("添加学生信息");
    
    if (studentCount >= MAX_STUDENTS)
    {
        printError("学生数量已达上限！");
        pauseSystem();
        return;
    }
    
    Student newStudent;
    memset(&newStudent, 0, sizeof(Student));
    
    printf("\n");
    
    // 输入学号
    inputStudentID(&newStudent);
    
    // 输入基本信息
    inputBasicInfo(&newStudent);
    
    // 输入课程信息
    inputCourseInfo(&newStudent);
    
    // 计算总分和平均分
    calculateStudentStats(&newStudent);
    
    // 添加到数组
    students[studentCount] = newStudent;
    studentCount++;
    
    // 标记数据已修改
    dataModified = true;
    statsNeedUpdate = true;
    
    // 显示添加成功信息
    displayAddedStudentInfo(&newStudent);
    
    pauseSystem();
}

/**
 * @brief 删除学生信息
 * @details 提供交互式界面删除指定学号的学生信息
 *          包含确认机制，防止误删除操作
 * @note 删除流程：
 *       1. 输入要删除的学生学号
 *       2. 查找并显示学生信息
 *       3. 用户确认删除操作
 *       4. 删除学生并重新排列数组
 *       5. 更新数据修改和统计更新标志
 * @warning 删除操作不可逆，请谨慎操作
 * @warning 如果没有学生数据，将显示警告信息
 */
void deleteStudent()
{
    clearScreen();
    printHeader("删除学生信息");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    char studentID[MAX_ID_LENGTH];
    printf("\n");
    safeInputString("请输入要删除的学生学号", studentID, MAX_ID_LENGTH);

    // 查找学生
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].studentID, studentID) == 0)
        {
            printf("\n找到学生信息：\n");
            printf("学号: %s\n", students[i].studentID);
            printf("姓名: %s\n", students[i].name);

            printf("\n确认删除？(y/n): ");
            char choice;
            scanf(" %c", &choice);
            clearInputBuffer();

            if (choice == 'y' || choice == 'Y')
            {
                // 移动后面的学生向前
                for (int j = i; j < studentCount - 1; j++)
                {
                    students[j] = students[j + 1];
                }
                studentCount--;

                dataModified = true;
                statsNeedUpdate = true;

                printSuccess("学生信息删除成功！");
            }
            else
            {
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
 * @brief 显示学生基本信息
 * @details 显示学生的学号、姓名、年龄、性别等基本信息
 * @param student 指向学生结构体的指针
 */
static void displayStudentBasicInfo(const Student *student)
{
    printf("\n找到学生信息：\n");
    printf("学号: %s\n", student->studentID);
    printf("姓名: %s\n", student->name);
    printf("年龄: %d\n", student->age);
    printf("性别: %c\n", student->gender);
}

/**
 * @brief 修改学生性别
 * @details 循环输入直到获得有效的性别值
 * @param student 指向学生结构体的指针
 */
static void modifyStudentGender(Student *student)
{
    while (1)
    {
        printf("请输入新性别 (M/F): ");
        char gender;
        scanf(" %c", &gender);
        clearInputBuffer();
        
        if (isValidGender(gender))
        {
            student->gender = gender;
            break;
        }
        printError("性别输入无效！");
    }
}

/**
 * @brief 修改现有课程成绩
 * @details 选择并修改学生的现有课程成绩
 * @param student 指向学生结构体的指针
 */
static void modifyExistingCourse(Student *student)
{
    if (student->courseCount == 0)
    {
        printWarning("该学生没有课程记录！");
        return;
    }
    
    int courseIndex = safeInputInt("请选择要修改的课程", 1, student->courseCount) - 1;
    student->scores[courseIndex] = safeInputFloat("新成绩", MIN_SCORE, MAX_SCORE);
}

/**
 * @brief 添加新课程
 * @details 为学生添加新的课程和成绩
 * @param student 指向学生结构体的指针
 */
static void addNewCourse(Student *student)
{
    if (student->courseCount >= MAX_COURSES)
    {
        printWarning("课程数量已达上限！");
        return;
    }
    
    safeInputString("课程名称", student->courses[student->courseCount], MAX_COURSE_NAME_LENGTH);
    student->scores[student->courseCount] = safeInputFloat("课程成绩", MIN_SCORE, MAX_SCORE);
    student->courseCount++;
}

/**
 * @brief 删除课程
 * @details 删除学生的指定课程和成绩
 * @param student 指向学生结构体的指针
 */
static void deleteCourse(Student *student)
{
    if (student->courseCount == 0)
    {
        printWarning("该学生没有课程记录！");
        return;
    }
    
    int courseIndex = safeInputInt("请选择要删除的课程", 1, student->courseCount) - 1;
    
    // 移动数组元素
    for (int k = courseIndex; k < student->courseCount - 1; k++)
    {
        strcpy(student->courses[k], student->courses[k + 1]);
        student->scores[k] = student->scores[k + 1];
    }
    student->courseCount--;
}

/**
 * @brief 显示课程列表
 * @details 显示学生的所有课程和成绩
 * @param student 指向学生结构体的指针
 */
static void displayCourseList(const Student *student)
{
    printf("\n当前课程列表：\n");
    for (int j = 0; j < student->courseCount; j++)
    {
        printf("%d. %s: %.2f\n", j + 1, student->courses[j], student->scores[j]);
    }
}

/**
 * @brief 修改课程信息
 * @details 提供课程修改的子菜单，包括修改、添加、删除课程
 * @param student 指向学生结构体的指针
 * @return true 如果进行了课程修改，false 如果没有修改
 */
static bool modifyCourseInfo(Student *student)
{
    displayCourseList(student);
    
    printf("\n修改选项：\n");
    printf("1. 修改现有课程成绩\n");
    printf("2. 添加新课程\n");
    printf("3. 删除课程\n");
    printf("0. 返回\n");
    
    int courseChoice = safeInputInt("请选择操作", 0, 3);
    switch (courseChoice)
    {
    case 1: // 修改现有课程成绩
        modifyExistingCourse(student);
        return true;
    case 2: // 添加新课程
        addNewCourse(student);
        return true;
    case 3: // 删除课程
        deleteCourse(student);
        return true;
    case 0:
        return false;
    }
    return false;
}

/**
 * @brief 处理学生信息修改
 * @details 处理找到学生后的修改操作
 * @param student 指向学生结构体的指针
 */
static void handleStudentModification(Student *student)
{
    displayStudentBasicInfo(student);
    
    printf("\n修改选项：\n");
    printf("1. 修改姓名\n");
    printf("2. 修改年龄\n");
    printf("3. 修改性别\n");
    printf("4. 修改课程成绩\n");
    printf("0. 返回\n");
    
    int choice = safeInputInt("请选择修改项", 0, 4);
    
    bool courseModified = false;
    
    switch (choice)
    {
    case 1: // 修改姓名
        safeInputString("请输入新姓名", student->name, MAX_NAME_LENGTH);
        break;
    case 2: // 修改年龄
        student->age = safeInputInt("请输入新年龄", 10, 100);
        break;
    case 3: // 修改性别
        modifyStudentGender(student);
        break;
    case 4: // 修改课程成绩
        courseModified = modifyCourseInfo(student);
        break;
    case 0:
        return;
    }
    
    if (courseModified)
    {
        calculateStudentStats(student);
    }
    
    dataModified = true;
    statsNeedUpdate = true;
    
    printSuccess("学生信息修改成功！");
}

/**
 * @brief 修改学生信息
 * @details 提供交互式界面修改指定学生的各项信息
 *          支持修改姓名、年龄、性别和课程成绩等信息
 * @note 修改选项：
 *       1. 修改姓名
 *       2. 修改年龄
 *       3. 修改性别
 *       4. 修改课程成绩（包括修改现有成绩、添加新课程、删除课程）
 * @note 课程成绩修改包含：
 *       - 修改现有课程成绩
 *       - 添加新课程
 *       - 删除课程
 * @warning 修改课程信息后会自动重新计算总分和平均分
 */
void modifyStudent()
{
    clearScreen();
    printHeader("修改学生信息");
    
    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }
    
    char studentID[MAX_ID_LENGTH];
    printf("\n");
    safeInputString("请输入要修改的学生学号", studentID, MAX_ID_LENGTH);
    
    // 查找学生
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].studentID, studentID) == 0)
        {
            handleStudentModification(&students[i]);
            pauseSystem();
            return;
        }
    }
    
    printError("未找到该学号的学生！");
    pauseSystem();
}