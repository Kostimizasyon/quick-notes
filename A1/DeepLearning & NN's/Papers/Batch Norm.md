Published At => 02.03.05 by **Sergey Ioffe** and **Christian Szegedy**

# Batch Normalization: Accelerating Deep Network Training by Reducing Internal Covariate Shift

## Abstract

NNN training is compicated due to *Internal Covariate Shift*  => The distrbition of each layer's output changing during training
as the parameters of the previous layer changes.

Batchnorm > everything, it lets us be less precise with hyper params.

## Introduction

Our batch's gradient is the estimate of the overall gradient of the set, whose quality improves as the batch size increases, due to paralelism it is much more
efficient to do gradient descent on a smaler batch.
// Bigger batch size, closer to data's gradient itself.

l = F2(F1(inp, p1), p2) if we were to x = F1(inp, p1) then loss = F2(x, p2) then our SGD (sthoic gradient descent)
is exactly the same as a standalone network F2 with an input x

Based on this, we can understand that the same logic for input distribution properties that make training more efficient 

(
training and testing data being from the same distribiton. THe models inputs constantly shift due the the parmas shifting (output of the other layers which causes a shift in vlaue)
these shifts make it so taht the model is harder to train
)

is also true for the sub-network (layers), which means **it is adventegous for x to remain fixed over time**, then p2 doesnt have to readjust.
This x being fixed, also affects other parts of the NN positively, for example lets take a sigmoid layer, z = g(Wu + b), due to the nature of the sigmoid function
as g(x) = 1 / 1 + exp(-x), as x grows, g'(x) gets closer and closer to zero, making this neuron's gradient less and less important causing inefficiencies during training
due to some training being lost on these dead neurons, which gets worse and worse deeper the NN gets.

So we propose: **Batch Normalization**, it reduces ICS via a normalization step that fixes means and variances of inputs. 
Batch Norm also lets our NN be resilient to high (exploding) and low (vanishing) gradients, which lets us use higher LR

## Towards Reducing Internal Covariate Shift

It has been know that NN training converges faster if its inputs are whitened (i.e. linearly transformed to have 0 mean and unit variances). 
Thus it would be adventegaous for each layer's inputs to be fully whitened.

The SGD does not give a shit about normalization and it will work against it.

## Normalization via Mini-Batch Statistics

It would be really expensive to normalize / whiten the entire input set, so we make 2 necesary simplifications: 

1. Independant Normalization
Instead of making the entirety of the input's each feature have the mean 0 and the varience one, we tackle each dimension as their own.

Note that simply normalizing a dimension might change what the layer represents (for example, a sigmoid layer's inputs would now constraint them to the linear part of the nonlinearty)
To adress this we introduce for each activation x, a pair of params gamma and beta where::

gamma = sqrt(var(x)) and beta = mean(x) ::: y = x(normalized) * gamma + b // These parameters are learned alongside original params they start at 1 and 0

2. Batching
Just like how we use mini-batching for SGD, we can also batch our normalization! This way, the statistics used for normalization can fully participate in
the gradient backpropagation

![crem-de-la-cop](https://kratzert.github.io/images/bn_backpass/bn_algorithm.PNG)

Even though the joint distribition of x(norm) can change, it is still a lot faster.
