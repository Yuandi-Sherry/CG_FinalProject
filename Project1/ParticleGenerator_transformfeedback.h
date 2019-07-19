#pragma once
#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <glad/glad.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "shader.h"
#include "utils.h"

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
//最大速度
#define MAX_VELOC glm::vec3(0.0,-3.0,0.0)
	//最小速度
#define MIN_VELOC glm::vec3(0.0,-1.0,0.0)
	//发射粒子最大周期
#define MAX_LAUNCH 1.0f*1000.0f
	//发射粒子最小周期
#define MIN_LAUNCH 0.5f*1000.0f
	//初始点精灵大小
#define INIT_SIZE 10.0f
#define MAX_SIZE 10.0f
#define MIN_SIZE 3.0f


const int MAX_PARTICLES = 5000;//定义粒子发射系统最大的粒子数
								   //初始发射器例子数量
const int INIT_PARTICLES = 500;
//落雪中心
const glm::vec3 center(0.0f);
const float areaLength = 500.0f;
const float fallHeight = 180.0f;

struct SnowParticle
{
	float type;
	glm::vec3 position;
	glm::vec3 velocity;
	float lifetimeMills;//年龄
	float size;//粒子点精灵大小
};



class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator();
	void init();
	void display(float frametimeMills);
private:
	bool initSnow();
	void updateParticles(float frametimeMills);//更新粒子的位置等
	void initRandomTexture(unsigned int size);//生成1维随机纹理
	void renderParticles(glm::mat4& worldMatrix, glm::mat4& viewMatrix, glm::mat4& projectMatrix);
	void genInitLocation(SnowParticle partciles[], int nums);//生成初始粒子

	unsigned int mCurVBOIndex, mCurTransformFeedbackIndex;
	GLuint mParticleBuffers[2]; //粒子发射系统的两个顶点缓存区
	GLuint mParticleArrays[2];
	GLuint mTransformFeedbacks[2];//粒子发射系统对应的TransformFeedback
	GLuint mRandomTexture;//随机一维纹理
	GLuint mParticleTexture;//Alpha纹理
	float mTimer;//粒子发射器已经发射的时间
	bool mFirst;
	Shader* mUpdateShader;//更新粒子的GPUProgram
	Shader* mRenderShader;//渲染粒子的GPUProgram
};

#endif