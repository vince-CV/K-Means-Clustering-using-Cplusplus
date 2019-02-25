#include <vector>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "json11.hpp"



using namespace cv;
using namespace std;
using namespace vince;

int main() 
{

	vector<Point2f> projectdata = getROIs(project);
	vector<Point2f> kmeans_centroids;

	kmeans_centroids = K_Means_Centroids(projectdata, 12);

	return 0;

}



