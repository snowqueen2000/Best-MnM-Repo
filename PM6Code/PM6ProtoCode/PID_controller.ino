//PID gains
double Kp  = 0.03; 
double Kd = 0.0003;
double Ki = 0.0000;

//CHANGE THIS TO CHANGE VELOCITY
//double Vel_desired = 2; //RPM
double Vel_desiredM = 4; //MnMs per second

//double Vel_desiredDeg = Vel_desired*360.0/60.0; //convert from RPM to deg/s
double Vel_desiredDeg = Vel_desiredM*60; // convert from MnMs/s to deg/s

double integralError = 0;


double PID_controller() {

    //Calculate error and the d/dt of error and integral error
    double error = Vel - Vel_desiredDeg;
    double derrordt = error/(t - t_old_enc);
    integralError = integralError + error*T_enc;
    
    //Proportional component
    double input = Kp*(error);

    //Add derivative component
    input = input - Kd*(derrordt);

    //Add integral component
    input = input - Ki*integralError;
    
    //Ensure values are something that the motor controller can provide
    return constrain(input, -10.0, 10.0);
  

    error_old = error;
  
}
