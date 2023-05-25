% Rainers Vorza
% rv20039

1;

function output = file2gray(path)
  img = imread(path);

  if size(img, 3) == 1
    output = img(:,:,1); % Grayscale image
  else
    % Normalize pixel values
    img_double = double(img) / 255;

    % Calculate grayscale value using luminosity
    r_weight = 0.299;
    g_weight = 0.587;
    b_weight = 0.114;

    output = ...
      r_weight * img_double(:,:,1) + ...
      g_weight * img_double(:,:,2) + ...
      b_weight * img_double(:,:,3);

    % Scale pixel values to [0, 255]
    output = uint8(output * 255);
  endif
endfunction

function output = filter1(img, kernel)
  % Normalize pixel values
  img_double = double(img) / 255;

  if size(img, 3) == 1
    % Grayscale convolution
    output = conv2(img_double, kernel, 'same');
  else
    % Color convolution
    output = zeros(size(img));
    output(:,:,1) = conv2(img_double(:,:,1), kernel, 'same');
    output(:,:,2) = conv2(img_double(:,:,2), kernel, 'same');
    output(:,:,3) = conv2(img_double(:,:,3), kernel, 'same');
  endif

  % Wrap negative values with abs(), keeping 0 as black
  % Scale pixel values to [0, 255]
  output = uint8(abs(output) * 255);
endfunction

function output = test3(img)
  % Edge detection filter
  % More pronounced on horizontal lines, than vertical ones.
  h = [ 4  3  2;
        1  0 -1;
       -2 -3 -4];

  output = filter1(img, h);
endfunction

function output = edgifyer(img)
    % Use the Sobel operator for edge detection
    kernel_x = [-1  0  1;
                -2  0  2;
                -1  0  1];
    kernel_y = [-1 -2 -1;
                 0  0  0;
                 1  2  1];

    grad_x = filter1(img, kernel_x);
    grad_y = filter1(img, kernel_y);

    % Combine gradients
    output = sqrt(double(grad_x).^2 + double(grad_y).^2);

    % Normalize
    output = output / max(output(:));

    % Scale pixel values to [0, 255]
    output = uint8(output * 255);
end

function output = negimage(colorimg)
  % Inverse image
  output = 255 - filter1(colorimg, -1);
endfunction

