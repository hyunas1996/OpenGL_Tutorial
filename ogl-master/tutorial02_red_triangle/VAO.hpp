//
//  VAO.hpp
//  Tutorials
//
//  Created by Hyuna on 2023/01/11.
//

#ifndef VAO_hpp
#define VAO_hpp

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include"VBO.hpp"

class VAO
{
public:
    // ID reference for the Vertex Array Object
    GLuint ID;
    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO to the VAO using a certain layout
    void LinkVBO(VBO& VBO, GLuint layout);
    // Shader를 위해서 필요한 함수
    void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    // Binds the VAO
    void Bind();
    // Unbinds the VAO
    void Unbind();
    // Deletes the VAO
    void Delete();
};

#endif /* VAO_hpp */
