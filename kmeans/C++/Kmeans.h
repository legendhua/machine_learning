#pragma once
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "data.h"
using namespace std;


/*��ʼ����������
dataset[]����������
K����Ҫ��������
�����ʽΪcluster_data��һά������ʽ������洢���źͶ�Ӧ����������
*/
dataAttrib *InitCentroids(dataAttrib *dataset,int K)
{
	//int data_size = GetArraySize(dataset);//�õ����ݼ������ݵĸ���
	//int data_dim = dataset[0].number;//�õ����ݼ���ÿһ�����ݵ�ά��
	dataAttrib *data_centroids=new dataAttrib[K];//����K���ռ�
	if (data_centroids==NULL)
	{
		cout << "�ڴ����ʧ��" << endl;
		return NULL;
	}

	//��ʼ������Ϊ���ݼ���ǰK�����ݵ�ֵ
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
��ŷ����þ���
*/
double EuclDistance(dataAttrib data,  dataAttrib centroid)
{
	double distance;
	distance = sqrt((data.m_dAttribA - centroid.m_dAttribA)*(data.m_dAttribA - centroid.m_dAttribA) + (data.m_dAttribB - centroid.m_dAttribB)*(data.m_dAttribB - centroid.m_dAttribB));
	return distance;
}

/*Kmeans����������
dataset[]����������
K����Ҫ��������
*/
cluster_data Kmeans(dataAttrib dataset[], int K, int iDataCount)
{
	bool bClusterChanged = true; //����� �����ĸı����
	int iMinIndex = 0;
	cluster_data cluster_result;
	//int iDataCount = GetArraySize(dataset);//�õ�ԭʼ���ݼ������ݵĸ���
    cluster_result.m_pCatagory = new int[iDataCount];//*data_catagory = new int[iDataCount];//����ռ����ڴ�ž��������ҳ�ʼ��
	for (int i=0;i<iDataCount;i++)
	{
		*(cluster_result.m_pCatagory + i) = 0;
		//data_catagory[i] = 0;
	}
	cluster_result.m_pCentroids = new dataAttrib[K];
	//dataAttrib *centroids = new dataAttrib[K];
	cluster_result.m_pCentroids = InitCentroids(dataset, K);//��ʼ����������
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
		//��������
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
	//ɾ����̬����Ŀռ�
	/*delete [] cluster_result.m_pCatagory;
	cluster_result.m_pCatagory = NULL;
	delete[]centroids;
	centroids = NULL;*/
	return cluster_result;
}