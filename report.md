### 开发环境及使用到的第三方库

环境：opengl基础环境，无特殊dll。

第三方lib如下。

```
opengl_libs
├─include
│  │  ft2build.h
│  │  stb_image.h
│  │
│  ├─freetype
│  │  │  freetype.h
│  │  │  ftadvanc.h
│  │  │  ftautoh.h
│  │  │  ftbbox.h
│  │  │  ftbdf.h
│  │  │  ftbitmap.h
│  │  │  ftbzip2.h
│  │  │  ftcache.h
│  │  │  ftcffdrv.h
│  │  │  ftchapters.h
│  │  │  ftcid.h
│  │  │  fterrdef.h
│  │  │  fterrors.h
│  │  │  ftfntfmt.h
│  │  │  ftgasp.h
│  │  │  ftglyph.h
│  │  │  ftgxval.h
│  │  │  ftgzip.h
│  │  │  ftimage.h
│  │  │  ftincrem.h
│  │  │  ftlcdfil.h
│  │  │  ftlist.h
│  │  │  ftlzw.h
│  │  │  ftmac.h
│  │  │  ftmm.h
│  │  │  ftmodapi.h
│  │  │  ftmoderr.h
│  │  │  ftotval.h
│  │  │  ftoutln.h
│  │  │  ftpfr.h
│  │  │  ftrender.h
│  │  │  ftsizes.h
│  │  │  ftsnames.h
│  │  │  ftstroke.h
│  │  │  ftsynth.h
│  │  │  ftsystem.h
│  │  │  fttrigon.h
│  │  │  ftttdrv.h
│  │  │  fttypes.h
│  │  │  ftwinfnt.h
│  │  │  t1tables.h
│  │  │  ttnameid.h
│  │  │  tttables.h
│  │  │  tttags.h
│  │  │  ttunpat.h
│  │  │
│  │  ├─config
│  │  │      ftconfig.h
│  │  │      ftheader.h
│  │  │      ftmodule.h
│  │  │      ftoption.h
│  │  │      ftstdlib.h
│  │  │
│  │  └─internal
│  │      │  autohint.h
│  │      │  ftcalc.h
│  │      │  ftdebug.h
│  │      │  ftdriver.h
│  │      │  ftgloadr.h
│  │      │  fthash.h
│  │      │  ftmemory.h
│  │      │  ftobjs.h
│  │      │  ftpic.h
│  │      │  ftrfork.h
│  │      │  ftserv.h
│  │      │  ftstream.h
│  │      │  fttrace.h
│  │      │  ftvalid.h
│  │      │  internal.h
│  │      │  psaux.h
│  │      │  pshints.h
│  │      │  sfnt.h
│  │      │  t1types.h
│  │      │  tttypes.h
│  │      │
│  │      └─services
│  │              svbdf.h
│  │              svcid.h
│  │              svfntfmt.h
│  │              svgldict.h
│  │              svgxval.h
│  │              svkern.h
│  │              svmm.h
│  │              svotval.h
│  │              svpfr.h
│  │              svpostnm.h
│  │              svprop.h
│  │              svpscmap.h
│  │              svpsinfo.h
│  │              svsfnt.h
│  │              svttcmap.h
│  │              svtteng.h
│  │              svttglyf.h
│  │              svwinfnt.h
│  │
│  ├─GL
│  │      eglew.h
│  │      freeglut.h
│  │      freeglut_ext.h
│  │      freeglut_std.h
│  │      glew.h
│  │      glut.h
│  │      glxew.h
│  │      wglew.h
│  │
│  ├─glad
│  │      glad.h
│  │
│  ├─GLFW
│  │      glfw3.h
│  │      glfw3native.h
│  │
│  ├─glm
│  │  │  CMakeLists.txt
│  │  │  common.hpp
│  │  │  exponential.hpp
│  │  │  ext.hpp
│  │  │  fwd.hpp
│  │  │  geometric.hpp
│  │  │  glm.hpp
│  │  │  integer.hpp
│  │  │  mat2x2.hpp
│  │  │  mat2x3.hpp
│  │  │  mat2x4.hpp
│  │  │  mat3x2.hpp
│  │  │  mat3x3.hpp
│  │  │  mat3x4.hpp
│  │  │  mat4x2.hpp
│  │  │  mat4x3.hpp
│  │  │  mat4x4.hpp
│  │  │  matrix.hpp
│  │  │  packing.hpp
│  │  │  trigonometric.hpp
│  │  │  vec2.hpp
│  │  │  vec3.hpp
│  │  │  vec4.hpp
│  │  │  vector_relational.hpp
│  │  │
│  │  ├─detail
│  │  │      compute_common.hpp
│  │  │      compute_vector_relational.hpp
│  │  │      func_common.inl
│  │  │      func_common_simd.inl
│  │  │      func_exponential.inl
│  │  │      func_exponential_simd.inl
│  │  │      func_geometric.inl
│  │  │      func_geometric_simd.inl
│  │  │      func_integer.inl
│  │  │      func_integer_simd.inl
│  │  │      func_matrix.inl
│  │  │      func_matrix_simd.inl
│  │  │      func_packing.inl
│  │  │      func_packing_simd.inl
│  │  │      func_trigonometric.inl
│  │  │      func_trigonometric_simd.inl
│  │  │      func_vector_relational.inl
│  │  │      func_vector_relational_simd.inl
│  │  │      glm.cpp
│  │  │      qualifier.hpp
│  │  │      setup.hpp
│  │  │      type_float.hpp
│  │  │      type_half.hpp
│  │  │      type_half.inl
│  │  │      type_mat2x2.hpp
│  │  │      type_mat2x2.inl
│  │  │      type_mat2x3.hpp
│  │  │      type_mat2x3.inl
│  │  │      type_mat2x4.hpp
│  │  │      type_mat2x4.inl
│  │  │      type_mat3x2.hpp
│  │  │      type_mat3x2.inl
│  │  │      type_mat3x3.hpp
│  │  │      type_mat3x3.inl
│  │  │      type_mat3x4.hpp
│  │  │      type_mat3x4.inl
│  │  │      type_mat4x2.hpp
│  │  │      type_mat4x2.inl
│  │  │      type_mat4x3.hpp
│  │  │      type_mat4x3.inl
│  │  │      type_mat4x4.hpp
│  │  │      type_mat4x4.inl
│  │  │      type_mat4x4_simd.inl
│  │  │      type_quat.hpp
│  │  │      type_quat.inl
│  │  │      type_quat_simd.inl
│  │  │      type_vec1.hpp
│  │  │      type_vec1.inl
│  │  │      type_vec2.hpp
│  │  │      type_vec2.inl
│  │  │      type_vec3.hpp
│  │  │      type_vec3.inl
│  │  │      type_vec4.hpp
│  │  │      type_vec4.inl
│  │  │      type_vec4_simd.inl
│  │  │      _features.hpp
│  │  │      _fixes.hpp
│  │  │      _noise.hpp
│  │  │      _swizzle.hpp
│  │  │      _swizzle_func.hpp
│  │  │      _vectorize.hpp
│  │  │
│  │  ├─ext
│  │  │      matrix_clip_space.hpp
│  │  │      matrix_clip_space.inl
│  │  │      matrix_common.hpp
│  │  │      matrix_common.inl
│  │  │      matrix_double2x2.hpp
│  │  │      matrix_double2x2_precision.hpp
│  │  │      matrix_double2x3.hpp
│  │  │      matrix_double2x3_precision.hpp
│  │  │      matrix_double2x4.hpp
│  │  │      matrix_double2x4_precision.hpp
│  │  │      matrix_double3x2.hpp
│  │  │      matrix_double3x2_precision.hpp
│  │  │      matrix_double3x3.hpp
│  │  │      matrix_double3x3_precision.hpp
│  │  │      matrix_double3x4.hpp
│  │  │      matrix_double3x4_precision.hpp
│  │  │      matrix_double4x2.hpp
│  │  │      matrix_double4x2_precision.hpp
│  │  │      matrix_double4x3.hpp
│  │  │      matrix_double4x3_precision.hpp
│  │  │      matrix_double4x4.hpp
│  │  │      matrix_double4x4_precision.hpp
│  │  │      matrix_float2x2.hpp
│  │  │      matrix_float2x2_precision.hpp
│  │  │      matrix_float2x3.hpp
│  │  │      matrix_float2x3_precision.hpp
│  │  │      matrix_float2x4.hpp
│  │  │      matrix_float2x4_precision.hpp
│  │  │      matrix_float3x2.hpp
│  │  │      matrix_float3x2_precision.hpp
│  │  │      matrix_float3x3.hpp
│  │  │      matrix_float3x3_precision.hpp
│  │  │      matrix_float3x4.hpp
│  │  │      matrix_float3x4_precision.hpp
│  │  │      matrix_float4x2.hpp
│  │  │      matrix_float4x2_precision.hpp
│  │  │      matrix_float4x3.hpp
│  │  │      matrix_float4x3_precision.hpp
│  │  │      matrix_float4x4.hpp
│  │  │      matrix_float4x4_precision.hpp
│  │  │      matrix_projection.hpp
│  │  │      matrix_projection.inl
│  │  │      matrix_relational.hpp
│  │  │      matrix_relational.inl
│  │  │      matrix_transform.hpp
│  │  │      matrix_transform.inl
│  │  │      quaternion_common.hpp
│  │  │      quaternion_common.inl
│  │  │      quaternion_common_simd.inl
│  │  │      quaternion_double.hpp
│  │  │      quaternion_double_precision.hpp
│  │  │      quaternion_exponential.hpp
│  │  │      quaternion_exponential.inl
│  │  │      quaternion_float.hpp
│  │  │      quaternion_float_precision.hpp
│  │  │      quaternion_geometric.hpp
│  │  │      quaternion_geometric.inl
│  │  │      quaternion_relational.hpp
│  │  │      quaternion_relational.inl
│  │  │      quaternion_transform.hpp
│  │  │      quaternion_transform.inl
│  │  │      quaternion_trigonometric.hpp
│  │  │      quaternion_trigonometric.inl
│  │  │      scalar_common.hpp
│  │  │      scalar_common.inl
│  │  │      scalar_constants.hpp
│  │  │      scalar_constants.inl
│  │  │      scalar_int_sized.hpp
│  │  │      scalar_relational.hpp
│  │  │      scalar_relational.inl
│  │  │      scalar_uint_sized.hpp
│  │  │      scalar_ulp.hpp
│  │  │      scalar_ulp.inl
│  │  │      vector_bool1.hpp
│  │  │      vector_bool1_precision.hpp
│  │  │      vector_bool2.hpp
│  │  │      vector_bool2_precision.hpp
│  │  │      vector_bool3.hpp
│  │  │      vector_bool3_precision.hpp
│  │  │      vector_bool4.hpp
│  │  │      vector_bool4_precision.hpp
│  │  │      vector_common.hpp
│  │  │      vector_common.inl
│  │  │      vector_double1.hpp
│  │  │      vector_double1_precision.hpp
│  │  │      vector_double2.hpp
│  │  │      vector_double2_precision.hpp
│  │  │      vector_double3.hpp
│  │  │      vector_double3_precision.hpp
│  │  │      vector_double4.hpp
│  │  │      vector_double4_precision.hpp
│  │  │      vector_float1.hpp
│  │  │      vector_float1_precision.hpp
│  │  │      vector_float2.hpp
│  │  │      vector_float2_precision.hpp
│  │  │      vector_float3.hpp
│  │  │      vector_float3_precision.hpp
│  │  │      vector_float4.hpp
│  │  │      vector_float4_precision.hpp
│  │  │      vector_int1.hpp
│  │  │      vector_int1_precision.hpp
│  │  │      vector_int2.hpp
│  │  │      vector_int2_precision.hpp
│  │  │      vector_int3.hpp
│  │  │      vector_int3_precision.hpp
│  │  │      vector_int4.hpp
│  │  │      vector_int4_precision.hpp
│  │  │      vector_relational.hpp
│  │  │      vector_relational.inl
│  │  │      vector_uint1.hpp
│  │  │      vector_uint1_precision.hpp
│  │  │      vector_uint2.hpp
│  │  │      vector_uint2_precision.hpp
│  │  │      vector_uint3.hpp
│  │  │      vector_uint3_precision.hpp
│  │  │      vector_uint4.hpp
│  │  │      vector_uint4_precision.hpp
│  │  │      vector_ulp.hpp
│  │  │      vector_ulp.inl
│  │  │
│  │  ├─gtc
│  │  │      bitfield.hpp
│  │  │      bitfield.inl
│  │  │      color_space.hpp
│  │  │      color_space.inl
│  │  │      constants.hpp
│  │  │      constants.inl
│  │  │      epsilon.hpp
│  │  │      epsilon.inl
│  │  │      integer.hpp
│  │  │      integer.inl
│  │  │      matrix_access.hpp
│  │  │      matrix_access.inl
│  │  │      matrix_integer.hpp
│  │  │      matrix_inverse.hpp
│  │  │      matrix_inverse.inl
│  │  │      matrix_transform.hpp
│  │  │      matrix_transform.inl
│  │  │      noise.hpp
│  │  │      noise.inl
│  │  │      packing.hpp
│  │  │      packing.inl
│  │  │      quaternion.hpp
│  │  │      quaternion.inl
│  │  │      quaternion_simd.inl
│  │  │      random.hpp
│  │  │      random.inl
│  │  │      reciprocal.hpp
│  │  │      reciprocal.inl
│  │  │      round.hpp
│  │  │      round.inl
│  │  │      type_aligned.hpp
│  │  │      type_precision.hpp
│  │  │      type_precision.inl
│  │  │      type_ptr.hpp
│  │  │      type_ptr.inl
│  │  │      ulp.hpp
│  │  │      ulp.inl
│  │  │      vec1.hpp
│  │  │
│  │  ├─gtx
│  │  │      associated_min_max.hpp
│  │  │      associated_min_max.inl
│  │  │      bit.hpp
│  │  │      bit.inl
│  │  │      closest_point.hpp
│  │  │      closest_point.inl
│  │  │      color_encoding.hpp
│  │  │      color_encoding.inl
│  │  │      color_space.hpp
│  │  │      color_space.inl
│  │  │      color_space_YCoCg.hpp
│  │  │      color_space_YCoCg.inl
│  │  │      common.hpp
│  │  │      common.inl
│  │  │      compatibility.hpp
│  │  │      compatibility.inl
│  │  │      component_wise.hpp
│  │  │      component_wise.inl
│  │  │      dual_quaternion.hpp
│  │  │      dual_quaternion.inl
│  │  │      easing.hpp
│  │  │      easing.inl
│  │  │      euler_angles.hpp
│  │  │      euler_angles.inl
│  │  │      extend.hpp
│  │  │      extend.inl
│  │  │      extended_min_max.hpp
│  │  │      extended_min_max.inl
│  │  │      exterior_product.hpp
│  │  │      exterior_product.inl
│  │  │      fast_exponential.hpp
│  │  │      fast_exponential.inl
│  │  │      fast_square_root.hpp
│  │  │      fast_square_root.inl
│  │  │      fast_trigonometry.hpp
│  │  │      fast_trigonometry.inl
│  │  │      float_notmalize.inl
│  │  │      functions.hpp
│  │  │      functions.inl
│  │  │      gradient_paint.hpp
│  │  │      gradient_paint.inl
│  │  │      handed_coordinate_space.hpp
│  │  │      handed_coordinate_space.inl
│  │  │      hash.hpp
│  │  │      hash.inl
│  │  │      integer.hpp
│  │  │      integer.inl
│  │  │      intersect.hpp
│  │  │      intersect.inl
│  │  │      io.hpp
│  │  │      io.inl
│  │  │      log_base.hpp
│  │  │      log_base.inl
│  │  │      matrix_cross_product.hpp
│  │  │      matrix_cross_product.inl
│  │  │      matrix_decompose.hpp
│  │  │      matrix_decompose.inl
│  │  │      matrix_factorisation.hpp
│  │  │      matrix_factorisation.inl
│  │  │      matrix_interpolation.hpp
│  │  │      matrix_interpolation.inl
│  │  │      matrix_major_storage.hpp
│  │  │      matrix_major_storage.inl
│  │  │      matrix_operation.hpp
│  │  │      matrix_operation.inl
│  │  │      matrix_query.hpp
│  │  │      matrix_query.inl
│  │  │      matrix_transform_2d.hpp
│  │  │      matrix_transform_2d.inl
│  │  │      mixed_product.hpp
│  │  │      mixed_product.inl
│  │  │      norm.hpp
│  │  │      norm.inl
│  │  │      normal.hpp
│  │  │      normal.inl
│  │  │      normalize_dot.hpp
│  │  │      normalize_dot.inl
│  │  │      number_precision.hpp
│  │  │      number_precision.inl
│  │  │      optimum_pow.hpp
│  │  │      optimum_pow.inl
│  │  │      orthonormalize.hpp
│  │  │      orthonormalize.inl
│  │  │      perpendicular.hpp
│  │  │      perpendicular.inl
│  │  │      polar_coordinates.hpp
│  │  │      polar_coordinates.inl
│  │  │      projection.hpp
│  │  │      projection.inl
│  │  │      quaternion.hpp
│  │  │      quaternion.inl
│  │  │      range.hpp
│  │  │      raw_data.hpp
│  │  │      raw_data.inl
│  │  │      rotate_normalized_axis.hpp
│  │  │      rotate_normalized_axis.inl
│  │  │      rotate_vector.hpp
│  │  │      rotate_vector.inl
│  │  │      scalar_multiplication.hpp
│  │  │      scalar_relational.hpp
│  │  │      scalar_relational.inl
│  │  │      spline.hpp
│  │  │      spline.inl
│  │  │      std_based_type.hpp
│  │  │      std_based_type.inl
│  │  │      string_cast.hpp
│  │  │      string_cast.inl
│  │  │      texture.hpp
│  │  │      texture.inl
│  │  │      transform.hpp
│  │  │      transform.inl
│  │  │      transform2.hpp
│  │  │      transform2.inl
│  │  │      type_aligned.hpp
│  │  │      type_aligned.inl
│  │  │      type_trait.hpp
│  │  │      type_trait.inl
│  │  │      vector_angle.hpp
│  │  │      vector_angle.inl
│  │  │      vector_query.hpp
│  │  │      vector_query.inl
│  │  │      vec_swizzle.hpp
│  │  │      wrap.hpp
│  │  │      wrap.inl
│  │  │
│  │  └─simd
│  │          common.h
│  │          exponential.h
│  │          geometric.h
│  │          integer.h
│  │          matrix.h
│  │          packing.h
│  │          platform.h
│  │          trigonometric.h
│  │          vector_relational.h
│  │
│  └─KHR
│          khrplatform.h
│
├─lib
│      freeglut.lib
│      freeglutd.lib
│      freetype.lib
│      freetyped.lib
│      glew32.lib
│      glew32s.lib
│      glfw3.lib
│
└─src
        glad.c
        stb_image.cpp
```

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

**显示字体**
一开始打算在 GitHub 上找一些比较好看的字体库来使用，找了一段时间找到过两个好一些的库，一个是渲染 3d 字体，一个是渲染 2d 字体，经测试后发现该 3d字体库 用的依赖较老且存在一些内部问题，该 2d字体库 则与项目不兼容，便决定老老实实跟着 freetype 的教程自己渲染 2d 的字体，花了些时间去找一些比较漂亮的2d字体。

- 测试阶段。  
配置过程主要是要解决依赖问题，花了点时间，此效果为已通过测试，但尚未加入项目中。
![](./xt-imgs/text1.png)
- 实现阶段。实现目标：在场景中显示时间戳，植物的生长状态会根据时间变化（比如每过十五分钟或半个小时，树长大一点）。
![](./xt-imgs/text2.png)

#### 遇到的问题

**显示字体**
按着教程实现字体的渲染还算简单，如测试阶段，但在实现阶段遇到了一些问题，主要是在项目中整合测试阶段所用的渲染字体代码时，导致场景其他物体显示不正常，比如树的叶子有些显示出来有些显示不出来，整个terrain不见了。

这个问题原因找了很久，后来发现是树的叶子显示不全是设置了 glEnable(GL_CULL_FACE) 导致被剔除了一部分；整个terrain消失则是因为变透明了，在与字体混合时，字体的渲染需要 glEnable(GL_BLEND)，而一同使用的 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) 则定义了 alpha 通道的混合模式，glBlendFunc() 可以用来解决纹理混合以及显示半透明纹理的需求。最后那个 GL_ONE_MINUS_SRC_ALPHA 有对字体的前景背景对调方便字体显示，导致了 terrain 变透明。解决方案就是等字体渲染完之后 glDisable(GL_BLEND)。

### 分工

|姓名|学号|分工内容|
|:-:|:-:|:-:|
|杨泓臻|16340269|粒子系统，重力系统，处理冲突|
|谢涛|16340255|显示名字|