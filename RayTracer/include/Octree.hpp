#pragma once


struct Point
{
	int id;
	double x, y, z;

};

struct OctreeNode
{
	Point* point;
	OctreeNode* children[8]; //array that stores 8 pointers for children
};


class Octree
{
public:

	Octree(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
	~Octree();


private:
	OctreeNode* root;
	double bounds[6];



};