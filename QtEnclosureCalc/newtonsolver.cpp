#include <newtonsolver.h>

/*
            Example:
            double d(0.015);
            double V(0.035);
            Eigen::MatrixXd sol(6,1);
            sol << newtonMethodSolver(d,V);
            afficherBoxDimension( sol);
*/

Eigen::MatrixXd newtonMethodSolver(double d, double V)
{
     /*Solve the non linear equation present in the matrix sys
        The matrix sys contains 6 eqution represention the dimension of a box,
        the aim being to get the dimension inside and outside for a defined volume V
        ,a thickness d of the plate and a ratio of 1x1.6x2.6

        the system is solved using the Newton method iteration:
        (xn+1)=(xn)-[JacobianMatrix of the System]^-1 *(system)
        (yn+1) (yn)

        system=[f1(xn,yn)]      --> formalism for two equation two unknow
               [f2(xn,yn)]

        JacobianMatrix=[df1/dx df1/dy]
                       [df2/dx df2/dy]


        More explication on the video https://www.youtube.com/watch?v=-Ws7cEH7w_U */


     double a(1),b(1),c(1),A(1),B(1),C(1);// initial value of the solution (guess)
     V*=0.001;// l--->m^3
    //initiate the different matrix and value
     Eigen::MatrixXd jaco(6,6);// jacobian matrix declaration
     jaco<<JacobianInit(jaco,a,b,c);// jacobian matrix initialisation
     Eigen::MatrixXd jacoInv(6,6);// jacobian matrix inverted declaration
     jacoInv << jaco.inverse();// invertion of the jacobian matrix
     Eigen::MatrixXd sol(6,1);// ...
     sol<< A,B,C,a,b,c;// initialisation of the solution -> 1 1 1 1 1 1
     Eigen::MatrixXd sys(6,1);
     sys<<system2Solve(sys,sol,d,V);// initiate the system

         for(int ii(0);ii<20;ii++)// number of iteration arbitrary set to 20
    {
        sol=sol-jacoInv*sys;
        sys<<system2Solve(sys,sol,d,V);
        jaco<<JacobianModif(jaco,sol);
        jacoInv << jaco.inverse();

    }
    //    cout << "Here is the matrix sol:" << endl << sol << endl;
    return sol;



}

Eigen::MatrixXd JacobianInit(Eigen::MatrixXd& m,double a, double b,double c)
{
    // define the Jacobian matrix (initial value)
    m << -1, 0, 1.6, 0, 0, 0,
          0, -1, 2.6, 0, 0, 0,
          -1, 0, 0, 1, 0, 0,
          0, -1, 0, 0, 1, 0,
          0, 0, -1, 0, 0, 1,
          0, 0, 0, c*b, a*c ,a*b;
          return m;

}

Eigen::MatrixXd JacobianModif(Eigen::MatrixXd& m,Eigen::MatrixXd&  sol )
{
        // modify the jacobian matrix (on the 3 last numbers in this case) at each iteration
        m(5,5)=sol(3,0)*sol(4,0);
        m(5,4)=sol(3,0)*sol(5,0);
        m(5,3)=sol(5,0)*sol(4,0);
        return m;

}

Eigen::MatrixXd system2Solve(Eigen::MatrixXd& sys,Eigen::MatrixXd& sol,double d,double V)
{
    // redefine the matrix of the system at each iteration or initialisation
//        A 0
//        B 1
//        C 2
//        a 3
//        b 4
//        c 5
        sys << 1.6*sol(2,0)-sol(0,0),2.6*sol(2,0)-sol(1,0),sol(3,0)+2*d-sol(0,0),sol(4,0)+2*d-sol(1,0),
                sol(5,0)+2*d-sol(2,0),sol(3,0)*sol(4,0)*sol(5,0)-V;
        return sys;
}

void afficherBoxDimension(Eigen::MatrixXd sol)
{
     cout<<"The width of the inner box is "<<sol(3,0)<<"m"<<endl;
     cout<<"The length of the inner box is "<<sol(5,0)<<"m"<<endl;
     cout<<"The height of the inner box is "<<sol(4,0)<<"m"<<endl;
     cout<<"The width of the outer box is "<<sol(0,0)<<"m"<<endl;
     cout<<"The length of the outer box is "<<sol(2,0)<<"m"<<endl;
     cout<<"The height of the outer box is "<<sol(1,0)<<"m"<<endl;

}

double matrix2Tab(Eigen::MatrixXd sol)
{
    double solReturn[6];

    return *solReturn;
}
