//
//  EBO.hpp
//  Tutorials
//
//  Created by Hyuna on 2023/01/11.
//

#ifndef EBO_hpp
#define EBO_hpp

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

class EBO
{
public:
    // ID reference of Elements Buffer Object
    GLuint ID;
    // Constructor that generates a Elements Buffer Object and links it to indices
    EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void Bind();
    // Unbinds the EBO
    void Unbind();
    // Deletes the EBO
    void Delete();
};

#endif /* EBO_hpp */
