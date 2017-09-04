/*******************************************************************************
*
* 版权信息：版权所有 (c) 20XX, 哈尔滨海果智能科技有限公司, 保留所有权利
*
* 文件名称：Higo_SSD_lib.h
* 摘    要：ssd封装的检测接口，该接口负责读取网络和参数等，并对图片进行检测
*
* 当前版本：1.0.0
* 作    者：张天琦，周纪强
* 日    期：2016年12月14日
* 备    注：创建最初版本
*
******************************************************************************/

#ifndef _HIGO_SSD_LIB_H_
#define _HIGO_SSD_LIB_H_

#include <opencv2/opencv.hpp>
#include <iostream>

using std::string;
typedef void *HANDLE;


/******************************************************************************
* 功  能：创建并初始化SSD分类器句柄，读取模型、参数、设置阈值
* 参  数：model_file 	  -I 	网络模型文件deploy.prototxt路径
*              weights_file   -I 	网络参数文件.caffemodel路径
*              threshold       -I 	判断阈值，一般设置为0.6
*              hHANDLE      -O 	SSD检测器句柄地址
* 返回值：无
******************************************************************************/
void SSDDetectInit(HANDLE *hHANDLE,
										const string &model_file,
										const string &weights_file,
										const float threshold = 0.6);

/******************************************************************************
* 功  能：用SSd检测器检测一张图片，输出检测框
* 参  数：hHANDLE 	 -I 	SSD检测器句柄
*             img_src        -I 	待检测的图片（大小不限，内部识别大小，并resize）
*             detections   -O 	检测框，第一维是多个检测框，第二位固定长度为4，为xmin,ymin,xmax,ymax
*             obj_nums    -O     检测到的目标数量，若没有目标则为0
* 返回值：无
******************************************************************************/
void SSDDetect(HANDLE hHANDLE,
											const cv::Mat &img_src,
											std::vector<std::vector<int> >  &detections,
											int &obj_nums);

/******************************************************************************
* 功  能：释放SSD检测器的内存资源
* 参  数：hHANDLE 	 -I 	SSD检测器句柄
* 返回值：无
******************************************************************************/
void SSDDetectUnInit(HANDLE hHANDLE);

#endif
