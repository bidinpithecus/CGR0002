#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "Coordinate3D.hpp"
#include "Coordinate2D.hpp"
#include "Color.hpp"

// OBJ
const std::string v = "v";
const std::string vt = "vt";
const std::string vn = "vn";
const std::string f = "f";
const std::string mtllib = "mtllib";
const std::string usemtl = "usemtl";
// MTL
const std::string newmtl = "newmtl";
const std::string Ks = "Ks";

struct Vertex {
	Color color;
	Coordinate2D texture;
	Coordinate3D position;
	Coordinate3D normal;

	Vertex();
	Vertex(Color color, Coordinate3D position, Coordinate2D texture, Coordinate3D normal) : color(color), position(position), texture(texture), normal(normal) {}
};

class Object {
	public:
		Object();
		~Object();
		bool loadOBJ(const std::string path);
		bool loadMTL();
		void addVertex(Coordinate3D index, std::string mtlName, std::vector<Coordinate3D> positions, std::vector<Coordinate2D> textures, std::vector<Coordinate3D> normals);

	private:
		std::string objPath;
		std::string mtlPath;
		std::vector<Vertex> vertices;
		std::map<std::string, Color> materialMap;
};

#endif
