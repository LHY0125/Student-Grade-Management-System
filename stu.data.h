#ifndef STU_DATA_H
#define STU_DATA_H

#include "config.h"

// 学生数据管理相关函数 (CRUD)
void loadStudentsFromFile();                // 从文件加载学生数据
void saveStudentsToFile();                  // 将学生数据保存到文件
void addStudent();                          // 增加学生信息
void deleteStudent();                       // 删除学生信息
void modifyStudent();                       // 修改学生信息
void searchStudentByID();                   // 按学号查找学生
void searchStudentByName();                 // 按姓名查找学生
void displayAllStudents();                  // 显示所有学生信息
void displayStudentInfo(const Student* student); // 显示单个学生信息
void sortStudents(int criteria, int order); // 统一排序函数，根据参数选择排序依据和升降序

#endif // STU_DATA_H