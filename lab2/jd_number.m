% Calculations of the Julian Day
function [JD] = jd_number(Y, M, D)


A = floor(Y/100);
B = floor(A/4);
C = 2 - A + B;

E = 365.25 * (Y + 4716);
F = floor(30.6001 * (M + 1));

JD = C + D + E + F - 1524.5;

return