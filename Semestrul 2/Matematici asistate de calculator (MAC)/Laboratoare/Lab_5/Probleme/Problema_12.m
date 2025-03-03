function x = Problema_12(x0, r, Dr, lambda, k)

x = x0;

for i = 1 : k
    A = Dr(x);
    v = (A' * A + lambda* diag(diag(A' * A))) \ (-A' * r(x));
    x = x + v;
end

% t0=[0.9120;0.9860;1.0600;1.1300;1.1900;1.2600;1.3200;1.3800;1.4100;1.4900];
% y0=[13.7;15.9;18.5;21.3;23.5;27.2;32.7;36.0;38.6;43.7];
% 
% r = @(x) [x(1).*t0.^( x(2)) - y0];
% Dr = @(x) [t0.^(x(2)) x(1).*t0.^( x(2)).*log(t0)];
% 
% x = Problema_12([16;3], r, Dr, 1, 50)
% 
% y_ap = x(1) * t0.^x(2) - y0;
% 
% norma = norm(y_ap);
% 
% REMP = norma / sqrt(length(t0))