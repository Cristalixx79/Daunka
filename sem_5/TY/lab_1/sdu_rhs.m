function dx = sdu_rhs(t, x, inputType)
    a0 = 15;
    a1 = 5;
    a2 = 0;
    a3 = 1;
    b  = 15;

    switch inputType
        case 1
            y = 1;
        case 2
            y = sin(t);
        case 0
            y = 0;
        otherwise
            error('sdu_rhs:inputType', 'inputType должен быть 0, 1 или 2');
    end

    dx = zeros(3, 1);
    dx(1) = x(2);
    dx(2) = x(3);
    dx(3) = (b*y - a0*x(1) - a1*x(2) - a2*x(3)) / a3;
end
