% Rainers Vorza
% rv20039

1;

function output = kd2u3(filename, filter)
    img = imread(filename);

    % Veicam konvolūciju ar filtra matricu katram krāsu kanālam atsevišķi
    output = zeros(size(img));
    for channel = 1:3
        output(:, :, channel) = conv2(double(img(:, :, channel)), filter, 'same');
    end

    % Saglabājam jaunā failā
    imwrite(uint8(output), "filtered.png");
end

% High-pass filtrs attēlam
% Pateicoties augstajai (40) vērtībai centrā un negatīvajām vērtībām apkārt,
% filtrs izceļ kontrastu, palīdzot noteikt robežas starp objektiem.
% Tas strādā īpaši labi uz labi izgaismotiem attēliem, sliktāk uz tumšiem.
% Pateicoties izteiktajai vērtību atšķirībai (40/-1/-2/-3/-4),
% filtrs arī izspiež krāsu no attēliem, atstājot tos gandrīz melnbaltus.
filter = [-4 -2 -1 -2 -4;
          -2 -1  0 -1 -2;
          -1  0 40  0 -1;
          -2 -1  0 -1 -2;
          -4 -2 -1 -2 -4];

%kd2u3("test.jpg", filter);

