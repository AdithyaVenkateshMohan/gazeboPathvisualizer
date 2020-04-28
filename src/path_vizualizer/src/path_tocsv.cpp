#include <gazebo-7/gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include<iostream>
#include<fstream>

#include <gazebo-7/gazebo/transport/transport.hh>
#include <gazebo-7/gazebo/msgs/msgs.hh>


#include <gazebo-7/gazebo/gazebo_client.hh>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>


std::string filename = "pose2path.csv";
std::ofstream myFile(filename);
int Datacount = 1000;

void pose_callback(ConstPosesStampedPtr &msg)
{
    // std::cout<<"the message received"<<msg->DebugString()<<std::endl;
    for (int i =0; i < msg->pose_size(); i++)
    {

        const ::gazebo::msgs::Pose &posestamped = msg->pose(i);
        std::string name = posestamped.name();
        bool file_writing = (Datacount > 0);

        if (name == std::string("mobile_base"))
        {
            // std::cout<< name <<std::endl;
            const ::gazebo::msgs::Vector3d &position = posestamped.position();
            // std::cout << "Current position" << position.x() 
            // << " " << position.y() << std::endl;
            if(file_writing)
            {
                myFile << position.x() <<"\t" <<position.y() <<"\n";
                Datacount --;
                if(Datacount == 0)
                {
                    std::cout<<"the data entry is done"<<std::endl;
                    myFile.close();
                }
                
            } 
            

        }

    }
}


int main (int _argc, char ** _argv)

{
    std::string colname = "2DPathTrajectory";
    myFile << colname << "\n";
    myFile << "x" << "\t" << "y" << "\n";
    // myFile.close();
    // myFile.open();
    // myFile << "ha ha ha "<<"\n";
    // myFile.close();
    std::cout<<"the gazebo path to csv file is up and running"<<std::endl;

    gazebo::client::setup(_argc,_argv);
    gazebo::transport::NodePtr gznode (new gazebo::transport::Node());
    gznode->Init();
    std::string poseTopic = "/gazebo/default/pose/info";
    gazebo::transport::SubscriberPtr poseSub = gznode->Subscribe(poseTopic, pose_callback);
    while (true)
    {
        gazebo::common::Time::MSleep(1000);
    }



    gazebo::client::shutdown();
    return 0;

}