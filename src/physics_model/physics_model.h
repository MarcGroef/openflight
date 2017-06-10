#ifndef INCLUDED_PHYSICS_MODEL_H_
#define INCLUDED_PHYSICS_MODEL_H_

#include <armadillo>
#include <ostream>
class PhysicsModel
{
    double d_mass;
    arma::mat d_position;
    arma::mat d_velocity;
    arma::mat d_angularVelocity;
    arma::mat d_summedForce;
    arma::mat d_summedTorque;
    arma::mat d_rollPitchYaw;
    arma::mat d_angularInertia;
public:
    PhysicsModel(double mass, arma::mat const &position, arma::mat const &velocity, arma::mat const &angInertia);
    void applyForce(arma::mat const &force);
    void applyTorque(arma::mat const &force);
    void update(double deltaTime);
    friend std::ostream &operator<<(std::ostream &ostr, PhysicsModel const &model);
};



inline void PhysicsModel::applyForce(arma::mat const &force)
{
    d_summedForce += force;
}

inline void PhysicsModel::applyTorque(arma::mat const &torque)
{
    d_summedTorque += torque;
}

inline void PhysicsModel::update(double deltaTime)
{
    //AngularMovement
    d_summedTorque /= d_angularInertia;
    d_summedTorque *= deltaTime;
    d_angularVelocity += d_summedTorque;
    d_rollPitchYaw += (d_angularVelocity * deltaTime);
    //d_rollPitchYaw.mod(360);
    d_summedTorque.fill(0.);
    
    //Linear movement
    //store accelerator temporarely in d_summed_force
    d_summedForce /= d_mass; // acc = F/m
    d_summedForce *= deltaTime;
    d_velocity += d_summedForce; // v += acc
    d_summedForce.fill(0.);
    d_position += (d_velocity * deltaTime);
}

inline std::ostream &operator<<(std::ostream &ostr, PhysicsModel const &model)
{
    ostr << "PhysicsModel:\n";
    ostr << "   Mass:  " << model.d_mass << \
    "\n   Position: " << model.d_position << \
    "   Velocity: " << model.d_velocity << \
    "   RollPitchYaw: " << model.d_rollPitchYaw << \
    "   AngularVelocity: " << model.d_angularVelocity << '\n';
    return ostr;
}
#endif