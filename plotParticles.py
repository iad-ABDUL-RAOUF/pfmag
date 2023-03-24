#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 24 14:00:26 2023

@author: ia266894
"""

# some function and a main to plot particles

import matplotlib.pyplot as plt
import matplotlib.colors as clr
import numpy as np
import csv
import glob
import natsort
import sys


def readCsv(filename, delimiter = ',', nlinetoskip = 1):
    data = []
    with open(filename, newline='') as csvfile:
        for k in range(nlinetoskip):
            next(csvfile) #skip header
        csvreader = csv.reader(csvfile, delimiter=delimiter, quoting=csv.QUOTE_NONNUMERIC)
        for row in csvreader:
            data.append(row)
    data = np.array(data)
    return data

def plot2Ddiscretmap(ax,fig,x,y,mag,alpha=1):
    magnorm = np.linalg.norm(mag, axis=1)
    print(round(np.min(magnorm),1), "uT <= |mag| <= ", round(np.max(magnorm),1), "uT")
    cmapname = "viridis"
    clrnorm = clr.Normalize(vmin=10, vmax=90)
    a = ax.scatter(
        x,
        y,
        c=magnorm,
        cmap=cmapname,
        norm=clrnorm,
        alpha=alpha,
        s=2)
    cb = fig.colorbar(a, shrink=0.35, aspect=7)
    cb.set_label("$\mu$T", loc='center', fontsize='xx-large')
    cb.ax.tick_params(labelsize='xx-large')
    return ax

def savePng(filename, fig, size=(11.69*1.2,8.27*1.2)):
    fig.set_size_inches(size, forward=False)
    fig.savefig(filename)


if __name__ == "__main__":
        
    plt.close('all')
    plt.ioff()
    # plt.ion()

    #%% load paramters
    trajectoryGtFilename = sys.argv[1] # TODO command line
    magmapFilename = sys.argv[2] # TODO command line
    pfoutputdir = sys.argv[3] # TODO command line

    estimatesfn = pfoutputdir + "estimates.csv"
    particlesdir = pfoutputdir + "particles/"

    # other parameters hardcoded for simplicity 
    xmin = -25
    xmax = 65
    ymin = -35
    ymax = 5

    #%% load estimates
    estimates = readCsv(estimatesfn, delimiter=',',nlinetoskip=1)

    x_m = estimates[:,0]
    x_v = estimates[:,1]
    y_m = estimates[:,2]
    y_v = estimates[:,3]
    cospsi_m = estimates[:,4]
    cospsi_v = estimates[:,5]
    sinpsi_m = estimates[:,6]
    sinpsi_v = estimates[:,7]
    # WARNING, is this really the mean of psi mathematically speaking ?
    psi_m = np.arctan2(sinpsi_m,cospsi_m)

    #%% load ground truth
    trajectoryGt = readCsv(trajectoryGtFilename, delimiter=',',nlinetoskip=1)
    x_gt = trajectoryGt[:,1]
    y_gt = trajectoryGt[:,2]
    psi_gt = trajectoryGt[:,3]

    #%% load discretised map
    magmap = readCsv(magmapFilename,delimiter=',',nlinetoskip=3) 
    gridpos = magmap[:,0:2]
    gridmag = magmap[:,2:5]

    #%% get all states and weight filenames 
    statesfnlist = natsort.natsorted(glob.glob(particlesdir+"states*.csv"))
    weightsfnlist = natsort.natsorted(glob.glob(particlesdir+"weights*.csv"))

    #%% plot particles
    # if statesfnlist is non empty, it means particle csv are available, so we can plot particles
    if statesfnlist:
        assert len(statesfnlist)==len(weightsfnlist), "not the smae number of particles and weights csv"
        assert len(statesfnlist)==estimates.shape[0], "error, each estimate should meet a csv files containing particles values"
        assert estimates.shape[0]==trajectoryGt.shape[0], "error, not the same number of estimates and groundtruth position"
        k = 0
        for sfn, wfn in zip(statesfnlist,weightsfnlist):
            states = readCsv(sfn, delimiter=',',nlinetoskip=1)
            weights = readCsv(sfn, delimiter=',',nlinetoskip=1)
            px = states[:,0]
            py = states[:,1]
            ppsi = states[:,2]

            # plot particles position
            fig, ax = plt.subplots()
            ax = plot2Ddiscretmap(ax,fig,gridpos[:,0],gridpos[:,1],gridmag, alpha=0.5)
            ax.plot(x_gt, y_gt,"gray",label="gt")
            ax.scatter(px, py, marker="o", color="blue", s=20*np.ones_like(weights), alpha=np.sqrt(weights))
            ax.scatter(x_m[k], y_m[k], marker="o", color="green", s=8, label="estim")
            ax.axis('equal')
            ax.axis(xmin=xmin, xmax=xmax, ymin=ymin, ymax=ymax)
            ax.set(title="particles at iteration %d"%k)
            ax.legend()
            filename = particlesdir + "particlesPos" + str(k)
            savePng(filename, fig)
            plt.close(fig)
            
            
            # plot psi particles
            fig, ax = plt.subplots(subplot_kw=dict(projection="polar"))
            ax.scatter(ppsi, np.ones_like(weights), c='blue', s=20*np.ones_like(weights), alpha=np.sqrt(weights))
            r = [0,1]
            t = [psi_gt[k],psi_gt[k]]
            ax.plot(t, r, c="gray", label="gt")
            t = [psi_m[k],psi_m[k]]
            ax.plot(t, r, c="green", label="estim")
            ax.set_rmax(1.2)
            ax.set(title="particles orientation at iteration %d"%k)
            ax.legend()
            filename = particlesdir + "particlesPsi" + str(k)
            savePng(filename, fig)
            plt.close(fig)
            
            k+=1

    
    
    
    
    
    
    
    
    
    
    
    