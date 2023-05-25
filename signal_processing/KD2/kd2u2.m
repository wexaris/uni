% Rainers Vorza
% rv20039

1;

function signal = kd2u2(filename, shift = 0.3, attenuation = 0.6)
    [input, fs] = audioread(filename);

    % Pārvēršam par mono audio
    input = mean(input, 2);

    % Izveidojam atbalss filtru
    delay_samples = round(shift * fs);
    filter = [1; zeros(delay_samples - 1, 1); attenuation];

    % Veicam konvolūciju
    signal = conv(input, filter);
    signal = signal(1:length(input)); % Trim
    signal = signal / max(signal);    % Normalize

    audiowrite('atbalss.wav', signal, fs);
end

