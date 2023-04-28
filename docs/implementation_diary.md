# Implementation Diary

## 27.04.2023 - Spiral Bucket Sequence
First, the bucket ordering for Crayg was determined by TBB - it was essentially a `tbb::parallel_for` over all bucket, which where generated line-by-line. Because that was a bit _weird_, the bucket sequence was changed to be line-by-line. 

This is also not ideal, because usually the most interesting part of the image is in the middle and not on the top of the image. That's why a spiral bucket sequence would be more useful.

To not create any performance regressions, some measurements where taken. No clear performance trend was recognizable, some scenes where a little bit slower, some a little bit faster. I think this is just noise, so no performance regressions where created. The Spiral Bucket Sequence will be the new default. 

Cato Runs for measuring the performance: 

Baseline Line-by-line: https://cato.frmbffr.com/projects/5/runs/873 \
Baseline Spiral: https://cato.frmbffr.com/projects/5/runs/874

Absolute Measurements:
![Bucket Sequence Performance Absolute](figures/27.04.2023/bucket-sequence-performance-absolute.svg)
Relative Measurements:
![Bucket Sequence Performance Relative](figures/27.04.2023/bucket-sequence-performance-relative.svg)

## 28.04.2023 - Adaptive Sampling Experiments

I experimented a little bit with adaptive sampling in the last days. I implemented the adaptive sampling inspired by [Dammertz et al.’s paper, "A Hierarchical Automatic Stopping Condition for Monte Carlo Global Illumination"](https://jo.dreggn.org/home/2009_stopping.pdf). 

- short summary of the paper

However, for the first experiments, I skipped the hierarchical part and just rendered the image in 8x8 pixel blocks. 
- later I found out that this was the same approach Dreamworks first took for their implementation of adaptive sampling for MoonRay.

First tests have shown that adaptive sampling can improve the render time quite a bit.
- to get some better numbers, I run on some test scenes 

uniform sampling: https://cato.frmbffr.com/projects/5/runs/873 \
adaptive sampling: https://cato.frmbffr.com/projects/5/runs/879

Total Time uniform sampling: 6h 32min
Total Time adaptive sampling: 4h 40min

- what showed greatest improvements (scenes with a lot of constant areas, for example ambient occlusion)
- what showed less improvement (Intel Sponza)
- why are some Intel Sponza scenes slower? 

- I am not sure, how much the sampling would benefit from using the hierarchy, as they will be some problems with multithreading. since multiple threads are rendering, multiple threads also need to edit the hierarchy 
- Dreamworks uses an approach based on the paper of Dammertz et al. for their adaptive sampling support in MoonRay. Their implementation can be found here (todo) and they also published a paper about that (https://dl-acm-org.ezp.hs-duesseldorf.de/doi/10.1145/3306307.3328205)
- They also skipped the hierarchy part at first, but they found that this leads to undersampling for low-probability effects such as caustics.
- however, since Crayg does not support caustics (and I think it will take quite some time to come to this point), its probalby ok to skip the hierarchy part for now.  
  

### Graphs
Absolute Measurements:
![Adaptive Sampling Performance Absolute](figures/28.04.2023/adaptive-sampling-absolute.svg)
Relative Measurements:
![Adaptive Sampling Performance Relative](figures/28.04.2023/adaptive-sampling-relative.svg)