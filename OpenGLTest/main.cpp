#include <iostream>
#include <string>

#include <GL/glew.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

int main()
{
	const std::string title = "OpenGL Test";
	Display display(800, 800, title);

	const std::string shaderPath = "./resources/BasicShader";
	Shader shader(shaderPath);

	const std::string texturePath = "./resources/DefaultShader.jpg";
	Texture texture(texturePath);

	Transform transform;

	Camera camera(
		glm::vec3(0, 0, -10),
		70,
		static_cast<float>(display.GetWidth()) / static_cast<float>(display.GetHeight()),
		0.01f,
		1000);
	
	Vertex a;
	Vertex b;
	Vertex c;

	// OpenGL coordinates goes from -1 to 1
	a.position = glm::vec3(-0.5, -0.5, 0);
	b.position = glm::vec3(0, 0.5, 0);
	c.position = glm::vec3(0.5, -0.5, 0);

	a.texCoord = glm::vec2(0.0, 0.0);
	b.texCoord = glm::vec2(0.5, 1.0);
	c.texCoord = glm::vec2(1.0, 0.0);
	
	Vertex vertices[] { a, b, c };
	unsigned int indices[] = { 0, 1, 2 };
	
	Mesh mesh{vertices, static_cast<int>(std::size(vertices)), indices, static_cast<int>(std::size(indices))};

	std::string objFilePath = "./resources/monkey3.obj";
	Mesh meshObj{ objFilePath };

	float baseSpeed = 1.f;
	float rotationSpeed = .005f;
	float movementSpeed = 1;
	float movementDistance = 8;
	float scaleSpeed = 1;
	
	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		// transform.GetPosition().x = cosf(baseSpeed * movementSpeed) * 1;
		// transform.GetPosition().z = sinf(baseSpeed * movementSpeed) * movementDistance;
		
		transform.GetRotation().x += rotationSpeed;
		transform.GetRotation().y += rotationSpeed * 2;
		// transform.GetRotation().z += rotationSpeed;

		// transform.SetScale(glm::vec3(.2, .2, .2));
		
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		meshObj.Draw();
		
		display.Update();

		baseSpeed += 0.01f;
	}
	
	return 0;
}
