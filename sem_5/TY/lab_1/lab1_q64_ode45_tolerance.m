%% Вопрос 6.4. Как ode45 обеспечивает заданную точность (система варианта 6)
%  ode45 - вложенная пара методов Рунге-Кутты 4(5) (Дорман-Принс).
%  На каждом шаге по одним и тем же вычислениям правой части получают ДВА
%  решения разных порядков (5-го и 4-го). Их разность - оценка локальной
%  погрешности e. Шаг принимается, если для всех компонент
%       |e_i| <= max(RelTol*|x_i|, AbsTol_i),
%  иначе он отбрасывается и повторяется с меньшим h. Новый шаг подбирается
%  примерно как  h_new ~ 0.8*h*(допуск/|e|)^(1/5):  где решение меняется
%  быстро - шаг мельче, где плавно - крупнее.
%
%  Здесь это показано на y = 1(t), x(0) = 0, где известно точное решение
%       x(t) = xe - expm(A*t)*xe,   xe = [b/a0; 0; 0]  (положение равновесия).
%  Файл sdu_rhs.m должен лежать в этой же папке.

clear; clc; close all;

a0 = 15;  a1 = 5;  a2 = 0;  a3 = 1;  b = 15;
A  = [0, 1, 0; 0, 0, 1; -a0/a3, -a1/a3, -a2/a3];
xe = [b/a0; 0; 0];                   % при y = 1 положение равновесия: A*xe + B = 0
Tend = 5;
x0   = [0 0 0];
rhs  = @(t, x) sdu_rhs(t, x, 1);

%% 1. Параметры по умолчанию: RelTol = 1e-3, AbsTol = 1e-6 (статистика решателя)
disp('--- ode45, допуски по умолчанию (RelTol = 1e-3, AbsTol = 1e-6) ---');
[tD, xD] = ode45(rhs, [0 Tend], x0, odeset('Stats', 'on'));
% в командное окно выводятся: успешные шаги, отброшенные шаги, число вычислений f

%% 2. Ужесточаем допуски: как меняются число шагов и ошибка
tols = [1e-3, 1e-6, 1e-9];           % RelTol; AbsTol берём в 1000 раз меньше
Tt   = cell(size(tols));             % моменты времени (для графика шага)
Et   = cell(size(tols));             % ошибка |x1 - x1_точное|(t)

fprintf('\n%8s %9s %8s %16s %16s\n', 'RelTol', 'AbsTol', 'шагов', 'max|ошибка x1|', 'отн. ошибка');
for k = 1:numel(tols)
    opts = odeset('RelTol', tols(k), 'AbsTol', tols(k)*1e-3, 'Refine', 1);
    [t, x] = ode45(rhs, [0 Tend], x0, opts);      % Refine = 1: только узлы шагов

    xex = zeros(numel(t), 1);                     % точное x1 в тех же узлах
    for i = 1:numel(t)
        e = xe - expm(A*t(i))*xe;
        xex(i) = e(1);
    end
    err    = abs(x(:,1) - xex);
    errAbs = max(err);
    errRel = errAbs / max(abs(xex));

    fprintf('%8.0e %9.0e %8d %16.2e %16.2e\n', tols(k), tols(k)*1e-3, numel(t)-1, errAbs, errRel);
    Tt{k} = t;
    Et{k} = err;
end

names = arrayfun(@(r) sprintf('RelTol = %.0e', r), tols, 'UniformOutput', false);

%% 3. Автоматический выбор шага
figure('Name', 'Шаг интегрирования ode45', 'NumberTitle', 'off');
hold on;
for k = 1:numel(tols)
    plot(Tt{k}(1:end-1), diff(Tt{k}), 'o-', 'LineWidth', 1.2);
end
hold off; grid on;
set(gca, 'YScale', 'log');
legend(names, 'Location', 'best');
xlabel('t, с');  ylabel('шаг h, с');
title('Чем жёстче допуск, тем мельче шаг (и шаг подстраивается под решение)');

%% 4. Ошибка относительно точного решения
figure('Name', 'Ошибка ode45', 'NumberTitle', 'off');
hold on;
for k = 1:numel(tols)
    plot(Tt{k}(2:end), Et{k}(2:end), 'o-', 'LineWidth', 1.2);
end
hold off; grid on;
set(gca, 'YScale', 'log');
legend(names, 'Location', 'best');
xlabel('t, с');  ylabel('|x_1 - x_{1,точн}|');
title('Погрешность растёт со временем (система неустойчива), но масштабируется допуском');

%% 5. Для сравнения: ode23 (пара 2(3)) и ode45 (пара 4(5)) при допусках по умолчанию
[t23, ~] = ode23(rhs, [0 Tend], x0, odeset('Refine', 1));
[t45, ~] = ode45(rhs, [0 Tend], x0, odeset('Refine', 1));
fprintf('\nДопуски по умолчанию: ode23 - %d шагов, ode45 - %d шагов\n', ...
        numel(t23)-1, numel(t45)-1);
