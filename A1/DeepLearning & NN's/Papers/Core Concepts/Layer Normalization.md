Published At => 21.07.16 by **Jimmy Lei Ba**, **Jamie Ryan Kiros**, and **Geoffrey E. Hinton**

(Batch norm but on rows instead of columns)
(Batch norm > LN for CNNs but LN is better at like everything else)
(Used for pre activation inputs)

# Layer Normalization

## Abstract

Batch norm good, but depends on mini-batch size. So we transpose the batch norm into layer norm. Unlike batch norm, same computation between training and test times.

## Introduction

Batch norm good, but keeping running variables can be difficuly for RNN's. Also cnat really be used for online learning tasks or really large models where batchsize is small.

*'However, the summed inputs to the recurrent neurons in a recurrent neural network (RNN) often vary with the length of the sequence so applying
batch normalization to RNNs appears to require different statistics for different time-steps.'* 

We propose: Layer Normalization. Unlike batch norm, layer norm directly estimates normalization statistics from the summed inputs to a neuron
in a hidden layer, so the normalization doesnt need to be seperate for training and inference.

## Background

One of the biggest challanges of deep learning, is that one layer is highly dependant to the outputs of the neurons in the previous layer, especially if these outputs are 
highly correlated. Batch norm was proposed to reduce this.Computing the true mean and standard deviation across the entire dataset is computationally impractical for every update, 
so they are estimated using the current mini-batch. Relying on mini-batch estimates places constraints on batch size (requiring batches large enough for stable statistics) and makes this
approach difficult to apply to Recurrent Neural Networks (RNNs)

## Layer Normalization

To reduce covariate shift by fixing the mean and the variance of the summed inputs to a layer. In layer norm we comput the normalization across all hidden units in the layer as follows:

mean_layer = 1/H * Sigma 1->H (a) ||| std_layer = sqrt(1/H * Sigma 1->H square(a - mean_layer)) // Where H is the amount of hidden units in a layer

With layer norm, all the hidden units in a layer share the same normalization terms mean and std, but different training cases have different normalization terms. Unlike batch normalization,
layer normaliztion does not impose any constraint on the size of a mini-batch and it can be used in the pure online regime with batch size 1.

### Layer Normalized RNN's

When we apply batch normalization to an RNN in the obvious way, we need to to compute and store separate statistics for
each time step in a sequence. This is problematic if a test sequence is longer than any of the training sequences. Layer normalization does not have such problem because its 
normalization terms depend only on the summed inputs to a layer at the current time-step. It also has only one set of gain and bias parameters shared over all time-steps.

## Analysis

### Invariance under weights and data transformations

Layer norm is based on batch norm and weight norm, altough μ and σ are calculated differently, these methods can be summarized as normalizing the summed inputs ai to a neruon via our two scalars.
They also learn adaptive bias b and gain g for each neuron after the norm.

hi = f(gi/σi*(ai-μi)+bi) // same formula for batch, layer but for weight μ is 0 and std is ||w|2| ( sigma of w's squares then taking a sqrt)

| | Weight matrix re-scaling | Weight matrix re-centering | Weight vector re-scaling | Dataset re-scaling | Dataset re-centering | Single training case re-scaling |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Batch norm** | Invariant | No | Invariant | Invariant | Invariant | No |
| **Weight norm** | Invariant | No | Invariant | No | No | No |
| **Layer norm** | Invariant | Invariant | No | Invariant | No | Invariant |

** Weight Re-scaling and Centering **  

Under batch and weight normalization, if the weight vector is scaled by δ, the two scalar μ and σ will also be scaled by δ.
So the batch and weight normalization are invariant to the re-scaling of the weights.

Layer normalization, on the other hand, is not invariant to the individual scaling of the single weight vectors. Instead, layer normalization is invariant to
scaling of the entire weight matrix and invariant to a shift to all of the incoming weights in the weight matrix.

** Data Re-scaling and Centering ** 

Layer normalization is invariant to re-scaling of individual training cases, because the normalization scalars μ and σ in Eq. (3) only depend on the current input data.

### Geometry of Parameter Space During Learning

In this section, we analyze learning behavior through the geometry and the manifold of the parameter space, We show that the normalization scalar σ can implicitly reduce learning rate and makes 
learning more stable

1. **Implicit learning rate reduction**: In normalized models, curvature (Fisher info) along the weight vector's direction scales as 1/‖w‖². So as the weight norm grows, updates to its direction automatically 
shrink — a built-in early-stopping/stabilizing effect not present in standard GLMs.

2. **Learning weight magnitude**: With normalization, weight magnitude is controlled by explicit gain parameters. Updates to these gains depend only on the prediction error magnitude — not on input/weight scale — 
making magnitude learning robust to scaling. In standard (unnormalized) models, the equivalent update depends on the input's norm, making it scale-sensitive.

## Conclusion

In this paper, we introduced layer normalization to speed-up the training of neural networks. We provided a theoretical analysis that compared the invariance properties of layer normalization with
batch normalization and weight normalization. We showed that layer normalization is invariant to per training-case feature shifting and scaling. Empirically, we showed that recurrent neural networks
benefit the most from the proposed method especially for long sequences and small mini-batches
