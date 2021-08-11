[toc]
## 参考链接
[Git官网](https://git-scm.com)
[廖雪峰git教程](https://www.liaoxuefeng.com/wiki/896043488029600)
[菜鸟教程（查git命令）](https://www.runoob.com/git/git-basic-operations.html)
[gitconfig配置](https://blog.csdn.net/alex_i/article/details/105945822)
## Git的设计哲学
```
o <-- o <-- o <-- o
            ^
             \
              --- o <-- o
```
`o` correspond to individual commits (snapshots)
A snapshot is the top-level tree that is being tracked.

Blobs, trees, and commits are unified in this way: they are all objects. When they reference other objects, they don’t actually contain them in their on-disk representation, but have a reference to them by their **hash**.
所以Git记录着各object的hash
而因为hash实在是unreadable for human，所以git使用
> human-readable names for SHA-1 hashes

e.g.`master` reference usually points to the latest commit in the main branch of development
`Head` where we currently are

>we can use `git log` to see the hash of each commit and we can notice that the references follow the hash
><img src="./note_img/hash_and_ref.png" style="zoom:80%;" />

git的存储结构 in pesudocode
```
// a file is a bunch of bytes
type blob = array<byte>
// a directory contains named files and directories
type tree = map<string, tree | blob>
// a commit has parents, metadata, and the top-level tree
type commit = struct {
    parent: array<commit>
    author: string
    message: string
    snapshot: tree
}
```



## Basic workflow
> 一套比较完整的在本地修改然后push到远程仓库的流程

0. 先将本地设备的ssh公钥添加到GitHub account

1. clone
   `git clone link(SSH,HTTPS...)` 
   <img src="./note_img/gitclone.png" style="zoom:50%;" />
   会clone到你目前所载的目录下
   
2. `cd repo` 

3. 修改

4. 查看git仓库状态
   `git status`
   
5. 将文件添加到暂存区(staging area)
   `git add [file1] [file2] ...`文件
   `git add [dir]`目录
   `git add .`所有
   >文件修改后(modified)，我们一般都需要进行 git add 操作，从而保存历史版本。删除后也使用add。
   6. 提交暂存区内容到本地仓个库
   `git commit [file1] [file2] ... -m [message]`选取指定文件提交
   >-m可以只写一行message，若无该参数，则会进入一个文本编辑界面写subject title body ...等等对这个commit的描述信息。

   `git commit -a`不执行`git add`直接提交
   
7. 可以修改提交的用户名和邮箱
   `git config --global user.name 'runoob'`
   `git config --global user.email test@runoob.com` 无`global`仅修改该仓库
   
8. 提交到远程仓库
   `git push <远程主机名> <本地分支名>:<远程分支名>`
   `git pull <远程主机名> <远程分支名>:<本地分支名>`
   >远程主机名一般叫origin，也可以自己改。这样在`git log`的时候就会不一样了。

   <img src="./note_img/分支名.png" alt="main分支" style="zoom:80%;" />
   
   例：该远程分支(branch)就叫做main
   
   >我们常常见到`git push -u origin master` -u 的意思是`set upstream for git pull/status`这样以后就可以直接用 `git push`了。
   
9. 最后检查一下status
   `git status`
   显示clean
   >On branch main
   Your branch is up to date with 'origin/main'.
   nothing to commit, working tree clean

## tips
### remote 
   1. git remote -v 查看远程仓库

   2. `git remote add <name> URL`添加远程仓库，并将本地仓库和远端仓库关联起来。
      
      >这个name只是本地对远端仓库的命名 不影响远端仓库
      
   3. `git push <remote> <local branch>:<remote branch>`将本地local branch的commit上传到远端仓库的remote branch
      

      >有可能产生新的branch

   4. `git pull <remote> <remote branch>:<local branch>`同理。
      **`git pull`等于`git fetch`再`git merge`**
      
   5. `git fetch <远程主机名> <分支名>`是将远程主机的分支为分支名的最新内容拉到本地，用户在检查了以后决定是否合并到工作本机分支中。
      `git fetch`后再`git log`可以见到区别
   
      **`git push` --> `git fetch` --> `git pull`**
      注意可以拉取远程单独的某个分支。
      
      **git fetch**的作用是将远程分支下载到本地的origin分支上。
      
   6. `git clone URL <local folder name>`可以不加`<local folder name>`这样就以远端名字创建
      `git clone --shallow`只复制最新的snapshot，这对于一些有很长的git history的repo是极为有用的。
### git merge
1. 合并直接祖先。
   场景：你需要修改一个master上的bug，你基于最新的master建了一个分支hotfix并进行了修改，如下图所示。
	<img src="https://git-scm.com/book/en/v2/images/basic-branching-4.png" style="zoom:50%">
	修改完成后，你git checkout master然后git merge hotfix，因为hotfix是master的直接儿子，所以git处理这个merge的方式是直接将master移到hotfix上，如下图所示。这样肯定不会产生冲突。
	<img src="https://git-scm.com/book/en/v2/images/basic-branching-5.png" style="zoom:50%"/>
2. 合并分叉分支。
   场景：你的feature分支已经与master有数个commit的不同，即发生了分叉，如下图所示。
	<img src="https://git-scm.com/book/en/v2/images/basic-branching-6.png" style="zoom:50%"/>你完成了这个feature后要将这个feature加入master分支。于是你
	```
	git checkout master
	git merge iss53
	```
	此时git会根据master的最新快照，iss53的最新快照以及两者的LCA进行一个三方合并。如下图所示。
	<img src="https://git-scm.com/book/en/v2/images/basic-merging-1.png" style="zoom:50%"/>
	并生成一个新的提交并指向它。如下图所示。
	<img src="https://git-scm.com/book/en/v2/images/basic-merging-2.png" style="zoom:50%"/>
### git log
   1. 查看历史记录不支持滚轮需要使用**方向键**
   2. `git log --all --graph --decorate`以DAG的形式显示历史
### git diff 
   1. `git diff <hash of commit> <file>`不写`<hash of commit>` means `HEAD` 将file的目前状态与某个commit进行比较
   2. `git diff <hash of commit1><hash of commit2> <file>`对比file在两个commit下的差别
      
      >we can use master or HEAD to replace the long hash string
   3. `git add -p <file>`
      then you can choose the change you want to commit by s(spilt) and decide y/n for each diff
      then you can use `git diff --cached` to show the changes you want to commit
      
      > `git diff`show all the changes

### git reset

返回到某个版本，将当前的工作区的文件变成untracked。

### git restore

   use `git restore <file>...` to discard changes in working directory

​	`git restore HEAD` 回退到HEAD处。

### .gitignore file
gitignore file不能忽略已经加入版本控制的文件。这时需要将其从仓库中删除再加入gitignore file。
具体可以`git rm --cached filename`再将文件写入`.gitignore`中即可。
   rule:
   ```
   # / 表示 当前文件所在的目录

   # 忽略public下的所有目录及文件
   /public/*
   #不忽略/public/assets，就是特例的意思，assets文件不忽略
   !/public/assets

   # 忽略具体的文件

   index.php

   # 忽略所有的php
   *.php

   # 忽略 a.php b.php
   [ab].php

   #匹配规则和linux文件匹配一样
   #以斜杠“/”开头表示目录；表示忽略一个目录
   #以星号“*”通配多个字符；
   #以问号“?”通配单个字符
   #以方括号“[]”包含单个字符的匹配列表；
   #以叹号“!”表示不忽略(跟踪)匹配到的文件或目录；
   ```
### submodule
   [git submodule使用](https://zhuanlan.zhihu.com/p/87053283)
   [git submodule官方](https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-%E5%AD%90%E6%A8%A1%E5%9D%97)
   在你的仓库中使用其他git仓库需要使用git submodule

## branch
1. `git branch <name of the new branch>` create a new branch based on the **current working commit** 
   `git branch -d <name of the new branch>`删除分支
   
   without the parameter we can see all the branches we have
2. `git checkout <name of the branch>`

   3. `git checkout <file>`可以将file变为目前HEAD的commit的状态，从而舍弃working directory的修改
3. `git fetch <远程仓库名> <远程分支名>`拉取远端分支。然后使用`git checkout -b <本地分支名> origin/远端分支名`切换到该分支。
4. `git merge <分支名>`将当前分支与<分支名>合并。（并不会删除任何分支）

一、开发分支（dev）上的代码达到上线的标准后，要合并到 master 分支
```
   git checkout dev
   git pull
   git checkout master
   git merge dev
   git push -u origin master
```
二、当master代码改动了，需要更新开发分支（dev）上的代码
```
   git checkout master 
   git pull 
   git checkout dev
   git merge master
   git push -u origin dev
```

## git workflow
### feature branch workflow
1. 在开始一个新的feature前，创建一个新的隔离的branch
	```
	git checkout -b marys-feature main
	```
	-b 意味着如果没有这个分支，就创建一个分支。
2. 在本地修改
	```
	git status
	git add
	git commit
	```
3. 将本地分支push到远端仓库
	```
	git push -u origin marys-feature
	```
   这可以作为一个备份以及你的合作者可以浏览你的commit
4. 完成feature后，将本地的所有修改push到远端。
   ```
	git push
	```
5. 然后发起一个pull request
   在pull request中，其他合作者会检查代码，提出意见。Mary会根据这些意见修改，修改的过程与第一次迭代相同，pull request会记录这个过程。
6. 当决定接受这个pull request时，即将这个feature加入main分支。
	```
	git checkout main
	git pull
	git pull origin marys-feature
	git push
	```

