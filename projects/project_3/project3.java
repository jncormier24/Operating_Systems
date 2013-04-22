/**
 * Project 3
 * By: Joe Cormier
 * This project is intended to be a traffic monitor. It will determine the lenght of time a light will stay green at a 1 way
 * tunnel.
 * */
import java.util.*;

public class project3{
	public static void main(String[] args){
		int carsLeft = 0;
		int sendNorth = 0;
		int fromNorth = 0;
		int sendSouth = 0;
		int fromSouth = 0;
		Light northLight = new Light( "Red" );
		Light southLight = new Light( "Red" );
		boolean tunnel = false;
		int cases = 5000;
		long totalTime = 0;
		long avgTime = 0;
		System.out.println("Traffic Monitor.");
		while( 0 < cases  ){
			long startTime = System.nanoTime();
			int dir = (int)(Math.random() * 2);
			if( 1 == dir ){
				sendSouth++;
			}
			else if(0 == dir){
				sendNorth++;
			}
			if( false == tunnel ){
				if( "Red" == northLight.status && "Red" == southLight.status ){
					//critical section
					if( 0 < sendSouth ){
						southLight.status = "Green";
						northLight.status = "Red";
						sendSouth--;
						fromNorth++;
						tunnel = true;
					}
					//critical section
					else{
						northLight.status = "Green";
						southLight.status = "Red";
						sendNorth--;
						fromSouth++;
						tunnel = true;
					}
				}
				else if( "Green" == northLight.status && "Red" == southLight.status ){
					//critical section
					if( 0 < sendSouth ){
						southLight.status = "Green";
						northLight.status = "Red";
						sendSouth--;
						fromNorth++;
						tunnel = true;
					}
					//critical section
					else{
						northLight.status = "Green";
						southLight.status = "Red";
						sendNorth--;
						fromSouth++;
						tunnel = true;
					}
				}
				else if( "Red" == northLight.status && "Green" == southLight.status ){
					//critical section
					if( 0 < sendNorth ){
						southLight.status = "Green";
						northLight.status = "Red";
						sendNorth--;
						fromSouth++;
						tunnel = true;
					}
					//critical section
					else{
						northLight.status = "Green";
						southLight.status = "Red";
						sendSouth--;
						fromNorth++;
						tunnel = true;
					}
				}
			}
			else if( true == tunnel ){
				if( "Green" == northLight.status && "Red" == southLight.status ){
					//critical section
					if( 0 < sendSouth ){
						southLight.status = "Green";
						northLight.status = "Red";
						sendSouth--;
						fromNorth++;
						tunnel = true;
					}
					else{
						tunnel = false;
					}
				}
				else if( "Red" == northLight.status && "Green" == southLight.status ){
					if( 0 < sendNorth ){
						tunnel = false;
					}
					//critical section
					else{
						northLight.status = "Green";
						southLight.status = "Red";
						sendSouth--;
						fromNorth++;
						tunnel = true;
					}
				}
			}
			long endTime = System.nanoTime() - startTime;
			totalTime += endTime;
			cases--;
			//System.out.println("The trip took "+endTime+" milliseconds.");
		}
		avgTime = totalTime / 5000;
		System.out.println("The average trip took: "+avgTime+" milliseconds.");
		System.out.println("There were "+fromNorth+" cars that traveled south.");
		System.out.println("There were "+fromSouth+" cars that traveled north.");
	}
}

class Light {
	String status;
	
	public Light( String status){
		this.status = status;
	}
	public void setStatus( String status ){
		this.status = status;
	}
	public String getStatus(){
		return this.status;
	}
}
