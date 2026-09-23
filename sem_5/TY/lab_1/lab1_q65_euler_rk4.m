%% Вопрос 6.5. Один шаг методов Эйлера, усовершенствованного Эйлера и Рунге-Кутты 4
%  Пример из Приложения Б методички:   y' = x^2 - 2y,   y(0) = 1,   h = 0.1
%  Точное решение:                     y*(x) = 3/4*exp(-2x) + x^2/2 - x/2 + 1/4
%
%  Часть 1: один шаг (x0,y0) -> (x1,y1): промежуточные величины и график
%  Часть 2: те же методы на всём отрезке [0,1] (таблица, как в методичке)
%  Часть 3: один шаг для системы варианта 6 (векторный случай, нужен sdu_rhs.m)

clear; clc; close all;

f   = @(x, y) x.^2 - 2*y;
yex = @(x) 0.75*exp(-2*x) + 0.5*x.^2 - 0.5*x + 0.25;

x0 = 0;  y0 = 1;  h = 0.1;
x1 = x0 + h;
xm = x0 + h/2;                       % середина шага

%% ---------- Часть 1. Один шаг ----------
% 1) Метод Эйлера: наклон берётся в НАЧАЛЕ шага
%       y1 = y0 + h*f(x0, y0)
k1 = f(x0, y0);
yE = y0 + h*k1;

% 2) Усовершенствованный метод Эйлера: наклон берётся в СЕРЕДИНЕ шага
%       y1 = y0 + h*f(x0 + h/2,  y0 + h/2*f(x0, y0))
p2 = y0 + h/2*k1;                    % "полушаг" Эйлера в середину интервала
k2 = f(xm, p2);                      % наклон в средней точке
yM = y0 + h*k2;

% 3) Классический метод Рунге-Кутты 4-го порядка: средневзвешенный наклон
%       y1 = y0 + h/6*(k1 + 2*k2 + 2*k3 + k4)
p3 = y0 + h/2*k2;
k3 = f(xm, p3);
p4 = y0 + h*k3;
k4 = f(x1, p4);
kR = (k1 + 2*k2 + 2*k3 + k4) / 6;
yR = y0 + h*kR;

yT = yex(x1);                        % точное значение y(x1)
fprintf('Шаг h = %g,  (x0, y0) = (%g, %g)\n', h, x0, y0);
fprintf('k1 = %9.5f\nk2 = %9.5f\nk3 = %9.5f\nk4 = %9.5f\n', k1, k2, k3, k4);
fprintf('средний наклон (k1+2k2+2k3+k4)/6 = %9.6f\n\n', kR);
fprintf('Точное y(%g)                = %.6f\n', x1, yT);
fprintf('Эйлер                     y1 = %.6f   |ошибка| = %.2e\n', yE, abs(yE - yT));
fprintf('Усовершенствованный Эйлер y1 = %.6f   |ошибка| = %.2e\n', yM, abs(yM - yT));
fprintf('Рунге-Кутта 4             y1 = %.6f   |ошибка| = %.2e\n\n', yR, abs(yR - yT));

% ----- график -----
xx  = linspace(x0, x0 + 1.4*h, 200);
d   = h/4;                            % полудлина отрезка-касательной на рисунке
lim = [x0 - 0.01, x0 + 1.4*h, 0.78, 1.03];
grey = [0.5 0.5 0.5];

figure('Name', 'Один шаг: Эйлер, усоверш. Эйлер, Рунге-Кутта 4', 'NumberTitle', 'off');

% --- Эйлер ---
subplot(2, 2, 1); hold on; grid on;
hEx = plot(xx, yex(xx), 'k-', 'LineWidth', 2);
hE  = plot([x0 x1], [y0 yE], 'r-o', 'LineWidth', 1.5);
hT  = plot(x1, yT, 'kp', 'MarkerSize', 10, 'MarkerFaceColor', 'k');
plot(x0, y0, 'ko', 'MarkerFaceColor', 'k');
text(x1, yE, sprintf('  y_1 = %.4f', yE));
legend([hEx hE hT], {'точное решение', 'ломаная Эйлера', 'y(x_1)'}, 'Location', 'southwest');
axis(lim);  xlabel('x');  ylabel('y');
title('Эйлер: наклон k_1 в начале шага');

% --- Усовершенствованный Эйлер ---
subplot(2, 2, 2); hold on; grid on;
plot(xx, yex(xx), 'k-', 'LineWidth', 2);
plot([x0 xm], [y0 p2], '--', 'Color', grey);                 % полушаг Эйлера
plot(xm, p2, 'b*');                                          % средняя точка
plot([xm-d xm+d], [p2 - k2*d, p2 + k2*d], 'b--');            % касательная в средней точке
plot([x0 x1], [y0 yM], 'b-s', 'LineWidth', 1.5);             % шаг с наклоном k2
plot(x1, yT, 'kp', 'MarkerSize', 10, 'MarkerFaceColor', 'k');
plot(x0, y0, 'ko', 'MarkerFaceColor', 'k');
text(x1, yM, sprintf('  y_1 = %.5f', yM));
axis(lim);  xlabel('x');  ylabel('y');
title('Усоверш. Эйлер: наклон k_2 в середине шага');

% --- Рунге-Кутта 4 ---
subplot(2, 2, 3); hold on; grid on;
plot(xx, yex(xx), 'k-', 'LineWidth', 2);
px = [x0, xm, xm, x1];   py = [y0, p2, p3, p4];   pk = [k1, k2, k3, k4];
for i = 1:4
    plot([px(i)-d, px(i)+d], [py(i) - pk(i)*d, py(i) + pk(i)*d], '-', 'Color', grey);
    plot(px(i), py(i), 'k.', 'MarkerSize', 12);
    text(px(i), py(i), sprintf('  k_%d', i));
end
plot([x0 x1], [y0 yR], 'g-d', 'LineWidth', 1.5);
plot(x1, yT, 'kp', 'MarkerSize', 10, 'MarkerFaceColor', 'k');
text(x1, yR, sprintf('  y_1 = %.6f', yR), 'VerticalAlignment', 'top');
axis(lim);  xlabel('x');  ylabel('y');
title('Рунге-Кутта 4: средневзвешенный наклон k_1...k_4');

% --- Погрешности после одного шага ---
subplot(2, 2, 4);
bar(1:3, [abs(yE - yT), abs(yM - yT), abs(yR - yT)]);
set(gca, 'YScale', 'log', 'XTick', 1:3, ...
         'XTickLabel', {'Эйлер', 'Усоверш. Эйлер', 'РК4'});
grid on;  ylabel('|y_1 - y(x_1)|');
title('Погрешность после одного шага');

%% ---------- Часть 2. Весь отрезок [0,1], h = 0.1 ----------
N  = 10;
x  = (0:N)*h;
Ye = zeros(1, N+1);   Ym = Ye;   Yr = Ye;
Ye(1) = y0;   Ym(1) = y0;   Yr(1) = y0;
for i = 1:N
    Ye(i+1) = Ye(i) + h*f(x(i), Ye(i));                                   % Эйлер
    Ym(i+1) = Ym(i) + h*f(x(i) + h/2, Ym(i) + h/2*f(x(i), Ym(i)));        % усоверш. Эйлер
    q1 = f(x(i),         Yr(i));                                          % Рунге-Кутта 4
    q2 = f(x(i) + h/2,   Yr(i) + h*q1/2);
    q3 = f(x(i) + h/2,   Yr(i) + h*q2/2);
    q4 = f(x(i) + h,     Yr(i) + h*q3);
    Yr(i+1) = Yr(i) + h/6*(q1 + 2*q2 + 2*q3 + q4);
end
Yt = yex(x);

fprintf('  i    x_i    Эйлер    Усов.Э.     РК4      точное   ош.Эйлер  ош.Усов.  ош.РК4\n');
for i = 1:N+1
    fprintf('%3d  %4.1f  %8.5f  %8.5f  %8.6f  %8.6f  %8.1e  %8.1e  %8.1e\n', ...
            i-1, x(i), Ye(i), Ym(i), Yr(i), Yt(i), ...
            abs(Ye(i) - Yt(i)), abs(Ym(i) - Yt(i)), abs(Yr(i) - Yt(i)));
end

figure('Name', 'Сравнение методов на [0, 1]', 'NumberTitle', 'off');
xf = linspace(0, 1, 200);
plot(xf, yex(xf), 'k-', x, Ye, 'r-o', x, Ym, 'b-s', x, Yr, 'g-d', 'LineWidth', 1.2);
grid on;
legend('точное решение', 'Эйлер', 'усоверш. Эйлер', 'Рунге-Кутта 4', 'Location', 'best');
xlabel('x');  ylabel('y');
title('y'' = x^2 - 2y,  y(0) = 1,  h = 0.1');

%% ---------- Часть 3. Один шаг для системы варианта 6 ----------
% y(t) = 1(t),  x(0) = [1; 0.5; 0.1],  h = 0.1  (те же формулы, но для вектора состояния)
F  = @(t, X) sdu_rhs(t, X, 1);
X0 = [1; 0.5; 0.1];

K1 = F(0,   X0);
XE = X0 + h*K1;                                   % Эйлер
K2 = F(h/2, X0 + h/2*K1);
XM = X0 + h*K2;                                   % усовершенствованный Эйлер
K3 = F(h/2, X0 + h/2*K2);
K4 = F(h,   X0 + h*K3);
XR = X0 + h/6*(K1 + 2*K2 + 2*K3 + K4);            % Рунге-Кутта 4

[~, Xs] = ode45(F, [0 h], X0, odeset('RelTol', 1e-10, 'AbsTol', 1e-12));
Xref = Xs(end, :)';                               % эталон (жёсткие допуски)

fprintf('\nСистема варианта 6, y = 1(t), h = %g, вектор [x1; x2; x3]:\n', h);
fprintf('  K1 (наклон в начале)        = [%9.5f %9.5f %9.5f]\n', K1);
fprintf('  Эйлер                       = [%9.5f %9.5f %9.5f]\n', XE);
fprintf('  Усовершенствованный Эйлер   = [%9.5f %9.5f %9.5f]\n', XM);
fprintf('  Рунге-Кутта 4               = [%9.5f %9.5f %9.5f]\n', XR);
fprintf('  Эталон (ode45, строгие tol) = [%9.5f %9.5f %9.5f]\n', Xref);
