#ifndef NEWTONSOLVER
#define NEWTONSOLVER

#include <iostream>
<<<<<<< HEAD
#include <eigen3/Eigen/LU>
=======
#include <Eigen/LU>
>>>>>>> 4d94345087e03439eb3b4da0e0006b9a2d760490
using namespace std;


Eigen::MatrixXd newtonMethodSolver(double d,double V);
// initiate the value of Jacobian matrix
Eigen::MatrixXd JacobianInit(Eigen::MatrixXd& m,double a, double b,double c);

// modification of the jacobian matrix (at each iteration)
Eigen::MatrixXd JacobianModif(Eigen::MatrixXd& m,Eigen::MatrixXd&  sol );

// construct the matrix of the system to solve (at each iteration)
Eigen::MatrixXd system2Solve(Eigen::MatrixXd& sys,Eigen::MatrixXd& sol,double d,double V);

void afficherBoxDimension(Eigen::MatrixXd sol);

double matrix2Tab(Eigen::MatrixXd sol);



#endif // NEWTONSOLVER

