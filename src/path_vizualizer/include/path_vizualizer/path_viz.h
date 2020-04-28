// #ifndef PATH_VIZ_HH

// #define PATH_VIZ_HH

#include <ros/ros.h>
#include <gazebo-7/gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Color.hh>

#include <gazebo-7/gazebo/transport/transport.hh>
#include <gazebo-7/gazebo/msgs/msgs.hh>
#include <geometry_msgs/PoseStamped.h>

#include <gazebo/rendering/rendering.hh>
#include <gazebo/gui/GuiIface.hh>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>


namespace gazebo
{
    class Gazebo_Path_Viz : public SystemPlugin
    {
        // constructor and distructor
        public: Gazebo_Path_Viz();
        public: ~Gazebo_Path_Viz();

        private: std::vector<event::ConnectionPtr> connections;

        public: void Load(int /*_argc*/ , char ** /*_argv*/);
        public: void Init();
        private: void InitScene();
        public: void Update();
        public: void DrawLineAdd(rendering::DynamicLines * l1, double x, double y, double z);
        public: void pose_callback(ConstPoseStampedPtr &msg);
        public: rendering::DynamicLines* createline();
        public: bool csvpath2gazebo(std::string filename);
        private: rendering::DynamicLines * line;
        private: rendering::ScenePtr scene;
        private: rendering::VisualPtr visual;

        // this is the node to get the pose of the robot mobile_base
        private: gazebo::transport::NodePtr gznode;
        private: gazebo::transport::SubscriberPtr gzposeSub;

        private: std::string filename ="pose2path.csv";

        private: std::string color = "Gazebo/Purple";
        private: const std::string topicTogetpose = "/gazebo/default/pose/info";

        private: bool is_pathDRWANcomplete = false;
        private: bool Fonce_done = false;
        
        
            
    };

}
