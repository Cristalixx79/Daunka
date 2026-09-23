a0 = 15;  a1 = 5;  a2 = 0;  a3 = 1;  b = 15;
x0_zero = [0 0 0]; x0_var6 = [1 0.5 0.1];
Tend  = 5;
tspan = linspace(0, Tend, 501);
opts  = odeset('RelTol', 1e-3, 'AbsTol', 1e-6);

exper = {
    'y = 1(t), нулевые НУ',                                  x0_zero,  1;
    'y = sin(t), нулевые НУ',                                x0_zero,  2;
    'y = 1(t), НУ [1 0.5 0.1]',                              x0_var6,  1;
    'y = sin(t), НУ [1 0.5 0.1]',                            x0_var6,  2;
    'y = 0 (свободное движение), НУ [1 0.5 0.1]',            x0_var6,  0 };

for k = 1:size(exper, 1)
    ttl = exper{k, 1};
    x0  = exper{k, 2};
    u   = exper{k, 3};
    [t, x] = ode45(@(t, x) sdu_rhs(t, x, u), tspan, x0, opts);

    switch u
        case 1
            y = ones(size(t)); ylab = 'y(t) = 1(t)';
        case 2
            y = sin(t); ylab = 'y(t) = sin(t)';
        otherwise
            y = zeros(size(t)); ylab = 'y(t) = 0';
    end
    leg = {'x_1(t)', 'x_2(t)', 'x_3(t)', ylab};
    if k == 1
        leg{1} = 'x_1(t) = h(t)';
        leg{2} = 'x_2(t) = w(t)';
    end

    figure('Name', ttl, 'NumberTitle', 'off');
    subplot(2, 1, 1);
    plot(t, x(:,1), 'b-',  'LineWidth', 1.5); hold on;
    plot(t, x(:,2), 'g--', 'LineWidth', 1.5);
    plot(t, x(:,3), 'r-.', 'LineWidth', 1.5);
    plot(t, y,      'k-',  'LineWidth', 2);
    hold off; grid on;
    legend(leg, 'Location', 'best');
    xlabel('t, с');  ylabel('x_i(t), y(t)');
    title(ttl);
end