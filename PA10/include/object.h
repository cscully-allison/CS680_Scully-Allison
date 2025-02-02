#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "graphics_headers.h"
#include <btBulletDynamicsCommon.h>

//assimp headers
#include <assimp/Importer.hpp> //includes the importer, which is used to read our obj file
#include <assimp/scene.h> //includes the aiScene object
#include <assimp/postprocess.h> //includes the postprocessing variables for the importer
#include <assimp/color4.h> //includes the aiColor4 object, which is used to handle the colors from the mesh objects 
#include <Magick++.h>

class Object
{
  public:
    Object();
    //dynamic object
    Object(std::string filename,btScalar mass, btVector3 interia, btVector3 startOrigin, btScalar friction, btScalar restitution, btScalar damping, int rotate);
    // ball
    Object(btScalar mass, btVector3 inertia, btVector3 startOrigin, btScalar friction, btScalar restitution, btScalar damping);
    //static object
    Object (std::string filename, btVector3 startOrigin, btScalar friction, btScalar restitution, btScalar damping, int indexNumber);
    Object (std::string filename);
    ~Object();
    void setOrientation();
    void Update();
    void UpdateFlipper(int side, unsigned int keyPress, unsigned int dt);
    void UpdateBumper(int scale);
    void ScoreUpdate();
    void BallNumUpdate();
    void Render(GLint scalarLoc, glm::vec3 scalar, GLint specLoc, glm::vec3 spec, GLint spotLoc, glm::vec3 spot, GLint heightLoc, GLfloat height);
    void setBodyTransform(btVector3);
    void setGrav(btVector3 grav);
    void applyForce (int force);
    void setPlunger();

    glm::mat4 GetModel();
    btRigidBody* GetRigidBody();
    glm::vec3 getSpec();
    void setSpec (glm::vec3 s);

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    std::vector<GLuint> TB;

    Assimp::Importer importer;
    const aiScene* scene;

    std::vector<Magick::Blob> m_blob;

    glm::vec3 spec;
    
    /* bullet rigid body stuff */
    btTriangleMesh* mTriMesh;
    btRigidBody* body;

    unsigned int dtInitial;
    bool pressed;

};


#endif /* OBJECT_H */
