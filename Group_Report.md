# 小组Report

| 组号 | 组员                         |
| ---- | ---------------------------- |
| 2    | 周远笛、谢涛、袁之浩、杨泓臻 |

## 项目介绍以及实现结果（周远笛）

## 开发环境以及使用到的第三方库（谢涛）

## 实现功能列表(Basic与Bonus)（谢涛和泓臻）

## 对实现的功能点做简单介绍(Bonus主要介绍实现原理)，加结果截图（粘贴个人报告）

### 天空盒

#### 简介

天空盒的精髓在于两点：1. 找到美丽的图片 2. 平移过程中最后一列为0（期中考试题有所提及）

#### 实现

技术上的实现主要就是其相对摄像机的位置不随着摄像机的移动而改变。

天空盒的实现主要输一个cubemap贴图的技术点。这一步需要绑定纹理类型`GL_TEXTURE_CUBE_MAP`，每一个面的纹理都需要`glTexImage2D`函数，OpenGL的六个不同纹理目标对应了立方体六个不同的面。这里由于每个纹理目标相对上一个是连续递增的枚举值，因此可以按照右、左、上、下、后、前的顺序依次绑定六个面的贴图。

在现实天空盒的时候需要注意以下几点：

1. 关闭深度写入`glDepthMask(GL_FALSE);`

2. 天空盒是不随玩家移动改变的，因此移除视图矩阵的平移部分：

   ```
   glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
   ```

#### 效果

<img src="C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/imgs/skybox.gif" width="500"/>

### 显示文字（xt）

### Stencil Test (模板测试)（TODO????）

### 重力系统与碰撞检测（hz）

### 粒子系统

每一滴雨都是一个粒子，通过粒子生成器particleGenerator来对粒子进行统一的管理，持续不断地生成新的粒子，以及将过期的粒子进行回收，避免内存的过度占用。

一般的粒子有一个生存周期life值，但是因为雨受重力控制，生存周期是从产生到落地，所以根据粒子位置的y值来判断粒子是否处于存活状态。

关于粒子用什么形状，本来有考虑过用贴图水滴的图片，但是因为雨的下落速度较快，正常观察到的不是水珠而是类似线端，所以以线段来作为粒子的显示形状。

如何控制雨量的大小，通过控制粒子的下落速度和每次更新增加的粒子数量来实现。
![](C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/yhz-imgs/rain.PNG)
**重力系统**
对每个粒子加一个y轴的向量velocity作为重力，每次刷新测得时间差，对粒子的位置position加上velocity进行更新。

### Anti-Aliasing (抗锯齿)（TODO????）

### 流体模拟

#### 简介

流体模拟在我们的项目中主要通过水的实现来体现。

其中mesh的导入在model import的部分已经写过了，水的流动主要是通过Gerstner Waves波动的物理模型实现的。

关于波浪的实现，采用的方法是对于三角面片上的每个顶点在不同时刻计算出其坐标（这一步在vs中实现），再传入fs进行渲染。

这一过程遵循以下公式：
$$
P(x,y,t) = \\\left(x+\sum\left(Q_iA_i\times D_i.x\times \cos(w_iD_i\bullet(x,y)+\phi_it\right),\\
y+\sum\left(Q_iA_i\times D_i.y\times \cos(w_iD_i\bullet(x,y)+\phi_it\right),\\
\sum\left(A_i\sin(w_iD_i\bullet(x,y)+\phi_it\right)\right)
$$

#### 实现

水的波动实际上是顶点的变化，这里是通过定点渲染器根据时间随着上面的公式改变坐标位置实现的。

#### 效果

<img src="C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/imgs/water.gif" width="400"/>

### LSystem和树生长

#### 简介

Lsystem用于树木生长的模拟。首先需要定义树生长的文法，根据文法进行每个树枝始末坐标的计算以及树叶位置坐标的计算。每个树枝和树叶根据自己的方向计算平移旋转的量；这样一步步根据文法将通过旋转到正确角度、平移到正确位置的树枝和树叶拼接在一起，就得到了一棵树。树的生长是根据文法的进一步迭代和树枝树叶数组加入新的对象实现的。

#### 实现

##### 规定文法

首先有一个**基础结构**（树苗），对其进行迭代得到最后的文法字符串。

> `FA[*+X][-/&X][/%X]B`
>
> <img src="C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/imgs/singleBranch.png" width="100">

###### 迭代

遍历字符串，遇到`X`则有一定概率加入一个**基础结构**。因此进行多次迭代后会有较长的文法字符串，如下：

> `FA[*+FA[*+X][-/&X][/%X]B][-/&FA[*+X][-/&X][/%X]B][/%FA[*+X][-/&X][/%X]B]B`

##### 解析文法并绘制树

###### 解析文法

- `F` - 添加树枝，当前位置为起点，根据旋转角度和树枝长度计算出终点位置

- `X` - 添加末端枝条，即树枝上带有叶片

- `A` - 【树枝变细】树枝的长度和半径按照一定比例缩小

- `B` - 【树枝变粗】在一个树枝绘制完毕回溯时使用

- `[` - 标识树枝开始

- `]` - 标识树枝结束

  > 整体使用一个栈保存每个结点的位置，每当新建一个树枝的时候新节点入栈，每当结束一个树枝的时候栈顶弹出。

- `+` - 绕x轴旋转正角度

- `-` - 绕x轴旋转负角度

- `*` - 绕y轴旋转正角度

- `/` - 绕y轴旋转负角度

- `&` - 绕z轴旋转正角度

- `%` - 绕z轴旋转负角度

###### 树枝

首先计算出单个圆柱体的控制顶点，并贴图构成树干。根据文法获得每一根树枝的起点和终点，并存入顶点数组。这样后期绘制圆柱体的步骤分为四步：

1. 绘制基础圆柱体：起点为原点，终点在y轴上
2. 计算缩放矩阵：根据起点终点距离获得树枝长度，根据解析文法时的存入的半径进行树枝粗细的缩放
3. 计算旋转矩阵：计算当前圆向量（竖直向上）与目标向量（从树枝的起点到终点）的叉积；标准化后点乘获得二者的夹角 => 得到旋转轴和旋转角即可用`rotate`函数获得旋转矩阵
4. 计算平移矩阵：平移到树枝起点位置

###### 树叶

计算出树叶的起点和终点坐标，在方形平面上贴图，根据树叶起点和终点的位置进行相应平移旋转变换即可得到树叶的坐标。

总体的缩放、平移、旋转和树枝相似，且树叶没有长度只有半径，而且半径为常量。

##### 树的生长

我们希望的是通过鼠标在屏幕上停留一段时间不移动作为树生长的条件。因此在main中计算鼠标上一次移动所经过的时间，并传入树的display()函数，在while循环中不断进行判断：

```cpp
if (interval > GROWINTERVAL) { // interval为main中的stopStartTime
    grow();
    stopStartTime = glfwGetTime();
}
```

在处理鼠标移动的回调函数中进行判断：

```cpp
// 更新停止移动鼠标开始的时间
stopStartTime = glfwGetTime();
```

#### 效果

##### 静态绘制

<img src="C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/imgs/tree.png" width="200">

##### 动态生长

<img src="C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/imgs/growing.gif" width="400"/>



### 倒影（curry）

### 地形生成

实在想不到terrain可以归属到Basic和Bonus的哪一个模块，干脆就放到最底下单独说一下。（个人认为可以拆分到texture和model import中，当然是一种从heightmap图像中引入model的特殊方式）。

#### 简介

这里的地形是根据一副平面的地形贴图得到的，根据灰度贴图的r通道数值决定地形的高低。为了使得地形实现得更加逼真，在不同的高度采用不同的贴图，比如最底下是沙地（sand），虽然在渲染的时候被水遮挡了；向上是草地和沙地的结合；之后是草地和石头的结合。并且根据坡度的变化调节二者再结合过程中的占比。

原理如下：

1. 生成三角形网格
2. 将三角形网格和图片上的点形成对应关系（即把纹理贴在三角形网格上）
3. 将纹理的r通道值作为顶点的高度（这一步在vs中实现）

经过以上步骤，我们就获得了一个由三角形网格构成的有高低变化的地形。

#### 实现

将贴图传入顶点着色器之后，使用以下语句，读取贴图对应位置的r通道颜色值：

```cpp
float height = texture(heightMapTex, UV).r;
```

#### 效果

<img src="C:/Users/Sherry/OneDrive%20-%20%E4%B8%AD%E5%B1%B1%E5%A4%A7%E5%AD%A6/%E5%A4%A7%E4%B8%89%E4%B8%8B/ComputerGraphics/Final%20Project/TryLSystem/Project1/imgs/terrain.png" width="500">

## 遇到的问题和解决方案（偷偷删掉）

## 小组成员分工

|  姓名  |   学号   |                           分工内容                           |
| :----: | :------: | :----------------------------------------------------------: |
| 周远笛 | 16340311 | Camera Roaming, Simple Lighting and Shading, Texture Mapping, Model Import & Mesh viewing, Skybox, Fluid Simulation, LSystem, Terraingit |
| 杨泓臻 | 16340269 |                 粒子系统，重力系统，处理冲突                 |