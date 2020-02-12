#!/usr/bin/env python
import rospy
x = 0
strin = ''
if __name__ == '__main__':
	rospy.init_node('hellos_Py_node')
	rate = rospy.Rate(1) # 1000hz, 100 times per second
	while not rospy.is_shutdown():
		for y in range(x):
			strin += '#'
		if(x == 5):
			strin = '###'
		rospy.loginfo(strin)
		x += 1
		strin = ''
		rate.sleep()

