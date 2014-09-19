im   = im2double(rgb2gray(imread('peppers.png')));
out  = im;
results = im;

d2x = @(x) (x(3)-2*x(2)+x(1))/(1^2);
h   = 0.01;

for t=1:h:3
	prev = out;
	for i=2:size(im,1)-1
		for j=2:size(im,2)-1
			out(i,j) = h*(d2x(prev(i-1:i+1,j)) + d2x(prev(i,j-1:j+1))) + prev(i,j);
		end
	end
	t
% 	results = [results out];
end

imshow(out)