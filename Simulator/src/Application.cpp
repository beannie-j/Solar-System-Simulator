/*
* SFML version
*/
#if 0
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
#endif

/*
* OpenGL
*/
//#if 0
#include <GL/glew.h>

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
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <array>

#include <GLFW/glfw3.h>

#define PI 3.14159265359
int main(void)
{
    GLFWwindow* window = nullptr;

    //Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a windowed mode window and its OpenGL context
    int width = 1900;
    int height = 1200;

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
    
    const char* glsl_version = "#version 130";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

	ImFont* pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20.0f);
	io.FontDefault = io.Fonts->Fonts.back();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, -1.5f, -1.0f, 1.0f); // 4 * 3 ratio, 2D rendering

    /*
        fov - field of view, fov Expressed in radians.
        aspect ratio - viewport width/height
        @param near Specifies the distance from the viewer to the near clipping plane (always positive).
    /// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
    */

    /*  move to the left 100, simulates moving camera to the right
        glm::mat4 view = glm::translate(glm::vec3(-100, 0, 0));
*/
    static glm::vec3 translation = glm::vec3{ 0.0f, 0.0f, 0.0f };
    glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3{ 0.0f, 1.0f, 3.0f })
        * glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    view = glm::inverse(view);

    float rotation = 0.0f; 

    glm::mat4 viewProj = projection * view;

    float r = 0.0f;
    float increment = 0.05f;

    float angle = 0.0f;

    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        float ts = 0.01667f;
        //rotation += 180.0f * ts;

        //Render here
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4("u_ViewProjection", viewProj);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
        shader.SetUniformMat4("u_Transform", transform);

        renderer.Draw(va, ib, shader);
        
        glm::vec3 translation2 = translation;
        translation2.z += 2.0f;
        transform = glm::translate(glm::mat4(1.0f), translation2) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
        shader.SetUniformMat4("u_Transform", transform);
        renderer.Draw(va, ib, shader);

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
          
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::DragFloat3("Translation", glm::value_ptr(translation), 0.05f);
            ImGui::SliderFloat("Rotation", &rotation, -180, 180);

            //angle in degrees = angle in radians * (180 / PI)
            //angle in radians = angle in degrees * (PI / 180)

            //ImGui::SliderAngle("slider angle", &angle);

            //rotation = 180 * angle * (PI / 180);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
    
}
//#endif