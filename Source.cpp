#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <mutex>
#include <omp.h>
void main_loop(double x, int n, int start, int number_thread, double &res);
double sum(int i, double x);
using namespace std;
int number_thread = 8;
int x = 100;
int potok = 1;
int n = 10000;
int flag;
mutex mtx;
int main()
{
	while (potok <= number_thread)
	{
		double result = 0;
		flag = 0;
		int flag_old = flag;
		int sch = 0;
		unsigned int start_time = clock();
			vector<thread> threads;
			for (int i = 1; i <= potok; i++) 
				threads.push_back(thread(main_loop, x, n, i, potok, ref(result)));
			while (sch < potok)
			{
				if (flag != flag_old)
				{
					flag_old++;//flag = flag_old;
					sch++;
				}
			}
		unsigned int search_time = clock() - start_time;
		cout << "Time for " << potok << " thread = " << search_time << endl;
		cout <<"result = "<< result << endl;
		potok++;
		main();
	}


	potok = 1;
	cout << "OMP Library" << endl;
	while (potok <= number_thread)
	{
		double result = 0;
		unsigned int start_time = clock();
		#pragma omp parallel num_threads(potok)
		{
		#pragma omp for
		for (int i = 1; i <= potok; i++)
			main_loop(x, n, i, potok, ref(result));
		}
		unsigned int search_time = clock() - start_time;
		cout << "Time for " << potok << " thread = " << search_time << endl;
		cout << result << endl;
		potok++;
	}

	cout << "Done!" << endl;
	system("pause");
	return 0;
}


double sum(int i, double x)
{
	double res_j = 0;
	for (int j = 1; j <= i; j++)
		res_j += (j + pow(x + j, 1.0 / 3.0)) / (2 * i * j - 1);
	return res_j;
}


void main_loop(double x, int n, int potok, int thread_number, double &result)
{
	double result_i = 0;
	for (int i = potok; i <= n; i += thread_number)
		result_i += sum(i, x);
	mtx.lock();
	result+=result_i;
	flag+=1;
	mtx.unlock();
}	

























//double sum(int i, int n, double x)
//{
//	return i + pow(x + j, 1.0 / 3)) / (2 * i * j - 1;
//}
//
//
//void calculation(double x, int n, int start, int thread_number)
//{
//	double result_i = 0;
//	for (int i = start; i <= n; i += thread_number)
//	{
//		int n_new = n - i + 1;
//		result_i += sum(i, n_new, x);
//	}
//	mtx.lock();
//	result += result_i;
//	mtx.unlock();
//}