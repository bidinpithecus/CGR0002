#include "Object.hpp"
#include "Coordinate3D.hpp"

using namespace std;

Object::Object() {}
Object::~Object() {}

bool Object::loadOBJ(const string path) {
	vector<Coordinate3D> positions;
	vector<Coordinate3D> normals;
	vector<Coordinate2D> textures;
	string curUseMtl;
	ifstream file(path);
	if (!file) { cout << "Error opening file" << endl; return false; }
	float x, y, z;

	string line;
	while (getline(file, line)) {
		if (!line.compare(0, v.length(), v)) {
			sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
			positions.push_back(Coordinate3D(x, y, z));
		} else if (!line.compare(0, vt.length(), vt)) {
			sscanf(line.c_str(), "vt %f %f", &x, &y);
			textures.push_back(Coordinate2D(x, y));
		} else if (!line.compare(0, vn.length(), vn)) {
			sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
			normals.push_back(Coordinate3D(x, y, z));
		} else if (!line.compare(0, mtllib.length(), mtllib)) {
			this->mtlPath = line.substr(mtllib.length() + 1);
			loadMTL();
		} else if (!line.compare(0, usemtl.length(), usemtl)) {
			curUseMtl = line.substr(usemtl.length() + 1);
		} else if (!line.compare(0, f.length(), f)) {
			int v1, vt1, vn1;
			int v2, vt2, vn2;
			int v3, vt3, vn3;
			sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);

			addVertex(Coordinate3D(v1, vt1, vn1), curUseMtl, positions, textures, normals);
			addVertex(Coordinate3D(v2, vt2, vn2), curUseMtl, positions, textures, normals);
			addVertex(Coordinate3D(v3, vt3, vn3), curUseMtl, positions, textures, normals);
		}
	}
	return true;
}

bool Object::loadMTL() {
	ifstream file(mtlPath);
	if (!file) { cout << "Error opening file" << endl; return false; }
	string curNewMtl;

	string line;
	while (getline(file, line)) {
		if (!line.compare(0, newmtl.length(), newmtl)) {
			curNewMtl = line.substr(newmtl.length() + 1);
			materialMap[curNewMtl] = Color();
		} else if (!line.compare(0, Ks.length(), Ks)) {
			float r, g, b;
			sscanf(line.c_str(), "Ks %f %f %f", &r, &g, &b);
			Color& color = materialMap[curNewMtl];
			color.setRed(r);
			color.setGreen(g);
			color.setBlue(b);
		}
	}
	return true;
}

void Object::addVertex(Coordinate3D index, std::string mtlName, std::vector<Coordinate3D> positions, std::vector<Coordinate2D> textures, std::vector<Coordinate3D> normals) {
	Color color;
	Coordinate3D newPos = positions.at(index.getX() - 1);
	Coordinate2D newTex = textures.at(index.getY() - 1);
	Coordinate3D newNor = normals.at(index.getZ() - 1);

	this->vertices.push_back(Vertex(color, newPos, newTex, newNor));
}
