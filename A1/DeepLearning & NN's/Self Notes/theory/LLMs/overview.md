# N gram models

N gram models are jsut models that take N as a context size use that as an input, then try to guess the next word

# RNN (Recurrent Neural Networks)

## NN's ( Neural Networks )

Embeddings, weights, biases , activations you know the drill.

## RNN's

Think of it in cells, we have a RNN cell => that takes in an input x and gives an output y. Where the input goes through a hidden state, where
this hidden state is sourced by the previous cell. Ex::

           yt
        
        |_____|
ht-1 => |     | => ht, where ht = act(Wht-1 + Vxt + bh), where then yt = Act(Uht + by)
        |     |
        |_____|
            
          xt

Now, we can recursively add our input! So unlike a n-gram, both the move is great , the great move is  are processed the same

CONS: Sequencial, extremely slow and compute heavy. They are inefficient to train, as for example for training a 4 word sequence, we would need to update the weights for the 3rd 2nd and 1st matrix accordingly, which
means that if our context size is quite large, then our updates might not reach a far away word. (Vanishing gradients)

## LSTM 

# ATTENTION

Originally meant to improve RNN's birthed transformers and killed RNN's

## Machine Translation

Encoders => encode the words meaning to vectors.

Decorders => decode the vectors to a translated language.

RNN's this is kind of a problem, as the last cell in each structure would hold A LOT of data, and is a bottleneck.

To solve this:

## Attention

To avoid bottlenecks, we can just make the encoders talk to the decoders and communicate with them.

How we do this is simple:

Example: We select a decoder S, and we have 4 encoders h1..4, we calcualte the dot product of s and h1..4, to see which hidden state S is most like, which results in which hidden state S is most likely to attend to
