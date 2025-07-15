#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "config.h"

// 用户认证与管理相关函数
int loginSystem();         // 处理用户登录
void loadUsersFromFile();  // 从文件加载用户数据
void saveUsersToFile();    // 将用户数据保存到文件
void addUserAccount();     // 增加用户
void deleteUserAccount();  // 删除用户
void modifyUserPassword(); // 修改用户密码
void viewAllUsers();       // 查看所有用户

#endif // USER_MANAGE_H