#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"

std::string boxTexture = "res/texture/box.PNG";
std::string boxSpecular = "res/texture/boxSpecular.png";
//std::string filePath = "res/texture/awesomeface.png";
std::string backGround = "res/texture/Background.png";


int width = 1600;
int height = 900;
float delthet = 3.0f;
int UnitNum = 0;

double MouseX = (double)width / 2;
double MouseY = (double)height / 2;
bool first = true;

Renderer renderer;
Camera cam("mV", height);

void mouse_callback(GLFWwindow* window, double x, double y)
{
    if (first)
    {
        MouseX = x;
        MouseY = y;
        first = false;
    }

    double delx = x - MouseX;
    double dely = y - MouseY;
    MouseX = x;
    MouseY = y;

    cam.ChangeFace(delx, -dely);
}

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(width, height, "GLEW_3", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }
    else
    {
        std::cout << "Perfect, you successfully put the glew code after a valid openGL rendering context." << std::endl;
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    {
        float ground[] = {
            -100.0f, 0.0f,  100.0f, 0.0f, 0.0f, //0.9f, 0.9f, 0.9f, 1.0f,
             100.0f, 0.0f, -100.0f, 7.0f, 7.0f, //0.9f, 0.9f, 0.9f, 1.0f,
             100.0f, 0.0f,  100.0f, 7.0f, 0.0f, //0.9f, 0.9f, 0.9f, 1.0f,
            -100.0f, 0.0f, -100.0f, 0.0f, 7.0f  //0.9f, 0.9f, 0.9f, 1.0f
        };

        unsigned int groundIndices[] = {
            0, 1, 2,
            1, 3, 0
        };

        float position[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,          // 0 (左下)
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,          // 1 (右上)
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,          // 2 (右下)
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,          // 3 (左上)

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,          // 4 (左下)
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,          // 5 (右上)
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,          // 6 (右下)
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,          // 7 (左上)

            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,          // 0
            -0.5f,  0.5f,  0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,          // 7
            -0.5f,  0.5f, -0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,          // 3
            -0.5f, -0.5f,  0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,          // 4

            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,          // 3
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,          // 5
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,          // 1
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,          // 7

             0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,          // 1
             0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,          // 6
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,          // 2
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,          // 5

             0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,          // 2
            -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,          // 4
            -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,          // 0
             0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,          // 6
        };

        unsigned int indices[] = {
             0,  1,  2,
             1,  3,  0,

             4,  5,  6,
             5,  7,  4,

             8,  9, 10,
             9, 11,  8,

            12, 13, 14,
            13, 15, 12,

            16, 17, 18,
            17, 19, 16,

            20, 21, 22,
            21, 23, 20
        };

        float lightPosition[] = {
            -0.1f, -0.1f, -0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
            -0.1f,  0.1f, -0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
             0.1f,  0.1f, -0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
             0.1f, -0.1f, -0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
            -0.1f, -0.1f,  0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
            -0.1f,  0.1f,  0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
             0.1f,  0.1f,  0.1f, //1.0f, 1.0f, 1.0f, 1.0f,
             0.1f, -0.1f,  0.1f  //1.0f, 1.0f, 1.0f, 1.0f
        };

        unsigned int lightIndices[] = {
            0, 1, 2,
            0, 3, 2,

            3, 2, 6,
            3, 7, 6,

            7, 6, 5,
            7, 4, 5,

            4, 5, 1,
            4, 0, 1,

            1, 5, 6,
            1, 2, 6,

            4, 0, 3,
            4, 7, 3
        };

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

        //Object groundObj(ground, groundIndices, 4 * 5 * sizeof(float), 6, backGround, "mM");
        Object groundObj(ground, groundIndices, 4 * 5 * sizeof(float), 6, "mM");
        groundObj.AddTexture(backGround);
        groundObj.SetLayout(FLOAT, 3);
        groundObj.SetLayout(FLOAT, 2);
        groundObj.AttachBuffer();
        groundObj.Translate(0.0f, -10.0f, 0.0f);
        groundObj.SetTexture(0, UnitNum++);
        groundObj.Unbind();

        //Object obj(position, indices, 24 * 8 * sizeof(float), 36, boxTexture, "mM");
        Object obj(position, indices, 24 * 8 * sizeof(float), 36, "mM");
        obj.AddTexture(boxTexture);
        obj.AddTexture(boxSpecular);
        obj.SetLayout(FLOAT, 3);
        obj.SetLayout(FLOAT, 2);
        obj.SetLayout(FLOAT, 3);
        obj.AttachBuffer();
        obj.Translate(0, 0, 0);
        obj.SetTexture(0, UnitNum++);
        obj.SetTexture(1, UnitNum++);
        obj.Unbind();

        //Object lightObj(lightPosition, lightIndices, 8 * 3 * sizeof(float), 36, "", "mM");
        Object lightObj(lightPosition, lightIndices, 8 * 3 * sizeof(float), 36, "mM");
        lightObj.AddTexture("");
        lightObj.SetLayout(FLOAT, 3);
        lightObj.AttachBuffer();
        lightObj.Translate(2.0f, 2.0f, 2.0f);
        lightObj.Unbind();
        ImVec4 lightColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        float lightPower = 1.0f;

        Shader groundShader({ "res/shader/vertex.shader", "res/shader/fragment.shader" }, 0, 0);
        groundShader.Bind();
        groundShader.setUniform1i("u_Texture", 0);
        groundShader.setUniformMatrix4fv("mM", groundObj.GetMatrix());
        groundShader.setUniformMatrix4fv("mV", cam.GetMatrix());
        groundShader.setUniformMatrix4fv("mP", projection);
        groundShader.Unbind();

        Shader shader({ "res/shader/vertex.shader", "res/shader/fragment.shader" }, 1, 1);
        shader.Bind();
        shader.setUniform1i("u_Texture", 1);
        shader.setUniform1i("h_Texture", 2);
        shader.setUniformMatrix4fv("mV", cam.GetMatrix());
        shader.setUniformMatrix4fv("mP", projection);
        shader.Unbind();

        Shader lightShader({ "res/shader/vertex.shader", "res/shader/fragment.shader" }, 2, 2);
        lightShader.Bind();
        lightShader.setUniformMatrix4fv("mV", cam.GetMatrix());
        lightShader.setUniformMatrix4fv("mP", projection);
        lightShader.Unbind();

        glEnable(GL_DEPTH_TEST);

        glm::vec3 lightPos;
        glm::vec3 camPos;

        bool show_another_window = true;

        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("OpenGL Test");
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("Light Power", &lightPower, 0.0, 1.0);
                ImGui::ColorEdit3("LightColor", (float*)&lightColor);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            /* 在此渲染 */
            
            groundShader.Bind();
            groundObj.TexBind();
            groundShader.setUniformMatrix4fv("mV", cam.GetMatrix());
            renderer.Clear();
            renderer.Draw(*(groundObj.GetVA()), *(groundObj.GetIB()), groundShader);
            groundShader.Unbind();

            lightShader.Bind();
            lightShader.setUniformMatrix4fv("mV", cam.GetMatrix());
            lightShader.setUniformMatrix4fv("mM", lightObj.GetMatrix());
            lightShader.setUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
            lightShader.setUniform4f("objectColor", 1.0f, 1.0f, 1.0f, 1.0f);

            //renderer.Clear();
            renderer.Draw(*(lightObj.GetVA()), *(lightObj.GetIB()), lightShader);
            lightShader.Unbind();
            
            shader.Bind();
            obj.TexBind();
            lightPos = lightObj.GetPosition();
            camPos = cam.GetPosition();
            shader.setUniform3f("lightPosition", lightPos[0], lightPos[1], lightPos[2]);
            shader.setUniform3f("viewPosition", camPos[0], camPos[1], camPos[2]);
            shader.setUniformMatrix4fv("mV", cam.GetMatrix());
            obj.Rotate(delthet, glm::vec3(0.0f, 1.0f, 1.0f));
            shader.setUniformMatrix4fv("mM", obj.GetMatrix());
            shader.setUniform1f("lightPower", lightPower);
            shader.setUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
            renderer.Draw(*(obj.GetVA()), *(obj.GetIB()), shader);
            shader.Unbind();

            cam.ListeningKey(window);
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* 惯例代码 */
            glfwSwapBuffers(window);
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

    }//自动析构

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}