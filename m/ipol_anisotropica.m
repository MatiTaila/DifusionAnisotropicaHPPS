close all;
clear all;
home;

%% Params

sigma	= 0.05;
lambda	= 0.1;
nIter	= 50;
track	= 0;   % ir viendo como itera
det		= 1;   % 0: Leclerc (exponencial)
			   % 1: Lorentziano

%% Img + Ruido

% path	= 'lena.png';
path	= 'milla.png';
% path	= 'peppers.png';
im		= im2double(rgb2gray(imread(path)));
% im		= [.2*ones(200,200); .8*ones(200, 200)];

[M,N,O] = size(im);
imR		= im + randn(M,N,O)*0.05;

%% Detector

figure;
	plot(0:255,1./(1+((0:1/255:1)/sigma).^2),'color',[243, 132, 0]/256, 'linewidth',3 )
	hold on
	plot(0:255,exp(-((0:1/255:1)/sigma).^2), 'color',[0,0,128]/256    , 'linewidth', 3 )
	legend('\fontsize{14}Lorentziano', '\fontsize{14}Leclerc (exponencial)')
    axis tight
    xlabel('\fontsize{16}Diferencia en niveles de gris')
    ylabel('\fontsize{16}g')

%% La Majuga	

im_out = imR;
im_out = im;

for t=1:nIter
	Dn = ([im_out(1,:) ; im_out(1:end-1,:)] - im_out);
	Ds = ([im_out(2:end,:) ; im_out(end,:)] - im_out);
	De = ([im_out(:,2:end) im_out(:,end)] - im_out);
    Dw = ([im_out(:,1) im_out(:,1:end-1)] - im_out);
	
	if det
		gDn = 1./(1+(Dn/sigma).^2);
		gDs = 1./(1+(Ds/sigma).^2);
		gDe = 1./(1+(De/sigma).^2);
		gDw = 1./(1+(Dw/sigma).^2);
	else
		gDn = exp(-(Dn/sigma).^2);
		gDs = exp(-(Ds/sigma).^2);
		gDe = exp(-(De/sigma).^2);
		gDw = exp(-(Dw/sigma).^2);
	end
	
	im_out = im_out + lambda*(gDn.*Dn + gDs.*Ds + gDe.*De + gDw.*Dw);
	
	if track
		figure(10);
			imshow(im_out);
			drawnow;
			pause(0.1);
	end
end

figure; imshow([imR im_out],[0 1]);