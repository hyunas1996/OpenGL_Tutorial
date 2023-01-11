// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

// 해당 tutorial에서는 shader를 아직 배우지 X. just copy & paste
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


// 이렇게 하고 나면, window가 normalize 됨
// 즉, 좌측 = -1, 우측 = +1, 하단 = -1, 상단 = +1

int main(void){

    // GLFW 초기화
    glfwInit();

    // glfwWindowHint를 사용해서 GLFW를 설정
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3 설정
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // OpenGL 3.3 설정
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac에서는 이것 추가해야함
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window 선언
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 02", NULL, NULL);

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // GLFW에게 window를 current context로 사용하고 싶다고 전달
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // *************** TUTORIAL 02 ***************//

    // *************** SHADER ***************//
    // 이제 이 vertices를 graphics pipeline 내부로 넣어야함
    // vertex shader, fragment shader는 우리가 references로만 접근이 가능함, 즉 value로 접근 가능

    // glCreateShader(Shader 종류)를 활용해서 shader 생성
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // GLuint: OpenGL unsigned integer

    // line 61에서 생성한 shader 변수에 shader source code를 적용
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // 근데 GPU는 이 source code를 바로 이해할 수 없기 때문에, machine code로 compile 해 줘야함
    glCompileShader(vertexShader); // 이제 vertext shader 완성

    // 동일 과정을 fragment shader에 대해서도 진행
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 이제 이 shader를 직접 사용하기 위해서는 shader program이라는 것으로 wrap up 해줘야함
    GLuint shaderProgram = glCreateProgram();

    // shaderProgram에게 vertex shader와 fragment shader를 plug in
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram); // 실제 wrap up 처리하는 함수

    // 이제 shader program에 vertex shader와 fragment shader가 다 들어갔으므로, 얘네는 더이상 사용 X -> delete
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // 이렇게 하면 shader 관련 부분은 완료.
    
//    GLuint shaderProgram = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

    // *************** SHADER ***************//

    
    // 삼각형의 꼭지점
    GLfloat vertices[] =  // float을 써도 되긴 하지만, GLfloat을 사용하는 것이 openGL 내부 연산에서 좀 더 안전
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

    
    // 이제 openGL에게 vertices를 어떻게 사용할지, 어떻게 해석할지를 알려줘야함
    // CPU와 GPU는 좀 느려.. 그래서 Big Batch = Buffer라는 것을 사용할 거야
    
    
    // *************** Vertex Buffer ***************//
    GLuint VAO;
    GLuint VBO; // 보편적으로 VBO는 array. 여기 예제에서는 object가 하나라서 이렇게 선언

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); // glGenBeffuer함수로 buffer를 생성. 인자: object #, vertex beffer

    glBindVertexArray(VAO);

    // OpenGL의 Binding: 특정 object를 current object로 설정. 그 종류의 object를 수정하는 함수가 호출되면, current object가 수정되는 셈
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // GL_ARRAY_BUFFER: vertex buffer binding 용

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // vertex buffer에 실제 vertices를 넣어줌


    // 그러나 여전히 OpenGL은 vertices를 어떻게 해석해야할 지 모름
    // 그걸 돕는 VAO를 사용
    // VAO는 VBO보다 반드시 먼저 선언 되어야함. => Line 94, 97, 99


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // glVertexAttribPointer: OpenGL이 VBO를 해석하도록 하는 함수
    glEnableVertexAttribArray(0); // glEnableVertexAttribArray: 위에서 만든 걸 enabling

    // nice if you do it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // *************** Vertex Buffer ***************//


    // window 종료하지 않을 경우 지속
    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);
        
        // tutorial 2에서부터 glClearColor와 glClear를 while loop 안으로 가져옴
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // background color
        glClear(GL_COLOR_BUFFER_BIT);

        // shaderProgram을 사용하라고 명시
        glUseProgram(shaderProgram);

        // bind VAO (이게 지금은 object 한개라서 필수는 아니지만, 이 과정을 통해서 openGL에게 이 array를 사용하라고 명시하는 것)
        glBindVertexArray(VAO);

        // Draw function
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffer
        glfwSwapBuffers(window);

        glfwPollEvents(); // 마우스 등을 사용하여 윈도우 사이즈를 조정했는지 확인하고 반영하는 함수

        // window에 색상 추가

    }
    
    
    // 더 이상 사용하지 않는 것들 삭제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // window로 해야할 일이 다 끝나면, window를 종료시키기
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}






//int main2( void )
//{
//	// Initialise GLFW
//	if( !glfwInit() )
//	{
//		fprintf( stderr, "Failed to initialize GLFW\n" );
//		getchar();
//		return -1;
//	}
//
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Open a window and create its OpenGL context
//	window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
//	if( window == NULL ){
//		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
//		getchar();
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Initialize GLEW
//	glewExperimental = true; // Needed for core profile
//	if (glewInit() != GLEW_OK) {
//		fprintf(stderr, "Failed to initialize GLEW\n");
//		getchar();
//		glfwTerminate();
//		return -1;
//	}
//
//	// Ensure we can capture the escape key being pressed below
//	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//
//	// Dark blue background
//	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//
//	GLuint VertexArrayID;
//	glGenVertexArrays(1, &VertexArrayID);
//	glBindVertexArray(VertexArrayID);
//
//	// Create and compile our GLSL program from the shaders
//	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
//
//
//	static const GLfloat g_vertex_buffer_data[] = {
//		-1.0f, -1.0f, 0.0f,
//		 1.0f, -1.0f, 0.0f,
//		 0.0f,  1.0f, 0.0f,
//	};
//
//	GLuint vertexbuffer;
//	glGenBuffers(1, &vertexbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//
//	do{
//
//		// Clear the screen
//		glClear( GL_COLOR_BUFFER_BIT );
//
//		// Use our shader
//		glUseProgram(programID);
//
//		// 1rst attribute buffer : vertices
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//		glVertexAttribPointer(
//			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//			3,                  // size
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			0,                  // stride
//			(void*)0            // array buffer offset
//		);
//
//		// Draw the triangle !
//		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
//
//		glDisableVertexAttribArray(0);
//
//		// Swap buffers
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	} // Check if the ESC key was pressed or the window was closed
//	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
//		   glfwWindowShouldClose(window) == 0 );
//
//	// Cleanup VBO
//	glDeleteBuffers(1, &vertexbuffer);
//	glDeleteVertexArrays(1, &VertexArrayID);
//	glDeleteProgram(programID);
//
//	// Close OpenGL window and terminate GLFW
//	glfwTerminate();
//
//	return 0;
//}
//
