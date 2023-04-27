# Implementation Diary

## 27.04.2023 - Spiral Bucket Sequence
First, the bucket ordering for Crayg was determined by TBB - it was essentially a `tbb::parallel_for` over all bucket, which where generated line-by-line. Because that was a bit _weird_, the bucket sequence was changed to be line-by-line. 

This is also not ideal, because usually the most interesting part of the image is in the middle and not on the top of the image. That's why a spiral bucket sequence would be more useful.

To not create any performance regressions, some measurements where taken. No clear performance trend was recognizable, some scenes where a little bit slower, some a little bit faster. I think this is just noise, so no performance regressions where created. The Spiral Bucket Sequence will be the new default. 

Cato Runs for measuring the performance: 

Baseline Line-by-line: https://cato.frmbffr.com/projects/5/runs/873 \
Baseline Spiral: https://cato.frmbffr.com/projects/5/runs/874

![](figures/27.04.2023/bucket-sequence-performance-absolute.svg)
![](figures/27.04.2023/bucket-sequence-performance-absolute.svg)