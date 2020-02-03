#include"utils.hpp"

namespace kos
{
	imgMap::imgMap()
	{   
	    // this-> aperture = 340;
	    this-> Hd = 400;
	    this-> Wd = (this->Hd)*2;
	}

	Obj3D::Obj3D(cv::Size WindowSize)
	{   
	    this->WindowSize = WindowSize;
	    this->update3dpts(WindowSize.height,0);
	}

	void Obj3D::update3dpts(double s, double squz)
	{
	    /* This function can be called when we want to update 
	    *  the value of 3D points with change in s or squz.
	    *  param@ s: Side of the square
	    *  param@ squz: Reduction in length of cube along z axis.
	    */
	   s = s*0.2;
	   this->pts3d.clear();
	   this->pts3d.push_back(cv::Point3d(-s,s,s-squz));
	   this->pts3d.push_back(cv::Point3d(s,s,s-squz));
	   this->pts3d.push_back(cv::Point3d(s,-s,s-squz));
	   this->pts3d.push_back(cv::Point3d(-s,-s,s-squz));
	   this->pts3d.push_back(cv::Point3d(-s,s,-s+squz));
	   this->pts3d.push_back(cv::Point3d(s,s,-s+squz));
	   this->pts3d.push_back(cv::Point3d(s,-s,-s+squz));
	   this->pts3d.push_back(cv::Point3d(-s,-s,-s+squz));

	   this->ori_pts3d.clear();
	   this->ori_pts3d.push_back(cv::Point3d(-s,s,s-squz));
	   this->ori_pts3d.push_back(cv::Point3d(s,s,s-squz));
	   this->ori_pts3d.push_back(cv::Point3d(s,-s,s-squz));
	   this->ori_pts3d.push_back(cv::Point3d(-s,-s,s-squz));
	   this->ori_pts3d.push_back(cv::Point3d(-s,s,-s+squz));
	   this->ori_pts3d.push_back(cv::Point3d(s,s,-s+squz));
	   this->ori_pts3d.push_back(cv::Point3d(s,-s,-s+squz));
	   this->ori_pts3d.push_back(cv::Point3d(-s,-s,-s+squz));
	}

	void Obj3D::print3dpts()
	{
	    /* This function simply loops over all 3D points 
	    *  and prints it.
	    */

	   for(size_t i{0}; i < this->pts3d.size();i++)
	   {
	       std::cout << this->pts3d.at(i) << std::endl;
	   }
	   std::cout << "\nDone !";
	}

	void Obj3D::rotateObj(double alpha, double beta, double gamma)
	{
		// cv::Mat Rx = (cv::Mat_<double>(3,3) << 1,0,0,0,cos(alpha),-1*sin(alpha),0,sin(alpha),cos(alpha));
		// cv::Mat Ry = (cv::Mat_<double>(3,3) << cos(beta),0,-1*sin(beta),0,1,0,sin(beta),0,cos(beta));
		// cv::Mat Rz = (cv::Mat_<double>(3,3) << cos(gamma),-1*sin(gamma),0,sin(gamma),cos(gamma),0,0,0,1);
	  cv::Mat Rx = (cv::Mat_<double>(3,3) << 1,0,0,0,cos(alpha),sin(alpha),0,-sin(alpha),cos(alpha));
	  cv::Mat Ry = (cv::Mat_<double>(3,3) << cos(beta),0,-1*sin(beta),0,1,0,sin(beta),0,cos(beta));
	  cv::Mat Rz = (cv::Mat_<double>(3,3) << cos(gamma),sin(gamma),0,-sin(gamma),cos(gamma),0,0,0,1);
		cv::Mat rotVec;
		rotVec = Rz*Ry*Rx;

		for(int i{0}; i<this->pts3d.size();i++)
		{
			this->pts3d[i].x = this->ori_pts3d[i].x*rotVec.at<double>(0,0) + this->ori_pts3d[i].y*rotVec.at<double>(0,1) + this->ori_pts3d[i].z*rotVec.at<double>(0,2);
			this->pts3d[i].y = this->ori_pts3d[i].x*rotVec.at<double>(1,0) + this->ori_pts3d[i].y*rotVec.at<double>(1,1) + this->ori_pts3d[i].z*rotVec.at<double>(1,2);
			this->pts3d[i].z = this->ori_pts3d[i].x*rotVec.at<double>(2,0) + this->ori_pts3d[i].y*rotVec.at<double>(2,1) + this->ori_pts3d[i].z*rotVec.at<double>(2,2);
		}
	}

	vcam::vcam(cv::Size WindowSize)
	{   
	    this->WindowSize = WindowSize;
	    this->focal_length = WindowSize.width;
	    this->center = cv::Point2d(WindowSize.width/2, WindowSize.height/2);
	    //NOTE : Camera matrix will not change once defined
	    this->cameraMatrix = (cv::Mat_<double>(3,3) << this->focal_length, 0, this->center.x, 0 , -1*this->focal_length, this->center.y, 0, 0, 1);
	    this->distCoeff = cv::Mat::zeros(4,1,cv::DataType<double>::type);
	    this->updtRotMat(0,0,0);
	    this->updtTxMat(0,500,this->focal_length);    
	}

	void vcam::updtRotMat(double alpha, double beta, double gamma)
	{	
		cv::Mat Rx = (cv::Mat_<double>(3,3) << 1,0,0,0,cos(alpha),-1*sin(alpha),0,sin(alpha),cos(alpha));
		cv::Mat Ry = (cv::Mat_<double>(3,3) << cos(beta),0,-1*sin(beta),0,1,0,sin(beta),0,cos(beta));
		cv::Mat Rz = (cv::Mat_<double>(3,3) << cos(gamma),-1*sin(gamma),0,sin(gamma),cos(gamma),0,0,0,1);

		this->rotVec = Rz*Ry*Rx;
	}

	void vcam::updtTxMat(double x, double y, double z)
	{
		this->txVec = (cv::Mat_<double>(1,3) << x,y,z);
	}

	void vcam::dispAllMat()
	{
		std::cout << "\nDisplaying all the matrices " << std::endl;

		std::cout << "######### Camera Matrix ##########" << std::endl;
		std::cout << this->cameraMatrix << std::endl;

		std::cout << "\n############ Overall rotation matrix ##########" << std::endl;
		std::cout << this->rotVec;

		std::cout << "########### Overall translation matri ##########" << std::endl;
		std::cout << this->txVec;
	}

	void vcam::updtPts2d(std::vector<cv::Point3d> pts3d)
	{
		cv::projectPoints(pts3d, this->rotVec, this->txVec, this->cameraMatrix, this->distCoeff, this->pts2d);
	}

	void vcam::dispPts2d(cv::Mat &displayWin)
	{	
		displayWin=0;
		for(size_t i{0};i<this->pts2d.size();i++)
			cv::circle(displayWin,this->pts2d[i],2,cv::Scalar(0,255,0));
		cv::imshow("Viewer",displayWin);
		// NOTE : Apply waitKey in the main loop
	}

	void vcam::render(cv::Mat pts3d1, cv::Mat displayWin)
	{
		std::vector<cv::Point3d> pts3d;
		for(size_t i{0};i<pts3d1.rows;i++)
		{
			pts3d.push_back(cv::Point3d(pts3d1.at<double>(i,0),pts3d1.at<double>(i,1),pts3d1.at<double>(i,2)));
		}

		// std::cout << "Details \nshape : " << pts3d1.rows << "," << pts3d1.cols; 
		// exit(0);

		// for(int i{0}; i < pts3d.size();i++)
		// 	std::cout << pts3d[i].x << "," << pts3d[i].y << "," << pts3d[i].z << std::endl;
		// exit(0);
		// cubeFaceIdx each row represents a face with indices to points making that face respectively
		int cubeFaceIdx[6][4] = {{0,1,2,3},{1,5,6,2},{5,4,7,6},{4,0,3,7},{4,5,1,0},{7,6,2,3}};
		// faceCenter is vector of points containing center of each face
		std::vector<cv::Point3d> faceCenter;

		cv::Mat mean_dist;

		// Creating a matrix. We later update the matrix to store absolute distance
		mean_dist = (cv::Mat_<double>(1,6) << 0,0,0,0,0,0);

		// Initializing some points for intermediate calculations
		std::vector<cv::Point3d> mean;
		std::vector<cv::Point3d> temp_face;

		/* We loop through each face 
		 * find the center point for each face
		 * find the mean distance of the face from the camera
		*/
		for(size_t i{0};i<6;i++)
		{
			temp_face.clear();
			for(size_t j{0}; j<4; j++)
			{
				temp_face.push_back(pts3d[cubeFaceIdx[i][j]]);			
			}
			cv::reduce(temp_face,mean,1,CV_REDUCE_AVG);		
			// mean_dist.at<double>(0,i) = abs(mean[0].x-this->txVec.at<double>(0,0)) + abs(mean[0].y-this->txVec.at<double>(0,1)) + abs(mean[0].z-this->txVec.at<double>(0,2));
			mean_dist.at<double>(0,i) = sqrt(pow((mean[0].x-this->txVec.at<double>(0,0)),2) + pow((mean[0].y-this->txVec.at<double>(0,1)),2) + pow((mean[0].z-this->txVec.at<double>(0,2)),2));
			// std::cout << "face mean : and camer coordinates\n"; 
			// std::cout << mean[0].x << " , " << this->txVec.at<double>(0,0) << std::endl;
			// std::cout << mean[0].y << " , " << this->txVec.at<double>(0,1) << std::endl;
			// std::cout << mean[0].z << " , " << this->txVec.at<double>(0,2) << std::endl;
		}

		// std::cout << std::endl << mean_dist << std::endl;
		// std::cout << "And the camera vector is \n";
		// std::cout << this->txVec.at<double>(0,0) << " , "<< this->txVec.at<double>(0,1) << " , "<< this->txVec.at<double>(0,2) << " , "<<std::endl; 
		
		// Storing the sorted index for mean_distance values in idx matrix
		cv::Mat idx;
		cv::sortIdx(mean_dist,idx,CV_SORT_DESCENDING);
		// std::cout << "\nindexes : " << idx;

		// Now we have sorted the faces based on their mean distance from the camera
		// Using these indices and cubeFaceIdx we find respective projections
		std::vector<cv::Point2d> temp_pts2d;
		displayWin = displayWin*0;
		for(int i{5}; i>(-1); i--)
		{	
			// if (i!=0)
			// 	continue;
			temp_face.clear();
			temp_pts2d.clear();
			for(int j{0}; j<4; j++)
			{
				// std::cout << idx.at<int>(0,i) << std::endl;
				// std::cout << i << std::endl;
				temp_face.push_back(pts3d[cubeFaceIdx[idx.at<int>(0,i)][j]]);			
			}

			cv::projectPoints(temp_face, this->rotVec, this->txVec, this->cameraMatrix, this->distCoeff, temp_pts2d);
			this->renderFace(temp_pts2d, displayWin,idx.at<int>(0,i));
			// std::cout << "inside for \n";
		}
		cv::imshow("output",displayWin);
		cv::waitKey(1);

	}

	void vcam::renderFace(std::vector<cv::Point2d> temp_pts2d, cv::Mat displayWin,int idx)
	{
		std::vector<cv::Mat> imgVec;
		cv::Mat img1,imgTemp;

		if(idx==0)
		{
			imgTemp = cv::imread("../img1.jpeg");
			cv::resize(imgTemp,img1,cv::Size(displayWin.rows, displayWin.cols));
		}

		if(idx==1)
		{
			imgTemp = cv::imread("../img2.jpeg");
			cv::resize(imgTemp,img1,cv::Size(displayWin.rows, displayWin.cols));
		}

		if(idx==2)
		{
			imgTemp = cv::imread("../img3.jpeg");
			cv::resize(imgTemp,img1,cv::Size(displayWin.rows, displayWin.cols));
		}

		if(idx==3)
		{
			imgTemp = cv::imread("../img4.jpeg");
			cv::resize(imgTemp,img1,cv::Size(displayWin.rows, displayWin.cols));
		}

		if(idx==4)
		{
			imgTemp = cv::imread("../img5.jpeg");
			cv::resize(imgTemp,img1,cv::Size(displayWin.rows, displayWin.cols));
			cv::flip(img1,img1,0);
		}

		if(idx==5)
		{
			imgTemp = cv::imread("../img6.jpg");
			cv::resize(imgTemp,img1,cv::Size(displayWin.rows, displayWin.cols));
			cv::flip(img1,img1,0);
		}


		cv::Point2f src[4];
		cv::Point2f dst[4];

		cv::Mat output = cv::Mat::zeros(img1.rows, img1.cols, img1.type());
		cv::Mat output_mask = cv::Mat::zeros(img1.rows, img1.cols, CV_8UC1);

		src[0] = cv::Point2f(0,0);
		src[1] = cv::Point2f(img1.cols,0);
		src[2] = cv::Point2f(img1.cols, img1.rows);
		src[3] = cv::Point2f(0, img1.rows);

		for(int i{0}; i<4; i++)
			dst[i] = cv::Point2f(float(temp_pts2d[i].x),float(temp_pts2d[i].y));

		cv::Mat M;
		M = cv::getPerspectiveTransform(src,dst);
		cv::warpPerspective(img1,output,M,output.size());
		cv::cvtColor(output, output_mask, CV_BGR2GRAY);

		output.copyTo(displayWin, output_mask);
	}

}