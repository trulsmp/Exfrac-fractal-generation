#!/bin/bash -l
#SBATCH --job-name=mandelbrot
#SBATCH --partition=iceq
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem=10000
#SBATCH --time=00:10:00
#SBATCH --output=16kresults.out
# ...end of SLURM preamble...

echo "This is job ’$SLURM_JOB_NAME’ (id: $SLURM_JOB_ID) running on the following nodes:"
uniq $SLURM_NODELIST
make
srun time exfrac -r 16000 -i 1000
echo "Have a nice day."
