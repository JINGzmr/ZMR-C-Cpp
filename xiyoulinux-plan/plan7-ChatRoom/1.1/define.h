#ifndef DEFINE_H
#define DEFINE_H

const int BUFFER_SIZE = 10240; // 缓冲区的大小（用于存储recv来的序列化好的string）

#define HADBLACK -7        // 已拉黑对方
#define HADFRIEND -6       // 已添加为好友
#define USERNAMEUNEXIST -5 // 用户名不存在
#define USERNAMEEXIST -4   // 用户名已存在
#define OFFLINE -3         // 不在线
#define ONLINE -2          // 在线
#define FAIL -1            // 失败  --->不能单定义一个N为-1 ！！！，否则可能会破坏引用的三方库里的其他对N的定义
#define SUCCESS 0          // 成功
#define LOGIN 1            // 登录请求
#define REGISTER 2         // 注册请求
#define SIGNOUT 3          // 注销请求

#define ADDFRIEND 4         // 添加好友
#define FRIENDAPPLYLIST 51  // 查看好友申请列表
#define FRIENDAPPLYEDIT 52  // 编辑好友申请
#define CHATFRIEND 6        // 选择好友私聊
#define HISTORYCHAT 7       // 查看历史聊天记录
#define FRIENDINFO 8        // 好友信息
#define ADDBLACK 9          // 加入黑名单（屏蔽好友）
#define DELFRIEND 10        // 删除好友
#define BLACKFRIENDLIST 111 // 查看屏蔽好友列表
#define BLACKFRIENDEDIT 112 // 编辑屏蔽好友

#define LOGOUT 16 // 退出登录

#endif