/**
 * Project 3
 * By: Joe Cormier
 * This project is intended to be a traffic monitor. It will determine the lenght of time a light will stay green at a 1 way
 * tunnel.
 * Tunnel is 1/2 mile long.
 * Cars move at 15mph
 * */
import java.util.*;
import java.util.concurrent.Semaphore;

public class project3{
	
	int carsLeft = 0;
	Car travel;
	Queue<Car> sendNorth = new LinkedList<Car>();
	Queue<Car> fromNorth = new LinkedList<Car>();
	Queue<Car> sendSouth = new LinkedList<Car>();
	Queue<Car> fromSouth = new LinkedList<Car>();
	Light northLight = new Light( 12, "Red" );
	Light southLight = new Light( 12, "Red" );
	Tunnel tunnel = new Tunnel( false );
	int cases = 1000;
	public static void main(String[] args){
		new project3();		
	}
	
	public project3(){
		long startTime = System.nanoTime();
		System.out.println("Traffic Monitor.");
		while( 0 < cases-- ){
			int dir = (int)(Math.random() * 2);
			if( 1 == dir ){
				Car car = new Car( "North", 15, 0 );
				sendSouth.add( car );
			}
			else{
				Car car = new Car( "South", 15, 0 );
				sendNorth.add( car );
			}
			if( false == tunnel.full ){
				if( "Red" == northLight.status && "Red" == southLight.status ){
					if( null != sendSouth.poll() ){
						northLight.status = "Green";
						fromNorth.add( sendSouth.remove() );
						tunnel.full = true;
					}
					else{
						southLight.status = "Green";
						fromSouth.add( sendNorth.remove() );
						tunnel.full = true;
					}
				}
				else if( "Green" == northLight.status && "Red" == southLight.status ){
					if( null != sendSouth.poll() ){
						northLight.status = "Green";
						fromNorth.add( sendSouth.remove() );
						tunnel.full = true;
					}
					else{
						southLight.status = "Green";
						fromSouth.add( sendNorth.remove() );
						tunnel.full = true;
					}
				}
				else if( "Red" == northLight.status && "Green" == southLight.status ){
					if( null != sendNorth.poll() ){
						southLight.status = "Green";
						fromSouth.add( sendNorth.remove() );
						tunnel.full = true;
					}
					else{
						northLight.status = "Green";
						fromNorth.add( sendSouth.remove() );
						tunnel.full = true;
					}
				}
			}
			else if( true == tunnel.full ){
				System.out.println("The tunnel is full.");
				tunnel.full = false;
			}
			long endTime = System.nanoTime() - startTime;
			System.out.println("The trip took "+endTime+" seconds.");
		}
	}
}

class Car {
	String direction;
	int speed;
	int duration;
	
	public Car( String direction, int speed, int duration ){
		this.direction = direction;
		this.speed = speed;
		this.duration = duration;
	}
	public void setDirection( String direction ){
		this.direction = direction;
	}
	public String getDirection(){
		return this.direction;
	}
	public void setSpeed( int speed ){
		this.speed = speed;
	}
	public int getSpeed(){
		return this.speed;
	}
	public void setDuration( int duration ){
		this.duration = duration;
	}
	public int getDuration(){
		return this.duration;
	}
}

class Light {
	int duration;
	String status;
	
	public Light( int duration , String status){
		this.duration = duration;
		this.status = status;
	}
	public void setDuration( int duration ){
		this.duration = duration;
	}
	public int getDuration(){
		return this.duration;
	}
	public void setStatus( String status ){
		this.status = status;
	}
	public String getStatus(){
		return this.status;
	}
	public void changeStatus(){
		if( this.status == "Red" ){
			this.status = "Green";
		}
		else if( this.status == "Green" ){
			this.status = "Red";
		}
	}
}

class Tunnel {
	boolean full;

	public Tunnel( boolean full ){
		this.full = full;
	}
	public void setFull( boolean full ){
		this.full = full;
	}
	public boolean getFull(){
		return this.full;
	}
}


/*
Process.

Generate Starting Cars in the SendNorth and SendSouth queues.
When a light turns green, one of the queues is released and 
allowed to travel through the tunnel. When the light turns red,
no more cars are released from that queue. When all the cars are 
accounted for, Then the other light can turn green. Thus the process
is repeated.

Lights are green for 2/6/8/10/12 minutes. 
*/

















































