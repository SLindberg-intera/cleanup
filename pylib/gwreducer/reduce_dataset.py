import logging
import os
import numpy as np
import matplotlib.pyplot as plt
import pylib.vzreducer.constants as c
import pylib.vzreducer.reduce_flux as red_flux
import pylib.vzreducer.plots as p
from pylib.vzreducer.summary_file import summary_info

SMOOTH = "SMOOTH"
RAW = "RAW"

def log_info(reduction_result):
    msg = "{} {} reduced: {} E_m:{:.2g}%"
    rr = reduction_result
    s = msg.format(
            rr.mass.copc,
            rr.mass.site,
            rr.num_reduced_points,
            rr.relative_total_mass_error*100
    )
    logging.info(s)


def summary_plot(reduction_result, output_folder):
    """ make a plot of hte reduction result and place it in output_folder"""
    copc = reduction_result.mass.copc
    site = reduction_result.mass.site
    f, ax1, ax2 = p.reduced_timeseries_plot(reduction_result)
    plt.savefig(os.path.join(output_folder, 
            "{}-{}.png".format(copc, site)))
    plt.close(f)


def reduce_dataset(timeseries, summary_file, output_folder):
    """ take a TimeSeries object and reduce it.

    write a summary into summary_folder

    """
    copc = timeseries.copc
    site = timeseries.site
    A = np.max(timeseries.values)
    timeseries.values = timeseries.values/A
    if timeseries.are_all_zero():
        logging.info("Skipped {} {} - all zero".format(
            copc, site))
        return False    
    mx = np.argmax(timeseries.values)
    points = [0, mx, len(timeseries)]


    x = timeseries.times

    mass = timeseries.integrate()

    area = 10*np.mean(timeseries.values)*(x[-1]-x[0])
    #mass.values[-1]
    ythresh = .1*np.max(timeseries.values)
    out_error = 1
    out_error_last = out_error
    OUT_ERROR_THRESHOLD = 1e-2
    UPPER_N = 50
    LOWER_N = 15
    last_result = None 
    MAX_ITERATIONS = 80

    solve_type = SMOOTH
    simple_peaks = False

    for ix in range(MAX_ITERATIONS):

        res = red_flux.reduce_flux(timeseries, area, ythresh, 
                solve_type=solve_type,
                simple_peaks=simple_peaks
                )
        out_error = abs(res.relative_total_mass_error)
        if out_error < OUT_ERROR_THRESHOLD and len(res.reduced_flux)>=LOWER_N:
            last_result = res
            break
        if len(res.reduced_flux) > 2*UPPER_N:
            simple_peaks = True
            solve_type = RAW
        ythresh = 0.5*ythresh
        area = 0.5*area
        out_error_last = out_error
        last_result = res

    if ix>=MAX_ITERATIONS - 1:
        logging.info("MAX ITERATIONS")

    delta_mass = last_result.total_mass_error

    last_result = red_flux.rebalance(last_result) 
    plot_file = summary_plot(last_result, output_folder)
    last_result.to_csv(output_folder)
    used_ythresh = ythresh
    used_area = area
    n_iterations = ix
    summary_info(last_result, summary_file, 
            delta_mass, used_ythresh, used_area, n_iterations)
    log_info(last_result)
