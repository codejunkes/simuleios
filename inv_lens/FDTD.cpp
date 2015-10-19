/*-------------FDTD.cpp-------------------------------------------------------//
*
*              Finite Difference Time Domain
*
* Purpose: To replicate the results of our invisible lense raytracer with 
*          FDTD. Woo!
*
*   Notes: Most of this is coming from the following link:
*             http://www.eecs.wsu.edu/~schneidj/ufdtd/chap3.pdf
*
*-----------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

// This is the function we writes the bulk of the code in
void FDTD(std::vector<double>& Ez, std::vector<double>& Hy,
          const int final_time, const double eps, const int space, 
          std::ofstream& output);

/*----------------------------------------------------------------------------//
* MAIN
*-----------------------------------------------------------------------------*/

int main(){

    // defines output
    std::ofstream output("FDTD.dat", std::ofstream::out);

    int space = 500, final_time = 1000;
    double eps = 377.0;

    // define initial E and H fields
    std::vector<double> Ez(space, 0.0), Hy(space, 0.0);

    FDTD(Ez, Hy, final_time, eps, space, output);

}

/*----------------------------------------------------------------------------//
* SUBROUTINES
*-----------------------------------------------------------------------------*/

// This is the function we writs the bulk of the code in
void FDTD(std::vector<double>& Ez, std::vector<double>& Hy, 
          const int final_time, const double eps, const int space,
          std::ofstream& output){

    // Time looping
    for (size_t t = 0; t < final_time; t++){

        // Linking the final two elements for an ABC
        Hy[space - 1] = Hy[space - 2];

        // update magnetic field
        for (size_t dx = 0; dx < space - 1; dx++){
            Hy[dx] += (Ez[dx + 1] - Ez[dx]) / eps;
            //output << Hy[dx] << '\n';
        }

        // Linking the first two elements in the electric field
        Ez[0] = Ez[1];

        // update electric field
        for (size_t dx = 1; dx < space; dx++){
            Ez[dx] += (Hy[dx] - Hy[dx-1]) * eps;
            output << Ez[dx] << '\n';
        }

        // set src for next step
        Ez[50] = exp(-(t - 30.0) * (t - 30.0)/100.0);
        /*
        if (t > 0){
            Ez[0] = sin(0.1 * t) / (0.1 * t);
        }
        else{
            Ez[0] = 1;
        }
        */
        output << '\n' << '\n';

    }
}