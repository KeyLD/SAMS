# SAMS 
Student and Association Management System By Qt


这里上传的只是源码，若要编译，运行，修改，请自行下载Qt库和[ IDE](https://www.qt.io/ide/,"QtCreator")，当然后续我有时间我会将编译后的文件+Qt库上传，并兼容windows操作系统

**若你要进行修改**，请将源文件的resource目录移动到编译目录即可。

以下是运行截图

![主界面](http://www.nodekey.com/wp-content/uploads/2018/03/Screenshot-from-2018-03-13-10-13-08.png "z主界面")

![添加学生](http://www.nodekey.com/wp-content/uploads/2018/03/Screenshot-from-2018-03-13-10-10-38.png "添加学生")

![显示社团](http://www.nodekey.com/wp-content/uploads/2018/03/Screenshot-from-2018-03-13-10-10-11.png "显示社团")

+ 2017.3.8 第一次提交功能完善版本

    该版本功能已完善，但还是有些许bug，兼容性不强，关键数据结构并非手写，哈希表映射函数效果不佳

+ 2018.3.13

    尝试用自写的红黑树进行修改，出现了两个严重Bug，不能修改，和输入数据的最后一个没有插入。第二个bug是因为我没有跟stl一样以左闭右开的方式实现迭代器导致。因为是老代码，写的臭，改不动，该项目进入废弃状态，有这时间不如去写个tinySTL。

