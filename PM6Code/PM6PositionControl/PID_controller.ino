//PID gains
double Kp  = 0.5; //0.6 goes unstable
double Kd = 0.0312;

//NOTE: Integral component is not included.
double PID_controller() {

    //Calculate error and the d/dt of error
    double error = Pos - Pos_desired;
    double derrordt = error/(t - t_old_enc);

    //Proportional component
    double input = Kp*(error);

    //Add derivative component
    input = input - Kd*(derrordt);
    
    //Ensure values are something that the motor controller can provide
    return constrain(input, -10.0, 10.0);
  

    error_old = error;
  
}
