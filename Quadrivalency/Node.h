#pragma once

struct Node {
	Node(Node *parent, int x, float f, float g, float   h) {
		_parent = parent;
		_x = x;
		_f = f;
		_g = g;
		_h = h;
	}
	Node *_parent;
	int _x;
	float _f, _g, _h;
};

