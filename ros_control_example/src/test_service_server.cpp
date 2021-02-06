//
// Created by christian on 06.02.21.
//

#include "ros/ros.h"
#include "ros_control_example/pos_service.h"
#include <std_msgs/Float32.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_pos_service");
    ROS_INFO("Usage: test pos_service");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ros_control_example::pos_service>("/ard_pos_service");
    ros::Publisher pub = n.advertise<std_msgs::Float32>("/ard_des_joint_position_1",10);
    ros::Rate r(10); // 10 hz

    ros_control_example::pos_service srv;
    srv.request.dummy = 1.0;
    std_msgs::Float32 des_pos;
    des_pos.data = 0.0;

    while (ros::ok()) {

        if (client.call(srv)) {
            ROS_INFO("Pos: %f", srv.response.pos);
        } else {
            ROS_ERROR("Failed to call service ros_service");
            return 1;
        }

        pub.publish(des_pos);
        ros::spinOnce();
        r.sleep();
        des_pos.data = des_pos.data + 1.0;
        if(des_pos.data > 10) {
            des_pos.data = 0.0;
        }

    }
}