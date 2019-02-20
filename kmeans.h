#include <vector>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "json11.hpp"

using namespace cv;
using namespace std;

namespace vince
{
	bool flag_maker(vector<Point2f> &A, vector<Point2f> &B);

	vector<vector<double>> Distance_Matrix(vector<Point2f> &Data, vector<Point2f> &Centroids);

	vector<Point2f> K_Means_Centroids(vector<Point2f> &ROIs, int K);

}
