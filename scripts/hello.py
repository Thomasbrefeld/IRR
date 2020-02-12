#!/usr/bin/env python
import rospy
if __name__ == '__main__':
	rospy.init_node('hello_Py_node')
	rospy.loginfo('hello_Py_node has been started')
	rospy.loginfo('hello World!')
	rospy.sleep(2)
	rospy.loginfo('hello_Py_node ended')
