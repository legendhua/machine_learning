#include <stdlib.h>
#include "data.h"
#include "Kmeans.h"
#include <iostream>
using namespace std;


int main(void)
{
	dataAttrib MyDataset[12] = { dataAttrib(12,11.0),
							   dataAttrib(3,6),
							   dataAttrib(6,6),
							   dataAttrib(7,12),
							   dataAttrib(5,8),
							   dataAttrib(23,32),
							   dataAttrib(4,3),
							   dataAttrib(12,14),
							   dataAttrib(34,23),
							   dataAttrib(16,28),
							   dataAttrib(2,6),
							   dataAttrib(3,5) };
	int count = sizeof(MyDataset) / sizeof(MyDataset[0]);//数据集中数据的个数
	int K = 4;
	cluster_data result;
	result = Kmeans(MyDataset, K,count);
	for (int j=0;j<K;j++)
	{
		cout << "第" << j<< "类数据包括："<<endl;
		for (int i=0;i<count;i++)
		{
			if (*(result.m_pCatagory+i)==j)
			{
				cout << "(" << MyDataset[i].m_dAttribA << "," << MyDataset[i].m_dAttribB << ")" << endl;
			}
		}
		cout << "聚类中心为：";
		cout << "(" << (result.m_pCentroids+j)->m_dAttribA << "," << (result.m_pCentroids + j)->m_dAttribB << ")" << endl;
	}
	return 0;
}