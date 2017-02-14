#include "hs.h"

/* It executes the Harmony Search for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runHS(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double fitValue;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runHS.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _HS_, Evaluate, arg); /* Initial evaluation of the search space */

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

    	va_copy(arg, argtmp);

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      tmp = GenerateNewAgent(s, _HS_);
      CheckAgentLimits(s, tmp);
      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    va_end(arg);
}

/* It executes the Improved Harmony Search for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runIHS(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double fitValue;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runIHS.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _HS_, Evaluate, arg); /* Initial evaluation of the search space */

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

    	va_copy(arg, argtmp);

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      s->PAR = s->PAR_min+((s->PAR_max-s->PAR_min)/s->iterations)*t;
      s->bw = s->bw_max*exp((log(s->bw_min/s->bw_max)/s->iterations)*t);
      tmp = GenerateNewAgent(s, _HS_);
      CheckAgentLimits(s, tmp);
      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    va_end(arg);
}

/* It updates the individual values of HMCR and PAR concerning PSF-HS
Parameters: [H]
H: Harmony Memory */
void UpdateIndividualHMCR_PAR(SearchSpace *s, char **rehearsal, double *HMCR, double *PAR){
    int i, j, ctr[3];
    for(j = 0; j < s->n; j++){
        ctr[0] = ctr[1] = ctr[2] = 0;
		for(i = 0; i < s->m; i++)
		      ctr[(int)rehearsal[i][j]]++;
        HMCR[j] = ctr[PSF_MEMORY]/(double)s->m;
        PAR[j] = ctr[PSF_PITCH]/(double)s->m;
	}
}

/* It generates a new PSF agent
Paremeters:
s: search space
*/
Agent *GenerateNewPSF(SearchSpace *s, double *HMCR, double *PAR, char *op_type){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @GenerateNewPSF.\n");
        exit(-1);
    }

    Agent *a = NULL;
    int i, j;
    double r, signal;

    a = CreateAgent(s->n, _HS_);

    for(j = 0; j < s->n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(HMCR[j] >= r){
            i = GenerateUniformRandomNumber(0, s->m-1);
            r = GenerateUniformRandomNumber(0, 1);
            op_type[j] = PSF_MEMORY;
            if(PAR[j] >= r){
                signal = GenerateUniformRandomNumber(0, 1);
                r = GenerateUniformRandomNumber(0, 1);
                if(signal >= 0.5)
                        a->x[j] = s->a[i]->x[j]+r*s->bw;
                else
                        a->x[j] = s->a[i]->x[j]-r*s->bw;
                op_type[j] = PSF_PITCH;
            }
        }else{
          r = (s->UB[j] - s->LB[j]) * GenerateUniformRandomNumber(0, 1) + s->LB[j];
          a->x[j] = r;
          op_type[j] = PSF_RANDOM;
        }
    }

    return a;
}

/* It executes the Parameter-setting-free Harmony Search for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runPSF_HS(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double fitValue, *HMCR, *PAR;
    char *op_type, **rehearsal;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runPSF_HS.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _HS_, Evaluate, arg); /* Initial evaluation of the search space */

    rehearsal = (char **)calloc(s->m, sizeof(char *));
    for(i = 0; i < s->m; i++)
        rehearsal[i] = (char *)calloc(s->n, sizeof(char));
    HMCR = (double *)calloc(s->n, sizeof(double));
    PAR = (double *)calloc(s->n, sizeof(double));
    op_type = (char *)calloc(s->n, sizeof(char));

    for(i = 0; i < s->m; i++)
        for(j = 0; j < s->n; j++)
            rehearsal[i][j] = PSF_RANDOM;

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

      va_copy(arg, argtmp);

      if(t == 1){
          for(j = 0; j < s->n; j++){
              HMCR[j] = s->HMCR;
              PAR[j] = s->PAR;
          }
      }

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      tmp = GenerateNewPSF(s, HMCR, PAR, op_type);
      CheckAgentLimits(s, tmp);
      UpdateIndividualHMCR_PAR(s, rehearsal, HMCR, PAR);

      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
        for(j = 0; j < s->n; j++)
          rehearsal[s->m-2][j] = op_type[j];
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    for(i = 0; i < s->m; i++)
      free(rehearsal[i]);
    free(rehearsal);
    free(HMCR);
    free(PAR);
    free(op_type);

    va_end(arg);
}

/* It executes the Tensor-based Harmony Search for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runTensorHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, l;
    double fitValue, r, signal, **tmp_t = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runTensorHS.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _HS_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

    	va_copy(arg, argtmp);

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      tmp = CreateAgent(s->n, _HS_);
      tmp_t = GenerateNewTensor(s, tensor_id);

      for(j = 0; j < s->n; j++){
          r = GenerateUniformRandomNumber(0, 1);
          if(s->HMCR >= r){
              i = GenerateUniformRandomNumber(0, s->m-1);
              r = GenerateUniformRandomNumber(0, 1);
              if(s->PAR >= r){
                  signal = GenerateUniformRandomNumber(0, 1);
                  r = GenerateUniformRandomNumber(0, 1);
                  if(signal >= 0.5)
                      for(l = 0; l < tensor_id; l++)
                          tmp_t[j][l] = s->a[i]->t[j][l]+r*s->bw;
                  else
                      for(l = 0; l < tensor_id; l++)
                          tmp_t[j][l] = s->a[i]->t[j][l]-r*s->bw;
              }
          }else{
            for(l = 0; l < tensor_id; l++){
                r = (s->UB[j] - s->LB[j]) * GenerateUniformRandomNumber(0, 1) + s->LB[j];
                tmp_t[j][l] = r;
            }
          }
      }

      CheckTensorLimits(s, tmp_t, tensor_id);
      for(j = 0; j < s->n; j++)
          tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DeallocateTensor(&s->a[s->m-1]->t, s->n);
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
        s->a[s->m-1]->t = CopyTensor(tmp_t, s->n, tensor_id);
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);
      DeallocateTensor(&tmp_t, s->n);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    va_end(arg);
}

/* It executes the Tensor-based Improved Harmony Search for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runTensorIHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, l;
    double fitValue, r, signal, **tmp_t = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runTensorIHS.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _HS_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

      va_copy(arg, argtmp);

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      s->PAR = s->PAR_min+((s->PAR_max-s->PAR_min)/s->iterations)*t;
      s->bw = s->bw_max*exp((log(s->bw_min/s->bw_max)/s->iterations)*t);

      tmp = CreateAgent(s->n, _HS_);
      tmp_t = GenerateNewTensor(s, tensor_id);

      for(j = 0; j < s->n; j++){
          r = GenerateUniformRandomNumber(0, 1);
          if(s->HMCR >= r){
              i = GenerateUniformRandomNumber(0, s->m-1);
              r = GenerateUniformRandomNumber(0, 1);
              if(s->PAR >= r){
                  signal = GenerateUniformRandomNumber(0, 1);
                  r = GenerateUniformRandomNumber(0, 1);
                  if(signal >= 0.5)
                      for(l = 0; l < tensor_id; l++)
                          tmp_t[j][l] = s->a[i]->t[j][l]+r*s->bw;
                  else
                      for(l = 0; l < tensor_id; l++)
                          tmp_t[j][l] = s->a[i]->t[j][l]-r*s->bw;
              }
          }else{
            for(l = 0; l < tensor_id; l++){
                r = (s->UB[j] - s->LB[j]) * GenerateUniformRandomNumber(0, 1) + s->LB[j];
                tmp_t[j][l] = r;
            }
          }
      }

      CheckTensorLimits(s, tmp_t, tensor_id);
      for(j = 0; j < s->n; j++)
          tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DeallocateTensor(&s->a[s->m-1]->t, s->n);
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
        s->a[s->m-1]->t = CopyTensor(tmp_t, s->n, tensor_id);
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);
      DeallocateTensor(&tmp_t, s->n);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    va_end(arg);
}