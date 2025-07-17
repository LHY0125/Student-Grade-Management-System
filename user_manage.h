/**
 * @file user_manage.h
 * @brief 用户管理实现文件
 * @note 实现用户认证和管理功能函数声明
 */

#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "config.h"

/**
 * @brief 处理用户登录
 * @details 提供用户登录验证功能，验证用户名和密码的正确性
 *          登录成功后设置当前用户信息和管理员权限
 * @return int 登录成功返回1，失败返回0
 * @note 登录过程：
 *       1. 获取用户输入的用户名和密码
 *       2. 遍历用户数组进行验证
 *       3. 验证成功则设置currentUser和isCurrentUserAdmin
 * @note 设置的全局变量：
 *       - currentUser: 当前登录用户名
 *       - isCurrentUserAdmin: 当前用户是否为管理员
 */
int loginSystem();

/**
 * @brief 从文件加载用户数据
 * @details 从USERS_FILE文件中读取用户数据到内存
 *          如果文件不存在，则创建默认的管理员和普通用户账户
 * @note 文件格式：每行格式为 "username:password:isAdmin"
 *       其中isAdmin为1表示管理员，0表示普通用户
 * @note 默认账户：
 *       - 管理员：用户名admin，密码123456
 *       - 普通用户：用户名teacher，密码password
 * @warning 如果文件格式错误，可能导致数据加载不完整
 */
void loadUsersFromFile();

/**
 * @brief 将用户数据保存到文件
 * @details 将内存中的用户数据写入到USERS_FILE文件中
 *          采用文本格式存储，每个用户占一行
 * @note 文件格式：每行格式为 "username:password:isAdmin"
 *       其中isAdmin为1表示管理员，0表示普通用户
 * @warning 如果文件无法打开，将显示错误信息
 */
void saveUsersToFile();

/**
 * @brief 增加用户账户
 * @details 提供交互式界面添加新的用户账户
 *          包括用户名唯一性检查、密码设置和用户类型选择
 * @note 添加流程：
 *       1. 检查用户数量是否达到上限
 *       2. 输入新用户名并检查唯一性
 *       3. 设置密码
 *       4. 选择用户类型（普通用户/管理员）
 *       5. 保存到文件并更新数据修改标志
 * @warning 如果用户数量已达MAX_USERS上限，将拒绝添加
 * @warning 如果用户名已存在，将拒绝添加
 */
void addUserAccount();

/**
 * @brief 删除用户账户
 * @details 提供交互式界面删除指定的用户账户
 *          包含安全检查，防止删除当前登录用户和最后一个用户
 * @note 删除限制：
 *       - 不能删除当前登录的用户
 *       - 系统至少需要保留一个用户账户
 * @note 删除过程：
 *       1. 输入要删除的用户名
 *       2. 进行安全检查
 *       3. 查找用户并删除
 *       4. 重新排列用户数组
 *       5. 保存到文件并更新数据修改标志
 * @warning 删除操作不可逆，请谨慎操作
 */
void deleteUserAccount();

/**
 * @brief 修改用户密码
 * @details 提供交互式界面修改指定用户的密码
 *          管理员可以修改任何用户的密码
 * @note 修改流程：
 *       1. 输入要修改密码的用户名
 *       2. 查找用户是否存在
 *       3. 输入新密码
 *       4. 更新用户密码
 *       5. 保存到文件并更新数据修改标志
 * @warning 密码修改后立即生效，用户需要使用新密码登录
 */
void modifyUserPassword();

/**
 * @brief 查看所有用户
 * @details 显示系统中所有用户的信息列表
 *          包括用户名、用户类型和当前登录状态
 * @note 显示内容：
 *       - 用户名
 *       - 用户类型（管理员/普通用户）
 *       - 状态（标识当前登录用户）
 *       - 总用户数统计
 * @note 表格格式显示，便于查看和管理
 * @warning 如果没有用户数据，将显示警告信息
 */
void viewAllUsers();

#endif // USER_MANAGE_H