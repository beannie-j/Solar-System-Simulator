#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

    std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //Attaches a shader object to a program object
    glAttachShader(program, vs); 
    glAttachShader(program, fs);

    //links the program object specified by program. If any shader objects of type GL_VERTEX_SHADER are attached to program, they will be used to create an executable that will run on the programmable vertex processor.
    glLinkProgram(program); 

    //Validates a program object. checks to see whether the executables contained in program can execute given the current OpenGL state
    glValidateProgram(program); 

    //frees the memory and invalidates the name associated with the shader object specified by shader. This command effectively undoes the effects of a call to glCreateShader.
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); //glCreateShader — Creates a shader object. A shader object is used to maintain the source code strings that define a shader.
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr); //glShaderSource — Replaces the source code in a shader object
    glCompileShader(id); //compiles the source code strings that have been stored in the shader object specified by shader.

    // Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));

        //Returns the information log for a shader object
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader! " << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }

    }
    return { ss[0].str(), ss[1].str() };
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!\n";

    m_UniformLocationCache[name] = location;

    return location;
}
