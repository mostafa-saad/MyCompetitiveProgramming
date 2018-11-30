// Jan Kanty Milczek

#include <cstdio>

int max(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}
int max(int x, int y, int z) {
	return max(x, max(y, z));
}

struct PersTree {
	PersTree *l, *r;
	int key;
	int value;
	int max_value;

	int find(int) const;
	PersTree *add(int, int) const;

	PersTree(PersTree *_l, PersTree *_r, int _key, int _value, int _max_value) : l(_l), r(_r), key(_key), value(_value), max_value(_max_value) {}

};

int safe_max_value(PersTree *x) {
	if (x == NULL)
		return 0;
	return x->max_value;
}

int PersTree::find(int mxkey) const {
	if (mxkey < key)
		return l->find(mxkey);
	else if (mxkey == key)
		return max(safe_max_value(l), value);
	else // if (mxkey > key)
		return max(safe_max_value(l), value, r->find(mxkey));
}

PersTree *PersTree::add(int _key, int nvalue) const {
	PersTree *_l = l;
	PersTree *_r = r;
	int _value = value;

	if (_key < key)
		_l = l->add(_key, nvalue);
	else if (_key == key)
		_value = nvalue;
	else // if (_key > key)
		_r = r->add(_key, nvalue);

	return new PersTree(_l, _r, key, _value, max(safe_max_value(_l), _value, safe_max_value(_r)));
}

PersTree *create_pers_tree(int left, int right) {
	if (left > right)
		return NULL;
	int s = (left + right) / 2;
	return new PersTree(create_pers_tree(left, s - 1), create_pers_tree(s + 1, right), s, 0, 0);
}

int n;
const int M = 3e5 + 5;
PersTree *akt[M];
int wyn[M];
int main() {
	scanf("%d", &n);
	akt[0] = create_pers_tree(0, n);
	wyn[0] = 0;

	for (int i = 1; i <= n; ++i) {
		int op;
		scanf("%d", &op);
		if (op > 0) {
			wyn[i] = op;
			akt[i] = akt[i-1]->add(0, i);
		} else {
			int cof = akt[i-1]->find(-op-1) - 1;
			wyn[i] = wyn[cof];
			akt[i] = akt[cof]->add(-op, i);
		}
    printf("%d\n", wyn[i]);
	}
}
