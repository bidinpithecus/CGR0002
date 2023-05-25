#include "App.hpp"
#include "Object.hpp"
#include "Shapes.hpp"
#include "Coordinate3D.hpp"
#include "Coordinate2D.hpp"
#include "Helpers.hpp"
#include <GL/gl.h>
#include <ctime>
#include <vector>
#include <FreeImage.h>

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
float fps = 0.0;
Object object;

GLuint textureID;

GLUquadricObj *pObj;

void loadTexture(const char* fileName, GLuint textureID) {
    // Carregando a imagem usando FreeImage
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName, 0);
    FIBITMAP* image = FreeImage_Load(format, fileName);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
    int width = FreeImage_GetWidth(image32bits);
    int height = FreeImage_GetHeight(image32bits);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurando os parâmetros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carregando os dados da imagem na textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

    // Liberando a memória utilizada pelas imagens
    FreeImage_Unload(image);
    FreeImage_Unload(image32bits);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void idle(void) {
	getFps();
	glutPostRedisplay();
}

void drawScene() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
    for (const auto& face : object.getFaces()) {
		long unsigned int materialIndex = face.materialIndex;

        if (materialIndex < object.getMaterials().size()) {
            const Material material = object.getMaterials()[materialIndex];
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);

        }

        glBegin(GL_POLYGON);
        for (size_t i = 0; i < face.vertexIndices.size(); ++i) {
            int vertexIndex = face.vertexIndices[i];
            int texCoordIndex = face.textureIndices[i];
            int normalIndex = face.normalIndices[i];
            const Vertex vertex = object.getVertices()[vertexIndex];
            const Texture texCoord = object.getTextures()[texCoordIndex];
            const Normal normal = object.getNormals()[normalIndex];
            glTexCoord2f(texCoord.x, texCoord.y);
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        glEnd();
    }
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


int main(int argc, char **argv) {
	glGenTextures(1, &textureID);
	if (!object.loadOBJ("data/cube.obj")) return 0;
	if (!object.loadMTL("data/cube.mtl")) return 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OBJ viewer");
	loadTexture("data/cube.png", textureID);
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	setupRC();
	glutMainLoop();

	return 0;
}
