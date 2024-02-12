#pragma once

/**
 * @brief Represents a point in 3D space.
 */
struct Point
{
	int id; /**< The ID of the point. */
	double x, y, z; /**< The coordinates of the point in 3D space. */
};

/**
 * @brief Represents a node in an octree data structure.
 */
struct OctreeNode
{
	Point* point; /**< A pointer to the point stored in this node. */
	OctreeNode* children[8]; /**< An array of pointers to the children nodes of this node. */
};

/**
 * @brief Represents an octree data structure.
 */
class Octree
{
public:
	/**
	 * @brief Constructs an octree with the specified bounds.
	 * @param xmin The minimum x-coordinate of the bounding box.
	 * @param xmax The maximum x-coordinate of the bounding box.
	 * @param ymin The minimum y-coordinate of the bounding box.
	 * @param ymax The maximum y-coordinate of the bounding box.
	 * @param zmin The minimum z-coordinate of the bounding box.
	 * @param zmax The maximum z-coordinate of the bounding box.
	 */
	Octree(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);

	/**
	 * @brief Destroys the octree.
	 */
	~Octree();

private:
	OctreeNode* root; /**< Pointer to the root node of the octree. */
	double bounds[6]; /**< Array representing the bounds of the octree. */
};
