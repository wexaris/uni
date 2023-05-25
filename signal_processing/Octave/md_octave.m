
% Izdomāt īsu bet efektīvu Octave komandu (izteiksmi),
% kas izmantojot dažādus operatorus izveido sekojošu matricu  A:
%  1  3  5   7   9   11
%  1  4  9   16  25  36
%  4  8  16  32  64  128

A = [1:2:11;                     % nepāra skaitļi
     cumsum(1:2:11);             % nepāra skaitļu summas
     repelem(2, 1, 6) .^ [2:7]]  % pakāpes ar bāzi 2


% Izdomāt tādas matricas B, C un D, lai tās reizinot ar A iegūst sekojošo:
%  A * B = ( A kolonnu 2 un 5 summa )
%  C * A = ( A matricas otrā rinda )
%  D * A = ( A matrica kurā 1 un 2 rindas ir samainītas vietām )

% inverse(A) * [12; 29; 72]
B = (pinv(A) * (A(:,2) + A(:,5)))

% [1 4 9 16 25 36] * inverse(A)
C = (A(2,:) * pinv(A))

% | 1  4  9   16  25  36  |
% | 1  3  5   7   9   11  | * inverse(A)
% | 4  8  16  32  64  128 |
D = ([A(2,:); A(1,:); A(3,:);] * pinv(A))


% Izdomāt 'vektora' matricas (tikai viena rinda vai viena kolonna)
% S, T, V un W tādas, lai to reizinājumi būtu sekojoši:
%  S * T =
%   1 2 3
%   1 2 3
%  V * W =
%   1 1
%   2 2
%   3 3

S = [1; 1]
T = [1, 2, 3]

V = [1; 2; 3]
W = [1, 1]

