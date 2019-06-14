#include "text.h"

Text::Text()
{
}

Text::~Text()
{
	
}

void Text::init() {
	//输入要显示的文字及字体	

	std::wstring text = L"北邮·IPOC OSG";

	for (const auto &c : text)
	{
		//获取字形信息
		if (c == ' ')
		{
			advances.back() *= 2;
			continue;
		}
		FreeTypeFont temp_char(c, "./fonts/stxinwei.ttf");
		//添加每个字形的步进宽度
		advances.push_back(temp_char.advanceX());
		//将字形信息存入绘制单元
		Glyph3D glyph = temp_char.getGlyph3D();
		//生成3D文字模型
		computeGlyphGeometry(glyph, 3.0);

		std::vector<glm::vec3> normals = glyph.getNormalArray();
		ElementArray indices = glyph.getIndices();
		std::vector<Vertex> verts(indices.size());

		for (size_t i = 0; i < indices.size(); ++i)
			verts.push_back({ glyph._vertices[indices[i]], normals[i], glm::vec2() });

		string3D.emplace_back(verts);
		//调试用输出
		//glyph.output();
	}	

	textShader.init("text3D.vs", "text3D.fs");
}

//void Text::selectFont(int size, int charset, const char* face) {
//	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
//		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
//		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
//	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
//	DeleteObject(hOldFont);
//}
//
//void Text::drawString(const char* str) {
//	static int isFirstCall = 1;
//	static GLuint lists;
//
//	if (isFirstCall) { // 如果是第一次调用，执行初始化
//					   // 为每一个ASCII字符产生一个显示列表
//		isFirstCall = 0;
//
//		// 申请MAX_CHAR个连续的显示列表编号
//		lists = glGenLists(MAX_CHAR);
//
//		// 把每个字符的绘制命令都装到对应的显示列表中
//		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
//	}
//	// 调用每个字符对应的显示列表，绘制每个字符
//	for (; *str != '\0'; ++str)
//		glCallList(lists + *str);
//}

void Text::display(const char* str, Camera camera) {	

	//selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	/*glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.7f, 0.4f);	
	drawString(str);*/


	//view matrix and projection matrix
	/*glm::mat4 view = camera.getViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(camera.zoom), (GLfloat)WIDTH / HEIGHT, 0.1f, 100.0f);

	glBindBuffer(GL_UNIFORM_BUFFER, Uniforms[VPmatrix]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(proj));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);*/


	/*sLights[0].position = camera.position;
	sLights[0].direction = camera.front;
	GLuint baseOffset = 64 + PointLightNum * 80;
	sLights[0].setUniform(Uniforms[lights], baseOffset);*/

	textShader.use();
	textShader.setVec3("viewPos", camera.Position);
	for (size_t i = 0, advance = 0; i < string3D.size(); advance += advances[i], ++i)
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.9 + advance * 0.05f, 0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		textShader.setMat4("model", model);

		string3D[i].draw(textShader);
	}

}