void pid_control()
{
  Kp=1.4 , Ki=-0, Kd=0 ;
  
  Serial.print("Current X:");
  Serial.print(current_value_x);
  Serial.print("\t");
  Serial.print("Desired Value:");
  Serial.print(desired_value);
  Serial.print("\t");
  error = desired_value - current_value_x;

  
  Serial.print("Error:");
  Serial.print(error);
  Serial.print("\t");
  P_control = Kp * error;
  Serial.print("P_CON:");
  Serial.print(P_control);
  Serial.print("\t");
  I_control = I_control + Ki * error * Time;
  Serial.print("I_CON:");
  Serial.print(I_control);
  Serial.print("\t");
  
  D_control = Kd * (error - error_previous) / Time;
             
  Serial.print("D_CON:");
  Serial.print(D_control);
  Serial.print("\t");
  pid =(P_control + I_control + D_control);
  pid = constrain(pid, -15, 15);
  Serial.print("PID Gain:");
  Serial.print(pid);
  Serial.print("\n");

 /*   if(error < -10 || error > 10)
  {
    PID_control = 0;
  }
  PID_control2 = PID_control * 3.5 ;
  PID_control3 = fabs(PID_control2);
  error_previous = error;
  Serial.print("PID control2:");
  Serial.print(PID_control2);
  Serial.print("\t");
  Serial.print("PID control3:");
  Serial.print(PID_control3);
  Serial.print("\t");*/
}
