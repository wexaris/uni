% Rainers Vorza
% rv20039

1;

% Get first second of audio from sample
function audio = onesec(sample, fs)
  audio = sample(1:fs);
endfunction

% Generate 0.25 second samples of Do-Re-Mi-Fa-Sol-La-Ti-Do
function audio = oneoctave(fs)
  note_fs = fs * 0.25;
  audio = [
    onenote(note_fs, 140);
    onenote(note_fs, 160);
    onenote(note_fs, 180);
    onenote(note_fs, 190);
    onenote(note_fs, 200);
    onenote(note_fs, 220);
    onenote(note_fs, 260);
    onenote(note_fs, 270) ];
endfunction

function note = onenote(fs, freq)
  t = linspace(0, 1, fs);
  s = sin(t * 2 * pi * freq);
  note = s';
endfunction

% Generate audio from 3 sine waves at frequencies f and amplitudes a
function audio = sine3(f1, f2, f3, a1, a2, a3, fs, len)
  t = linspace(0, len, len * fs);

  s1 = a1 * sin(t * 2 * pi * f1);
  s2 = a2 * sin(t * 2 * pi * f2);
  s3 = a3 * sin(t * 2 * pi * f3);

  audio = s1 + s2 + s3;
endfunction

% Apply an ADSR envelope effect to an audio sample
function audio = adsr(sample, fs, attack, decay, sustain, release)
    len = length(sample);
    t = linspace(0, len / fs, len);

    a = linspace(0, 1, attack * fs);
    d = linspace(1, sustain, decay * fs);
    r = linspace(sustain, 0, release * fs);

    envelope = zeros(size(sample));
    envelope(t < attack) = a;
    envelope(t >= attack & t < attack + decay) = d;
    envelope(t >= attack + decay & t < len / fs - release) = sustain;
    envelope(t >= len / fs - release) = r;

    audio = sample .* envelope;
endfunction

% Synthesize audio using given base frequency
function audio = mysynth(freq, fs)
    duration = 1; % seconds
    t = linspace(0, duration, fs * duration);

    base = sin(t * 2 * pi * freq);

    harmonics = 10; % number of harmonics
    modulation = sin(t * 2 * pi * freq);

    % add harmonics
    for i = 2:harmonics
        harmonic = sin(t * 2 * pi * freq * i);
        amplitude = 1 / i;
        modulation = modulation + amplitude * harmonic;
    end

    audio = modulation .* base;
    audio = adsr(audio, fs, 0.2, 0.2, 0.5, 0.25);
endfunction


function md_test()
  freq = 440;
  fs = 44100;
  data = mysynth(freq, fs);

  audiowrite('test.ogg', data, fs);
endfunction

