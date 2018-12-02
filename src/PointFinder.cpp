#include <PointFinder.h>

PointFinder::PointFinder()
{
}

PointFinder::~PointFinder()
{
}

std::unique_ptr<PointFinder>
PointFinder::Make(Method method)
{
	switch (method)
	{
		case Method::KDTree:
			throw std::runtime_error("K-D Tree method not yet implemented");
		case Method::QuadTree:
			throw std::runtime_error("Quadtree method not yet implemented");
		case Method::Linear:
			throw std::runtime_error("Linear method not yet implemented");
	}
	return nullptr;
}
