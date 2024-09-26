#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

// 0x109 --> 0001001001 -> edges 0,3 and 8

int edgeTable[256] = {
	0x0,   0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c, 0x80c, 0x905, 0xa0f, 0xb06, 0xc0a,
	0xd03, 0xe09, 0xf00, 0x190, 0x99,  0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c, 0x99c, 0x895,
	0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90, 0x230, 0x339, 0x33,  0x13a, 0x636, 0x73f, 0x435,
	0x53c, 0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30, 0x3a0, 0x2a9, 0x1a3, 0xaa,
	0x7a6, 0x6af, 0x5a5, 0x4ac, 0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0, 0x460,
	0x569, 0x663, 0x76a, 0x66,  0x16f, 0x265, 0x36c, 0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963,
	0xa69, 0xb60, 0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff,  0x3f5, 0x2fc, 0xdfc, 0xcf5, 0xfff,
	0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0, 0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55,  0x15c,
	0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950, 0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6,
	0x2cf, 0x1c5, 0xcc,  0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0, 0x8c0, 0x9c9,
	0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc, 0xcc,  0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9,
	0x7c0, 0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c, 0x15c, 0x55,  0x35f, 0x256,
	0x55a, 0x453, 0x759, 0x650, 0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc, 0x2fc,
	0x3f5, 0xff,  0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0, 0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f,
	0xd65, 0xc6c, 0x36c, 0x265, 0x16f, 0x66,  0x76a, 0x663, 0x569, 0x460, 0xca0, 0xda9, 0xea3,
	0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac, 0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa,  0x1a3, 0x2a9, 0x3a0,
	0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c, 0x53c, 0x435, 0x73f, 0x636, 0x13a,
	0x33,  0x339, 0x230, 0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c, 0x69c, 0x795,
	0x49f, 0x596, 0x29a, 0x393, 0x99,  0x190, 0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905,
	0x80c, 0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0};

int tetraTable[16][7] = {
	{-1, -1, -1, -1, -1, -1, -1}, // 0  (0000, no vertices inside)
	{0, 3, 2, -1, -1, -1, -1}, // 1  (0001, 1 vertex inside)
	{0, 1, 4, -1, -1, -1, -1}, // 2  (0010, 1 vertex inside)
	{1, 2, 4, 4, 2, 3, -1}, // 3  (0011, 2 vertices inside)
	{1, 5, 2, -1, -1, -1, -1}, // 4  (0100, 1 vertex inside)
	{0, 3, 5, 5, 3, 2, -1}, // 5  (0101, 2 vertices inside)
	{0, 1, 4, 2, 1, 5, -1}, // 6  (0110, 2 vertices inside)
	{5, 4, 3, 5, 3, 2, -1}, // 7  (0111, 3 vertices inside)
	{3, 4, 5, -1, -1, -1, -1}, // 8  (1000, 1 vertex inside)
	{0, 4, 3, 3, 4, 5, -1}, // 9  (1001, 2 vertices inside)
	{1, 2, 5, 1, 5, 4, -1}, // 10 (1010, 2 vertices inside)
	{1, 5, 3, 1, 3, 4, -1}, // 11 (1011, 3 vertices inside)
	{2, 3, 5, -1, -1, -1, -1}, // 12 (1100, 2 vertices inside)
	{0, 5, 2, 2, 5, 4, -1}, // 13 (1101, 3 vertices inside)
	{0, 1, 5, 5, 4, 3, -1}, // 14 (1110, 3 vertices inside)
	{5, 4, 3, 5, 3, 2, -1} // 15 (1111, all vertices inside)
};

int triTable[256][16] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
						 {3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
						 {3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
						 {3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
						 {9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
						 {9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
						 {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
						 {8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
						 {9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
						 {4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
						 {3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
						 {1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
						 {4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
						 {4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
						 {9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
						 {5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
						 {2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
						 {9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
						 {0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
						 {2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
						 {10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
						 {4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
						 {5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
						 {5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
						 {9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
						 {0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
						 {1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
						 {10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
						 {8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
						 {2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
						 {7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
						 {9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
						 {2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
						 {11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
						 {9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
						 {5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
						 {11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
						 {11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
						 {1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
						 {9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
						 {5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
						 {2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
						 {0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
						 {5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
						 {6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
						 {3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
						 {6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
						 {5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
						 {1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
						 {10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
						 {6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
						 {8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
						 {7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
						 {3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
						 {5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
						 {0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
						 {9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
						 {8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
						 {5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
						 {0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
						 {6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
						 {10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
						 {10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
						 {8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
						 {1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
						 {3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
						 {0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
						 {10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
						 {3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
						 {6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
						 {9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
						 {8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
						 {3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
						 {6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
						 {0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
						 {10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
						 {10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
						 {2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
						 {7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
						 {7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
						 {2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
						 {1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
						 {11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
						 {8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
						 {0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
						 {7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
						 {10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
						 {2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
						 {6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
						 {7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
						 {2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
						 {1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
						 {10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
						 {10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
						 {0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
						 {7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
						 {6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
						 {8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
						 {6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
						 {4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
						 {10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
						 {8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
						 {0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
						 {1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
						 {8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
						 {10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
						 {4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
						 {10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
						 {5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
						 {11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
						 {9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
						 {6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
						 {7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
						 {3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
						 {7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
						 {9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
						 {3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
						 {6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
						 {9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
						 {1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
						 {4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
						 {7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
						 {6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
						 {3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
						 {0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
						 {6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
						 {0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
						 {11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
						 {6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
						 {5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
						 {9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
						 {1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
						 {1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
						 {10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
						 {0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
						 {5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
						 {10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
						 {11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
						 {9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
						 {7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
						 {2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
						 {8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
						 {9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
						 {9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
						 {1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
						 {9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
						 {9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
						 {5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
						 {0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
						 {10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
						 {2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
						 {0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
						 {0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
						 {9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
						 {5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
						 {3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
						 {5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
						 {8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
						 {9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
						 {0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
						 {1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
						 {3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
						 {4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
						 {9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
						 {11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
						 {11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
						 {2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
						 {9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
						 {3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
						 {1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
						 {4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
						 {4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
						 {0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
						 {3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
						 {3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
						 {0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
						 {9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
						 {1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

struct Vec3
{
	float x, y, z;
	Vec3(float _x = 0, float _y = 0, float _z = 0)
		: x(_x)
		, y(_y)
		, z(_z)
	{}
};

struct Triangle
{
	Vec3 v0, v1, v2;
	Triangle(const Vec3& _v0, const Vec3& _v1, const Vec3& _v2)
		: v0(_v0)
		, v1(_v1)
		, v2(_v2)
	{}
};

// Utility to interpolate between two points based on the isolevel
Vec3 interpolate(const Vec3& p1, const Vec3& p2, float valp1, float valp2, float isolevel)
{
	if(fabs(isolevel - valp1) < 1e-5)
		return p1;
	if(fabs(isolevel - valp2) < 1e-5)
		return p2;
	if(fabs(valp1 - valp2) < 1e-5)
		return p1;

	float t = (isolevel - valp1) / (valp2 - valp1);
	return Vec3(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y), p1.z + t * (p2.z - p1.z));
}

std::vector<Triangle>
marchingTetrahedrons(float* volume, int width, int height, int depth, float isolevel)
{
	std::vector<Triangle> triangles;

	// Define the 6 tetrahedrons within each cube
	int tetrahedronTable[6][4] = {
		{0, 5, 1, 6}, // Tetrahedron 1
		{0, 5, 6, 4}, // Tetrahedron 2
		{0, 1, 6, 2}, // Tetrahedron 3
		{0, 6, 2, 3}, // Tetrahedron 4
		{0, 6, 3, 7}, // Tetrahedron 5
		{0, 6, 7, 4} // Tetrahedron 6
	};

	for(int z = 0; z < depth - 1; ++z)
	{
		for(int y = 0; y < height - 1; ++y)
		{
			for(int x = 0; x < width - 1; ++x)
			{

				// Get cube corners and their scalar values
				Vec3 cubeCorners[8] = {Vec3(x, y, z),
									   Vec3(x + 1, y, z),
									   Vec3(x + 1, y + 1, z),
									   Vec3(x, y + 1, z),
									   Vec3(x, y, z + 1),
									   Vec3(x + 1, y, z + 1),
									   Vec3(x + 1, y + 1, z + 1),
									   Vec3(x, y + 1, z + 1)};

				float cubeValues[8];
				for(int i = 0; i < 8; ++i)
				{
					int xi = cubeCorners[i].x;
					int yi = cubeCorners[i].y;
					int zi = cubeCorners[i].z;
					cubeValues[i] = volume[xi + width * (yi + height * zi)];
				}

				// Process each of the 6 tetrahedrons within the cube
				for(int t = 0; t < 6; ++t)
				{
					Vec3 tetCorners[4];
					float tetValues[4];

					// Get the tetrahedron's corner vertices and values
					for(int i = 0; i < 4; ++i)
					{
						tetCorners[i] = cubeCorners[tetrahedronTable[t][i]];
						tetValues[i] = cubeValues[tetrahedronTable[t][i]];
					}

					// Calculate tetrahedron index based on which vertices are inside/outside the isosurface
					int tetraIndex = 0;
					for(int i = 0; i < 4; ++i)
					{
						if(tetValues[i] < isolevel)
							tetraIndex |= (1 << i);
					}

					// Find the vertices where the surface intersects the tetrahedron
					Vec3 vertList[6];
					if(tetraIndex == 0 || tetraIndex == 15)
					{
						// No intersection or fully inside, skip
						continue;
					}

					// Edge interpolation for tetrahedron edges
					if(tetraIndex & 1)
						vertList[0] = interpolate(
							tetCorners[0], tetCorners[1], tetValues[0], tetValues[1], isolevel);
					if(tetraIndex & 2)
						vertList[1] = interpolate(
							tetCorners[1], tetCorners[2], tetValues[1], tetValues[2], isolevel);
					if(tetraIndex & 4)
						vertList[2] = interpolate(
							tetCorners[2], tetCorners[3], tetValues[2], tetValues[3], isolevel);
					if(tetraIndex & 8)
						vertList[3] = interpolate(
							tetCorners[3], tetCorners[0], tetValues[3], tetValues[0], isolevel);
					if(tetraIndex & 5)
						vertList[4] = interpolate(
							tetCorners[0], tetCorners[2], tetValues[0], tetValues[2], isolevel);
					if(tetraIndex & 10)
						vertList[5] = interpolate(
							tetCorners[1], tetCorners[3], tetValues[1], tetValues[3], isolevel);

					// Triangulate the tetrahedron based on the intersection
					for(int i = 0; tetraTable[tetraIndex][i] != -1; i += 3)
					{
						Vec3 v0 = vertList[tetraTable[tetraIndex][i]];
						Vec3 v1 = vertList[tetraTable[tetraIndex][i + 1]];
						Vec3 v2 = vertList[tetraTable[tetraIndex][i + 2]];
						triangles.push_back(Triangle(v0, v1, v2));
					}
				}
			}
		}
	}

	return triangles;
}

// Core Marching Cubes function for generating isosurface
std::vector<Triangle> marchingCubes(float* volume, int width, int height, int depth, float isolevel)
{
	std::vector<Triangle> triangles;

	for(int z = 0; z < depth - 1; ++z)
	{
		for(int y = 0; y < height - 1; ++y)
		{
			for(int x = 0; x < width - 1; ++x)
			{
				int cubeIndex = 0;
				float cubeValues[8];
				Vec3 cubeCorners[8] = {Vec3(x, y, z),
									   Vec3(x + 1, y, z),
									   Vec3(x + 1, y + 1, z),
									   Vec3(x, y + 1, z),
									   Vec3(x, y, z + 1),
									   Vec3(x + 1, y, z + 1),
									   Vec3(x + 1, y + 1, z + 1),
									   Vec3(x, y + 1, z + 1)};

				// Assign scalar values from volume data to cube vertices
				for(int i = 0; i < 8; ++i)
				{
					int xi = cubeCorners[i].x;
					int yi = cubeCorners[i].y;
					int zi = cubeCorners[i].z;
					cubeValues[i] = volume[xi + width * (yi + height * zi)];
					if(cubeValues[i] < isolevel)
						cubeIndex |= (1 << i);
				}

				// Check if the cube is entirely inside or outside the isosurface
				if(edgeTable[cubeIndex] == 0)
					continue;

				// Find the vertices where the surface intersects the cube
				Vec3 vertList[12];
				if(edgeTable[cubeIndex] & 1)
					vertList[0] = interpolate(
						cubeCorners[0], cubeCorners[1], cubeValues[0], cubeValues[1], isolevel);
				if(edgeTable[cubeIndex] & 2)
					vertList[1] = interpolate(
						cubeCorners[1], cubeCorners[2], cubeValues[1], cubeValues[2], isolevel);
				if(edgeTable[cubeIndex] & 4)
					vertList[2] = interpolate(
						cubeCorners[2], cubeCorners[3], cubeValues[2], cubeValues[3], isolevel);
				if(edgeTable[cubeIndex] & 8)
					vertList[3] = interpolate(
						cubeCorners[3], cubeCorners[0], cubeValues[3], cubeValues[0], isolevel);
				if(edgeTable[cubeIndex] & 16)
					vertList[4] = interpolate(
						cubeCorners[4], cubeCorners[5], cubeValues[4], cubeValues[5], isolevel);
				if(edgeTable[cubeIndex] & 32)
					vertList[5] = interpolate(
						cubeCorners[5], cubeCorners[6], cubeValues[5], cubeValues[6], isolevel);
				if(edgeTable[cubeIndex] & 64)
					vertList[6] = interpolate(
						cubeCorners[6], cubeCorners[7], cubeValues[6], cubeValues[7], isolevel);
				if(edgeTable[cubeIndex] & 128)
					vertList[7] = interpolate(
						cubeCorners[7], cubeCorners[4], cubeValues[7], cubeValues[4], isolevel);
				if(edgeTable[cubeIndex] & 256)
					vertList[8] = interpolate(
						cubeCorners[0], cubeCorners[4], cubeValues[0], cubeValues[4], isolevel);
				if(edgeTable[cubeIndex] & 512)
					vertList[9] = interpolate(
						cubeCorners[1], cubeCorners[5], cubeValues[1], cubeValues[5], isolevel);
				if(edgeTable[cubeIndex] & 1024)
					vertList[10] = interpolate(
						cubeCorners[2], cubeCorners[6], cubeValues[2], cubeValues[6], isolevel);
				if(edgeTable[cubeIndex] & 2048)
					vertList[11] = interpolate(
						cubeCorners[3], cubeCorners[7], cubeValues[3], cubeValues[7], isolevel);

				// Create triangles based on the triangulation table
				for(int i = 0; triTable[cubeIndex][i] != -1; i += 3)
				{
					Vec3 v0 = vertList[triTable[cubeIndex][i]];
					Vec3 v1 = vertList[triTable[cubeIndex][i + 1]];
					Vec3 v2 = vertList[triTable[cubeIndex][i + 2]];
					triangles.push_back(Triangle(v0, v1, v2));
				}
			}
		}
	}

	return triangles;
}

class SurfaceNets
{
public:
	int cube_edges[24];
	int edge_table[256];

	SurfaceNets()
	{
		initSurfaceNet();
	}

	void initSurfaceNet()
	{
		int k = 0;
		for(int i = 0; i < 8; ++i)
		{
			for(int j = 1; j <= 4; j <<= 1)
			{
				int p = i ^ j;
				if(i <= p)
				{
					cube_edges[k++] = i;
					cube_edges[k++] = p;
				}
			}
		}
        
		for(int i = 0; i < 256; ++i)
		{
			int em = 0;
			for(int j = 0; j < 24; j += 2)
			{
				int a = !(i & (1 << cube_edges[j]));
				int b = !(i & (1 << cube_edges[j + 1]));
				em |= a != b ? (1 << (j >> 1)) : 0;
			}
			edge_table[i] = em;
		}
	}

	std::vector<Triangle>
	generateSurfaceNet(float* volume, int width, int height, int depth, float isolevel)
	{
		int n = 0;
		float x[3];
		int R[3];
		float grid[8];
		std::vector<Vec3> vertices;
		std::vector<Triangle> triangles;

		int dims[3];
		dims[0] = width;
		dims[1] = height;
		dims[2] = depth;

		R[0] = 1;
		R[1] = dims[0] + 1;
		R[2] = (dims[0] + 1) * (dims[1] + 1);

		for(x[2] = 0; x[2] < dims[2] - 1; ++x[2])
		{
			int m = 1 + (dims[0] + 1) * (1 + (dims[1] + 1));
			for(x[1] = 0; x[1] < dims[1] - 1; ++x[1], ++n, m += 2)
			{
				for(x[0] = 0; x[0] < dims[0] - 1; ++x[0], ++n, ++m)
				{
					int mask = 0, g = 0, idx = n;
					for(int k = 0; k < 2; ++k, idx += dims[0] * (dims[1] - 2))
					{
						for(int j = 0; j < 2; ++j, idx += dims[0] - 2)
						{
							for(int i = 0; i < 2; ++i, ++g, ++idx)
							{
								float p = volume[idx] - isolevel;
								grid[g] = p;
								mask |= (p < 0) ? (1 << g) : 0;
							}
						}
					}
					if(mask == 0 || mask == 0xff)
						continue;

					int edge_mask = edge_table[mask];
					Vec3 v(0.0, 0.0, 0.0);
					int e_count = 0;

					for(int i = 0; i < 12; ++i)
					{
						if(!(edge_mask & (1 << i)))
							continue;

						++e_count;
						int e0 = cube_edges[i << 1]; // Unpack vertices
						int e1 = cube_edges[(i << 1) + 1];
						float g0 = grid[e0]; // Unpack grid values
						float g1 = grid[e1];
						float t = g0 - g1; // Compute point of intersection
						if(fabs(t) > 1e-6)
							t = g0 / t;
						else
							continue;

						int k = 1;
						for(int j = 0; j < 3; ++j)
						{
							int a = e0 & k;
							int b = e1 & k;
							if(a != b)
								v.x += a ? 1.0 - t : t;
							else
								v.x += a ? 1.0 : 0;
							k <<= 1;
						}
					}

					float s = 1.0 / e_count;
					for(int i = 0; i < 3; ++i)
						((float*)&v)[i] = x[i] + s * ((float*)&v)[i];

					vertices.push_back(v); // Store vertex
					int vertexIndex = vertices.size() - 1;

					for(int i = 0; i < 3; ++i)
					{
						if(!(edge_mask & (1 << i)))
							continue;

						int iu = (i + 1) % 3;
						int iv = (i + 2) % 3;
						if(x[iu] == 0 || x[iv] == 0)
							continue;

						int du = R[iu];
						int dv = R[iv];

						triangles.push_back(Triangle(vertices[vertexIndex],
													 vertices[vertexIndex - du - dv],
													 vertices[vertexIndex - du]));
					}
				}
			}
			n += dims[0];
		}

		return triangles;
	}
};

void writePLY(const std::string& filename, const std::vector<Triangle>& triangles)
{
	std::ofstream plyFile(filename);

	if(!plyFile.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	// PLY header
	plyFile << "ply\n";
	plyFile << "format ascii 1.0\n";
	plyFile << "element vertex " << triangles.size() * 3 << "\n";
	plyFile << "property float x\n";
	plyFile << "property float y\n";
	plyFile << "property float z\n";
	plyFile << "element face " << triangles.size() << "\n";
	plyFile << "property list uchar int vertex_indices\n";
	plyFile << "end_header\n";

	// Write vertices
	for(const Triangle& tri : triangles)
	{
		plyFile << tri.v0.x << " " << tri.v0.y << " " << tri.v0.z << "\n";
		plyFile << tri.v1.x << " " << tri.v1.y << " " << tri.v1.z << "\n";
		plyFile << tri.v2.x << " " << tri.v2.y << " " << tri.v2.z << "\n";
	}

	// Write faces
	int vertexIndex = 0;
	for(size_t i = 0; i < triangles.size(); ++i)
	{
		plyFile << "3 " << vertexIndex << " " << vertexIndex + 1 << " " << vertexIndex + 2 << "\n";
		vertexIndex += 3;
	}

	plyFile.close();
}

int main()
{
	// Example volume data (in reality, this should be 3D scalar field data)
	int width = 100, height = 100, depth = 100;
	float isolevel = 0.5f;
	std::vector<float> volume(width * height * depth);

	float radius = 5.0f; // Define the radius of the sphere

	for(int z = 0; z < depth; ++z)
	{
		for(int y = 0; y < height; ++y)
		{
			for(int x = 0; x < width; ++x)
			{
				// Example: Create a spherical shape
				float distance =
					sqrt(pow(x - width / 2, 2) + pow(y - height / 2, 2) + pow(z - depth / 2, 2));
				volume[z * width * height + y * width + x] =
					distance < radius ? 1.0f : 0.0f; // Adjust threshold
			}
		}
	}
	//// Generate isosurface using Marching Cubes
	//std::vector<Triangle> triangles = marchingCubes(volume.data(), width, height, depth, isolevel);
	//// Write the result to a .ply file
	//writePLY("output.ply", triangles);

	// Generate isosurface using Marching Tets
	// std::vector<Triangle> triangles =
	// 	marchingTetrahedrons(volume.data(), width, height, depth, isolevel);
	// writePLY("output_tet.ply", triangles);

	// Generate isosurface using SurfaceNets
	//SurfaceNets surfaceNets;
	//std::vector<Triangle> triangles =
	//	surfaceNets.generateSurfaceNet(volume.data(), width, height, depth, isolevel);
	//writePLY("output_snet.ply", triangles);

	std::cout << "PLY file generated!" << std::endl;

	return 0;
}