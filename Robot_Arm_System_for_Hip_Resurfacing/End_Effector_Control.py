#!/usr/bin/env python
import time
import roslib; roslib.load_manifest('ur_driver')
import rospy
import actionlib

#
import roslib; roslib
import ee_cart_imped_action
import roslib; roslib.load_manifest('ee_cart_imped_tutorial')
#

import sys
import copy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg

from std_msgs.msg import String
from control_msgs.msg import *
from trajectory_msgs.msg import *
from sensor_msgs.msg import JointState
from math import pi


JOINT_NAMES = ['shoulder_pan_joint', 'shoulder_lift_joint', 'elbow_joint',
               'wrist_1_joint', 'wrist_2_joint', 'wrist_3_joint']

Q1 = [2.2,0,-1.57,0,0,0]
Q2 = [1.5,0,-1.57,0,0,0]
Q3 = [1.5,-0.2,-1.57,0,0,0]
    
client = None

def move1():
    global joints_pos
    g = FollowJointTrajectoryGoal()
    g.trajectory = JointTrajectory()
    g.trajectory.joint_names = JOINT_NAMES
    try:
        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        g.trajectory.points = [
            JointTrajectoryPoint(positions=joints_pos, velocities=[0]*6, time_from_start=rospy.Duration(0.0)),
            JointTrajectoryPoint(positions=Q1, velocities=[0]*6, time_from_start=rospy.Duration(2.0)),
            JointTrajectoryPoint(positions=Q2, velocities=[0]*6, time_from_start=rospy.Duration(3.0)),
            JointTrajectoryPoint(positions=Q3, velocities=[0]*6, time_from_start=rospy.Duration(4.0))]
        client.send_goal(g)
        client.wait_for_result()
    except KeyboardInterrupt:
        client.cancel_goal()
        raise
    except:
        raise

def move_disordered():
    order = [4, 2, 3, 1, 5, 0]
    g = FollowJointTrajectoryGoal()
    g.trajectory = JointTrajectory()
    g.trajectory.joint_names = [JOINT_NAMES[i] for i in order]
    q1 = [Q1[i] for i in order]
    q2 = [Q2[i] for i in order]
    q3 = [Q3[i] for i in order]
    try:
        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        g.trajectory.points = [
            JointTrajectoryPoint(positions=joints_pos, velocities=[0]*6, time_from_start=rospy.Duration(0.0)),
            JointTrajectoryPoint(positions=q1, velocities=[0]*6, time_from_start=rospy.Duration(2.0)),
            JointTrajectoryPoint(positions=q2, velocities=[0]*6, time_from_start=rospy.Duration(3.0)),
            JointTrajectoryPoint(positions=q3, velocities=[0]*6, time_from_start=rospy.Duration(4.0))]
        client.send_goal(g)
        client.wait_for_result()
    except KeyboardInterrupt:
        client.cancel_goal()
        raise
    except:
        raise
    
def move_repeated():
    g = FollowJointTrajectoryGoal()
    g.trajectory = JointTrajectory()
    g.trajectory.joint_names = JOINT_NAMES
    try:
        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        d = 2.0
        g.trajectory.points = [JointTrajectoryPoint(positions=joints_pos, velocities=[0]*6, time_from_start=rospy.Duration(0.0))]
        for i in range(10):
            g.trajectory.points.append(
                JointTrajectoryPoint(positions=Q1, velocities=[0]*6, time_from_start=rospy.Duration(d)))
            d += 1
            g.trajectory.points.append(
                JointTrajectoryPoint(positions=Q2, velocities=[0]*6, time_from_start=rospy.Duration(d)))
            d += 1
            g.trajectory.points.append(
                JointTrajectoryPoint(positions=Q3, velocities=[0]*6, time_from_start=rospy.Duration(d)))
            d += 2
        client.send_goal(g)
        client.wait_for_result()
    except KeyboardInterrupt:
        client.cancel_goal()
        raise
    except:
        raise

def move_interrupt():
    g = FollowJointTrajectoryGoal()
    g.trajectory = JointTrajectory()
    g.trajectory.joint_names = JOINT_NAMES
    try:
        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        g.trajectory.points = [
            JointTrajectoryPoint(positions=joints_pos, velocities=[0]*6, time_from_start=rospy.Duration(0.0)),
            JointTrajectoryPoint(positions=Q1, velocities=[0]*6, time_from_start=rospy.Duration(2.0)),
            JointTrajectoryPoint(positions=Q2, velocities=[0]*6, time_from_start=rospy.Duration(3.0)),
            JointTrajectoryPoint(positions=Q3, velocities=[0]*6, time_from_start=rospy.Duration(4.0))]
    
        client.send_goal(g)
        time.sleep(3.0)
        print "Interrupting"
        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        g.trajectory.points = [
            JointTrajectoryPoint(positions=joints_pos, velocities=[0]*6, time_from_start=rospy.Duration(0.0)),
            JointTrajectoryPoint(positions=Q1, velocities=[0]*6, time_from_start=rospy.Duration(2.0)),
            JointTrajectoryPoint(positions=Q2, velocities=[0]*6, time_from_start=rospy.Duration(3.0)),
            JointTrajectoryPoint(positions=Q3, velocities=[0]*6, time_from_start=rospy.Duration(4.0))]
        client.send_goal(g)
        client.wait_for_result()
    except KeyboardInterrupt:
        client.cancel_goal()
        raise
    except:
        raise
def test():

	robot = moveit_commander.RobotCommander()
	scene = moveit_commander.PlanningSceneInterface()
	group = moveit_commander.MoveGroupCommander("manipulator")
	display_trajectory_publisher = rospy.Publisher('/move_group/display_planned_path',moveit_msgs.msg.DisplayTrajectory)
	try:
		print "============ Generating plan"

		waypoints = []

# position: 
#   x: 0.484467703589
#   y: 0.109126478876
#   z: 0.427125764458
# orientation: 
#   x: 4.96855655485e-05
#   y: 0.707128424213
#   z: -5.203839691e-05
#   w: 0.707085133837

		waypoints.append(group.get_current_pose().pose)
		wpose = geometry_msgs.msg.Pose()

		wpose.orientation.x = -2.64250307892e-05
		wpose.orientation.y = 0.707140563721
		wpose.orientation.z = -1.21447841307e-06
		wpose.orientation.w = 0.707072996543

		wpose.position.x = waypoints[0].position.x 
		wpose.position.y = waypoints[0].position.y  
		wpose.position.z = waypoints[0].position.z+0.15
		waypoints.append(copy.deepcopy(wpose))

		# second move down
		wpose.position.x = waypoints[0].position.x+0.15
		
		waypoints.append(copy.deepcopy(wpose))

		# third move to the side
		wpose.position.z = waypoints[0].position.z
		waypoints.append(copy.deepcopy(wpose))

		wpose.position.x = waypoints[0].position.x
		waypoints.append(copy.deepcopy(wpose))


		(plan3, fraction) = group.compute_cartesian_path(waypoints,0.0007,0.0)   	
																			# waypoints to follow
																			# eef_step
																			# jump_threshold
		print "============ Waiting while RVIZ displays plan3..."
		rospy.sleep(5)
		display_trajectory = moveit_msgs.msg.DisplayTrajectory()

		display_trajectory.trajectory_start = robot.get_current_state()
		display_trajectory.trajectory.append(plan3)
		display_trajectory_publisher.publish(display_trajectory);
		#group.execute(plan3)
		
		#client.send_goal(g)
		#client.wait_for_result()
	except KeyboardInterrupt:
		#client.cancel_goal()
		raise
	except:
		raise

def test2():
	
	robot = moveit_commander.RobotCommander()
	scene = moveit_commander.PlanningSceneInterface()
	group = moveit_commander.MoveGroupCommander('manipulator')
	display_trajectory_publisher = rospy.Publisher('/move_group/display_planned_path',moveit_msgs.msg.DisplayTrajectory)
	try:
		#home -193.48mm 2.56mm 601.99mm 2.4428 24129 -2.4117
		#-193.48 2.61 297.66 2.443 2.412 -2.411 current
		## Planning to a Pose goal
		## ^^^^^^^^^^^^^^^^^^^^^^^
		## We can plan a motion for this group to a desired pose for the 
		## end-effector 1m=1000mm 1cm = 10mm
		print "============ Generating plan 1"

		#pose_target = geometry_msgs.msg.Pose()
		pose_target = group.get_current_pose().pose
# position: 
#   x: 0.484467703589
#   y: 0.109126478876
#   z: 0.427125764458
# orientation: 
#   x: 4.96855655485e-05
#   y: 0.707128424213
#   z: -5.203839691e-05
#   w: 0.707085133837

		pose_target.position.x = 0.00000294186 
		pose_target.position.y = 0.191450000031
		pose_target.position.z = 1.00105899965

		pose_target.orientation.x = 0.00001691583
		pose_target.orientation.y = 0.00001691827
		pose_target.orientation.z = 0.707132202906
		pose_target.orientation.w = 0.707081358148

		group.set_pose_target(pose_target)
		
		plan1 = group.plan()

		print "============ Waiting while RVIZ displays plan1..."
		rospy.sleep(5)


		## You can ask RVIZ to visualize a plan (aka trajectory) for you.  But the
		## group.plan() method does this automatically so this is not that useful
		## here (it just displays the same trajectory again).
		print "============ Visualizing plan1"
		display_trajectory = moveit_msgs.msg.DisplayTrajectory()

		display_trajectory.trajectory_start = robot.get_current_state()
		display_trajectory.trajectory.append(plan1)
		display_trajectory_publisher.publish(display_trajectory);

		print "============ Waiting while plan1 is visualized (again)..."
		rospy.sleep(5)

		#group.go(wait=True)
		

	except KeyboardInterrupt:

		raise
	except:
		raise
def test3():
    try:
		control = ee_cart_imped_action.EECartImpedClient('UR5')
		control.addTrajectoryPoint(0.5, 0, 0, 0, 0, 0, 1,
		                           1000, 1000, 1000, 30, 30, 30,
		                           False, False, False, False, False,
		                           False, 4, '/ee_link');
		control.addTrajectoryPoint(0.75, 0, 0, 0, 0, 0, 1,
		                           50, 1000, 1000, 30, 30, 30,
		                           False, False, False, False, False,
		                           False, 6, '/ee_link');
		control.sendGoal()
    except KeyboardInterrupt:
        #client.cancel_goal()
        raise
    except:
        raise

def main():
	global client
	# global client2
	try:
		#moveit_commander.roscpp_initialize(sys.argv)
		rospy.init_node("test_move", anonymous=True, disable_signals=True)
		client = actionlib.SimpleActionClient('follow_joint_trajectory', FollowJointTrajectoryAction)
		# client2 = actionlib.SimpleActionClient('ee_cart_imped_action', ee_cart_imped_msgs.msg.EECartImpedAction)
		print "Waiting for server..."
		client.wait_for_server()
		# client2.wait_for_server()
		print "Connected to server"
		parameters = rospy.get_param(None)
		index = str(parameters).find('prefix')
		if (index > 0):
			prefix = str(parameters)[index+len("prefix': '"):(index+len("prefix': '")+str(parameters)[index+len("prefix': '"):-1].find("'"))]
			for i, name in enumerate(JOINT_NAMES):
					JOINT_NAMES[i] = prefix + name
			print "This program makes the robot move between the following three poses:"
			print str([Q1[i]*180./pi for i in xrange(0,6)])
			print str([Q2[i]*180./pi for i in xrange(0,6)])
			print str([Q3[i]*180./pi for i in xrange(0,6)])
			print "Please make sure that your robot can move freely between these poses before proceeding!"
			inp = raw_input("Continue? y/n: ")[0]
			if (inp == 'y'):
				
				#move1()
				#move_repeated()
				#move_disordered()
				#move_interrupt()
				#test()
				#test2()
				test3()
		else:
			print "Halting program"
		
	except KeyboardInterrupt:
			rospy.signal_shutdown("KeyboardInterrupt")
			raise

if __name__ == '__main__': main()