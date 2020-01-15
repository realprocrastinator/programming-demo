
#compute confidence given x and guassian distribution
from math import *
def conf(mu, sigma2, x):
    return 1/sqrt(2.*pi*sigma2)*exp(-.5*(x -mu)**2/sigma2)

#given the prior prob distribution and measurment distribution compute
#the posteria distribution mean and variance
def update(mean1, var1, mean2, var2):
    new_mean = (var1*mean1 + var2*mean2)/(var1 + var2)
    new_var = 1/(1/var1 + 1/var2)
    return [new_mean, new_var]

#given the posteria disribution and the move noise distribution
#calculate predict distribution after move
def predict(mean1, var1, mean2, var2):
    new_mean = mean1 + mean2
    new_var = var1 + var2
    return [new_mean, new_var]

#implementtation of kalmen filtering
measurements = [5., 6., 7., 9., 10.] #the measurments mean
motion = [1., 1., 2., 1., 1.]
measurement_sig = 4. #measurment variance P(zi|X)
motion_sig = 2.      
mu = 0.             #prior distribution mean
sig = 10000.        #prior distribution variance

for n in range(len(measurment)):
    [mu, sig] = update(mu,sig,measurments[n],measurement_sig) #update to posterior distribution
    print("update: ",[mu,sig])
    [mu, sig] = predict(mu, sig, motion[n], motion_sig)
    print("predicts: ",[mu,sig])


#multi dim kalmen filter
def kalmen_filter(x,P):
    Z = matrix([[measurements]])
    y = Z - (H*x)
    S = H*P*H.transpose() + R #how correlated with is the meseaurement with the hidden variance 
    K = P*H.transpose()*S.inverse()
    x = x_ (K*y)
    P = (I - K*H)*P

    #prediction
    x = (F * x) + u
    P = F*P*F.transpose()






measurements = [1, 2, 3]

x = matrix([[0.], [0.]]) # initial state (location and velocity)
P = matrix([[1000., 0.], [0., 1000.]]) # initial uncertainty
u = matrix([[0.], [0.]]) # external motion
F = matrix([[1., 1.], [0, 1.]]) # next state function
H = matrix([[1., 0.]]) # measurement function
R = matrix([[1.]]) # measurement uncertainty
I = matrix([[1., 0.], [0., 1.]]) # identity matrix

print(kalman_filter(x, P))
# output should be:
# x: [[3.9996664447958645], [0.9999998335552873]]
# P: [[2.3318904241194827, 0.9991676099921091], [0.9991676099921067, 0.49950058263974184]]


