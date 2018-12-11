#ifndef QUADTREEPOINTFINDER_H
#define QUADTREEPOINTFINDER_H
#include <CountyRecord.h>
#include <PointFinder.h>
#include <vector>
#include <string>

class Quad;
class QuadTreePointFinder final : public PointFinder
{
public:
	// Point dat struct
	struct Point 
	{ 
		float x; 
		float y; 
		//constructors
		Point(float _x, float _y) 
		{ 
			x = _x; //longitude
			y = _y;  // latitude
		} 
		Point() 
		{ 
			x = 0; 
			y = 0; 
		} 
	}; 

	// The objects that we want stored in the quadtree 
	struct Node 
	{ 
		Point pos; 
		std::string state;
		std::string county;
		bool visited;
		int quadrant;
		Node(Point _pos, std::string _state, std::string _county) 
		{ 
			pos = _pos; 
			state = _state;
			county = _county;
			visited = false;
			quadrant = 0;
			visited = false;
		} 
	}; 

	QuadTreePointFinder(const std::vector<CountyRecord>& countyRecords);
	virtual ~QuadTreePointFinder();
	virtual std::vector<CountyRecord> FindNearest(
			decltype(CountyRecord::m_latitude) latitude,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) override;
private:
	std::unique_ptr<Quad> m_quad;
	std::vector<Node> m_nodes;
};

#endif //QUADTREEPOINTFINDER_H
