# turtlesim_plan

#### 介绍
规划路径控制小乌龟走工字形
![1](./imgs/tur1.png)
![2](./imgs/tur2.png)
![3](./imgs/tur3.png)

```bash
mkdir -p catkin_ws/src
cd  catkin_ws/src
git clone https://gitee.com/lirich674/turtlesim_plan.git
cd ../..
caktin_make
source devel/setup.bash
roscore
 rosrun test velocity_publisher
rosrun turtlesim turtlesim_node

```

