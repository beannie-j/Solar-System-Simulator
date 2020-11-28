#if 0
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Application.h"
#include "Planet.h"

/*
    * All images are from http://planetpixelemporium.com
*/

int main()
{
    int width = 1900;
    int height = 1200;

    int div = 2.8;

    sf::RenderWindow window(sf::VideoMode(width, height), "Solar System");

    Planet Sun(width / div, height / div, 0, 0, 0, 50);
    Sun.SetTexture("Simulator/res/assets/img/sunmap.jpg");

    float relativeToSunX = (width / div) + Sun.GetRadius();
    float relativeToSunY = (height / div) + Sun.GetRadius();

    Planet Mercury(relativeToSunX - 30.0f, relativeToSunY - 30.0f, 110, 0, 0.35, 30.0f);
    Mercury.SetTexture("Simulator/res/assets/img/mercurymap.jpg");

    Planet Venus(relativeToSunX - 30.0f, relativeToSunY - 30.0f, 160, 0, 0.19, 30.0f);
    Venus.SetTexture("Simulator/res/assets/img/venusmap.jpg");

    Planet Earth(relativeToSunX - 30.0f, relativeToSunY - 30.0f, 210, 0, 0.11, 30.0f);
    Earth.SetTexture("Simulator/res/assets/img/earthmap1k.jpg");

    Planet Mars(relativeToSunX - 15.0f, relativeToSunY - 15.0f, 250, 0, 0.12, 15.0f);
    Mars.SetTexture("Simulator/res/assets/img/mars_1k_color.jpg");

    Planet Jupiter(relativeToSunX - 15.0f, relativeToSunY - 15.0f, 300, 10.f, 0.13, 45.0f);
    Jupiter.SetTexture("Simulator/res/assets/img/jupitermap.jpg");

    Planet Saturn(relativeToSunX - 15.0f, relativeToSunY - 15.0f, 350, 0, 0.14, 45.0f);
    Saturn.SetTexture("Simulator/res/assets/img/saturnmap.jpg");

    Planet Uranus(relativeToSunX - 15.0f, relativeToSunY - 15.0f, 400, 0, 0.12234, 35.0f);
    Uranus.SetTexture("Simulator/res/assets/img/uranusmap.jpg");

    Planet Neptune(relativeToSunX - 15.0f, relativeToSunY - 15.0f, 450, 0, 0.093, 30.0f);
    Neptune.SetTexture("Simulator/res/assets/img/neptunemap.jpg");

    Planet Pluto(relativeToSunX - 15.0f, relativeToSunY - 15.0f, 500, 0, 0.1973, 30.0f);
    Pluto.SetTexture("Simulator/res/assets/img/plutomap1k.jpg");

    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("Simulator/res/assets/img/milkyway.jpg"))
        std::cout << "[Error] : Could not load background texture" << std::endl;

    sf::Sprite backgroundSprite = sf::Sprite(backgroundTexture);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite);

        Jupiter.Orbit();
        Saturn.Orbit();
        Uranus.Orbit();
        Neptune.Orbit();
        Pluto.Orbit();
        Mars.Orbit();
        Mercury.Orbit();
        Venus.Orbit();
        Earth.Orbit();

        Sun.Draw(window);
        Mercury.Draw(window);
        Venus.Draw(window);
        Earth.Draw(window);
        Mars.Draw(window);
        Jupiter.Draw(window);
        Saturn.Draw(window);
        Uranus.Draw(window);
        Neptune.Draw(window);
        Pluto.Draw(window);

        window.display();
    }

    return 0;
}
#if 0
int main(void)
{
    GLFWwindow* window;

    //Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a windowed mode window and its OpenGL context
    int width = 1280;
    int height = 1024;
    window = glfwCreateWindow(width, height, "Solar System Simulator", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;


    float positions[] = {
            // Front
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
             0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
             0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            // Back
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

            // Left
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

            // Right
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

			 // Top
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

			// Bottom
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
    };


    int offset = 0;
    uint32_t indices[36];
    for (int i = 0; i < 36; i += 6)
    {
        indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

        offset += 4;
    }

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));
    
    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push<float>(3);
	layout.Push<float>(3);

    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 36);

    Shader shader("Simulator/res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    //Texture texture("Simulator/res/textures/planet-earth.png");
    //texture.Bind();
    //shader.SetUniform1i("u_Texture", 0);
  
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3{ 0.0f, 1.0f, 3.0f })
        * glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    view = glm::inverse(view);

    float rotation = 0.0f;

    glm::mat4 viewProj = projection * view;

    float r = 0.0f;
    float increment = 0.05f;
    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        float ts = 0.01667f;
        rotation += 180.0f * ts;
        glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3{ 0.0f, 1.0f, 0.0f });

        //Render here
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4("u_ViewProjection", viewProj);
        shader.SetUniformMat4("u_Transform", transform);

        renderer.Draw(va, ib, shader);

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
    
}
#endif