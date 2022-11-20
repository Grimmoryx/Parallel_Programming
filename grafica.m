//La referencia del código fue sacado del siguiente link: https://www.mathworks.com/matlabcentral/answers/381761-plotting-a-temperature-graphs-of-a-heat-equation-of-a-rod

clearvars
close all
clc

c = 4;
L = 2;
deltat = 0.125000;
k = 0:99;
t = k*deltat;
x = linspace(0,6,50);
xp = c*pi/L^2;
[T,X] = meshgrid(t,x);
u = zeros(size(T));
for n = 1:1000
    u = u + ((-1)^(n+1)/n) * (sin(n*pi*X/L).*exp(-n*xp*T));
end
figure(1)
surf(T, X, u)
grid on
xlabel('t')
ylabel('x')
zlabel('u(x,t)')
