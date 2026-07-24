Published At => 02.03.15 by **Sergey Ioffe** and **Christian Szegedy**

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

### Training and Inference with Batch-Normalized Networks

Batch norm behaves differently during training and inference (deployment / evaluation) becacuse during training Batch Norm is done for every mini batch meaning their mean
and variance are calculated fresh from each batch while great in training, this has 2 major flaws in inference:

1. Size = 1 Issue

In some applications of NNs, the input might come one frame at a time and we cant really normalize that

2. Non Deterministic Outputs

If inference depended on batch norm, the outputs would randomly chnage based on which batch has been chosen, making it non deterministic.

#### The solution:

To make the layer deterministic, E[x] and Var[x] are converted to fixed numbers during inference, and these constants are derived from training by taking the 
average of all batch means and variances.

Where we then use the formula:
X(norm) = X - E[X] / sqrt(Var[X] + Epsilon

### Batch-Normalized Convolutional Net-works

z = g(Wu + b), We add the BN right before the non-linearity by normalizing x = Wu + b. And since we normalize Wu + b, taking a mean would render the "+b" part useless, so with BN we can
ignore the bias completely, making our z = g(BN(Wu)) where BN is applied to each dimension of x = Wu seperatly with seperate gamma and beta variables learned for each dimension.

> [!IMPORTANT]
> dont relaly get this part ngl

For convoliton layers, we have a problem : instead of each neuron giving a single activation, but in a conv layer each feature map (channel), produces a whole grid of activations: p x q how do we normalize?

Treat the whole feature map as one thing. m(norm) = m * p * q ( m = all exmaples in batch )

### Batch-Normalization enables Higher Learning Rates

In nn's a too high LR makes some gradients explode and others to vanish, batch norm helps this as it is normalizing activations it helps the NN become resilient to too high and low gradients 
Batch norm stabilizes the parameter growth. We actually dont know what exactly it does on gradient propogation, but its positive.

### Batch-Normalization regularizes the model

Dropout where it is used to reduce overfitting, in a batch normalized framework it can either be removed entirely or reduced.

## Experiments

### Activations over Time

Batch norm helps the usual 28x28 handwritten digit recognition to slightly improve its loss, but the bigger impact being that it helps the model iron out the first errors of distribiton of activations
a lot faster in a lot fewer steps, which might just be the reason for the loss improvement.
Where it also helps the model have less swingy outputs leading to better neuron activations.

### ImageNet Classification

It better with bathc nor but we gotta do:

1. Increase LR
2. Remove dropout
3. Reduce L2 weight reg
4. Accelerate learning rate decay
5. Remove Local Response Norm
6. Shuffle training more thorougly
7. Reduce photometric distortions

## Conclusion

It good and only adds 2 extra params.


## Related:

[Batch Renormalization](https://github.com/Kostimizasyon/quick-notes/blob/master/A1/DeepLearning%20%26%20NN's/Papers/Batchrenormalization.md)
