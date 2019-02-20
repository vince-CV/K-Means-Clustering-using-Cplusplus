#include <vector>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "json11.hpp"
#include "vinceAlgorithm.h"


using namespace cv;
using namespace std;




namespace vince {

	bool flag_maker(vector<Point2f> &A, vector<Point2f> &B)
	{

		int size = A.size();
		for (int elem = 0; elem < size; elem++)
		{
			if (A[elem] != B[elem])
			{
				return 1;
			}
		}

		return 0;
	}

	vector<vector<double>> Distance_Matrix(vector<Point2f> &Data, vector<Point2f> &Centroids)
	{
		int Data_size = Data.size();
		int Cetr_size = Centroids.size();

		vector<double> distance;
		vector<vector<double>> distance_matrix;

		double eDis;

		for (int i = 0; i < Cetr_size; i++)
		{
			distance.clear();
			for (int j = 0; j < Data_size; j++)
			{
				eDis = squareDistance(Data[j], Centroids[i]);
				distance.push_back(eDis);
			}
			distance_matrix.push_back(distance);
		}

		return distance_matrix;

	}

	vector<Point2f> K_Means_Centroids(vector<Point2f> &ROIs, int K)
	{
		vector<int> ramdon;
		vector<Point2f> current_Centroids;
		vector<Point2f> previous_Centroids;
		vector<int> cluster_info;
		vector<vector<double>> Distance_matrix;
		vector<Point2f> belong_k;
		vector<double> dist;
		int cum_x, cum_y, cnt;
		int n = 0;
		int Row = ROIs.size();
		int Col = K;

		for (int i = 0; i < Row; i++)
		{
			cluster_info.push_back(0);
		}

		srand((unsigned)time(NULL));
		while (n < K)
		{
			int r = rand() % (Row);
			ramdon.push_back(r);
			current_Centroids.push_back(ROIs[r]);
			previous_Centroids.push_back(Point2f(0.0, 0.0));
			n++;
		}

		while (flag_maker(current_Centroids, previous_Centroids))
		{
			previous_Centroids.assign(current_Centroids.begin(), current_Centroids.end());

			Distance_matrix.clear();
			Distance_matrix = Distance_Matrix(ROIs, current_Centroids);

			for (int row_i = 0; row_i < Row; row_i++)
			{
				dist.clear();

				for (int col_i = 0; col_i < Col; col_i++)
				{
					dist.push_back(Distance_matrix[col_i][row_i]);
				}

				cluster_info[row_i] = distance(begin(dist), min_element(begin(dist), end(dist)));
			}

			for (int k_loop = 0; k_loop < K; k_loop++)
			{

				belong_k.clear();
				cum_x = 0;
				cum_y = 0;
				cnt = 0;
				for (int cluster = 0; cluster < Row; cluster++)
				{
					if (cluster_info[cluster] == k_loop)
					{
						cum_x += ROIs[cluster].x;
						cum_y += ROIs[cluster].y;
						cnt++;
					}
				}

				if (cnt != 0)
				{
					current_Centroids[k_loop].x = cum_x / cnt;
					current_Centroids[k_loop].y = cum_y / cnt;
				}

			}

		}

		return current_Centroids;
	};


}

