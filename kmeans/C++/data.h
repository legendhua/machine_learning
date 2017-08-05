#pragma once

//定义数据属性的类，包含两个属性
class dataAttrib
{
public:
	dataAttrib()
	{}
	dataAttrib(double attribA,double attribB):m_dAttribA(attribA),m_dAttribB(attribB)
	{}
	virtual ~dataAttrib()
	{}
public:
	double m_dAttribA;
	double m_dAttribB;
};

class cluster_data
{
public:
	cluster_data(int * catagory = NULL,dataAttrib * centroid =NULL)
	{
		m_pCatagory = catagory;
		m_pCentroids = centroid;
	}
	~cluster_data()
	{
	}

public:
	int *m_pCatagory;
	dataAttrib *m_pCentroids;
};
