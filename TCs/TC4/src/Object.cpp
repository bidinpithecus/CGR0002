#include "Object.hpp"
#include <sstream>

using namespace std;

Object::Object() { }
Object::~Object() {}
std::string Object::getObjPath() { return objPath; }
std::string Object::getMtlPath() { return mtlPath; }
std::vector<Vertex> Object::getVertices() { return vertices; }
std::vector<Texture> Object::getTextures() { return textureCoords; }
std::vector<Normal> Object::getNormals() { return normals; }
std::vector<Face> Object::getFaces() { return faces; }
std::map<std::string, Material> Object::getMaterialMap() {return materialMap; }
std::vector<Material> Object::getMaterials() { return materials; }

bool Object::loadOBJ(const string path) {
	string curUseMtl;
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Error opening file: " << path << endl;
		return false;
	}

	string line;
	while (getline(file, line)) {
		istringstream iss(line);
        string token;
        iss >> token;

		if (token == vt) {
			Texture texCoords;
			iss >> texCoords.x >> texCoords.y;
			textureCoords.push_back(texCoords);
		} else if (token == vn) {
			Normal normal;
			iss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		} else if (token == v) {
			Vertex vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		} else if (token == mtllib) {
			this->mtlPath = dataPath;
			this->mtlPath = mtlPath.append(line.substr(mtllib.length() + 1));
		} else if (token == f) {
			Face face;
			string vertexIndex;
			while (iss >> vertexIndex) {
				istringstream viss(vertexIndex);
				int vIndex, tIndex, nIndex;
				char slash;
				if (viss >> vIndex >> slash >> tIndex >> slash >> nIndex) {
                    face.vertexIndices.push_back(vIndex - 1);
                    face.textureIndices.push_back(tIndex - 1);
                    face.normalIndices.push_back(nIndex - 1);
                } else {
                    std::cerr << "Failed to parse face vertex index: " << vertexIndex << std::endl;
                    return false;
                }
			}
			faces.push_back(face);
		} else if (token == usemtl) {
            std::string materialName;
            iss >> materialName;
            for (size_t i = 0; i < materials.size(); ++i) {
                if (materials[i].name == materialName) {
                    faces.back().materialIndex = static_cast<int>(i);
                    break;
                }
            }
        }
	}
	file.close();
	return true;
}

bool Object::loadMTL(const string path) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Error opening file: " << path << endl;
		return false;
	}

	string line;
    std::vector<Material> materials;
    Material currentMaterial;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == newmtl) {
            if (!currentMaterial.name.empty()) {
                materials.push_back(currentMaterial);
            }
            currentMaterial = Material();
            iss >> currentMaterial.name;
        } else if (token == Ka) {
            iss >> currentMaterial.ambient[0] >> currentMaterial.ambient[1] >> currentMaterial.ambient[2];
        } else if (token == Ks) {
            iss >> currentMaterial.specular[0] >> currentMaterial.specular[1] >> currentMaterial.specular[2];
        } else if (token == Ke) {
            iss >> currentMaterial.emission[0] >> currentMaterial.emission[1] >> currentMaterial.emission[2];
        } else if (token == Ns) {
            iss >> currentMaterial.shininess;
        } else if (token == Ni) {
            iss >> currentMaterial.opticalDensity;
        } else if (token == d || token == Tr) {
            iss >> currentMaterial.dissolve;
        } else if (token == illum) {
            iss >> currentMaterial.illuminationModel;
        } else if (token == map_Kd) {
            iss >> currentMaterial.diffuseMap;
        }
    }

    if (!currentMaterial.name.empty()) {
        materials.push_back(currentMaterial);
    }

	file.close();
	return true;
}
