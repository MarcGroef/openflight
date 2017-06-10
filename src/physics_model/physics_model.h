#ifndef INCLUDED_PHYSICS_MODEL_H_
#define INCLUDED_PHYSICS_MODEL_H_

#include <glm/glm.hpp>
#include <ostream>
class PhysicsModel
{
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

inline void PhysicsModel::update(float deltaTime)
{
    //AngularMovement
    d_summedTorque /= d_angularInertia;
    d_summedTorque *= deltaTime;
    d_angularVelocity += d_summedTorque;
    d_rollPitchYaw += (d_angularVelocity * deltaTime);
    glm::mod(d_rollPitchYaw, 360.0f);
    d_summedTorque = glm::vec3(0,0,0);
    
    //Linear movement
    //store accelerator temporarely in d_summed_force
    d_summedForce /= d_mass; // acc = F/m
    d_summedForce *= deltaTime;
    d_velocity += d_summedForce; // v += acc
    d_summedForce = glm::vec3(0,0,0);
    d_position += (d_velocity * deltaTime);
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