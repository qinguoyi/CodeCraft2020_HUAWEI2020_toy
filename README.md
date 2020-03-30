2020华为软件精英挑战赛热身赛
===============
<div align=center><img width="679" height="34" src="https://github.com/twomonkeyclub/CodeCraft2019/blob/master/result/chusai.jpg"/></div>

#### 赛题简述
通俗讲，**赛题打算通过研究现有数据的规律，然后对新数据进行二分类。**

#### 思路流程图

赛题大体上可以分为四部分，数据读取与转换，模型训练，模型预测和结果文件生成。

* 数据读取与转换
	* 主线程通过mmap对文件进行映射，得到数据指针
	* 四个线程从指针四等分处对字节进行处理，通过自己编写的myatof函数转为具体数据
* 模型训练
	* 极其简化的K-Means分类，使用1000个特征维度
	* 子线程读取训练文件的四部分，主线程得到0和1两个类别的平均中心
* 模型预测
	* 将测试文件进行读取与转换，设置阈值对第一个维度的数据进行过滤
	* 小于阈值的使用类别中心和欧氏距离对该行数据进行分类，大于阈值的直接赋值为类别1
* 结果文件生成
	* 模型预测时生成的类别类型为char，而不是int型
	* 每行数据预测后，生成类别+换行符，主线程通过fwrite写入文件

<div align=center><img src="http://ww1.sinaimg.cn/large/005TJ2c7ly1gdby9l8vc0j30ve0vtadf.jpg" height="500"/> </div>

#### 具体解析
选择底部菜单栏：**互联网 -> 经验分享 -> 2020华为软挑热身赛代码开源-思路大起底**

更多资料，请关注公众号 **“两猿社”**.
> * **带你丰富互联网相关项目经验，轻松应对校招！！！**
> * **项目模块详细讲解，在公众号内持续更新！！！**

<div align=center><img src="https://github.com/twomonkeyclub/TinyWebServer/blob/master/root/test1.jpg" height="350"/> </div>