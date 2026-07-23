# Chapter 1

## Artificial Neurons

### Perceptrons 

takes several inputs, returns a single binary output:
    
Rosenbalt proposed a simple way to compute its output => weights (importance of each input), and he proposed
that the weighted sum **∑jwjxj** is less than or greater than a threshold value.

We can think of them as a device to make a yes/no desicion by weighing up evidence


::

X inputs => 3 perceptrons, they gauge given inputs and feed their findings to 4 other perceptrons which then feed their findings to
one final output.

why do we have the other 4? since the first 3 gauged inputs and came to new conclusions, the new 4 will then ponder on these conclusions and be able to tackle more complex questions
and coem to a conclusion

![img](http://neuralnetworksanddeeplearning.com/images/tikz1.png)

a perceptron is === w * x + b

::

Perceptrons can basically act as NAND gates, so we can use perceptrons to compute simple logical functions

Inputs are called "input perceptrons", but they actually arent really perceptrons at all

### Sigmoid Neurons

For an act like classifying digits, to optimize our weights and biases would nudge the input in one direction and as perceptrons are binary output while we might classify the current  
input correctly, we could totally flip on other inputs, to solve this we use:

A sigmoid neuron, takes inputs same way as a perceptron but instead of 0 or 1 it gives an output between 0 and 1

σ(w⋅x+b) is our output where σ is our sigmoid function :: 1 * (1 + e**x)**-1

So to understand the similarity of the perceptron and the sigmoid, we need to view: z = w * x + b
when this gets fed into a sigmoid function, if z were to be a large psotiive number, then our output from the sigmoid would be 1
now supose that z is a really small negative number, then our output would be 0, making it really close to a perceptron at really big and small values

But the crucial part of a sigmoid is the activation, it being smoothed out by the function. This smoothness means that any change in weights and the bias, will effect our output

## Architecture of NNN

!(http://neuralnetworksanddeeplearning.com/images/tikz11.png)

Hidden is litterally called that just cuz its neither an input or output

### The Design of Input and Output
They are realy simple actually, for example, making a NNN taht will gauge if the given 64x64 image is a 9 or not. The input layer would be just each pixel in the image
so 64*64 = 4096 input neurons, and the output layer would be just 1 neuron, where if the output is >0.5, its a 9

*Side note, while we have been just seeing NN's where output from one layer is fed as the input for the next (feedforward NNN's), there exists NNN's where they can make loops 
[reccurrent neural networks](https://en.wikipedia.org/wiki/Recurrent_neural_network)*

While, input and output is quite easy. The hidden layers involve some deep theory where there arent just some few rules of thumb, researchers developed
many heuristics for hidden layers, where some trade off the number of hidden layers for less training for example.

### Building A Digit Recognizer

![img](http://neuralnetworksanddeeplearning.com/images/tikz12.png)

#### Arcitechure
784 (28*28) input neurons, that have been greyscaled as preprocessing.
2nd layer is our hidden layer with n=15 (well be experimenting with this n)
And our output is 10 neurons for each digit, where each output shows how closely that number was to the model, here instead of 10 neurons
we could have used 4 neurons that represent binary, this would have been sufficient as 2**4 == 16, but for this model 10 neurons just performed better

#### Why?


## Learning with Gradient Descent

Why introduce the quadratic cost? After all, aren't we primarily interested in the number of images correctly classified by the network? Why not try to maximize that number directly, rather than minimizing a proxy measure like the quadratic cost? The problem with that is that the number of images correctly classified is not a smooth function of the weights and biases in the network. For the most part, making small changes to the weights and biases won't cause any change at all in the number of training images classified correctly. That makes it difficult to figure out how to change the weights and biases to get improved performance. If we instead use a smooth cost function like the quadratic cost it turns out to be easy to figure out how to make small changes in the weights and biases so as to get an improvement in the cost. That's why we focus first on minimizing the quadratic cost, and only after that will we examine the classification accuracy.

## Implementing our NNNN



