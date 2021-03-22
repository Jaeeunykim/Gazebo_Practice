#include <gazebo/gazebo.hh>
#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>


int main(int _argc, char **_argv)
{
    gazebo::client::setup(_argc, _argv);

    gazebo::transport::NodePtr node_handle_ = gazebo::transport::NodePtr(new gazebo::transport::Node());
    node_handle_->Init();

    gazebo::transport::PublisherPtr pub =
    node_handle_->Advertise<gazebo::msgs::Any>("~/jebi_mini/right_elevon_start");

    pub->WaitForConnection();

    gazebo::msgs::Any msg;
    msg.set_type(gazebo::msgs::Any_ValueType_DOUBLE);
    msg.set_double_value(std::atof(_argv[1]));

    // gazebo::msgs::Set(&msg, ignition::math::Vector3d(std::atof(_argv[1]), 0, 0));
    pub->Publish(msg);

  gazebo::client::shutdown();

}