# Django

## Basic

`python manage.py sqlmigrate app_name 000x`

返回SQL语句

`python manage.py makemigrations app`

检测你对模型文件的修改（在这种情况下，你已经取得了新的），并且把修改的部分储存为一次 *迁移*。

`python manage.py migrate`

这个migrate命令选中所有还没有执行过的迁移（Django 通过在数据库中创建一个特殊的表 `django_migrations` 来跟踪执行过哪些迁移）并应用在数据库上 - 也就是将你对模型的更改同步到数据库结构上。

> 迁移是非常强大的功能，它能让你在开发过程中持续的改变数据库结构而不需要重新删除和创建表 - 它专注于使数据库平滑升级而不会丢失数据。我们会在后面的教程中更加深入的学习这部分内容，现在，你只需要记住，改变模型需要这三步：
>
> - 编辑 `models.py` 文件，改变模型。
> - 运行python manage.py makemigrations 为模型的改变生成迁移文件。
> - 运行python manage.py migrate来应用数据库迁移。

## View

`render(request, 'polls/index.html', context)`

载入模板，填充上下文，再返回由它生成的HttpResponse对象

`get_object_or_404(Question, pk=question_id)`

尝试用 get() 函数获取一个对象，如果不存在就抛出 Http404 错误

### Template

### 通用视图