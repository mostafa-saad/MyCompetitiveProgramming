#include <cstdio>
#include <cstring>
#include <stack>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct HTMLelement {
	string id;
	set<int> classes;
	vector<int> children;
	HTMLelement() {}
	HTMLelement(char *name):
		id(name) {}

	void add_child(int child_id) {
		children.push_back(child_id);
	}

	void add_class(char *str) {
		int hash = 0;
		for(char *ptr = str; *ptr; ++ptr)
			hash = hash * 71 + *ptr - 'a' + 1;
		classes.insert(hash);
	}
};

struct SelectorElement {
	int type;
	vector<int> classes;
	SelectorElement(int type):
		type(type) {}

	void add_class(char *str) {
		int hash = 0;
		for(char *ptr = str; *ptr; ++ptr)
			hash = hash * 71 + *ptr - 'a' + 1;
		classes.push_back(hash);
	}

	bool check(const HTMLelement &E) {
		for(auto cls : classes)
			if(E.classes.find(cls) == E.classes.end())
				return 0;
		return 1;
	}
};

vector<HTMLelement> read_document(void) {
	int N; scanf("%d", &N);

	stack<int> ancestors;

	vector<HTMLelement> tree;
	tree.push_back(HTMLelement());
	ancestors.push(0);

	for(int i = 0; i < N; ++i) {
		char tag_start[11];
		scanf("%s", tag_start);
		if(strcmp(tag_start, "</div>") == 0) {
			ancestors.pop();
		} else {
			char name[31];
			scanf(" id='%[^']'", name);

			tree.push_back(HTMLelement(name));
			tree[ancestors.top()].add_child(tree.size() - 1);
			ancestors.push(tree.size() - 1);

			scanf(" class='");
			char class_name[31];
			while(scanf(" %[^ ']", class_name))
				tree.back().add_class(class_name);
			scanf("'>");
		}
	}

	return tree;
}

vector<SelectorElement> read_selector(void) {
	vector<SelectorElement> sel;

	char c;
	while(scanf("%c", &c)) {
		if(c == ' ') continue;
		if(c == '\n') break;
		if(c == '>') {
			sel.push_back(SelectorElement(0));
			scanf(" %c", &c);
		} else
			sel.push_back(SelectorElement(1));
	
		sel.push_back(SelectorElement(2));

		char class_name[21];
		while(scanf("%[^. \n]", class_name)) {
			sel.back().add_class(class_name);
			scanf(".");
		}
	}

	return sel;
}

vector<HTMLelement> DocumentTree;
vector<SelectorElement> Selector;
bool visited[2][5010][5010];

void dfs(int jump, int node, int pos, vector<int> &ans) {
	if(visited[jump][node][pos]) return;
	visited[jump][node][pos] = 1;

	if(pos == Selector.size()) {
		if(!jump) ans.push_back(node);
		return;
	}

	if(Selector[pos].type == 0) {
		for(auto child : DocumentTree[node].children)
			dfs(0, child, pos + 1, ans);
	}

	if(Selector[pos].type == 1) {
		if(jump) dfs(0, node, pos + 1, ans);
		for(auto child : DocumentTree[node].children)
			dfs(1, child, pos, ans);
	}

	if(Selector[pos].type == 2) {
		if(!Selector[pos].check(DocumentTree[node])) return;
		dfs(0, node, pos + 1, ans);
	}
}

int main(void) {
	
	DocumentTree = read_document();

	int M; scanf("%d\n", &M);
	for(int i = 0; i < M; ++i) {
		Selector = read_selector();

		memset(visited, 0, sizeof visited);
		vector<int> ans;

		dfs(0, 0, 0, ans);

		printf("%d ", (int)ans.size());
		sort(ans.begin(), ans.end());
		for(auto id : ans) printf("%s ", DocumentTree[id].id.c_str());
		printf("\n");
	}

	return 0;

}
