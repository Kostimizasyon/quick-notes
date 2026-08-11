# Diffusion Models & Prompt Conditioning

> **Where were the Transformers?**
>
> Early diffusion models (DDPM, DDIM, etc.) used **U-Nets** as the denoising network. Transformer-based diffusion models (DiT, MMDiT, FLUX, SD3, etc.) came later.

---

# DDPM (Denoising Diffusion Probabilistic Models)

> **Main drawback:** Sampling is slow because it requires hundreds or thousands of denoising steps.

## Training

1. Take a clean image.
2. Gradually add Gaussian noise until it becomes almost pure noise.
3. Randomly sample a timestep `t`.
4. Give the noisy image and timestep to the model:

```
f(x, t)
```

where:
- `x` = noisy image
- `t` = diffusion timestep

The model predicts the **total noise** added to the image rather than only the previous denoising step.

### Why predict the total noise?

Many noisy trajectories pass through similar intermediate states, making the overall noise easier to estimate than predicting each tiny reverse step.

The timestep tells the model **how noisy** the current image is.

---

## Sampling (Inference)

1. Start from pure Gaussian noise.
2. Predict the noise.
3. Remove part of the predicted noise.
4. Repeat until a clean image is obtained.

```
Noise
  ↓
Predict Noise
  ↓
Remove Noise
  ↓
Repeat...
  ↓
Image
```

Although we're denoising, **random noise is still injected at every reverse step**.

Without this stochasticity, trajectories collapse toward the mean of the data distribution (e.g., the center of the Welsh Lab spiral), producing blurry average images. Injecting noise keeps trajectories diverse and allows the model to sample different valid images.

---

# DDIM (Denoising Diffusion Implicit Models)

## Training

Exactly the same as DDPM.

## Sampling

DDIM derives a deterministic reverse process that produces nearly the same results **without adding random noise** at every step.

This makes inference:
- Faster
- Deterministic (given the same starting noise)
- Require far fewer denoising steps

---

# Prompt Conditioning

During training, the text prompt is embedded and injected into the denoising network (typically through **cross-attention**) so the model can condition image generation on the prompt.

Instead of only predicting

```
f(x, t)
```

the model predicts

```
f(x, t, prompt)
```

where the prompt embedding guides the denoising process toward the desired image.

---

# Classifier-Free Guidance (CFG)

Simply conditioning on a prompt isn't always enough—the model may prioritize matching the overall data distribution rather than following the prompt.

To solve this, the model is trained in two modes:

- **Conditional:** `f(x, t, prompt)`
- **Unconditional:** `f(x, t, ∅)`

The difference

```
f(x,t,prompt) - f(x,t,∅)
```

represents the direction that moves the prediction toward the prompt.

This direction is amplified using the **guidance scale** (`α`):

```
f(x,t,∅) + α(f(x,t,prompt) - f(x,t,∅))
```

Higher guidance scales make the model follow the prompt more strongly.

---

# Negative Prompts

Modern diffusion and video generation models (e.g., **Wan 2.1**) often support **negative prompts**.

Instead of only specifying what should appear, you also specify what **should not** appear.

Conceptually, the model follows the direction

```
Positive Prompt − Negative Prompt
```

which encourages desired features while suppressing unwanted ones.

---

<!-- ========================================================= -->

# Original Notes

```text
Diffisiuon Models => {

    where the fuck were the transformers i forgor claude

    DDPM {

            REQUIRE SO MUCH FUCKING COMPUTE FOR ADDING NOISE

            TRAINING {

                    Take image, add noise | repeat till image is fucked. Make model guess the total noise added to the image.

                    Cuz : its more efficient as a lot of points will go through a certain point makign it easier for the model to guess where they originated from rather then
                    what was the latest step they have taken (simplified a lot) ( E[x99 - x100 | x100 ] == E[x0 - x100 | x100] / 100 )

                    f(x, t=1.00) // let the model know what step its on

            }

            Eval {

                    Take noise, process create a kind of resembling image to prompt, add to og noise | repeat till image is clear.

                    While evaluating, we STILL add random noise to the model, as if we werent to do that the model would form all particles ( Welsh Lab vid example ) into the mean are of the shape, making a blurry image that isnt represented
                    well, if we were to add random noise it would shift around the vectors leading to a better distribitiun over the original shape.

            }

    }

    DDIM {

            TRAINING { same i believe }

            Eval {

                math is mathing and a new function that will produce the exact same output as DDPM, but without needing to add noise.

            }

    }

}

Prompt Generating {

    (prompt image generation training) :: cross attention, embed the prompt with the image to be noised, insert it in the noise, insert it while processing etc etc

    Spiral's parts corresponds to :cats, dogs, men ( Welsh Lab again ) :: While processing an input f(x, t) (non conditioned vector) also give it a class f(x, t, class) (conditioned vector)|| this alone isnt enough, as the model's wanting of forming the spiral can overtake the desire to classify
    solution === run a no context model on a part of the data : f(x, t, none) and contextful data : f(x,t,cat) || subtract the two :: you have a vector pointing to the classification for cat, multiply by alpha (guidance scale) to make it stronger.
    This is called : classifier free guidance.

    "Modern day" video generators like Wan2.1 use whats called a neg prompt, where our conditional vector containing our prompt is subtracted from a negative prompt that is stuff that we dont want, and the diffusion is generated
    in that direction.

}
```iffusion Models & Prompt Conditioning

> **Where were the Transformers?**
>
> Early diffusion models (DDPM, DDIM, etc.) used **U-Nets** as the denoising network. Transformer-based diffusion models (DiT, MMDiT, FLUX, SD3, etc.) came later.

---

# DDPM (Denoising Diffusion Probabilistic Models)

> **Main drawback:** Sampling is slow because it requires hundreds or thousands of denoising steps.

## Training

1. Take a clean image.
2. Gradually add Gaussian noise until it becomes almost pure noise.
3. Randomly sample a timestep `t`.
4. Give the noisy image and timestep to the model:

```
f(x, t)
```

where:
- `x` = noisy image
- `t` = diffusion timestep

The model predicts the **total noise** added to the image rather than only the previous denoising step.

### Why predict the total noise?

Many noisy trajectories pass through similar intermediate states, making the overall noise easier to estimate than predicting each tiny reverse step.

The timestep tells the model **how noisy** the current image is.

---

## Sampling (Inference)

1. Start from pure Gaussian noise.
2. Predict the noise.
3. Remove part of the predicted noise.
4. Repeat until a clean image is obtained.

```
Noise
  ↓
Predict Noise
  ↓
Remove Noise
  ↓
Repeat...
  ↓
Image
```

Although we're denoising, **random noise is still injected at every reverse step**.

Without this stochasticity, trajectories collapse toward the mean of the data distribution (e.g., the center of the Welsh Lab spiral), producing blurry average images. Injecting noise keeps trajectories diverse and allows the model to sample different valid images.

---

# DDIM (Denoising Diffusion Implicit Models)

## Training

Exactly the same as DDPM.

## Sampling

DDIM derives a deterministic reverse process that produces nearly the same results **without adding random noise** at every step.

This makes inference:
- Faster
- Deterministic (given the same starting noise)
- Require far fewer denoising steps

---

# Prompt Conditioning

During training, the text prompt is embedded and injected into the denoising network (typically through **cross-attention**) so the model can condition image generation on the prompt.

Instead of only predicting

```
f(x, t)
```

the model predicts

```
f(x, t, prompt)
```

where the prompt embedding guides the denoising process toward the desired image.

---

# Classifier-Free Guidance (CFG)

Simply conditioning on a prompt isn't always enough—the model may prioritize matching the overall data distribution rather than following the prompt.

To solve this, the model is trained in two modes:

- **Conditional:** `f(x, t, prompt)`
- **Unconditional:** `f(x, t, ∅)`

The difference

```
f(x,t,prompt) - f(x,t,∅)
```

represents the direction that moves the prediction toward the prompt.

This direction is amplified using the **guidance scale** (`α`):

```
f(x,t,∅) + α(f(x,t,prompt) - f(x,t,∅))
```

Higher guidance scales make the model follow the prompt more strongly.

---

# Negative Prompts

Modern diffusion and video generation models (e.g., **Wan 2.1**) often support **negative prompts**.

Instead of only specifying what should appear, you also specify what **should not** appear.

Conceptually, the model follows the direction

```
Positive Prompt − Negative Prompt
```

which encourages desired features while suppressing unwanted ones.

---

<!-- ========================================================= -->

# Original Notes

```text
Diffisiuon Models => {

    where the fuck were the transformers i forgor claude

    DDPM {

            REQUIRE SO MUCH FUCKING COMPUTE FOR ADDING NOISE

            TRAINING {

                    Take image, add noise | repeat till image is fucked. Make model guess the total noise added to the image.

                    Cuz : its more efficient as a lot of points will go through a certain point makign it easier for the model to guess where they originated from rather then
                    what was the latest step they have taken (simplified a lot) ( E[x99 - x100 | x100 ] == E[x0 - x100 | x100] / 100 )

                    f(x, t=1.00) // let the model know what step its on

            }

            Eval {

                    Take noise, process create a kind of resembling image to prompt, add to og noise | repeat till image is clear.

                    While evaluating, we STILL add random noise to the model, as if we werent to do that the model would form all particles ( Welsh Lab vid example ) into the mean are of the shape, making a blurry image that isnt represented
                    well, if we were to add random noise it would shift around the vectors leading to a better distribitiun over the original shape.

            }

    }

    DDIM {

            TRAINING { same i believe }

            Eval {

                math is mathing and a new function that will produce the exact same output as DDPM, but without needing to add noise.

            }

    }

}

Prompt Generating {

    (prompt image generation training) :: cross attention, embed the prompt with the image to be noised, insert it in the noise, insert it while processing etc etc

    Spiral's parts corresponds to :cats, dogs, men ( Welsh Lab again ) :: While processing an input f(x, t) (non conditioned vector) also give it a class f(x, t, class) (conditioned vector)|| this alone isnt enough, as the model's wanting of forming the spiral can overtake the desire to classify
    solution === run a no context model on a part of the data : f(x, t, none) and contextful data : f(x,t,cat) || subtract the two :: you have a vector pointing to the classification for cat, multiply by alpha (guidance scale) to make it stronger.
    This is called : classifier free guidance.

    "Modern day" video generators like Wan2.1 use whats called a neg prompt, where our conditional vector containing our prompt is subtracted from a negative prompt that is stuff that we dont want, and the diffusion is generated
    in that direction.

}
```
