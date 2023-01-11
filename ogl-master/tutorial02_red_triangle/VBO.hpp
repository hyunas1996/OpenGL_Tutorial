//
//  VBO.hpp
//  Tutorials
//
//  Created by Hyuna on 2023/01/11.
//

#ifndef VBO_hpp
#define VBO_hpp

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

class VBO{
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);
    
    void Bind();
    void Unbind();
    void Delete();
};

#endif /* VBO_h */
