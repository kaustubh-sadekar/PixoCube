#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace kos
{

	class CV_EXPORTS_W imgMap
	{

	    public:
	    	
	        int Wd; 
	        int Hd; 
	    	CV_WRAP imgMap();
	};

	class CV_EXPORTS_W Obj3D
	{

	    public:
	    	
	        std::vector<cv::Point3d> ori_pts3d;
	        CV_PROP std::vector<cv::Point3d> pts3d;
	        float focal_length;
	        cv::Point2d center;
	        cv::Size WindowSize;

	    	CV_WRAP Obj3D(cv::Size WindowSize);
	    	void update3dpts(double s, double squz);
	    	void print3dpts();
	        CV_WRAP void rotateObj(CV_IN_OUT double alpha,CV_IN_OUT double beta,CV_IN_OUT double gamma);
	};

	class CV_EXPORTS_W vcam
	{

	    public:
	    	
	        CV_PROP cv::Mat cameraMatrix;
	        CV_PROP cv::Mat distCoeff;
	        CV_PROP cv::Mat rotVec;
	        CV_PROP cv::Mat txVec;
	        CV_PROP std::vector<cv::Point2d> pts2d;
	        CV_PROP float focal_length;
	        cv::Point2d center;
	        cv::Size WindowSize;
	        std::vector< std::vector<cv::Point3d> > cubeFacePts;

	    	CV_WRAP vcam(cv::Size WindowSize);
	        CV_WRAP void updtRotMat(double alpha, double beta, double gamma);
	        CV_WRAP void updtTxMat(double x, double y, double z);
	        void dispAllMat();
	        void updtPts2d(std::vector<cv::Point3d> pts3d);
	        void dispPts2d(cv::Mat &displayWin);
	        CV_WRAP void render(CV_IN_OUT cv::Mat pts3d1,CV_OUT cv::Mat displayWin);
	        void renderFace(std::vector<cv::Point2d> temp_pts2d, cv::Mat displayWin, int idx);
	};

}