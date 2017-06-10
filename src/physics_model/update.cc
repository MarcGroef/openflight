#include "physics_model.ih"

void PhysicsModel::update(float deltaTime)
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