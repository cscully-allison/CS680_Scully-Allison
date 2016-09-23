#ifndef OBJECT_HIn
#define OBJECT_H

#include <vector>
#include <string>
#include "graphics_headers.h"

class Object
{
  public:
    Object(std::string file);
    ~Object();
    void Update(unsigned int dt, unsigned int pressedKey);
    void Update(unsigned int dt, unsigned int pressedKey, glm::mat4 planet);
    void Render();
    bool loadOBJ (std::string file);

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float rotateAngle;
    float translateAngle;
    glm::mediump_vec2 direction = {1,1};
    
};


#endif /* OBJECT_H */
