#include "CountyRecord.h"
#include <QuadTreePointFinder.h>
#include "Maxheap.h"
#include <iostream> 
#include <cmath> 
#include <string.h>
#include<vector>
using namespace std;
using Node = QuadTreePointFinder::Node;
using Point = QuadTreePointFinder::Point;

//shoudl these be static?
static int NE = 1;
static int NW = 2;
static int SE = 3;
static int SW = 4;

// The main quadtree class 
class Quad 
{ 
	// Hold details of the boundary of this node 
	Point topLeft; 
	Point botRight; 
	int numpoints;
	// Contains details of node 
	Node *n; 

	// Children of this tree 
	Quad *topLeftTree; //NW
	Quad *topRightTree; //NE
	Quad *botLeftTree;  // SW
	Quad *botRightTree;  // SE
	

public: 
	Quad() 
	{ 
		topLeft = Point(0, 0); 
		botRight = Point(0, 0); 
		numpoints = 0;
		n = NULL; 
		topLeftTree = NULL; 
		topRightTree = NULL; 
		botLeftTree = NULL; 
		botRightTree = NULL; 
	} 
	Quad(Point topL, Point botR) 
	{ 
		n = NULL; 
		topLeftTree = NULL; 
		topRightTree = NULL; 
		botLeftTree = NULL; 
		botRightTree = NULL; 
		topLeft = topL; 
		botRight = botR; 
	} 
	void insert(Node*); 
	Node* search(Point); 
	bool inBoundary(Point); 
	vector<Node> knn(int k, Quad& quad, float longi, float lati, MaxHeap<float, Point>& heap);
}; 

// Insert a node into the quadtree 
void Quad::insert(Node *node) 
{ 
	if (node == NULL) 
		return; 

	// Current quad cannot contain it 
	if (!inBoundary(node->pos)) 
		return; 

	// We are at a quad of unit area 
	// We cannot subdivide this quad further 
	if (abs(topLeft.x - botRight.x) <= 1 && 
		abs(topLeft.y - botRight.y) <= 1) 
	{ 
		if (n == NULL){
			n = node; 
			numpoints++;
		return; }
			
	} 

	if ((topLeft.x + botRight.x) / 2 >= node->pos.x) 
	{ 
		// Indicates topLeftTree 
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) 
		{ 
			if (topLeftTree == NULL) 
				topLeftTree = new Quad( 
					Point(topLeft.x, topLeft.y), 
					Point((topLeft.x + botRight.x) / 2, 
						(topLeft.y + botRight.y) / 2)); 
			topLeftTree->insert(node); 
		} 

		// Indicates botLeftTree 
		else
		{ 
			if (botLeftTree == NULL) 
				botLeftTree = new Quad( 
					Point(topLeft.x, 
						(topLeft.y + botRight.y) / 2), 
					Point((topLeft.x + botRight.x) / 2, 
						botRight.y)); 
			botLeftTree->insert(node); 
		} 
	} 
	else
	{ 
		// Indicates topRightTree 
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) 
		{ 
			if (topRightTree == NULL) 
				topRightTree = new Quad( 
					Point((topLeft.x + botRight.x) / 2, 
						topLeft.y), 
					Point(botRight.x, 
						(topLeft.y + botRight.y) / 2)); 
			topRightTree->insert(node); 
		} 

		// Indicates botRightTree 
		else
		{ 
			if (botRightTree == NULL) 
				botRightTree = new Quad( 
					Point((topLeft.x + botRight.x) / 2, 
						(topLeft.y + botRight.y) / 2), 
					Point(botRight.x, botRight.y)); 
			botRightTree->insert(node); 
		} 
	} 
} 

Node* Quad::search(Point p) 
{ 
	// Current quad cannot contain it 
	if (!inBoundary(p)) 
		return NULL; 

	// We are at a quad of unit length 
	// We cannot subdivide this quad further 
	if (n != NULL) 
	{
		n->visited = true;
		return n; 
	}

	if ((topLeft.x + botRight.x) / 2 >= p.x) 
	{ 
		// Indicates topLeftTree 
		if ((topLeft.y + botRight.y) / 2 >= p.y) 
		{ 
			if (topLeftTree == NULL) 
				return NULL; 
			return topLeftTree->search(p); 
		} 

		// Indicates botLeftTree 
		else
		{ 
			if (botLeftTree == NULL) 
				return NULL; 
			return botLeftTree->search(p); 
		} 
	} 
	else
	{ 
		// Indicates topRightTree 
		if ((topLeft.y + botRight.y) / 2 >= p.y) 
		{ 
			if (topRightTree == NULL) 
				return NULL; 
			return topRightTree->search(p); 
		} 

		// Indicates botRightTree 
		else
		{ 
			if (botRightTree == NULL) 
				return NULL; 
			return botRightTree->search(p); 
		} 
	} 
}; 



// Check if current quadtree contains the point 
bool Quad::inBoundary(Point p) 
{ 
	return (p.x >= topLeft.x && 
		p.x <= botRight.x && 
		p.y >= topLeft.y && 
		p.y <= botRight.y); 
} 

float findDistance(float long1,float lat1,float long2,float lat2){
	float x = (long2 - long1) * cos((lat1 + lat2)/2);
	float y = lat2 - lat1;
	return (sqrt(x*x + y*y)*6371);
}

 vector<Node> Quad::knn(int k, Quad& quad, float longi, float lati, MaxHeap<float, Point>& heap){

 	for(int i = 0; i < k; i++){
 		// heap.insert(quad.search(Point(longi, lati)));	
 	}
 	//Node node = quad.search(Point(longi, lati));
 	//if NW, check ne, sw, se
 	//if NE check nw, se, sw
 	//if SW, check se, nw, ne
 	//if SE, check sw, ne, nw
 	//now, check all quadrants
	return {};
}

QuadTreePointFinder::QuadTreePointFinder(
		const std::vector<CountyRecord>& countyRecords)
	: m_quad(new Quad()), m_nodes()
{
	m_nodes.reserve(countyRecords.size());
	for (const auto& record : countyRecords)
	{
		// TODO: insert nodes in the tree for each record.
		m_nodes.emplace_back(Point(record.m_longitude, record.m_latitude), record.m_state, record.m_county);
		m_quad->insert(&m_nodes.back());
	}


}

QuadTreePointFinder::~QuadTreePointFinder()
{
}

std::vector<CountyRecord> QuadTreePointFinder::FindNearest(
		decltype(CountyRecord::m_latitude) latitude,
		decltype(CountyRecord::m_latitude) longitude,
		unsigned int nearestCount)
{
	MaxHeap<float, Point> heap(nearestCount);
	m_quad->knn(nearestCount, *m_quad, longitude, latitude, heap);

	//PRINT HEAP

	/*cout << "Node a: " << 
		center.search(Point(1, 1))->data << "\n"; 
	cout << "Node b: " << 
		center.search(Point(2, 5))->data << "\n"; 
	cout << "Node c: " << 
		center.search(Point(7, 6))->data << "\n"; 
	cout << "Non-existing node: "
		<< center.search(Point(5, 5)); */

	// TODO: Return the actual nearest points instead of an empty vector.
	return {};
}
