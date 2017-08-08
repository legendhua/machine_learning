# -*- coding:utf-8 -*-
'''
函数功能：构造房屋面积和房价的线性拟合（一元回归）
给定一些房屋面积和价格的数据，拟合出线性模型
并且给定房屋面积，预测出对应的房价
'''
#需要的包
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn import datasets,linear_model

# 读取数据函数
def get_data(file_name):
     data = pd.read_csv(file_name)
     X_parameter = []
     Y_parameter = []
 #zip函数：接受任意多个（包括0个和1个）序列作为参数，返回一个tuple列表
     for single_square_feet ,single_price_value in zip(data['square_feet'],data['price']):
         X_parameter.append([float(single_square_feet)])
         Y_parameter.append(float(single_price_value))
     return X_parameter,Y_parameter
 
 #线性回归函数
'''
输入：数据X和Y，待预测房价的面积
 
'''
def linear_model_main(X_parameters,Y_parameters,predict_value):
    #构造回归对象 
     regr = linear_model.LinearRegression()
     regr.fit(X_parameters, Y_parameters)
     predict_outcome = regr.predict(predict_value)
     predictions = {}
     predictions['intercept'] = regr.intercept_  #截距的值
     predictions['coefficient'] = regr.coef_      #系数的值
     predictions['predicted_value'] = predict_outcome
     return predictions

#绘制拟合的曲线
def show_linear_line(X_parameters,Y_parameters):
    # 构造回归对象
    regr = linear_model.LinearRegression()
    regr.fit(X_parameters, Y_parameters)
    plt.scatter(X_parameters,Y_parameters,color='blue')
    plt.plot(X_parameters,regr.predict(X_parameters),color='red',linewidth=4)
    plt.xticks(())
    plt.yticks(())
    plt.show()

if __name__=="__main__":
    X,Y = get_data('input_data.csv')  #导入训练数据
    show_linear_line(X,Y)
    predictvalue = float(input("请输入要预测的房屋面积："))   #待预测房价的面积,python3中input返回的值为string型
    result = linear_model_main(X,Y,predictvalue)
    print("截距是：" , result['intercept'])
    print("系数是：" , result['coefficient'])
    print("房子面积为"+str(predictvalue)+"的房价是：",result['predicted_value'])