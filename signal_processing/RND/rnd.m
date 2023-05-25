
% RND
x = rand(1000000, 1)
hist(x, 50)

% RND + RND
x = rand(1000000, 1) + \
    rand(1000000, 1)
hist(x, 50)

% RND + RND + RND + RND
x = rand(1000000, 1) + \
    rand(1000000, 1) + \
    rand(1000000, 1) + \
    rand(1000000, 1)
hist(x, 50)









