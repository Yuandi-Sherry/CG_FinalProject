#ifndef  _TREE_H_
#define  _TREE_H_
typedef enum _TreeType //树的类型
{
	Tree_0 = 0,
	Tree_1 = 1,
} TreeType;

typedef enum _LeafType //树叶的类型
{
	Leaf_0 = 0,
	Leaf_1 = 1,
} LeafType;

class Leaf //树叶
{
public:
	LeafType L_type;
	double radius = 3.00;//叶片半径
	Leaf() {}
	Leaf(LeafType type) :L_type(type) {}
	//更新树叶类型（树叶类型）
	void update_type(LeafType type) {
		L_type = type;
	}
	//更新叶片半径
	void update_radius(double r) {
		radius = r;
	}
	~Leaf() {}
};

class Trunk //树干
{
public:
	TreeType T_type;//树干类型
	double length = 10.0;//树枝长度
	double length_shrink = 0.75;//树枝长度收缩率
	double radius = 1.0;//树枝半径
	double radius_shrink = 0.75;//树枝半径收缩率
	double leap_x = 35.00;//树枝_x倾斜角
	double leap_y = 30.00;//树枝_y倾斜角
	double leap_z = 30.00;//树枝_z倾斜角
	Trunk() {}
	Trunk(TreeType type) :T_type(type) {}
	//更新树枝类型（类型）
	void update_type(TreeType type) {
		T_type = type;
	}
	//更新树枝长度信息（长度，收缩率）
	void update_length(double len, double len_shrink) {
		length = len;
		length_shrink = len_shrink;
	}
	//更新树枝半径信息（半径，收缩率）
	void update_radius(double r, double r_shrink) {
		radius = r;
		radius_shrink = r_shrink;
	}
	//更新树枝角度（x,y,z）
	void update_leap(double x, double y, double z) {
		leap_x = x;
		leap_y = y;
		leap_z = z;
	}
	~Trunk() {}
};

class Tree //树
{
public:
	TreeType type;
	Trunk trunk;
	Leaf leaf;
	Tree() :type(Tree_0), trunk(Tree_0), leaf(Leaf_0) {}//默认类型
	Tree(TreeType ttype, LeafType ltype) :type(ttype), trunk(ttype), leaf(ltype) {}//选择tree类型
	~Tree() {}
};
#endif // ! _TREE_H_


