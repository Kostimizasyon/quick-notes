# KV Caching

During autoregressive inference, **only the Query (Q) for the newest token needs to be computed**. All previous **Keys (K)** and **Values (V)** are reused from the KV cache.

## Memory Usage (Per Token)

| Method | Cache Size | Notes |
|--------|-----------:|------|
| Raw KV Cache | ~4 MB | Baseline |
| MQA (Multi-Query Attention) | ~32 KB | All heads share the same Keys & Values. Significant performance/quality hit. |
| GQA (Grouped Query Attention) | ~500 KB | Heads are grouped (typically groups of 8). Smaller quality hit than MQA. |
| **MLA (Multi-Head Latent Attention)** | **~70 KB** | Higher performance than raw KV caching, ~6× faster than regular Transformers. Scales with the latent vector size + RoPE dimension, **not** the number of attention heads. |

## MLA (Multi-Head Latent Attention)

**Idea:** Instead of storing full Keys and Values, let the model **learn a compressed latent representation**.

1. Multiply the input by a shared projection matrix (**W<sub>dkv</sub>**) to produce a **compressed latent vector**.
2. This latent vector is then projected into the Key and Value vectors using separate learned weights.

At first glance, this seems pointless because it introduces **another matrix multiplication**, increasing computation when the original bottleneck was memory.

### DeepSeek's Insight

Using linear algebra, the explicit reconstruction of Keys and Values can be eliminated:

- The **Key projection** can be folded into the **Query projection**.
- The **Value projection** can be folded into the **output projection**.

This shortcut avoids reconstructing full Keys and Values altogether, reducing memory usage without introducing extra computational overhead.

**Result:**
- ~70 KB KV cache per token
- Higher performance than raw KV caching
- ~6× faster inference than standard Transformers
- Memory usage scales with the **latent vector size** and **RoPE dimension**, **not** the number of attention heads.

<!--  
KV Caching ( only the new inputs query is needed ) => (deepseek r1) PER TOKEN
4mb raw caching
32kb MQA ( every block uses same keys and queries) (performance of the model hit)
500kb GQA ( every group of blocks uses same keys and queries) ( a little bit less perf hit ) ( group sizes of 8 )
	  
70kbs with perf higher than raw caching ( 6x faster than regular transformers AND better ) scales with the size of the Latent vector + RoPE dimension, DOESNT CARE ABOUT NUMBER OF ATTENTION

	  MLA (multi headed latent attention) What if the model could learn to compress its own key and values? => We multiply our input with a different set of weights Wdkv that is shared like MQA
	  that resulst in a compressed vector of our key values and value vector. Then we multiply them with a new set of weights to produce the Key and Value vectors.
	  However this just introduces a new multplication that just takes more memory, while our whole problem was the usage of memory. Here, the deepseek team realises that with some linear algebra
	  instead we can just multiply our queries with the trained weights for the Wdkv for the key part, and we can just multiply our output with our value weights (trained for the Wdkv vector), resulting
	  in a shortcut.
-->

