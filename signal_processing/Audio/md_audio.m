% Rainers Vorza
% rv20039

1;

function retval = md_audio(in_file)
  % Read the audio file
  [data, rate] = audioread(in_file);

  % Combine any channels
  data = mean(data, 2);

  % normalize the signal
  processed = data / max(abs(data));

  % Apply median filter
  medianFilter = ones(1, 10) / 10;
  processed = conv(processed, medianFilter, 'same');

  % Remove silence
  silenceThreshold = 1; % RMS multiplier
  silenceDuration = 200; % milliseconds
  processed = removeSilence(processed, rate, silenceThreshold, silenceDuration);

  % Apply low-pass filter
  lowPassCutoff = 3500; % Hz
  lowPassOrder = 30;
  lowFilter = lowPassFilterKernel(rate, lowPassCutoff, lowPassOrder);
  processed = conv(processed, lowFilter, 'same');

  % normalize the signal
  retval = processed / max(abs(processed));
endfunction

function filter = lowPassFilterKernel(rate, cutoff, order)
  % Compute filter coefficients
  nyquist = rate / 2;
  cutoffNormal = cutoff / nyquist;

  n = 0:order;
  w = blackman(order+1)';
  h = sinc(2 * cutoffNormal * (n - (order/2)));
  h = h .* w;
  filter = h / sum(h);
  %plot(filter);
end

function filtered = removeSilence(data, rate, rmsFactor, durationMillis)
  % Calculate the quiet threshold with RMS
  threshold = sqrt(mean(data .^ 2)) * rmsFactor;

  % Create a quetness bitfield
  quiet = abs(data) < threshold;

  % Convert silence duration to samples
  durationSamples = round(rate * durationMillis * 0.001);

  % Kernel for counting quiet samples
  quietCounterKernel = ones(durationSamples, 1);

  % Count quiet samples
  quietCounter = conv(double(quiet), quietCounterKernel, 'same');

  % Shift samples to remove intitial delay
  shiftedQuietCounter = circshift(quietCounter, round(-durationSamples * 0.9));

  % Check both bitfields to find removable samples
  removable = quietCounter >= durationSamples & shiftedQuietCounter >= durationSamples;

  %plot(removable);

  filtered = data(~removable);
endfunction

function md_test()
  % Define path to input file
  in_file = 'test2.ogg';

  % Get file sample rate
  [original, rate] = audioread(in_file);

  % Process audio
  processed = md_audio(in_file);

  %plot(processed);

  % Save processed audio
  audiowrite('processed.ogg', processed, rate);
endfunction

