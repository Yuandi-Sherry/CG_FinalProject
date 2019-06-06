#ifndef  _TREE_H_
#define  _TREE_H_
typedef enum _TreeType //��������
{
	Tree_0 = 0,
	Tree_1 = 1,
} TreeType;

typedef enum _LeafType //��Ҷ������
{
	Leaf_0 = 0,
	Leaf_1 = 1,
} LeafType;

class Leaf //��Ҷ
{
public:
	LeafType L_type;
	double radius = 3.00;//ҶƬ�뾶
	Leaf() {}
	Leaf(LeafType type) :L_type(type) {}
	//������Ҷ���ͣ���Ҷ���ͣ�
	void update_type(LeafType type) {
		L_type = type;
	}
	//����ҶƬ�뾶
	void update_radius(double r) {
		radius = r;
	}
	~Leaf() {}
};

class Trunk //����
{
public:
	TreeType T_type;//��������
	double length = 10.0;//��֦����
	double length_shrink = 0.75;//��֦����������
	double radius = 1.0;//��֦�뾶
	double radius_shrink = 0.75;//��֦�뾶������
	double leap_x = 35.00;//��֦_x��б��
	double leap_y = 30.00;//��֦_y��б��
	double leap_z = 30.00;//��֦_z��б��
	Trunk() {}
	Trunk(TreeType type) :T_type(type) {}
	//������֦���ͣ����ͣ�
	void update_type(TreeType type) {
		T_type = type;
	}
	//������֦������Ϣ�����ȣ������ʣ�
	void update_length(double len, double len_shrink) {
		length = len;
		length_shrink = len_shrink;
	}
	//������֦�뾶��Ϣ���뾶�������ʣ�
	void update_radius(double r, double r_shrink) {
		radius = r;
		radius_shrink = r_shrink;
	}
	//������֦�Ƕȣ�x,y,z��
	void update_leap(double x, double y, double z) {
		leap_x = x;
		leap_y = y;
		leap_z = z;
	}
	~Trunk() {}
};

class Tree //��
{
public:
	TreeType type;
	Trunk trunk;
	Leaf leaf;
	Tree() :type(Tree_0), trunk(Tree_0), leaf(Leaf_0) {}//Ĭ������
	Tree(TreeType ttype, LeafType ltype) :type(ttype), trunk(ttype), leaf(ltype) {}//ѡ��tree����
	~Tree() {}
};
#endif // ! _TREE_H_


