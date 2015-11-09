#ifndef ESTIMATES_SCALE_H
#define ESTIMATES_SCALE_H

__global__ void estimates_scale_kernel1(chain_t *dd, double iterations){
  int l, n;

  dd->nuPostMean[0]/= iterations;
  dd->omegaSquaredPostMean[0]/= iterations;
  dd->tauPostMean[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l]/= iterations;
    dd->thetaPostMean[l]/= iterations;
  }

  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMean[n]/= iterations;
}

__global__ void estimates_scale_kernel2(chain_t *dd, double iterations){
  int l, n;
  dd->nuPostMeanSquare[0]/= iterations;
  dd->omegaSquaredPostMeanSquare[0]/= iterations;
  dd->tauPostMeanSquare[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l]/= iterations;
    dd->thetaPostMeanSquare[l]/= iterations;
  }

  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMeanSquare[n]/= iterations;
}

__global__ void estimates_scale_kernel3(chain_t *dd, double iterations){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaPostMean[id]/= iterations;
  for(l = 0; l < dd->L; ++l){
    dd->betaPostMean[I(l, id)]/= iterations;
    dd->xiPostMean[I(l, id)]/= iterations;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonPostMean[I(n, id)]/= iterations;
}

__global__ void estimates_scale_kernel4(chain_t *dd, double iterations){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaPostMeanSquare[id]/= iterations;
  for(l = 0; l < dd->L; ++l){
    dd->betaPostMeanSquare[I(l, id)]/= iterations;
    dd->xiPostMeanSquare[I(l, id)]/= iterations;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonPostMeanSquare[I(n, id)]/= iterations;
}

__global__ void estimates_scale_kernel5(chain_t *dd, double iterations){
  int g = IDX, p;
  if(g >= dd->G) return;
  for(p = 0; p < dd->P; ++p)
    dd->probs[I(p, g)] /= iterations;
}

void estimates_scale(SEXP hh, chain_t *dd){
  double iterations = (double) li(hh, "iterations")[0];
  estimates_scale_kernel1<<<1, 1>>>(dd, iterations);
  estimates_scale_kernel2<<<1, 1>>>(dd, iterations);
  estimates_scale_kernel3<<<GRID, BLOCK>>>(dd, iterations);
  estimates_scale_kernel4<<<GRID, BLOCK>>>(dd, iterations);
  estimates_scale_kernel5<<<GRID, BLOCK>>>(dd, iterations);
}

#endif // ESTIMATES_SCALE_H