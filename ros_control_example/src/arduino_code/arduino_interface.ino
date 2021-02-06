
#include <ros.h>
#include <ArduinoHardware.h>
//#include <ArduinoTcpHardware.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_srvs/Empty.h>
#include <ros_control_example/pos_service.h>
#include <elapsedMillis.h>


#define ROS_MESSAGE_CHECK 10000    // 0.01 seconds, times how often arudino is spinned
 
ros::NodeHandle nh;

std_msgs::Float32 f_msg;
float f_position = 0.0;

void messageCb( const std_msgs::Float32& pos_msg){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
  f_position = pos_msg.data;
}

void Callback(const ros_control_example::pos_service::Request & req, ros_control_example::pos_service::Response & res)
{
   res.pos = f_position;
}

elapsedMicros rosMessageCheck;

ros::Subscriber<std_msgs::Float32> sub("ard_des_joint_position_1", &messageCb );
//ros::Publisher pos_pub("ard_joint_position_1", &f_msg);
ros::ServiceServer<ros_control_example::pos_service::Request, ros_control_example::pos_service::Response> service("ard_pos_service", &Callback );

void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
    nh.initNode();
    nh.advertiseService(service);
    delay(1);
    nh.subscribe(sub);

    //nh.advertise(pos_pub);

    }
  
void loop()
{
  f_msg.data = f_position;
  //pos_pub.publish( &f_msg );
  if (rosMessageCheck >ROS_MESSAGE_CHECK) {
    nh.spinOnce();
    rosMessageCheck = 0;
  }

}
