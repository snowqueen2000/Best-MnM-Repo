// === GLOBAL ENCODER VARIABLES === //
const double GearRatio = 313.0;           // the gear ratio ONLY INPUT INTEGER VALUES
const double countsPerRev_motor = 20.0;   // the counts per revolution of the motor shaft. ONLY INPUT INTEGER VALUES
long counts = 0;                          // Globally initialize encoder counts


void EncoderCalcs() {

    //Read counts and calculate current position/velocity
    counts = myEnc.read();  // get current counts
    Pos = (counts*360.0)/(countsPerRev_motor*GearRatio);   // Position in deg
    Vel = (Pos - Pos_old)/(t - t_old_enc);           // Velocity in deg/sec 

      Serial.print(t, 5);     // print time; comment out if using the serial plotter
      Serial.print(",\t");     // tab command
      Serial.print(Pos, 5);   // print position
      Serial.print(",\t");
      Serial.println(Pos_desired, 5); // print velocity
  
}
