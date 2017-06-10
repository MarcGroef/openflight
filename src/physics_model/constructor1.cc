#include "physics_model.ih"

PhysicsModel::PhysicsModel(double mass, mat const &position, mat const &velocity, mat const &angInertia)
:
    d_mass(mass),
    d_position(position),
    d_velocity(velocity),
    d_angularInertia(angInertia)
{
    mat zeros(1,3);
    zeros.fill(0.);
    d_angularVelocity = zeros;
    d_summedForce = zeros;
    d_summedTorque = zeros;
    d_rollPitchYaw = zeros;
}