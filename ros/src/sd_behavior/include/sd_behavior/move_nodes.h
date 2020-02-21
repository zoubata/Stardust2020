#include "behaviortree_cpp/bt_factory.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <ros/ros.h>
#include <mutex>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

namespace MoveNodes
{
	void registerNodes(BT::BehaviorTreeFactory& factory, ros::NodeHandle& nh);

	// Async spinner node handle
	static ros::NodeHandle* nh_;
	
	class SetPositionNode : public BT::SyncActionNode
	{
		public:
			SetPositionNode(const std::string& name, const BT::NodeConfiguration& config);

			BT::NodeStatus tick() override;

		    static BT::PortsList providedPorts()
		    {
			    return { 
			    	BT::InputPort<double>("x"), 
					BT::InputPort<double>("y"),
					BT::InputPort<double>("theta")
				};
			}
		
		private:
			ros::Publisher initialpose_pub;
	};
    
    class ConstantVelocityNode : public BT::SyncActionNode
	{
		public:
			ConstantVelocityNode(const std::string& name, const BT::NodeConfiguration& config);

			BT::NodeStatus tick() override;

		    static BT::PortsList providedPorts()
		    {
			    return { 
			    	BT::InputPort<double>("linear_x"), 
					BT::InputPort<double>("linear_y"),
					BT::InputPort<double>("angular_z")
				};
			}
		
		private:
			ros::Publisher cmd_pub;
	};

	class GotoNode : public BT::CoroActionNode
	{
		public:
			GotoNode(const std::string& name, const BT::NodeConfiguration& config);

			BT::NodeStatus tick() override;

			virtual void halt() override;

		    static BT::PortsList providedPorts()
		    {
			    return { 
			    	BT::InputPort<double>("x"), 
					BT::InputPort<double>("y"),
					BT::InputPort<double>("theta"),
					BT::InputPort<double>("x_mul"),
                    BT::InputPort<double>("y_mul"),
                    BT::InputPort<double>("theta_mul"),
					BT::InputPort<double>("comment")
				};
			}

		private:
			MoveBaseClient *ac;
			std::atomic_bool halted_;
			std::mutex ac_mutex_;
	};

	class StopNode : public BT::SyncActionNode
	{
		public:
			StopNode(const std::string& name, const BT::NodeConfiguration& config);

			BT::NodeStatus tick() override;

			static BT::PortsList providedPorts()
		    {
			    return {};
			}

		private:
			MoveBaseClient *ac;
	};

}