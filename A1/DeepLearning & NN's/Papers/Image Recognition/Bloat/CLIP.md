[https://openai.com/index/clip/]

A model trained by Open Ai circa 2020, fed both images and captions for those images, the model's aim is to maximise the cosine relevence to the prompt and the image's embedding,
while minimizing the cosine relevence for non related images / captions. It does this by creating a matrix, where images are the columns and captions are the rows, aligning it so that 
the matching pairs are in the middle of the matrix and learning to maxime cosine relevence through this.

Where in the resulting embedding space, directions carry info as in LLM's too.
