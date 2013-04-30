"""
Lab 4: Which one is better?
By: Joe Cormier
The purpose of this lab is to figure out which algorithm is better, First Come First Server or Round Robbin.
"""
#!/usr/bin/python
import random
from copy import copy, deepcopy

def test():
	fcfs = [] #creates the FCFS queue
	RR = [] #creates the RR queue
	context = 0
	quanta = 100
	
	for i in range( 1000 ):
		arrival = random.random() * 10000
		service = random.random() * 500
		fcfs.append([arrival, service])
		RR.append([arrival, service])

	file = open("Which_is_better.txt", "w")
	header = """Lab 4: Which one is better?
By: Joe Cormier
The purpose of this lab is to figure out which algorithm is better, First Come First Server or Round Robbin.
"""

	file.write(header)
	
	f_turn, f_wait = calc_fcfs( fcfs )
	file.write("+--------------------------------------------+\n")
	file.write( "| FCFS turnaround: %r \n" %f_turn )
	file.write( "| FCFS wait: %r \n" %f_wait )
	file.write("+--------------------------------------------+\n")
	while( context < 30 ):
		file.write( "| RR Context: %r \n" %context )
		quanta = 100
		while( quanta < 300 ):
			r_turn, r_wait = calc_rr( RR, context, quanta )
			file.write( "| RR quanta: %r \n" %quanta )
			file.write( "| RR turnaround: %r \n" %r_turn )
			file.write( "| RR wait: %r \n" %r_wait )
			quanta += 50
		context += 5
		file.write("+--------------------------------------------+\n")

	file.close()
def calc_fcfs( fcfs ):
	fcfs.sort()
	f_turn = 0
	f_wait = -fcfs[0][1]
	
	for proc in fcfs:
		f_turn = f_turn + proc[1]
		f_wait = f_wait + proc[1]
	
	f_turn = f_turn / 1000
	f_wait = f_wait / 1000
	
	return f_turn, f_wait

def calc_rr( RR, context, quanta ):
	RR_dup = deepcopy( RR )
	r_turn = 0
	r_wait = 0
	
	while( len( RR_dup ) > 0):
		for proc in RR_dup:
			r_turn += context
			r_wait += context
			proc[1] = proc[1] - quanta
			if proc[1] <= 0:
				r_turn = r_turn + ( proc[1] + quanta )
				r_wait = r_wait + ( proc[1] + quanta )
				RR_dup.pop( RR_dup.index(proc) )
			else:
				r_turn = r_turn + quanta
			
	
	r_turn = r_turn / 1000
	r_wait = r_wait / 1000
	
	return r_turn, r_wait
		
test()