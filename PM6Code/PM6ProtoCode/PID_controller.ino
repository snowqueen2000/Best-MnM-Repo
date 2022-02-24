//PID gains
double Kp  = 0.5; //0.6 goes unstable
double Kd = 0.0312;

//CHANGE THIS TO CHANGE VELOCITY
double Vel_desired = 2; //RPM

double Vel_desiredDeg = Vel_desired*360.0/60.0; //convert from RPM to deg/s

//NOTE: Integral component is not included.
double PID_controller() {

    //Calculate error and the d/dt of error
    double error = Vel - Vel_desiredDeg;
    double derrordt = error/(t - t_old_enc);

    //Proportional component
    double input = Kp*(error);

    //Add derivative component
    input = input - Kd*(derrordt);
    
    //Ensure values are something that the motor controller can provide
    return constrain(input, -10.0, 10.0);
  

    error_old = error;
  
}
