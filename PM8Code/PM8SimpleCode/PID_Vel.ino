////PID gains
//double Kp  = 0.3; // 0.6 goes unstable
//double Kd = 0.001;
//double Ki = 0.6;
//
//double integralError = 0;
//
//double PID_Vel() {
//
//    //Calculate error and the d/dt of error
//    double error = Vel - Vel_desired;
//    double derrordt = error/(t - t_old_enc);
//    integralError = integralError + error*T_enc;
//
//    //Proportional component
//    double input = Kp*(error);
//
//    //Add derivative component
//    input = input + Kd*(derrordt);
//
//    //Add integral component
//    input = input + (Ki*integralError);
//    
//    //Ensure values are something that the motor controller can provide
//    return constrain(input, -10.0, 10.0);
//  
//    error_old = error;
//}
