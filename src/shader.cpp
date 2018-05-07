#include "shader.h"

#include <iostream>
#include <fstream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string &fileName);
static GLuint CreateShader(const std::string &text, GLenum shaderType);

Shader::Shader(const std::string &filename) {

    this->program = glCreateProgram();

    this->shaders[VERTEX_SHADER] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER);
    this->shaders[FRAGMENT_SHADER] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(this->program, this->shaders[i]);

    glBindAttribLocation(this->program, 0, "position");
    glBindAttribLocation(this->program, 1, "texCoord");
    glBindAttribLocation(this->program, 2, "normal");
    glBindAttribLocation(this->program, 3, "color");

    glLinkProgram(this->program);
    CheckShaderError(this->program, GL_LINK_STATUS, true, "Error: program linking failed.\n");

    glValidateProgram(this->program);
    CheckShaderError(this->program, GL_VALIDATE_STATUS, true, "Error: program is invalid.\n");

    this->uniforms[TRANSFORM_U] = glGetUniformLocation(this->program, "transform");
    this->uniforms[VIEWPROJECTION_U] = glGetUniformLocation(this->program, "view");

}

Shader::~Shader() {

    for(unsigned int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(this->program, this->shaders[i]);
        glDeleteShader(this->shaders[i]);
    }

    glDeleteProgram(this->program);

}

void Shader::bind() {

    glUseProgram(this->program);

}

void Shader::update(const Transform &transform, const Camera &camera) {

    glm::mat4 model =  transform.getModel();
    glm::mat4 modelViewProjection = camera.getViewProjection();

    glUniformMatrix4fv(this->uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(this->uniforms[VIEWPROJECTION_U], 1, GL_FALSE, &modelViewProjection[0][0]);

}

static GLuint CreateShader(const std::string &text, GLenum shaderType) {

    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr << "Error: shader creation failed!\n";

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed.");

    return shader;

}

static std::string LoadShader(const std::string &fileName) {

    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << '\n';
    }

    return output;
}


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {

    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
