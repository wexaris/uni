% Rainers Vorza
% rv20039

1;

function signal = kd2u1()
    fs = 44100;   % Mērījumu biežums
    duration = 1; % Signāla ilgums (1 sekunde)

    t = linspace(0, duration, duration * fs);

    K = 2^(1/12);       % Koeficients starp notīm
    f_La = 440;         % La
    f_Do = f_La / K^9;  % Do
    f_Mi = f_La / K^5;  % Mi
    f_Sol = f_La / K^2; % Sol

    signal_Do = sin(2 * pi * f_Do * t);
    signal_Mi = sin(2 * pi * f_Mi * t);
    signal_Sol = sin(2 * pi * f_Sol * t);

    signal = signal_Do + signal_Mi + signal_Sol;
    signal = signal / max(signal); % Normalizācija

    audiowrite('akords.wav', signal, fs);
end

