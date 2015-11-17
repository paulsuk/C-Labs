#include "assignment2.h"


double calcAverageWaitingTime(struct Simulation * S)
{
	/*This function takes the simulation S, and returns the average waiting time for packets in a specific router. It does this by adding up the differences between departure times and arrival times of packets and dividing it by the size of the eventQueue which stores the packets in order of departure, with it's arrival and departure time.*/ 
	struct Queue eventQueue = S->eventQueue;
	double waitingTime, sum = 0;
	int n = eventQueue.currSize;
	while(eventQueue.currSize > 0)
	{
		struct Data data = dequeue(&eventQueue);
		waitingTime = data.departureTime - data.arrivalTime;
		sum += waitingTime;
	}
	return sum/n;
}


struct Simulation initSimulation(double arrivalRate, double serviceTime, double simTime)
{
	/*This function initiallizes a simulation by giving the currTime a value of 0, and assigning the appropriate values based on the given arrivalRate, serviceTime, and simTime. As well, it initiallizes the queues buffer and eventQueue using the initQueuefunction in queue.c*/
	struct Simulation S;
	double arrivalTime, departureTime;
	arrivalTime = getRandTime(arrivalRate);
	departureTime = arrivalTime + serviceTime;

	S.currTime = 0;
	S.arrivalRate = arrivalRate;
	S.serviceTime = serviceTime;
	S.timeForNextArrival = arrivalTime;
	S.timeForNextDeparture = departureTime;	
	S.totalSimTime = simTime;
	S.buffer = initQueue();
	S.eventQueue = initQueue();
	return S;
}


double runSimulation(double arrivalRate, double serviceTime, double simTime)
{
	/*This function runs a simulation using a given arrivalRate, serviceTime, and simTime, and returns the average waiting time by using the function calcAverageWaitingTime*/

	//Neccessary variables are initialized and simulation is initiallized using the initSimulation function.
	struct Simulation simulation = initSimulation(arrivalRate, serviceTime, simTime);
	struct Data tempdata;
	int e;

	//Run the simulation until currTime is more than or equal to the specified simTime
	while(simulation.currTime < simTime)
	{
		//Determines whether the next action in time will be an ARRIVAL or DEPARTURE
		if(simulation.timeForNextArrival > simulation.timeForNextDeparture && simulation.buffer.currSize != 0)
		{
			simulation.e = 1;
		}	
		else
		{
			simulation.e = 0;
		}
		
		e = simulation.e;


		switch(e)
		{	
			case ARRIVAL:
				tempdata.arrivalTime = simulation.timeForNextArrival;
				enqueue(&(simulation.buffer), tempdata);
				simulation.currTime = simulation.timeForNextArrival;
				simulation.timeForNextArrival += getRandTime(arrivalRate);
				
				break;

			case DEPARTURE:
				tempdata = dequeue(&(simulation.buffer));
				tempdata.departureTime = simulation.timeForNextDeparture;
				if(simulation.buffer.currSize != 0)
				{
					simulation.timeForNextDeparture += serviceTime;
				}				
				else
				{
					simulation.timeForNextDeparture = simulation.timeForNextArrival + serviceTime;				
				}
				simulation.currTime = simulation.timeForNextDeparture;				
				enqueue(&(simulation.eventQueue), tempdata);
				break;
		}
	}
	//Freeing anything that is stuck in the buffer(things that never departed the queue)
	while(simulation.buffer.currSize > 0)
	{
		tempdata = dequeue(&(simulation.buffer));
	}
	
	//Using the calcAverageWaitingTime function, returns the average waiting time for packets
	return calcAverageWaitingTime(&simulation);
}
