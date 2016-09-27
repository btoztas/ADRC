/* declarations for use of the random number generator */

void randini(void);
double randlcg(int stream);
void randss(int stream, long zset);
long randgs(int stream);
double rand_exp(int stream, double mean);
int drand_unif(int stream, int n);
double rand_bimod(int stream, double p, double s, double l);
double rand_unif(int stream, double u);
int rand_bernoulli(int stream, double p);

