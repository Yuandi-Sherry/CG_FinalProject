#include "text.h"

Text::Text()
{
}

Text::~Text()
{
	
}

void Text::init() {
	//����Ҫ��ʾ�����ּ�����	

	std::wstring text = L"���ʡ�IPOC OSG";

	for (const auto &c : text)
	{
		//��ȡ������Ϣ
		if (c == ' ')
		{
			advances.back() *= 2;
			continue;
		}
		FreeTypeFont temp_char(c, "./fonts/stxinwei.ttf");
		//���ÿ�����εĲ������
		advances.push_back(temp_char.advanceX());
		//��������Ϣ������Ƶ�Ԫ
		Glyph3D glyph = temp_char.getGlyph3D();
		//����3D����ģ��
		computeGlyphGeometry(glyph, 3.0);

		std::vector<glm::vec3> normals = glyph.getNormalArray();
		ElementArray indices = glyph.getIndices();
		std::vector<Vertex> verts(indices.size());

		for (size_t i = 0; i < indices.size(); ++i)
			verts.push_back({ glyph._vertices[indices[i]], normals[i], glm::vec2() });

		string3D.emplace_back(verts);
		//���������
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
//	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
//					   // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
//		isFirstCall = 0;
//
//		// ����MAX_CHAR����������ʾ�б���
//		lists = glGenLists(MAX_CHAR);
//
//		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
//		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
//	}
//	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
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