Published At => 30.03.17 by **Sergey Ioffe** 

# Batch Renormalization: Towards Reducing Minibatch Dependence in Batch-Normalized Models

## Abstract

Batch norm is fucking great, but it suffers when batch sizes are small or batch contains non-independant samples, we propose: **Batch Renormalization** a simple and effective
exenstion that ensures the training and inference models generate the same outputs that depond on individual examples rather than a minibatch. Models trained with batch renorm
out class models trained with bnorm when training with smal or non-i.i.d minibatches while retaining all the good stuff from batchnorm.

## Introduction

It is clear that normalized activactions corresponding to an input example will depend on the other examples in the minibatch, which is undesirable for inference, therefore the
mean calculated over all training data is used instead.

While it makes sense to do this, this changes activations in the network. In particular this means the upper layers(who's inputs are normalized via minibatch), are trained on
representations different from those in computed inference (where inputs are normalized by means calculated during training). When the minibatch size is large, and its elements 
are i.i.d (independant and identically distrubited), the difference is minimal and can aid generelization.

However:

1. For small batches:
The estimate for mean and variance becomes less accurate, these inaccurasies are compounded with depth and reduce the quality of the resulting models.

2. For non-i.i.d batches:
This can have a detremental effect on the model, Ex: in metric learning (training embedding with +/- pairs). Here without batch norm no gradient can effect others so its fine.
But with batchnorm this independance breaks, and ruins the model.

The dependence of batch-normalized activations on the entire minibatch makes the BN method powerful but also introduces its drawbacks.

We propose **Batch Renormalization**, a new extension to batchnorm. This method ensures that the activations computed in the forward pass of the training step
depend only on a single example and are identical to the activations computed in inference. This significantly improves the training on non-i.i.d. or small minibatches,
compared to batchnorm, without incurring extra cost

## Prior Work: BatchNorm

We want batchnorm to rely less on the batch, so a proposition is to use our running variance and running mean to train the model aswell, however this blows the model up.

## Batch Renormalization

With batchnorm, activities in the network differ in training and inference, we aim to rectify this while retaning the benefits of batchnorm.

We have: x - mean / s.d. ==> x - meanB / s.d.B * r + d where r = s.d.B/ s.d. , d = meanB - mean / s.d.

if mean = Mean(meanB) and s.d. = mean(s.d.B) then E[r] = 1, E[d] = 0. Let us retain r and d and treat them as constants. So our NN would be batchnorm then a batchrenorm

#### Formula

    xnorm = ( x - meanB / sdB ) * r + d

##### Inference:
    ynorm = gamma * ( x - mean / sd ) + beta

# Batch Renorm didnt really see adoption so after this part I aint covering it ngl

    Batch renorm didnt really get adapted because the issue it tackles isnt that common and it introduces a new layer and params that slow the model down a bit without
    too much of a gain.

## Related:
[Batch Normalization](https://github.com/Kostimizasyon/quick-notes/blob/master/A1/DeepLearning%20%26%20NN's/Papers/Batch%20Norm.md)
