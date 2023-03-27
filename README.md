# PFMAG a C langage programing student project

You use google map regularly ? Robots too need to know their location, often indoor without access to Global Navigation Satellite System (comonly called GPS). Other sensor can replace it. For instance an odometry system to measure the relative displacement at each timestep and a magnetometer to observe the magnetic field that vary indoor from one position to another. The goal of this project is to implement a bootstrap particle filter algorithm to merge this two sensor outputs and estimate the localisation of the robot inside a map of the magnetic field of the building.

# Dependencies

This code depend on the GNU Scientific Library (GSL) for random number generation

```shell
sudo apt-get install libgsl-dev
```

If you want to plot the particles, I gave you my python3 script for that. It depends on a few module. However the C code works just fine without it (it's a C project after all). To install them globally :

```shell
pip3 install matplotlib natsort
```

# Compilation

I already created a Makefile for you, which should be updated everytime you add a new ".c" file.

To compile, open a terminal, go in the directory and type :
```shell
make
```

To remove all the files generated by the compilation :
```shell
make clean
```

And if you only want to remove all ".o" files while keeping the executable :
```shell
make clean_object
```

# Usage

The compilation yields two executables : pfmag and evaluatePfmag. The first one run the particle filter whereas evaluatePfmag compare its output against the true trajectory to compute localisation errors. Before everything, you should create an empty output directory that will store the output files generated automatically.

## Execute manually

An usage example and parameter meanings are to be found in the file run.bash, and therefore they are not detailed too much here

To run the particle filter
```shell
./pfmag nParticles odometryFilename observationFilename mapFilename stateName resamplingName outputDirname seed
```
It produce the file estimates.csv in outputDirname that store the localisation estimation and variance at each iteration (line by line). It also produce several files weights*.csv and states*.csv containing the values and weight of each particles at each iteration (e.g states3.csv contain the values x,y,psi of each particles at the timestep 3).

To evaluate the particle filter outputs
```shell
./evaluatePfmag estimatesFilename groundtruthFilename
```
It print the error of the last estimate compared to the the last position and orientation of the true trajectory (groundtruth).

(optional) to plot the particles
```shell
python3 estimatesFilename groundtruthFilename
```
It produce images of particle positions and orientations at each time steps

## Execute automatically

On linux you can directly use the bash script to run everithing at once. Make it executable :
```shell
chmod +x run.bash
```

Then, open it, change the filenames to match your computer path and run in a terminal
```shell
./run.bash
```
That's it ! Notice that this bash file copy itself in the output directory, so you can verify later which parameters you used

On other platform (Windows, mac), I advise that you create your own script.


# Which subject ?

You all need to work on the preliminaries to get your particle filter working. Then you can choose.

The simultaneous localisation and calibration is harder (but more interesting ?) than the resampling part. It involves to develop a larger quantity of functions. It also requires a better understanding of the particle filtering algorithm which is not stricly speaking what is evaluated in this IN104 course. I will be happy to help. For my own projects, I'm also curious on the results you might acheive with the algorithms which you chose to implement.

That being said, if you are a beginer in C, I strongly advise that you start by the resampling option.

Option 3 (graphical interface) is for people not interested in either of the previous ones. I never developped such an interface myself so you will be on your own on this one. To adress only if you are experienced in C.

You can do a bit of several options if you want to.

# Pedagogy

I feel that learning is more efficient when there is both a code model to look at and some parts to develop yourself. This is why I provided you with this (relatively long) codebase, instead of making you starting from scratch.

However it is a lot to read at once. So you will find in the next section what are the important files to look at to complete each part of the project.

# Important files

The main is in pfmag.c. It is the entry point of the program and you should definitely take a look. It is split into two parts : First, every input parameters and data are loaded. Then particle filtering is used to estimate the state (x,y,psi) iteratively.

This project makes extensive use of list of vectors of dimention d. For instance all the state can be seen as a list of 'nParticles' elements of dimention 3. The weights are a list of 'nParticles' elements of dimention 1 and so on. For that a special container called 'Data' has been created and is used everywhere. Therefore you should look at 'data.h'.

## Preliminaries

To create your own resampling strategy, first, look at how the 'doNothingResampling' is loaded in the main. Update the main to be able to use your 'multinomialResampling' instead. You may develop it in multinomialResampling.h and multinomialResampling.c. Again take inspiration on doNothingResampling.h and .c. You may also look at the usefull function provided in weight.h

Using 'gsl_ran_multinomial' from GSL, to generate samples folowing the multinomial distribution, can help you.

To give you an idea, my own multinomialResampling.c file is shorter than 40 lines. If you need much more lines of code it might means that you made a mistake somewhere. The hardest part is mainly to understand the codebase and the subject I gave you (ask for help).

## Option 1 : Resampling

Same as preliminaries. With this subject you just keep on developing and testing more resampling strategies.

If your resampling strategy involves to take into account the states values (in addition to the weights as in a classic resampling strategy), then you might want to look at stateXYPsi.h

## Option 2 : Simultaneous localisation and calibration

Here we are changing the state. It contains (x,y,psi,bx,by,bz) instead of just (x,y,psi). Look inside the main where the state is choosen and add the possibility of using another state.

In new files, you will adapt stateXYPsi.h and .c to add the biais. initParticlesXYPsi.h and .c to initializes it for each particles and moveParticlesXYPsi.h and .c to update it. Finally estimatesXYPsi.h and .c can be adapted to also compute biais estimation from the particles states and weights.

## Option 3 (bonus) : graphical interface

I am not that much experimented in graphical interfaces, but you will need to inspect the inputs and outputs of the main. Either open directly the input and output files to see what is inside or look at the writing functions declared in csv.h, writeParticles.h and estimatesXYPsi.h.
