typedef int ValueT;
const ValueT INF = 1<<29;

struct Edge {
	int from, to;
	ValueT weight;
	Edge(int a, int b, ValueT c) {from=a; to=b; weight=c;}
};

struct Node {	
	ValueT dist; 
	int idx;
	bool visited;
	Node() {dist=INF; idx=-1; visited=false;}
	Node(int i) {dist=INF; idx=i; visited=false;}
};
