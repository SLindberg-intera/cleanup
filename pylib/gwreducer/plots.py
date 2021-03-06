import matplotlib.pyplot as plt
from matplotlib.ticker import EngFormatter
import pylib.gwreducer.constants as c
from pylib.gwreducer.config import config
import numpy as np
from scipy import interpolate

def make_title(residual):
    return "{} {}".format(residual.raw.copc, residual.raw.site)

BLACK = 'k

FORMATTER = EngFormatter(places=0, sep="\N{THIN SPACE}")

def reduced_timeseries_plot(reduction_result):
    """  makes a pretty plot of the reduction result """
    f, (ax1, ax2) = plt.subplots(2,1, sharex=True)
    flux = reduction_result.flux
    mass = reduction_result.mass

    r_flux = reduction_result.reduced_flux
    #r_flux = reduction_result.reduced_flux.interpolate_at_timeseries(flux)
    r_mass = reduction_result.reduced_mass
    #r_mass = r_flux.integrate()
    #reduction_result.reduced_mass

    dflux = flux - r_flux
    dmass = mass - r_mass

    ax1.plot(flux.times, flux.values, 'b', label="input")
    ax1.plot(r_flux.times, r_flux.values, 'r.', label="reduced")
    ax2.plot(mass.times, mass.values, 'b')
    ax2.plot(r_mass.times, r_mass.values, 'r.')

    ax1.plot(dflux.times, dflux.values, 'k', label="diff")
    ax2.plot(dmass.times, dmass.values, 'k')

    ax1.yaxis.set_major_formatter(FORMATTER)
    ax2.yaxis.set_major_formatter(FORMATTER)
    ax1.legend()

    ax1.set_title(
            "{}  {}".format(
            flux.site, flux.copc)
            )
    ax1.set_ylabel("Flux (Ci/yr)")
    ax2.set_ylabel("Mass (Ci)")

    return  f, ax1, ax2



