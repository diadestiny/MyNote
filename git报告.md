# git记录

## 1. git理解

* 分布式版本管理工具 (类似多人共享的百度云盘的感觉)
* 工作区、暂存区、本地仓库、远程仓库的概念

> 工作区:在当前仓库中，新增，更改，删除文件这些动作，都发生在工作区里面。

> 暂存区:保留历史版本，用git add 添加的区域。

> 本地仓库:本地git clone下的内容。

> 远程仓库:相对应仓库的github上面的内容。

## 2.个人常用git bash命令

### 初始配置
* git config --global user.name author
* git config --global user.email author@xxx.com


* git clone xxxxx //拷贝远程仓库到本地
* git add -A//添加所有变化到暂存区
* git commit -m“message”//备注message信息
* git push (origin master)//推到远程仓库
* git pull //拉取同步远处仓库
* git status//查看暂存区历史信息


### 多人一起弄的话(分枝机制)
1. 先fork一下
2. 再git checkout -b branchname
3. git add -A
4. git commit -m “branchmessage”
5. git push origin branchname
6. 主master合并就切到主分支
7. 然后git merge branchanme