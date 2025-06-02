🎮 Go_Gomoku_Chess_Game
Version Alpha-0.1.0
本项目是一个基于 C++ 和 EasyX 图形库开发的双棋类对战游戏，支持本地双人五子棋与围棋玩法，拥有图形化 UI 与基础胜负判断功能。

✅ 已实现的功能
 实现图形化 UI，支持点击操作与页面切换逻辑

 支持本地双人五子棋与围棋对局，能够判断胜负

 游戏状态栈功能支持悔棋、重开等扩展

❌ 尚需解决的问题
🚧 功能缺失
 暂未实现网络对战功能（计划引入客户端/服务器通信）

🐛 已知 Bug（人机对战部分）
[严重] 玩家点击已存在棋子处，会触发 AI 落子

问题代码逻辑：

cpp
复制
编辑
if (player.computer_and_player_put_Chess(m)) break;
chessesBuff.push_back(chesses);

if (ai.put_Chess()) break;
chessesBuff.push_back(chesses);
玩家点击已有棋子位置不会添加棋子，但 computer_and_player_put_Chess 返回 true，导致跳转到 AI 回合。

[严重] AI 有时跳过自己回合，直接切换到玩家

表现：AI 并未下子，回合却切换给玩家

怀疑点：AI::put_Chess() 中未落子时未阻止回合切换

cpp
复制
编辑
if (!newChess.is_Chess_Exist(chesses)) {
    chesses.push_back(newChess);
    ...
    return result != NORMAL_WIN;
}
return NORMAL_WIN; // 可能错误地允许回合结束
[严重] 围棋对战中 AI 始终在右下角落子，部分棋子消失

原因可能为围棋 AI 策略未正确检测已有棋子

[规则缺陷] 五子棋某些特殊情况下误判胜利

示例：出现“三三禁手”时仍判断为胜

💡 潜在的解决方案建议
取消全局状态变量

建议将 chesses、chesscolor 等变量封装为玩家对象的属性，传入判断函数更清晰，也便于支持网络与 AI 对战逻辑

完善交互流程阻塞

玩家在点击已存在棋子位置时应提示无效操作，而非默认进入下一步流程

构建客户端-服务器架构

将服务端改为数据中转处理节点，仅接受并广播 JSON 格式数据

客户端仅负责本地渲染，核心数据统一由服务端管理

需重点设计：

数据存储结构（如每一步棋坐标与颜色）

通信格式与协议

客户端与服务端状态同步机制

📌 项目结构（建议）
plaintext
复制
编辑
Go_Gomoku_Chess_Game/
├── src/               # 核心源代码
├── assets/            # 图像资源等
├── README.md
├── .gitignore
└── CMakeLists.txt     # 构建脚本
📋 开发环境
语言：C++

图形库：EasyX

开发工具：CLion + CMake

平台支持：Windows（需 EasyX 环境支持）

📅 更新日志
版本号	日期	说明
Alpha-0.1.0	2025-06-02	初始版本，支持本地双人模式及 UI 展示

📮 联系与贡献
欢迎提出 Issues 或提交 Pull Requests 来一起改进本项目！

