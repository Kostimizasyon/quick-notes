# IEEE 754 Floating Point Convertion

```javascript

const a = 0.1;
const b = 0.7;

console.log(a + b);
// 0.7999999999999999
```

Has this happened to you? Did you just blame javascript (as you should)? Well, for once its not javascript's fault. This is true for almost
any language! The reason? ====> **IEEE 754**!

## The Crem De La Crop

The thing is, in any language we do not have infinite space to represent numbers. So a number like 1/3 ===== 0.3333333333... to infinity, is really hard to represent.
T1 get around this we have **IEEE 754**. The thing is that no matter what we do, we just cannot represent every DECIMAL number with binary. 0.8 CANNOT be represented in binary.

## How **IEEE 754** tackles It

In **IEE 754**, we tackle this issue like we were thingking of scientifict notation. We break the number into two parts, the mnatissa and the exponent.

Sign bit: 0 = positive, 1 = negative.
Exponent: stored as an unsigned int, but shifted by a bias (1023 for double, 127 for float) so it can represent negative exponents too.
Mantissa (aka significand): the fractional part after an implicit leading 1. — this "implicit bit" trick gives you one extra bit of precision for free, since every normalized binary number starts with 1.

value = (-1)^sign × 1.mantissa × 2^(exponent - bias)

We have 2 ways to represent this,

1. 32 Bit Single Presicion === float

2. 64 Bit Double Preiscion === double

We tackle the issue as follows => we give 1 bit of value for sign, then 8 or 11 bits for exponent and 23 or 54 bits for mantissa.
