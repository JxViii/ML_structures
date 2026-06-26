set terminal qt
set title 'Linear Regression'
m = -0.620143
b = 1.60729
plot 'plot.dat' with points title 'Data', m*x+b with lines title 'Fit'
pause -1
