#!/bin/bash -l
#SBATCH --job-name=firstjob
#SBATCH --partition=iceq
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=8
#SBATCH --mem=10000
#SBATCH --time=00:05:00
# ...end of SLURM preamble...

echo "This is job ’$SLURM_JOB_NAME’ (id: $SLURM_JOB_ID) running on the following nodes:"
uniq $SLURM_NODELIST
fract
echo "Have a nice day."