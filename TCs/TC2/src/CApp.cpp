#include "CApp.hpp"

// Default constructor
CApp::CApp() {
}

CApp::CApp(int width, int height, int bitDepth, int numParticles, double gravity) {
	this->width = width;
	this->height = height;
	this->bitDepth = bitDepth;
	this->firework = Firework(numParticles, gravity);
	isRunning = true;
	window = 0;
}

void CApp::ResizeCallback(int width, int height) {
    cAppInstance->OnResize(width, height);
}

void CApp::NormalKeyCallback(unsigned char key, int x, int y) {
    cAppInstance->OnNormalKeyPressed(key, x, y);
}

void CApp::SpecialKeyCallback(int key, int x, int y) {
    cAppInstance->OnSpecialKeyPressed(key, x, y);
}

void CApp::getOpenGLInfo() {
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

bool CApp::OnInit() {
	int screenCenterX = (glutGet(GLUT_SCREEN_WIDTH) - this->width) / 2;
	int screenCenterY = (glutGet(GLUT_SCREEN_HEIGHT) - this->height) / 2;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(this->width, this->height);
	glutInitWindowPosition(screenCenterX, screenCenterY);
	window = glutCreateWindow("Firework");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		// This Will Clear The Background Color To Black
	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	gluPerspective(45.0f,(GLfloat) this->width / (GLfloat) this->height, 0.1f, 100.0f);	// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);

	return true;
}

void CApp::Setup() {
	// Light values and coordinates
	GLfloat whiteLight[] = { 0.4, 0.4, 0.4, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);  // Hidden surface removal
	glFrontFace(GL_CCW);      // Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);// Do not calculate inside

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(1.0, 1.0, 1.0, 1.0);
}

int CApp::OnExecute() {
	OnInit();
	glutDisplayFunc(Firework::DisplayCallback);
	glutIdleFunc(Firework::DisplayCallback);
	glutReshapeFunc(CApp::ResizeCallback);
	glutKeyboardFunc(CApp::NormalKeyCallback);
	glutSpecialFunc(CApp::SpecialKeyCallback);
	glutMainLoop();
	Setup();

	OnExit();
	return 0;
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
}

void CApp::OnResize(int width, int height) {
	GLfloat fAspect;

	// Prevent a divide by zero
	if (height == 0) {
		height = 1;
	}
	// Set Viewport to window dimensions
	glViewport(0, 0, width, height);

	fAspect = (GLfloat)width / (GLfloat)height;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Produce the perspective projection
	gluPerspective(35.0f, fAspect, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CApp::OnNormalKeyPressed(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			OnExit();
			break;

  	}
}

void CApp::OnSpecialKeyPressed(int key, int x, int y) {
}

void CApp::OnExit() {
	glutDestroyWindow(window);
	exit(0);
}
