#include <armadillo>

#include "../view/view.h"
#include "../shader/shader.h"
#include "../shader_program/shader_program.h"
#include "../physics_model/physics_model.h"
#include "../world_object/world_object.h"
#include "../world/world.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>

using namespace std;

int main(int argc, char** argv)
{
    World world;
    WorldObject obj;
    world.addObject(obj);
    cout << obj;
    for(size_t itIdx = 0; itIdx != 10; ++itIdx)
    {
        obj.applyForce({1,0,0});
        obj.applyTorque({1,0,0});
        obj.update(1.0);
        cout << obj;
    }
    ShaderProgram shaders("shaders/simple_fragment.glsl","shaders/simple_vertex.glsl");
    View view(800,600, world);
    //glfwGetFramebufferSize()
    view.addShaders(shaders);
    view.loop(); //runs render loop
    
    
    return 0;
}