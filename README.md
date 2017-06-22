# my_pcl_tutorial
Practice ROS point cloud library with Intel Realsense R200 on NVIDIA TX1

## Autostart using systemctl
make a new file called `/etc/systemd/system/ros.service`, and write the following:

```
[Unit]
Description= Robotics Operating System autostart

[Service]
Type=simple
User=%i
ExecStart=/home/ubuntu/catkin_ws/src/my_pcl/tutorial/script/startup.sh

[Install]
WantedBy=multi-user.target
```

And edit the `startup.sh` for the target command, be careful to `source /home/ubuntu/catkin_ws/devel/setup.bash` before `roslaunch` or `rosrun`.
