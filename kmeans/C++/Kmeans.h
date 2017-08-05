#pragma once
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "data.h"
using namespace std;


/*初始化聚类重心
dataset[]：输入数据
K：需要聚类的类别
输出格式为cluster_data的一维矩阵形式，里面存储类别号和对应的属性重心
*/
dataAttrib *InitCentroids(dataAttrib *dataset,int K)
{
	//int data_size = GetArraySize(dataset);//得到数据集中数据的个数
	//int data_dim = dataset[0].number;//得到数据集中每一个数据的维度
	dataAttrib *data_centroids=new dataAttrib[K];//申请K个空间
	if (data_centroids==NULL)
	{
		cout << "内存分配失败" << endl;
		return NULL;
	}

	//初始化重心为数据集中前K个数据的值
	for (int i = 0; i < K; i++)
	{
		//data_centroids[i].iCatagory = i;
		(data_centroids + i)->m_dAttribA = (dataset + i)->m_dAttribA;
		(data_centroids + i)->m_dAttribB = (dataset + i)->m_dAttribB;
	}
	/*delete []data_centroids;
	data_centroids = NULL;*/
	return data_centroids;
}

/*
求欧几里得距离
*/
double EuclDistance(dataAttrib data,  dataAttrib centroid)
{
	double distance;
	distance = sqrt((data.m_dAttribA - centroid.m_dAttribA)*(data.m_dAttribA - centroid.m_dAttribA) + (data.m_dAttribB - centroid.m_dAttribB)*(data.m_dAttribB - centroid.m_dAttribB));
	return distance;
}

/*Kmeans聚类主程序
dataset[]：输入数据
K：需要聚类的类别
*/
cluster_data Kmeans(dataAttrib dataset[], int K, int iDataCount)
{
	bool bClusterChanged = true; //定义聚 类中心改变与否
	int iMinIndex = 0;
	cluster_data cluster_result;
	//int iDataCount = GetArraySize(dataset);//得到原始数据集中数据的个数
    cluster_result.m_pCatagory = new int[iDataCount];//*data_catagory = new int[iDataCount];//申请空间用于存放聚类的类别并且初始化
	for (int i=0;i<iDataCount;i++)
	{
		*(cluster_result.m_pCatagory + i) = 0;
		//data_catagory[i] = 0;
	}
	cluster_result.m_pCentroids = new dataAttrib[K];
	//dataAttrib *centroids = new dataAttrib[K];
	cluster_result.m_pCentroids = InitCentroids(dataset, K);//初始化聚类中心
	while (bClusterChanged)
	{
		bClusterChanged = false;
		for (int i = 0; i < iDataCount; i++)
		{
			double dMinDis = 10000.0;
			for (int j = 0; j < K; j++)
			{
				double distance = EuclDistance(dataset[i], cluster_result.m_pCentroids[j]);
				if (distance < dMinDis)
				{
					dMinDis = distance;
					iMinIndex = j;
				}
			}
			if (*(cluster_result.m_pCatagory + i) !=iMinIndex)
			{
				bClusterChanged = true;
				//data_catagory[i] = iMinIndex;
				*(cluster_result.m_pCatagory + i) = iMinIndex;
			}
		}
		//更新重心
		for (int i=0;i<K;i++)
		{
			(cluster_result.m_pCentroids + i)->m_dAttribA = 0;
			(cluster_result.m_pCentroids + i)->m_dAttribB = 0;
		}
		for (int j = 0; j < K; j++)
		{
			int count = 0;
			for (int i = 0; i < iDataCount; i++)
			{
				if (*(cluster_result.m_pCatagory + i) == j)
				{
					count++;
					cluster_result.m_pCentroids[j].m_dAttribA += dataset[i].m_dAttribA;
					cluster_result.m_pCentroids[j].m_dAttribB += dataset[i].m_dAttribB;
				}
			}
			//centroids[j].m_dAttribA = centroids[j].m_dAttribA / count;
			//centroids[j].m_dAttribB = centroids[j].m_dAttribB / count;
			(cluster_result.m_pCentroids+j)->m_dAttribA= cluster_result.m_pCentroids[j].m_dAttribA / count;
			(cluster_result.m_pCentroids + j)->m_dAttribB = cluster_result.m_pCentroids[j].m_dAttribB / count;
		}	
	}
	cout << "Congratulations,cluster complete!" << endl;
	//删除动态申请的空间
	/*delete [] cluster_result.m_pCatagory;
	cluster_result.m_pCatagory = NULL;
	delete[]centroids;
	centroids = NULL;*/
	return cluster_result;
}