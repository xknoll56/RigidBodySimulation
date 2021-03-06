#pragma once
#include "Scene.h"
extern void drawLine(Mesh& line, glm::vec3 from, glm::vec3 to);
extern MainWindow* gMainWindow;

class CubeDropScene: public Scene
{
private:
    PhysicsWorld world;
    BoxCollider collider;
    BoxCollider otherCollider;

    SphereCollider sphereCollider;
    UniformRigidBody rb;
    UniformRigidBody otherRb;
    UniformRigidBody sphereRb;


public:
    CubeDropScene()
    {

    }

    void start()
    {
        float mass = 1.0f;
        float radius = 1.0f;
        float inertia = 1.0f;
        rb = UniformRigidBody(mass, inertia);
        otherRb = UniformRigidBody(mass, inertia);
        sphereRb = UniformRigidBody(mass, inertia);
        // SphereBody otherRb(mass, 0.5f);
        collider = BoxCollider(glm::vec3(0.5f,0.5f,0.5f));
        otherCollider = BoxCollider(glm::vec3(10,5.0f,10));
        otherCollider = BoxCollider(glm::vec3(10.0f,0.1f,10.0f));
        sphereCollider = SphereCollider(0.5f);
        collider.rb = &rb;
        otherCollider.rb = &otherRb;
        sphereCollider.rb = &sphereRb;
        sphereRb.position = glm::vec3(2,8,0);
        rb.position = glm::vec3(-7, 10, 0);
        rb.setVelocity(glm::vec3(5,0,0));
        rb.setAngularVelocity(glm::vec3(0,0,5));
        rb.dynamic = true;
        otherRb.position = glm::vec3(0,-0.1f, 0);
        otherRb.dynamic = false;
        rb.rotation = glm::quat(glm::vec3(0.3f,0.0f, 0.4f));
       // rb.setAngularVelocity(glm::vec3(0,2,0));
        otherRb.rotation = glm::quat(glm::vec3(0.3f, 0,0));
        console.rb = &rb;
       // rb.rotation = glm::quat(glm::vec3(0.0f,0.0f, 0.0f));


        std::vector<Collider*> colliders = {  &sphereCollider, &otherCollider};
        world.gravity = glm::vec3(0,-10.0f,0);
        world.enableResponse = true;
        world.setColliders(&colliders);
    }

    void update(float dt)
    {
        Scene::update(dt);
        //rb.setVelocity(glm::vec3());
        if(gMainWindow->getKey(Qt::Key_Right))
        {
            rb.setVelocity(1.0f*cam.getRight());
            //rb.addForce(2.0f*cam.getRight());
        }
        if(gMainWindow->getKey(Qt::Key_Left))
        {
            rb.setVelocity(-1.0f*cam.getRight());
            //rb.addForce(-2.0f*cam.getRight());
        }
        if(gMainWindow->getKey(Qt::Key_E))
        {
            rb.setVelocity(1.0f*glm::vec3(0,1,0));
        }
        if(gMainWindow->getKey(Qt::Key_Q))
        {
            rb.setVelocity(-1.0f*glm::vec3(0,1,0));
        }
        if(gMainWindow->getKey(Qt::Key_Up))
        {
            rb.setVelocity(glm::cross(glm::vec3(0,1,0), cam.getRight()));
            //rb.addForce(glm::cross(glm::vec3(0,2,0), cam.getRight()));

        }
        if(gMainWindow->getKey(Qt::Key_Down))
        {
            rb.setVelocity(glm::cross(glm::vec3(0,-1,0), cam.getRight()));
            //rb.addForce(glm::cross(glm::vec3(0,-2,0), cam.getRight()));

        }
        if(gMainWindow->getKeyDown(Qt::Key_Space))
        {
            rb.addForce(glm::vec3(0,800,0));
        }
        if(gMainWindow->getKeyDown(Qt::Key_R))
        {
            rb.setVelocity(glm::vec3((float)(rand()%8)/8.0f,0,(float)(rand()%8)/8.0f));
            rb.position = glm::vec3(0,5,0);
            rb.setAngularVelocity(glm::vec3(0,0,0));
            rb.rotation = glm::quat(glm::vec3((float)(rand()%8),(float)(rand()%8),(float)(rand()%8)));
            rb.applyGravity = true;
           // rb.rotation += 0.5f*glm::quat(glm::vec3(PI,0,0))*rb.rotation;

        }

        if(gMainWindow->getKeyDown(Qt::Key_1))
        {
            rb.setVelocity(glm::vec3(0,0,0));
        }

        world.stepWorld(dt);

        if(world.contacts.size()>0)
        {
            cube.meshes[1].setColor(glm::vec3(1,0,0));

            for(int i =0;i<world.contacts.size();i++)
            {
                for(int j =0;j<world.contacts[i].points.size();j++)
                {
                    point.setPosition(world.contacts[i].points[j]);
                    point.draw();
                    if(j == 0)
                    {
                        drawLine(lineMesh, world.contacts[i].b->rb->position, world.contacts[i].b->rb->position+2.0f*world.contacts[i].normal);
                        drawLine(lineMesh, world.contacts[i].a->rb->position, world.contacts[i].a->rb->position-2.0f*world.contacts[i].normal);
                    }
                }
            }
        }
        else
        {
            cube.meshes[1].setColor(glm::vec3(0,1,0));
        }

    }

    void updateDraw(float dt)
    {
        cube.setPosition(rb.position);
        cube.setRotation(rb.rotation);
        cube.setScale(collider.scale);
        cube.draw();

        sphere.setPosition(sphereRb.position);
        sphere.setRotation(sphereRb.rotation);
        sphere.setScale(sphereCollider.scale);
        sphere.draw();


        cube.setPosition(otherRb.position);
        cube.setRotation(otherRb.rotation);
        cube.setScale(otherCollider.scale);
        cube.draw();
       // plane.draw();
    }

};
