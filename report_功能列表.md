### 实现的功能列表
#### Basic
1. Camera Roaming
2. Simple lighting and shading(phong)
3. Texture mapping
4. Model import & Mesh viewing (Assimp)

#### Bonus
1. Sky Box (天空盒)
2. Display Text (显示文字，中文/英文/立体/平面)
3. Stencil Test (模板测试)
4. Complex Lighting (复杂光照: Gamma矫正、法线贴图、HDR、SSAO…)
5. Gravity System and Collision Detection (重力系统与碰撞检测)
6. Particle System (粒子系统: 渲染雨、雪、雾等)
7. Anti-Aliasing (抗锯齿)
8. Fluid Simulation (流体模拟)
9. L system和树生长
10. reflect

### 功能点介绍
#### Basic

#### Bonus
**粒子系统**
每一滴雨都是一个粒子，通过粒子生成器particleGenerator来对粒子进行统一的管理，持续不断地生成新的粒子，以及将过期的粒子进行回收，避免内存的过度占用。

一般的粒子有一个生存周期life值，但是因为雨受重力控制，生存周期是从产生到落地，所以根据粒子位置的y值来判断粒子是否处于存活状态。

关于粒子用什么形状，本来有考虑过用贴图水滴的图片，但是因为雨的下落速度较快，正常观察到的不是水珠而是类似线端，所以以线段来作为粒子的显示形状。

如何控制雨量的大小，通过控制粒子的下落速度和每次更新增加的粒子数量来实现。
![](yhz-imgs/rain.PNG)
**重力系统**
对每个粒子加一个y轴的向量velocity作为重力，每次刷新测得时间差，对粒子的位置position加上velocity进行更新。

###分工
|姓名|学号|分工内容|
|:-:|:-:|:-:|
|杨泓臻|16340269|粒子系统，重力系统，处理冲突|