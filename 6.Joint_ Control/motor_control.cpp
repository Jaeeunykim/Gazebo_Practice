#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <gazebo/physics/Joint.hh>
#include <ignition/math.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>


namespace gazebo 
{
    class MotorControlPlugin : public ModelPlugin
    {

        public: void Load(physics::ModelPtr _parent, sdf::ElementPtr)
        {
            //model에 모델 포인터를 저장 
            this->model = _parent;

            this->node = transport::NodePtr(new transport::Node());
            this->node->Init(this->model->GetWorld()->Name());
            // this->model->GetJoint("left_elevon_joint")->SetPosition(0,0.872665);
            // update이벤트를 듣는다. 이 이벤트는 시물레이션의 iteration마다 broadcast 한다 
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&MotorControlPlugin::OnUpdate, this));

            std::string prop_topicName = "~/" + this->model->GetName() + "/prop_start";
            std::string left_elevon_topicName = "~/" + this->model->GetName() + "/left_elevon_start";
            std::string right_elevon_topicName = "~/" + this->model->GetName() + "/right_elevon_start";

            this->prop_sub = this->node->Subscribe(prop_topicName, &MotorControlPlugin::StartProp, this);
            this->left_evelon_sub = this->node->Subscribe(left_elevon_topicName, &MotorControlPlugin::StartLeftElevon, this);
            this->right_evelon_sub = this->node->Subscribe(right_elevon_topicName, &MotorControlPlugin::StartRightElevon, this);
        }
        
        // World의 update 이벤트가 시작되면 호출된다
        public: void OnUpdate(){
            
            if(left_elevon_control){
                this->model->GetJoint("left_elevon_joint")->SetPosition(0,left_elevon_radian);
            }
            if(right_elevon_control){
                this->model->GetJoint("right_elevon_joint")->SetPosition(0,right_elevon_radian);
            }
        }
        
        public: void StartProp(ConstAnyPtr &_speed){
            
            double motor_speed = _speed->double_value();

            gzerr << "Subscribe motor speed : " << motor_speed <<std::endl;

            this->model->GetJoint("rotor_0_joint")->SetVelocity(0,-motor_speed);
            this->model->GetJoint("rotor_1_joint")->SetVelocity(0,motor_speed);   

        }

       public: void StartLeftElevon(ConstAnyPtr &_angle){
            if(_angle == 0){
                left_elevon_control= false;
            }
            left_elevon_radian = _angle->double_value();
            gzerr << "Subscribe LeftElevon Degree : " << left_elevon_radian <<std::endl;
            this->model->GetJoint("left_elevon_joint")->SetPosition(0,left_elevon_radian);
            left_elevon_control = true;

        }

       public: void StartRightElevon(ConstAnyPtr &_angle){
            if(_angle == 0){
                right_elevon_control= false;
            }
            right_elevon_radian = _angle->double_value();
            gzerr << "Subscribe RightElevon Degree : " << right_elevon_radian <<std::endl;
            this->model->GetJoint("right_elevon_joint")->SetPosition(0,right_elevon_radian);
            right_elevon_control = true;

        }

        bool left_elevon_control = false;
        bool right_elevon_control = false;
        double left_elevon_radian;
        double right_elevon_radian;

        // model 포인터
        private: physics::ModelPtr model;

        // update 이벤트 포이터
        private: event::ConnectionPtr updateConnection;

        private: transport::NodePtr node;

        private: transport::SubscriberPtr prop_sub;
        private: transport::SubscriberPtr left_evelon_sub;
        private: transport::SubscriberPtr right_evelon_sub;

        // box의 pose 정보 
    };
    // 이 플러그인을 시물레이션 등록 
    GZ_REGISTER_MODEL_PLUGIN(MotorControlPlugin)
}