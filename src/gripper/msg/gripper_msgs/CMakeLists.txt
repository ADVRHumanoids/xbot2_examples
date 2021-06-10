cmake_minimum_required(VERSION 3.0)
project (albero_gripper_msgs)
find_package(catkin REQUIRED COMPONENTS std_msgs message_generation)

add_message_files(
    FILES
    Gripper.msg
)

generate_messages(DEPENDENCIES std_msgs)
catkin_package()
