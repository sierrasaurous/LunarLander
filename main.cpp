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

using namespace std;

class lander{
public:
    double z, zdot, zdotdot;
    double mass, gravity, zforce;
    double target;
    double tolerance;
    
    void initialize();
    double thruster(double F);
};

void lander::initialize(){
    z = rand()%1000;
    zdot = -20;
    gravity = -9.81;
    mass = 10;
    zforce = mass*gravity*-1;
    zdotdot = gravity + zforce/mass;
    target = 0;
    tolerance = (z-target)*0.01;
    cout << "0 \t\t" << z << "\t\t" << zdot << endl;
}

double lander::thruster(double force){
    double accel;
    return accel = gravity + force/mass;
}

double jeremy(double position, double velocity, double time){
    double thrust = position/velocity +2;
    return thrust;
}

void dynamicscalc(double & position, double & velocity, double & time, double g, double m, double timestep, double & accel){
    double force = jeremy(position, velocity, time);
    accel = 0.9*accel + 0.1*force/m;
    velocity = velocity + accel*timestep;
    position = position + velocity*timestep + .5*accel*timestep*timestep;
    time = time + timestep;
}


int main() {
    srand(time(NULL));
    
    double t = 0;
    double tstep = 0.1;
    
    vector<lander> coordinates;
    
    lander d;
    d.initialize();
    coordinates.push_back(d);
    
    ofstream myfile;
    myfile.open ("timestepdata.txt");
    
    while((coordinates.at(0).z-coordinates.at(0).target)>coordinates.at(0).tolerance){
        
        dynamicscalc(coordinates.at(0).z, coordinates.at(0).zdot, t, coordinates.at(0).gravity, coordinates.at(0).mass
                     , tstep, coordinates.at(0).zdotdot);
        cout << t << "\t\t" << coordinates.at(0).z << "\t\t" << coordinates.at(0).zdot << "\n";
        myfile << t << "\t\t" << coordinates.at(0).z << "\t\t" << coordinates.at(0).zdot << "\n";
    };
    
    myfile.close();
    
    return 0;
}
