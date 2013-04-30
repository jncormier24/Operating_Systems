"""
Lab 4: Which one is better?
By: Joe Cormier
The purpose of this lab is to figure out which algorithm is better, First Come First Server or Round Robbin.
"""
#!/usr/bin/python
import random

def test():
	fcfs = [] #creates the FCFS queue
	RR = [] #creates the RR queue
	
	for i in range( 1000 ):
		arrival = random.random() * 10000
		service = random.random() * 500
		fcfs.append([arrival, service])
		RR.append([arrival, service])

	f_turn, f_wait = calc_fcfs( fcfs )
	r_turn, r_wait = calc_rr( RR )
	
	print "FCFS turnaround: %r \n" %f_turn
	print "FCFS wait: $r \n" %f_wait
	print "RR turnaround: %r \n" %r_turn
	print "RR wait: %r \n" %r_wait

def calc_fcfs( fcfs ):
	fcfs.sort()
	f_turn = 0
	f_wait = 0 - fcfs[0][1]
	
	for proc in fcfs:
		f_turn = f_turn + proc[1]
		f_wait = f_wait + proc[1]
	
	f_turn = f_turn / 1000
	f_wait = f_wait / 1000
	
	return f_turn, f_wait

def calc_rr( RR ):
	print "running RR"
	RR_dup = RR
	r_turn = 0
	r_wait = 0 - 50
	
	while( len( RR ) > 0):
		for proc in RR:
			proc[1] - 100
			if proc[1] <= 0:
				print "popping %r" %proc
				RR.pop(proc) 
			r_turn = r_turn + 50
			r_wait = r_wait + 50
	
	r_turn = r_turn / 1000
	r_wait = r_wait / 1000
	
	return r_turn, r_wait
		
test()