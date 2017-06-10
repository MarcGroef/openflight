#include "physics_model.ih"

PhysicsModel::PhysicsModel(float mass, vec3 const &position, vec3 const &velocity, vec3 const &angInertia)
:
    d_mass(mass),
    d_position(position),
    d_velocity(velocity),
    d_angularInertia(angInertia)
{

    d_angularVelocity = glm::vec3(0,0,0);
    d_summedForce = glm::vec3(0,0,0);
    d_summedTorque = glm::vec3(0,0,0);
    d_rollPitchYaw = glm::vec3(0,0,0);
}