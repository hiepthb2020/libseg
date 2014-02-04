import numpy as np
import pylab as pl

#densities = np.genfromtxt('densities.txt')
#print densities.shape

for densfile in ['densities_nomedfilter.txt', 'densities_medfilter.txt']:
    densities = np.genfromtxt(densfile)
    pl.figure()
    pl.suptitle(densfile)
    for c in xrange(3):
        pl.subplot(3, 1, c + 1)
        pl.title('Channel %d' % c)
        p_fg = densities[2*c]
        p_bg = densities[2*c + 1]
        pl.plot(np.arange(255), p_fg, c='b', label='fg')
        pl.plot(np.arange(255), p_bg, c='g', label='bg')
        print 'sum(p_fg) : ', np.sum(p_fg)
        print 'sum(p_bg) : ', np.sum(p_bg)
pl.show()
