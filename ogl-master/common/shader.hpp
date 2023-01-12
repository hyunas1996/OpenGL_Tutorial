#ifndef SHADER_HPP
#define SHADER_HPP

class Shader
{
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char* vertexFile, const char* fragmentFile);

    // Activates the Shader Program
    void Activate();
    
    // Delete the Shader Program
    void Delete();
};



//GLuint ProgramID;
//
//GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
//
//// Activates the Shader Program
//void Activate();

#endif
