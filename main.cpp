//
//  main.cpp
//  MoonLander
//
//  Created by Sierra on 9/21/15.
//  Copyright (c) 2015 Sierra Adibi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
//#include "jeremy.h"

using namespace std;

class DOF{
public:
    double s, sdot, sdotdot;
    double mass, gravity, force;
    double target, energy;
    
    void initialize();
};

void DOF::initialize(){
    s = rand()%1000;
    sdot = -5;
    gravity = -9.81;
    mass = 10;
    sdotdot = gravity + force/mass;
    target = 0;
    energy = 0.5*mass*pow(sdot,2)-mass*gravity*s;
    
    cout << "0.00 \t\t" << s << "\t\t" << sdot << "\t\t" << energy << endl;
}

double jeremy(double position, double velocity, double time){
    double thrust = position*10/(velocity);
    return thrust;
}

double dynamicscalc(double & position, double & velocity, double & time, double g, double m, double timestep, double & accel){
    double accelprev = accel;
    double velocityprev = velocity;
    double force = jeremy(position, velocity, time);
    accel = force/m + g;
    velocity = velocity + 0.5*timestep*(accelprev+accel);
    position = position + 0.5*timestep*(velocity+velocityprev);
    time = time + timestep;
    double energy = 0.5*m*pow(velocity,2)-m*g*position;
    return energy; // calc KE, PE, combine later
}


int main() {
    srand(time(NULL));
    
    double t = 0;
    double tstep = 0.01;
    double E;
    
    vector<DOF> coordinates;
    
    DOF d;
    d.initialize();
    coordinates.push_back(d);
    
    ofstream myfile;
    myfile.open ("timestepdata.txt");
    
    while((coordinates.at(0).s>coordinates.at(0).target) && t<20){
        
        E = dynamicscalc(coordinates.at(0).s, coordinates.at(0).sdot, t, coordinates.at(0).gravity, coordinates.at(0).mass
                     , tstep, coordinates.at(0).sdotdot);
        cout << setiosflags(ios::fixed) << setprecision(2) << t << "\t\t" << coordinates.at(0).s << "\t\t" << coordinates.at(0).sdot << "\t\t" << E<< "\n";
        myfile << setiosflags(ios::fixed) << setprecision(2) << t << "\t\t" << coordinates.at(0).s << "\t\t" << coordinates.at(0).sdot << "\t\t"<< E <<"\n";
    };
    
    myfile.close();
    
    return 0;
}
