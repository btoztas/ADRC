/* 
   Prime modulus multiplicative linear congruential generator 
   Z[i] = (630360016 * Z[i-1]) (mod(pow(2,31) - 1)) taken from A. Law and D. Kelton's book.
   The input argument
   "stream" must be an int greater than or equal to zero,
   giving the desired stream number. The header file rand.h must be included
   in the calling program before using these functions.
*/

#include <math.h>
#include "random.h"

#define MODULUS 2147483647
#define MULT1        24112
#define MULT2        26143

/* define an array to hold 40 seeds */

static long zrng[40];

/* initialize the seeds to that value */

void randini(void)
{
	zrng[0] = 1973272912;
	zrng[1] = 281629770;
	zrng[2] = 20006270; 
	zrng[3] = 1280689831;
	zrng[4] = 2096730329;
	zrng[5] = 1933576050;
	zrng[6] = 913566091;
	zrng[7] = 246780520;
	zrng[8] = 1363774876;
	zrng[9] = 604901985;
	zrng[10] = 1511192140;
	zrng[11] = 1259851944;
	zrng[12] = 824064364;
	zrng[13] = 150493284;
	zrng[14] = 242708531;
	zrng[15] = 75253171;
	zrng[16] = 1964472944;
	zrng[17] = 1202299975;
	zrng[18] = 233217322;
	zrng[19] = 1911216000;
	zrng[20] = 726370533;
	zrng[21] = 403498145;
	zrng[22] = 993232223;
	zrng[23] = 1103205531;
	zrng[24] = 762430696;
	zrng[25] = 1922803170;
	zrng[26] = 1385516923;
	zrng[27] = 76271663;
	zrng[28] = 413682397;
	zrng[29] = 726466604;
	zrng[30] = 336157058;
	zrng[31] = 1432650381;
	zrng[32] = 1120463904;
	zrng[33] = 595778810;
	zrng[34] = 877722890;
	zrng[35] = 1046574445;
	zrng[36] = 68911991;
	zrng[37] = 2088367019;
	zrng[38] = 748545416;
	zrng[39] = 622401386;
}

/* Generate the next random number */

double randlcg(int stream)
{
	long zi, lowprd, hi31;

	zi		= zrng[stream];
	lowprd	= (zi & 65535) * MULT1;
	hi31	= (zi >> 16) * MULT1 + (lowprd >> 16);
	zi		= ((lowprd & 65535) - MODULUS) +
			  ((hi31 & 32767) << 16) + (hi31 >> 15);
	if (zi < 0) zi += MODULUS;
	lowprd	= (zi & 65535) * MULT2;
	hi31	= (zi >> 16) * MULT2 + (lowprd >> 16);
	zi		= ((lowprd & 65535) - MODULUS) +
			  ((hi31 & 32767) << 16) + (hi31 >> 15);
	if (zi < 0) zi += MODULUS;
	zrng[stream] = zi;
	return ((zi >> 7 | 1) + 1)/ 16777216.0;
}

/* Set the current zrng for stream "stream" to zset */

void randss(int stream, long zset)
{
	zrng[stream] = zset;
}

/* Return the current zrng for stream "stream" */

long randgs(int stream)
{
	return zrng[stream];
}

/* Generate an exponential random variate */

double rand_exp(int stream, double mean)
{
	return (- mean * log(randlcg(stream)));
}

/* Generate a discrete uniform variate in the set {0,...,n-1} */

int drand_unif(int stream, int n)
{
	int			nl;	

	nl = (int) floor(n * randlcg(stream));
	return (nl < n) ? nl : n - 1;
}

/* Generate a bimodal distribution */

double rand_bimod(int stream, double p, double s, double l)
{
	return (randlcg(stream) < p) ? s : l;
}

/* Generate a uniform distribution */

double rand_unif(int stream, double u)
{
    return (randlcg(stream) * u);
}

/* Generate a Bernoulli trial */
int	rand_bernoulli(int stream, double p)
{
	return (randlcg(stream) < p);
}
