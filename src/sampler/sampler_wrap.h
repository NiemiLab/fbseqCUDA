#ifndef SAMPLER_SAMPLER_H
#define SAMPLER_SAMPLER_H

#define DEFAULT 1
#define SLICE_STEP 2
#define METROPOLIS 3

__device__ args_t sampler_wrap(chain_t *dd, args_t args){
  switch(args.sampler){
    case SLICE_STEP : return slice_step(dd, args);
//    case METROPOLIS : return metropolis(dd, args); // Not tested or fully implemented.
    default         : return slice_step(dd, args);
  }
}

#endif // SAMPLER_SAMPLER_H
