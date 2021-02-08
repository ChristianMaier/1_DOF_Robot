
#include <ros.h>
#include <ArduinoHardware.h>

#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_srvs/Empty.h>
#include <ros_control_example/pos_service.h>
#include <elapsedMillis.h>
#include <AccelStepper.h>


#define ROS_MESSAGE_CHECK 10000    // 0.01 seconds, times how often arudino is spinned
 
ros::NodeHandle nh;

float f_position = 0.0;
float f_des_position = 0.0;
const int steps_per_rev = 200; // 1,8° per step

AccelStepper stepper1(1, 2, 3);
int i_des_pos_steps = 0;

// functions-------------- 

void messageCb( const std_msgs::Float32& pos_msg){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
  f_des_position = pos_msg.data;
}

void Callback(const ros_control_example::pos_service::Request & req, ros_control_example::pos_service::Response & res)
{
   res.pos = f_position;
}

int calc_pos_in_steps(float pos_in_rad){
  // convert pos from radians to steps
  int steps = round( pos_in_rad/(2*PI)* (float)steps_per_rev);
  return steps;
  }

float calc_pos_in_rad(int pos_in_steps){
  // convert pos from steps to radians
  float pos = ((float)pos_in_steps)/((float)steps_per_rev)*2*PI;
  return pos;
  }

// setup-------------- 

elapsedMicros rosMessageCheck;
ros::Subscriber<std_msgs::Float32> sub("ard_des_joint_position_1", &messageCb );
ros::ServiceServer<ros_control_example::pos_service::Request, ros_control_example::pos_service::Response> service("ard_pos_service", &Callback );

void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
    nh.initNode();
    nh.advertiseService(service);
    delay(1);
    nh.subscribe(sub);

    stepper1.setMaxSpeed(400);
    stepper1.setAcceleration(2000);

    }

// main loop-------------- 

void loop()
{
  // check if the desired position has changed, if yes then set the new position
  int des_pos = calc_pos_in_steps(f_des_position);
  if(des_pos != i_des_pos_steps){
    stepper1.moveTo(des_pos); 
    i_des_pos_steps = des_pos;
    }

  // run the stepper, also update the position var to the new value
  stepper1.run();
  f_position = calc_pos_in_rad(stepper1.currentPosition());
  
  // check ros messages, not done in every loop
  if (rosMessageCheck > ROS_MESSAGE_CHECK) {
    nh.spinOnce();
    rosMessageCheck = 0;
  }

}
