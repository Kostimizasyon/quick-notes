Published At => 10.12.15 by **Kaiming He**, **Xiangyu Zhang**, **Shaoqing Ren** and **Jian Sun**

# Deep Residual Learning for Image Recognition

## Abstract

Instead of training networks on the outputs of x => H(x) where the model normally just learns H(x) where H is the desired mapping. We can do this in a referenced input way
where instead, we make hte model learn the DIFFERENCE between our activations, so F(x) = H(x) - x, the model learns F(X). Which lets us depeen our
networks a lot easier as we will do A lot less processing and spend less compute.

## Introduction

The recent evidence showed that the deeper a model is the better the potential it has, earlier deepining a NN would result in exploding gradients, however
this issue has been mostly tackled by normalization.

However, still when deeper NN's are able to converge, a degradation problem happens. Where the model's accuracy gets saturated then it starts degrading rapidly.
However, this is NOT caused by overfitting, and adding more layers can result in higher training error. Which mean that not all systems are easy to optimize through normalization.

In this paper we adress this degradign issue with a *deep residual learning framework*. Where we let the stacked nonlinear layers fit the mapping of : F(x) = H(x) - x. The original
mapping is then cast into F(x) + x

![Resnet (Fig 2)](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT52wojcVGlNQLFu9rcURaz6G_-ZlqF_Wgs4ZMPKF3EHg&s=10)

It is easier to optimize the residual mapping rather than the original mapping.

Shortcut connections are those skipping one or more layers. In our case, the shortcut connections simply perform identity mapping, and their outputs are added to
the outputs of the stacked layers

## Deep Residual Learning

### Residual Learning

H(x) is the underlying mapping of a few stacked layers, we can asymptotically aproximate the residual functions => H(x) - x. So rather than making the layers
aproximate H(x), we let them aproximate a residual function, F(X) = H(X) - X. The original function thus becomes F(X) + X

### Indentity Mapping by Shortcuts

We adopt Res Learning to every few stacked layers and get the block: y = F{x{Wi}} + x, where biases are ommited after some normalizations. For example our fig 2 example:

F = W2σ(W1x), where σ denotes ReLU, the operation F + x is performed by a shortcut connection that does not introduce any new parameters or anything. But for the F + x
operation they need to be the same dimensoions, if they are not we can perform a linear projection via Ws. ::: y = F{x, {Wi}}  + Wsx

The form of the funciton F is flexible, but when it is 1 layer it does not provide any benefits. (2 - 3 for this paper)

### Bottleneck Structure

Used in deeper ResNets (50/101/152) instead of the plain 2-layer 3x3 block.

Structure: 1x1 → 3x3 → 1x1 conv, instead of two 3x3 convs.

1x1 (reduce): shrinks channel depth (e.g. 256 → 64)
3x3: does the actual spatial conv, but now on fewer channels — cheaper
1x1 (expand): restores depth back (64 → 256) before adding the shortcut

## Experiments

This practice very good.

# After Paper

After this paper, it has been noticed that one of the reasosn the ResNEt is so efficient, is taht the gradient flow is really good:

F(x) + x if we were to backprop this, it is  Derv_x(F) + 1, no matter how small the partial derv of F is, there is still a 1 contributing to the gradients.
