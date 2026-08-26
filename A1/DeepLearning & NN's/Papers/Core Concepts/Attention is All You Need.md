Published At => 12.06.17 by Ashish Vaswani, Noam Shazeer, Niki Parmar, Jakob Uszkoreit, Llion Jones, Aidan N. Gomez, Łukasz Kaiser, and Illia Polosukhin

# ATTENTION IS ALL YOU NEED

## Abstact

Instead of the whole RNN bullshit, lets just use Transformers based only on attention.

## Introduction

Recurrent models cannot do paralelization as they are just hidden layer after hidden layer which is a big efficiency loss.
Attention mechanisms became integral, however they are still chained to the recurrent model and their boundaries.
We porpose: **Transformers** a model relying only on attention which allows paralelization like a motherfucker.

## Background

Self attention (infra attention), is an attention mechanism relating different positions of a single sequence in order to compute a representation of the sequence.

## Model Arcitechure

Most competitive neural sequence transduction models have an encoder-decoder structure
Here, the encoder maps an input sequence of symbol representations (x1, ..., xn) to a sequence
of continuous representations z = (z1, ..., zn). Given z, the decoder then generates an output
sequence (y1, ..., ym) of symbols one element at a time. At each step the model is auto-regressive
, consuming the previously generated symbols as additional input when generating the next.

![transformer](https://media.geeksforgeeks.org/wp-content/uploads/20251210153206327851/transformers.webp)

The Transformer follows this overall architecture using stacked self-attention and point-wise, fully
connected layers for both the encoder and decoder, shown in the left and right halves of Figure 1,
respectively.

### Encoder and Decoder Stacks

**Encoder** = The encoder is composed of N=6 indentical layers, each layer has 2 sublayers. The first being a multi-head attention mechanism and the second being a 
simple feed-forward network. We employ a residual connection to each network followed by a layer normalization.

x = LayerNorm(x + Sublayer(x)) // we now do pre norm instead of post norm so :: x = x + Sublayer(Layernorm(x))

**Decoder** = The encoder is composed of N=6 indentical layers, each layer has 3 sublayers. The first being a multi-head attention mechanism and the second being a 
simple feed-forward network. We employ a residual connection to each network followed by a layer normalization, where the third one is another multiheaded attention
that acts over the output from the encoder. We also do masking here. (Past cannot see future)

### Attention

An attention function can be described as mapping a query and a set of key-value pairs to an output,
where the query, keys, values, and output are all vectors. The output is computed as a weighted sum

![Attention](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSHY48TjVeZbySyGQAmqWoegmDM8CKJ509cdL7Q3dIs-IQFTOaKylb7VSXE&s=10)

#### Scaled Dot Product Attention

The input consists of queries and keys of dimension dk and values of dimension dv. We compute the dot product of q @ kT, divide each by sqrt(dk), and apply a softmax to obtain the weights of the vlaues.

Attention(Q, K, V ) = softmax( QKT / √dk)V


Additive attention computes the compatibility function using a feed-forward network with a single hidden layer. While the two are similar in theoretical complexity, dot-product attention is
much faster and more space-efficient in practice, since it can be implemented using highly optimized matrix multiplication code. While for small values of dk the two mechanisms perform similarly,
additive attention outperforms dot product attention without scaling for larger values of dk. We suspect that for large values of dk, the dot products grow large in magnitude,
pushing the softmax function into regions where it has extremely small gradients 4. To counteract this effect, we scale the dot products by 1/√dk

#### MultiHeaded Attention

We found it beneficial to linearly project the queries, keys and values h times with different learned projections to dk, dk and dv respectively. On each of these projected versions, we can execute
the attention function in paralel. These are then concatinated and once again projected.

![formula](https://media.licdn.com/dms/image/v2/D4D12AQGw6RIV4YgDOg/article-cover_image-shrink_720_1280/article-cover_image-shrink_720_1280/0/1691329217886?e=2147483647&v=beta&t=LUYt7_jUybda90NoMuq1VUAFE8Gvhcdy91R2TKkHPSI)

### Position-wise Feed-Forward Networks

In addition to attention sub-layers, each of the layers in our encoder and decoder contains a fully connected feed-forward network, which is applied to each position separately and identically.
This consists of two linear transformations with a ReLU activation in between.

FFN(x) = max(0, xW1 + b1)W2 + b2

### Embeddings and Softmax

We use learned embeddings to convert the input tokens and output tokens to vectors of dimension dmodel. We also use the usual learned linear transformation and
softmax function to convert the decoder output to predicted next-token probabilities. In our model, we share the same weight matrix between the two embedding layers and the pre-softmax
linear transformation. In the embedding layers, we multiply those weights by √dmodel.

### Positional Encoding

Since our model contains no recurrence and no convolution, in order for the model to make use of the order of the sequence, we must inject some information about the relative or absolute position of the
tokens in the sequence. To this end, we add "positional encodings" to the input embeddings at the bottoms of the encoder and decoder stacks. The positional encodings have the same dimension dmodel
as the embeddings, so that the two can be summed.

## Why Self Attention?

Less complex, can do paralel, less sequential operations, less long range between dependencies.

## Conclusion

Transformer good.





