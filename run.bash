#!/bin/bash

#### run particle filtering

# number of particles
nParticles="10000"
# odometry file name
odometryFilename="/home/ia266894/Data/20230300-0_in104/20230326-11_atrium/trajectories/6_2994_3425/odometry.csv"
# magnetic observation file name
observationFilename="/home/ia266894/Data/20230300-0_in104/20230326-11_atrium/trajectories/6_2994_3425/observation.csv"
# magnetic map file name
mapFilename="/home/ia266894/Data/20230300-0_in104/20230326-11_atrium/magmap.mm"
# state name : "XYPsi" for (x,y,psi) states. Option 2 makes you implement 'XYPsiBias' too.
stateName="XYPsi"
# resampling name : "noResampling" to use doNothingResampling. Following the preliminary section of this project, you should implement "multinomial".
resamplingName="noResampling"
# output directory of the particle filter. Will automatically write results inside. Path must end with '/'
outputDirname="/home/ia266894/Data/20230300-0_in104/new/"
# a seed to initialaise the random number generator (so the random number generated are always the same for each execution of this program). 
seed="2345"
# the executable file
pfmag="/home/ia266894/Documents/teaching/20230300_ENSTA_IN104/pfmag/pfmag"

# copy this file so you can verify later which parameters you used
cp /home/ia266894/Documents/teaching/20230300_ENSTA_IN104/pfmag/run.bash $outputDirname

# run particle filtering using the previous parameters
$pfmag $nParticles $odometryFilename $observationFilename $mapFilename $stateName $resamplingName $outputDirname $seed


#### run particle filtering evaluation

# estimation computed by the particle filter
estimatesFilename=$outputDirname"estimates.csv"
# file name of the true trajectory
groundtruthFilename="/home/ia266894/Data/20230300-0_in104/20230326-11_atrium/trajectories/6_2994_3425/trajectory.csv"
# the executable file
evaluatePfmag="/home/ia266894/Documents/teaching/20230300_ENSTA_IN104/pfmag/evaluatePfmag"

# run evaluation using the previous parameters
$evaluatePfmag $estimatesFilename $groundtruthFilename


#### plot particles

# the executable file
plotParticles="/home/ia266894/Documents/teaching/20230300_ENSTA_IN104/pfmag/plotParticles.py"
python3 $plotParticles $groundtruthFilename $mapFilename $outputDirname
