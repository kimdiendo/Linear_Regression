// Expanse_Linear_Regression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;

int main()
{
	ifstream ip("winequality-white.csv");
	if (!ip.is_open())
	{
		cout << "ERROR FILE";
	}
	string** dataset = new string  *[4898];
	for (int i = 0; i < 4898 && ip.good(); i++)
	{
		dataset[i] = new string[12];
		for (int j = 0; j < 12; j++)
		{
			getline(ip, dataset[i][j],',');
		}
	}
	ip.close();
	float** updated_data = new float* [4898];
	for (int i = 0; i < 4898; i++)
	{
		updated_data[i] = new float[12];
		for (int j = 0; j < 12; j++)
		{
			updated_data[i][j] = stof(dataset[i][j]);
		}
	}
//Find min , max of each column
	float* list_max = new float[12];
	for (int i = 0; i < 12; i++)
	{
		float max = updated_data[0][i];
		for (int j = 0; j < 4898; j++)
		{
			if (max <= updated_data[j][i])
			{
				max = updated_data[j][i];
			}
		}
		list_max[i] = max;
	}
	float* list_min = new float[12];
	for (int i = 0; i < 12; i++)
	{
		float min = updated_data[0][i];
		for (int j = 0; j < 4898; j++)
		{
			if (min >= updated_data[j][i])
			{
				min = updated_data[j][i];
			}
		}
		list_min[i] = min;
	}
//Min ,Max norlization 
 for(int i=0;i< 12;i++)
 {
	 for (int j = 0; j < 4898; j++)
	 {
		 updated_data[j][i] = (updated_data[j][i] - list_min[i]) / (list_max[i] - list_min[i]);
	 }
 }
 //Get 80% data for training
 int d1 = 4898 * 0.8;
 float** updated_data_train = new float* [d1];
 for (int i = 0; i < d1; i++)
 {
	 updated_data_train[i] = new float[12];
	 for (int j = 0; j < 12; j++)
	 {
		 updated_data_train[i][j] = updated_data[i][j];
	 }
 }
 int k = d1;
 //Get 20% data for testing
 float** updated_data_test = new float* [4898 - d1];
 for (int i = 0; i < 4898-d1; i++)
 {
	 updated_data_test[i] = new float[12];
	 for (int j = 0; j < 12; j++)
	 {
		 updated_data_test[i][j] = updated_data[k][j];
	 }
	 k++;
 }
 //TRAINING 80% DATA:
 float learning_rate = 0.01;
 float b = 0.0;
 float w[11] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
 float loss = 0.0;
 while (1)
 {
	 float* pre_y  = new float[d1];
	 for (int i = 0; i < d1; i++)
	 {
		 float y0 = 0.0;
		 for (int j = 0; j < 11; j++)
		 {
			 y0 = y0 + w[j] * updated_data_train[i][j];
		 }
		 pre_y[i] = y0 + b;
	 }
	 float sum = 0.0;
	 for (int i = 0; i < d1; i++)
	 {
		 sum = sum + pow((pre_y[i]- updated_data_train[i][11]), 2);
	 }
	 loss = sum / d1;
	 cout << "Value of loss function is : " << loss<< endl;
	 if (loss<  0.02)
	 {
		 break;
	 }
	 float* dw = new float[11];
	 for (int t = 0; t < 11; t++)
	 {
		 float y0 = 0.0;
		 for (int i = 0; i < d1; i++)
		 {
			 float y01 = 0.0;
			 for (int j = 0; j < 11; j++)
			 {
				 y01 = y01 + w[j] * updated_data_train[i][j];
			 }
			y0 = y0 + 2 * (y01 + b - updated_data_train[i][11]) * updated_data_train[i][t]; 
		 }
		 dw[t] = y0 / d1;
	 }
	 float b0 = 0.0;
	 for (int i = 0; i < d1; i++)
	 {
		 float b01 = 0.0;
		 for (int j = 0; j < 11; j++)
		 {
			 b01 = b01 + w[j] * updated_data_train[i][j];
		 }
		 b0 = b0 + 2 * (b01 + b - updated_data_train[i][11]);
	 }
	 b = b - learning_rate * (b0 / d1);
	 for (int i = 0; i < 11; i++)
	 {
		 w[i] = w[i] - learning_rate * dw[i];
	 }
 }
 float* pre_y = new float[4898-d1];
 for (int i = 0; i < 4898-d1; i++)
 {
	 float y0 = 0.0;
	 for (int j = 0; j < 11; j++)
	 {
		 y0 = y0 + w[j] * updated_data_test[i][j];
	 }
	 pre_y[i] = y0 + b;
 }
 float sum = 0.0;
 for (int i = 0; i < 4898-d1; i++)
 {
	 sum = sum + pow((pre_y[i] - updated_data_test[i][11]), 2);
 }
 loss = sum / d1;
 cout << "Value of loss function on 20% data for testing is : " << loss << endl;
 return 0;
}


