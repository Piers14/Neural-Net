# Neural-Net
 
An artificial neural network class.

matrix.h: Matrix class which makes linear algebra easier.
NormalGenerator.h: Random number generator class, used for initialisation of weights matrix.

activation_functon.h: Abstract class of activation functions. Relu class inherits - implements (leaky) ReLu function.

loss_function.h: Abstract class of loss functions. Quadratic_loss class inherits.

A neural_net object requires an activation function, a loss function and a structure vector to instantiate. The neural network learns via stochastic gradient descent.

An example is included in driver.cpp
