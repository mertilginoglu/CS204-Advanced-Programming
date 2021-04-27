#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <random>
#include <time.h>
#include <iomanip> 
#include "HW8DynIntQueue.h"

using namespace std;
mutex coutMutex, queueMutex, counterMutex;
int threshold, counter = 0;
bool c1Slept = false, c2Slept = false;

//This is used to decrease the number of variables in for thread functions.
struct minMax {
	int min;
	int max;
};

//Function to create random integer.
int random_range(const int & min, const int & max) 
{
 static mt19937 generator(time(0));
 uniform_int_distribution<int> distribution(min, max);
 return distribution(generator);
}

//Customer thread function
void arrival(HW8DynIntQueue & queue, minMax arrivalTime, int & totalCustomer, const int & maxCustomer)
{
	while (totalCustomer < maxCustomer) //Customers arrive until max customer number is reached.
	{
		totalCustomer++;
		queueMutex.lock();
		queue.enqueue(totalCustomer);
		int currSize = queue.getCurrentSize(); //Getting current size before unlocking mutex
		queueMutex.unlock();

		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
		struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
		localtime_s(ptm, &tt);  //converting the time structures
		coutMutex.lock();
		cout << "New customer with ID " << totalCustomer << " has arrived (queue size is " << currSize << "): " << put_time(ptm,"%X") << endl;
		coutMutex.unlock();
		
		this_thread::sleep_for(chrono::seconds(random_range(arrivalTime.min, arrivalTime.max))); //Sleep between the ranges given by user.
	}
	return;
}

void checkout(HW8DynIntQueue & queue, minMax checkoutTime, int cashierNo, int & checkoutTotal, const int & maxCustomer)
{
	int item;
	while(counter < maxCustomer)
	{
		queueMutex.lock();
		if (cashierNo == 1)
		{
			if(!c1Slept) //This is used to make cashiers sleep once in the first part of the simulation.
			{
				queueMutex.unlock();
				this_thread::sleep_for(chrono::seconds(random_range(checkoutTime.min, checkoutTime.max)));
				c1Slept = true;
			}
			else if(!queue.isEmpty()) //If there are customers in queue.
			{
				
				queue.dequeue(item);
				int item1 = queue.getCurrentSize();
				queueMutex.unlock();
				
				counterMutex.lock();
				counter++;
				counterMutex.unlock();

				time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
				struct tm *ptm1 = new struct tm;  //creating the time struct to be used in thread
				localtime_s(ptm1, &tt);  //converting the time structures
				coutMutex.lock();
				cout << "Cashier 1 started transaction with customer " << item << " (queue size is " << item1 << "): " << put_time(ptm1,"%X") << endl;
				coutMutex.unlock();
				

				this_thread::sleep_for(chrono::seconds(random_range(checkoutTime.min, checkoutTime.max)));
				tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
				localtime_s(ptm1, &tt);  //converting the time structures
				coutMutex.lock();
				cout << "Cashier 1 finished transaction with customer " << item << " " << put_time(ptm1,"%X") << endl;
				coutMutex.unlock();

			}
			else //If queue is empty, unlock mutex.
			{
				queueMutex.unlock();
			}
		}

		else //Cashier no => 2
		{
			if(!c2Slept) //To sleep once at first.
			{
				queueMutex.unlock();
				this_thread::sleep_for(chrono::seconds(random_range(checkoutTime.min, checkoutTime.max)));
				c2Slept = true;
			}
			else if(!queue.isEmpty())
			{
				if(queue.getCurrentSize() >= threshold)
				{
					queue.dequeue(item);
					int item2 = queue.getCurrentSize();
					queueMutex.unlock();

					counterMutex.lock();
					counter++;
					counterMutex.unlock();

					time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
					struct tm *ptm2 = new struct tm;  //creating the time struct to be used in thread
					localtime_s(ptm2, &tt);  //converting the time structures
					coutMutex.lock();
					cout << "Cashier 2 started transaction with customer " << item << " (queue size is " << item2 << "): " << put_time(ptm2,"%X") << endl;
					coutMutex.unlock();
					
					this_thread::sleep_for(chrono::seconds(random_range(checkoutTime.min, checkoutTime.max)));

					tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
					localtime_s(ptm2, &tt);  //converting the time structures
					coutMutex.lock();
					cout << "Cashier 2 finished transaction with customer " << item << " " << put_time(ptm2,"%X") << endl;
					coutMutex.unlock();

				}
				else
				{
					queueMutex.unlock();
				}
			}
			else
			{
				queueMutex.unlock();
			}
		}
	}
	return;
}


int main()
{
	int maxCustomer, minArrival, maxArrival, minCheck, maxCheck;
	int totalCustomer = 0, checkoutTotal = 0;


	HW8DynIntQueue queue;

	cout << "Please enter the total number of customers: ";
	cin >> maxCustomer;

	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> threshold;

	cout << "Please enter the inter-arrival time range between two customers: " << endl << "Min: ";
	cin >> minArrival;
	cout << "Max: ";
	cin >> maxArrival;

	//Create the struct to be used in thread func.
	minMax CustomerStr;
	CustomerStr.min = minArrival;
	CustomerStr.max = maxArrival;


	cout << "Please enter the checkout time range of cashiers: " << endl << "Min: ";
	cin >> minCheck;
	cout << "Max: ";
	cin >> maxCheck;

	//Create the struct to be used in thread func.
	minMax CheckoutStr;
	CheckoutStr.max = maxCheck;
	CheckoutStr.min = minCheck;

	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &tt);  //converting the time structures
	cout << "Simulation start " << put_time(ptm,"%X") << endl; 
	thread Customer(&arrival,  ref(queue), CustomerStr, totalCustomer, maxCustomer);
	thread Cashier1(&checkout, ref(queue), CheckoutStr, 1, checkoutTotal, maxCustomer);
	thread Cashier2(&checkout, ref(queue), CheckoutStr, 2, checkoutTotal, maxCustomer);

	//Join at last.
	Customer.join();
	Cashier1.join();
	Cashier2.join();
	cout << "Simulation ends";
	return 0;
}