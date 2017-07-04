sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update
sudo apt-get install ros-lunar-desktop-full
sudo rosdep init
rosdep update
echo "source /opt/ros/lunar/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt-get install python-rosinstall

sudo apt-get install ros-lunar-cv-bridge -y
sudo apt-get install ros-lunar-image-transport -y
sudo apt-get install ros-lunar-camera-info-manager -y
sudo apt-get install ros-lunar-tf -y
sudo apt-get install ros-lunar-pcl-ros -y
sudo apt-get install ros-lunar-rgbd-launch -y

git clone https://github.com/IntelRealSense/librealsense.git
git clone https://github.com/intel-ros/realsense.git
git clone https://github.com/Beck-Sisyphus/my_pcl_tutorial.git

sudo apt-get install libusb-1.0-0-dev pkg-config
sudo apt-get install libglfw3-dev
mkdir build && cd build
cmake ../
make && sudo make install
sudo cp config/99-realsense-libusb.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && udevadm trigger
sudo apt-get install libssl-dev
cd librealsense
./scripts/patch-realsense-ubuntu-xenial.sh

cd ../realsense
git checkout 1.5.0

cd ../..
rosdep install --skip-keys=librealsense --from-paths -i src/librealsense
