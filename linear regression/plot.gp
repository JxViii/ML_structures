set terminal qt
set title 'Linear Regression'
m = -0.140976
b = 0.713908
plot 'plot.dat' with points title 'Data', m*x+b with lines title 'Fit'
pause -1
