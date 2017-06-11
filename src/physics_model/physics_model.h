#ifndef INCLUDED_PHYSICS_MODEL_H_
#define INCLUDED_PHYSICS_MODEL_H_

#include <glm/glm.hpp>
#include <ostream>
class PhysicsModel
{
protected:
    float d_mass;
    glm::vec3 d_position;
    glm::vec3 d_velocity;
    glm::vec3 d_angularVelocity;
    glm::vec3 d_summedForce;
    glm::vec3 d_summedTorque;
    glm::vec3 d_rollPitchYaw;
    glm::vec3 d_angularInertia;
public:
    PhysicsModel(float mass, glm::vec3 const &position, glm::vec3 const &velocity, glm::vec3 const &angInertia);
    void applyForce(glm::vec3 const &force);
    void applyTorque(glm::vec3 const &force);
    void update(float deltaTime);
    friend std::ostream &operator<<(std::ostream &ostr, PhysicsModel const &model);
};



inline void PhysicsModel::applyForce(glm::vec3 const &force)
{
    d_summedForce += force;
}

inline void PhysicsModel::applyTorque(glm::vec3 const &torque)
{
    d_summedTorque += torque;
}
 

inline std::ostream &operator<<(std::ostream &ostr, glm::vec3 const &vec)
{
    ostr << '[' << vec.x << ", " << vec.y << ", " << vec.z << ']';
    return ostr;
}

inline std::ostream &operator<<(std::ostream &ostr, PhysicsModel const &model)
{
    ostr << "PhysicsModel:\n";
    ostr << "   Mass:  " << model.d_mass << \
    "\n   Position: " << model.d_position << \
    "\n   Velocity: " << model.d_velocity << \
    "\n   RollPitchYaw: " << model.d_rollPitchYaw << \
    "\n   AngularVelocity: " << model.d_angularVelocity << '\n';
    return ostr;
}
#endif