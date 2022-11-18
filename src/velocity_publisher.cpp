/**
 * 该例程将发布turtle1/cmd_vel话题，消息类型geometry_msgs::Twist
 */
#include <math.h>
#include <vector>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

ros::Publisher turtle_vel_pub;

struct point
{
    float x;
    float y;
    point() {}
    point(float a, float b) : x(a), y(b) {} //有参构造
};

std::vector<point> Des;
int id = 0;

void turtlePoseCallback(const turtlesim::Pose &msg)
{
    point des;
    des.x = 4.0;
    des.y = 4.0;
    des = Des[id];

    float x1 = cos(msg.theta);
    float y1 = sin(msg.theta);
    float x2 = des.x - msg.x;
    float y2 = des.y - msg.y;
    float ang_theta=atan2(y2,x2);
    float flag=1.0;
    if(msg.theta>ang_theta){
        if(msg.theta-ang_theta<3.14){
            flag=-1.0;
        }
    }else{
        if(ang_theta-msg.theta>3.14){
            flag=-1.0;
        }
    }

    geometry_msgs::Twist vel_msg;


    std::cout<<id<<std::endl;
    if (fabs(x1 * y2 - x2 * y1) > 0.03 || x1 * x2 + y1 * y2 < -0.1)
    {
        vel_msg.angular.z = 0.2*flag;
        vel_msg.linear.x = 0.0;
    }
    else
    {
        vel_msg.angular.z = 0.0;
        if (fabs(x2) + fabs(y2) > 0.01)
        {
            vel_msg.linear.x = 1.5;
        }
       
    }

    // vel_msg.angular.z = 0.2;
    ROS_INFO("pose[%0.2f m, %0.2f m,%0.2f deg]",
             msg.x, msg.y, msg.theta);
    if (fabs(x2) + fabs(y2) <0.05)
    {
        id+=1;
        if(id==Des.size()){
            id =0;
        }        
    }
    turtle_vel_pub.publish(vel_msg);
}
int main(int argc, char **argv)
{
    // ROS节点初始化
    Des.push_back(point(1.0, 1.0));
    Des.push_back(point(8.0, 1.0));
    Des.push_back(point(8.0, 2.0));
    Des.push_back(point(1.0, 2.0));
    Des.push_back(point(1.0, 3.0));
    Des.push_back(point(8.0, 3.0));
    Des.push_back(point(8.0, 4.0));
    Des.push_back(point(1.0, 4.0));
    Des.push_back(point(1.0, 5.0));
    Des.push_back(point(8.0, 5.0));
    Des.push_back(point(8.0, 6.0));
    Des.push_back(point(1.0, 6.0));
    Des.push_back(point(1.0, 7.0));
    Des.push_back(point(8.0, 7.0));
    Des.push_back(point(8.0, 8.0));
    Des.push_back(point(1.0, 8.0));
    Des.push_back(point(1.0, 9.0));
    Des.push_back(point(8.0, 9.0));
    Des.push_back(point(8.0, 10.0));
    Des.push_back(point(1.0, 10.0));
    Des.push_back(point(1.0, 11.0));
    ros::init(argc, argv, "velocity_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/turtle1/cmd_vel的topic，消息类型为geometry_msgs::Twist，队列长度10
    turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Publisher turtle_pose = n.advertise<turtlesim::Pose>("/turtle1/ppose", 10);
    ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 10, turtlePoseCallback);

    // // 设置循环的频率
    // ros::Rate loop_rate(10);

    // int count = 0;
    // while (ros::ok())
    // {
    //     // 初始化geometry_msgs::Twist类型的消息
    // 	geometry_msgs::Twist vel_msg;
    // 	vel_msg.linear.x = 0.5;
    // 	vel_msg.angular.z = 0.2;
    //     turtlesim::Pose pose_msg;
    //     pose_msg.x=0.2;
    //     pose_msg.y=0.2;
    //     pose_msg.theta=0.3;
    //     // turtle_pose.publish(pose_msg);

    //     // 发布消息
    // 	// turtle_vel_pub.publish(vel_msg);
    // 	ROS_INFO("Publsh turtle velocity command[%0.2f m/s, %0.2f rad/s]",
    // 			vel_msg.linear.x, vel_msg.angular.z);

    //     // 按照循环频率延时
    //     loop_rate.sleep();
    // }

    ros::spin();

    return 0;
}