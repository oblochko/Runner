#include "..\include\scene.h"

Scene::Scene()
{
	
}

void Scene::main(GLFWwindow* window)
{
}

void Scene::init()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;	
	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);

	BufferVertex::bufferVertex.generate();
	pathway.init();
}

void Scene::event()
{
	GLfloat currentFrame = glfwGetTime();
	Camera::camera.deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glfwPollEvents();
	do_movement();
}

void Scene::render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pathway.draw();
}


void Scene::onKey(GLFWwindow* _window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			if (key == GLFW_KEY_D)
			{
				pathway.player.currentColumn++;
				if (pathway.player.currentColumn > 1)
					pathway.player.currentColumn = 1;
			}
			if (key == GLFW_KEY_A)
			{
				pathway.player.currentColumn--;
				if (pathway.player.currentColumn < -1)
					pathway.player.currentColumn = -1;
			}
			if (key == GLFW_KEY_SPACE)
				pathway.player.life = true;
			if (key == GLFW_KEY_V)
			{
				//Camera::camera.flag = !Camera::camera.flag;
				if (Camera::camera.flag)
				{
					Camera::camera.setPosition(pathway.player.position);
					Camera::camera.flag = false;
				} else
					Camera::camera.flag = true;
			}

			keys[key] = true;
			if (keys[GLFW_KEY_D])
				pathway.player.right = true;
			if (keys[GLFW_KEY_A])
				pathway.player.left = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
			if (!keys[GLFW_KEY_D])
				pathway.player.right = false;
			if (!keys[GLFW_KEY_A])
				pathway.player.left = false;
		}
	}
	/*if (keys[GLFW_KEY_W])
		cout << "true" << endl;*/
}

bool firstMouse = true;
void Scene::onMouse(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	Camera::camera.ProcessMouseMovement(xoffset, yoffset);
}

void Scene::onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::camera.ProcessMouseScroll(yoffset);
}

void Scene::do_movement()
{
	if (Camera::camera.flag)
	{
		if (keys[GLFW_KEY_W])
			Camera::camera.ProcessKeyboard(FORWARD, Camera::camera.deltaTime);
		if (keys[GLFW_KEY_S])
			Camera::camera.ProcessKeyboard(BACKWARD, Camera::camera.deltaTime);
		if (keys[GLFW_KEY_A])
			Camera::camera.ProcessKeyboard(LEFT, Camera::camera.deltaTime);
		if (keys[GLFW_KEY_D])
			Camera::camera.ProcessKeyboard(RIGHT, Camera::camera.deltaTime);
	}
}

void Scene::key_callback(GLFWwindow* _window, int key, int scancode, int action, int mode)
{
	//cout << "calbackk" << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, GL_TRUE);
	((Scene*)glfwGetWindowUserPointer(_window))->onKey(_window, key, scancode, action, mode);
}

void Scene::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	((Scene*)glfwGetWindowUserPointer(window))->onMouse(window, xpos, ypos);
}

void Scene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	((Scene*)glfwGetWindowUserPointer(window))->onScroll(window, xoffset, yoffset);
}
